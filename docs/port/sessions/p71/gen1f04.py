#!/usr/bin/env python3
"""P71: setups for func_15031F04 (attachment undo), p71/knobs.sh with env
DIFFTEST_ARGMEM=15161C40=2:5,151482D4=0:5,15149A50=0:5 (the message records). EU jal targets: func_15083E90 =
0x150842F8, func_151616D0 = 0x15161C40, func_151494E0 = 0x15149A50. Every model id 0..0x9F (+1), kinds +6."""
import random
r = random.Random(0x1F04); R = 0x804B0000; O = 0x804C0000
ids = list(range(0, 0xA0)); kinds = [0x16, 0x63, 0x89, 0, 0x15, 0x17, 0x62, 0x88]
for i, mid in enumerate(ids):
    k = kinds[i % len(kinds)]
    p = ['%08X=%02X%02X%04X' % (R, r.randint(0, 255), mid, r.getrandbits(16)), '%08X=%04X%02X%02X' % (R + 4, r.getrandbits(16), k, r.randint(0, 255)),
         '%08X=%08X' % (O + 0x31C, 0 if i % 3 == 0 else 0x804D0000), '%08X=%08X' % (O + 0x9C, r.getrandbits(32)),
         '804D01A4=%08X' % r.getrandbits(32), '%08X=%08X' % (O + 0x38, r.getrandbits(32))]
    ret = '150842F8=%08X' % (0 if i % 23 == 22 else O)
    print('k%02X_m%02X_k%02X ! 0=%08X ! %s ! %s ! ! ! ! ' % (i, mid, k, R, ','.join(p), ret))
