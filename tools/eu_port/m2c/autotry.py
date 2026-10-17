#!/usr/bin/env python3
# Runs inside the container from /conker/conker.
# usage: autotry.py gen_dir [limit]  -- for each gen/<func>.c try replacing the pragma; keep if the
# whole object matches the ROM and no data sections grew. Writes results to gen_dir/results.txt
import sys,os,re,glob,subprocess,struct
sys.path.insert(0,'../tools/eu_port')
import check_files as cf
from elftools.elf.elffile import ELFFile
gd=sys.argv[1]; limit=int(sys.argv[2]) if len(sys.argv)>2 else 10**9
rom=open('conker.eu.bin','rb').read()
ranges=cf.file_ranges()
done=set()
resf=os.path.join(gd,'results.txt')
if os.path.exists(resf):
    for l in open(resf):
        done.add(l.split()[1])
# map func -> file
f2p={}
for p in glob.glob('src_eu/**/*.c',recursive=True):
    for m in re.finditer(r'#pragma GLOBAL_ASM\("[^"]*/(\w+)\.s"\)',open(p).read()):
        f2p[m.group(1)]=p
def datasizes(o):
    with open(o,'rb') as fh:
        e=ELFFile(fh); r={}
        for s in e.iter_sections():
            if s.name in ('.rodata','.data','.sdata','.rdata'): r[s.name]=s['sh_size']
        return r
def build(p):
    o='build/'+p+'.o'
    if os.path.exists(o): os.remove(o)
    r=subprocess.run(['make','VERSION=eu',o],capture_output=True,text=True)
    return r.returncode==0, o
def check(p,o):
    name=p[len('src_eu/'):-2]
    start,end=ranges[name]
    data,masked=cf.text_words(o)
    want=rom[start:end] if end else rom[start:start+len(data)]
    if name in ('init_eu_289A0','game_eu_227BF0','debugger_eu_259B40'):
        want=rom[start:start+len(data)]
    if len(data)!=len(want): return 'SIZE'
    n=0
    for off in range(0,len(data),4):
        a=struct.unpack('>I',data[off:off+4])[0]; b=struct.unpack('>I',want[off:off+4])[0]
        m=masked.get(off,0xFFFFFFFF)
        if (a&m)!=(b&m): n+=1
    return 'OK' if n==0 else 'DIFF%d'%n
base={}
cnt=0
out=open(resf,'a')
for g in sorted(glob.glob(os.path.join(gd,'func_*.c'))):
    f=os.path.basename(g)[:-2]
    if f in done or f not in f2p: continue
    if cnt>=limit: break
    cnt+=1
    p=f2p[f]
    orig=open(p).read()
    if p not in base:
        ok,o=build(p)
        base[p]=datasizes(o) if ok else None
    code=open(g).read().strip('\n')
    m=re.search(r'#pragma GLOBAL_ASM\("[^"]*/%s\.s"\)'%f,orig)
    new=orig[:m.start()]+code+orig[m.end():]
    open(p,'w').write(new)
    ok,o=build(p)
    if not ok: res='CERR'
    else:
        res=check(p,o)
        if res=='OK' and datasizes(o)!=base[p]: res='DATA'
    if res!='OK':
        open(p,'w').write(orig)
    out.write('%s %s %s\n'%(res,f,p)); out.flush()
    print(res,f,p,flush=True)
# rebuild touched objects to restore state
for p in base: build(p)
