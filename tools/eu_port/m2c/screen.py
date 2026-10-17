#!/usr/bin/env python3
# Runs inside the container from /conker/conker.
# usage: screen.py gen_dir [jobs]
# Screens each gen_dir/<func>.c in a standalone TU (the source file with all GLOBAL_ASM
# pragmas dropped and the candidate in place of its own pragma), compiled directly with the
# file's cc flags, and compares the function with its .s (relocs masked, reloc symbol names
# must appear in the asm line, no relocs to section symbols). Writes gen_dir/screen.txt.
import sys,os,re,glob,subprocess,shlex
from multiprocessing import Pool
from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection
WORD_RE = re.compile(r"/\*\s+[0-9A-F]+\s+([0-9A-F]+)\s+([0-9A-F]{8})\s+\*/\s*(.*)")
PRAG = re.compile(r'#pragma GLOBAL_ASM\("([^"]*)/(\w+)\.s"\)')
gd=sys.argv[1]; jobs=int(sys.argv[2]) if len(sys.argv)>2 else 8
VERB=[''] if os.environ.get('SCREEN_V') else None
TMP=os.environ.get('SCREEN_TMP','build/screen'); os.makedirs(TMP,exist_ok=True); os.makedirs(os.path.join(gd,'errs'),exist_ok=True)

def asm_words(path):
    w,t=[],[]
    for line in open(path):
        m=WORD_RE.search(line)
        if m: w.append(int(m.group(2),16)); t.append(m.group(3))
    return w,t

def cc_cmd(p):
    r=subprocess.run(['make','-n','-B','VERSION=eu','build/'+p+'.o'],capture_output=True,text=True).stdout
    for l in r.split('\n'):
        if '/cc ' in l and ' -c ' in l:
            a=shlex.split(l)
            i=a.index('-o'); a=a[:i]+a[i+2:]   # drop -o out
            a=[x for x in a if not x.endswith('.c')]
            return a
    return None

def check_func(o,f,spath):
    ref,reft=asm_words(spath)
    with open(o,'rb') as fh:
        e=ELFFile(fh)
        text=e.get_section_by_name('.text'); data=text.data()
        symtab=e.get_section_by_name('.symtab')
        tidx=[i for i,s in enumerate(e.iter_sections()) if s.name=='.text'][0]
        fs=sorted((s['st_value'],s['st_size'],s.name) for s in symtab.iter_symbols() if s['st_shndx']==tidx and s['st_info']['type']=='STT_FUNC')
        ent=[x for x in fs if x[2]==f]
        if not ent: return 'NOSYM'
        addr,size,_=ent[0]
        if size==0:
            nx=[x[0] for x in fs if x[0]>addr]; size=(nx[0] if nx else len(data))-addr
        rels={}
        for sec in e.iter_sections():
            if isinstance(sec,RelocationSection) and sec.name=='.rel.text':
                for rr in sec.iter_relocations():
                    off=rr['r_offset']
                    if addr<=off<addr+size:
                        sym=symtab.get_symbol(rr['r_info_sym'])
                        rels[off]=(rr['r_info_type'],sym.name,sym['st_info']['type'])
    mine=[int.from_bytes(data[addr+i:addr+i+4],'big') for i in range(0,size,4)]
    while len(ref)>len(mine) and ref[-1]==0: ref.pop()
    while len(mine)>len(ref) and mine[-1]==0: mine.pop()
    if len(mine)!=len(ref):
        if VERB:
            for i in range(max(len(mine),len(ref))):
                a=ref[i] if i<len(ref) else 0; b=mine[i] if i<len(mine) else 0
                VERB.append('%s %08X %08X  %s'%('  ' if a==b else '**',a,b,reft[i] if i<len(reft) else ''))
        return 'SIZE%+d'%(len(mine)-len(ref))
    n=0
    for i,(a,b) in enumerate(zip(ref,mine)):
        off=addr+i*4
        m=0xFFFFFFFF
        if off in rels:
            t,name,st=rels[off]
            if st=='STT_SECTION' or not name: return 'SECREL'
            if not re.search(r'\b%s\b'%re.escape(name),reft[i]):
                n+=1
                if VERB: VERB.append('** %08X %08X  %s  [reloc %s]'%(a,b,reft[i],name))
                continue
            m={4:0xFC000000,5:0xFFFF0000,6:0xFFFF0000}.get(t,0)
        if (a&m)!=(b&m): n+=1
        if VERB: VERB.append('%s %08X %08X  %s'%('  ' if (a&m)==(b&m) else '**',a,b,reft[i]))
    return 'OK' if n==0 else 'DIFF%d'%n

def work(item):
    p,funcs=item
    src=open(p).read()
    cmd=cc_cmd(p)
    out=[]
    if cmd is None: return [(f,p,'NOCMD') for f in funcs]
    for f in funcs:
        m=None
        for mm in PRAG.finditer(src):
            if mm.group(2)==f: m=mm
        if not m: out.append((f,p,'NOPRAGMA')); continue
        spath=m.group(1)+'/'+f+'.s'
        code=open(os.path.join(gd,f+'.c')).read()
        tu=src[:m.start()]+'\n'+code+'\n'+src[m.end():]
        tu=PRAG.sub('',tu)
        cpath=os.path.join(TMP,f+'.c'); opath=os.path.join(TMP,f+'.o')
        open(cpath,'w').write(tu)
        if os.path.exists(opath): os.remove(opath)
        r=subprocess.run(cmd+['-o',opath,cpath],capture_output=True,text=True)
        if r.returncode or not os.path.exists(opath):
            res='CERR'
            em=[l for l in (r.stdout+r.stderr).split('\n') if 'Error' in l]
            open(os.path.join(gd,'errs',f+'.txt'),'w').write('\n'.join(em[:3]))
        else:
            try: res=check_func(opath,f,spath)
            except Exception as ex: res='EXC'
            if VERB: open(os.path.join(gd,f+'.diff'),'w').write('\n'.join(VERB)); del VERB[1:]
        out.append((f,p,res))
        for x in (cpath,opath):
            if os.path.exists(x): os.remove(x)
    return out

f2p={}
for p in glob.glob('src_eu/**/*.c',recursive=True):
    for m in PRAG.finditer(open(p).read()): f2p[m.group(2)]=p
groups={}
for g in sorted(glob.glob(os.path.join(gd,'func_*.c'))):
    f=os.path.basename(g)[:-2]
    if f in f2p: groups.setdefault(f2p[f],[]).append(f)
items=sorted(groups.items(),key=lambda x:-len(x[1]))
with open(os.path.join(gd,'screen.txt'),'w') as fo, Pool(jobs) as pool:
    for res in pool.imap_unordered(work,items):
        for f,p,r in res: fo.write('%s %s %s\n'%(r,f,p))
        fo.flush()
