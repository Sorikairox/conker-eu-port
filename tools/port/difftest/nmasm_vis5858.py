#!/usr/bin/env python3
"""P34: compare the hand-asm blob func_150A5858 .. func_150A5F98 (game_eu_D2DB0; level visibility walk + level DL
filter) with its NON_MATCHING C, whole.

The asm uses 64-bit registers (sd/ld of DL words, dsll32/dmtc1, sdc1/ldc1 and c.eq.d on odd FPRs, i.e. FR=1),
$gp as a variable and private t-register calls, so neither difftest nor 32-bit Unicorn can run it. The reference
runs here in a small VR4300 interpreter (64-bit GPRs, 32 x 64-bit FPRs) on the instruction words of
build/conker.eu.elf; float32 ops are computed in double and rounded once (exact for + and *, p' >= 2p + 2).
The candidate (build_nm/conker.eu.elf, IDO -mips2 code) runs in Unicorn MIPS32.

Scenes: random BSP trees (pre-order nodes with child / skip offsets, hide bits, leaf triangle-index lists with
absolute and relative entries), a random view matrix and frustum constants, and a random level DL (VTX, TRI1/TRI2/
0x1x, SETTILE / SETTILESIZE incl. tile bytes 8-15 (aliasing the 'current' table), LOADBLOCK, SETTIMG, LOADTLUT,
SETCOMBINE, SETOTHERMODE, TEXTURE, syncs, other commands, repeats of the last state) ending with G_ENDDL.
Optional: `--level FILE.bin`: a real node tree + DL dump (see P34.md) instead of random ones.
Compared: v0 and all of RDRAM except the stack page. Inputs: $gp = 0 at entry (the C starts with prev = 0).

Run in the container from /conker/conker after both builds: python3 ../tools/port/difftest/nmasm_vis5858.py [N] [seed]"""
import struct, random, sys, ctypes, subprocess, os
_UC = os.environ.get('DIFFTEST_UNICORN', os.path.join(os.path.dirname(os.path.abspath(__file__)), '../../../port_work/pyuc201'))
if os.path.isdir(_UC): sys.path.insert(0, os.path.abspath(_UC))   # Unicorn 2.0.1 (2.1.x delay-slot FPU bug, see difftest.py)
from unicorn import Uc, UC_ARCH_MIPS, UC_MODE_MIPS32, UC_MODE_BIG_ENDIAN, UC_PROT_ALL
from unicorn.mips_const import *

M64 = (1 << 64) - 1
RET = 0x153F0000
SP0 = 0x806FF000
RAM = 0x800000

def section(elf, name):
    out = '/tmp/p34_%s_%s.bin' % (elf.replace('/', '_'), name)
    subprocess.check_call(['mips-linux-gnu-objcopy', '-O', 'binary', '-j', name, elf, out])
    h = subprocess.check_output(['mips-linux-gnu-objdump', '-h', elf]).decode()
    for l in h.split('\n'):
        f = l.split()
        if len(f) > 3 and f[1] == name: return int(f[3], 16), open(out, 'rb').read()

def syms(elf):
    d = {}
    for l in subprocess.check_output(['mips-linux-gnu-nm', elf]).decode().split('\n'):
        f = l.split()
        if len(f) == 3: d[f[2]] = int(f[0], 16)
    return d

phys = lambda a: a & 0x1FFFFFFF
sx32 = lambda v: (v & 0xFFFFFFFF) | (M64 ^ 0xFFFFFFFF if v & 0x80000000 else 0)
s64 = lambda v: v - (1 << 64) if v & (1 << 63) else v
def f32(bits): return struct.unpack('>f', struct.pack('>I', bits & 0xFFFFFFFF))[0]
def b32(x): return struct.unpack('>I', struct.pack('>f', ctypes.c_float(x).value))[0]
def f64(bits): return struct.unpack('>d', struct.pack('>Q', bits & M64))[0]

