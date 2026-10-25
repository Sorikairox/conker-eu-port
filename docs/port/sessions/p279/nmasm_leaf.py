#!/usr/bin/env python3
"""P279: whole-function harness for two hand-asm leaf functions that use 64-bit ld / sd (Unicorn MIPS32 cannot run
the reference): func_150A80F0 (mtx_scale_fixed, game_eu_D5900) and func_150B2290 (texture_green_to_grey,
game_eu_DFAA0). Reference: the VR4300 interpreter of nmasm_vis5858.py on build/conker.eu.elf; candidate: the NM C in
build_nm/conker.eu.elf (Unicorn). Compared: v0 and all RDRAM except the stack page.

usage (container, /conker/conker): python3 ../docs/port/sessions/p279/nmasm_leaf.py 80f0|b2290 [N] [seed]"""
import sys, random, struct
sys.path.insert(0, '/conker/tools/port/difftest')
from nmasm_vis5858 import Ref, Cand, RAM, SP0, phys, P

BUF = 0x80300000
FN = {'80f0': 'func_150A80F0', 'b2290': 'func_150B2290'}

def fbits(x):
    return struct.unpack('>I', struct.pack('>f', x))[0]

def case(mode, rng, mem):
    for a in range(BUF - 0x40, BUF + 0x2000, 4): P(mem, a, 'I', rng.getrandbits(32))
    if mode == '80f0':
        def one():
            k = rng.random()
            if k < 0.15: return rng.choice([0.0, -0.0, 1.0, -1.0, 0.5, -0.5, 32767.99, -32768.0, 1.0 / 65536, -1.0 / 65536, 1.5 / 65536])
            if k < 0.45: return rng.uniform(-4, 4)
            if k < 0.7: return rng.uniform(-32767, 32767)
            return (rng.randrange(-1 << 20, 1 << 20) + rng.choice([0, 0.25, 0.5, 0.75])) / 65536.0
        return [BUF, fbits(one()), fbits(one()), fbits(one())]
    k = rng.choice([1, 1, 2, 3, 8, 33, 128, 300])
    end = BUF + 16 * k + rng.choice([0, 0, 0, -16 * k, 4, 20 - 16 * k if k > 1 else 4])
    return [BUF, end]

def main():
    mode = sys.argv[1]
    n = int(sys.argv[2]) if len(sys.argv) > 2 else 400
    seed = int(sys.argv[3]) if len(sys.argv) > 3 else 1
    ref = Ref('build/conker.eu.elf')
    cand = Cand('build_nm/conker.eu.elf', 'build/conker.eu.elf')
    base = bytearray(RAM)
    for v, bb in cand.data(): base[phys(v):phys(v) + len(bb)] = bb
    bad = skip = 0
    for t in range(n):
        res = []
        for who in ('ref', 'cand'):
            rng = random.Random(seed * 100003 + t)
            mem = bytearray(base)
            args = case(mode, rng, mem)
            try:
                v0 = ref.run(mem, args, entry=FN[mode]) if who == 'ref' else cand.run(mem, args, entry=FN[mode])
            except RuntimeError as e:
                if 'range' in str(e): v0 = None
                else: raise
            mem[phys(SP0) - 0x1000:phys(SP0) + 0x100] = bytes(0x1100)
            res.append((v0, mem))
            if v0 is None: break
        if res[0][0] is None: skip += 1; continue
        if res[0][1] != res[1][1]:
            bad += 1
            if bad <= 5:
                d = next(i for i in range(RAM) if res[0][1][i] != res[1][1][i])
                print('DIFF trial %d args %s: first byte %X ref %02X cand %02X' % (t, [hex(a) for a in args], d, res[0][1][d], res[1][1][d]))
    print('%s: %d differences in %d trials (%d skipped)' % ('EQUIV' if bad == 0 else 'DIFFER', bad, n, skip))

if __name__ == '__main__':
    main()
