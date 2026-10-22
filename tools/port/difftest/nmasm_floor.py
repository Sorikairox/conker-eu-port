#!/usr/bin/env python3
"""P53: func_150A44A4 (hand asm, floor height of a triangle under (x, z)) vs its NON_MATCHING C (game_eu_D1760.c).
Reference: VR4300 interpreter (nmasm_vr.Ref; the asm uses ldl / ldr and keeps s5-s7 / fp in f1-f4); candidate: Unicorn.
Inputs: random s16 triangles (mixed scales, shared z / x values, points on vertices and edges, slivers), passed
either as 3 vertex pointers (a2, a3 = 0) or 9 inline halfwords (a3; sometimes with a zero first / second 8 bytes);
x / z floats near or inside the triangle (incl. .5 ties for the cvt.w.s rounding).
Compared: v0, the output float, s0-s7 / fp / sp, all RDRAM.
Run in the container from /conker/conker: python3 ../tools/port/difftest/nmasm_floor.py [N] [seed] [--mutant]"""
import sys, random, struct, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from nmasm_vr import *

def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    n = int(args[0]) if args else 3000
    rng = random.Random(int(args[1]) if len(args) > 1 else 1)
    ref, cand = Ref(), Cand()
    base = base_image()
    VA, PK, OUT = 0x80500100, 0x80500200, 0x80500300
    bad = 0; hist = {}
    for t in range(n):
        sc = rng.choice([4, 30, 300, 3000, 30000])
        pool = [rng.randint(-sc, sc) for _ in range(4)]
        def c(): return max(-32768, min(32767, rng.choice(pool) if rng.random() < 0.25 else rng.randint(-sc, sc)))
        v = [[c(), c(), c()] for _ in range(3)]
        if rng.random() < 0.15: v[1][0] = v[0][0]                     # vertical edge in x
        k = rng.random()
        if k < 0.2:
            j = rng.randrange(3); x, z = float(v[j][0]), float(v[j][2])
        elif k < 0.35:
            i, j = rng.sample(range(3), 2); u = rng.random()
            x = v[i][0] + (v[j][0] - v[i][0]) * u; z = v[i][2] + (v[j][2] - v[i][2]) * u
        elif k < 0.45:
            x = rng.randint(-sc, sc) + 0.5; z = rng.randint(-sc, sc) + rng.choice([0.5, -0.5, 0.0])
        else:
            w = [rng.random() for _ in range(3)]; s = sum(w)
            x = sum(v[i][0] * w[i] for i in range(3)) / s + rng.uniform(-2, 2)
            z = sum(v[i][2] * w[i] for i in range(3)) / s + rng.uniform(-2, 2)
        mem = bytearray(base)
        packed = rng.random() < 0.5
        if packed:
            P = struct.pack('>9h', *[q for vv in v for q in vv])
            r = rng.random()
            if r < 0.05: P = bytes(8) + P[8:]
            elif r < 0.1: P = P[:8] + bytes(8) + P[16:]
            off = rng.choice([0, 2, 6])                               # ldl / ldr on unaligned halfword data
            mem[phys(PK + off):phys(PK + off) + 18] = P
            a = (0x12345678, PK + off)
        else:
            for i in range(3):
                mem[phys(VA + 4 * i):phys(VA + 4 * i + 4)] = struct.pack('>I', 0x80500400 + 0x10 * i)
                mem[phys(0x80500400 + 0x10 * i):phys(0x80500400 + 0x10 * i) + 6] = struct.pack('>3h', *v[i])
            a = (VA, 0)
        mem[phys(OUT):phys(OUT) + 4] = struct.pack('>I', 0xDEADBEEF)
        fa = {12: b32(x), 14: b32(z)}
        sreg = {16 + i: 0x1000 * (i + 1) + 0x11 for i in range(8)}; sreg[30] = 0x9999
        m1, m2 = bytearray(mem), bytearray(mem)
        try:
            r1 = ref.run(m1, a=(0, 0) + a, fa=fa, stack=(OUT,), entry=0x150A44A4, regs=sreg)
        except RuntimeError as e:
            print('REF', t, e); bad += 1; continue
        r2 = cand.run(m2, a=(0, 0) + a, fa=fa, stack=(OUT,), entry='func_150A44A4', regs=sreg)
        k1 = (r1['v0'], [r1['gpr'][i] for i in list(range(16, 24)) + [29, 30]])
        k2 = (r2['v0'], [r2['gpr'][i] for i in list(range(16, 24)) + [29, 30]])
        d = memdiff(m1, m2, skip=[(SP0 - 0x400, SP0 + 0x100)])
        key = 'hit' if r1['v0'] else 'miss'
        hist[key] = hist.get(key, 0) + 1
        if k1 != k2 or d:
            bad += 1
            if bad <= 6: print('DIFF', t, 'packed' if packed else 'ptrs', v, x, z, hex(r1['v0']), hex(r2['v0']),
                               struct.unpack('>f', m1[phys(OUT):phys(OUT) + 4]), struct.unpack('>f', m2[phys(OUT):phys(OUT) + 4]), [hex(q) for q in d])
    print('func_150A44A4 trials', n, 'diffs', bad, hist)

if __name__ == '__main__':
    main()
