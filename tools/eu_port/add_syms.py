#!/usr/bin/env python3
"""Append the 'undef' lines printed by cmp_syms.py to undefined_syms.eu.txt. Run from conker/."""
import sys
lines = [l.split() for l in open(sys.argv[1]) if l.strip().endswith('undef')]
with open('undefined_syms.eu.txt', 'a') as f:
    for name, addr, _ in lines:
        f.write('%-32s= %s;\n' % (name, addr))
        print('added', name, addr)
