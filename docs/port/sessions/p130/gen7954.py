#!/usr/bin/env python3
# P130: setups for func_15187954 (knobs.sh format). World objects (0xA0 bytes) at 0x80400000 = D_800DBEF4.
import random
rng = random.Random(7954)
OBJ, BUF = 0x80400000, 0x80440000
for s in range(40):
    n = rng.choice([0, 1, 2, rng.randrange(1, 30), 40])
    x, z, r = rng.randrange(-3000, 3000), rng.randrange(-3000, 3000), rng.choice([0xE6, rng.randrange(0, 500)])
    pk = ['800DC320=%08X' % n, '800DC324=%08X' % OBJ]
    for k in range(n):
        o = OBJ + 0xA0 * k
        sz0, sz1 = rng.randrange(0, 600), rng.randrange(0, 600)
        if rng.random() < 0.2: sz0 = sz1
        size = max(sz0, sz1)
        def coord(c, lo, hi):
            q = rng.random()
            if q < 0.15: return hi + size        # exactly touching the box edge
            if q < 0.3: return lo - size
            if q < 0.4: return hi + size + 1
            if q < 0.5: return lo - size - 1
            return c + rng.randrange(-r - size - 300, r + size + 300)
        ox, oz = coord(x, x - r, x + r), coord(z, z - r, z + r)
        ox, oz = max(-0x8000, min(0x7FFF, ox)), max(-0x8000, min(0x7FFF, oz))
        f6e = 1 if rng.random() < 0.1 else 0
        f4f = rng.choice([0, 0, 0, 0x20, 0x40, 0x9F])
        pk += ['%08X=%08X' % (o + 0x10, (ox & 0xFFFF) << 16 | rng.getrandbits(16)),
               '%08X=%08X' % (o + 0x14, (oz & 0xFFFF) << 16 | rng.getrandbits(16)),
               '%08X=%08X' % (o + 0x4C, rng.getrandbits(24) << 8 | f4f),
               '%08X=%08X' % (o + 0x50, sz0 << 16 | sz1),
               '%08X=%08X' % (o + 0x6C, rng.getrandbits(8) << 24 | rng.getrandbits(8) << 16 | f6e << 8 | rng.getrandbits(8))]
    cnt = rng.choice([0, 3, rng.randrange(0, 60)])
    k = rng.randrange(0, 6)
    args = '0=%X,1=%X,2=%X,3=%X,4=80450000,5=%X,6=%X' % (x & 0xFFFFFFFF, z & 0xFFFFFFFF, r, BUF, BUF + 0x2000, cnt)
    ret = '150A6324=%X' % (BUF + cnt * 20 + 0x3C * k)
    print('s%d ! %s ! %s ! %s ! ! ! !' % (s, args, ','.join(pk), ret))
