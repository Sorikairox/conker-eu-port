#!/usr/bin/env python3
# usage: narrow.py indir outdir -- give parameters their narrow type when m2c masks them:
# a param `s32 argN` used as `(argN & 0xFF)` becomes `u8 argN` (0xFFFF: u16) and the masks go.
# IDO homes a u8/u16 parameter and re-truncates it on entry (`sw a2, 8(sp); andi t6, a2, 0xFF;
# move a2, t6`), which m2c does not reproduce (session 6: the "SIZE-1" handlers with an
# `(obj, msg, u8 event)` signature). Writes only changed drafts.
import sys,os,re,glob
# Optional third arg: a u8params.py list; those params are narrowed even without a mask.
ind,outd=sys.argv[1],sys.argv[2]; os.makedirs(outd,exist_ok=True)
force={}
if len(sys.argv)>3:
    for l in open(sys.argv[3]):
        f,_,k,t=l.split(); force.setdefault(f,{})['arg'+k]=t
n=0
for f in glob.glob(os.path.join(ind,'func_*.c')):
    src=open(f).read(); name=os.path.basename(f)[:-2]
    m=re.search(r'^([^\n;]*\b%s\()([^)]*)\)\s*\{'%name,src,re.M)
    if not m: continue
    params=m.group(2); body=src[m.end():]; newp=params; out_body=body
    for pm in re.finditer(r'(?:s32|u32|s16|u16|s8|u8) (arg\d+)',params):
        a=pm.group(1)
        ft=force.get(name,{}).get(a)
        if ft:
            out_body=re.sub(r'\b%s & %s\b'%(a,'0xFF' if ft=='u8' else '0xFFFF'),a,out_body)
            newp=newp.replace(pm.group(0),'%s %s'%(ft,a),1); continue
        for mask,t in (('0xFF','u8'),('0xFFFF','u16')):
            pat=r'\b%s & %s\b'%(a,mask)
            if re.search(pat,out_body):
                out_body=re.sub(pat,a,out_body)
                newp=newp.replace(pm.group(0),'%s %s'%(t,a),1)
                break
    if newp!=params:
        out=src[:m.start(2)]+newp+src[m.end(2):m.end()]+out_body
        open(os.path.join(outd,os.path.basename(f)),'w').write(out); n+=1
print(n)
