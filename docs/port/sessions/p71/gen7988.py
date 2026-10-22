#!/usr/bin/env python3
"""P71: setups for func_15037988 (point in joint range), p71/knobs.sh. Objects at EU 0x800CC6F0, 0x32C each, +0x1D4."""
import random, struct
r = random.Random(0x7988); M = 0x804B0000
fb = lambda f: '%08X' % struct.unpack('>I', struct.pack('>f', f))[0]
for i in range(48):
    oid = r.randint(0, 25); nomtx = i % 9 == 8; force = i % 11 == 10
    j1 = r.randint(0, 5); j2 = r.randint(0, 5); lim = r.choice([10.0, 50.0, 0.5, 200.0])
    dist = r.choice([lim * 0.5, -lim * 0.5, lim, -lim, lim * 2, -lim * 3, 0.0])
    p = ['%08X=%08X' % (0x800CC6F0 + 0x32C * oid + 0x1D4, 0 if nomtx else M)]
    p += ['%08X=%s' % (M + 4 * k, fb(r.uniform(-100, 100))) for k in range(6 * 16)]
    a = '0=%X,1=%X,2=%X,3=%s,4=%s,5=%s,6=804C0000,7=%s,8=%X,9=%X' % (oid, j1, j2, fb(r.uniform(-200, 200)), fb(r.uniform(-200, 200)),
        fb(r.uniform(-200, 200)), fb(lim), 1 if force else 0, r.randint(0, 3))
    print('k%02d_o%d_m%d_f%d ! %s ! %s ! ! ! ! 15038758=0:%s ! ' % (i, oid, 0 if nomtx else 1, force, a, ','.join(p), fb(dist)))
