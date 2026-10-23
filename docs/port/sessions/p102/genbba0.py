#!/usr/bin/env python3
"""P102 setups for func_1512BBA0(cam, out, lo, hi, value, second): D_800DC634 / D_800DC636 (bss, same EU address)
entries poked; cam +0x84 bit 0x8000 / 0x4000 mixed. usage: genbba0.py [n] > bba0.txt"""
import random, sys
sys.path.insert(0, '/Users/sorikairo/conker-wt/portb/docs/port/sessions/p96')
from gen import Mem
R = random.Random(1020)
for i in range(int(sys.argv[1]) if len(sys.argv) > 1 else 24):
    M = Mem(); cam = M.alloc(0x300); out = M.alloc(0x10)
    p = R.randint(0, 3); s = R.randint(0, 3)
    M.put(cam + 0x23D, bytes([p])); M.h(cam + 0x1B4, s)
    M.w(cam + 0x84, R.choice([0x8000, 0, 0x4000, 0xC000, 0x18000]) | (R.getrandbits(32) & 0xFFFF3FFF if R.random() < 0.3 else 0))
    e = 0x800DC634 + p * 0x20 + s * 8
    v1 = R.choice([R.randint(-0x6000, 0x6000), R.randint(0x4000, 0x7FFF), R.randint(1, 200)])
    v2 = R.choice([R.randint(-0x6000, 0x6000), R.randint(0x4000, 0x7FFF), R.randint(1, 200)])
    M.h(e, v1); M.h(e + 2, v2)
    sec = R.choice([0, 1])
    v = v2 if sec else v1
    lo = v + R.choice([-5, 5, 300, v, R.randint(-500, 500)])
    hi = R.randint(-100, 100); val = hi + R.choice([-3, 3, 0])
    print('bba0_%d ! 0=%X,1=%X,2=%X,3=%X,4=%X,5=%X ! %s !  !  !  !  ! ' % (i, cam, out, lo & 0xFFFFFFFF, hi & 0xFFFFFFFF,
          val & 0xFFFFFFFF, sec, M.poke(R)))
