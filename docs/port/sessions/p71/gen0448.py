#!/usr/bin/env python3
"""P71: knob setups for func_15030448 (attachment free): now x +9 x +8 x zero buffers x list head / neighbours."""
import random
r = random.Random(71); R = 0x804B0000
for i in range(48):
    now = i & 1; b9 = (i >> 1) & 1; b8 = (i >> 2) & 1; head = (i >> 3) % 3
    p = ['%08X=%02X%02X0000' % (R + 8, b8 * r.randint(1, 255), b9 * r.randint(1, 255))]
    for o in (0x28, 0x2C, 0x34, 0x44, 0x48, 0x4C, 0x50):
        p.append('%08X=%08X' % (R + o, 0 if r.random() < 0.3 else 0x80480000 + r.randrange(0, 0x10000, 4)))
    p.append('%08X=%08X' % (R + 0x54, 0 if r.random() < 0.4 else 0x804C0000))
    p.append('%08X=%08X' % (R + 0x58, 0 if r.random() < 0.4 else 0x804D0000))
    p.append('800C4300=%08X' % ([R, 0x804E0000, 0][head]))
    print('k%02d_n%d_l%d_c%d_h%d ! 0=%08X,1=%X ! %s ! !' % (i, now, b9, b8, head, R, now, ','.join(p)))
