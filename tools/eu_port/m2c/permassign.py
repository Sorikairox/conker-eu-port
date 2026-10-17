#!/usr/bin/env python3
# usage: permassign.py draft.c outdir [first_fixed=0] [max=120]
#   writes every permutation of the first block of consecutive `tmp.X = ...;` assignment lines of a draft (the first
#   <first_fixed> lines stay in place) as outdir/p<i>.c, for tryall.
import sys, os, itertools
src, od = sys.argv[1], sys.argv[2]
fixed = int(sys.argv[3]) if len(sys.argv) > 3 else 0
mx = int(sys.argv[4]) if len(sys.argv) > 4 else 120
L = open(src).read().split('\n')
idx = [i for i, l in enumerate(L) if l.strip().startswith('tmp.')]
idx = [i for n, i in enumerate(idx) if i == idx[0] + n]     # first consecutive block only
A = [L[i] for i in idx]
os.makedirs(od, exist_ok=True)
for n, p in enumerate(itertools.permutations(A[fixed:])):
    if n >= mx:
        break
    M = L[:idx[0]] + A[:fixed] + list(p) + L[idx[-1] + 1:]
    open(os.path.join(od, 'p%d.c' % n), 'w').write('\n'.join(M))
