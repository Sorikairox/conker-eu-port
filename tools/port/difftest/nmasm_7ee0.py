#!/usr/bin/env python3
"""P148: hand-asm trampoline func_150A7EE0 (D5650: j func_150A7E40 with $ra = func_150A7EF4, which adds the w row)
vs its NON_MATCHING C, whole. Inputs: random / special float matrices and points (0, -0, +-1, large, fractions).
Reference: VR4300 interpreter (nmasm_vr.Ref) on the ROM code; candidate: Unicorn on the NM build. Compared: all RDRAM
outside the stack pages, s0-s7 / fp / sp.
Run in the container from /conker/conker after both builds: python3 ../tools/port/difftest/nmasm_7ee0.py [N] [seed]"""
import sys, random, struct, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from nmasm_vr import *

M = 0x80500000

def fv(rng):
    k = rng.random()
    if k < 0.1: return rng.choice([0.0, -0.0, 1.0, -1.0, 0.5])
    if k < 0.2: return rng.uniform(-1e6, 1e6)
    if k < 0.3: return rng.uniform(-1e-3, 1e-3)
    return rng.uniform(-1000, 1000)

def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    n = int(args[0]) if args else 2000
    rng = random.Random(int(args[1]) if len(args) > 1 else 1)
    ref, cand = Ref(), Cand()
    base = base_image()
    sreg = {16 + i: 0x1000 * (i + 1) + 0x11 for i in range(8)}; sreg[30] = 0x9999
    bad = 0
    for t in range(n):
        mem = bytearray(base)
        for i in range(0x140):
            mem[phys(M) + i] = (0x5A + 7 * i) & 0xFF
        for i in range(16):
            mem[phys(M) + 4 * i:phys(M) + 4 * i + 4] = struct.pack('>I', b32(fv(rng)))
        x, y, z = fv(rng), fv(rng), fv(rng)
        a = (M, b32(x), b32(y), b32(z))
        outs = [M + 0x100, M + 0x104, M + 0x108, M + 0x10C]
        if t % 4 == 3: rng.shuffle(outs)
        stack = tuple(outs)
        m1, m2 = bytearray(mem), bytearray(mem)
        try:
            r1 = ref.run(m1, a=a, stack=stack, entry=0x150A7EE0, regs=sreg)
        except RuntimeError as e:
            print('REF', t, e); bad += 1; continue
        r2 = cand.run(m2, a=a, stack=stack, entry=os.environ.get('NMASM_CAND', 'func_150A7EE0'), regs=sreg)  # NMASM_CAND: harness self-check
        k1 = [r1['gpr'][i] for i in list(range(16, 24)) + [29, 30]]
        k2 = [r2['gpr'][i] for i in list(range(16, 24)) + [29, 30]]
        d = memdiff(m1, m2, skip=[(SP0 - 0x400, SP0 + 0x100)])
        if k1 != k2 or d:
            bad += 1
            if bad <= 6:
                print('DIFF', t, (x, y, z), [hex(q) for q in d], m1[phys(M) + 0x100:phys(M) + 0x110].hex(),
                      m2[phys(M) + 0x100:phys(M) + 0x110].hex())
    print('nmasm_7ee0 trials', n, 'diffs', bad)

if __name__ == '__main__':
    main()
