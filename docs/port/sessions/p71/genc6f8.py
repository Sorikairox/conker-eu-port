#!/usr/bin/env python3
"""P71: setups for func_1502C6F8 (object shadow), p71/knobs.sh + env DIFFTEST_ARGMEM=15095B70=1:14 (the quad).
func_15095380 fills the quad first (OUTA N=3: the two bytes the C never sets are then defined on both sides).
Objects at EU 0x800CC6F0 (0x32C each); D_800BEAC0 = EU 0x800BEEE0."""
import random, struct
r = random.Random(0xC6F8)
fb = lambda f: '%08X' % struct.unpack('>I', struct.pack('>f', f))[0]
for i in range(40):
    idx = r.randint(0, 25); O = 0x800CC6F0 + 0x32C * idx
    off = i % 10 == 9; alpha = 0 if i % 7 == 6 else r.randint(1, 255); st = 3 if i & 1 else r.choice([0, 1, 2, 4, 7])
    size = r.randint(0, 255)
    p = ['800BEEE0=%08X' % ((1 << 24) if off else 0), '%08X=%08X' % (O, st), '%08X=%08X' % (O + 4, r.getrandbits(24) << 8 | alpha),
         '%08X=%08X' % (O + 0x120, r.getrandbits(16) << 16 | size << 8 | r.getrandbits(8)),
         '%08X=%04X%04X' % (O + 0x60, r.getrandbits(16), r.getrandbits(16))]
    p += ['%08X=%s' % (O + k, fb(r.uniform(-3000, 3000))) for k in (0x14, 0x18, 0x1C)]
    outa = '15095380=3:%08X;%08X;%08X;%08X' % tuple(r.getrandbits(32) for _ in range(4))
    print('k%02d_o%d_s%d ! 0=804C0000,1=%X ! %s ! 15095380=804B0000,15095B70=804B1000 ! ! %s ! ! ' % (i, idx, st, idx, ','.join(p), outa))
