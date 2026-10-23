#!/usr/bin/env python3
"""P102 setups for func_15097E9C(id, cmd, args). usage: gen.py [per_cmd] [seed] [cmds hex,comma] > e9c.txt
knobs.sh lines: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB. Stubs keyed by decoded jal words (jal.txt):
func_1505EEF4 = 1505F2A0, func_150871B8 = 150871B8, func_1508712C = 1508712C, func_15084000 = 15084468,
func_15072208 = 150725C8, func_15083E90 = 150842F8, func_15031C4C = 15031C4C, func_150ADA20 = 150ADF00,
func_15048AD0 = 15048DC0, sinf = 15048050, cosf = 15047EF0, func_1510ED24 = 1510ED24.
cmd 9: no OUTW for func_1508712C (its pointers are obj +0x14.. ; the stub write faults on that page).
EU addresses (euaddr.txt): D_800D3C60 800D3C60, D_800D2104 800D2524, D_800DBFF0 800DC420, D_800BE728 800BEB48,
D_800CC2D0 800CC6F0 (25 objects of 0x32C). ROM .data (not poked, ELF values): D_8008FD8C = 1, D_80082FA0 = 0,
D_80090130 = 1, D_8009015C = 0."""
import random, struct, sys
sys.path.insert(0, '/Users/sorikairo/conker-wt/portb/docs/port/sessions/p96')
from gen import Mem, fb
N = int(sys.argv[1]) if len(sys.argv) > 1 else 4
R = random.Random(int(sys.argv[2]) if len(sys.argv) > 2 else 102)
CMDS = [int(x, 16) for x in sys.argv[3].split(',')] if len(sys.argv) > 3 else list(range(1, 0x8F)) + [0, 0x8F, 0x100]
ARR = 0x800CC6F0
SPECIAL = [0, 0, 1, 1, 2, 3, 4, 9, 0x3B, -1, 0x2000, 0x7FFFFFFF, 0x78000000, 5, 0x10, 0x80, 0x100]
SMALL = {0x2E: [2], 0x33: [2], 0x59: [3], 0x6E: [2], 0x6F: [2], 0x43: [2], 0x44: [2], 0x8D: [], 0x22: [], 0x23: []}
NARROW = {0x2A: [3], 0x2B: [3], 0x2C: [7], 0x2F: [4], 0x8B: [6]}   # u16 / s8 callee parameters: 0..0x7F

def word(R):
    c = R.random()
    if c < 0.45: return R.choice(SPECIAL)
    if c < 0.75: return R.randint(-300, 300)
    if c < 0.9: return R.randint(-0x400000, 0x400000)
    return R.getrandbits(32) - (1 << 31)

