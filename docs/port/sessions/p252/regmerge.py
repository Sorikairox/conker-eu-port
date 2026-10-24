#!/usr/bin/env python3
# P252: verify_registry.tsv after merge_union: drop rows that only OUR side has when the incoming side has a row for
# the same func (its newer version), then drop exact duplicate rows. Usage: regmerge.py REG OURS.tsv THEIRS.tsv
import sys
reg, ours, theirs = sys.argv[1:4]
O = set(open(ours).read().splitlines()); T = set(open(theirs).read().splitlines())
tf = {l.split('\t')[0] for l in T}
out = []; seen = set(); dropped = 0
for l in open(reg).read().splitlines():
    if (l in O and l not in T and l.split('\t')[0] in tf) or l in seen: dropped += 1; continue
    seen.add(l); out.append(l)
open(reg, 'w').write('\n'.join(out) + '\n'); print('dropped', dropped, 'rows; left', len(out))
