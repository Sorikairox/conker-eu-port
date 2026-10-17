#!/usr/bin/env python3
"""C initializer for a table of code pointers in the EU data (for C files that own their .data).

usage: ptrtable.py <rom start> <rom end> [type]   (run from the repo root; reads conker/conker.eu.bin)
Prints `name, name, ...` (NULL for 0), names from symbol_addrs.eu.txt / undefined syms, else func_XXXXXXXX
with a warning on stderr. Paste into e.g. `void (*D_x[])(s32) = { ... };` and declare the functions first.
"""
import os, re, sys, struct
ROOT = os.path.expanduser('~/conker/conker')
a, b = int(sys.argv[1], 0), int(sys.argv[2], 0)
names = {}
for f in ('symbol_addrs.eu.txt', 'undefined_syms.eu.txt', 'undefined_funcs_auto.txt'):
    p = os.path.join(ROOT, f)
    if os.path.exists(p):
        for l in open(p):
            m = re.match(r'\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)', l)
            if m and m.group(1).startswith('func_'):
                names.setdefault(int(m.group(2), 16), m.group(1))
data = open(os.path.join(ROOT, 'conker.eu.bin'), 'rb').read()
out = []
for r in range(a, b, 4):
    v = struct.unpack('>I', data[r:r + 4])[0]
    if v == 0:
        out.append('NULL')
    else:
        n = names.get(v)
        if n is None:
            n = 'func_%08X' % v
            print('warning: no name for 0x%08X' % v, file=sys.stderr)
        out.append(n)
print(', '.join(out))