class Ref:
    """VR4300 subset interpreter for the asm blob"""
    def __init__(self, elf):
        self.code = {}
        v, b = section(elf, '.game')
        self.cv, self.cb = v, b
        self.s = syms(elf)
    def word(self, pc):
        o = pc - self.cv
        return struct.unpack('>I', self.cb[o:o + 4])[0]
    def run(self, mem, args, gp=0, maxi=3000000, entry='func_150A5858'):
        r = [0] * 32; f = [0] * 32; cc = False; lo = hi = 0
        for k, a in enumerate(args[:4]): r[4 + k] = sx32(a)
        r[28] = gp; r[29] = sx32(SP0); r[31] = sx32(RET)
        sp = SP0 - 0x10
        for k, a in enumerate(args[4:]): mem[phys(SP0) + 0x10 + 4 * k: phys(SP0) + 0x14 + 4 * k] = struct.pack('>I', a & 0xFFFFFFFF)
        def ea(base, off): return (r[base] + off) & 0xFFFFFFFF
        def rd(a, n):
            return int.from_bytes(mem[phys(a):phys(a) + n], 'big')
        def wr(a, n, v):
            mem[phys(a):phys(a) + n] = (v & ((1 << (8 * n)) - 1)).to_bytes(n, 'big')
        pc = self.s[entry]; npc = pc + 4; n = 0
        while True:
            if pc == RET: return r[2] & 0xFFFFFFFF
            n += 1
            if n > maxi: raise RuntimeError('timeout')
            w = self.word(pc)
            op = w >> 26; rs = (w >> 21) & 31; rt = (w >> 16) & 31; rdr = (w >> 11) & 31; sa = (w >> 6) & 31
            fn = w & 63; imm = w & 0xFFFF; simm = imm - 0x10000 if imm & 0x8000 else imm
            tgt = None; likely_skip = False
            def setr(i, v):
                if i: r[i] = v & M64
            if op == 0:
                if w == 0: pass
                elif fn == 0: setr(rdr, sx32((r[rt] << sa) & 0xFFFFFFFF))
                elif fn == 2: setr(rdr, sx32((r[rt] & 0xFFFFFFFF) >> sa))
                elif fn == 8: tgt = r[rs] & 0xFFFFFFFF
                elif fn == 9: tgt = r[rs] & 0xFFFFFFFF; setr(rdr, sx32(pc + 8))
                elif fn == 0x21: setr(rdr, sx32(r[rs] + r[rt]))
                elif fn == 0x23: setr(rdr, sx32(r[rs] - r[rt]))
                elif fn == 0x24: setr(rdr, r[rs] & r[rt])
                elif fn == 0x25: setr(rdr, r[rs] | r[rt])
                elif fn == 0x26: setr(rdr, r[rs] ^ r[rt])
                elif fn == 0x27: setr(rdr, ~(r[rs] | r[rt]))
                elif fn == 0x2A: setr(rdr, int(s64(r[rs]) < s64(r[rt])))
                elif fn == 0x2B: setr(rdr, int(r[rs] < r[rt]))
                elif fn == 0x3C: setr(rdr, r[rt] << (sa + 32))
                elif fn == 0x38: setr(rdr, r[rt] << sa)                               # dsll (P279)
                elif fn == 0x20: setr(rdr, sx32(r[rs] + r[rt]))                       # add (P291: no overflow trap)
                elif fn == 0x2D: setr(rdr, r[rs] + r[rt])                             # daddu (P291)
                elif fn == 0x2F: setr(rdr, r[rs] - r[rt])                             # dsubu (P291)
                elif fn == 0x18:                                                      # mult (P291)
                    pr = (s64(sx32(r[rs])) * s64(sx32(r[rt]))) & M64; lo, hi = sx32(pr), sx32(pr >> 32)
                elif fn == 0x12: setr(rdr, lo)                                        # mflo (P291)
                elif fn == 0x10: setr(rdr, hi)                                        # mfhi (P291)
                elif fn == 0x3A: setr(rdr, (r[rt] & M64) >> sa)                       # dsrl (P279)
                else: raise RuntimeError('special %x at %08X' % (fn, pc))
            elif op == 1:
                if rt in (0, 2, 1, 3):
                    c = s64(r[rs]) < 0 if rt in (0, 2) else s64(r[rs]) >= 0
                    if c: tgt = (pc + 4 + (simm << 2)) & 0xFFFFFFFF
                    elif rt in (2, 3): likely_skip = True
                else: raise RuntimeError('regimm %x' % rt)
            elif op in (2, 3):
                tgt = ((pc + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
                if op == 3: setr(31, sx32(pc + 8))
            elif op in (4, 5, 6, 7, 0x14, 0x15):
                a, b = s64(r[rs]), s64(r[rt])
                c = {4: a == b, 5: a != b, 6: a <= 0, 7: a > 0, 0x14: a == b, 0x15: a != b}[op]
                if c: tgt = (pc + 4 + (simm << 2)) & 0xFFFFFFFF
                elif op >= 0x14: likely_skip = True
            elif op in (8, 9): setr(rt, sx32(r[rs] + simm))                      # addi (P279: no overflow case) / addiu
            elif op == 0xA: setr(rt, int(s64(r[rs]) < simm))
            elif op == 0xB: setr(rt, int(r[rs] < (simm & M64)))
            elif op == 0xC: setr(rt, r[rs] & imm)
            elif op == 0xD: setr(rt, r[rs] | imm)
            elif op == 0xE: setr(rt, r[rs] ^ imm)
            elif op == 0xF: setr(rt, sx32(imm << 16))
            elif op == 0x11:
                fmt = rs
                fs = (w >> 11) & 31; fd = (w >> 6) & 31; ft = rt
                if fmt == 0: setr(rt, sx32(f[fs]))                                   # mfc1
                elif fmt == 4: f[fs] = (f[fs] & ~0xFFFFFFFF & M64) | (r[rt] & 0xFFFFFFFF)  # mtc1
                elif fmt == 5: f[fs] = r[rt]                                         # dmtc1
                elif fmt == 8:
                    c = cc if (rt & 1) else not cc
                    if c: tgt = (pc + 4 + (simm << 2)) & 0xFFFFFFFF
                    elif rt & 2: likely_skip = True
                elif fmt == 16:
                    a, b = f32(f[fs]), f32(f[ft])
                    if fn == 0: res = b32(a + b)
                    elif fn == 1: res = b32(a - b)
                    elif fn == 2: res = b32(a * b)
                    elif fn == 3:                                                    # div.s (P291; double rounding is exact)
                        if b == 0: res = 0x7FBFFFFF if a == 0 or a != a else (0x7F800000 | ((f[fs] ^ f[ft]) & 0x80000000))
                        else: res = b32(a / b)
                    elif fn == 5: res = f[fs] & 0x7FFFFFFF
                    elif fn == 6: res = f[fs] & 0xFFFFFFFF
                    elif fn == 7: res = (f[fs] ^ 0x80000000) & 0xFFFFFFFF
                    elif fn == 0x36: cc = a <= b; res = None
                    elif fn == 0x32: cc = a == b; res = None
                    elif fn == 0x3C: cc = a < b; res = None
                    elif fn == 0x34: cc = a < b; res = None                          # c.olt (P38)
                    elif fn == 0x35: cc = not (a >= b); res = None                   # c.ult
                    elif fn == 0x37: cc = not (a > b); res = None                    # c.ule
                    elif fn == 0x0D:                                                 # trunc.w.s (P279)
                        if a != a or abs(a) >= 2147483648.0: raise RuntimeError('cvt.w.s range at %08X' % pc)
                        res = int(a) & 0xFFFFFFFF
                    elif fn == 0x24:                                                 # cvt.w.s (round to nearest even)
                        if a != a or abs(a) >= 2147483648.0: raise RuntimeError('cvt.w.s range at %08X' % pc)
                        res = round(a) & 0xFFFFFFFF
                    else: raise RuntimeError('cop1.s %x at %08X' % (fn, pc))
                    if res is not None: f[fd] = (f[fd] & ~0xFFFFFFFF & M64) | res
                elif fmt == 17:
                    if fn == 6: f[fd] = f[fs]
                    elif fn == 0x32: cc = f64(f[fs]) == f64(f[ft])
                    else: raise RuntimeError('cop1.d %x at %08X' % (fn, pc))
                elif fmt == 20 and fn == 0x20:
                    v = f[fs] & 0xFFFFFFFF; v = v - (1 << 32) if v & 0x80000000 else v
                    f[fd] = (f[fd] & ~0xFFFFFFFF & M64) | b32(float(v))
                else: raise RuntimeError('cop1 fmt %x at %08X' % (fmt, pc))
            elif op == 0x20: v = rd(ea(rs, simm), 1); setr(rt, v - 0x100 if v & 0x80 else v); setr(rt, r[rt] & M64)
            elif op == 0x21: v = rd(ea(rs, simm), 2); setr(rt, (v - 0x10000 if v & 0x8000 else v) & M64)
            elif op == 0x23: setr(rt, sx32(rd(ea(rs, simm), 4)))
            elif op == 0x24: setr(rt, rd(ea(rs, simm), 1))
            elif op == 0x25: setr(rt, rd(ea(rs, simm), 2))
            elif op == 0x22 or op == 0x26:   # lwl / lwr (big-endian)
                a = ea(rs, simm); al = a & ~3; word = rd(al, 4); k = a & 3; cur = r[rt] & 0xFFFFFFFF
                if op == 0x22: v = ((word << (8 * k)) & 0xFFFFFFFF) | (cur & ((1 << (8 * k)) - 1))
                else:
                    sh = 8 * (3 - k); v = (word >> sh) | (cur & ~(0xFFFFFFFF >> sh) & 0xFFFFFFFF)
                setr(rt, sx32(v))
            elif op == 0x28: wr(ea(rs, simm), 1, r[rt])
            elif op == 0x29: wr(ea(rs, simm), 2, r[rt])
            elif op == 0x2B: wr(ea(rs, simm), 4, r[rt])
            elif op == 0x31: f[rt] = (f[rt] & ~0xFFFFFFFF & M64) | rd(ea(rs, simm), 4)
            elif op == 0x39: wr(ea(rs, simm), 4, f[rt])
            elif op == 0x35: f[rt] = rd(ea(rs, simm), 8)
            elif op == 0x3D: wr(ea(rs, simm), 8, f[rt])
            elif op == 0x37: setr(rt, rd(ea(rs, simm), 8))
            elif op == 0x3F: wr(ea(rs, simm), 8, r[rt])
            else: raise RuntimeError('op %x at %08X' % (op, pc))
            if likely_skip:
                pc, npc = npc + 4, npc + 8
            elif tgt is not None:
                pc, npc = npc, tgt
            else:
                pc, npc = npc, npc + 4

class Cand:
    def __init__(self, elf, data_from):
        self.secs = [section(data_from if n == '.game_data' else elf, n) for n in ('.game', '.game_data', '.nm_rodata', '.init')]   # .init: IDO's __ll_* helpers (P291)
        self.s = syms(elf)
        mu = Uc(UC_ARCH_MIPS, UC_MODE_MIPS32 | UC_MODE_BIG_ENDIAN)
        mu.mem_map(0x15000000, 0x400000, UC_PROT_ALL)
        mu.mem_map(0x80000, RAM - 0x80000, UC_PROT_ALL)   # not page 0 (P18 Unicorn TLB bug)
        mu.mem_map(0x10000000, 0x100000, UC_PROT_ALL)
        for v, b in self.secs:
            if v >= 0x80000000: continue
            mu.mem_write(v, b)
        self.mu = mu
    def data(self):
        return [(v, b) for v, b in self.secs if v >= 0x80000000]
    def run(self, mem, args, entry='func_150A5858'):
        mu = self.mu
        mu.mem_write(0x80000, bytes(mem[0x80000:RAM]))
        for k, a in enumerate(args[:4]): mu.reg_write(UC_MIPS_REG_A0 + k, a & 0xFFFFFFFF)
        for k, a in enumerate(args[4:]): mu.mem_write(phys(SP0) + 0x10 + 4 * k, struct.pack('>I', a & 0xFFFFFFFF))
        mu.reg_write(UC_MIPS_REG_SP, SP0); mu.reg_write(UC_MIPS_REG_RA, RET); mu.reg_write(UC_MIPS_REG_GP, 0)
        try:
            mu.emu_start(self.s[entry], RET, count=20000000)
        except Exception as e:
            raise RuntimeError('cand %s at pc %08X ra %08X' % (e, mu.reg_read(UC_MIPS_REG_PC), mu.reg_read(UC_MIPS_REG_RA)))
        if mu.reg_read(UC_MIPS_REG_PC) != RET: raise RuntimeError('cand timeout')
        mem[0x80000:RAM] = bytes(mu.mem_read(0x80000, RAM - 0x80000))
        return mu.reg_read(UC_MIPS_REG_V0)

VIS, MTX, TREE, DL, OUT = 0x80300000, 0x80310000, 0x80320000, 0x80340000, 0x80360000
P = lambda mem, a, fmt, *v: mem.__setitem__(slice(phys(a), phys(a) + struct.calcsize('>' + fmt)), struct.pack('>' + fmt, *v))

def tree(rng, mem, nvis, mask):
    """pre-order node tree at TREE; returns end address"""
    buf = bytearray()
    nodes = []
    def node2(depth):
        idx = len(nodes); nodes.append(None)
        start = len(buf)
        leaf = depth >= 3 or rng.random() < 0.35
        y0 = rng.randrange(-600, 600); y1 = y0 + rng.randrange(0, 600)
        if rng.random() < 0.08: y0 |= mask
        y0 = ((y0 & 0xFFFF) ^ 0x8000) - 0x8000
        h2 = y1 | (mask if rng.random() < 0.3 else 0); h2 = ((h2 & 0xFFFF) ^ 0x8000) - 0x8000
        half = rng.choice([rng.randrange(1, 300), rng.randrange(300, 3000), 20000])
        buf.extend(struct.pack('>hhhHhhh', y0, h2, 0, half, rng.randrange(-3000, 3000), rng.randrange(-3000, 3000), 0))
        if leaf:
            prev = None
            for _ in range(rng.randrange(0, 10)):
                i = rng.randrange(nvis)
                if prev is not None and 0 < i - prev < 0x80 and rng.random() < 0.6: buf.append(i - prev)
                else: buf.extend(bytes([0x80 | (i >> 8), i & 0xFF]))
                prev = i
            if rng.random() < 0.05: buf.append(rng.randrange(1, 4))
            buf.append(0)
            if len(buf) & 1: buf.append(0)
            nodes[idx] = (start, None)
            return idx
        kids = [node2(depth + 1) for _ in range(rng.randrange(1, 4))]
        nodes[idx] = (start, kids)
        return idx
    roots = [node2(0) for _ in range(rng.randrange(1, 4))]
    end = len(buf)
    # +4: offset to the next node after this subtree (0 for the last); +0xC: first child
    order = sorted(range(len(nodes)), key=lambda i: nodes[i][0])
    def subtree_end(i):
        s, kids = nodes[i]
        return subtree_end(kids[-1]) if kids else (order_next.get(s, end))
    starts = [nodes[i][0] for i in order]
    order_next = {starts[k]: starts[k + 1] for k in range(len(starts) - 1)}
    for i in order:
        s, kids = nodes[i]
        if kids: struct.pack_into('>h', buf, s + 0xC, nodes[kids[0]][0] - s)
        e = subtree_end(i)
        struct.pack_into('>h', buf, s + 4, 0 if e == end else e - s)
    mem[phys(TREE):phys(TREE) + len(buf)] = buf
    return TREE + len(buf)

def dlist(rng, mem, nvis):
    out = []; used = 0
    last = {}
    def w(hi, lo): out.append((hi & 0xFFFFFFFF, lo & 0xFFFFFFFF))
    for _ in range(rng.randrange(5, 120)):
        k = rng.random()
        if k < 0.25 and used + 4 <= nvis:
            op = rng.choice([5, 6, 0x10, 0x15]); n = {5: 1, 6: 2}.get(op, 4); used += n
            w(op << 24 | rng.getrandbits(24), rng.getrandbits(32))
        elif k < 0.35: w(0x01000000 | rng.getrandbits(24), 0x80380000 + 16 * rng.randrange(64))
        else:
            op = rng.choice([0xF5, 0xF2, 0xF3, 0xEF, 0xFC, 0xFD, 0xD7, 0xF0, 0xE7, 0xE6, 0xD9, 0xFA, 0xDE, 0xF5, 0xF2])
            if op in last and rng.random() < 0.4: w(*last[op]); continue
            lo = rng.getrandbits(32)
            if op in (0xF5, 0xF2): lo = (rng.choice([0, 1, 2, 7] + ([8, 9, 15] if rng.random() < 0.1 else [])) << 24) | (lo & 0xFFFFFF)
            hi = op << 24 | rng.getrandbits(24)
            if rng.random() < 0.3: hi = op << 24; lo = rng.choice([0, lo])
            last[op] = (hi, lo); w(hi, lo)
    w(0xDF000000, 0)
    for k, (hi, lo) in enumerate(out): P(mem, DL + 8 * k, 'II', hi, lo)

def scene(rng, mem, base):
    mem[:] = base
    mem[phys(VIS):phys(OUT) + 0x10000] = bytes(phys(OUT) + 0x10000 - phys(VIS))
    nvis = 8 * rng.choice([rng.randrange(1, 8), rng.randrange(1, 8), rng.randrange(1, 64)])
    mem[phys(VIS):phys(VIS) + nvis] = bytes(rng.choice([0, 0, 1, 2]) for _ in range(nvis))
    P(mem, 0x800D3A88, 'II', VIS, VIS + nvis)                 # D_800D3668 / D_800D3A8C (EU)
    if rng.random() < 0.85: P(mem, 0x800D3A00, 'ff', rng.uniform(0.3, 2.0), rng.uniform(0.3, 2.0))
    else: P(mem, 0x800D3A00, 'ff', rng.uniform(-2.0, 2.0), rng.uniform(-2.0, 2.0))
    P(mem, 0x800D3A90, 'f', rng.choice([rng.uniform(-12000, -6000)] * 4 + [rng.uniform(-12000, -50), rng.uniform(-300, 10)]))
    mask = rng.choice([1, 2, 4, 8, 0x10, 3])
    tree(rng, mem, nvis, mask)
    P(mem, 0x800DC278, 'I', TREE)
    P(mem, 0x800DC26C, 'I', 0x80390000)
    m = [rng.uniform(-1.2, 1.2) for _ in range(16)]
    for k in (12, 13): m[k] = rng.uniform(-1500, 1500)
    m[14] = rng.uniform(-6000, 1000)
    if rng.random() < 0.7:
        m = [rng.uniform(-0.1, 0.1) for _ in range(16)]; m[0] = m[5] = m[10] = m[15] = 1.0
        m[12] = rng.uniform(-300, 300); m[13] = rng.uniform(-300, 300); m[14] = rng.uniform(-4000, -2500)
    P(mem, MTX, '16f', *m)
    dlist(rng, mem, nvis)
    return [DL, OUT, MTX, 0, 0, mask]

def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 300
    seed = int(sys.argv[2]) if len(sys.argv) > 2 else 1
    ref = Ref('build/conker.eu.elf')
    cand = Cand('build_nm/conker.eu.elf', 'build/conker.eu.elf')
    base = bytearray(RAM)
    for v, b in cand.data(): base[phys(v):phys(v) + len(b)] = b
    bad = 0; st = {'emitted': 0, 'visbytes': 0}
    for t in range(n):
        res = []
        for who in ('ref', 'cand'):
            rng = random.Random(seed * 100003 + t)
            mem = bytearray(RAM)
            args = scene(rng, mem, base)
            v0 = ref.run(mem, args) if who == 'ref' else cand.run(mem, args)
            mem[phys(SP0) - 0x1000:phys(SP0) + 0x100] = bytes(0x1100)
            res.append((v0, mem))
        st['emitted'] += (res[0][0] - OUT) // 8
        st['visbytes'] += sum(1 for b in res[0][1][phys(VIS):phys(VIS) + 0x200] if b)
        st['tris'] = st.get('tris', 0) + sum(1 for k in range(0, res[0][0] - OUT, 8) if res[0][1][phys(OUT) + k] in (5, 6, 0x10, 0x15))
        if res[0][0] != res[1][0] or res[0][1] != res[1][1]:
            bad += 1
            if bad <= 5:
                d = next((i for i in range(RAM) if res[0][1][i] != res[1][1][i]), None)
                print('DIFF trial %d: v0 ref %08X cand %08X, first byte %s' % (t, res[0][0], res[1][0], d if d is None else hex(d)))
    print('%s: %d differences in %d trials, %s' % ('EQUIV' if bad == 0 else 'DIFFER', bad, n, st))

if __name__ == '__main__':
    main()
