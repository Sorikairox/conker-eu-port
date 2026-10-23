#!/usr/bin/env python3
"""P130: compare the hand-asm shadow triangle projectors func_150A6070 (level triangles by bit mask) and
func_150A6324 (world object triangles by id list), with their private vertex transform func_150A661C, against
their NON_MATCHING C (game_eu_D3880.c), whole.

Reference: the VR4300 interpreter of tools/port/difftest/nmasm_vis5858.py on build/conker.eu.elf, extended here
with add / addi / mult / mflo (the asm uses them). Candidate: build_nm/conker.eu.elf in Unicorn.
Inputs: random bit masks / id lists, triangle tables (3 vertex pointers or offsets), s16 x/z bounds around the shadow
box D_800DF518..D_800DF524, s16 vertices, a light matrix, u/v scale, near/far depth (some NaN, some exact
boundaries), output limits that cut the walk. Compared: v0 and all RDRAM except the stack page.

Run in the container from /conker/conker after both builds:
  python3 ../docs/port/sessions/p130/nmasm_shadow.py [6070|6324] [N] [seed]"""
import os, sys, random, struct, inspect, textwrap
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '../../../../tools/port/difftest'))
import nmasm_vis5858 as V
from nmasm_vis5858 import Cand, RAM, SP0, phys, P, syms

# extend the reference interpreter: add (= addu), addi (= addiu), mult, mflo
src = textwrap.dedent(inspect.getsource(V.Ref))
src = src.replace("elif fn == 0x21: setr(rdr, sx32(r[rs] + r[rt]))",
                  "elif fn in (0x20, 0x21): setr(rdr, sx32(r[rs] + r[rt]))\n"
                  "                elif fn == 0x18: self.lo = sx32((s64(sx32(r[rs])) * s64(sx32(r[rt]))) & 0xFFFFFFFF)\n"
                  "                elif fn == 0x12: setr(rdr, self.lo)", 1)
src = src.replace("elif op == 9: setr(rt, sx32(r[rs] + simm))", "elif op in (8, 9): setr(rt, sx32(r[rs] + simm))", 1)
assert 'fn == 0x18' in src and 'op in (8, 9)' in src
ns = dict(V.__dict__); exec(src, ns); Ref = ns['Ref']

MASK, TRI, BOX, VTX, MTX, OUT, IDS, OBJ, BASES = (0x80300000, 0x80310000, 0x80330000, 0x80340000, 0x80350000,
                                                0x80360000, 0x80370000, 0x80380000, 0x80390000)
NAN = struct.unpack('>f', struct.pack('>I', 0x7FC00000))[0]
fr = lambda rng, lo, hi: struct.unpack('>f', struct.pack('>f', rng.uniform(lo, hi)))[0]
NV = 600

def setsym(mem, addrs, name, fmt, v):
    for a in addrs[name]: P(mem, a, fmt, v)

def common(rng, mem, addrs):
    x0, z0 = rng.randrange(-3000, 3000), rng.randrange(-3000, 3000)
    r = rng.choice([0, 0xE6, rng.randrange(1, 2000)])
    setsym(mem, addrs, 'D_800DF518', 'i', x0 - r); setsym(mem, addrs, 'D_800DF51C', 'i', x0 + r)
    setsym(mem, addrs, 'D_800DF520', 'i', z0 - r); setsym(mem, addrs, 'D_800DF524', 'i', z0 + r)
    su, sv = rng.choice([(1.0, 1.0), (fr(rng, -0.01, 0.01), fr(rng, -0.01, 0.01)), (fr(rng, -3, 3), fr(rng, -3, 3))])
    near = rng.choice([-20000.0, fr(rng, -30000, -100), -5.0]); far = rng.choice([-1.0, fr(rng, -500, 50), 0.0])
    if rng.random() < 0.03: su = NAN
    if rng.random() < 0.03: near = NAN
    if rng.random() < 0.03: far = NAN
    setsym(mem, addrs, 'D_800D3AA0', 'f', su); setsym(mem, addrs, 'D_800D3AA4', 'f', sv)
    setsym(mem, addrs, 'D_800D3AA8', 'f', near); setsym(mem, addrs, 'D_800D3AAC', 'f', far)
    m = [fr(rng, -1, 1) for _ in range(16)]
    m[12], m[13], m[14] = fr(rng, -2000, 2000), fr(rng, -2000, 2000), fr(rng, -8000, 1000)
    if rng.random() < 0.3: m[2] = m[6] = m[10] = 0.0; m[14] = rng.choice([near, far, -m[12], 0.0])  # w on a bound
    if rng.random() < 0.02: m[rng.randrange(16)] = NAN
    P(mem, MTX, '16f', *m)
    # vertices around the box (sometimes exactly on it), s16
    for k in range(NV):
        v = [rng.randrange(-0x8000, 0x8000) if rng.random() < 0.05 else
             max(-0x8000, min(0x7FFF, c + rng.randrange(-r - 300, r + 300))) for c in (x0, rng.randrange(-500, 500), z0)]
        P(mem, VTX + 6 * k, '3h', *v)
    return x0, z0, r

def tris(rng, mem, addrs, n, x0, z0, r, rel):
    setsym(mem, addrs, 'D_800DC270', 'I', BOX); setsym(mem, addrs, 'D_800D3AB0', 'I', TRI)
    for t in range(n):
        vs = [rng.randrange(NV) for _ in range(3)]
        if rng.random() < 0.1: vs = [vs[0]] * 3
        P(mem, TRI + 12 * t, '3I', *[(6 * v if rel else VTX + 6 * v) for v in vs])
        b = []
        for c in (x0, z0):
            lo = c + rng.randrange(-r - 400, r + 400); b.append((lo, lo + rng.randrange(0, 600)))
        if rng.random() < 0.15:  # exactly on a box edge
            k = rng.randrange(4); e = [x0 + r, z0 + r, x0 - r, z0 - r][k]
            if k < 2: b[k] = (e, e + 10)
            else: b[k - 2] = (e - 10, e)
        cl = lambda v: max(-0x8000, min(0x7FFF, v))
        P(mem, BOX + 8 * t, '4h', cl(b[0][0]), cl(b[1][0]), cl(b[0][1]), cl(b[1][1]))

