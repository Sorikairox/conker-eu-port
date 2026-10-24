#!/usr/bin/env python3
"""P185: reorder HANDOFF.md session blocks (a '## ... session PNNN' heading plus following '## Next steps' block)
newest first, only blocks numbered >= MIN (argv[2]) move to the top; the rest keep their order; text before the first session heading stays on top. Stable for equal numbers."""
import re, sys
p = sys.argv[1]; L = open(p).read().split('\n')
starts = [i for i, l in enumerate(L) if l.startswith('## ') and re.search(r'session P(\d+)', l)]
head = L[:starts[0]]; blocks = []
for k, s in enumerate(starts):
    e = starts[k + 1] if k + 1 < len(starts) else len(L)
    blocks.append((int(re.search(r'session P(\d+)', L[s]).group(1)), k, L[s:e]))
mn = int(sys.argv[2])
blocks = sorted([b for b in blocks if b[0] >= mn], key=lambda b: (-b[0], b[1])) + [b for b in blocks if b[0] < mn]
out = head + [l for b in blocks for l in b[2]]
open(p, 'w').write('\n'.join(out))
print(' '.join('P%d' % b[0] for b in blocks[:14]))
