#!/usr/bin/env python3
"""P71: setups for func_15033ECC (attachment sound callback), p71/knobs.sh. voice 0x804B0000 (+0x18 rec, +0x1C owner)."""
import random, struct
r = random.Random(0x3ECC); V, R, O, P = 0x804B0000, 0x804C0000, 0x804D0000, 0x804F0000
fb = lambda f: '%08X' % struct.unpack('>I', struct.pack('>f', f))[0]
for i in range(64):
    play = i & 1; m37 = (i >> 1) & 1; k = i >> 2
    norec = k == 15 and play; noobj = k == 14; st0 = k == 13
    anim = [0x15F, 0x15F, 0x120, r.getrandbits(16)][k % 4]; r38 = [0x513, 0x513, anim, 0x15F, r.getrandbits(32)][k % 5]
    p = ['%08X=%08X' % (V + 0x18, 0 if norec else R), '%08X=%08X' % (V + 0x1C, 0 if noobj else O),
         '%08X=%08X' % (V + 0x24, (0 if k % 3 == 0 else r.randint(1, 0xFFFF)) << 16 | r.getrandbits(16)),
         '%08X=%02X%02X%04X' % (R, r.randint(0, 255), 0x37 if m37 else r.choice([0x36, 0x38, 0x4B, 0x10]), r.getrandbits(16)),
         '%08X=%08X' % (R + 0x38, r38), '%08X=%08X' % (O, 0 if st0 else r.randint(1, 9)),
         '%08X=%04X%04X' % (O + 0x84, anim, r.getrandbits(16)), '%08X=%08X' % (O + 0x31C, 0 if k % 6 == 5 else P),
         '%08X=%04X%04X' % (P + 0x19C, r.choice([5, 99, 100, 300]), r.getrandbits(16)), '804E0000=%08X' % (play * r.randint(1, 9))]
    p += ['%08X=%s' % (O + o, fb(r.uniform(-4000, 4000))) for o in (0x14, 0x18, 0x1C)]
    print('k%02d_p%d_m%d ! 0=%08X,2=804E0000,6=804E0100 ! %s ! ! ! ! ! ' % (i, play, m37, V, ','.join(p)))
