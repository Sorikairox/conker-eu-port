#!/usr/bin/env python3
# mvline.py draft.c 'line text' first_anchor last_anchor outprefix: move one statement to every position in [first,last]
import sys
s=open(sys.argv[1]).read().split('\n'); t=sys.argv[2]; a=sys.argv[3]; b=sys.argv[4]; o=sys.argv[5]
i=[k for k,l in enumerate(s) if l.strip()==t][0]; r=s[:i]+s[i+1:]
lo=[k for k,l in enumerate(r) if l.strip()==a][0]; hi=[k for k,l in enumerate(r) if l.strip()==b][0]
for n,k in enumerate(range(lo,hi+2)):
    open('%s_%02d.c'%(o,n),'w').write('\n'.join(r[:k]+[s[i]]+r[k:]))
