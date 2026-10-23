#!/bin/bash
# P86: write the NON_MATCHING block of FUNC (the one whose #else holds FUNC's GLOBAL_ASM) from FILE to OUT
# usage: draft.sh FUNC src_eu/FILE.c OUT.c
python3 - "$1" "$2" "$3" <<'PY'
import sys
f, src, out = sys.argv[1:]
L = open(src).read().split('\n')
for i, l in enumerate(L):
    if 'GLOBAL_ASM' in l and '/%s.s' % f in l and L[i-1].startswith('#else'):
        j = i - 1
        while not L[j].startswith('#ifdef NON_MATCHING'): j -= 1
        open(out, 'w').write('\n'.join(L[j+1:i-1]) + '\n'); print(out, i - 1 - j - 1, 'lines'); break
else: print('not found')
PY
