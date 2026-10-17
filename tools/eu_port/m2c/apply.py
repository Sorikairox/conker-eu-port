#!/usr/bin/env python3
# Runs inside the container from /conker/conker.
# usage: apply.py gen_dir   -- inserts screen.txt OK candidates into src_eu, builds the touched
# objects in parallel, checks whole files against the ROM; for failing files retries the
# candidates one at a time. Prints ACCEPT/REJECT lines.
import sys,os,re,subprocess,struct
sys.path.insert(0,'../tools/eu_port')
import check_files as cf
from elftools.elf.elffile import ELFFile
gd=sys.argv[1]
rom=open('conker.eu.bin','rb').read(); ranges=cf.file_ranges(); owned=cf.owned_sections()
def prag(f): return re.compile(r'#pragma GLOBAL_ASM\("[^"]*/%s\.s"\)'%f)
def datasz(o):
    with open(o,'rb') as fh:
        return {s.name:s['sh_size'] for s in ELFFile(fh).iter_sections() if s.name in ('.rodata','.data','.rdata','.sdata')}
def build(ps):
    # files owning .rodata: re-plan the GLOBAL_ASM functions' rodata for the current C/asm split
    st=[p[len('src_eu/'):-2] for p in ps if p[len('src_eu/'):-2] in owned]
    if st: subprocess.run(['python3','../tools/eu_port/rodata_inject.py']+st,capture_output=True)
    objs=['build/'+p+'.o' for p in ps]
    for o in objs:
        if os.path.exists(o): os.remove(o)
    subprocess.run(['make','VERSION=eu','-j8','-k']+objs,capture_output=True,text=True)
def ok(p,base):
    o='build/'+p+'.o'
    if not os.path.exists(o): return False
    name=p[len('src_eu/'):-2]; start,end=ranges[name]
    data,masked=cf.text_words(o)
    want=rom[start:end]
    if name in ('init_eu_289A0','game_eu_227BF0','debugger_eu_259B40'): want=rom[start:start+len(data)]
    if len(data)!=len(want): return False
    for off in range(0,len(data),4):
        a=struct.unpack('>I',data[off:off+4])[0]; b=struct.unpack('>I',want[off:off+4])[0]
        m=masked.get(off,0xFFFFFFFF)
        if (a&m)!=(b&m): return False
    # sections the file owns (rodata_split.py --own) must match the ROM; others must not grow
    base=dict(base); cur=datasz(o)
    for sec,a,b in owned.get(name,[]):
        if cf.section_diff(o,sec,rom[a:b]): return False
        base.pop(sec,None); cur.pop(sec,None)
    return cur==base
cands={}
for l in open(os.path.join(gd,'screen.txt')):
    r,f,p=l.split()
    if r=='OK': cands.setdefault(p,[]).append(f)
ps=sorted(cands)
build(ps); base={p:datasz('build/'+p+'.o') for p in ps}
orig={p:open(p).read() for p in ps}
def insert(src,fs):
    for f in fs:
        code=open(os.path.join(gd,f+'.c')).read().strip('\n')
        m=prag(f).search(src)
        src=src[:m.start()]+code+src[m.end():]
    return src
new={p:insert(orig[p],cands[p]) for p in ps}  # all drafts first: a failure must not truncate a file
for p in ps: open(p,'w').write(new[p])
build(ps)
bad=[p for p in ps if not ok(p,base[p])]
for p in ps:
    if p not in bad:
        for f in cands[p]: print('ACCEPT',f,p)
for p in bad:
    cur=orig[p]; open(p,'w').write(cur)
    for f in cands[p]:
        t=insert(cur,[f]); open(p,'w').write(t); build([p])
        if ok(p,base[p]): cur=t; print('ACCEPT',f,p)
        else: open(p,'w').write(cur); print('REJECT',f,p)
    build([p])
