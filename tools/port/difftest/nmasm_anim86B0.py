#!/usr/bin/env python3
"""P51: compare the hand-asm skeleton / animation evaluator anim_eval_joint_matrices (asm/D5E90.s, with its private helpers
func_150A8680 .. func_150A9E60) with its NON_MATCHING C (src_eu/nm_asm/D5E90_anim.c), whole.

The asm decodes the key frames with 64-bit ldl / ldr / dsrlv / dsllv / dsra32 and sdl / sdr, and uses its own
register conventions, so it runs in the VR4300 interpreter of nmasm_vis5858.py, extended here (mult / mflo, sra,
sub, 64-bit shifts, ldl / ldr / sdl / sdr, div.s, floor.w.s, reads of the sine table D_150AA11C from .game).
The candidate (build_nm/conker.eu.elf, IDO -mips2) runs in Unicorn MIPS32.

Inputs are real ROM data (anim_inputs.py: the model asset of id 0 (Conker) -> skeleton, its animation bank ->
animation header + the two key frames anim_copy_keyframes would copy, at a frame time), with knobs:
  * single animation, blend with animation 2 (A+0x3C = 1..1024, a second animation in slot 2 at +0x210 / +0x34 /
    +0x39 / +0xC / +0x1C), next-key-pair blend (header flag 0x10 forced on in byte 7, A+0x3C <= 0), header flags
    0x20 / 0x40 / 0x80 toggled (0x80 on Conker's data is real for some animations), frame times past the end;
  * per-object adjustments buf (angle adds < 0x800 / scale entries >= 0x800, terminated by 0x1000);
  * remap table with callback indexes 1..5 (the callback table at 0x80088924 points at stubs; every call is
    recorded with a snapshot of the arena) or NULL; random root matrix and height; n = 28 / 24 / 1;
  * anim == NULL (func_150A8680).
Compared: all of RDRAM except the stack pages, the five work-table pointers D_80088908 .. D_80088918 (they point at
the asm's below-stack tables vs the C's stack array) and D_800888EC (compared as NULL / not NULL), plus the
callback sequence with arena snapshots.

Run in the container from /conker/conker after both builds:
  python3 ../tools/port/difftest/nmasm_anim86B0.py [N] [seed]"""
import struct, random, sys, ctypes, subprocess, os, math
HERE = os.path.dirname(os.path.abspath(__file__))
_UC = os.environ.get('DIFFTEST_UNICORN', os.path.join(HERE, '../../../port_work/pyuc201'))
if os.path.isdir(_UC): sys.path.insert(0, os.path.abspath(_UC))
sys.path.insert(0, HERE)
from unicorn import Uc, UC_ARCH_MIPS, UC_MODE_MIPS32, UC_MODE_BIG_ENDIAN, UC_PROT_ALL, UC_HOOK_CODE
from unicorn.mips_const import *
import anim_inputs as AI

M64 = (1 << 64) - 1
RET = 0x153F0000
STUB = 0x153F1000          # callback k: STUB + 0x10 * k
SP0 = 0x806FF000
RAM = 0x800000
ARENAP, ARENA, SKEL, ANIM, BLOB1, BLOB2, BUF, REMAP, MTX = (0x80500000, 0x80510000, 0x80520000, 0x80530000,
                                                           0x80540000, 0x80541000, 0x80550000, 0x80551000, 0x80552000)
CBTAB = 0x8008891C

def section(elf, name):
    out = '/tmp/p51_%s_%s.bin' % (elf.replace('/', '_'), name)
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
s32 = lambda v: (v & 0xFFFFFFFF) - (1 << 32) if v & 0x80000000 else v & 0xFFFFFFFF
def f32(bits): return struct.unpack('>f', struct.pack('>I', bits & 0xFFFFFFFF))[0]
def b32(x):
    try: return struct.unpack('>I', struct.pack('>f', ctypes.c_float(x).value))[0]
    except OverflowError: return 0x7F800000 if x > 0 else 0xFF800000

