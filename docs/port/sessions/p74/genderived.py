#!/usr/bin/env python3
"""P74: sef90.txt / seb1c.txt from sed44.txt (gen6b970.py ed44). usage: genderived.py ef90|eb1c > s....txt
ef90: + RET func_1510FE58 (floor heights, seed 0xEF90). eb1c: parent table D_800847E4[kind] = -1/-2/0/1/2/7 and
object i's unk1D4 (0x800CC6F0 + 0x32C * i + 0x1D4) = 0x804D0000 or NULL (seed 0xEB1C)."""
import random, re, sys, os
which = sys.argv[1]
r = random.Random(0xEF90 if which == 'ef90' else 0xEB1C)
for l in open(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'sed44.txt')):
    l = l.rstrip('\n')
    if which == 'ef90':
        seq = ';'.join('%08X' % (r.choice([-10, 100, 0, -50, 20, 3, -3]) & 0xFFFFFFFF) for _ in range(8))
        print(l[:-len('! ! ! ! ! ')] + '! 1510FE58=%s ! ! ! ! ' % seq)
    else:
        i = int(re.match(r'k\d+_i(\d)', l).group(1))
        att = [r.choice([0xFF, 0xFE, 0, 1, 2, 7]) for _ in range(8)]
        l = re.sub(r'804B8000=[0-9A-F]{8}', '804B8000=%02X%02X%02X%02X' % tuple(att[:4]), l)
        l = re.sub(r'804B8004=[0-9A-F]{8}', '804B8004=%02X%02X%02X%02X' % tuple(att[4:]), l)
        m = r.choice([0x804D0000, 0x804D0000, 0x804D0000, 0])
        print(l.replace(' ! ! ! ! ! ', ',%08X=%08X ! ! ! ! ! ' % (0x800CC6F0 + 0x32C * i + 0x1D4, m)))
