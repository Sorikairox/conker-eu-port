#!/usr/bin/env python3
"""P71: setups for func_15039D68 (look angle limits), p71/knobs.sh. func_15039D44 (EU jal 0x15039D44) returns the
limit block 0x804B0000; camera record = object (EU 0x800CC6F0 + 0x32C * id) +0x318."""
import random, struct
r = random.Random(0x9D68); L = 0x804B0000; C = 0x804C0000
fb = lambda f: '%08X' % struct.unpack('>I', struct.pack('>f', f))[0]
for i in range(64):
    oid = r.randint(0, 25); cam = [0, C, C, C][i % 4]; mode = 0x100 if i % 8 == 1 else r.choice([0, 1, 0x80, 0x200])
    lim = [r.uniform(10, 80), r.uniform(-80, -10), r.uniform(5, 60), r.uniform(-60, -5), r.uniform(0, 20), r.uniform(0, 20)]
    def ang(hi, lo, m):
        return r.choice([r.uniform(lo, hi), hi + m * 0.5, hi + m * 2 + 1, lo - m * 0.5, lo - m * 2 - 1, hi, lo, r.uniform(-200, 200)])
    y = ang(lim[0], lim[1], lim[4]); p = ang(lim[2], lim[3], lim[5])
    pk = ['%08X=%08X' % (0x800CC6F0 + 0x32C * oid + 0x318, cam), '%08X=%08X' % (C + 0x2C, mode), '804D0000=%s' % fb(y), '804D0004=%s' % fb(p)]
    pk += ['%08X=%s' % (L + 4 * k, fb(v)) for k, v in enumerate(lim)]
    outs = '804D0010,3=804D0014' if i & 4 else '0,3=0'
    a = '0=804D0000,1=804D0004,2=%s,4=%s,5=%s,6=%X' % (outs, fb(r.uniform(-30, 30)), fb(r.uniform(-30, 30)), oid)
    print('k%02d_c%d_m%X ! %s ! %s ! 15039D44=%08X ! ! ! ! ' % (i, 1 if cam else 0, mode, a, ','.join(pk), L))
