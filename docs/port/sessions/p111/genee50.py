#!/usr/bin/env python3
"""P111 setups for func_1512EE50(cam). EU data: D_800D2778 = 800D2778 (node table pointer, 16-byte nodes),
D_800DC450 / D_800DC454 = same (0x18-byte position records), D_800CC2D0 = 800CC6F0 (objects, 0x32C each).
Stubs by decoded jal word: func_15123934 15123EA4 (RET 0/1), func_15086268 15086268 (node index),
func_1505EEF4 1505F2A0 (object pointer), func_150ADDE0 150ADDE0 (RETF), func_15048F20 15049210 (OUTA / OUTW a2 =
the candidate point), func_150AD78C 150ADC6C / func_150AD780 150ADC60 (RETF).
usage: genee50.py [mode-set] > ee50.txt"""
import random, struct, sys
sys.path.insert(0, __file__.rsplit('/', 2)[0] + '/p96')
from gen import Mem, fb

OBJS = 0x800CC6F0
R = random.Random(111)
MODES = [4, 7, 7, 7, 5, 5, 0xB, 0xA, 0xE, 0xE, 0xF, 3, 2, 2, 1, 1, 0, 0, 0xD, 6, 9]
n = int(sys.argv[1]) if len(sys.argv) > 1 else 120
DEEP = len(sys.argv) > 2
ALL = len(sys.argv) > 2 and sys.argv[2] == 'all'
if DEEP: R = random.Random(1113 if ALL else 1112); MODES = MODES if ALL else [7]
for i in range(n):
    M = Mem(); cam = M.alloc(0x960); h3d4 = M.alloc(0x130); hold = M.alloc(0x200); r36c = M.alloc(0x10)
    nodes = M.alloc(16 * 8); recs = M.alloc(0x18 * 4)
    mode = MODES[i % len(MODES)]
    req = cam + 0x6FC; st = cam + 0x6CC
    M.w(cam + 0x2C, R.choice([0, 0, 0, 0, 0x40, 0x400, 0x2000]) | (0x100 if R.random() < 0.03 else 0) | (0x40000 if R.random() < 0.03 else 0))
    M.h(cam + 0x73C, 1 if R.random() < 0.03 else 0)
    M.w(cam + 0x3D4, h3d4); M.put(h3d4 + 0x120, bytes([R.choice([0, 0, 0, 1])]))
    M.w(cam + 0x3D0, hold); M.f(hold + 0x3C, R.choice([10.0, 30.0, 31.5, 50.0]))
    M.w(cam + 0x36C, r36c); M.h(r36c, R.choice([0, 1, 4, 8, 0x10]))
    M.put(cam + 0x92C, bytes([R.choice([0, 0, 1])])); M.put(cam + 0x948, bytes([7]))
    M.put(cam + 0x23C, bytes([R.choice([0, 0, 1])])); M.put(cam + 0x23D, bytes([R.randint(0, 3)]))
    M.w(cam + 0x6C8, R.choice([0, 0, 1, 1, 2])); M.w(cam + 0x84, R.getrandbits(32)); M.w(cam + 0x5F0, R.getrandbits(32))
    M.w(cam + 0x134, R.randint(0, 9)); M.w(cam + 0x628, 5); M.w(cam + 0x614, 0x80431234)
    M.h(cam + 0x1B4, R.randint(-500, 500)); M.h(cam + 0x1E0, R.randint(-500, 500))
    M.w(cam + 0x738, 9); M.w(cam + 0x734, 9)
    for o in (0x2A4, 0x2A8, 0x2AC, 0x2F8, 0x2FC, 0x300, 0x27C, 0x280, 0x284, 0x288, 0x28C, 0x290, 0x618, 0x61C,
              0x620, 0x348, 0x34C, 0x370, 0x8F0, 0x8F4, 0x8F8, 0x8FC, 0x900, 0x904):
        M.f(cam + o, round(R.uniform(-400, 400), 2))
    M.f(cam + 0x374, R.choice([50.0, 200.0, 600.0, 1000.0]))
    for o in (0x908, 0x90C, 0x910, 0x914, 0x918, 0x91C, 0x924, 0x928, 0x62C, 0x5DC, 0x670, 0x278):
        M.f(cam + o, round(R.uniform(-3, 3), 3))
    M.f(cam + 0x37C, round(R.uniform(-180, 180), 2)); M.f(cam + 0x384, 1.0); M.f(cam + 0x39C, round(R.uniform(-180, 180), 2))
    M.f(cam + 0x7B4, R.choice([1.0, 2.0]))
    M.h(cam + 0x920, R.getrandbits(8) if R.random() < 0.7 else R.choice([0, 2, 0x40, 0x42, 0x10, 0x18, 0x24]))
    M.h(cam + 0x272, R.randint(-1, 3))
    # request
    rid = R.randint(0, 5)
    M.w(req, mode); M.h(req + 4, rid)
    if mode == 5: arg = R.choice([5, 0x11, 3, 0])
    elif mode == 7: arg = R.getrandbits(8)
    else: arg = R.choice([0, 0, 40, 120, 0x80000010])
    M.w(req + 8, arg)
    for o in (0x10, 0x12, 0x14): M.h(req + o, R.randint(-600, 600))
    a = R.randint(0, 3) if mode == 5 else R.choice([R.randint(0, 3), 150, 400, 900, 0x80000020])
    if mode in (0xA, 0xE) and R.random() < 0.5: a = (a & ~0xFF) | R.randint(0, 255)
    M.w(req + 0x1C, a); M.w(req + 0x20, R.choice([0, 60, 250, 0x90000000]))
    M.h(req + 0x34, 3)
    # state
    M.h(st, R.choice([0, 1, 1, 1, 1])); M.h(st + 2, rid if R.random() < 0.7 else rid + 1)
    M.h(st + 4, R.choice([0, 1, 1, 0xE, 4, 7])); M.h(st + 6, R.choice([0, 0, 0, 0, 1])); M.h(st + 8, R.choice([0, 0, 0, 0, 1]))
    M.f(st + 0x10, R.choice([0.0, 0.3, 0.99, 1.0])); M.f(st + 0x14, R.choice([0.0, 0.01, 0.038, 0.04]))
    M.f(st + 0x18, round(R.uniform(-400, 400), 2)); M.f(st + 0x20, round(R.uniform(-400, 400), 2))
    for o in (0x24, 0x28, 0x2C): M.f(st + o, 5.0)
    # node graph
    M.w(0x800D2778, nodes)
    for k in range(8):
        e = nodes + 16 * k
        for j in range(3): M.h(e + 2 * j, R.randint(-800, 800))
        M.put(e + 9, bytes([R.choice([0xFF, R.randint(0, 7), R.randint(0, 7)]) for _ in range(5)]))
    M.w(0x800DC450, recs); M.w(0x800DC454, 0x80431000)
    for k in range(4):
        for j in range(3): M.h(recs + 0x18 * k + 2 * j, R.randint(-800, 800))
    for k in range(4):
        for j in range(3): M.f(OBJS + 0x32C * k + 0x14 + 4 * j, round(R.uniform(-500, 500), 2))
    if DEEP:
        M.w(cam + 0x2C, 0); M.h(st, 1); M.h(st + 2, rid); M.h(st + 6, 0); M.h(st + 8, 0); M.put(h3d4 + 0x120, bytes([0]))
        M.h(cam + 0x73C, 2 if i % 10 == 9 else 0); M.w(cam + 0x84, R.getrandbits(32) | 0x80000006)
        M.w(req + 8, R.getrandbits(8) & ~2 if i % 2 else R.getrandbits(8))
        if ALL and mode == 5: M.w(req + 8, [5, 0x11, 0x11, 3][i % 4]); M.h(cam + 0x272, R.choice([-1, a, a]))
        if ALL and mode in (2, 1, 0): M.f(cam + 0x374, 1500.0)
        if ALL and i % 7 == 3: M.w(cam + 0x2C, 0x440); M.h(st, 0)
        if ALL and mode == 0xB: M.w(req + 8, [0x80000010, 0xC0000001, 77][i % 3])
        if ALL and mode == 2 and i % 2:
            for o, v in ((0x2F8, 200.0), (0x2A4, 0.0), (0x300, 0.0), (0x2AC, 0.0), (0x374, 200.0)): M.f(cam + o, v)
            M.w(req + 0x1C, 200)
        if ALL: pass
        elif i % 5 == 2: M.w(req + 8, 4 | (R.getrandbits(8) & 0x28)); M.w(cam + 0x84, R.getrandbits(32) & ~0x20000)
        if not ALL and i % 3 == 0: M.w(req + 8, R.getrandbits(8) & ~0x10)
        if i % 3 == 0:
            for o in (0x2F8, 0x2FC, 0x300): M.f(cam + o, 0.0)
        if i % 4 == 1: M.f(cam + 0x2FC, 2.0e7)
        for k in range(8): M.put(nodes + 16 * k + 9, bytes([R.randint(0, 7), R.randint(0, 7), 0xFF, R.randint(0, 7), 0xFF]))
    rets = ['15123EA4=%s' % ';'.join(R.choice(['0', '1', '1']) if not DEEP else '1' for _ in range(3)), '15086268=%X' % R.randint(0, 7)]
    if mode in (0xA, 0xE):
        o = R.choice([0, OBJS + 0x32C * R.randint(0, 3), M.alloc(0x40)])
        if o:
            for j in range(3): M.f(o + 0x14 + 4 * j, round(R.uniform(-500, 500), 2))
        rets.append('1505F2A0=%X' % o)
    retf = ['150ADDE0=%X' % fb(round(R.uniform(-300, 300), 2)), '150ADC6C=%X' % fb(round(R.uniform(-1, 1), 3)),
            '150ADC60=%X' % fb(round(R.uniform(-1, 1), 3))]
    pts = [fb(round(R.uniform(-800, 800), 2)) for _ in range(5)]
    if DEEP and i % 3 == 0: pts = [fb(10.0), fb(-10.0), fb(-10.0), fb(-10.0), fb(3.0)]
    if DEEP and i % 4 == 1: pts = [fb(5.0), fb(7.0), fb(9.0), fb(1.0), fb(2.0)]
    if (DEEP and i % 3 == 0) or (DEEP and i % 4 == 1) or R.random() < 0.5:
        outw = '15049210=2:%s' % ';'.join('%X' % v for v in pts); outa = ''
    else:
        outw = ''; outa = '15049210=2:%s' % ';'.join('%X' % v for v in pts[:3])
    print(('aee50' if ALL else 'dee50' if DEEP else 'see50') + '_%d ! 0=%X ! %s ! %s ! %s ! %s ! %s ! ' % (i, cam, M.poke(R), ','.join(rets), ','.join(retf), outa, outw))
