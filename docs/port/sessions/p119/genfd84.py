#!/usr/bin/env python3
# P119: setups for func_1517FD84 (hud_lens_set_target). usage: genfd84.py N SEED
import random, struct, sys
n, seed = int(sys.argv[1]), int(sys.argv[2]); R = random.Random(seed)
def f(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
for s in range(n):
    p = R.choice([0, 1, 3]); proj = R.choice([0, 0, 1]); vp = 0x80400000 + p * 0x180
    pk = {0x800BEA48: '80400000', vp + 0xC: f(R.choice([160.0, 80.0])), vp + 0x10: f(R.choice([120.0, 60.0])),
          vp + 0x24: f(R.choice([0.0, 5.0])), vp + 0x2C: f(R.choice([0.0, 7.5]))}
    big = [-20000.0, -10000.0, -3.5, 0.0, 12.25, 9999.0, 10000.0, 15000.0]
    args = '0=%X,1=%s,2=%s,3=%s,4=%X' % (proj, f(R.choice(big)), f(R.choice(big)), f(R.uniform(-50, 50)), p)
    w = R.choice([0.0, 0.0, 1.0, 0.5, -2.0, 0.001])
    outw = '150A7EE0=4:%s/5:%s/6:%s/7:%s' % (f(R.choice(big) / 100), f(R.choice(big) / 100), f(1.0), f(w))
    print('sfd84_%d ! %s ! %s !  !  !  ! %s ! ' % (s, args, ','.join('%08X=%s' % kv for kv in sorted(pk.items())), outw))
