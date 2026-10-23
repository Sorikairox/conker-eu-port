#!/usr/bin/env python3
"""P96 setups for func_1512B2C4(cam). EU: D_800BE628 = 800BEA48 (entries 0x180), D_800DC620..62C (= US).
Stubs by jal word: func_1512BAAC 1512BAAC (RET). The projection / turn callees write globals and +0x3EC,
so those are poked directly. usage: genb2c4.py [n] > b2c4.txt"""
import random
from gen import Mem
R = random.Random(96221)
for i in range(24):
    M = Mem(); cam = M.alloc(0x900); hold = M.alloc(0x200); rec = M.alloc(0x10); ents = M.alloc(0x180 * 4)
    pn = R.randint(0, 3); e = ents + 0x180 * pn; M.w(0x800BEA48, ents)
    M.put(cam + 0x23D, bytes([pn])); M.w(cam + 0x3D0, hold); M.w(cam + 0x36C, rec); M.h(rec, R.choice([0, 1, 2, 3, 4]))
    M.w(cam + 0x84, R.choice([0, 0, 0x10]))
    M.f(hold + 0x17C, R.choice([100.0, 50.0, -20.0])); M.f(hold + 0x180, R.choice([0.0, 60.0, 120.0]))
    M.f(cam + 0x2C0, R.choice([30.0, 59.0, 60.0, 61.0, 80.0, 10.0]))
    for o in (0x2BC, 0x2C4, 0x2F8, 0x2FC, 0x300, 0x3FC, 0x400, 0x404): M.f(cam + o, round(R.uniform(-300, 300), 2))
    M.f(cam + 0x7B4, R.choice([1.0, 2.0]))
    # viewport y0 / y1 / x0 / x1 at +0x24 / +0x28 / +0x2C / +0x30
    M.f(e + 0x24, 10.5); M.f(e + 0x28, 230.5); M.f(e + 0x2C, 12.5); M.f(e + 0x30, 310.5)
    M.f(0x800DC620, R.choice([11.5, 12.0, 12.7, 150.3, 309.9, 310.0, 400.0, -5.0, 200.0]))
    M.f(0x800DC624, R.choice([9.0, 10.0, 10.5, 120.8, 229.5, 230.0, 300.0, 100.0]))
    M.f(0x800DC628, R.choice([0.5, 1000.7, 70000.2, -3.9]))
    M.f(0x800DC62C, R.choice([0.0, 0.0, 2.5, -1.0]))
    M.f(cam + 0x3EC, R.choice([0.0, 2.9, 3.0, 3.1, -3.5, 45.0, -10.0]))
    M.w(cam + 0x240, R.choice([0, 1, 1, 2])); M.w(cam + 0x698, 5); M.h(cam + 0x5F8, 7); M.put(cam + 0x8B8, bytes([9])); M.h(cam + 0x8BA, 9)
    print('fb2c4_%d ! 0=%X ! %s ! 1512BAAC=%X !  !  !  ! ' % (i, cam, M.poke(R), 0 if R.random() < 0.85 else 1))
