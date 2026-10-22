#!/usr/bin/env python3
"""P74: setups for func_1503E6B4 (p74/knobs.sh): args (i, piece, jointOffset, pc = 0x804B0000, detached), object i
(0x800CC6F0 + 0x32C * i: position +0x14.., unk1D4 = 0x804D0000), kind in record +0xE (0x800C6A8C + 16 * i),
parent table D_800847E4[kind] -> 0x804B8000, bcopy (0x10023E80) writes a matrix through a1.
Every 4th setup puts the piece about 30 units above the object (float rounding keeps the distance non-zero; the
len == 0 guard only matters for 0 / 0 and is an equivalent mutant: 0 * anything = 0). ARGMEM for the matrix: see P74.md."""
import random, struct
r = random.Random(0xE6B4)
def f(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
for t in range(40):
    i = r.randint(0, 3); piece = r.randint(0, 7); jo = r.choice([0, 1, 5]); det = r.choice([0, 0, 1]); kind = r.randint(0, 15)
    ob = 0x800CC6F0 + 0x32C * i
    pos = [r.uniform(-500, 500) for _ in range(3)]
    p = ['%08X=%s' % (ob + 0x14 + 4 * k, f(pos[k])) for k in range(3)] + ['%08X=804D0000' % (ob + 0x1D4)]
    p += ['%08X=%08X' % (0x800C6A8C + 16 * i, (r.getrandbits(16) << 16) | (kind << 8) | r.getrandbits(8)),
          '%08X=804B8000' % (0x800847E4 + 4 * kind)]
    par = [r.choice([0xFF, 0, 1, 3, 7]) for _ in range(8)]
    p += ['804B8000=%02X%02X%02X%02X' % tuple(par[:4]), '804B8004=%02X%02X%02X%02X' % tuple(par[4:])]
    pc = [r.uniform(-500, 500) for _ in range(9)]
    if t % 4 == 0: pc[0], pc[1], pc[2] = pos[0], pos[1] + 30.0, pos[2]
    p += ['%08X=%s' % (0x804B0000 + 4 * k, f(pc[k])) for k in range(9)]
    m = ';'.join(f(r.choice([0.0, 1.0, r.uniform(-10, 10)])) for _ in range(16))
    print('k%02d_i%d_p%d_d%d ! 0=%X,1=%X,2=%X,3=804B0000,4=%X ! %s ! ! ! 10023E80=1:%s ! ! ' % (t, i, piece, det, i, piece, jo, det, ','.join(p), m))
