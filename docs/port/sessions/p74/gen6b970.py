#!/usr/bin/env python3
"""P74: setups for func_1503ED44 (ed44) and func_1503F45C (f45c), p74/knobs.sh. usage: gen6b970.py ed44|f45c
EU: D_800C6660 0x800C6A80 (16-byte records), D_800BE9E4 0x800BEE04, D_80098CC4 / D_800847E4 same address,
D_800CC2D0 0x800CC6F0 (0x32C objects), func_1503F23C jal 0x1503F23C."""
import random, sys, struct
r = random.Random(0x6B97); which = sys.argv[1]
def f2w(x): return struct.unpack('>I', struct.pack('>f', x))[0]
if which == 'ed44':
    for t in range(40):
        i = r.randint(0, 3); kind = r.randint(0, 15); n = r.choice([0, 1, 3, 5, 8]) if t % 8 else 0
        p = ['%08X=804B0000' % (0x800C6A80 + 16 * i), '%08X=%08X' % (0x800C6A8C + 16 * i, (r.getrandbits(16) << 16) | (kind << 8) | r.getrandbits(8)),
             '800BEE04=%08X' % r.choice([1, 2, 3, 0, 0xFFFFFFFF]), '%08X=%08X' % (0x80098CC4 + (kind & ~3), n << (8 * (3 - (kind & 3)))),
             '%08X=804B8000' % (0x800847E4 + 4 * kind)]
        att = [r.choice([0xFF, 0xFF, 0, 1, 0x80]) for _ in range(8)]
        p += ['804B8000=%02X%02X%02X%02X' % tuple(att[:4]), '804B8004=%02X%02X%02X%02X' % tuple(att[4:])]
        for k in range(8):
            b = 0x804B0000 + k * 0x68
            for off in range(0x24, 0x64, 4):
                p.append('%08X=%08X' % (b + off, f2w(r.choice([0.0, 1.5, -2.25, 100.0, r.uniform(-50, 50)]))))
            p.append('%08X=%08X' % (b + 0x64, r.choice([0, 0x01000000, 0xFF123456, 0x00FFFFFF])))
        print('k%02d_i%d_n%d ! 0=%X ! %s ! ! ! ! ! ' % (t, i, n, i, ','.join(p)))
else:
    for t in range(32):
        i = r.randint(0, 25); bits = t % 8
        seq = ';'.join(str((bits >> k) & 1) for k in range(3))
        p = ['%08X=%08X' % (0x800CC6F0 + 0x32C * i + 0x94, r.choice([0, 0xFFFFFFFF, r.getrandbits(32)]))]
        print('k%02d_i%d_b%d ! 0=%X ! %s ! 1503F23C=%s ! ! ! ! ' % (t, i, bits, i, ','.join(p), seq))
