#!/usr/bin/env python3
# s170: slice GLOBAL_ASM functions 8-140 insns, not named in repair_log / docs/sessions/s*.md / HANDOFF / skip list
import os,re,glob
R='/Users/sorikairo/conker-wt/a'; os.chdir(R+'/conker')
size={}
for l in open(R+'/tools/eu_port/m2c/all.txt').read().split('\n')[1:]:
    t=l.split()
    if len(t)>=4: size[t[2]]=int(t[0])
excl=set()
txt=open(R+'/tools/eu_port/repair_log.tsv').read()+open(R+'/HANDOFF.md').read()
for p in glob.glob(R+'/docs/sessions/s*.md'): txt+=open(p).read()
excl|=set(re.findall(r'func_(?:eu_)?[0-9A-F]{8}',txt))
skip='''func_15173090 func_15148E34 func_1517F18C func_1515C388 func_151777CC func_15160310 func_1517E7FC func_1517F01C func_1515E7E8 func_1514948C func_eu_151670C0 func_1518CFF0 func_1516A964'''.split()
excl|=set(skip)
rows=[]
for c in glob.glob('src_eu/*.c'):
    b=os.path.basename(c)
    s=open(c).read()
    addrs=[int(a,16) for a in re.findall(r'(?m)^[A-Za-z][^;=\n]*?\bfunc_(?:eu_)?([0-9A-F]{8})\s*\([^;]*$',s)+re.findall(r'GLOBAL_ASM\(".*/func_(?:eu_)?([0-9A-F]{8})\.s',s)]
    if not addrs: continue
    if not b.startswith('debugger') and not (0x15130000<=min(addrs)<=0x1518FFFF): continue
    for f in re.findall(r'GLOBAL_ASM\("asm/nonmatchings/[^/]+/(func_\w+)\.s',s):
        n=size.get(f)
        if n is None or n<8 or n>140 or f in excl: continue
        rows.append((n,b,f))
rows.sort()
print('# s170 targets: slice GLOBAL_ASM 8-140 insns, not in repair_log / any sNN.md / HANDOFF / s170 skip list; cols: insns file func')
for n,b,f in rows: print(n,b,f)
