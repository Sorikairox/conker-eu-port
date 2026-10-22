#!/usr/bin/env python3
"""P92 setups for func_1501E5AC (free = jal 100042C4, stub; EU D_800C3958 = 800C3D78). usage: gene5ac.py [n]"""
import random, sys
from gen import Mem
R = random.Random(925)
for i in range(int(sys.argv[1]) if len(sys.argv) > 1 else 30):
    M = Mem(); slot = i % 2; n = R.choice([0, 1, 2, 4, 7]) if i else 0
    if i == 1: M.w(0x800C3A88 + 4 * slot, 0)
    else:
        asset = M.alloc(8); hdr = M.alloc(8); M.w(0x800C3A88 + 4 * slot, asset); M.w(asset, hdr); M.h(hdr, n)
    e8 = M.alloc(16); M.w(0x800C39E8 + 4 * slot, e8)
    acts = M.alloc(0x40 * 8); M.w(0x800C3E70 + 4 * slot, acts)
    for j in range(8):
        M.h(e8 + 2 * j, R.choice([0, 2, 3])); M.w(acts + 0x40 * j + 4, 0x80440000 + 0x100 * j); M.w(acts + 0x40 * j + 0x38, 0x80448000 + 0x100 * j)
        M.w(0x800C3D80 + slot * 0x78 + 4 * j, 0x80450000 + 0x10 * j)
    for a in (0x800C3D78, 0x800C39F0, 0x800C39F8, 0x800C3A00): M.w(a + 4 * slot, 0x80460000 + (a & 0xFFF)); M.w(a + 4 * (1 - slot), 0x80470000)
    M.w(0x800C4170, 0x80461000)
    print('e5ac_%d ! 0=%X ! %s !  !  !  !  ! ' % (i, slot, M.poke(R)))
