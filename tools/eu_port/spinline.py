#!/usr/bin/env python3
"""spinline.py <indir> <outdir> [func ...]  m2c names the stack slots that hold call results across later calls
(`sp58 = func_150ADA68(); ... func_x(..., sp58 * 2.0f, ...)`). IDO spills such values itself when the call is nested in the
argument list; a named local instead takes a (different) frame slot. Inline body-level `spXX = <call expr>;` into its single
later use (statement at the same indent), drop the declaration. Order of the inlined calls stays the assignment order. (s55)"""
import sys,os,re
ind,outd=sys.argv[1],sys.argv[2]; os.makedirs(outd,exist_ok=True)
names=sys.argv[3:] or [f[:-2] for f in os.listdir(ind) if f.endswith('.c')]
n=0
for f in names:
    s=open(f'{ind}/{f}.c').read(); L=s.split('\n'); changed=False
    i=0
    while i<len(L):
        m=re.match(r'^    (sp[0-9A-F]+) = (.*\bfunc_\w+\(.*|.*\bsinf\(.*|.*\bcosf\(.*);$',L[i])
        if m:
            nm,expr=m.group(1),m.group(2)
            # next assignment of same name ends the live range
            j=i+1; end=len(L)
            for k in range(i+1,len(L)):
                if re.match(r'^    %s = '%nm,L[k]): end=k; break
            uses=[k for k in range(i+1,end) if re.search(r'(?<![\w&])%s\b'%nm,L[k]) or re.search(r'&%s\b'%nm,L[k])]
            if len(uses)==1 and not re.search(r'&%s\b'%nm,L[uses[0]]) and L[uses[0]].startswith('    ') and not L[uses[0]].startswith('     ') \
               and len(re.findall(r'(?<![\w&])%s\b'%nm,L[uses[0]]))==1:
                u=uses[0]
                L[u]=re.sub(r'(?<![\w&])%s\b'%nm,'('+expr+')',L[u])
                del L[i]; changed=True
                continue
        i+=1
    if changed:
        t='\n'.join(L)
        for nm in set(re.findall(r'^    \w[\w ]*? \*?(sp[0-9A-F]+);$',t,re.M)):
            if len(re.findall(r'\b%s\b'%nm,t))==1: t=re.sub(r'^    [\w ]+? \*?%s;\n'%nm,'',t,flags=re.M)
        open(f'{outd}/{f}.c','w').write(t); n+=1
print('spinline changed',n)
