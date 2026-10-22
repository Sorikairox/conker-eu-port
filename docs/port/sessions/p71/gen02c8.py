#!/usr/bin/env python3
"""P71: setups for func_150302C8 (attachment model load), for p71/knobs.sh (8 fields).
EU jal targets: func_15030100 = 0x15030100, func_1503F91C = 0x1503F91C, allocate_memory = 0x10003E90."""
import random
r = random.Random(0x2C8); R = 0x804B0000; O = 0x804C0000
for i in range(48):
    asset9 = i & 1; fail = (i >> 1) % 4 == 3; b10 = (i >> 3) & 1; m66 = [8, 0xC, 4, 0x18 | 8][(i >> 4) % 4] if i < 40 else r.randint(0, 255)
    a30 = 0 if i % 5 == 4 else 0x80450000; alloc = ['804A0000;804A1000', '0', '804A0000;0', '804A0000;804A1000'][i % 4]
    loaded = i == 47
    p = ['%08X=%08X' % (R + 0x24, 0x80440000 if loaded else 0), '%08X=%08X' % (R + 0x14, 0xFF if asset9 else r.randint(0, 0x7F)),
         '%08X=%08X' % (R + 4, (b10 << 28) | r.getrandbits(24) & 0xEFFFFF), '%08X=%08X' % (R + 0x30, a30),
         '%08X=%08X' % (O + 0x64, m66 << 8), '%08X=%08X' % (R, r.getrandbits(32))]
    sz = r.randrange(4, 0x800, 4)
    rets = '15030100=%d,1503F91C=%d,10003E90=%s' % (fail, fail, alloc)
    outw = '15030100=1:%08X/3:80470000,1503F91C=2:%08X/4:80470000' % (0x80470000 + sz, 0x80470000 + sz)
    print('k%02d_a%d_f%d_b%d_m%X ! 0=%08X,1=%08X ! %s ! %s ! ! ! %s ! ' % (i, asset9, fail, b10, m66, R, O, ','.join(p), rets, outw))
