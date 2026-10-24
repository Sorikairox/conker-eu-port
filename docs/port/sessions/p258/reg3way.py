#!/usr/bin/env python3
# P258: 3-way merge of tools/port/verify_registry.tsv by func (replaces merge_union + p252/regmerge.py, which keeps the
# wrong row when the incoming side is older). Per func: unchanged side -> take the changed side; both changed ->
# take the rows whose session column has the higher P number (printed as CONFLICT for review).
# Usage (during a conflicted merge): reg3way.py   (reads index stages 1/2/3, writes the file, git-adds nothing)
import subprocess, collections, re
F = 'tools/port/verify_registry.tsv'
def stage(n):
    d = collections.OrderedDict()
    for l in subprocess.run(['git', 'show', ':%d:%s' % (n, F)], capture_output=True, text=True).stdout.splitlines():
        d.setdefault(l.split('\t')[0], []).append(l)
    return d
b, o, t = stage(1), stage(2), stage(3)
def sess(rows): return max([int(m) for r in rows for m in re.findall(r'\bP(\d+)', r.split('\t')[-1])] or [0])
out = collections.OrderedDict()
for k in list(o) + [k for k in t if k not in o]:
    ro, rt, rb = o.get(k), t.get(k), b.get(k)
    if ro == rt or rt == rb: pick = ro
    elif ro == rb: pick = rt
    else:
        pick = ro if sess(ro or []) >= sess(rt or []) else rt
        print('CONFLICT', k, 'ours', sess(ro or []), 'theirs', sess(rt or []), '->', 'ours' if pick is ro else 'theirs')
    if pick: out[k] = pick
open(F, 'w').write('\n'.join(l for v in out.values() for l in v) + '\n')
print('rows', sum(len(v) for v in out.values()), 'funcs', len(out))
