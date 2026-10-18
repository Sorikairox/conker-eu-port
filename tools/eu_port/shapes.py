#!/usr/bin/env python3
"""Tag every function still in GLOBAL_ASM with the known IDO shapes (HANDOFF "Known IDO shapes").
usage: shapes.py [--list SHAPE [maxinsns]]   (default: counts per shape and size bucket)
shapes: A argcopy (a1..a3 = a0 copy spilled to a0 home slot), B outvec (s32 x[3] frame: sp addresses 12 apart),
        C reload (lw aN from own home slot), D unfilled (store; jr ra; nop)"""
import re, sys, glob, os
R = os.path.expanduser('~/conker/conker')
live = set()
for f in glob.glob(R + '/src_eu/*.c'):
    live.update(re.findall(r'GLOBAL_ASM\("[^"]*/(\w+)\.s"\)', open(f).read()))
INS = re.compile(r'/\* \w+ \w+ \w+ \*/\s+(\.?\w[\w.]*)\s*(.*)')
BUCK = [(20, '<=20'), (40, '21-40'), (60, '41-60'), (100, '61-100'), (150, '101-150'), (10**9, '>150')]
def tags(path):
    ins = []
    for l in open(path):
        m = INS.search(l)
        if m: ins.append((m.group(1), m.group(2).split('#')[0].strip()))
    n = len(ins); frame = 0; t = set()
    for op, a in ins:
        if op == 'addiu' and a.startswith('$sp, $sp, -'): frame = int(a.split('-')[1], 16); break
    copies = set(); sps = []
    for i, (op, a) in enumerate(ins):
        m = re.match(r'or\s*', op)
        if op == 'or' and re.match(r'\$a[1-3], \$a0, \$zero', a): copies.add(a[:3])
        m = re.match(r'sw (\$a[0-3]), (0x[0-9A-F]+|\d+)\(\$sp\)', op + ' ' + a)
        if m:
            off = int(m.group(2), 16)
            if frame and off >= frame and m.group(1) in copies and m.group(1) != '$a0': t.add('A')
        m = re.match(r'addiu (\$a[0-3]), \$sp, (0x[0-9A-F]+)$', op + ' ' + a)
        if m: sps.append(int(m.group(2), 16))
        m = re.match(r'lw (\$a[0-3]), (0x[0-9A-F]+)\(\$sp\)', op + ' ' + a)
        if m and frame and int(m.group(2), 16) == frame + 4 * int(m.group(1)[2]): t.add('C')
        if op == 'jr' and a == '$ra' and i > 0 and ins[i-1][0] in ('sw', 'sb', 'sh', 'swc1') \
           and i + 1 < n and ins[i+1][0] == 'nop': t.add('D')
    ss = set(sps)
    if frame >= 0x20 and any(s + 12 in ss for s in ss): t.add('B')
    return n, t
rows = []
for p in glob.glob(R + '/asm/nonmatchings/*/*.s'):
    fn = os.path.basename(p)[:-2]
    if fn in live: n, t = tags(p); rows.append((fn, n, t))
if len(sys.argv) > 2 and sys.argv[1] == '--list':
    mx = int(sys.argv[3]) if len(sys.argv) > 3 else 10**9
    for fn, n, t in sorted(rows, key=lambda r: r[1]):
        if sys.argv[2] in t and n <= mx: print(fn, n, ''.join(sorted(t)))
    sys.exit()
print('live GLOBAL_ASM functions:', len(rows))
print('%-8s' % 'shape', *['%7s' % b for _, b in BUCK], '%7s' % 'total')
for s in 'ABCD':
    c = [0] * len(BUCK)
    for fn, n, t in rows:
        if s in t:
            for k, (lim, _) in enumerate(BUCK):
                if n <= lim: c[k] += 1; break
    print('%-8s' % s, *['%7d' % x for x in c], '%7d' % sum(c))
c = [0] * len(BUCK)
for fn, n, t in rows:
    for k, (lim, _) in enumerate(BUCK):
        if n <= lim: c[k] += 1; break
print('%-8s' % 'all', *['%7d' % x for x in c], '%7d' % sum(c))
