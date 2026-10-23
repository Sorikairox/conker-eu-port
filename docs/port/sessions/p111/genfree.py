#!/usr/bin/env python3
"""P111 setups for the free-camera callees. EU: D_800BE628 = 800BEA48 (player entries 0x180), D_800DC630 / D_800DC4F0
/ D_800899D0 = same as US, D_800BE9E4 = 800BEE04. Stub by jal word: func_1512BBA0 1512BBA0 (RET).
D_800899D0 (z decode, .data) is poked with its real ROM words. usage: genfree.py b728|bca0 [n]"""
import random, sys
sys.path.insert(0, __file__.rsplit('/', 2)[0] + '/p96')
from gen import Mem, fb

ZTAB = [6, 0, 5, 0x20000, 4, 0x30000, 3, 0x38000, 2, 0x3C000, 1, 0x3E000, 0, 0x3F000, 0, 0x3F800]
kind = sys.argv[1]; n = int(sys.argv[2]) if len(sys.argv) > 2 else 40
R = random.Random(1110 if kind == 'b728' else 1111)
for i in range(n):
    M = Mem(); cam = M.alloc(0x900); ents = M.alloc(0x180 * 4)
    pl = R.randint(0, 3); slot = R.randint(0, 3)
    M.put(cam + 0x23D, bytes([pl])); M.h(cam + 0x1B4, slot)
    w = R.choice([8, 16, 40, 60, 100]); h = R.choice([20, 120, 240])
    M.h(0x800DC630 + pl * 0x20 + slot * 8, w); M.h(0x800DC630 + pl * 0x20 + slot * 8 + 2, h)
    if kind == 'b728':
        for k in range(16): M.w(0x800899D0 + 4 * k, ZTAB[k])
        M.w(0x800BEA48, ents); e = ents + 0x180 * pl
        x = R.randint(0, 300)
        M.f(e + 0x2C, R.choice([0.0, 10.0, float(x - 20), -1.0])); M.f(e + 0x30, R.choice([320.0, 310.0, float(x + 15), 500.0]))
        M.f(cam + 0x60C, R.choice([float(w), w + 0.6, w - 3.3, 0.0, 30.0])); M.f(cam + 0x610, round(R.uniform(0, 240), 2))
        row = M.alloc(2 * 1024); M.w(cam + 0x8BC, row)
        for k in range(max(0, x - 120), min(1024, x + 120)): M.h(row + 2 * k, R.getrandbits(16))
        depth = R.choice([0x3FFFF, 0x30000, 0x20000, 0x1000, 0])
        rets = '1512BBA0=%s' % ';'.join(R.choice(['0', '0', '0', '1']) for _ in range(6))
        print('sb728_%d ! 0=%X,1=%X,2=%X,3=%X ! %s ! %s !  !  !  ! ' % (i, cam, x, R.randint(0, 200), depth, M.poke(R), rets))
    else:
        rec = 0x800DC4F0 + pl * 0x4C; hold = M.alloc(0x100); fol = M.alloc(0x130)
        for o in (0, 0xC, 0x18, 0x24): M.put(rec + o, bytes([R.choice([0, 1, 2, 2, 4])]))
        a = R.randint(0, 120); b = R.choice([a, a + 5, max(0, a - 7), R.randint(0, 120)])
        M.w(rec + 4, a); M.w(rec + 0x10, b); M.put(rec + 0x30, bytes([R.choice([0, 1, 2, 3])]))
        M.w(cam + 0x3D0, hold); M.put(hold + 0xAD, bytes([R.choice([0, 1, 2])]))
        M.w(cam + 0x3D4, fol); M.put(fol + 0x120, bytes([R.choice([0, 0, 1])]))
        M.w(cam + 0x2C, R.choice([0, 0x80, 0x40])); M.h(cam + 0x5FE, R.choice([0, 3, 50])); M.h(cam + 0x3F0, R.choice([0, 0, 2, 30]))
        M.w(0x800BEE04, R.choice([1, 2, 3]))
        M.f(cam + 0x3F4, R.choice([-1.0, -1.0, 200.0])); M.f(cam + 0x3F8, R.choice([-1.0, 300.0]))
        M.f(cam + 0x374, round(R.uniform(50, 400), 2)); M.f(cam + 0x348, round(R.uniform(50, 400), 2))
        M.put(cam + 0x23C, bytes([R.choice([0, 1])])); M.f(cam + 0x26C, 9.0)
        M.f(cam + 0x3EC, round(R.uniform(-20, 20), 2))
        print('sbca0_%d ! 0=%X,1=%X,2=0 ! %s !  !  !  !  ! ' % (i, cam, cam + 0x3EC, M.poke(R)))
