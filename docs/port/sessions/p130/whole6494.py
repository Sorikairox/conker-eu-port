#!/usr/bin/env python3
"""P130: whole-function test of func_15186494 (shadow polygon clip + Vtx conversion, game_eu_1B1ED0) with its real
callees: the polygon clipper func_15186344 and the 10 plane test / intersection functions it calls through the
.data tables D_8008D838 / D_8008D860 (all compiled C in both builds). difftest cannot test it: its callee returns
pointers into its own stack buffers, and the two frames differ.

Reference: build/conker.eu.elf, candidate: build_nm/conker.eu.elf, both in Unicorn (the Cand runner of
nmasm_vis5858.py) with the matching build's .game_data; for the candidate the two function tables are rewritten
to the NM addresses of the same functions. Inputs: a projected triangle (3 x 20-byte shadow vertices: x, y, w,
source vertex pointer, outcode) around the view (inside, crossing 1..4 side planes, the near / far depth, w = 0
avoided), the near / far depths and alpha, split 0 / 1. Compared: v0 and all RDRAM except the stack page.

Run in the container from /conker/conker after both builds: python3 ../docs/port/sessions/p130/whole6494.py [N] [seed]"""
import os, sys, random, struct
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '../../../../tools/port/difftest'))
import nmasm_vis5858 as V
from nmasm_vis5858 import Cand, RAM, SP0, phys, P, syms
_section = V.section
V.section = lambda elf, name: _section(elf, name) or (0x15000000, b'')   # the matching ELF has no .nm_rodata

IN, VTX, OUT, CNT = 0x80300000, 0x80301000, 0x80310000, 0x80320000
fr = lambda rng, lo, hi: struct.unpack('>f', struct.pack('>f', rng.uniform(lo, hi)))[0]

def case(rng, mem, addrs):
    far = rng.choice([fr(rng, -20000, -2000), -5000.0]); near = rng.choice([fr(rng, -50, -1), -10.0])
    alpha = rng.choice([185.0, fr(rng, 0, 255), 0.0, 255.0])
    for a in addrs['D_800D3AA8']: P(mem, a, 'f', far)
    for a in addrs['D_800D3AAC']: P(mem, a, 'f', near)
    for a in addrs['D_800DE45C']: P(mem, a, 'f', alpha)
    n = 3
    spread = rng.choice([0.5, 1.0, 1.5, 3.0])
    for i in range(n):
        q = rng.random()
        if q < 0.1: w = fr(rng, near * 0.5, -0.5)               # in front of the near depth
        elif q < 0.2: w = fr(rng, far * 1.5, far)                # beyond the far depth
        else: w = fr(rng, far, near)
        x, y = fr(rng, -spread, spread) * -w, fr(rng, -spread, spread) * -w
        if rng.random() < 0.05: x = 0.0
        if rng.random() < 0.05: y = 0.0
        P(mem, VTX + 8 * i, '3h', *[rng.randrange(-0x8000, 0x8000) for _ in range(3)])
        P(mem, IN + 20 * i, '3fII', x, y, w, VTX + 8 * i, rng.getrandbits(32))
    for k in range(5): P(mem, CNT + 4 * k, 'I', 0xDEAD0000 + k)
    return [IN, n, 0x1A, OUT, CNT, rng.choice([0, 1, 1])]

def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 1000
    seed = int(sys.argv[2]) if len(sys.argv) > 2 else 1
    R, C = 'build/conker.eu.elf', os.environ.get('NM_ELF', 'build_nm/conker.eu.elf')
    ref, cand = Cand(R, R), Cand(C, R)
    sr, sc = syms(R), syms(C)
    addrs = {k: sorted({sr[k], sc[k]}) for k in ('D_800D3AA8', 'D_800D3AAC', 'D_800DE45C')}
    base = bytearray(RAM)
    for v, bb in ref.data(): base[phys(v):phys(v) + len(bb)] = bb
    byaddr = {v: k for k, v in sr.items() if k.startswith('func_')}
    patch = []
    for tab in ('D_8008D838', 'D_8008D860'):
        for i in range(10):
            a = sr[tab] + 4 * i
            f = struct.unpack('>I', base[phys(a):phys(a) + 4])[0]
            patch.append((a, sc[byaddr[f]], byaddr[f]))
    print('tables:', ' '.join(nm for _, _, nm in patch))
    bad = 0; st = {}
    for t in range(n):
        res = []
        for who, runner in (('ref', ref), ('cand', cand)):
            rng = random.Random(seed * 100003 + t)
            mem = bytearray(base)
            args = case(rng, mem, addrs)
            if who == 'cand':
                for a, v, _ in patch: P(mem, a, 'I', v)
            v0 = runner.run(mem, args, entry='func_15186494')
            if who == 'cand':
                for a, v, _ in patch: mem[phys(a):phys(a) + 4] = base[phys(a):phys(a) + 4]
            mem[phys(SP0) - 0x1000:phys(SP0) + 0x100] = bytes(0x1100)
            res.append((v0, mem))
        st[res[0][0]] = st.get(res[0][0], 0) + 1
        if res[0][0] != res[1][0] or res[0][1] != res[1][1]:
            bad += 1
            if bad <= 5:
                d = next((i for i in range(RAM) if res[0][1][i] != res[1][1][i]), None)
                print('DIFF trial %d: v0 ref %08X cand %08X, first byte %s' % (t, res[0][0], res[1][0], d if d is None else hex(d)))
    print('%s func_15186494: %d differences in %d trials, vertex counts %s' % ('EQUIV' if bad == 0 else 'DIFFER', bad, n, dict(sorted(st.items()))))

if __name__ == '__main__':
    main()
