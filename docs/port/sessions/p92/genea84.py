#!/usr/bin/env python3
"""P92 setups for func_1501EA84 (EU addresses: D_800C3671 = 800C3A91, D_800C3663 = 800C3A87, D_800CC2D0 = 800CC6F0,
D_800D121C = 800D163C; stub func_15022A8C = jal 15022A8C, RET per call). usage: genea84.py [n] > ea84.txt"""
import random, sys
from gen import Mem
R = random.Random(9284)
for i in range(int(sys.argv[1]) if len(sys.argv) > 1 else 40):
    M = Mem(); slot = i % 2
    M.put(0x800C3A91, bytes([R.choice([0, 0, 1])])); M.put(0x800C39E2, bytes([R.choice([0, 0, 3])]))
    M.put(0x800C3AA0, bytes([R.choice([0, 1])])); M.put(0x800C3A7E + slot, bytes([R.choice([0, 1])]))
    M.put(0x800C3A87, bytes([R.choice([1, 0])])); M.put(0x800C3E78, bytes([R.choice([5, 0])]))
    M.f(0x800C3A94, R.choice([999.0, 12.5, -3.0])); M.f(0x800C3A98, R.choice([999.0, 40.0, 0.0]))
    M.w(0x800C3A9C, R.getrandbits(32)); M.f(0x800C39C0, R.uniform(-180, 180)); M.f(0x800C39B4, 1.0)
    for j in range(3): M.h(0x800C39B8 + 2 * j, R.randint(-3000, 3000)); M.h(0x800C39AC + 2 * j, 7)
    cam = M.alloc(0x390); M.w(0x800DBFF0, cam)
    for o in (0x2F8, 0x2FC, 0x300, 0x37C, 0x388): M.f(cam + o, round(R.uniform(-900, 900), 2))
    for j in range(25):
        o = 0x800CC6F0 + 0x32C * j
        M.w(o, R.choice([0, 0x80440000, 1])); M.put(o + 0xA4, bytes([9])); M.f(o + 0xB8, 2.0); M.f(o + 0xC4, 3.0)
    rets = ';'.join(R.choice(['0', '1', '2', '0']) for _ in range(25))
    print('ea84_%d ! 0=%X ! %s ! 15022A8C=%s !  !  !  ! ' % (i, slot, M.poke(R), rets))
