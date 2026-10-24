#!/usr/bin/env python3
# P240: drop '## ' blocks of HANDOFF.md whose heading AND body repeat an earlier block exactly (merge_union duplicates).
# Usage: hodedup.py FILE [--dry]. Reports headings that repeat with different bodies (kept).
import sys
p = sys.argv[1]; L = open(p).read().split('\n')
st = [i for i, l in enumerate(L) if l.startswith('## ')]
out = L[:st[0]]; seen = {}; drop = 0; diff = []
for k, s in enumerate(st):
    e = st[k + 1] if k + 1 < len(st) else len(L)
    b = L[s:e]; key = '\n'.join(x.rstrip() for x in b).strip()
    if key in seen: drop += 1; continue
    if L[s] in [v for v in seen.values()]: diff.append(L[s])
    seen[key] = L[s]; out += b
print('dropped', drop, 'identical blocks; same heading, different body:', len(diff))
for d in diff: print('  ', d[:100])
if '--dry' not in sys.argv: open(p, 'w').write('\n'.join(out))
