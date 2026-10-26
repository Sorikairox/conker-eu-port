#!/usr/bin/env python3
"""P54: the floor candidate collectors (hand asm) vs their NON_MATCHING C:
  floor_collect_level_tris (level: all triangles or the BSP tree), floor_collect_world_obj_tris (world objects), floor_collect_record_tris (records),
  all three around the shared per-triangle test func_150A408C (C: floor_tri), and world_objects_in_box (object box list).
Reference: VR4300 interpreter (nmasm_vr.Ref) on build/conker.eu.elf; candidate: Unicorn on build_nm/conker.eu.elf.
Entry registers: $gp = 0 and $v1 = 0 (the asm uses the caller's $gp as the tag of the all-triangles path and $v1 as
the "previous index" of a leaf list starting with a delta; the C uses 0).
Synthetic mode: random triangles (vertex pool, offsets / bounds tables, bounds sometimes perturbed), random trees
(nested nodes, sibling chains, leaf lists mixing deltas and 15-bit indices, > 0x27 hits), objects, records.
Level mode (--level L): the level's area tables are built by nmasm_level's pipeline (asm collision_build_level_tris in Unicorn on
build/conker.eu.elf from the ROM), func_150A4ED4(area) selects them, then floor_collect_level_tris runs at points on / near
real triangles, with D_800DBE62 = 0 and 1. Compared: v0, s0-s7 / fp / sp, all RDRAM except the stack.
Run in the container from /conker/conker: python3 ../tools/port/difftest/nmasm_floorsets.py [N] [seed]
   [--only 3f50|48c0|5480|6a48] [--level 0x21 --rom ../baserom.eu.z64]"""
import sys, random, struct, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from nmasm_vr import *

D3720, DBE62, DBE4C, D39A4 = 0x800D3720, 0x800DC292, 0x800DC27C, 0x800D39A4
T26C, T270, T278 = 0x800DC26C, 0x800DC270, 0x800DC278
OBJS, NOBJ, D328 = 0x800DC324, 0x800DC320, 0x800DC328
RECS, D39FC, CNT5D38, OFS6490 = 0x800CC6F0, 0x800D39FC, 0x800C5D38, 0x800C6490
L3C00, L3C50 = 0x800D3C00, 0x800D3C50
VP, VOFS, BND, TREE, OBJA, BASES, IDS, OUTC = (0x80600000, 0x80610000, 0x80620000, 0x80630000, 0x80640000,
                                              0x80650000, 0x80658000, 0x80659000)
SREG = {16 + i: 0x1000 * (i + 1) + 0x11 for i in range(8)}
SREG.update({30: 0x9999, 28: 0, 3: 0})

def W(m, a, fmt, *v): b = struct.pack('>' + fmt, *v); m[phys(a):phys(a) + len(b)] = b
def R(m, a, fmt): return struct.unpack('>' + fmt, m[phys(a):phys(a) + struct.calcsize('>' + fmt)])

def tris(rng, m, nt, base, rel):
    """nt random triangles; vertex offsets relative to base (rel) or absolute; returns the vertex lists"""
    sc = rng.choice([8, 60, 600, 6000, 30000])
    cx, cz = rng.randint(-sc, sc), rng.randint(-sc, sc)
    pool = [rng.randint(-sc, sc) for _ in range(4)]
    def c(o): return max(-32760, min(32760, o + (rng.choice(pool) if rng.random() < 0.2 else rng.randint(-sc, sc))))
    out = []
    for t in range(nt):
        v = [[c(cx), c(0), c(cz)] for _ in range(3)]
        if rng.random() < 0.15: v[1][2] = v[0][2]
        if rng.random() < 0.1: v[2][0] = v[0][0]
        for k in range(3):
            a = VP + 0x18 * t + 8 * k
            W(m, a + (base - VP if rel else 0), '3h', *v[k])
            W(m, VOFS + 12 * t + 4 * k, 'I', ((a - VP) if rel else a) & M32)
        bx = [min(q[0] for q in v), min(q[2] for q in v), max(q[0] for q in v), max(q[2] for q in v)]
        if rng.random() < 0.15: bx[rng.randrange(4)] += rng.randint(-5, 5)
        W(m, BND + 8 * t, '4h', *[max(-32768, min(32767, q)) for q in bx])
        out.append(v)
    return out

