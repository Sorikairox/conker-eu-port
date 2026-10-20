#!/usr/bin/env python3
# spdecl.py in out : declare undefined spXX names (arrays when indexed / address-taken, scalars otherwise)
import sys,re
s=open(sys.argv[1]).read()
names=set(re.findall(r'\bsp([0-9A-F]+)\b',s))
decl=set(re.findall(r'^\s+[A-Za-z_][\w ]*?[\s*]+sp([0-9A-F]+)(?:\[\d+\])?;',s,re.M))
undef=sorted(int(n,16) for n in names-decl)
alln=sorted(int(n,16) for n in names)
out=[]
for o in undef:
    nm='sp%X'%o
    idx=[int(x) for x in re.findall(r'\b%s\[(\d+)\]'%nm,s)]
    addr=re.search(r'&%s\b'%nm,s) is not None
    nxt=[x for x in alln if x>o]
    gap=(nxt[0]-o)//4 if nxt else 4
    line=[l for l in s.split('\n') if re.search(r'\b%s\b'%nm,l)][0]
    isf=bool(re.search(r'temp_f|f32|\d\.\d*f|sqrt|cosf|sinf',line))
    t='f32' if isf else 's32'
    if idx or addr:
        n=max(max(idx)+1 if idx else 1, min(gap,16) if (gap>1 and (addr or idx)) else 1)
        # matrices passed to guMtx*/func_150A8050 use 16
        if re.search(r'guMtx\w*\(\(f32 \(\*\)\[4\]\) &%s'%nm,s): n=16
        out.append('    f32 %s[%d];'%(nm,n))
    else:
        out.append('    %s %s;'%(t,nm))
i=s.index('{\n',s.index(') {')-1 if ') {' in s else 0)
m=re.search(r'^[^\n]*\) \{\n',s,re.M)
p=m.end()
s=s[:p]+'\n'.join(out)+'\n'+s[p:]
open(sys.argv[2],'w').write(s)
print(len(out),'decls')
