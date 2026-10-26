#!/usr/bin/env python3
"""P62: the D5E90.s matrix helpers vs their NON_MATCHING C (src_eu/nm_asm/D5E90_mtx.c), whole.
  * mtx_rotate_scale_3x3 (EU code 0x150A9FEC, raw words): rotation from three angles in degrees times per-row scales into
    the 3x3 part of a float matrix. Calls the hand-asm cos / sin fast_cosf / fast_sinf (not stubbed: the
    reference runs the asm ones, the candidate the NM C ones verified in P24).
    Inputs: angles (small, +-180, +-720, multiples of 90, huge 1e6 / 3e8 for the sin range-reduction paths, 0),
    scales (1.0, random, negative, 0), a matrix pre-filled with a marker pattern (row 3 / column 3 must survive).
  * mtx_f_to_l_batch: n (1..4) float matrices -> Mtx in place. Inputs: values in +-32767 with fractions, exact .5 / 2^-17
    ties for the round-to-even, negative, 0, -0.
Reference: VR4300 interpreter (nmasm_vr.Ref); candidate: Unicorn. Compared: all RDRAM outside the stack pages,
s0-s7 / fp / sp.
Run in the container from /conker/conker after both builds: python3 ../tools/port/difftest/nmasm_mtx.py [N] [seed]"""
import sys, random, struct, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from nmasm_vr import *

M = 0x80500000

def ang(rng):
    k = rng.random()
    if k < 0.1: return 0.0
    if k < 0.25: return float(rng.choice([90, -90, 180, -180, 270, 45, 360, -720]))
    if k < 0.45: return rng.uniform(-180, 180)
    if k < 0.6: return rng.uniform(-1, 1)
    if k < 0.75: return rng.uniform(-3000, 3000)
    if k < 0.85: return rng.choice([1e6, -2.5e7, 3e8, 1e10, 1e-3])
    return rng.uniform(-720, 720)

def scl(rng):
    k = rng.random()
    if k < 0.3: return 1.0
    if k < 0.4: return 0.0
    if k < 0.5: return -rng.uniform(0, 4)
    return rng.uniform(0, 4)

def fixval(rng):
    k = rng.random()
    if k < 0.1: return 0.0
    if k < 0.15: return -0.0
    if k < 0.3: return rng.randint(-32767, 32767) + rng.choice([0.5, -0.5, 0.25]) / 65536.0   # ties
    if k < 0.45: return rng.randint(-32767, 32767) / 65536.0 * rng.choice([1, 2, 4])
    if k < 0.6: return rng.uniform(-2, 2)
    return rng.uniform(-32767, 32767)

def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    n = int(args[0]) if args else 2000
    rng = random.Random(int(args[1]) if len(args) > 1 else 1)
    ref, cand = Ref(), Cand()
    base = base_image()
    sreg = {16 + i: 0x1000 * (i + 1) + 0x11 for i in range(8)}; sreg[30] = 0x9999
    bad = {'9B0C': 0, '9E64': 0}
    for t in range(n):
        mem = bytearray(base)
        for i in range(0x140):
            mem[phys(M) + i] = (0x5A + 7 * i) & 0xFF
        if t % 2 == 0:
            name = '9B0C'
            x, y, z = ang(rng), ang(rng), ang(rng)
            sc = (scl(rng), scl(rng), scl(rng))
            a = (M, b32(x), b32(y), b32(z))
            stack = tuple(b32(s) for s in sc)
            r_entry, c_entry = 0x150A9FEC, 'mtx_rotate_scale_3x3'
            info = (x, y, z, sc)
        else:
            name = '9E64'
            cnt = rng.choice([1, 1, 2, 4])
            for i in range(16 * cnt):
                mem[phys(M) + 4 * i:phys(M) + 4 * i + 4] = struct.pack('>I', b32(fixval(rng)))
            a = (M, cnt); stack = ()
            r_entry, c_entry = 0x150A9E64, 'mtx_f_to_l_batch'
            info = cnt
        m1, m2 = bytearray(mem), bytearray(mem)
        try:
            r1 = ref.run(m1, a=a, stack=stack, entry=r_entry, regs=sreg)
        except RuntimeError as e:
            print('REF', t, name, e); bad[name] += 1; continue
        r2 = cand.run(m2, a=a, stack=stack, entry=c_entry, regs=sreg)
        k1 = [r1['gpr'][i] for i in list(range(16, 24)) + [29, 30]]
        k2 = [r2['gpr'][i] for i in list(range(16, 24)) + [29, 30]]
        d = memdiff(m1, m2, skip=[(SP0 - 0x400, SP0 + 0x100)])
        if k1 != k2 or d:
            bad[name] += 1
            if sum(bad.values()) <= 6:
                print('DIFF', t, name, info, [hex(q) for q in d],
                      m1[phys(M):phys(M) + 0x40].hex(), m2[phys(M):phys(M) + 0x40].hex())
    print('nmasm_mtx trials', n, 'diffs', bad)

if __name__ == '__main__':
    main()
