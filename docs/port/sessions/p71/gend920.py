#!/usr/bin/env python3
"""P71: setups for func_1502D920 (fog alpha), p71/knobs.sh. func_150A7EE0 (EU 0x150A7EE0) writes w via its 8th
argument (OUTW N=7); D_800D9F3C / D_800D9F40 near / far, D_800DD718 / D_800DD71C fog range (u16, upper halves)."""
import random, struct
r = random.Random(0xD920)
fb = lambda f: '%08X' % struct.unpack('>I', struct.pack('>f', f))[0]
for i in range(60):
    a = r.choice([0.0, 300.0, 1000.0, 5000.0]); b = r.choice([0.0, 2.0, 10.0, 50.0])
    lo = r.randint(0, 1000); hi = r.randint(0, 1000)
    ia = 0.001 if a == 0 else 1 / a; ib = 0.001 if b == 0 else 1 / b; st = (ia - ib) * 0.001
    fmin = lo * st + ib; fmax = hi * st + ib
    k = i % 6
    if k == 0: iw = r.uniform(min(fmin, fmax), max(fmin, fmax))
    elif k == 1: iw = fmin * r.choice([0.5, 1.0, 1.5])
    elif k == 2: iw = fmax * r.choice([0.5, 1.0, 1.5])
    elif k == 3: iw = -r.uniform(0.001, 1)
    else: iw = r.uniform(0.0001, 0.5)
    w = 0.0 if i % 13 == 12 else 1 / iw
    p = '800D9F3C=%s,800D9F40=%s,800DD718=%04X0000,800DD71C=%04X0000,804B0014=%s,804B0018=%s,804B001C=%s' % (
        fb(a), fb(b), lo, hi, fb(r.uniform(-500, 500)), fb(r.uniform(-500, 500)), fb(r.uniform(-500, 500)))
    print('k%02d_%d ! 0=804B0000,1=804C0000,2=%X ! %s ! ! ! ! 150A7EE0=7:%s ! ' % (i, k, r.randint(0, 3), p, fb(w)))
