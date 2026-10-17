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
            if os.environ.get('SCREEN_OPT'):   # e.g. SCREEN_OPT="-O2 -g": replaces the file's -O/-g flags
                a=[x for x in a if not re.match(r'-(O\d?|g\d?)$',x)]+os.environ['SCREEN_OPT'].split()
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
                        nm=sym.name
                        if sym['st_info']['type']=='STT_SECTION':
                            nm=e.get_section(sym['st_shndx']).name
                        rels[off]=(rr['r_info_type'],nm,sym['st_info']['type'])
    rod=_rodata(e_path=o) if any(st=='STT_SECTION' for _,_,st in rels.values()) else None
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
    hiw={}
    for i,(a,b) in enumerate(zip(ref,mine)):
        off=addr+i*4
        m=0xFFFFFFFF
        if off in rels:
            t,name,st=rels[off]
            if st=='STT_SECTION' and name in ('.rodata',) and rod is not None and t in (5,6):
                # literal / string / jump table in the TU's own .rodata: compare its contents with
                # what the asm's D_/jtbl_ symbol points at in the ROM
                if t==5: hiw[name]=(b&0xFFFF)<<16
                else:
                    tgt=re.search(r'%lo\((\w+)\)',reft[i])
                    ok=False
                    if tgt and name in hiw:
                        lo=b&0xFFFF; lo=lo-0x10000 if lo&0x8000 else lo
                        ok=_cmp_rodata(rod,hiw[name]+lo,tgt.group(1),reft[i],addr)
                    if not ok:
                        n+=1
                        if VERB: VERB.append('** %08X %08X  %s  [rodata contents differ]'%(a,b,reft[i]))
                        continue
                m=0xFFFF0000
                if (a&m)!=(b&m): n+=1
                if VERB: VERB.append('%s %08X %08X  %s'%('  ' if (a&m)==(b&m) else '**',a,b,reft[i]))
                continue
            if st=='STT_SECTION' or not name: return 'SECREL'+(':%s:%d'%(name,t) if VERB else '')
            if not re.search(r'\b%s\b'%re.escape(name),reft[i]):
                n+=1
                if VERB: VERB.append('** %08X %08X  %s  [reloc %s]'%(a,b,reft[i],name))
                continue
            m={4:0xFC000000,5:0xFFFF0000,6:0xFFFF0000}.get(t,0)
        if (a&m)!=(b&m): n+=1
        if VERB: VERB.append('%s %08X %08X  %s'%('  ' if (a&m)==(b&m) else '**',a,b,reft[i]))
    return 'OK' if n==0 else 'DIFF%d'%n

sys.path.insert(0,'../tools/eu_port')
_SYMS=None
def _symaddr(name):
    global _SYMS
    if _SYMS is None:
        _SYMS={}
        for f in ('undefined_syms_auto.txt','undefined_syms.eu.txt','symbol_addrs.eu.txt'):
            if os.path.exists(f):
                for l in open(f):
                    m=re.match(r'\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)',l)
                    if m: _SYMS.setdefault(m.group(1),int(m.group(2),16))
    if name in _SYMS: return _SYMS[name]
    m=re.match(r'(?:D|jtbl)_([0-9A-F]{8})',name)
    return int(m.group(1),16) if m else None

_ROM=None
def _romread(vaddr,n):
    """bytes at a data-segment vram address, from conker.eu.bin"""
    global _ROM
    import datarefs
    if _ROM is None: _ROM=(open('conker.eu.bin','rb').read(),datarefs.segments())
    data,segs=_ROM
    for nm,sg in segs.items():
        if nm.endswith('_data') and 'vram' in sg and sg['vram']<=vaddr<sg['vram']+(sg['end']-sg['start']):
            r=vaddr-sg['vram']+sg['start']; return data[r:r+n]
    return None

def _rodata(e_path):
    with open(e_path,'rb') as fh:
        e=ELFFile(fh)
        s=e.get_section_by_name('.rodata')
        if s is None: return None
        rel={}
        rs=e.get_section_by_name('.rel.rodata')
        if rs is not None:
            for rr in rs.iter_relocations(): rel[rr['r_offset']]=rr['r_info_type']
        return (s.data(),rel)

def _cmp_rodata(rod,off,sym,line,faddr):
    data,rel=rod
    va=_symaddr(sym)
    if va is None: return False
    if 'lwc1' in line or 'swc1' in line: n=4
    elif 'ldc1' in line or 'sdc1' in line: n=8
    elif sym.startswith('jtbl_'):
        # jump table: entries relative to the function start must agree
        rv=None; i=0
        while off+i+4<=len(data) and (off+i) in rel:
            mine=int.from_bytes(data[off+i:off+i+4],'big')-faddr
            rw=_romread(va+i,4)
            if rw is None: return False
            ref=int.from_bytes(rw,'big')
            if rv is None: rv=ref-mine   # function vram
            if ref-mine!=rv: return False
            i+=4
        return i>0
    else:
        # string or table: compare up to the first NUL (at least 4 bytes)
        z=data.find(b'\0',off); n=max(4,(z-off+1) if z>=0 else 4)
    rb=_romread(va,n)
    return rb is not None and data[off:off+n]==rb

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
