#!/usr/bin/env python3
"""P291: whole-function harness for the hand-asm star field func_150FBA40 (game_eu_129250) vs its NON_MATCHING C.
The asm builds 64-bit display-list words (dsll32 / daddu / sd), so difftest's MIPS32 Unicorn cannot run it.
Reference: the VR4300 interpreter of nmasm_vis5858.py on build/conker.eu.elf; candidate: the NM C in
build_nm/conker.eu.elf (Unicorn). Compared: v0 and all RDRAM except the stack page.

Inputs per trial: the 8000 stars of D_800DC2B0 (upper halves of f32 positions; most in front of the camera, some
behind, some raw), a view matrix (random rotation, or an axis-aligned one with exact coordinates: w == 203,
.5 fractions for the round-to-even, points exactly on the viewport's left / top / right / bottom edges), the camera
record D_800BE628[D_80082FA4] (player 0..3) and the list pointer (aligned or not, sometimes KSEG1).
Trials whose reference hits a trunc / cvt range error (|x| >= 2^31, a VR4300 exception) are skipped.

usage (container, /conker/conker): python3 ../tools/port/difftest/nmasm_stars.py [N] [seed]"""
import sys, random, struct, math, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from nmasm_vis5858 import Ref, Cand, RAM, SP0, phys, P, b32

STARS, CAMS, MTX, DL = 0x80300000, 0x80320000, 0x80330000, 0x80340000
D_STARS, D_CAMS, D_PLAYER = 0x800DC2B0, 0x800BEA48, 0x80083334   # EU addresses of D_800DC2B0 / D_800BE628 / D_80082FA4
N_STARS = 8000

def half(x):
    return b32(x) >> 16

def unit(rng):
    v = [rng.gauss(0, 1) for _ in range(3)]
    n = math.sqrt(sum(c * c for c in v)) or 1.0
    return [c / n for c in v]

def cross(a, b):
    return [a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]]

def case(rng, mem):
    exact = rng.random() < 0.4
    if exact:   # axis-aligned rotation: rows of right / up / fwd are signed unit axes
        perm = rng.sample(range(3), 3); sg = [rng.choice([-1.0, 1.0]) for _ in range(3)]
        right, up, fwd = [[0.0] * 3 for _ in range(3)]
        right[perm[0]] = sg[0]; up[perm[1]] = sg[1]; fwd[perm[2]] = sg[2]
    else:
        fwd = unit(rng); right = cross(fwd, unit(rng)); n = math.sqrt(sum(c * c for c in right)) or 1.0
        right = [c / n for c in right]; up = cross(right, fwd)
    m = [[rng.uniform(-2, 2) for _ in range(4)] for _ in range(4)]
    for i in range(3): m[i][0], m[i][1], m[i][3] = right[i], up[i], fwd[i]
    for i in range(4):
        for j in range(4): P(mem, MTX + 16 * i + 4 * j, 'I', b32(m[i][j]))
    # camera record of player p
    p = rng.randrange(4)
    P(mem, D_PLAYER, 'I', p); P(mem, D_CAMS, 'I', CAMS)
    cam = CAMS + 0x180 * p
    for a in range(cam, cam + 0x180, 4): P(mem, a, 'I', rng.getrandbits(32) & 0x3FFFFFFF)
    sx_ = rng.choice([128.0, 160.0, 64.0, rng.uniform(20, 400)]); sy_ = rng.choice([sx_, 120.0, 96.0, rng.uniform(20, 300)])
    left0 = rng.choice([0.0, 0.0, rng.uniform(0, 300), -sx_]); top0 = rng.choice([0.0, 0.0, rng.uniform(0, 200), -sy_])
    left, top = left0 + sx_, top0 + sy_
    width = rng.choice([2 * sx_ + left0, left, left + 0.5, rng.uniform(1, 700)])     # left: the centre is the right edge
    height = rng.choice([2 * sy_ + top0, top, top + 0.5, rng.uniform(1, 500)])
    for off, v in ((4, width), (8, height), (0xC, sx_), (0x10, sy_), (0x24, top0), (0x2C, left0)): P(mem, cam + off, 'I', b32(v))
    if exact and rng.random() < 0.5:   # exact projection: scale 128, w a power of 2 -> sx = left + coordinate / 2^k
        for off, v in ((0xC, 128.0), (0x10, 128.0), (0x24, rng.choice([0.0, -128.0])), (0x2C, rng.choice([0.0, -128.0]))):
            P(mem, cam + off, 'I', b32(v))
    # stars
    P(mem, D_STARS, 'I', STARS)
    for k in range(N_STARS):
        q = rng.random()
        if q < 0.55:    # behind / beside the camera (cheap rejects)
            d = unit(rng); R = rng.uniform(1, 30000)
            pos = [R * c for c in d]
        elif q < 0.6:   # raw halves (finite)
            pos = None; h = [rng.getrandbits(16) for _ in range(3)]
            h = [x if (x >> 7) & 0xFF != 0xFF else x & 0x807F for x in h]
        elif exact:     # exact coordinates along the axes
            w = rng.choice([203.0, 203.0, 202.0, 204.0, 256.0, 512.0, 1024.0, 4096.0])
            pos = [0.0] * 3
            for i in range(3):
                pos[i] = fwd[i] * w + right[i] * rng.choice([0.0, 0.5, 1.0, 1.5, -0.5, rng.randrange(-300, 300) * 0.5]) * w / 128 \
                    + up[i] * rng.choice([0.0, 0.5, -1.5, rng.randrange(-300, 300) * 0.25]) * w / 128
        else:           # in front, near the view direction
            R = rng.choice([rng.uniform(100, 400), rng.uniform(400, 30000)])
            j = rng.uniform(0, 1.5)
            d = [fwd[i] + j * rng.gauss(0, 1) * (right[i] + up[i]) for i in range(3)]
            n = math.sqrt(sum(c * c for c in d)) or 1.0
            pos = [R * c / n for c in d]
        if pos is not None: h = [half(c) for c in pos]
        tint = rng.choice([0, 1, 2, 3, rng.randrange(256)]); alpha = rng.choice([255, 0, 1, 128, rng.randrange(256)])
        P(mem, STARS + 8 * k, '>HHHBB'[1:], h[0], h[1], h[2], tint, alpha)
    dl = DL + rng.choice([0, 0, 8, 8]) + rng.choice([0, 0, 0, 0x20000000])
    return [dl, MTX]

