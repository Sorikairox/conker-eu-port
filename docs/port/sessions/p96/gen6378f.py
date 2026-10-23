#!/usr/bin/env python3
"""P96 setups for func_15126378(cam). EU addresses: D_800BE628 = 800BEA48 (pointer to 0x180-byte player entries),
D_800CC2D0 = 800CC6F0 (objects, 0x32C), D_800DBFF4 = 800DC424. Stubs by jal word: sinf 15048050, cosf 15047EF0
(RETF sequences). usage: gen6378.py [n] > 6378.txt"""
import random, struct, sys
from gen import Mem, fb
R = random.Random(int(sys.argv[2]) if len(sys.argv) > 2 else 9663); TGT = len(sys.argv) > 3  # P96: start-mode setups for the types of argv[3]
AIM = [0x23, 0x24, 0x16, 0x18, 0x41, 0xC, 0x14, 0x3F, 0x1B, 0x1F, 0x29]
for i in range(int(sys.argv[1]) if len(sys.argv) > 1 else 60):
    M = Mem(); cam = M.alloc(0x800); pl = M.alloc(0x200); hold = M.alloc(0x200); rec = M.alloc(0x10)
    ents = M.alloc(0x180 * 4); pn = R.randint(0, 3); e = ents + 0x180 * pn
    mode = i % 3   # 0 start, 1 frame, 2 other
    M.w(0x800BEA48, ents)
    M.f(e + 0x6C, R.choice([45.0, 60.0, 30.0, 5.0])); M.f(e + 0x70, R.choice([60.0, 80.0, 40.0])); M.f(e + 0x84, 0.5)
    M.put(cam + 0x23D, bytes([pn])); typ = R.choice(AIM + [0x12, 0, 5]) if R.random() < 0.85 else R.choice([0x1B, 0x1F, 0x29])
    if TGT: typ = R.choice([int(x, 16) for x in sys.argv[3].split(',')]); mode = 1 if len(sys.argv) > 4 else 0
    M.put(cam + 0x23E, bytes([typ]))
    M.w(cam + 0x3D4, pl); M.w(cam + 0x3D0, hold); M.w(cam + 0x36C, rec)
    M.h(cam + 0x36A, R.choice([0, 0x10, 0x101]))
    M.h(rec, R.choice([0x10, 0x14, 0x18]) if TGT else R.choice([0x10, 0x10, 0x18, 0x14, 0x1C, 0, 0x08]))
    M.put(rec + 2, bytes([R.choice([127, 0x80, 100, 0x9C]) & 0xFF, R.choice([127, 0x81, 110, 0x90]) & 0xFF]))
    M.put(pl + 0x197, bytes([[0, 2, R.choice([1, 3, 0, 2])][mode]]))
    M.put(pl + 0x194, bytes([R.choice([0, 1])])); M.put(pl + 0x11A, bytes([2 if TGT else R.choice([2, 2, 0, 1])]))
    M.w(pl + 0x190, R.choice([typ, typ, 0, 0x16]))
    M.f(pl + 0x184, R.choice([-20.0, -40.0, -5.0])); M.f(pl + 0x188, -30.0)
    for o in (0x16C, 0x170, 0x174, 0x178, 0x17C, 0x180): M.f(pl + o, round(R.uniform(-100, 100), 2))
    M.put(pl + 0x1AC, bytes([0 if R.random() < 0.8 else 1])); M.h(pl + 0x114, R.randint(-50, 200))
    M.h(hold + 0x84, R.choice([0x76, 0, 0x194])); v65 = R.choice([0, 0, 1, 3]); M.put(hold + 0x65, bytes([v65]))
    M.f(hold + 0x28, R.choice([0.0, 30.0]) if TGT else R.choice([0.0, 0.0, 0.5, 30.0, -2.0])); M.put(hold + 0x104, bytes([R.choice([0, 1]) if TGT else 0 if R.random() < 0.75 else 1]))
    M.put(hold + 0x1CA, bytes([R.choice([1, 1, 0])]))
    for o in (0x14, 0x18, 0x1C, 0x40): M.f(hold + o, round(R.uniform(-300, 300), 2))
    if v65:
        ob = 0x800CC6F0 + (v65 - 1) * 0x32C
        M.f(ob + 0x28, R.choice([0.0, 0.0, 10.0])); M.f(ob + 0x40, round(R.uniform(-180, 180), 2)); M.h(ob + 0x2E4, R.randint(-100, 100))
        M.put(ob + 0x2FC, bytes([R.choice([0, 1, 4])])); M.put(ob + 0x74, bytes([R.choice([0, 2, 8])]))
    else:
        M.put(hold + 0x2FC - 0x200 + 0x200 if False else hold + 0x74, bytes([R.choice([0, 2])]))
    M.w(cam + 0x5F0, R.choice([0, 0, 4, 0x10, 0x14]))
    for o in (0x2F8, 0x2FC, 0x300, 0x37C, 0x19C, 0x1A0, 0x1A4, 0x1A8):
        M.f(cam + o, R.choice([-0.5, -0.2, round(R.uniform(-60, 10), 2)]) if o >= 0x19C and o <= 0x1A8 else round(R.uniform(-300, 300), 2))
    M.f(cam + 0x7B4, R.choice([1.0, 2.0])); M.h(cam + 0x73C, 7)
    sins = ';'.join('%08X' % fb(round(R.uniform(-1, 1), 3)) for _ in range(3))
    coss = ';'.join('%08X' % fb(round(R.uniform(-1, 1), 3)) for _ in range(3))
    print((('f6378_' if len(sys.argv) > 4 else 't6378_') if TGT else 's6378_') + '%d ! 0=%X ! %s !  ! 15048050=%s,15047EF0=%s !  !  ! ' % (i, cam, M.poke(R), sins, coss))