def point(rng, vs):
    v = rng.choice(vs); k = rng.random()
    if k < 0.15: j = rng.randrange(3); return v[j][0], v[j][2]
    if k < 0.3:
        i, j = rng.sample(range(3), 2); u = rng.random()
        return int(v[i][0] + (v[j][0] - v[i][0]) * u), int(v[i][2] + (v[j][2] - v[i][2]) * u)
    w = [rng.random() for _ in range(3)]; s = sum(w)
    return (int(sum(v[i][0] * w[i] for i in range(3)) / s) + rng.randint(-3, 3),
            int(sum(v[i][2] * w[i] for i in range(3)) / s) + rng.randint(-3, 3))

def tree(rng, m, nt, x, z):
    """random BSP-like tree at TREE; nodes near (x, z) so that walks reach leaves"""
    cur = [TREE]
    def alloc(n):
        a = cur[0]; cur[0] += (n + 1) & ~1; return a
    def node(depth):
        leaf = depth >= 3 or rng.random() < 0.3
        lst = []
        if leaf:
            k = rng.randint(0, 50); i = 0
            for j in range(k):
                if j == 0 and rng.random() < 0.8 or rng.random() < 0.2:
                    i = rng.randrange(nt); lst += [0x80 | (i >> 8), i & 0xFF]
                else:
                    d = rng.randint(1, 3)
                    if i + d >= nt: i = rng.randrange(nt); lst += [0x80 | (i >> 8), i & 0xFF]
                    else: i += d; lst.append(d)
            lst.append(0)
        a = alloc(0xE + len(lst))
        r = rng.choice([0, 5, 50, 500, 5000, 40000])
        W(m, a, 'IhHhhh', 0, 0, r, max(-32768, min(32767, x + rng.randint(-r - 20, r + 20))),
          max(-32768, min(32767, z + rng.randint(-r - 20, r + 20))), 0)
        m[phys(a) + 0xE:phys(a) + 0xE + len(lst)] = bytes(lst)
        if not leaf:
            kids = [node(depth + 1) for _ in range(rng.randint(1, 3))]
            W(m, a + 0xC, 'h', kids[0] - a)
            for p, q in zip(kids, kids[1:]): W(m, p + 4, 'h', q - p)
        return a
    root = node(0)
    if rng.random() < 0.5:                                     # root siblings
        sib = node(1); W(m, root + 4, 'h', sib - root)
    W(m, T278, 'I', root)

def run(ref, cand, m, fn, args, stack=()):
    m1, m2 = bytearray(m), bytearray(m)
    r1 = ref.run(m1, a=args, stack=stack, entry=fn[0], regs=SREG, maxi=20000000)
    r2 = cand.run(m2, a=args, stack=stack, entry=fn[1], regs=SREG)
    k1 = (r1['v0'] & M32, [r1['gpr'][i] & M32 for i in list(range(16, 24)) + [29, 30]])
    k2 = (r2['v0'] & M32, [r2['gpr'][i] & M32 for i in list(range(16, 24)) + [29, 30]])
    d = memdiff(m1, m2, skip=[(SP0 - 0x400, SP0 + 0x100), (SCR, SCR + 0x100)])
    return k1 == k2 and not d, r1['v0'] & M32, (k1, k2, [hex(q) for q in d])

