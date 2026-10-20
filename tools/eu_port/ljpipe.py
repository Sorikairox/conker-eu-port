#!/usr/bin/env python3
"""ljpipe.py <base.res> <outdir> [maxdiff=40] [ljcap=64] > sweep_list

s70 mechanical sweep, step 2: from an ljsweep.py result file ("<result> <func> <path>") take the
best draft per function (lowest DIFFn <= maxdiff, else a SIZE+-1 draft), write it to
<outdir>/sel.txt, and print an ljsweep list with: the baseline, linejoin.py variants (ljcap)
and blkvar.py variants (s69 block-local declaration) of it. Then:
  ljsweep.py list name > res;  ljbest.py res sel.txt   (improvements per function)
s73: BVONLY=1 skips the linejoin variants (blkvar only); MAXSIZE=n also takes SIZE+-2..n drafts
(ranked after DIFF and SIZE+-1).
"""
import sys, os, re, subprocess
T = os.path.dirname(os.path.abspath(__file__))
res, od = sys.argv[1], os.path.abspath(sys.argv[2])
maxd = int(sys.argv[3]) if len(sys.argv) > 3 else 40
cap = sys.argv[4] if len(sys.argv) > 4 else '64'
R = os.path.expanduser(os.environ.get('CONKER_ROOT', '~/conker'))
best = {}
for l in open(res):
    c = l.split()
    if len(c) < 3: continue
    r, f, p = c[:3]
    m = re.match(r'DIFF(\d+)$', r)
    z = re.match(r'SIZE[+-](\d+)$', r); ms = int(os.environ.get('MAXSIZE', '1'))
    k = (0, int(m.group(1))) if m and int(m.group(1)) <= maxd else ((1, int(z.group(1))) if z and int(z.group(1)) <= ms else None)
    if k and (f not in best or k < best[f][0]): best[f] = (k, p, r)
os.makedirs(od, exist_ok=True)
with open(os.path.join(od, 'sel.txt'), 'w') as fo:
    for f, (k, p, r) in sorted(best.items()): fo.write('%s %s %s\n' % (f, r, p))
for f, (k, p, r) in sorted(best.items()):
    src = p if os.path.isabs(p) else os.path.join(R, p)
    print(f, src)
    n = 0 if os.environ.get('BVONLY') else int(subprocess.run(['python3', T + '/linejoin.py', src, '%s/lj/%s' % (od, f), cap, f], capture_output=True, text=True).stdout.strip() or 0)
    for i in range(n): print(f, '%s/lj/%s/lj_%03d.c' % (od, f, i))
    os.makedirs(od + '/bv', exist_ok=True)
    for x in subprocess.run(['python3', T + '/blkvar.py', src, '%s/bv/%s' % (od, f)], capture_output=True, text=True).stdout.split():
        print(f, x if os.path.isabs(x) else os.path.abspath(x))
