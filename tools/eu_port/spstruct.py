#!/usr/bin/env python3
"""spstruct.py <in.c> <out.c> [first_sp_hex]  (s57) m2c effect-spawner drafts declare the stack struct as many scalars
`s16 sp9C; s8 sp98; f32 sp28[13]; ...` and pass `sp28` (or &spXX) to the spawner: IDO then drops stores to the never-addressed scalars.
Merge every `spXX` local with offset >= first_sp (default: the lowest array / address-taken one) into ONE `struct {...} sp;`
(fields at their stack offsets, pads between) and rewrite uses: spXX -> sp.uXX, spXX[i] -> sp.uXX[i]; a bare array name passed as an
argument -> &sp (for the base array) ."""
import sys,re
src=open(sys.argv[1]).read()
lines=src.split('\n')
decl=re.compile(r'^\s+(s8|u8|s16|u16|s32|u32|f32)\s+sp([0-9A-F]+)(\[(\d+)\])?;\s*$')
items={}; base=None
for i,l in enumerate(lines):
    m=decl.match(l)
    if m:
        t,off,_,n=m.groups(); items[int(off,16)]=(t,int(n) if n else None,i,off)
# base = lowest array offset address-taken (an array) if not given
if len(sys.argv)>3: base=int(sys.argv[3],16)
else:
    arrs=[o for o,(t,n,i,_) in items.items() if n]
    base=min(arrs) if arrs else min(items)
sz={'s8':1,'u8':1,'s16':2,'u16':2,'s32':4,'u32':4,'f32':4}
sel={o:v for o,v in items.items() if o>=base}
fields=[]; cur=base
for o in sorted(sel):
    t,n,i,off=sel[o]
    if o<cur: continue
    if o>cur: fields.append('        u8 pad%X[0x%X];'%(cur,o-cur)); cur=o
    al=sz[t]
    fields.append('        %s u%s%s;'%(t,off,'[%d]'%n if n else ''))
    cur=o+sz[t]*(n or 1)
body='\n'.join(lines)
first=min(v[2] for v in sel.values())
for o,(t,n,i,off) in sel.items(): lines[i]=None
struct='    struct {\n'+'\n'.join(fields)+'\n    } sp;'
out=[]
done=False
for i,l in enumerate(lines):
    if l is None:
        if not done: out.append(struct); done=True
        continue
    out.append(l)
t='\n'.join(out)
for o,(ty,n,i,off) in sel.items():
    nm='sp'+off
    if o==base and n:
        t=re.sub(r'(?<![\w.&])%s\[(\d+)\]'%nm,r'sp.u%s[\1]'%off,t)
        t=re.sub(r'(?<![\w.&])%s\b(?!\[)'%nm,'&sp',t)
        t=re.sub(r'&%s\b(?!\[)'%nm,'&sp',t)
    else:
        t=re.sub(r'(?<![\w.])%s\b'%nm,'sp.u'+off,t)
open(sys.argv[2],'w').write(t)
print('base %X fields %d'%(base,len(fields)))
