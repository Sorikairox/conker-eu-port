#!/usr/bin/env python3
"""P197 (copy of P38 nmasm_view6840.py for func_150A66F0, the variant without a camera record: side tests
(u -+ r*0.7071) * D_800D3A00[0] against +-(depth + r*0.7071), v likewise with ry and D_800D3A00[1]).
P38: compare the hand-asm view test func_150A6840 (game_eu_D3880; FR=1 odd FPRs f13/f15/f17 as singles) with its
NON_MATCHING C, whole.

Reference: the VR4300 interpreter of nmasm_vis5858.py on build/conker.eu.elf (float32 ops computed in double and
rounded once; c.ule / c.ult are true on NaN; cvt.w.s rounds to nearest even). Candidate: build_nm/conker.eu.elf in
Unicorn MIPS32. Inputs: camera record (side planes at +0x88..+0xB4), 4x4 matrix, x y z r ry far, D_800D9F40.
Cases cover every exit (near / far / 4 side planes / inside), round-half ties, w rounding to 0 (returns 1), NaN.
Compared: v0 and all RDRAM except the stack page.

Run in the container from /conker/conker after both builds: python3 ../tools/port/difftest/nmasm_view6840.py [N] [seed]"""
import os, sys, random, struct
sys.path.insert(0, '/conker/tools/port/difftest')
from nmasm_vis5858 import Ref, Cand, RAM, SP0, phys, P, syms

CAM, MTX = 0x80300000, 0x80310000
NAN = struct.unpack('>f', struct.pack('>I', 0x7FC00000))[0]

def b(f):
    return struct.unpack('>I', struct.pack('>f', f))[0]

def fr(rng, lo, hi):
    return struct.unpack('>f', struct.pack('>f', rng.uniform(lo, hi)))[0]

def model(m, c, x, y, z, r, ry, far, D):
    """exit class (stats only); c = (ex, ey)"""
    f = lambda a: struct.unpack('>f', struct.pack('>f', a))[0]
    w = f(f(f(m[2] * x) + f(m[6] * y)) + f(f(m[10] * z) + m[14]))
    if not (f(w - r) <= -D): return 'near'
    if f(w + r) < -far: return 'far'
    d = -w; rs = f(r * K); lim = f(d + rs)
    u = f(f(f(m[0] * x) + f(m[4] * y)) + f(f(m[8] * z) + m[12]))
    if not (f(f(u - rs) * c[0]) <= lim): return 'u+'
    if f(f(u + rs) * c[0]) < -lim: return 'u-'
    v = f(f(f(m[1] * x) + f(m[5] * y)) + f(f(m[9] * z) + m[13]))
    rys = f(ry * K)
    if not (f(f(v - rys) * c[1]) <= lim): return 'v+'
    if f(f(v + rys) * c[1]) < -lim: return 'v-'
    return 'in0' if round(d) == 0 else 'in'

KADDR = []
K = struct.unpack('>f', bytes.fromhex('3F3504F3'))[0]

def case(rng, mem, base, addrs, eaddrs):
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
    c = [rng.choice([fr(rng, 0.5, 3), 1.0, fr(rng, -2, 2), 1.7320508]) for _ in range(2)]
    f = lambda a: struct.unpack('>f', struct.pack('>f', a))[0]
    w = f(f(f(m[2] * x) + f(m[6] * y)) + f(f(m[10] * z) + m[14]))
    u = f(f(f(m[0] * x) + f(m[4] * y)) + f(f(m[8] * z) + m[12]))
    v = f(f(f(m[1] * x) + f(m[5] * y)) + f(f(m[9] * z) + m[13]))
    k = rng.random()          # exact boundary cases
    if k < 0.08: far = -f(w + r)
    elif k < 0.14: D = -f(w - r); [P(mem, a, 'f', D) for a in addrs]
    elif k < 0.24 and c[0] != 0: m[14] = f(-(abs(u) + 50)); m[2] = m[6] = m[10] = 0.0
    vals = [x, y, z, r, ry, far]
    if rng.random() < 0.04:
        k = rng.randrange(6); vals[k] = NAN
    if rng.random() < 0.02:
        c[rng.randrange(2)] = NAN
    x, y, z, r, ry, far = vals
    for a in eaddrs: P(mem, a, 'f', c[0]); P(mem, a + 4, 'f', c[1])
    P(mem, 0x8009FA70, 'I', 0x3F3504F3)   # the reference's sqrt(1/2) (NM rodata sits elsewhere)
    for a in KADDR: P(mem, a, 'I', 0x3F3504F3)   # the candidate's literal in .nm_rodata (NOLOAD)
    P(mem, MTX, '16f', *m)
    args = [MTX, b(x), b(y), b(z), b(r), b(ry), b(far)]
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
    # P197: .nm_rodata is NOLOAD: find the candidate's float literals (lui at, 0x804x / lwc1 ft, off(at))
    fa = syms('build_nm/conker.eu.elf')['func_150A66F0']
    code = dict(cand.secs[0:1])
    for v, bb in cand.secs:
        if v <= fa < v + len(bb): words = [struct.unpack('>I', bb[fa - v + 4 * i:fa - v + 4 * i + 4])[0] for i in range(0x80)]
    hi = None
    for w in words:
        if w >> 16 == 0x3C01 and (w & 0xFFF0) == 0x8040: hi = (w & 0xFFFF) << 16
        elif hi is not None and w >> 26 == 0x31 and (w >> 21) & 31 == 1: KADDR.append(hi + ((w & 0xFFFF) ^ 0x8000) - 0x8000)
    print('candidate literals at', [hex(a) for a in KADDR])
    eaddrs = sorted({syms('build/conker.eu.elf')['D_800D3A00'], syms('build_nm/conker.eu.elf')['D_800D3A00']})
    base = bytearray(RAM)
    for v, bb in cand.data(): base[phys(v):phys(v) + len(bb)] = bb
    bad = 0; st = {}; skip = 0
    for t in range(n):
        res = []
        for who in ('ref', 'cand'):
            rng = random.Random(seed * 100003 + t)
            mem = bytearray(RAM)
            args, cls = case(rng, mem, base, addrs, eaddrs)
            try:
                v0 = ref.run(mem, args, entry='func_150A66F0') if who == 'ref' else cand.run(mem, args, entry='func_150A66F0')
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
