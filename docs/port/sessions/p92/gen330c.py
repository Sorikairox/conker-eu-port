#!/usr/bin/env python3
"""P92 setups for func_1502330C (uses gen.py's Mem). Stub func_15023C60 = jal 15023C60: RET distance per call,
OUTW a3 = found record pointer per call (0 = none). usage: gen330c.py [n] > 330c.txt"""
import random, sys
from gen import Mem
R = random.Random(9230)
for i in range(int(sys.argv[1]) if len(sys.argv) > 1 else 40):
    M = Mem(); slot = i % 2; n = R.choice([0, 1, 2, 3, 4, 6])
    M.put(0x800C3A5A + slot, bytes([n])); M.put(0x800C3A5A + 1 - slot, bytes([R.randint(0, 9)]))
    ent = M.alloc(8 * 8); M.w(0x800C3A10 + 4 * slot, ent)
    for j in range(8): M.h(ent + 8 * j, R.choice([0, 1, 2, 3, 1]))
    rets, founds = [], []
    for j in range(n):
        M.w(0x800C3AA8 + slot * 0x78 + 4 * j, R.choice([0, M.alloc(0x20), M.alloc(0x20)]))
    for j in range(n):
        rets.append(R.choice([99999, 99998, 100000, 5, 5, R.randint(-50, 2000), R.randint(0, 200000)]))
        if R.random() < 0.3: founds.append(0)
        else:
            f = M.alloc(4); M.h(f + 2, R.choice([R.randint(0, 29), -1, 0xFFFF & -3])); founds.append(f)
    rets = rets or [0]; founds = founds or [0]
    print('s330c_%d ! 0=%X,1=%X ! %s ! 15023C60=%s !  !  ! 15023C60=3:%s ! ' % (
        i, slot, R.randint(0, 500), M.poke(R), ';'.join('%X' % (r & 0xFFFFFFFF) for r in rets),
        ';'.join('%X' % f for f in founds)))
