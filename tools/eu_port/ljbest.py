#!/usr/bin/env python3
"""ljbest.py <sweep.res> <sel.txt>: per function, baseline (from sel.txt "func result path") vs the
best variant in sweep.res ("<result> <func> <path>"); prints improved functions and a summary
(how many changed at all, improved, OK, split by linejoin (/lj/) and blkvar (/bv/) variants)."""
import sys, re, collections
def sc(r):
    m = re.match(r'DIFF(\d+)$', r)
    return 0 if r == 'OK' else int(m.group(1)) if m else (5000 if r.startswith('SIZE') else 9999)
base = {}
for l in open(sys.argv[2]):
    f, r, p = l.split()[:3]; base[f] = (r, p)
best = {}; changed = collections.defaultdict(set); impr = collections.defaultdict(set)
for l in open(sys.argv[1]):
    c = l.split()
    if len(c) < 3: continue
    r, f, p = c[:3]
    if f not in base or p == base[f][1]: continue
    kind = 'lj' if '/lj/' in p or '/lj_' in p else 'bv'
    if r != base[f][0]: changed[kind].add(f)
    if sc(r) < sc(base[f][0]): impr[kind].add(f)
    if f not in best or sc(r) < sc(best[f][0]): best[f] = (r, p)
for f in sorted(best, key=lambda f: sc(best[f][0])):
    if sc(best[f][0]) < sc(base[f][0]): print(f, base[f][0], '->', best[f][0], best[f][1])
for k in ('lj', 'bv'):
    ok = sum(1 for f in best if best[f][0] == 'OK' and (('/lj' in best[f][1]) == (k == 'lj')))
    print('# %s: functions %d, changed %d, improved %d, OK %d' % (k, len(base), len(changed[k]), len(impr[k]), ok))
