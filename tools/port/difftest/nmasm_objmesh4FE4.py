#!/usr/bin/env python3
"""P190: compare the hand-asm obj_floor_mesh_update (+ its exit / release labels func_150A53D4 / func_150A543C, 0x150A4FE4 -
0x150A5480; game_eu_D1760; object floor mesh build) with its NON_MATCHING C, whole.

The asm saves $gp and every FPR and keeps values in odd FPRs (f1 / f3 / f13 / f31 as a GPR spill), so it runs in
the VR4300 interpreter (Ref) of nmasm_vis5858.py; the candidate (build_nm/conker.eu.elf) runs in Unicorn (Cand).
allocate_memory and heap_free (free) are replaced in both images by the same small MIPS stub: allocations come
from a bump pointer (STATE + 0), bit k of STATE + 4 makes the k-th allocation fail, and every call logs its
arguments at STATE + 8 (pointer into LOG), so the logs are part of the compared RDRAM.

Scenes: the 25 records D_800CC2D0 (EU 800CC6F0, 0x32C each; live / not, x / z, the radius +0x270 incl. exact
boundary distances), the record under test (+0 / +0x1D4 / +0xF8 & 0x4000 gates, model byte, buffers +0x264 /
+0x268 / +0x26C present or not), model tables D_800C5C08 (EU 800C6028, group list or NULL), D_800C6318 (group
count), D_800C5BC0 (vertex count), D_800C5D38 (triangle count), D_800C6070 (EU 800C6490, triangle vertex offsets),
4 random matrices (sometimes identity + .5 translations: cvt.w.s ties to even), groups with counts 0..8.
Compared: all of RDRAM except the stack page (v0 not: the function is void).

Run in the container from /conker/conker after both builds:
  python3 ../tools/port/difftest/nmasm_objmesh4FE4.py [N] [seed] [mutant-elf]"""
import os, sys, random, struct
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from nmasm_vis5858 import Ref, Cand, RAM, SP0, phys

STATE, LOG = 0x80700000, 0x80700100
ALLOC = 0x80400000
RECS, NREC, RSZ = 0x800CC6F0, 25, 0x32C
T_GROUPS, T_NGROUP, T_NVERT, T_NTRI, T_TRIS = 0x800C6028, 0x800C6318, 0x800C5BC0, 0x800C5D38, 0x800C6490
MTX, GRP, SRC, TRI, OLD = 0x80300000, 0x80310000, 0x80320000, 0x80340000, 0x80360000

STUB_ALLOC = [0x3C088070, 0x8D0B0008, 0xAD640000, 0xAD650004, 0xAD660008, 0xAD67000C, 0x256B0010, 0xAD0B0008,
              0x8D090004, 0x00095042, 0xAD0A0004, 0x31290001, 0x15200004, 0x8D020000, 0x00445021, 0x03E00008,
              0xAD0A0000, 0x03E00008, 0x00001025]
STUB_FREE = [0x3C088070, 0x8D0B0008, 0xAD640000, 0x256B0004, 0x03E00008, 0xAD0B0008]

class RefS(Ref):
    def __init__(self, elf):
        Ref.__init__(self, elf)
        self.st = {}
        for name, code in (('allocate_memory', STUB_ALLOC), ('heap_free', STUB_FREE)):
            for k, w in enumerate(code): self.st[self.s[name] + 4 * k] = w
    def word(self, pc):
        if pc in self.st: return self.st[pc]
        return Ref.word(self, pc)

def cand_stubs(cand):
    for name, code in (('allocate_memory', STUB_ALLOC), ('heap_free', STUB_FREE)):
        cand.mu.mem_write(cand.s[name], b''.join(struct.pack('>I', w) for w in code))

def P(mem, a, fmt, *v):
    mem[phys(a):phys(a) + struct.calcsize('>' + fmt)] = struct.pack('>' + fmt, *v)

