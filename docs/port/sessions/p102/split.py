#!/usr/bin/env python3
"""P102: compact asm of func_15097E9C split at jump-table targets. usage: split.py > blocks.txt"""
import re
src = open('/Users/sorikairo/conker-wt/portb/conker/asm/nonmatchings/game_eu_C5530/func_15097E9C.s').read().splitlines()
cases = {}
for f, base in (('jt1.txt', ''), ('jt2.txt', 'sub')):
    for l in open(f):
        c, t = l.split(); cases.setdefault(int(t, 16), []).append(base + c)
out = []
for l in src:
    m = re.match(r'\s*/\* \w+ (\w{8}) \w{8} \*/\s+(.*)', l)
    if m:
        a = int(m.group(1), 16)
        if a in cases: out.append('==== case %s' % ','.join(cases[a]))
        out.append('%X  %s' % (a & 0xFFFF, re.sub(r'\s+', ' ', m.group(2))))
    elif l.strip().startswith('.L'): out.append(l.strip())
print('\n'.join(out))
