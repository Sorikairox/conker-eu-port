#!/usr/bin/env python3
"""P38: compare the hand-asm view test func_150A6840 (game_eu_D3880; FR=1 odd FPRs f13/f15/f17 as singles) with its
NON_MATCHING C, whole.

Reference: the VR4300 interpreter of nmasm_vis5858.py on build/conker.eu.elf (float32 ops computed in double and
rounded once; c.ule / c.ult are true on NaN; cvt.w.s rounds to nearest even). Candidate: build_nm/conker.eu.elf in
Unicorn MIPS32. Inputs: camera record (side planes at +0x88..+0xB4), 4x4 matrix, x y z r ry far, D_800D9F40.
Cases cover every exit (near / far / 4 side planes / inside), round-half ties, w rounding to 0 (returns 1), NaN.
Compared: v0 and all RDRAM except the stack page.

Run in the container from /conker/conker after both builds: python3 ../tools/port/difftest/nmasm_view6840.py [N] [seed]"""
import os, sys, random, struct
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from nmasm_vis5858 import Ref, Cand, RAM, SP0, phys, P, syms

CAM, MTX = 0x80300000, 0x80310000
NAN = struct.unpack('>f', struct.pack('>I', 0x7FC00000))[0]

def b(f):
    return struct.unpack('>I', struct.pack('>f', f))[0]

def fr(rng, lo, hi):
    return struct.unpack('>f', struct.pack('>f', rng.uniform(lo, hi)))[0]

def model(m, c, x, y, z, r, ry, far, D):
    """exit class (stats only)"""
    f = lambda a: struct.unpack('>f', struct.pack('>f', a))[0]
    w = f(f(f(m[2] * x) + f(m[6] * y)) + f(f(m[10] * z) + m[14]))
    if not (f(w - r) <= -D): return 'near'
    if f(w + r) < -far: return 'far'
    u = f(f(f(m[0] * x) + f(m[4] * y)) + f(f(m[8] * z) + m[12]))
    v = f(f(f(m[1] * x) + f(m[5] * y)) + f(f(m[9] * z) + m[13]))
    for k, (a, p, q, lim) in enumerate([(u, 0, 2, r), (u, 3, 5, r), (v, 7, 8, ry), (v, 10, 11, ry)]):
        if not (f(f(a * c[p]) + f(w * c[q])) >= -lim): return 'side%d' % k
    rw = round(w)
    return 'in0' if rw == 0 else 'in'

