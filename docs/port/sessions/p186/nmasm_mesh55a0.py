#!/usr/bin/env python3
"""P186: compare the hand-asm func_150A55A0 (+ its loop func_150A563C / func_150A5654 .., 0x150A55A0-0x150A5858;
game_eu_D2DB0; mesh display-list cull copy) with its NON_MATCHING C, whole.

The asm copies DL words with ld/sd and keeps base in $gp, so difftest (32-bit Unicorn, tail call into
func_150A5654 stubbed) cannot run it. Reuses the VR4300 interpreter (Ref) and the Unicorn candidate runner (Cand)
of tools/port/difftest/nmasm_vis5858.py (imported, not changed).

Scenes: random vertex buffers (s16 x / y / z, 0x10 bytes each) at base + w1, a random view matrix, a random
D_800D3A00 (side-plane factor), random old flags in D_800D3A08, a random output byte before gdl, and a random DL:
G_VTX (1..32 vertices, sometimes twice in a row), G_TRI1 (indices below the loaded count, or any byte), 0xF3
(runs with and without triangles in between), other commands, ending with G_ENDDL (0xDF).
Compared: v0 and all of RDRAM except the stack page.

Run in the container from /conker/conker after both builds:
  python3 ../docs/port/sessions/p186/nmasm_mesh55a0.py [N] [seed] [mutant-elf]"""
import os, sys, random, struct
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '../../../../tools/port/difftest'))
from nmasm_vis5858 import Ref, Cand, RAM, SP0, phys

MTX, VTX, DL, OUT = 0x80310000, 0x80320000, 0x80340000, 0x80360000
FLAGS = 0x800D3A08
BASE = 0x7F000000   # arg5: DL w1 + base = the vertex address

def P(mem, a, fmt, *v):
    mem[phys(a):phys(a) + struct.calcsize('>' + fmt)] = struct.pack('>' + fmt, *v)

def scene(rng, mem, base):
    mem[:] = base
    mem[phys(MTX):phys(OUT) + 0x10000] = bytes(phys(OUT) + 0x10000 - phys(MTX))
    P(mem, FLAGS, '512B', *[rng.randrange(2) for _ in range(512)])
    P(mem, OUT - 8, 'II', rng.choice([0x01000000, 0xE7000000, 0x05000204, 0]), 0)
    P(mem, 0x800D3A00, 'f', rng.choice([rng.uniform(0.3, 2.0)] * 3 + [rng.uniform(-1.0, 0.3)]))
    m = [rng.uniform(-1.2, 1.2) for _ in range(16)]
    for k in (12, 13, 14): m[k] = rng.uniform(-800, 800)
    if rng.random() < 0.5:
        m = [rng.uniform(-0.2, 0.2) for _ in range(16)]; m[0] = m[5] = m[10] = m[15] = rng.choice([1.0, -1.0])
        m[12] = rng.uniform(-300, 300); m[14] = rng.uniform(-300, 300)
    edge = rng.random() < 0.2   # exact side-plane edge: |z'| == |x'| * 1.0 for some vertices
    if edge:
        m = [0.0] * 16; m[0] = m[5] = m[10] = m[15] = 1.0
        P(mem, 0x800D3A00, 'f', 1.0)
    P(mem, MTX, '16f', *m)
    # vertex pool
    nv = 64
    for i in range(nv):
        v = [rng.randrange(-1000, 1000) for _ in range(3)]
        if edge and rng.random() < 0.5: v[2] = rng.choice([v[0], -v[0]])
        P(mem, VTX + 0x10 * i, '3h', *v)
    dl = []
    loaded = 0
    for _ in range(rng.randrange(1, 60)):
        r = rng.random()
        if r < 0.2 or loaded == 0:
            n = rng.randrange(1, 33); s = rng.randrange(0, nv - n + 1)
            w0 = 0x01000000 | (n << 12) | ((n) << 1)
            dl.append((w0, VTX + 0x10 * s - BASE)); loaded = n
            if rng.random() < 0.15: dl.append((w0, VTX + 0x10 * s - BASE))
        elif r < 0.65:
            if rng.random() < 0.95: ix = [rng.randrange(loaded) for _ in range(3)]
            else: ix = [rng.randrange(128) for _ in range(3)]
            dl.append((0x05000000 | (ix[0] * 2) << 16 | (ix[1] * 2) << 8 | ix[2] * 2, rng.getrandbits(32)))
        elif r < 0.8:
            dl.append((0xF3000000 | rng.getrandbits(24), rng.getrandbits(32)))
        else:
            dl.append((rng.choice([0xE7, 0xFC, 0xFA, 0xD9, 0xDA, 0xDE, 0x06, 0x00, 0x02]) << 24 | rng.getrandbits(24), rng.getrandbits(32)))
    dl.append((0xDF000000, 0))
    for k, (a, b) in enumerate(dl): P(mem, DL + 8 * k, 'II', a, b)
    return [DL, OUT, MTX, rng.getrandbits(32), rng.getrandbits(32), BASE]

def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 300
    seed = int(sys.argv[2]) if len(sys.argv) > 2 else 1
    celf = sys.argv[3] if len(sys.argv) > 3 else 'build_nm/conker.eu.elf'
    ref = Ref('build/conker.eu.elf')
    cand = Cand(celf, 'build/conker.eu.elf')
    base = bytearray(RAM)
    for v, b in cand.data(): base[phys(v):phys(v) + len(b)] = b
    bad = 0; st = {'cmds': 0, 'kept_tris': 0, 'nops': 0}
    for t in range(n):
        res = []
        for who in ('ref', 'cand'):
            rng = random.Random(seed * 100003 + t)
            mem = bytearray(RAM)
            args = scene(rng, mem, base)
            v0 = ref.run(mem, args, entry='func_150A55A0') if who == 'ref' else cand.run(mem, args, entry='func_150A55A0')
            mem[phys(SP0) - 0x1000:phys(SP0) + 0x100] = bytes(0x1100)
            res.append((v0, mem))
        k = (res[0][0] - OUT) // 8
        st['cmds'] += k
        st['kept_tris'] += sum(1 for i in range(k) if res[0][1][phys(OUT) + 8 * i] == 5)
        st['nops'] += sum(1 for i in range(k) if res[0][1][phys(OUT) + 8 * i] == 0)
        if res[0][0] != res[1][0] or res[0][1] != res[1][1]:
            bad += 1
            if bad <= 5:
                d = next((i for i in range(RAM) if res[0][1][i] != res[1][1][i]), None)
                print('DIFF trial %d: v0 ref %08X cand %08X, first byte %s' % (t, res[0][0], res[1][0], d if d is None else hex(d)))
    print('%s: %d differences in %d trials, %s' % ('EQUIV' if bad == 0 else 'DIFFER', bad, n, st))

if __name__ == '__main__':
    main()
