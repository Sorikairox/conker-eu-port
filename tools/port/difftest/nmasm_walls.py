#!/usr/bin/env python3
"""P56: the hand-asm wall engine (func_150AB6D0 / func_150AC8C4 -> func_150AB708) and the ray cast func_150ACEA0
vs their NON_MATCHING C (src_eu/nm_asm/D5E90.c + D5E90_walls.inc (asm2c_hand.py); the ray cast is readable C since P291).
Reference: VR4300 interpreter (nmasm_vr.Ref) on build/conker.eu.elf; candidate: Unicorn on build_nm/conker.eu.elf.
Callees (func_1507C7C0, func_150492CC, sinf / cosf, func_150A69A8, func_150A49D0, func_1510F800) run on both sides.
Synthetic mode: random triangles around a record (walls = vertical quads' halves, slopes, floors, degenerate ones),
bounds tables (sometimes perturbed), flags D_800DBE5C, a BSP tree (one leaf or nmasm_floorsets' random trees),
area kind 0 / 1 (level) and 3 (records' own models), record kinds 0 / 4 / 0x2C (func_1507C7C0's sizes), moves of
0..200 units, mark flag. Level mode (--level L): level built by nmasm_level's pipeline, func_150A4ED4(area), the
record placed next to real triangles of areas 0 / 1.
Compared: v0 and all RDRAM except the stacks.
Run in the container from /conker/conker: python3 ../tools/port/difftest/nmasm_walls.py [N] [seed]
   [--only ab6d0|ac8c4|ray] [--level 0x21 --rom ../baserom.eu.z64] [--unit all|aa950,aa9b0,..] (P285: one private
   helper called directly, see unit())"""
import sys, random, struct, os, math
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from nmasm_vr import *
import nmasm_floorsets as FS
W, R = FS.W, FS.R

SY = syms('build/conker.eu.elf')     # EU symbol names are not their addresses (D_800DBE5C is at 0x800DC28C)
T26C, T270, T274, T278, DBE5C, DC280 = [SY[n] for n in ('D_800DC26C', 'D_800DC270', 'D_800DC274', 'D_800DC278',
                                                         'D_800DBE5C', 'D_800DC280')]
DBE08, DC320 = SY['D_800DBE08'], SY['D_800DC320']
VP, VOFS, BND, YB, FLG = 0x80600000, 0x80610000, 0x80620000, 0x80628000, 0x8062C000
OUTS = 0x80660000
SREG = {16 + i: 0x1000 * (i + 1) + 0x11 for i in range(8)}
SREG.update({30: 0x9999, 28: 0x7777})

STUBS = [None, None]

def run(ref, cand, m, fn, args, fa=None, stack=()):
    m1, m2 = bytearray(m), bytearray(m)
    r1 = ref.run(m1, a=args, fa=fa, stack=stack, entry=fn[0], regs=SREG, maxi=40000000, stubs=STUBS[0])
    r2 = cand.run(m2, a=args, fa=fa, stack=stack, entry=fn[1], regs=SREG, stubs=STUBS[1])
    k1 = (r1['v0'] & M32, [r1['gpr'][i] & M32 for i in list(range(16, 24)) + [28, 29, 30]])
    k2 = (r2['v0'] & M32, [r2['gpr'][i] & M32 for i in list(range(16, 24)) + [28, 29, 30]])
    d = memdiff(m1, m2, skip=[(SP0 - 0x4000, SP0 + 0x100), (SCR, SCR + 0x100), (0x80700000, 0x80710004)])
    if d and os.environ.get('NMW_DEBUG'):   # P288: the differing words, ref / cand (hex and float)
        for a in sorted(set(q & ~3 for q in d))[:8]:
            w1, w2 = R(m1, a, 'I')[0], R(m2, a, 'I')[0]
            print('  word %08x ref %08x %r cand %08x %r' % (a, w1, f32(w1), w2, f32(w2)))
    return k1 == k2 and not d, r1['v0'] & M32, (k1, k2, [hex(q) for q in d]), m1

