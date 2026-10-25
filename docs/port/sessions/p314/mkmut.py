#!/usr/bin/env python3
"""P314: turn m5EC8.spec (old ||| new ||| setups [||| occurrence]) into line-numbered sed mutants (m5EC8.txt).
Line numbers are those of the NM block (tools/port/nmblock.py, NMBLOCK_WHOLE=1) given as argv[1]."""
import re, sys, os
cand = open(sys.argv[1]).read().split('\n')
d = os.path.dirname(os.path.abspath(__file__))
out = []
for ln in open(os.path.join(d, 'm5EC8.spec')):
    ln = ln.rstrip('\n')
    if not ln.strip() or ln.startswith('#'):
        continue
    parts = [p.strip() for p in ln.split('|||')]
    old, new, sets = parts[0], parts[1], parts[2]
    occ = int(parts[3]) if len(parts) > 3 else 1
    hits = [i for i, l in enumerate(cand) if old in l]
    if len(hits) < occ:
        sys.exit('not found: %r' % old)
    if len(hits) > 1 and len(parts) < 4:
        sys.exit('ambiguous (%d): %r' % (len(hits), old))
    n = hits[occ - 1] + 1
    esc = lambda s: re.sub(r'([][.*^$\\/&])', r'\\\1', s)
    escn = lambda s: re.sub(r'([\\/&])', r'\\\1', s)
    out.append('%ds/%s/%s/ %% %s' % (n, esc(old), escn(new), sets))
open(os.path.join(d, 'm5EC8.txt'), 'w').write('\n'.join(out) + '\n')
print(len(out), 'mutants')