class Ref:
    """VR4300 subset interpreter (from nmasm_vis5858.py, extended)"""
    def __init__(self, elf):
        v, b = section(elf, '.game')
        self.cv, self.cb = v, b
        self.s = syms(elf)
    def word(self, pc):
        o = pc - self.cv
        return struct.unpack('>I', self.cb[o:o + 4])[0]
    def run(self, mem, args, cblog, arena_rng, maxi=5000000, entry='anim_eval_joint_matrices'):
        r = [0] * 32; f = [0] * 32; cc = False; hi = lo = 0
        for k, a in enumerate(args[:4]): r[4 + k] = sx32(a)
        r[29] = sx32(SP0); r[31] = sx32(RET)
        for k, a in enumerate(args[4:]): mem[phys(SP0) + 0x10 + 4 * k: phys(SP0) + 0x14 + 4 * k] = struct.pack('>I', a & 0xFFFFFFFF)
        def ea(base, off): return (r[base] + off) & 0xFFFFFFFF
        def rd(a, n):
            if 0x15000000 <= a < 0x15400000:
                o = a - self.cv; return int.from_bytes(self.cb[o:o + n], 'big')
            return int.from_bytes(mem[phys(a):phys(a) + n], 'big')
        def wr(a, n, v):
            if not a & 0x80000000: raise RuntimeError('ref write %08X' % a)
            mem[phys(a):phys(a) + n] = (v & ((1 << (8 * n)) - 1)).to_bytes(n, 'big')
        pc = self.s[entry]; npc = pc + 4; n = 0
        while True:
            if pc == RET:
                self.count = n
                return r[2] & 0xFFFFFFFF
            if STUB < pc < STUB + 0x100:
                cblog.append(((pc - STUB) >> 4, bytes(mem[phys(ARENA):phys(ARENA) + arena_rng])))
                pc = r[31] & 0xFFFFFFFF; npc = pc + 4; continue
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
                elif fn == 3: setr(rdr, sx32(s32(r[rt]) >> sa))
                elif fn == 8: tgt = r[rs] & 0xFFFFFFFF
                elif fn == 9: tgt = r[rs] & 0xFFFFFFFF; setr(rdr, sx32(pc + 8))
                elif fn == 0x10: setr(rdr, hi)
                elif fn == 0x12: setr(rdr, lo)
                elif fn == 0x14: setr(rdr, r[rt] << (r[rs] & 63))
                elif fn == 0x16: setr(rdr, r[rt] >> (r[rs] & 63))
                elif fn == 0x18:
                    p = s32(r[rs]) * s32(r[rt]); lo = sx32(p & 0xFFFFFFFF); hi = sx32((p >> 32) & 0xFFFFFFFF)
                elif fn in (0x21, 0x20): setr(rdr, sx32(r[rs] + r[rt]))
                elif fn in (0x23, 0x22): setr(rdr, sx32(r[rs] - r[rt]))
                elif fn == 0x24: setr(rdr, r[rs] & r[rt])
                elif fn == 0x25: setr(rdr, r[rs] | r[rt])
                elif fn == 0x26: setr(rdr, r[rs] ^ r[rt])
                elif fn == 0x27: setr(rdr, ~(r[rs] | r[rt]))
                elif fn == 0x2A: setr(rdr, int(s64(r[rs]) < s64(r[rt])))
                elif fn == 0x2B: setr(rdr, int(r[rs] < r[rt]))
                elif fn == 0x38: setr(rdr, r[rt] << sa)
                elif fn == 0x3A: setr(rdr, r[rt] >> sa)
                elif fn == 0x3B: setr(rdr, s64(r[rt]) >> sa)
                elif fn == 0x3C: setr(rdr, r[rt] << (sa + 32))
                elif fn == 0x3E: setr(rdr, r[rt] >> (sa + 32))
                elif fn == 0x3F: setr(rdr, s64(r[rt]) >> (sa + 32))
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
            elif op in (8, 9): setr(rt, sx32(r[rs] + simm))
            elif op == 0xA: setr(rt, int(s64(r[rs]) < simm))
            elif op == 0xB: setr(rt, int(r[rs] < (simm & M64)))
            elif op == 0xC: setr(rt, r[rs] & imm)
            elif op == 0xD: setr(rt, r[rs] | imm)
            elif op == 0xE: setr(rt, r[rs] ^ imm)
            elif op == 0xF: setr(rt, sx32(imm << 16))
            elif op == 0x11:
                fmt = rs
                fs = (w >> 11) & 31; fd = (w >> 6) & 31; ft = rt
                if fmt == 0: setr(rt, sx32(f[fs]))
                elif fmt == 4: f[fs] = (f[fs] & ~0xFFFFFFFF & M64) | (r[rt] & 0xFFFFFFFF)
                elif fmt == 8:
                    c = cc if (rt & 1) else not cc
                    if c: tgt = (pc + 4 + (simm << 2)) & 0xFFFFFFFF
                    elif rt & 2: likely_skip = True
                elif fmt == 16:
                    a, b = f32(f[fs]), f32(f[ft])
                    if fn == 0: res = b32(a + b)
                    elif fn == 1: res = b32(a - b)
                    elif fn == 2: res = b32(a * b)
                    elif fn == 3:
                        if b == 0.0:
                            res = 0x7FBFFFFF if a == 0.0 or a != a else ((0x7F800000 if (a > 0) == (math.copysign(1, b) > 0) else 0xFF800000))
                        else: res = b32(a / b)
                    elif fn == 6: res = f[fs] & 0xFFFFFFFF
                    elif fn == 7: res = (f[fs] ^ 0x80000000) & 0xFFFFFFFF
                    elif fn == 0xF:
                        if a != a or abs(a) >= 2147483648.0: raise RuntimeError('floor.w.s range at %08X' % pc)
                        res = math.floor(a) & 0xFFFFFFFF
                    elif fn == 0x24:
                        if a != a or abs(a) >= 2147483648.0: raise RuntimeError('cvt.w.s range at %08X' % pc)
                        res = round(a) & 0xFFFFFFFF
                    elif fn == 0x36: cc = a <= b; res = None
                    elif fn == 0x32: cc = a == b; res = None
                    elif fn in (0x34, 0x3C): cc = a < b; res = None
                    elif fn == 0x3E: cc = a <= b; res = None
                    else: raise RuntimeError('cop1.s %x at %08X' % (fn, pc))
                    if res is not None: f[fd] = (f[fd] & ~0xFFFFFFFF & M64) | res
                elif fmt == 20 and fn == 0x20:
                    v = f[fs] & 0xFFFFFFFF; v = v - (1 << 32) if v & 0x80000000 else v
                    f[fd] = (f[fd] & ~0xFFFFFFFF & M64) | b32(float(v))
                else: raise RuntimeError('cop1 fmt %x at %08X' % (fmt, pc))
            elif op == 0x20: v = rd(ea(rs, simm), 1); setr(rt, v - 0x100 if v & 0x80 else v)
            elif op == 0x21: v = rd(ea(rs, simm), 2); setr(rt, v - 0x10000 if v & 0x8000 else v)
            elif op == 0x23: setr(rt, sx32(rd(ea(rs, simm), 4)))
            elif op == 0x24: setr(rt, rd(ea(rs, simm), 1))
            elif op == 0x25: setr(rt, rd(ea(rs, simm), 2))
            elif op in (0x1A, 0x1B):          # ldl / ldr (big-endian)
                a = ea(rs, simm); k = a & 7; dw = rd(a & ~7, 8); cur = r[rt]
                if op == 0x1A: v = ((dw << (8 * k)) & M64) | (cur & ((1 << (8 * k)) - 1))
                else:
                    sh = 8 * (7 - k); v = (dw >> sh) | (cur & ~(M64 >> sh) & M64)
                setr(rt, v)
            elif op == 0x2C:                  # sdl
                a = ea(rs, simm); k = a & 7
                for j in range(8 - k): wr(a + j, 1, (r[rt] >> (56 - 8 * j)) & 0xFF)
            elif op == 0x2D:                  # sdr
                a = ea(rs, simm); k = a & 7
                for j in range(k + 1): wr(a - j, 1, (r[rt] >> (8 * j)) & 0xFF)
            elif op == 0x28: wr(ea(rs, simm), 1, r[rt])
            elif op == 0x29: wr(ea(rs, simm), 2, r[rt])
            elif op == 0x2B: wr(ea(rs, simm), 4, r[rt])
            elif op == 0x31: f[rt] = (f[rt] & ~0xFFFFFFFF & M64) | rd(ea(rs, simm), 4)
            elif op == 0x39: wr(ea(rs, simm), 4, f[rt])
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
        self.secs = [section(data_from if n == '.game_data' else elf, n) for n in ('.game', '.game_data', '.nm_rodata')]
        self.s = syms(elf)
        mu = Uc(UC_ARCH_MIPS, UC_MODE_MIPS32 | UC_MODE_BIG_ENDIAN)
        mu.mem_map(0x15000000, 0x400000, UC_PROT_ALL)
        mu.mem_map(0x80000, RAM - 0x80000, UC_PROT_ALL)
        mu.mem_map(0x10000000, 0x100000, UC_PROT_ALL)
        for v, b in self.secs:
            if v >= 0x80000000: continue
            mu.mem_write(v, b)
        for k in range(16): mu.mem_write(STUB + 0x10 * k, struct.pack('>II', 0x03E00008, 0))
        self.log = None; self.rng = 0
        def hook(uc, addr, size, ud):
            if STUB < addr < STUB + 0x100 and not addr & 0xF and self.log is not None:
                self.log.append(((addr - STUB) >> 4, bytes(uc.mem_read(phys(ARENA), self.rng))))
        mu.hook_add(UC_HOOK_CODE, hook, begin=STUB, end=STUB + 0x100)
        self.mu = mu
    def data(self):
        return [(v, b) for v, b in self.secs if v >= 0x80000000]
    def run(self, mem, args, cblog, arena_rng, entry='anim_eval_joint_matrices'):
        mu = self.mu; self.log = cblog; self.rng = arena_rng
        mu.mem_write(0x80000, bytes(mem[0x80000:RAM]))
        for k, a in enumerate(args[:4]): mu.reg_write(UC_MIPS_REG_A0 + k, a & 0xFFFFFFFF)
        for k, a in enumerate(args[4:]): mu.mem_write(phys(SP0) + 0x10 + 4 * k, struct.pack('>I', a & 0xFFFFFFFF))
        mu.reg_write(UC_MIPS_REG_SP, SP0); mu.reg_write(UC_MIPS_REG_RA, RET)
        try:
            mu.emu_start(self.s[entry], RET, count=20000000)
        except Exception as e:
            raise RuntimeError('cand %s at pc %08X ra %08X' % (e, mu.reg_read(UC_MIPS_REG_PC), mu.reg_read(UC_MIPS_REG_RA)))
        if mu.reg_read(UC_MIPS_REG_PC) != RET: raise RuntimeError('cand timeout')
        mem[0x80000:RAM] = bytes(mu.mem_read(0x80000, RAM - 0x80000))
        return mu.reg_read(UC_MIPS_REG_V0)

