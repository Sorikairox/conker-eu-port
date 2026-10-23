#!/usr/bin/env python3
"""P98: nmdup.py FILE 'OLD LINE TEXT' 'NEW LINE TEXT' [--inplace]
Default: the (unique, stripped) line is compiled in both builds -> wrap it as
  #ifdef NON_MATCHING / NEW / #else / OLD / #endif   (default build unchanged)
--inplace: the line is NM-only, replace it."""
import sys
p, old, new = sys.argv[1], sys.argv[2], sys.argv[3]
L = open(p).read().split('\n')
hits = [i for i, l in enumerate(L) if l.strip() == old.strip()]
assert len(hits) == 1, (p, old, hits)
i = hits[0]; ind = L[i][:len(L[i]) - len(L[i].lstrip())]
if '--inplace' in sys.argv: L[i] = ind + new.strip()
else: L[i:i + 1] = ['#ifdef NON_MATCHING', ind + new.strip(), '#else', L[i], '#endif']
open(p, 'w').write('\n'.join(L))
print('ok', p, i + 1)
