#!/usr/bin/env python3
# greedy.py func draft.c first_stmt last_stmt out.c [passes]: coordinate descent over statement order
# (each statement line in [first,last] tried at every position in that range, via m2c/tryall).
import sys, subprocess, os, re
func, draft, first, last, out = sys.argv[1:6]; passes = int(sys.argv[6]) if len(sys.argv) > 6 else 2
R = os.environ.get('CONKER_ROOT', os.path.expanduser('~/conker')); W = os.path.dirname(os.path.abspath(out)) + '/gr_' + func; os.makedirs(W, exist_ok=True)
def score(r):
    if r == 'OK': return 0
    m = re.match(r'DIFF(\d+)', r); return int(m.group(1)) if m else 10**6
def run(variants):
    paths = []
    for i, v in enumerate(variants):
        p = '%s/v%03d.c' % (W, i); open(p, 'w').write('\n'.join(v)); paths.append(p)
    res = {}
    for k in range(0, len(paths), 64):
        o = subprocess.run([R + '/tools/eu_port/m2c/tryall', func] + paths[k:k+64], capture_output=True, text=True, cwd=R).stdout
        for l in o.splitlines():
            t = l.split()
            if len(t) >= 2 and t[-1] in paths: res[t[-1]] = t[0]
    return [score(res.get(p, 'X')) for p in paths]
cur = open(draft).read().split('\n')
best = run([cur])[0]; print('start', best, flush=True)
for ps in range(passes):
    improved = False
    lo = [k for k, l in enumerate(cur) if l.strip() == first][0]; hi = [k for k, l in enumerate(cur) if l.strip() == last][0]
    for i in range(lo, hi + 1):
        line = cur[i]
        if not line.strip().endswith(';'): continue
        r = cur[:i] + cur[i+1:]
        vs = [r[:k] + [line] + r[k:] for k in range(lo, hi + 1) if k != i]
        sc = run(vs); j = min(range(len(sc)), key=lambda x: sc[x])
        if sc[j] < best:
            best = sc[j]; cur = vs[j]; improved = True; print('pass', ps, 'line', line.strip(), '->', best, flush=True)
            open(out, 'w').write('\n'.join(cur))
            if best == 0: print('OK'); sys.exit(0)
    if not improved: break
print('final', best)
