#!/usr/bin/env python3
"""P92 setups for func_15124C38 (camera arg0 on the heap; EU D_800C3671 = 800C3A91; stubs keyed by jal words:
func_15125490 = 15125A00 (RET), func_1507C7C0 = 1507C7C0 (OUTW a1 = s16 height in the high half),
func_1507E1D0 = 1507E5B0 (OUTA a2 = y)). usage: gen4c38.py [n] > 4c38.txt"""
import random, struct, sys
from gen import Mem
def fb(v): return struct.unpack('>I', struct.pack('>f', v))[0]
R = random.Random(9696); B = False  # P96 targeted: 0.9 look-up path and the -10000 floor path
for i in range(int(sys.argv[1]) if len(sys.argv) > 1 else 60):
    M = Mem(); cam = M.alloc(0x800); hold = M.alloc(0x140); pl = M.alloc(0x130)
    M.h(cam + 0x7F4, 0 if B else R.choice([0, 0, 0, 1]))
    M.w(cam + 0x3D4, 0 if R.random() < 0.12 else pl); M.w(cam + 0x3D0, hold)
    T = i % 2; M.w(cam + 0x2C, 0x100 if T == 0 else R.choice([0, 0x2])); M.w(cam + 0x5F0, R.choice([0, 0x100, 0x200, 0x80]))
    M.w(cam + 0x84, R.choice([0, 0, 0x200000]) if T else 0)
    M.put(cam + 0x23E, bytes([0 if T == 0 else R.choice([0, 5, 0x13])]))
    M.put(cam + 0x23C, bytes([0 if B else R.choice([0, 0, 0, 1])])); M.put(cam + 0x600, bytes([R.choice([0, 1])]))
    M.f(cam + 0x77C, R.choice([-20.0, -16.0, -15.5])); M.f(cam + 0x360, R.choice([-10000.0, 50.0]))
    M.f(cam + 0x370, R.choice([301.0, 500.0]) if T else R.choice([50.0, 301.0])); M.f(cam + 0x2FC, round(R.uniform(-100, 300), 2))
    M.f(cam + 0x2CC, round(R.uniform(-100, 300), 2)); M.f(cam + 0x7B4, R.choice([1.0, 0.5, 2.0]))
    M.f(cam + 0x2C0, 11.0); M.f(cam + 0x2A0, 3.0)
    M.put(pl + 0x4E, bytes([R.choice([0, 2, 9])])); M.h(pl + 0x114, R.randint(-50, 200))
    M.put(pl + 0x120, bytes([0]))
    M.h(hold + 0xCC, R.randint(-50, 100)); M.f(hold + 0x18, round(R.uniform(-200, 200), 2))
    M.f(hold + 0x180, round(R.uniform(-200, 200), 2)); M.f(hold + 0x28, R.choice([100.0, 165.0, 169.0, 150.0]) if T else R.choice([0.0, 100.0, 171.0]))
    M.put(hold + 0x137, bytes([0])); M.h(hold + 0x84, R.choice([0, 0x195]))
    M.put(hold + 0xAD, bytes([R.choice([0, 2])])); M.put(hold + 0x102, bytes([0]))
    M.put(0x800C3A91, bytes([0]))
    out = '80450000' if B else R.choice(['0', '0', '80450000'])
    print('%s%d ! 0=%X,1=%s ! %s ! 15125A00=%X !  ! 1507E5B0=2:%08X ! 1507C7C0=1:%08X ! ' % (
        't4c38_' if True else '', i, cam, out, M.poke(R), 0, fb(round(R.uniform(-100, 100), 2)), (R.randint(-50, 300) & 0xFFFF) << 16))
