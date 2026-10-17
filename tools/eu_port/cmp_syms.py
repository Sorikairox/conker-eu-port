#!/usr/bin/env python3
"""Compare implied symbol addresses ("NAME 0xADDR" lines, from check_funcs.py -s)
with the EU symbol files and the link map. Run from conker/."""
import re, sys
from collections import defaultdict
defs = {}
for fn in ['symbol_addrs.eu.txt', 'undefined_syms.eu.txt', 'undefined_syms_auto.txt', 'undefined_funcs_auto.txt']:
    for l in open(fn):
        m = re.match(r'\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)', l)
        if m:
            defs.setdefault(m.group(1), int(m.group(2), 16))
for l in open('build/conker.eu.map'):
    m = re.match(r'\s+0x0*([0-9a-f]{8})\s+(\w+)\s*$', l)
    if m:
        defs.setdefault(m.group(2), int(m.group(1), 16))
imp = defaultdict(set)
for l in open(sys.argv[1]):
    a, b = l.split()[:2]
    imp[a].add(int(b, 16))
for k, v in sorted(imp.items()):
    if k.startswith('.'):
        continue
    d = defs.get(k)
    st = 'undef' if d is None else ('ok' if v == {d} else 'MISMATCH %08X' % d)
    if st != 'ok':
        print(k, ' '.join('0x%08X' % x for x in v), st)