def synth(ref, cand, base, rng, n, only):
    bad = 0; hist = {}
    kinds = [only] if only else ['3f50', '3f50t', '48c0', '5480', '6a48']
    for t in range(n):
        kind = kinds[t % len(kinds)] if not only else ('3f50t' if only == '3f50' and t % 2 else only)
        m = bytearray(base)
        nt = rng.choice([1, 3, 20, 80])
        if kind in ('3f50', '3f50t'):
            vs = tris(rng, m, nt, 0, False)
            W(m, T26C, 'I', VOFS); W(m, T270, 'I', BND); W(m, DBE4C, 'i', nt)
            m[phys(DBE62)] = 0 if kind == '3f50' else rng.choice([1, 0x80, 0xFF])
            W(m, D39A4, 'I', 0x5A5A5A5A)
            j = rng.randrange(nt); x, z = point(rng, [vs[j]])
            if rng.random() < 0.3:                             # a bound exactly at the point +- 2 (+- 1 / 3)
                k = rng.randrange(4); d = rng.choice([1, 2, 2, 3])
                W(m, BND + 8 * j + 2 * k, 'h', max(-32768, min(32767, (x, z)[k & 1] + (d if k < 2 else -d))))
            if kind == '3f50t': tree(rng, m, nt, x, z)
            ok, v0, info = run(ref, cand, m, (0x150A3F50, 'floor_collect_level_tris'), (x, z))
        elif kind == '48c0':
            nobj = rng.randint(1, 5); per = []
            vs = tris(rng, m, nt, BASES + 0x1000, True)
            W(m, T26C, 'I', VOFS); W(m, T270, 'I', BND)
            W(m, OBJS, 'I', OBJA); W(m, D328, 'I', BASES)
            for o in range(nobj):
                f = rng.randrange(nt); c = rng.randint(0, nt - f)
                W(m, OBJA + 0xA0 * o + 0x56, 'HH', c, f)
                W(m, BASES + 4 * o, 'I', 0 if rng.random() < 0.15 else BASES + 0x1000)
            ids = [rng.randrange(nobj) for _ in range(rng.randint(0, 6))]
            for i, q in enumerate(ids): W(m, IDS + 2 * i, 'H', q)
            x, z = point(rng, vs)
            ok, v0, info = run(ref, cand, m, (0x150A48C0, 'floor_collect_world_obj_tris'), (x, z, len(ids), IDS))
        elif kind == '5480':
            vs = tris(rng, m, nt, BASES + 0x1000, True)
            for i in range(25):
                r = RECS + 0x32C * i
                on = rng.random() < 0.6
                W(m, r, 'I', rng.choice([0, 0x80123456]) if not on else 0x80123456)
                W(m, r + 0x58, 'I', rng.getrandbits(32))
                W(m, r + 0xF8, 'I', (0x4000 if (on or rng.random() < 0.5) else 0) | rng.getrandbits(14))
                W(m, r + 0x264, 'I', BASES + 0x1000 if (on or rng.random() < 0.5) else 0)
                W(m, r + 0x268, 'I', BND if (on or rng.random() < 0.5) else 0)
                md = rng.randrange(4); m[phys(r) + 4] = md
            for md in range(4):
                W(m, CNT5D38 + 2 * md, 'H', rng.randint(0, nt))
                W(m, OFS6490 + 4 * md, 'I', VOFS)
            m[phys(D39FC)] = rng.randint(0, 26)
            x, z = point(rng, vs)
            ok, v0, info = run(ref, cand, m, (0x150A5480, 'floor_collect_record_tris'), (x, z))
        else:
            nobj = rng.choice([0, 1, 5, 30])
            W(m, OBJS, 'I', OBJA); W(m, NOBJ, 'i', nobj)
            sc = rng.choice([10, 300, 5000])
            for o in range(nobj):
                a = OBJA + 0xA0 * o
                W(m, a + 0x10, '3h', *[rng.randint(-sc, sc) for _ in range(3)])
                W(m, a + 0x50, 'HH', rng.randint(0, sc), rng.randint(0, sc))
                m[phys(a) + 0x4F] = rng.choice([0, 0x20, 0x40, 0x60, 0x80, 0x1F])
                m[phys(a) + 0x6E] = 0 if rng.random() < 0.8 else rng.randint(1, 255)
            x, z = rng.randint(-sc, sc), rng.randint(-sc, sc)
            if rng.random() < 0.5: x2, z2 = x, z
            else: x2, z2 = x + rng.randint(0, sc), z + rng.randint(0, sc)
            y = rng.choice([-10000, rng.randint(-sc, sc)]); y2 = rng.randint(-sc, sc)
            W(m, OUTC, 'I', 0xDEADBEEF)
            ok, v0, info = run(ref, cand, m, (0x150A6A48, 'world_objects_in_box'), (x, z, OUTC, rng.choice([0, 1, 3, nobj])),
                               stack=(x2, z2, y, y2))
        key = '%s:%s' % (kind, 'hit' if v0 else 'none' if v0 == 0 else '')
        hist[key] = hist.get(key, 0) + 1
        if v0 >= 0x27 and kind != '6a48': hist['cap'] = hist.get('cap', 0) + 1
        if not ok:
            bad += 1
            if bad <= 6: print('DIFF', t, kind, info)
    return bad, hist

