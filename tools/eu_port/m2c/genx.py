#!/usr/bin/env python3
# usage: genx.py outdir min max [m2c flags...]  -- one m2c draft per function (instruction count
# in [min,max], from all.txt) with extra m2c flags, e.g. --void or --reg-vars saved.
# (macOS spawns workers with the truncated argv, so the flags travel with each item.)
# Same post-processing as gen2.py; writes outdir/<func>.c. Needs venv/ (see gen2.py).
import sys,re,os
sys.argv,args=sys.argv[:4],sys.argv[4:]
import gen2
from multiprocessing import Pool
od,mn,mx=sys.argv[1],int(sys.argv[2]),int(sys.argv[3])
def work(a):
    f,p,sp,args=a
    c=gen2.m2c(sp,gen2.ctx(p),args)
    if not c: return 0
    os.makedirs(od,exist_ok=True)
    open('%s/%s.c'%(od,f),'w').write(gen2.fixscale(c)); return 1
if __name__=='__main__':
    items=[]
    for l in open(gen2.S+'/all.txt').read().split('\n')[1:]:
        if not l: continue
        ins,p,f,jt,fl=l.split(); ins=int(ins)
        if ins>mx or ins<mn or jt=='True': continue
        m=re.search(r'#pragma GLOBAL_ASM\("([^"]*/%s\.s)"\)'%f,open(p).read())
        if m: items.append((f,p,m.group(1),args))
    with Pool(8) as pool: print(sum(pool.map(work,items,chunksize=4)),len(items))
