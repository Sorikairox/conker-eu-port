#!/usr/bin/env python3
"""P71: setups for func_1502EF24 (tint colour / alpha), p71/knobs.sh. cosf = EU jal target (RETF)."""
import random, struct, sys
COS = sys.argv[1] if len(sys.argv) > 1 else '0'
r = random.Random(0xEF24); R = 0x804B0000
fb = lambda f: '%08X' % struct.unpack('>I', struct.pack('>f', f))[0]
for i in range(54):
    kind = i % 9
    word = r.choice([r.randint(0, 0xFF), 0x804C0000, r.getrandbits(32) & 0xFFFFFF00 | 0x01000000]) if kind != 1 else r.choice([r.randint(0, 0xFF), 0x804C0000])
    if kind in (4, 5, 6, 7): word = r.getrandbits(32)
    pc = r.choice([-10.0, 0.0, 37.5, 100.0, 255.0, 300.0])
    p = ['%08X=%08X' % (R + 0xA0, word), '%08X=%02X%02X%02X%02X' % (R + 0xA4, kind, r.randint(0, 255), r.randint(0, 255), r.randint(0, 255)),
         '804C0000=%s' % fb(pc)]
    print('k%02d_t%d ! 0=%08X,1=804D0000,2=804D0004,3=804D0008,4=804D000C ! %s ! ! %s=%s ! ! ! ' % (i, kind, R, ','.join(p), COS, fb(r.uniform(-1, 1))))