def case(rng, mem, base, addrs):
    mem[:] = base
    D = rng.choice([fr(rng, 200, 400), fr(rng, 0, 2), 0.0, 320.0])
    for a in addrs: P(mem, a, 'f', D)
    m = [fr(rng, -1.2, 1.2) for _ in range(16)]
    m[12], m[13], m[14] = fr(rng, -1500, 1500), fr(rng, -1500, 1500), fr(rng, -6000, 1000)
    if rng.random() < 0.5:   # camera-like
        m = [fr(rng, -0.1, 0.1) for _ in range(16)]; m[0] = m[5] = m[10] = m[15] = 1.0
        m[12], m[13], m[14] = fr(rng, -300, 300), fr(rng, -300, 300), fr(rng, -4000, -200)
    x, y, z = fr(rng, -1500, 1500), fr(rng, -1500, 1500), fr(rng, -1500, 1500)
    if rng.random() < 0.15:  # w = k + 0.5 or near 0 exactly
        m[2] = m[6] = m[10] = 0.0
        m[14] = rng.choice([rng.randrange(-400, 0) + 0.5, rng.choice([-0.5, 0.5, -1.5, 0.25, -0.25, 0.0, -2.5])])
        if rng.random() < 0.5: D = 0.0; [P(mem, a, 'f', D) for a in addrs]
    r = rng.choice([fr(rng, 0, 50), fr(rng, 0, 600), fr(rng, 300, 3000)])
    ry = rng.choice([r, fr(rng, 0, 600), fr(rng, 0, 3000)])
    far = rng.choice([fr(rng, 1000, 20000), 20000.0, fr(rng, 0, 3000)])
    c = [fr(rng, -1, 1) for _ in range(12)]
    if rng.random() < 0.6:   # plausible frustum normals: p0 * u + p2 * w >= -r
        c[0], c[2] = fr(rng, 0.5, 1), fr(rng, -1, -0.3)
        c[3], c[5] = fr(rng, -1, -0.5), fr(rng, -1, -0.3)
        c[7], c[8] = fr(rng, 0.5, 1), fr(rng, -1, -0.3)
        c[10], c[11] = fr(rng, -1, -0.5), fr(rng, -1, -0.3)
    f = lambda a: struct.unpack('>f', struct.pack('>f', a))[0]
    w = f(f(f(m[2] * x) + f(m[6] * y)) + f(f(m[10] * z) + m[14]))
    u = f(f(f(m[0] * x) + f(m[4] * y)) + f(f(m[8] * z) + m[12]))
    v = f(f(f(m[1] * x) + f(m[5] * y)) + f(f(m[9] * z) + m[13]))
    k = rng.random()          # exact boundary cases (each comparison at equality)
    if k < 0.06: far = -f(w + r)
    elif k < 0.12: r = -f(f(u * c[0]) + f(w * c[2]))
    elif k < 0.18: r = -f(f(u * c[3]) + f(w * c[5]))
    elif k < 0.24: ry = -f(f(v * c[7]) + f(w * c[8]))
    elif k < 0.30: ry = -f(f(v * c[10]) + f(w * c[11]))
    elif k < 0.34: D = -f(w - r); [P(mem, a, 'f', D) for a in addrs]
    vals = [x, y, z, r, ry, far]
    if rng.random() < 0.04:
        k = rng.randrange(6); vals[k] = NAN
    if rng.random() < 0.02:
        c[rng.randrange(12)] = NAN
    x, y, z, r, ry, far = vals
    for k in range(48): P(mem, CAM + 4 * k, 'I', rng.getrandbits(32))
    for k, off in enumerate(range(0x88, 0xB8, 4)): P(mem, CAM + off, 'f', c[k])
    P(mem, MTX, '16f', *m)
    args = [CAM, MTX, b(x), b(y), b(z), b(r), b(ry), b(far)]
    try:
        cls = model(m, c, x, y, z, r, ry, far, D)
    except Exception:
        cls = 'nan'
    return args, cls

def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 3000
    seed = int(sys.argv[2]) if len(sys.argv) > 2 else 1
    ref = Ref('build/conker.eu.elf')
    cand = Cand('build_nm/conker.eu.elf', 'build/conker.eu.elf')
    addrs = sorted({syms('build/conker.eu.elf')['D_800D9F40'], syms('build_nm/conker.eu.elf')['D_800D9F40']})
    base = bytearray(RAM)
    for v, bb in cand.data(): base[phys(v):phys(v) + len(bb)] = bb
    bad = 0; st = {}; skip = 0
    for t in range(n):
        res = []
        for who in ('ref', 'cand'):
            rng = random.Random(seed * 100003 + t)
            mem = bytearray(RAM)
            args, cls = case(rng, mem, base, addrs)
            try:
                v0 = ref.run(mem, args, entry='func_150A6840') if who == 'ref' else cand.run(mem, args, entry='func_150A6840')
            except RuntimeError as e:
                if 'cvt.w.s range' in str(e): v0 = None
                else: raise
            mem[phys(SP0) - 0x1000:phys(SP0) + 0x100] = bytes(0x1100)
            res.append((v0, mem))
            if v0 is None: break
        if res[0][0] is None: skip += 1; continue
        st[cls] = st.get(cls, 0) + 1
        if res[0][0] != res[1][0] or res[0][1] != res[1][1]:
            bad += 1
            if bad <= 5:
                d = next((i for i in range(RAM) if res[0][1][i] != res[1][1][i]), None)
                print('DIFF trial %d (%s): v0 ref %08X cand %08X, first byte %s' % (t, cls, res[0][0], res[1][0], d if d is None else hex(d)))
    print('%s: %d differences in %d trials (%d skipped), exits %s' % ('EQUIV' if bad == 0 else 'DIFFER', bad, n, skip, dict(sorted(st.items()))))

if __name__ == '__main__':
    main()
