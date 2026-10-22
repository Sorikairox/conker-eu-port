#!/usr/bin/env python3
"""P71 (the out pointers are fixed per setup: DIFFTEST_ARG choices follow the per-trial rng, the same in every setup) (func_1502B6BC is EU 0x1502B9AC in the jal): knob setups for func_15030100 (asset 9 multi-DL load): refs 0 / n, load fails, 0..5 lists, null outs."""
import random
r = random.Random(7100); H = 0x804B0000
for i in range(40):
    idx = r.choice([0, 5, 6, 0x1F]); refs = 0 if i % 3 else r.randint(1, 254); n = i % 6
    fail = i % 7 == 3
    p = []
    w = 0x800DFC00 + (idx & ~3); sh = 24 - 8 * (idx & 3)
    p.append('%08X=%08X' % (w, refs << sh))
    p.append('%08X=%08X' % (0x800E0578 + 4 * idx, H))
    p.append('%08X=%08X' % (H, H + 0x1000))
    p.append('%08X=%08X' % (H + 4, n * 4 + r.randint(0, 3)))
    for k in (8, 0xC, 0x10):
        p.append('%08X=%08X' % (H + k, r.getrandbits(32)))
    for k in range(n):
        p.append('%08X=%08X' % (H + 0x1000 + 4 * k, 0x200 + 0x40 * k))
    a = '0=%X,1=804C0100,2=804C0200,3=804C0300,4=%s,5=%s,6=%s' % (idx, ['0','804C0400'][i&1], ['0','804C0410'][(i>>1)&1], ['0','804C0420'][(i>>2)&1])
    print('k%02d_i%X_r%d_n%d_f%d ! %s ! %s ! 1502B9AC=%s ! ' % (i, idx, refs, n, fail, a, ','.join(p), '0' if fail else '%08X' % H))
