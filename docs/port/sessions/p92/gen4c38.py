#!/usr/bin/env python3
"""P92 setups for func_15124C38 (camera arg0 on the heap; EU D_800C3671 = 800C3A91; stubs keyed by jal words:
func_15125490 = 15125A00 (RET), func_1507C7C0 = 1507C7C0 (OUTW a1 = s16 height in the high half),
func_1507E1D0 = 1507E5B0 (OUTA a2 = y)). usage: gen4c38.py [n] > 4c38.txt"""
import random, struct, sys
from gen import Mem
def fb(v): return struct.unpack('>I', struct.pack('>f', v))[0]
R = random.Random(int(sys.argv[2]) if len(sys.argv) > 2 else 9248); B = len(sys.argv) > 2
for i in range(int(sys.argv[1]) if len(sys.argv) > 1 else 60):
    M = Mem(); cam = M.alloc(0x800); hold = M.alloc(0x140); pl = M.alloc(0x130)
    M.h(cam + 0x7F4, 0 if B else R.choice([0, 0, 0, 1]))
    M.w(cam + 0x3D4, 0 if R.random() < 0.12 else pl); M.w(cam + 0x3D0, hold)
    M.w(cam + 0x2C, R.choice([0, 0x100, 0x80, 0x180, 0x2])); M.w(cam + 0x5F0, R.choice([0, 0, 0x100, 0x200, 0x800, 0x80]))
    M.w(cam + 0x84, R.choice([0, 0, 0x20000000, 0x200000, 0x200000]))
    M.put(cam + 0x23E, bytes([R.choice([0, 0, 0xC, 0x9, 0x38, 0x3B, 0x3A, 0x26, 0x13, 5])]))
    M.put(cam + 0x23C, bytes([0 if B else R.choice([0, 0, 0, 1])])); M.put(cam + 0x600, bytes([R.choice([0, 1])]))
    M.f(cam + 0x77C, R.choice([-20.0, 0.0, -15.0, -15.0])); M.f(cam + 0x360, R.choice([-10000.0, -10000.0, 50.0]))
    M.f(cam + 0x370, R.choice([50.0, 100.0, 250.0, 301.0, 500.0, 250.0])); M.f(cam + 0x2FC, round(R.uniform(-100, 300), 2))
    M.f(cam + 0x2CC, round(R.uniform(-100, 300), 2)); M.f(cam + 0x7B4, R.choice([1.0, 0.5, 2.0]))
    M.f(cam + 0x2C0, 11.0); M.f(cam + 0x2A0, 3.0)
    M.put(pl + 0x4E, bytes([R.choice([1, 0x11, 2, 0, 9])])); M.h(pl + 0x114, R.randint(-50, 200))
    M.put(pl + 0x120, bytes([0 if B else R.choice([0, 0, 0, 0, 1])]))
    M.h(hold + 0xCC, R.randint(-50, 100)); M.f(hold + 0x18, round(R.uniform(-200, 200), 2))
    M.f(hold + 0x180, round(R.uniform(-200, 200), 2)); M.f(hold + 0x28, R.choice([-10.0, 0.0, 100.0, 165.0, 169.0, 171.0, 400.0]))
    M.put(hold + 0x137, bytes([R.choice([0, 0, 0, 1])])); M.h(hold + 0x84, R.choice([0, 0, 0x194, 0x195]))
    M.put(hold + 0xAD, bytes([R.choice([0, 0, 1, 2, 0, 0])])); M.put(hold + 0x102, bytes([0 if B and R.random() < 0.85 else R.choice([0, 1])]))
    M.put(0x800C3A91, bytes([R.choice([0, 0, 0, 1])]))
    out = '80450000' if B else R.choice(['0', '0', '80450000'])
    print('%s%d ! 0=%X,1=%s ! %s ! 15125A00=%X !  ! 1507E5B0=2:%08X ! 1507C7C0=1:%08X ! ' % (
        'b4c38_' if B else 's4c38_', i, cam, out, M.poke(R), R.choice([0, 0, 1]), fb(round(R.uniform(-100, 100), 2)), (R.randint(-50, 300) & 0xFFFF) << 16))