def walltris(rng, m, nt, c, rel_base=None, first=0):
    """nt triangles around c = (x, y, z); offsets table VOFS (absolute, or relative to rel_base), bounds BND / YB;
    P291: `first` = index of the first one (object triangles follow the level's)"""
    sc = rng.choice([40, 120, 300, 900])
    out = []
    for t in range(first, first + nt):
        k = rng.random()
        o = lambda: rng.randint(-sc, sc)
        if k < 0.5:                                            # wall: vertical
            x0, z0, x1, z1 = c[0] + o(), c[2] + o(), c[0] + o(), c[2] + o()
            y0, y1 = c[1] + rng.randint(-sc, 0), c[1] + rng.randint(0, 2 * sc)
            v = rng.choice([[[x0, y0, z0], [x1, y0, z1], [x0, y1, z0]], [[x1, y1, z1], [x0, y1, z0], [x1, y0, z1]],
                            [[x0, y0, z0], [x0, y1, z0], [x1, y0, z1]]])
        elif k < 0.75:                                         # floor / ceiling-ish, often a step near c
            yy = c[1] + (rng.randint(-sc // 2, sc // 2) if rng.random() < 0.5 else rng.randint(-70, 70))
            v = [[c[0] + o(), yy + rng.randint(-5, 5), c[2] + o()] for _ in range(3)]
        elif k < 0.95:
            v = [[c[0] + o(), c[1] + o(), c[2] + o()] for _ in range(3)]
        else:                                                  # degenerate
            p = [c[0] + o(), c[1] + o(), c[2] + o()]
            v = [list(p), list(p), [p[0] + rng.randint(-2, 2), p[1], p[2]]]
        v = [[max(-32760, min(32760, q)) for q in p] for p in v]
        for kk in range(3):
            a = VP + 0x18 * t + 8 * kk
            W(m, a, '3h', *v[kk])
            W(m, VOFS + 12 * t + 4 * kk, 'I', (a - rel_base) & M32 if rel_base is not None else a)
        bx = [min(q[0] for q in v), min(q[2] for q in v), max(q[0] for q in v), max(q[2] for q in v)]
        by = [min(q[1] for q in v), max(q[1] for q in v)]
        if rng.random() < 0.1: bx[rng.randrange(4)] += rng.randint(-8, 8)
        W(m, BND + 8 * t, '4h', *[max(-32768, min(32767, q)) for q in bx])
        W(m, YB + 4 * t, '2h', *by)
        fl = rng.choice([0, 0, 0x1000000, 0x0E000000, 0x0E000000, 0x0F000000, 0x02000000, rng.getrandbits(32)])
        W(m, FLG + 4 * t, 'I', fl)
        out.append(v)
    return out

def onetree(rng, m, nt, x, z):
    if rng.random() < 0.5:
        FS.TREE  # random trees from P54
        FS.tree(rng, m, nt, x, z)
        return
    a = FS.TREE; lst = []
    for i in range(nt): lst += [0x80 | (i >> 8), i & 0xFF]
    lst.append(0)
    W(m, a, 'IhHhhh', 0, 0, 40000, x, z, 0)
    m[phys(a) + 0xE:phys(a) + 0xE + len(lst)] = bytes(lst)
    W(m, T278, 'I', a)

def setup_rec(rng, m, recs, pos):
    i = rng.randrange(25); rec = recs + 0x32C * i
    W(m, rec, 'I', rng.choice([0, 0, 4, 0x2C]))
    W(m, rec + 0xE4, '2h', rng.randint(5, 40), rng.randint(5, 40))
    W(m, rec + 0x14, '3f', *[float(q) + rng.choice([0, 0.5, 0.25]) for q in pos])
    W(m, rec + 0x20, 'i', rng.choice([0, 0, -3, 5, 1]))
    W(m, rec + 0x28, 'I', rng.choice([0, 1, 0x80000000]))
    W(m, rec + 0x40, 'f', rng.uniform(-360, 360))
    m[phys(rec) + 0x275] = 0xEE
    return rec, i

def wall_call(ref, cand, m, rng, rec, pos, which):
    mv = rng.choice([0, 5, 30, 80, 200])
    tgt = [pos[0] + rng.uniform(-mv, mv), pos[1] + rng.uniform(-mv / 4, mv / 4), pos[2] + rng.uniform(-mv, mv)]
    fa = {12: b32(tgt[0]), 14: b32(tgt[1])}
    fn = (0x150AB6D0, 'func_150AB6D0') if which == 'ab6d0' else (0x150AC8C4, 'func_150AC8C4')
    return run(ref, cand, m, fn, (0, 0, b32(tgt[2]), rec), fa=fa, stack=(rng.choice([0, 1]),))

RAY_PCS = {0x150ADAF8: 'yz', 0x150ADB48: 'zx', 0x150ADB88: 'xy', 0x150ADC10: 'hit',   # func_150AD844 projections
           0x150AD510: 'obj listed', 0x150AD68C: 'obj hit', 0x150AD32C: 'next leaf'}    # func_150ACEA0 (P291)
OBJS, OBJVB, OBJFT = 0x80670000, 0x80674000, 0x80676000

def ray_grid_tree(rng, m, vs, pos):
    """P291: a root square split into g x g leaves (half size h), each listing the level triangles whose xz bounds
    meet the cell (absolute / relative entries; sometimes a relative first entry, which counts from the asm's t3):
    rays then hit in later leaves, so the next-leaf walk (exit point, side flags, maxDist) decides the result."""
    g = rng.choice([2, 3, 4, 6]); h = rng.choice([60, 150, 300, 600])
    cx0, cz0 = pos[0] + rng.randint(-h, h), pos[2] + rng.randint(-h, h)
    buf = bytearray(struct.pack('>IhHhhh', 0, 0, g * h + rng.choice([0, 0, 5]), cx0, cz0, 14))
    leaves = []
    for i in range(g):
        for j in range(g):
            cx = cx0 - g * h + h + 2 * h * i; cz = cz0 - g * h + h + 2 * h * j
            ids = [t for t, v in enumerate(vs) if min(q[0] for q in v) <= cx + h and max(q[0] for q in v) >= cx - h
                   and min(q[2] for q in v) <= cz + h and max(q[2] for q in v) >= cz - h]
            lst = bytearray(); prev = None
            for t in ids:
                if prev is None and t >= 2 and t < 0x80 and rng.random() < 0.2: lst.append(t - rng.choice([0, 1]) or 1)
                elif prev is not None and 0 < t - prev < 0x80 and rng.random() < 0.6: lst.append(t - prev)
                else: lst += bytes([0x80 | (t >> 8), t & 0xFF])
                prev = t
            lst.append(0)
            if len(lst) & 1: lst.append(0)
            leaves.append((cx, cz, lst))
    for k, (cx, cz, lst) in enumerate(leaves):
        nxt = 0 if k == len(leaves) - 1 else 14 + len(lst)
        buf += struct.pack('>IhHhhh', 0, nxt, h, cx, cz, 0) + lst
    a = FS.TREE
    m[phys(a):phys(a) + len(buf)] = bytes(buf)
    W(m, T278, 'I', a)

def ray_objects(rng, m, nt, pos):
    """P291: collidable objects for the ray cast (D_800DBEF4 records of 0xA0 bytes, D_800DC320 count, D_800DC328
    vertex bases): centre near pos, radii, triangles nt.. (offsets relative to the object's vertex base), flags
    +0x40 or a per-triangle table +0x44, some switched off (+0x6E) or not collidable (+0x4F & 0x60 == 0x20).
    Returns the object triangles (absolute vertices)."""
    nobj = rng.choice([0, 1, 2, 3, 6, 10])
    out = []; first = nt
    for i in range(nobj):
        o = OBJS + 0xA0 * i
        for k in range(0, 0xA0, 4): W(m, o + k, 'I', rng.getrandbits(32))
        c = [pos[0] + rng.randint(-250, 250), pos[1] + rng.randint(-80, 160), pos[2] + rng.randint(-250, 250)]
        ntr = rng.choice([1, 2, 4, 8])
        vb = rng.choice([VP - 0x1000, VP + 0x18 * first, 0x80000000])   # != 0: func_150A49D0 keeps it (no transform)
        out += walltris(rng, m, ntr, c, rel_base=vb, first=first)
        W(m, OBJVB + 4 * i, 'I', vb)
        W(m, o + 0x10, '3h', *c)
        r1, r2 = rng.choice([(40, 30), (10, 300), (200, 200), (5, 5), (rng.randint(0, 600), rng.randint(0, 600))])
        W(m, o + 0x50, '2H', r1, r2)
        W(m, o + 0x56, '2H', ntr, first)
        m[phys(o) + 0x6E] = rng.choice([0, 0, 0, 0, 1])
        m[phys(o) + 0x4F] = rng.choice([0, 0x40, 0x60, 0x20, rng.getrandbits(8)])
        ft = 0 if rng.random() < 0.5 else OBJFT + 0x40 * i
        W(m, o + 0x44, 'I', ft)
        for k in range(ntr): W(m, OBJFT + 0x40 * i + 4 * k, 'I', rng.getrandbits(32))
        first += ntr
    W(m, SY['D_800DBEF4'], 'I', OBJS); W(m, SY['D_800DC328'], 'I', OBJVB); W(m, SY['D_800DC32C'], 'I', OBJFT + 0x1000)
    return nobj, out

def ray_aim(rng, p0, vs):
    """P291: a direction from p0 at a point of one of the triangles vs: a vertex, an edge point (midpoint, thirds,
    random), the inside, just outside an edge, or along an edge (parallel to the plane); scaled so the hit is inside
    the segment, beyond it or behind the origin. Exact-edge hits make the projections' rounding differ."""
    v = rng.choice(vs); k = rng.random()
    if k < 0.15: q = list(v[rng.randrange(3)])
    elif k < 0.55:
        i = rng.randrange(3); a, b = v[i], v[(i + 1) % 3]
        u = rng.choice([0.5, 1 / 3.0, 0.25, rng.random()])
        q = [a[j] + u * (b[j] - a[j]) for j in range(3)]
        if rng.random() < 0.3:   # just outside / inside the edge
            c = [(v[0][j] + v[1][j] + v[2][j]) / 3.0 for j in range(3)]; e = rng.choice([-1e-3, 1e-3, -0.05, 0.05])
            q = [q[j] + e * (q[j] - c[j]) for j in range(3)]
    elif k < 0.85:
        w = [rng.random() for _ in range(3)]; sw = sum(w) or 1.0
        q = [sum(w[i] * v[i][j] for i in range(3)) / sw for j in range(3)]
    else:   # along an edge: parallel to the plane (denominator 0 for exact walls / floors)
        i = rng.randrange(3); a, b = v[i], v[(i + 1) % 3]
        return [float(b[j] - a[j]) * rng.choice([1.0, 0.5, 3.0]) for j in range(3)]
    sc = rng.choice([1.0, 1.0, 1.25, 4.0, 0.5, -1.0])
    return [(q[j] - p0[j]) * sc for j in range(3)]

def ray_call(ref, cand, m, rng, pos, vs=None):
    p0 = [pos[0] + rng.uniform(-50, 50), pos[1] + rng.uniform(-50, 150), pos[2] + rng.uniform(-50, 50)]
    if rng.random() < 0.3:
        p0 = [float(round(q)) for q in p0]   # integer origins: exact hits on integer vertices / edges
    if vs and rng.random() < 0.75: d = ray_aim(rng, p0, vs)
    else: d = [rng.choice([0.0, rng.uniform(-400, 400)]) for _ in range(3)]
    if rng.random() < 0.05: d = [0.0, 0.0, 0.0]
    for k in range(0x14): W(m, OUTS + 4 * k, 'I', 0xDEAD0000 + k)
    stack = (b32(d[1]), b32(d[2]), rng.choice([0, OUTS + 0x20]), rng.choice([0, OUTS + 0x40]),
             rng.choice([0, OUTS]), rng.choice([0, OUTS + 4]), rng.choice([0, OUTS + 8]),
             rng.choice([0, OUTS + 12]), rng.choice([0, OUTS + 16]),
             rng.choice([0, OUTS + 0x24]) if R(m, DBE5C, 'I')[0] else 0,   # flags out: needs D_800DBE5C
             b32(rng.choice([0.0, 0.0, 50.0, 300.0])))
    fa = {12: b32(p0[0]), 14: b32(p0[1])}
    return run(ref, cand, m, (0x150ACEA0, 'func_150ACEA0'), (0, 0, b32(p0[2]), b32(d[0])), fa=fa, stack=stack)

# P294: engine paths counted per trial (executed reference PCs), walls / ledges
WALL_PCS = {0x150ABC28: 'rec next', 0x150ABD34: 'obj next', 0x150ABE58: 'visited add', 0x150ABF28: 'obj mark',
            0x150ABF84: 'rec mark', 0x150AC0CC: 'clamp test', 0x150AC104: 'clamp', 0x150AC3CC: 'edge push test',
            0x150AC508: 'edge best', 0x150AC5D8: 'face push test', 0x150AC63C: 'keepfall clear', 0x150AC698: 'pushed',
            0x150AC960: 'ledge tri', 0x150ACC38: 'ledge edge', 0x150ACE20: 'ledge -', 0x150ACE38: 'ledge +'}
OBJMARK, VOFS2 = 0x80677000, 0x80618000

def rec_models(rng, m, recs, nt):
    """P294: area kind 3: some of the 25 records (D_800CC2D0, 0x32C bytes) get the level triangles as their model:
    word 0 != 0, +0xF8 & 0x4000, kind byte +4 -> D_800C6070[kind] = offsets (relative to the vertex base +0x264),
    D_800C5D38[kind] = count; xz / y bounds tables +0x268 / +0x26C. Some records are off (no flag / no base)."""
    vb = rng.choice([VP - 0x2000, VP])
    for t in range(nt):
        for kk in range(3): W(m, VOFS2 + 12 * t + 4 * kk, 'I', (R(m, VOFS + 12 * t + 4 * kk, 'I')[0] - vb) & M32)
    k = rng.randrange(187)
    W(m, SY['D_800C6070'] + 4 * k, 'I', VOFS2); W(m, SY['D_800C5D38'] + 2 * k, 'H', nt)
    for i in range(25):
        r = recs + 0x32C * i
        W(m, r, 'I', rng.choice([0, 1, 1, 1, 0x2C]))
        m[phys(r) + 4] = k
        W(m, r + 0xF8, 'I', rng.choice([0x4000, 0x4000, 0x4000, 0, 0xFFFFBFFF]))
        W(m, r + 0x264, '3I', rng.choice([vb, vb, vb, 0]), BND, YB)

def common_globals(rng, m):
    for a in ('D_800CC1F2', 'D_800CC1F3', 'D_800CC1F4'):
        m[phys(SY[a])] = rng.choice([0, 0, 1])
    W(m, SY['D_800CC1F8'], 'f', rng.choice([0.0, 20.0, 60.0, 140.0, 200.0]))
    W(m, SY['D_800CC1FC'], 'f', rng.choice([0.0, 10.0, 40.0]))

def synth(ref, cand, base, rng, n, only):
    bad = 0; hist = {}
    recs = ref.s['D_800CC2D0']
    kinds = [only] if only else ['ab6d0', 'ac8c4', 'ray']
    for t in range(n):
        kind = kinds[t % len(kinds)]
        m = bytearray(base)
        nt = rng.choice([1, 4, 20, 60, 130])
        pos = [rng.randint(-3000, 3000), rng.randint(-500, 500), rng.randint(-3000, 3000)]
        vs = walltris(rng, m, nt, pos)
        if kind == 'ac8c4':                                    # ledges 63..66 units up (the step window)
            for t2 in rng.sample(range(nt), max(1, nt // 3)):
                yy = pos[1] + rng.choice([62, 63, 64, 65, 66, 67]); r = rng.choice([30, 100, 300])
                v = [[pos[0] - r + rng.randint(-20, 20), yy, pos[2] - r], [pos[0] + 2 * r, yy, pos[2] - r],
                     [pos[0] - r, yy + rng.choice([0, 0, 1, -1]), pos[2] + 2 * r]]
                if rng.random() < 0.5: v = v[::-1]
                for kk in range(3): W(m, VP + 0x18 * t2 + 8 * kk, '3h', *v[kk])
                W(m, BND + 8 * t2, '4h', min(q[0] for q in v), min(q[2] for q in v), max(q[0] for q in v),
                  max(q[2] for q in v))
                W(m, YB + 4 * t2, '2h', min(q[1] for q in v), max(q[1] for q in v))
                W(m, FLG + 4 * t2, 'I', rng.choice([0x0E000000, 0x0F000000, 0x0E000000 | rng.getrandbits(24)]))
        W(m, T26C, 'I', VOFS); W(m, T270, 'I', BND); W(m, T274, 'I', YB)
        W(m, DBE5C, 'I', FLG if rng.random() < 0.8 else 0)
        W(m, DC280, 'i', rng.choice([0, 1]))
        onetree(rng, m, nt, pos[0], pos[2])
        common_globals(rng, m)
        area = rng.choice([0, 0, 2, 3]) if kind != 'ray' else 0
        if area == 2:                                          # P294: world objects (func_150A69A8 lists them)
            nobj, _ = ray_objects(rng, m, nt, pos); W(m, DC320, 'i', nobj); W(m, DC280, 'i', 2)
            W(m, SY['D_800DC3C4'], 'I', OBJMARK)
            vb0 = VP - 0x1000                                  # the engine adds the object's vertex base to the
            for i in range(nobj):                              # level triangles too: one base for all
                W(m, OBJVB + 4 * i, 'I', vb0)
                if rng.random() < 0.6:                         # listed (D_800D3C00): collidable, box around pos
                    o = OBJS + 0xA0 * i; m[phys(o) + 0x6E] = 0; m[phys(o) + 0x4F] = rng.choice([0, 0x80, 0x1F])
                    W(m, o + 0x10, '3h', pos[0] + rng.randint(-20, 20), pos[1], pos[2] + rng.randint(-20, 20))
                    W(m, o + 0x50, '2H', rng.choice([300, 2000]), rng.choice([300, 2000]))
                    W(m, o + 0x56, 'H', rng.choice([1, 3, nt, nt + 20]))
            for t2 in range(nt + 80):
                for kk in range(3): W(m, VOFS + 12 * t2 + 4 * kk, 'I', VP + 0x18 * t2 + 8 * kk - vb0)
        elif area == 3:                                        # P294: the other records' own models
            rec_models(rng, m, recs, nt); W(m, DC280, 'i', 3)
        rec, ri = setup_rec(rng, m, recs, pos)
        if kind == 'ray':
            if rng.random() < 0.5: ray_grid_tree(rng, m, vs, pos)
            W(m, DBE08, 'I', R(m, T278, 'I')[0])
            nobj, ovs = ray_objects(rng, m, nt, pos); W(m, DC320, 'i', nobj); vs = vs + ovs
            STUBS[:] = [{ref.s['func_1510F800']: lambda r, f, mm: None}, {cand.s['func_1510F800']: lambda r, f, mm: None}]
            ref.trace = []
            try:
                ok, v0, info, m1 = ray_call(ref, cand, m, rng, pos, vs)
            except RuntimeError as e:   # P291: an object hit with the flags output and no vertex output reads the flags
                if not str(e).startswith('ref'): raise   # through the last triangle record (Rare's gp): may fault
                hist['ray ref fault'] = hist.get('ray ref fault', 0) + 1; ref.trace = None; STUBS[:] = [None, None]; continue
            for q in sorted(set(RAY_PCS[x] for x in ref.trace if x in RAY_PCS)): hist['ray ' + q] = hist.get('ray ' + q, 0) + 1
            ref.trace = None
            STUBS[:] = [None, None]
        else:
            ref.trace = []
            try:
                ok, v0, info, m1 = wall_call(ref, cand, m, rng, rec, pos, kind)
            except RuntimeError as e:   # P294: area 2 list entries past the listed triangles can read garbage offsets
                if not str(e).startswith('ref'): raise
                hist['wall ref fault'] = hist.get('wall ref fault', 0) + 1; ref.trace = None; continue
            for q in sorted(set(WALL_PCS[x] for x in ref.trace if x in WALL_PCS)): hist['  ' + q] = hist.get('  ' + q, 0) + 1
            ref.trace = None
        key = '%s:%s' % (kind, v0 if v0 in (0, 1) else 'other')
        if kind == 'ac8c4': key += ' hit%d' % R(m1, SY['D_800CC1C0'] + 2 * ri, 'h')[0]
        if kind != 'ray': key += ' area%d' % area
        hist[key] = hist.get(key, 0) + 1
        if not ok:
            bad += 1
            if bad <= 6: print('DIFF', t, kind, 'area', area, info)
    return bad, hist

def level_mode(ref, cand, rng, n, levelno, rom, only):
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
    emu.call('func_15003668', [levelno]); emu.call('func_150038A0', [])
    lv = emu.ram()
    recs = ref.s['D_800CC2D0']
    bad = 0; hist = {}
    kinds = [only] if only else ['ab6d0', 'ac8c4', 'ray']
    for area in (0, 1):
        m0 = bytearray(lv)
        ref.run(m0, a=(area,), entry=0x150A4ED4, regs=SREG)
        nt = R(m0, FS.DBE4C, 'i')[0]; vofs = R(m0, T26C, 'I')[0]
        if nt <= 0: print('area', area, 'no triangles'); continue
        print('area %d: %d triangles, tree %08X, flags %08X, kind %d' % (area, nt, R(m0, T278, 'I')[0],
              R(m0, DBE5C, 'I')[0], R(m0, DC280, 'i')[0]))
        for t in range(n):
            kind = kinds[t % len(kinds)]
            m = bytearray(m0)
            ti = rng.randrange(nt)
            v = [list(R(m, R(m, vofs + 12 * ti + 4 * k, 'I')[0], '3h')) for k in range(3)]
            c = [sum(q[k] for q in v) // 3 for k in range(3)]
            pos = [c[0] + rng.randint(-120, 120), c[1] + rng.randint(-40, 60), c[2] + rng.randint(-120, 120)]
            common_globals(rng, m)
            rec, ri = setup_rec(rng, m, recs, pos)
            if kind == 'ray': ok, v0, info, m1 = ray_call(ref, cand, m, rng, pos)
            else: ok, v0, info, m1 = wall_call(ref, cand, m, rng, rec, pos, kind)
            key = 'area%d %s:%s' % (area, kind, v0 if v0 in (0, 1) else 'other')
            if kind == 'ac8c4': key += ' hit%d' % R(m1, SY['D_800CC1C0'] + 2 * ri, 'h')[0]
            hist[key] = hist.get(key, 0) + 1
            if not ok:
                bad += 1
                if bad <= 6: print('DIFF level', area, t, kind, info)
    return bad, hist

# P285: unit mode (--unit HELPER|all): call one private helper of the wall machine directly. Reference = the asm entry
# with the registers set; candidate = nmw_unit(entry, io) in the NM build (D5E90.c), io = f0..f31 then the GPRs in
# NMW_IO_GPRS order. Inputs come half from a small pool of exact values (0, -0, halves, small integers: sums and
# differences coincide, so the `>` / `<` boundaries and equal coordinates are hit), half random. No NaN / inf.
# Compared: memory, and each helper's outputs (v0, plus the registers listed; the helpers' scratch FPRs are not
# outputs: their callers overwrite them).
IO = 0x80670000
IOG = [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 24, 25, 16, 17, 18, 19, 20, 21, 22, 23, 28, 30]
POOL = [0.0, -0.0, 0.5, -0.5, 1.0, -1.0, 1.5, -1.5, 2.0, -2.0, 3.0, -3.0, 4.0, -4.0, 5.0, -5.0, 6.0, -6.0, 7.0, -7.0,
        10.0, -10.0, 0.25, -0.25]
# helper: (fprs set, gprs set {reg: kind}, outputs: ('v0' | 'f<n>' | '<gpr no>'), description)
UNIT = {
    'aa950': (0x150AA950, list(range(0, 6)), {}, ['v0'], 'box outcode'),
    'aa9b0': (0x150AA9B0, list(range(0, 6)), {}, ['v0'], 'box edge outcode'),
    'aaa88': (0x150AAA88, list(range(0, 6)), {}, ['v0'], 'box corner outcode'),
    'aab58': (0x150AAB58, list(range(0, 12)), {3: 'mask6'}, ['v0'], 'segment vs box faces'),
    'aacf4': (0x150AACF4, [3, 4, 5] + list(range(23, 32)), {}, ['v0'], 'point in triangle'),
    'aae80': (0x150AAE80, list(range(23, 32)), {}, ['f19', 'f20', 'f21', 'f22'], 'triangle plane'),
    'ac824': (0x150AC824, list(range(18, 23)), {8: 'tri'}, ['f%d' % k for k in range(23, 32)], 'triangle to local'),
    'aaf00': (0x150AAF00, list(range(0, 3)) + list(range(23, 32)), {}, ['v0'], 'triangle vs box'),
}

def unit_val(rng, k, pooled):
    if k in (0, 1, 2):                                         # box half extents: >= 0
        return abs(rng.choice(POOL)) if pooled else rng.choice([rng.uniform(0, 60), float(rng.randint(0, 40))])
    if k == 12 and pooled: return rng.choice([1.0, 0.5, 0.0, 2.0, 0.25])
    if k == 18 and pooled: return rng.choice([0.0, 0.0, -0.0, 1.0, -1.0])
    return rng.choice(POOL) if pooled else rng.choice([rng.uniform(-80, 80), float(rng.randint(-60, 60)),
                                                       rng.uniform(-1, 1)])

def unit(ref, cand, base, rng, n, which):
    names = sorted(UNIT) if which == 'all' else which.split(',')
    bad = 0; hist = {}
    for t in range(n):
        nm = names[t % len(names)]
        entry, fl, gl, outs, _ = UNIT[nm]
        pooled = rng.random() < 0.5
        fv = {k: b32(unit_val(rng, k, pooled)) for k in fl}
        if nm == 'aab58' or nm == 'aac58' or nm == 'aaf00':     # sometimes an exact copy of one point in another
            if rng.random() < 0.3:
                src = rng.choice([3, 6, 9, 23, 26, 29]); dst = rng.choice([3, 6, 9, 23, 26, 29])
                for d in range(3):
                    if src + d in fv and dst + d in fv: fv[dst + d] = fv[src + d]
        if nm in ('aa950', 'aa9b0', 'aaa88') and pooled and rng.random() < 0.6:   # the point exactly on a face /
            ax = rng.sample([0, 1, 2], rng.choice([1, 2, 2, 3, 3]))                  # edge / corner plane
            sg = [rng.choice([1, -1]) for _ in ax]
            e = sum(f32(fv[i]) for i in ax) - sum(sg[j] * f32(fv[3 + ax[j]]) for j in range(len(ax) - 1))
            fv[3 + ax[-1]] = b32(sg[-1] * e)
        if nm == 'aacf4' and rng.random() < 0.7:                # the point on the triangle: a vertex, an edge
            vv = [[f32(fv[23 + 3 * i + d]) for d in range(3)] for i in range(3)]   # midpoint or an inner point
            w = rng.choice([(1, 0, 0), (0.5, 0.5, 0), (0, 0.5, 0.5), (0.25, 0.25, 0.5), (0.5, 0.25, 0.25)])
            w = rng.sample(w, 3)
            for d in range(3): fv[3 + d] = b32(sum(w[i] * vv[i][d] for i in range(3)))
        if nm == 'aacf4' and pooled and rng.random() < 0.5:     # a small triangle: edge cross products of +-1
            for k in range(23, 32): fv[k] = b32(rng.choice([0.0, 0.5, -0.5, 1.0, -1.0, 2.0, -2.0, 1.5]))
            for k in (3, 4, 5): fv[k] = b32(rng.choice([0.0, 0.5, -0.5, 1.0, -1.0, 0.25]))
        gv = {}
        for r, kind in gl.items():
            if kind == 'tri': gv[r] = IO + 0x400; continue
            gv[r] = rng.choice([rng.getrandbits(6), rng.choice([1, 2, 3, 4, 8, 12, 0x30, 0x3F, 0])]) if kind == 'mask6' \
                else rng.choice([7, 7, rng.getrandbits(3)])
        if nm == 'aab58' and rng.random() < 0.6:                 # as the caller: a crossing segment, diff = the
            box = [f32(fv[i]) for i in range(3)]                  # end points' outcode bits
            for k in range(6, 12):
                h = box[(k - 6) % 3] + 0.001
                fv[k] = b32(rng.choice([rng.uniform(-1.5 * h, 1.5 * h), rng.uniform(-3 * h, 3 * h), rng.choice([h, -h])]))
            oc = lambda q: sum(b for b, c in ((1, q[0] > box[0]), (2, q[0] < -box[0]), (4, q[1] > box[1]),
                                              (8, q[1] < -box[1]), (16, q[2] > box[2]), (32, q[2] < -box[2])) if c)
            gv[3] = oc([f32(fv[6 + d]) for d in range(3)]) | oc([f32(fv[9 + d]) for d in range(3)])
        m = bytearray(base)
        if nm == 'aacf4' and rng.random() < 0.5: W(m, SY['D_8009FAB0'], 'f', rng.choice([0.0, 1.0, 0.5, 2.0]))
        if nm == 'aaf00':
            for i, a in enumerate(('D_800CC64C', 'D_800CC650', 'D_800CC654')): W(m, SY[a], 'I', fv[i])
            # P288: the box diagonals' slopes ky / kz = hy / hx, hz / hx (func_150492CC sets them with the box); they
            # were left as the image's values, so the diagonal stage saw ky = kz = 0 and its mutants survived
            hx = f32(fv[0]) or 1.0
            W(m, SY['D_800CC658'], 'f', f32(fv[1]) / hx); W(m, SY['D_800CC65C'], 'f', f32(fv[2]) / hx)
            if rng.random() < 0.5:   # a big triangle around a point near the box (no vertex in it, its plane cuts
                box = [max(f32(fv[i]), 0.5) for i in range(3)]   # the box or passes a corner): reaches the diagonals
                c = [rng.uniform(-1.3, 1.3) * box[i] for i in range(3)]
                u = [rng.uniform(-1, 1) for _ in range(3)]; w = [rng.uniform(-1, 1) for _ in range(3)]
                if rng.random() < 0.4: u[rng.randrange(3)] = 0.0   # axis-parallel edges / planes
                R = rng.uniform(3, 8) * max(box); a0 = rng.uniform(0, 6.3)
                for k in range(3):
                    ca, sa = math.cos(a0 + 2.0944 * k), math.sin(a0 + 2.0944 * k)
                    for d in range(3): fv[23 + 3 * k + d] = b32(c[d] + R * (ca * u[d] + sa * w[d]))
        frame = [0] * (0x268 // 4)
        if nm == 'ac824':                                       # 3 vertex offsets at t0, vertex base at sp+0x150
            vb = 0x80660000 + 8 * rng.randrange(0x100); frame[0x150 // 4] = vb
            W(m, IO + 0x400, '3I', *[0x18 * rng.randrange(8) + 6 * rng.randrange(3) for _ in range(3)])
            for k in range(0x60): W(m, vb + 2 * k, 'h', rng.choice([rng.randint(-32768, 32767), rng.randint(-50, 50)]))
            if pooled:
                for k in (18, 19): fv[k] = b32(rng.choice([0.0, 1.0, -1.0, 0.5, -0.5, 0.70710677]))
            else:
                a = rng.uniform(-7, 7); fv[18] = b32(math.sin(a)); fv[19] = b32(math.cos(a))
        m1, m2 = bytearray(m), bytearray(m)
        for k, w in enumerate(frame): W(m1, SP0 + 4 * k, 'I', w)
        r1 = ref.run(m1, fa=fv, regs=dict(gv), entry=entry, maxi=200000)
        for k, w in enumerate(frame): W(m1, SP0 + 4 * k, 'I', 0)
        io = [fv.get(k, 0) for k in range(32)] + [gv.get(r, 0) for r in IOG] + frame
        m2[phys(IO):phys(IO) + 4 * len(io)] = struct.pack('>%dI' % len(io), *io)
        r2 = cand.run(m2, a=(entry, IO), entry='nmw_unit')
        io2 = list(struct.unpack('>%dI' % len(io), bytes(m2[phys(IO):phys(IO) + 4 * len(io)])))
        m2[phys(IO):phys(IO) + 4 * len(io)] = m[phys(IO):phys(IO) + 4 * len(io)]
        o1, o2 = [], []
        for o in outs:
            if o == 'v0': o1.append(r1['v0']); o2.append(r2['v0'] & M32)
            elif isinstance(o, str): o1.append(r1['fpr'][int(o[1:])]); o2.append(io2[int(o[1:])])
            else: o1.append(r1['gpr'][o] & M32); o2.append(io2[32 + IOG.index(o)])
        d = memdiff(m1, m2, skip=[(SP0 - 0x4000, SP0 + 0x100), (SCR, SCR + 0x100)])
        key = '%s:%s' % (nm, o1[0] if o1[0] < 0x10000 else 'val')
        hist[key] = hist.get(key, 0) + 1
        if o1 != o2 or d:
            bad += 1
            if bad <= 8: print('DIFF unit', t, nm, 'in', {k: hex(v) for k, v in fv.items()}, gv,
                                'ref', [hex(q) for q in o1], 'cand', [hex(q) for q in o2], [hex(q) for q in d[:4]])
    return bad, hist

def patch_libm(ref, cand, fns=('sinf', 'cosf', 'func_150484A0', 'func_15048360')):
    """some NM-build callees read tables / literals at addresses that only exist in the NM data layout, which the
    candidate does not have (it runs on the reference's data image): sinf / cosf (libultra C) and func_150484A0
    (atan2-like) return garbage there. Jump from them to copies of the reference's code (jal targets re-pointed to
    the candidate's symbol of the same name)"""
    scr = 0x153E0000
    byaddr = {}
    for k, v in ref.s.items(): byaddr.setdefault(v, k)
    for fn in fns:
        a = ref.s[fn]; nxt = min(v for v in ref.s.values() if v > a); nw = (nxt - a) // 4
        assert nw <= 0x100
        words = [ref.word(a + 4 * i) for i in range(nw)]
        for i, w in enumerate(words):
            if w >> 26 == 3:
                t = ((a + 4 * i + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
                words[i] = (3 << 26) | ((cand.s[byaddr[t]] >> 2) & 0x3FFFFFF)
            elif w >> 26 == 2: raise RuntimeError('%s: j' % fn)
        cand.mu.mem_write(scr, b''.join(w.to_bytes(4, 'big') for w in words))
        j = (2 << 26) | ((scr >> 2) & 0x3FFFFFF)
        cand.mu.mem_write(cand.s[fn], j.to_bytes(4, 'big') + bytes(4))
        scr += 0x400

def main():
    a = sys.argv[1:]; opts = {}; pos = []
    while a:
        x = a.pop(0)
        if x.startswith('--'): opts[x[2:]] = a.pop(0)
        else: pos.append(x)
    n = int(pos[0]) if pos else 300
    rng = random.Random(int(pos[1]) if len(pos) > 1 else 1)
    ref, cand = Ref(), Cand()
    patch_libm(ref, cand)
    if 'unit' in opts:
        bad, hist = unit(ref, cand, base_image(), rng, n, opts['unit'])
    elif 'level' in opts:
        bad, hist = level_mode(ref, cand, rng, n, int(opts['level'], 0), opts.get('rom', '../baserom.eu.z64'),
                               opts.get('only'))
    else:
        bad, hist = synth(ref, cand, base_image(), rng, n, opts.get('only'))
    print('walls trials', n, 'diffs', bad, dict(sorted(hist.items())))

if __name__ == '__main__':
    main()
