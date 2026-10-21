import glob,re,os
R='/Users/sorikairo/conker-wt/a/'
yaml=open(R+'conker/conker.eu.yaml').read()
src={}
for p in glob.glob(R+'conker/src_eu/*.c'):
    for m in re.finditer(r'GLOBAL_ASM\("asm/nonmatchings/(\w+)/(func_\w+)\.s"\)',open(p).read()):
        src[m.group(2)]=m.group(1)
out=set()
for d in sorted(glob.glob(R+'docs/sessions/s1[2-6]*_drafts/*.c')):
    t=open(d).read()
    if not re.search(r'extern f32 D_800',t): continue
    for m in re.finditer(r'^[A-Za-z].*?\b(func_[0-9A-F]{8})\([^;{]*\)\s*\{?\s*$',t,re.M):
        f=m.group(1)
        if f not in src: continue
        st=src[f]; h=re.search(r'([0-9A-F]{5,6})$',st)
        if not h or not (0x15D000<=int(h.group(1),16)<=0x1BB000): continue
        if not re.search(r'\.rodata, %s\]'%st,yaml): continue
        out.add((f,st,os.path.relpath(d,R)))
for o in sorted(out): print(*o)