def scene(rng, mem, base, st):
    mem[:] = base
    for a, n in ((MTX, 0x80000), (ALLOC, 0x40000)):
        mem[phys(a):phys(a) + n] = bytes(rng.getrandbits(8) for _ in range(0x100)) * (n // 0x100)
    me = rng.randrange(NREC)
    obj = RECS + RSZ * me
    m = rng.randrange(187)
    # records
    near = rng.random() < 0.8
    r = rng.choice([rng.uniform(0, 400), 5.0, 0.0, 100.0])
    ox, oz = rng.uniform(-500, 500), rng.uniform(-500, 500)
    for i in range(NREC):
        a = RECS + RSZ * i
        P(mem, a, 'I', rng.choice([0, 0, 1, 0x80401234]))
        P(mem, a + 0x14, 'fff', rng.uniform(-3000, 3000), rng.uniform(-50, 50), rng.uniform(-3000, 3000))
    if near:
        o = rng.choice([k for k in range(NREC) if k != me])
        a = RECS + RSZ * o
        P(mem, a, 'I', 1)
        if rng.random() < 0.4 and r == 5.0:   # exact boundary 3 / 4 / 5 (and just outside)
            ox, oz = 100.0, 200.0
            P(mem, a + 0x14, 'f', 100.0 + rng.choice([3.0, -3.0])); P(mem, a + 0x1C, 'f', 200.0 + rng.choice([4.0, 4.0001, -4.0]))
            st['edge'] += 1
        else:
            P(mem, a + 0x14, 'f', ox + rng.uniform(-r, r) * 0.7); P(mem, a + 0x1C, 'f', oz + rng.uniform(-r, r) * 0.7)
    P(mem, obj, 'I', rng.choice([1] * 12 + [0]))
    P(mem, obj + 4, 'B', m)
    P(mem, obj + 0x14, 'fff', ox, rng.uniform(-50, 50), oz)
    P(mem, obj + 0xF8, 'I', rng.getrandbits(32) | 0x4000 if rng.random() < 0.92 else rng.getrandbits(32) & ~0x4000)
    P(mem, obj + 0x1D4, 'I', MTX if rng.random() < 0.92 else 0)
    P(mem, obj + 0x270, 'f', r)
    # matrices
    tie = rng.random() < 0.25
    for k in range(4):
        if tie:
            mt = [1.0, 0, 0, 0, 0, 1.0, 0, 0, 0, 0, 1.0, 0] + [rng.randrange(-20, 20) + 0.5 for _ in range(3)] + [1.0]
        else:
            mt = [rng.uniform(-1.5, 1.5) for _ in range(12)] + [rng.uniform(-1000, 1000) for _ in range(3)] + [1.0]
        P(mem, MTX + 0x40 * k, '16f', *mt)
    # groups and source vertices
    ng = rng.randrange(1, 5)
    counts = [rng.choice([0, 1, 2, 3, 5, 8]) for _ in range(ng)]
    nv = sum(counts)
    s = SRC
    for g in range(ng):
        P(mem, GRP + 12 * g, 'III', s, counts[g], rng.randrange(4))
        for v in range(counts[g]):
            P(mem, s + 16 * v, '3h', *[rng.randrange(-1000, 1000) for _ in range(3)])
        s += 16 * counts[g] + 16 * rng.randrange(2)
    nvalloc = max(nv, 1) + rng.randrange(3)
    ntri = rng.randrange(1, 30)
    for t in range(ntri * 3):
        P(mem, TRI + 4 * t, 'I', 16 * rng.randrange(max(nv, 1)))
    P(mem, T_GROUPS + 4 * m, 'I', GRP if rng.random() < 0.93 else 0)
    P(mem, T_NGROUP + 2 * m, 'H', ng)
    P(mem, T_NVERT + 2 * m, 'H', nvalloc)
    P(mem, T_NTRI + 2 * m, 'H', ntri)
    P(mem, T_TRIS + 4 * m, 'I', TRI)
    # existing buffers (big enough)
    for k, off in enumerate((0x264, 0x268, 0x26C)):
        P(mem, obj + off, 'I', OLD + 0x4000 * k if rng.random() < 0.35 else 0)
    # allocator state
    fail = 0
    for k in range(3):
        if rng.random() < 0.08: fail |= 1 << k
    P(mem, STATE, 'III', ALLOC, fail, LOG)
    st['nv'] += nv; st['ntri'] += ntri; st['fail'] += fail != 0
    return [obj]

def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 400
    seed = int(sys.argv[2]) if len(sys.argv) > 2 else 1
    celf = sys.argv[3] if len(sys.argv) > 3 else 'build_nm/conker.eu.elf'
    ref = RefS('build/conker.eu.elf')
    cand = Cand(celf, 'build/conker.eu.elf')
    cand_stubs(cand)
    base = bytearray(RAM)
    for v, b in cand.data(): base[phys(v):phys(v) + len(b)] = b
    bad = 0; st = {'nv': 0, 'ntri': 0, 'fail': 0, 'edge': 0, 'built': 0, 'freed': 0}
    for t in range(n):
        res = []
        for who in ('ref', 'cand'):
            rng = random.Random(seed * 100003 + t)
            mem = bytearray(RAM)
            args = scene(rng, mem, base, st if who == 'ref' else {k: 0 for k in st})
            if who == 'ref': ref.run(mem, args, entry='obj_floor_mesh_update')
            else: cand.run(mem, args, entry='obj_floor_mesh_update')
            mem[phys(SP0) - 0x1000:phys(SP0) + 0x100] = bytes(0x1100)
            res.append(mem)
        o = phys(args[0])
        if struct.unpack('>I', res[0][o + 0x26C:o + 0x270])[0]: st['built'] += 1
        else: st['freed'] += 1
        if res[0] != res[1]:
            bad += 1
            if bad <= 5:
                d = next((i for i in range(RAM) if res[0][i] != res[1][i]), None)
                print('DIFF trial %d: first byte %s' % (t, d if d is None else hex(d | 0x80000000)))
    print('%s: %d differences in %d trials, %s' % ('EQUIV' if bad == 0 else 'DIFFER', bad, n, st))

if __name__ == '__main__':
    main()