def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 300
    seed = int(sys.argv[2]) if len(sys.argv) > 2 else 1
    ref = Ref('build/conker.eu.elf')
    cand = Cand('build_nm/conker.eu.elf', 'build/conker.eu.elf')
    base = bytearray(RAM)
    for v, bb in cand.data(): base[phys(v):phys(v) + len(bb)] = bb
    bad = skip = 0; drawn = 0
    for t in range(n):
        rng = random.Random(seed * 100003 + t)
        mem0 = bytearray(base)
        args = case(rng, mem0)
        res = []
        for who in ('ref', 'cand'):
            mem = bytearray(mem0)
            try:
                v0 = ref.run(mem, args, entry='func_150FBA40', maxi=6000000) if who == 'ref' else cand.run(mem, args, entry='func_150FBA40')
            except RuntimeError as e:
                if 'range' in str(e) and who == 'ref': v0 = None
                else: raise
            mem[phys(SP0) - 0x1000:phys(SP0) + 0x100] = bytes(0x1100)
            res.append((v0, mem))
            if v0 is None: break
        if res[0][0] is None: skip += 1; continue
        drawn += (res[0][0] - (args[0] & ~0x20000000)) // 64
        if res[0][0] != res[1][0] or res[0][1] != res[1][1]:
            bad += 1
            if bad <= 5:
                d = next((i for i in range(RAM) if res[0][1][i] != res[1][1][i]), None)
                print('DIFF trial %d args %s: v0 ref %X cand %X; first byte %s' % (t, [hex(a) for a in args], res[0][0], res[1][0],
                      'none' if d is None else '%X ref %s cand %s' % (d, res[0][1][d & ~7:(d & ~7) + 8].hex(), res[1][1][d & ~7:(d & ~7) + 8].hex())))
    print('%s: %d differences in %d trials (%d skipped, ~%d stars drawn)' % ('EQUIV' if bad == 0 else 'DIFFER', bad, n, skip, drawn))

if __name__ == '__main__':
    main()
