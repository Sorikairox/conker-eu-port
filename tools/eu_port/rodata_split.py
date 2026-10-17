#!/usr/bin/env python3
# usage: rodata_split.py <src stem> <rom start> <rom end> [--section .rodata|.data]
# Carves [start, end) out of the rodatabin/databin that contains it in conker/conker.eu.yaml and
# makes it the given section of src_eu/<stem>.c (default .rodata): the blob line is split into
# [blob start, rodatabin], [start, .rodata, stem], [end, rodatabin] (empty pieces dropped).
# Afterwards: define the constants in the C file (exact bytes, 16-byte padded object section),
# re-split (rm -rf conker/asm conker/build, *_auto.txt, make extract) and run verify_all.sh;
# only the full ROM check covers data bytes.
import sys,re,os
stem,a,b=sys.argv[1],int(sys.argv[2],16),int(sys.argv[3],16)
sec=sys.argv[sys.argv.index('--section')+1] if '--section' in sys.argv else '.rodata'
p=os.path.expanduser('~/conker/conker/conker.eu.yaml'); L=open(p).read().split('\n')
R=re.compile(r'^(\s*)- \[0x([0-9A-Fa-f]+),\s*([\w.]+)')
for i,l in enumerate(L):
    m=R.match(l)
    if not m: continue
    s=int(m.group(2),16)
    # next subsegment start = end of this one
    nxt=None
    for l2 in L[i+1:]:
        m2=R.match(l2) or re.match(r'^\s*- \[0x([0-9A-Fa-f]+)\]',l2)
        if m2: nxt=int(m2.group(2) if m2.re is R else m2.group(1),16); break
    if m.group(3) in ('rodatabin','databin') and s<=a and nxt is not None and b<=nxt:
        ind=m.group(1); new=[]
        bt=m.group(3)
        if s<a: new.append('%s- [0x%X, %s]'%(ind,s,bt))
        new.append('%s- [0x%X, %s, %s]'%(ind,a,sec,stem))
        if b<nxt: new.append('%s- [0x%X, %s]'%(ind,b,bt))
        L[i:i+1]=new; open(p,'w').write('\n'.join(L)); print('\n'.join(new)); break
else:
    sys.exit('no rodatabin contains 0x%X-0x%X'%(a,b))
