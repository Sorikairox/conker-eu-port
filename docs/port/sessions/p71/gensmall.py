#!/usr/bin/env python3
"""P71: setups for func_1503F23C (sF23C) and func_1503DE70 (sDE70), p71/knobs.sh. usage: gensmall.py f23c|de70
D_800847FC (EU, same name) -> 0x804B0000 table; slot flags D_800C6A84 / D_800C6A88 (16-byte records)."""
import random, sys
r = random.Random(0xF23C); which = sys.argv[1]
for i in range(48):
    st = r.randint(0, 3); en = r.randint(0, 3); sl = r.randint(0, 3)
    p = ['%08X=804B0000' % (0x800847FC + 4 * st)]
    for k in range(8):
        p.append('%08X=%08X' % (0x804B0000 + 4 * k, r.choice([0, 1 << r.randint(0, 31), r.getrandbits(32)])))
    p.append('%08X=%08X' % (0x800C6A84 + 16 * sl, r.choice([0, r.getrandbits(32), 0xFFFFFFFF])))
    p.append('%08X=%08X' % (0x800C6A88 + 16 * sl, r.choice([0, r.getrandbits(32), 0xFFFFFFFF])))
    if which == 'f23c':
        print('k%02d ! 0=%X,1=%X,2=%X ! %s ! ! ! ! ! ' % (i, st, en, sl, ','.join(p)))
    else:
        e = 'FFFFFFFF' if i % 4 == 0 else '%X' % en
        print('k%02d ! 0=%08X,1=%X,2=%s ! %s ! ! ! ! ! ' % (i, 0x800CC6F0 + 0x32C * r.randint(0, 25), st, e, ','.join(p)))
