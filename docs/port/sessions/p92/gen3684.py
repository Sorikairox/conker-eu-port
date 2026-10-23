#!/usr/bin/env python3
"""P92 setups for func_15023684 (EU: D_800CC2D0 = 800CC6F0; stub func_15083E90 = jal 150842F8 returns an object
of the table or 0). usage: gen3684.py [n] > 3684.txt"""
import random, sys
from gen import Mem
R = random.Random(9236)
for i in range(int(sys.argv[1]) if len(sys.argv) > 1 else 40):
    M = Mem(); k = R.randint(0, 24); o = 0x800CC6F0 + 0x32C * k
    M.put(0x800C39CA, bytes([1 if i == 0 else R.choice([0, 0, 0, 0, 2])]))
    M.w(0x800CC6F0 + 0x25C, R.getrandbits(32))
    blk = M.alloc(0x40); M.w(o + 0x31C, 0 if i == 1 else blk); M.put(blk + 0x20, bytes([R.choice([0, 1, 3, 2])]))
    M.f(blk, 7.0)
    floor = round(R.uniform(-200, 200), 2)
    feet = floor + R.choice([0, 10, 100])
    water = R.choice([-10000.0, feet + R.choice([5, 30, 60, 200]), feet - 5, feet])
    M.f(o + 0x118, water); M.f(o + 0x18, feet); M.f(o + 0x180, floor)
    M.h(o + 0x1A6, int(water - 50 + R.choice([-20, 20, 0])) if water > -9000 else R.randint(-100, 100))
    ret = 0 if i == 2 else o
    print('s3684_%d ! 0=%X ! %s ! 150842F8=%X !  !  !  ! ' % (i, R.randint(0, 1), M.poke(R), ret))