P = lambda mem, a, fmt, *v: mem.__setitem__(slice(phys(a), phys(a) + struct.calcsize('>' + fmt)), struct.pack('>' + fmt, *v))

class Inputs:
    def __init__(self):
        self.rom = bytearray(open(os.environ.get('ANIM_ROM', '../baserom.eu.z64'), 'rb').read())
        self.elf = AI.Elf('build/conker.eu.elf')
        self.mdl = AI.model(self.rom, 0)
        self.bank = AI.bank(self.rom, self.elf, 0)
        self.ok = [k for k, (key, sfx, ptr) in enumerate(self.bank['entries']) if key != 999 and key < 30000]
        self.cache = {}
    def state(self, k, t, base):
        try:
            A, blob, info = AI.anim_state(self.rom, self.elf, 0, k, t, base)
        except SystemExit:
            return None
        return A, blob, info

def scene(rng, mem, base, inp, st):
    mem[:] = base
    for a in (ARENA, SKEL, ANIM, BLOB1, BLOB2, BUF, REMAP, MTX):
        mem[phys(a):phys(a) + 0x1000] = bytes(rng.getrandbits(8) for _ in range(0x1000)) if a == ARENA else bytes(0x1000)
    P(mem, ARENAP, 'I', ARENA)
    for k in range(1, 6): P(mem, CBTAB + 8 * k, 'II', STUB + 0x10 * k, 1)
    sk = inp.mdl['skel']; nj = inp.mdl['joints']
    mem[phys(SKEL):phys(SKEL) + len(sk)] = sk
    n = rng.choice([AI.nmat(0, nj)] * 6 + [nj - 4, 1])
    # root matrix
    m = [rng.uniform(-1.5, 1.5) for _ in range(16)]
    for i in (12, 13, 14): m[i] = rng.uniform(-3000, 3000)
    P(mem, MTX, '16f', *m)
    h = rng.choice([0, 0, rng.randrange(-200, 200)])
    # buf: per-object adjustments
    ents = []
    if rng.random() < 0.6:
        for _ in range(rng.randrange(0, 8)):
            if rng.random() < 0.6: ents.append((2 * rng.randrange(0, 3 * (nj - 1)), rng.randrange(-0x3000, 0x3000)))
            else: ents.append((0x800 | 2 * rng.randrange(0, 3 * (nj - 1)), rng.randrange(-0x8000, 0x8000)))
    for i, (o, v) in enumerate(ents): P(mem, BUF + 4 * i, 'Hh', o, v)
    P(mem, BUF + 4 * len(ents), 'Hh', 0x1000, 0)
    remap = 0
    if rng.random() < 0.4:
        remap = REMAP
        for s in range(0x44): mem[phys(REMAP) + s] = rng.choice([0] * 8 + [1, 2, 3, 4, 5])
    if rng.random() < 0.04:
        st['null'] += 1
        return [ARENAP, MTX, 0, SKEL, n, BUF, remap, h], n
    k1 = rng.choice(inp.ok)
    while True:
        frames = None
        t = rng.choice([rng.uniform(0, 40), rng.uniform(0, 3), rng.uniform(0, 200), float(rng.randrange(0, 40))])
        s1 = inp.state(k1, t, BLOB1)
        if s1 is not None: break
        k1 = rng.choice(inp.ok)
    A, blob, info = s1
    if rng.random() < 0.15:
        # frame time exactly at the last whole loop of key groups (time == base in func_150A8EF8)
        d = A[0x48] + 1; base_t = float(((A[0x43] - 1) // d) * d)
        s1b = inp.state(k1, base_t, BLOB1)
        if s1b is not None and base_t < A[0x43] - 1:
            A, blob, info = s1b; st['tbase'] = st.get('tbase', 0) + 1
    mode = rng.random()
    if A[0x45] == 0:
        st['static'] += 1
    if mode < 0.3:
        # blend with a second animation (anim_start_entry copies slot 1 to slot 2)
        k2 = rng.choice(inp.ok)
        s2 = inp.state(k2, rng.uniform(0, 40), BLOB2)
        if s2 is not None:
            A2, blob2, info2 = s2
            A[0x210:0x3E0] = A2[0x40:0x210]
            A[0xC:0x10] = A2[0x8:0xC]
            A[0x1C:0x20] = A2[0x18:0x1C]
            A[0x34:0x38] = A2[0x30:0x34]
            A[0x39] = A2[0x38]
            struct.pack_into('>h', A, 0x3C, rng.choice([1, 1024, rng.randrange(1, 1025), rng.randrange(1, 1025)]))
            mem[phys(BLOB2):phys(BLOB2) + len(blob2)] = blob2
            st['blend2'] += 1
    elif mode < 0.45:
        A[0x47] |= 0x10
        if rng.random() < 0.5: struct.pack_into('>h', A, 0x3C, -rng.randrange(0, 5))
        st['next'] += 1
    else:
        st['single'] += 1
    if rng.random() < 0.15: A[0x47] ^= rng.choice([0x20, 0x40, 0x80])
    if A[0x47] & 0x80: st['f80'] += 1
    if A[0x47] & 0x40: st['f40'] += 1
    mem[phys(ANIM):phys(ANIM) + 0x3E0] = A
    mem[phys(BLOB1):phys(BLOB1) + len(blob)] = blob
    return [ARENAP, MTX, ANIM, SKEL, n, BUF, remap, h], n

MASKS = [(0x80088908, 0x8008891C)]

def main():
    ntr = int(sys.argv[1]) if len(sys.argv) > 1 else 200
    seed = int(sys.argv[2]) if len(sys.argv) > 2 else 1
    ref = Ref('build/conker.eu.elf')
    cand = Cand('build_nm/conker.eu.elf', 'build/conker.eu.elf')
    inp = Inputs()
    base = bytearray(RAM)
    for v, b in cand.data(): base[phys(v):phys(v) + len(b)] = b
    bad = 0; st = dict(null=0, single=0, blend2=0, next=0, static=0, f80=0, f40=0, cbs=0, err=0)
    for t in range(ntr):
        res = []
        for who in ('ref', 'cand'):
            rng = random.Random(seed * 100003 + t)
            mem = bytearray(RAM)
            args, n = scene(rng, mem, base, inp, st if who == 'ref' else dict(st))
            base0 = bytes(mem[phys(ARENA):phys(ARENA) + 0x40 * 32])
            log = []
            rngsz = 0x40 * 0x44
            try:
                (ref.run if who == 'ref' else cand.run)(mem, args, log, rngsz)
                err = None
            except RuntimeError as e:
                err = str(e)
            mem[phys(SP0) - 0x10000:phys(SP0) + 0x100] = bytes(0x10100)
            ec = struct.unpack('>I', mem[phys(0x800888EC):phys(0x800888EC) + 4])[0]
            for a, b in MASKS: mem[phys(a):phys(b)] = bytes(b - a)
            mem[phys(0x800888EC):phys(0x800888EC) + 4] = struct.pack('>I', int(ec != 0))
            res.append((err, mem, log))
            if who == 'ref':
                pass
        if res[0][0] is not None:
            st['err'] += 1
            if st['err'] <= 3: print('ref error trial %d: %s / cand %s' % (t, res[0][0], res[1][0]))
        st['cbs'] += len(res[0][2])
        st['insns'] = st.get('insns', 0) + getattr(ref, 'count', 0); ref.count = 0
        chg = sum(1 for i in range(phys(ARENA), phys(ARENA) + 0x40 * 32) if res[0][1][i] != base0[i - phys(ARENA)])
        st['arena_changed'] = st.get('arena_changed', 0) + chg
        if res[0][0] != res[1][0] or res[0][1] != res[1][1] or res[0][2] != res[1][2]:
            bad += 1
            if bad <= 5:
                d = next((i for i in range(RAM) if res[0][1][i] != res[1][1][i]), None)
                print('DIFF trial %d: err %s / %s, first byte %s (ref %s cand %s), callbacks %d / %d' % (
                    t, res[0][0], res[1][0], d if d is None else hex(d | 0x80000000),
                    None if d is None else res[0][1][d:d + 4].hex(), None if d is None else res[1][1][d:d + 4].hex(),
                    len(res[0][2]), len(res[1][2])))
    print('%s: %d differences in %d trials, %s' % ('EQUIV' if bad == 0 else 'DIFFER', bad, ntr, st))

if __name__ == '__main__':
    main()