def case6070(rng, mem, addrs):
    x0, z0, r = common(rng, mem, addrs)
    nw = rng.choice([1, 2, rng.randrange(1, 40), 187])
    dens = rng.choice([0.02, 0.2, 0.6, 1.0])
    for k in range(nw):
        w = 0
        if rng.random() < 0.8:
            for bit in range(32):
                if rng.random() < dens: w |= 1 << bit
        if rng.random() < 0.05: w = rng.choice([0x80000000, 1, 0xFFFFFFFF])
        P(mem, MASK + 4 * k, 'I', w)
    setsym(mem, addrs, 'D_800D3AB4', 'I', MASK + 4 * nw)
    tris(rng, mem, addrs, nw * 32, x0, z0, r, False)
    end = OUT + rng.choice([0x3C * rng.randrange(0, 8), rng.randrange(0, 0x400), 0x10000])
    return [MASK, OUT, MTX, end]

def case6324(rng, mem, addrs):
    x0, z0, r = common(rng, mem, addrs)
    nobj = rng.randrange(1, 12); nid = rng.choice([1, rng.randrange(1, 16)])
    setsym(mem, addrs, 'D_800DF514', 'i', nid)
    setsym(mem, addrs, 'D_800DBEF4', 'I', OBJ); setsym(mem, addrs, 'D_800DC328', 'I', BASES)
    ntri = 0
    for o in range(nobj):
        cnt = rng.choice([1, 2, rng.randrange(1, 40)])
        P(mem, OBJ + 0xA0 * o + 0x56, 'H', cnt); P(mem, OBJ + 0xA0 * o + 0x58, 'H', ntri)
        P(mem, BASES + 4 * o, 'I', VTX + 6 * rng.randrange(0, 50))
        ntri += cnt
    tris(rng, mem, addrs, ntri, x0, z0, r, True)
    for k in range(nid): P(mem, IDS + 2 * k, 'H', rng.randrange(nobj))
    end = OUT + rng.choice([0x3C * rng.randrange(0, 8), rng.randrange(0, 0x400), 0x10000])
    return [IDS, OUT, MTX, end]

def nancanon(mem):
    """the interpreter makes Python's NaN 0x7FC00000, the VR4300 / Unicorn 0x7FBFFFFF: NaN words in OUT -> one value"""
    o = phys(OUT)
    for k in range(o, o + 0x10000, 4):
        w = int.from_bytes(mem[k:k + 4], 'big')
        if (w & 0x7F800000) == 0x7F800000 and (w & 0x7FFFFF): mem[k:k + 4] = b'\x7f\xff\xff\xff'

def main():
    which = sys.argv[1] if len(sys.argv) > 1 else '6070'
    n = int(sys.argv[2]) if len(sys.argv) > 2 else 500
    seed = int(sys.argv[3]) if len(sys.argv) > 3 else 1
    entry = 'func_150A' + which; mk = case6070 if which == '6070' else case6324
    ref = Ref('build/conker.eu.elf')
    cand = Cand(os.environ.get('NM_ELF', 'build_nm/conker.eu.elf'), 'build/conker.eu.elf')
    sr, sc = syms('build/conker.eu.elf'), syms(os.environ.get('NM_ELF', 'build_nm/conker.eu.elf'))
    names = ['D_800DF518', 'D_800DF51C', 'D_800DF520', 'D_800DF524', 'D_800D3AA0', 'D_800D3AA8', 'D_800D3AAC',
             'D_800D3AB0', 'D_800D3AB4', 'D_800DC270', 'D_800DF514', 'D_800DBEF4', 'D_800DC328']
    addrs = {k: sorted({sr[k], sc[k]}) for k in names}
    addrs['D_800D3AA4'] = [a + 4 for a in addrs['D_800D3AA0']]
    base = bytearray(RAM)
    for v, bb in cand.data(): base[phys(v):phys(v) + len(bb)] = bb
    bad = 0; st = {}
    for t in range(n):
        res = []
        for who in ('ref', 'cand'):
            rng = random.Random(seed * 100003 + t)
            mem = bytearray(base)
            args = mk(rng, mem, addrs)
            v0 = ref.run(mem, args, entry=entry) if who == 'ref' else cand.run(mem, args, entry=entry)
            mem[phys(SP0) - 0x1000:phys(SP0) + 0x100] = bytes(0x1100)
            nancanon(mem)
            res.append((v0, mem))
        k = (res[0][0] - OUT) // 0x3C
        st[min(k, 9)] = st.get(min(k, 9), 0) + 1
        if res[0][0] != res[1][0] or res[0][1] != res[1][1]:
            bad += 1
            if bad <= 5:
                d = next((i for i in range(RAM) if res[0][1][i] != res[1][1][i]), None)
                print('DIFF trial %d: v0 ref %08X cand %08X, first byte %s' % (t, res[0][0], res[1][0], d if d is None else hex(d)))
    print('%s %s: %d differences in %d trials, triangles out (9 = 9+) %s' % ('EQUIV' if bad == 0 else 'DIFFER', entry, bad, n, dict(sorted(st.items()))))

if __name__ == '__main__':
    main()
