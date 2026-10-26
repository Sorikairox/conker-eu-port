#!/usr/bin/env python3
# usage: voidret.py indir outdir -- in each draft, local prototypes `s32 func_X(...)` whose
# result is never used (every call is a bare statement) become `void func_X(...)`.
# m2c types unused call results as s32; a non-void return makes IDO keep v0 out of the way,
# which shifts register allocation (breakable_cb_settle). Writes only changed drafts.
import sys,os,re,glob
ind,outd=sys.argv[1],sys.argv[2]; os.makedirs(outd,exist_ok=True)
n=0
for f in glob.glob(os.path.join(ind,'func_*.c')):
    src=open(f).read(); out=src
    for m in re.finditer(r'^(?:s32|u8 \*|s32 \*) (func_\w+)\(.*\);$',src,re.M):
        name=m.group(1)
        uses=[u for u in re.finditer(r'\b%s\b'%name,src) if u.start()!=m.start(1)]
        if uses and all(re.match(r'^\s+$',src[src.rfind('\n',0,u.start())+1:u.start()]) for u in uses):
            out=out.replace(m.group(0),'void'+m.group(0)[m.group(0).index(' '+name):],1)
    if out!=src:
        open(os.path.join(outd,os.path.basename(f)),'w').write(out); n+=1
print(n)
