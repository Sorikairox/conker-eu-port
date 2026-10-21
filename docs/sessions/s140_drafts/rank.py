#!/usr/bin/env python3
"""rank.py sweep.txt : best result per function (DIFFn by n; SIZE+-n after DIFF<=30 by |n|*10)."""
import sys, re
best = {}
def score(r):
    m = re.match(r'DIFF(\d+)', r)
    if m: return int(m.group(1))
    m = re.match(r'SIZE([+-]\d+)', r)
    if m: return 25 + 10 * abs(int(m.group(1)))
    return 10**6
for l in open(sys.argv[1]):
    p = l.split()
    if len(p) < 3: continue
    r, f, path = p[0], p[1], p[2]
    if f not in best or score(r) < score(best[f][0]): best[f] = (r, path)
for f, (r, path) in sorted(best.items(), key=lambda kv: score(kv[1][0])):
    print('%-8s %s %s' % (r, f, path.replace('/Users/sorikairo/conker-wt/a/', '')))
