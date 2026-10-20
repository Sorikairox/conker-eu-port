#!/usr/bin/env python3
"""ljcollect.py <out_list> [max_off_hex=130000] [min_off_hex=0]

Collects open near-miss drafts for the line-join sweep (s70). Functions: still GLOBAL_ASM in a
game file whose hex offset is in [min_off, max_off). Included when repair_log.tsv's last row
is unmatched with end DIFF<=12, or DIFF<=60 / SIZE+-1 with a note about order, scheduling,
store, register or the permuter; or when a draft file for it exists in docs/sessions/sNN_drafts
or conker/build_port/sNN. For each function it lists every draft source found (repair/<f>.c,
nm/<f>/best.c, decomp-permuter/drafts, sessions drafts, the 6 newest build_port files) as
"func path" lines; screen them (ljsweep.sh base) to pick the best baseline.
"""
import sys, os, re, glob, collections
R = os.path.expanduser(os.environ.get('CONKER_ROOT', '~/conker')); os.chdir(R)
out = sys.argv[1]
hi = int(sys.argv[2], 16) if len(sys.argv) > 2 else 0x130000
lo = int(sys.argv[3], 16) if len(sys.argv) > 3 else 0
PRAG = re.compile(r'#pragma GLOBAL_ASM\("([^"]*)/(\w+)\.s"\)')
f2p = {}
for p in glob.glob('conker/src_eu/**/*.c', recursive=True):
    b = os.path.basename(p)
    if not b.startswith('game'): continue
    m = re.search(r'_([0-9A-Fa-f]+)\.c$', b)
    if not m or not (lo <= int(m.group(1), 16) < hi): continue
    for mm in PRAG.finditer(open(p).read()): f2p[mm.group(2)] = p
KW = re.compile(r'order|sched|store|regist|permut|swap|roles?\b|v0/v1|t-reg', re.I)
last = {}
for l in open('tools/eu_port/repair_log.tsv'):
    c = l.rstrip('\n').split('\t')
    if len(c) >= 7 and c[0].startswith('func_'): last[c[0]] = c
funcs = set()
for f, c in last.items():
    if f not in f2p or c[4] == 'y': continue
    m = re.match(r'DIFF(\d+)', c[3]); s = re.match(r'SIZE[+-]1\b', c[3])
    if m and int(m.group(1)) <= 12: funcs.add(f)
    elif (m and int(m.group(1)) <= 60 or s) and KW.search(c[6]): funcs.add(f)
files = collections.defaultdict(list)
for p in glob.glob('docs/sessions/s*_drafts/**/*.c', recursive=True) + glob.glob('conker/build_port/s*/**/*.c', recursive=True):
    for f in set(re.findall(r'func_[0-9A-F]{8}', p)):
        if f in f2p: files[f].append(p)
for f in list(files):
    if 'DIFF' in ' '.join(files[f]) or f in last: funcs.add(f)
lines = []
for f in sorted(funcs):
    cand = [p for p in ('tools/decomp-permuter/repair/%s.c' % f, 'tools/decomp-permuter/nm/%s/best.c' % f) if os.path.exists(p)]
    cand += glob.glob('tools/decomp-permuter/drafts/*%s*.c' % f)
    sess = [p for p in files.get(f, []) if p.startswith('docs/')]
    bp = sorted([p for p in files.get(f, []) if p.startswith('conker/')], key=os.path.getmtime)[-6:]
    for p in cand + sess + bp: lines.append('%s %s' % (f, p))
open(out, 'w').write('\n'.join(lines) + '\n')
print(len(funcs), 'functions,', len(lines), 'drafts')
