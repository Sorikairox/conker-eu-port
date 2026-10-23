#!/usr/bin/env python3
"""P96 setups for func_1501E0C8(slot). EU addresses: D_800BE9F0 = 800BEE10 (!), D_80090124, D_800C3A08,
D_800BEB30 (u16), D_8000030C, D_800C39D0, D_800C40BC, D_800D3260, D_800C40B9, D_eu_800C3A60.
Stub func_1501D330 = jal 1501D330 (RET)."""
import random
from gen import Mem
R = random.Random(9608)
for i in range(60):
    M = Mem(); slot = R.choice([0, 1])
    M.w(0x800BEE10, R.choice([0x1D, 0x1D, 0x21, 0x21, 3, 0x1E]))
    M.put(0x80090124, bytes([R.choice([0, 0, 1, 0x80])]))
    M.put(0x800C3A08, bytes([R.choice([5, 5, 4, 0]), R.choice([5, 2])]))
    M.h(0x800BEB30, R.choice([0, 0x1000, 0x20, 0x1020, 0xEFDF]))
    M.w(0x8000030C, R.choice([1, 1, 0, 2]))
    M.w(0x800C39D0, R.choice([0xFA, 0xFB, 0x10, 0x200])); M.w(0x800C39D4, R.choice([0xFA, 0xFB, 0x10, 0x200]))
    M.w(0x800C3A60, R.choice([0x113, 0x114, 0x115, 0x20, 0x300])); M.w(0x800C3A64, R.choice([0x113, 0x114, 0x29, 0x2A, 0x300]))
    M.put(0x800C40BC, bytes([R.choice([0, 0, 0, 1])])); M.put(0x800C40B9, bytes([R.choice([0, 0, 1])]))
    M.put(0x800D3260, bytes([R.choice([0, 0, 0, 1])]))
    print('se0c8_%d ! 0=%X,1=800C3C88 ! %s ! 1501D330=%X !  !  !  ! ' % (i, slot, M.poke(R), R.choice([0, 1, 1, 2])))