for cmd in CMDS:
    for k in range(N):
        M = Mem(); rets = {}; retf = {}; outw = {}
        slot = R.choice([0, 0, 1, 3, 7, 24])
        obj = ARR + slot * 0x32C if R.random() < 0.8 else M.alloc(0x340)
        rets['1505F2A0'] = ['%X' % obj]
        rec = M.alloc(0x200) if R.random() < 0.9 else 0
        M.w(obj + 0x31C, rec)
        M.w(obj + 0x144, M.alloc(0x10))
        pn = R.randint(0, 3); M.put(obj + 0x13F, bytes([pn]))
        tab = M.alloc(0x10); M.w(0x800D2524, tab); lst = M.alloc(0x80); M.w(tab + 4 * pn, lst)
        cam = M.alloc(0x400); M.w(0x800DC420, cam)
        for off in (0x2F8, 0x2FC, 0x300): M.f(cam + off, round(R.uniform(-3000, 3000), 2))
        M.f(cam + 0x3A0, round(R.uniform(-3.2, 3.2), 3))
        pt = M.alloc(0x20); M.w(0x800BEB48, pt)
        for i in range(8): M.w(pt + 4 * i, M.alloc(0x10))
        for b in (0x101, 0x74, 0x2FA): M.put(obj + b, bytes([R.getrandbits(8)]))
        a = [word(R) for _ in range(12)]
        # P102 v2: each k favours another value of args[2] / args[3] (flag / selector / keep cases)
        a[2] = [0, 1, 2, a[2], -1, R.choice([9, 0x3B, 4, 0x2000, 3, 5])][k % 6] if R.random() < 0.7 else a[2]
        a[3] = [a[3], 0, 0x7FFFFFFF, 1, 0, a[3]][k % 6] if R.random() < 0.6 else a[3]
        if cmd == 8:
            for i in (2, 3, 4): a[i] = 0x7FFFFFFF if R.random() < 0.4 else R.randint(-3000, 3000)
        for i in SMALL.get(cmd, []): a[i] = R.randint(0, 3)
        for i in NARROW.get(cmd, []): a[i] = R.randint(0, 0x7F)
        if cmd in (0x22, 0x23):
            for i in range(2, 12):
                a[i] = R.choice([0x78000000, 0x7FFFFFFF, R.randint(-0x20000, 0x20000)])
        if cmd == 0x34 or cmd == 0x71:
            lo = R.randint(-2000, 1000); a[2:8] = [lo, lo + R.randint(0, 2000), R.randint(-2000, 1000), 0, 0, 0]
            a[3] = a[2] + R.randint(-50, 2000); a[4] = R.randint(-2000, 1000); a[5] = a[4] + R.randint(-50, 2000)
            a[6] = R.randint(-200, 200); a[7] = R.randint(-200, 200)
            if cmd == 0x71: a[5] = a[4] + R.randint(1, 500)
        nw = R.choice([2, 3, 3, 4, 4, 5, 6, 8, 10])
        M.w(0x800D3C60, nw)
        args = M.alloc(0x40); a[0] = R.getrandbits(8); a[1] = cmd
        for i, v in enumerate(a): M.w(args + 4 * i, v)
        rets['150871B8'] = [R.choice(['FFFFFFFF', '3', '0', '7'])]
        rets['1508712C'] = [R.choice(['0', '1'])]
        rets['15084468'] = [R.choice(['FFFFFFFF', '5', '0', '12'])]
        o2 = ARR + R.choice([0, 2, 5, 24]) * 0x32C
        rets['150725C8'] = [R.choice(['0', '%X' % M.alloc(0x240)])]
        rets['150842F8'] = [R.choice(['0', '%X' % o2, '%X' % o2])]
        rets['15031C4C'] = [R.choice(['0', '%X' % M.alloc(0x40)])]
        if cmd == 0x78 and R.random() < 0.7: rets['1505F2A0'] = ['%X' % obj, R.choice(['0', '%X' % o2])]
        rets['150ADF00'] = ['%X' % R.getrandbits(32), '%X' % R.getrandbits(32)]
        rets['15048DC0'] = ['%X' % R.randint(1, 360)]
        retf['15048050'] = ['%08X' % fb(round(R.uniform(-1, 1), 4))]
        retf['15047EF0'] = ['%08X' % fb(round(R.uniform(-1, 1), 4))]
        if cmd != 9: outw['1508712C'] = '1:%08X/2:%08X/3:%08X' % tuple(fb(round(R.uniform(-4000, 4000), 2)) for _ in range(3))
        outw['1510ED24'] = '2:%08X' % fb(round(R.uniform(-500, 500), 2))
        print('e9c_%02X_%d ! 0=%X,1=%X,2=%X ! %s ! %s ! %s !  ! %s ! ' % (
            cmd, k, a[0], cmd, args, M.poke(R), ','.join('%s=%s' % (x, ';'.join(v)) for x, v in rets.items()),
            ','.join('%s=%s' % (x, ';'.join(v)) for x, v in retf.items()),
            ','.join('%s=%s' % (x, v) for x, v in outw.items())))