def level_mode(ref, cand, rng, n, levelno, rom):
    import nmasm_level as L
    romb = open(rom, 'rb').read()
    emu = L.Emu('build/conker.eu.elf', 'build/conker.eu.elf')
    base = bytearray(RAM)
    for v, b in emu.secs:
        if v >= 0x80000000: base[phys(v):phys(v) + len(b)] = b
    models = L.asset(romb, [4, levelno])
    mem = L.level_setup(rng, base, models, levelno, {})
    L.knobs(rng, mem, levelno, 0)
    emu.load(mem, {})
    emu.mu.mem_write(0x10000D24, struct.pack('>I', 0x12345678))
    emu.call('collision_build_level_tris', [levelno]); emu.call('collision_build_quadtrees', [])
    lv = emu.ram()
    print('level %#x built: %s' % (levelno, L.summary(lv)))
    bad = 0; hist = {}
    for area in (0, 1):
        m = bytearray(lv)
        ref.run(m, a=(area,), entry=0x150A4ED4, regs=SREG)
        nt = R(m, DBE4C, 'i')[0]; vofs, bnd = R(m, T26C, 'II')
        if nt <= 0: print('area', area, 'no triangles'); continue
        print('area %d: %d triangles, tree %08X' % (area, nt, R(m, T278, 'I')[0]))
        for t in range(n):
            ti = rng.randrange(nt)
            v = [list(R(m, R(m, vofs + 12 * ti + 4 * k, 'I')[0], '3h')) for k in range(3)]
            x, z = point(rng, [v]) if rng.random() < 0.9 else (rng.randint(-8000, 8000), rng.randint(-8000, 8000))
            m[phys(DBE62)] = t & 1
            ok, v0, info = run(ref, cand, m, (0x150A3F50, 'floor_collect_level_tris'), (x, z))
            key = 'area%d tree%d %s' % (area, t & 1, 'hit' if v0 else 'none')
            hist[key] = hist.get(key, 0) + 1
            if ok and v0 and t < 4:
                print('  (%d, %d): %d candidates' % (x, z, v0))
            if not ok:
                bad += 1
                if bad <= 6: print('DIFF level', area, t, x, z, info)
    return bad, hist

def main():
    a = sys.argv[1:]; opts = {}; pos = []
    while a:
        x = a.pop(0)
        if x.startswith('--'): opts[x[2:]] = a.pop(0)
        else: pos.append(x)
    n = int(pos[0]) if pos else 500
    rng = random.Random(int(pos[1]) if len(pos) > 1 else 1)
    ref, cand = Ref(), Cand()
    if 'level' in opts:
        bad, hist = level_mode(ref, cand, rng, n, int(opts['level'], 0), opts.get('rom', '../baserom.eu.z64'))
    else:
        bad, hist = synth(ref, cand, base_image(), rng, n, opts.get('only'))
    print('floorsets trials', n, 'diffs', bad, dict(sorted(hist.items())))

if __name__ == '__main__':
    main()
