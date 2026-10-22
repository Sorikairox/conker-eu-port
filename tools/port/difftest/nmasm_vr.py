#!/usr/bin/env python3
"""P53: a generic whole-function harness core for hand-written asm vs its NON_MATCHING C.

Ref:  a VR4300 subset interpreter (64-bit GPRs, FR=0 FPU: 32 x 32-bit FPRs, doubles in even/odd pairs, FCSR rounding
      modes and cause bits for cvt/trunc) running the instruction words of build/conker.eu.elf (.init + .game).
      Float32/64 + - * / sqrt are computed in Python doubles and rounded once (exact for float32; float64 uses the
      host double directly). Integer div by zero gives the VR4300 result (lo = rs < 0 ? 1 : -1, hi = rs).
Cand: build_nm/conker.eu.elf in Unicorn MIPS32 (2.0.1), on the reference's .game_data image + its own .nm_rodata.

Both run on a copy of the same 8 MB RDRAM image (bytearray, physical addresses) and return
dict(v0, f0, gpr[32], fpr[32]) plus the memory after the call. A `stubs` dict {addr: fn(regs, mem) -> v0}
replaces callees on both sides (the reference by address, the candidate by symbol of the NM build).
Stubs see GPRs only on the candidate side (Unicorn FPR reads are no-ops): do not stub float callees.
Run in the container from /conker/conker; nmasm_floor.py is the first user."""
import struct, sys, os, ctypes, subprocess, math
_HERE = os.path.dirname(os.path.abspath(__file__))
_UC = os.environ.get('DIFFTEST_UNICORN', os.path.join(_HERE, '../../../port_work/pyuc201'))
if os.path.isdir(_UC): sys.path.insert(0, os.path.abspath(_UC))
from unicorn import Uc, UC_ARCH_MIPS, UC_MODE_MIPS32, UC_MODE_BIG_ENDIAN, UC_PROT_ALL, UC_HOOK_CODE
from unicorn.mips_const import *

M64 = (1 << 64) - 1
M32 = 0xFFFFFFFF
RET = 0x153F0000
SP0 = 0x807FE000      # stack top (frames grow down; SCR above)
RAM = 0x800000
SCR = 0x807FF000      # candidate FPR in / out block (skip it in memdiff)
PRO, EPI = 0x100F0000, 0x100F0100
phys = lambda a: a & 0x1FFFFFFF
sx32 = lambda v: (v & M32) | (M64 ^ M32 if v & 0x80000000 else 0)
s64 = lambda v: v - (1 << 64) if v & (1 << 63) else v
s32 = lambda v: (v & M32) - (1 << 32) if v & 0x80000000 else v & M32
def f32(bits): return struct.unpack('>f', struct.pack('>I', bits & M32))[0]
def b32(x): return struct.unpack('>I', struct.pack('>f', ctypes.c_float(x).value))[0]
def f64(bits): return struct.unpack('>d', struct.pack('>Q', bits & M64))[0]
def b64(x): return struct.unpack('>Q', struct.pack('>d', x))[0]

def section(elf, name):
    out = '/tmp/p53_%s_%s.bin' % (elf.replace('/', '_'), name)
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

def base_image(elf='build/conker.eu.elf'):
    """RDRAM with the reference's .init_data / .game_data loaded"""
    mem = bytearray(RAM)
    for n in ('.init_data', '.game_data'):
        v, b = section(elf, n)
        mem[phys(v):phys(v) + len(b)] = b
    return mem

def cvt_round(x, rm):
    if rm == 0:
        r = math.floor(x); d = x - r
        if d > 0.5 or (d == 0.5 and r % 2): r += 1
        return int(r)
    if rm == 1: return int(math.trunc(x))
    if rm == 2: return int(math.ceil(x))
    return int(math.floor(x))

class Ref:
    def __init__(self, elf='build/conker.eu.elf'):
        self.secs = [section(elf, n) for n in ('.init', '.game')]
        self.s = syms(elf)
        self.ninsn = 0
    def word(self, pc):
        for v, b in self.secs:
            if v <= pc < v + len(b): return struct.unpack('>I', b[pc - v:pc - v + 4])[0]
        raise RuntimeError('ref pc %08X outside code' % pc)
    def run(self, mem, a=(), fa=None, stack=(), entry=None, regs=None, stubs=None, maxi=5000000, sp=SP0):
        r = [0] * 32; f = [0] * 32; st = {'fcsr': 0, 'hi': 0, 'lo': 0, 'cc': False}
        for k, v in enumerate(a): r[4 + k] = sx32(v)
        for k, v in (fa or {}).items(): f[k] = v & M32
        for k, v in (regs or {}).items(): r[k] = sx32(v)
        r[29] = sx32(sp); r[31] = sx32(RET)
        for k, v in enumerate(stack): mem[phys(sp) + 0x10 + 4 * k:phys(sp) + 0x14 + 4 * k] = struct.pack('>I', v & M32)
        stubs = stubs or {}
        def ea(base, off): return (r[base] + off) & M32
        def rd(ad, n):
            if ad < 0x80000000:
                return int.from_bytes(b''.join(self.word((ad & ~3) + 4 * i).to_bytes(4, 'big') for i in range(3))[ad & 3:(ad & 3) + n], 'big')
            return int.from_bytes(mem[phys(ad):phys(ad) + n], 'big')
        def wr(ad, n, v):
            if ad < 0x80000000 or phys(ad) + n > RAM: raise RuntimeError('ref write %08X at %08X' % (ad, pc))
            mem[phys(ad):phys(ad) + n] = (v & ((1 << (8 * n)) - 1)).to_bytes(n, 'big')
        def setr(i, v):
            if i: r[i] = v & M64
        def gd(i): return (f[i | 1] << 32) | f[i & ~1]       # FR=0 double pair
        def sd(i, v): f[i & ~1] = v & M32; f[i | 1] = (v >> 32) & M32
        pc = entry if isinstance(entry, int) else self.s[entry]; npc = pc + 4; n = 0
        while True:
            if pc == RET:
                return dict(v0=r[2] & M32, v1=r[3] & M32, f0=f[0], gpr=[x & M32 for x in r], fpr=list(f))
            if pc in stubs:
                rv = stubs[pc](r, f, mem)
                if rv is not None: r[2] = sx32(rv)
                pc = r[31] & M32; npc = pc + 4; continue
            n += 1
            if n > maxi: raise RuntimeError('ref timeout at %08X' % pc)
            w = self.word(pc)
            op = w >> 26; rs = (w >> 21) & 31; rt = (w >> 16) & 31; rdr = (w >> 11) & 31; sa = (w >> 6) & 31
            fn = w & 63; imm = w & 0xFFFF; simm = imm - 0x10000 if imm & 0x8000 else imm
            tgt = None; likely_skip = False
            if op == 0:
                if w == 0: pass
                elif fn == 0: setr(rdr, sx32((r[rt] << sa) & M32))
                elif fn == 2: setr(rdr, sx32((r[rt] & M32) >> sa))
                elif fn == 3: setr(rdr, sx32(s32(r[rt]) >> sa))
                elif fn == 4: setr(rdr, sx32((r[rt] << (r[rs] & 31)) & M32))
                elif fn == 6: setr(rdr, sx32((r[rt] & M32) >> (r[rs] & 31)))
                elif fn == 7: setr(rdr, sx32(s32(r[rt]) >> (r[rs] & 31)))
                elif fn == 8: tgt = r[rs] & M32
                elif fn == 9: tgt = r[rs] & M32; setr(rdr, sx32(pc + 8))
                elif fn == 0xF: pass                                                  # sync
                elif fn == 0x10: setr(rdr, st['hi'])
                elif fn == 0x11: st['hi'] = r[rs]
                elif fn == 0x12: setr(rdr, st['lo'])
                elif fn == 0x13: st['lo'] = r[rs]
                elif fn in (0x18, 0x19):
                    x, y = (s32(r[rs]), s32(r[rt])) if fn == 0x18 else (r[rs] & M32, r[rt] & M32)
                    p = x * y; st['lo'] = sx32(p & M32); st['hi'] = sx32((p >> 32) & M32)
                elif fn in (0x1A, 0x1B):
                    x, y = (s32(r[rs]), s32(r[rt])) if fn == 0x1A else (r[rs] & M32, r[rt] & M32)
                    if y == 0: st['lo'] = sx32(1 if x < 0 else M32); st['hi'] = sx32(x)
                    else:
                        q = abs(x) // abs(y)
                        if (x < 0) != (y < 0): q = -q
                        st['lo'] = sx32(q & M32); st['hi'] = sx32((x - q * y) & M32)
                elif fn in (0x20, 0x21): setr(rdr, sx32(r[rs] + r[rt]))
                elif fn in (0x22, 0x23): setr(rdr, sx32(r[rs] - r[rt]))
                elif fn == 0x24: setr(rdr, r[rs] & r[rt])
                elif fn == 0x25: setr(rdr, r[rs] | r[rt])
                elif fn == 0x26: setr(rdr, r[rs] ^ r[rt])
                elif fn == 0x27: setr(rdr, ~(r[rs] | r[rt]))
                elif fn == 0x2A: setr(rdr, int(s64(r[rs]) < s64(r[rt])))
                elif fn == 0x2B: setr(rdr, int(r[rs] < r[rt]))
                elif fn == 0x2D: setr(rdr, r[rs] + r[rt])
                elif fn == 0x3C: setr(rdr, r[rt] << (sa + 32))
                elif fn == 0x3E: setr(rdr, r[rt] >> (sa + 32))
                elif fn == 0x3F: setr(rdr, s64(r[rt]) >> (sa + 32))
                else: raise RuntimeError('special %x at %08X' % (fn, pc))
            elif op == 1:
                c = s64(r[rs]) < 0 if rt in (0, 2, 0x10, 0x12) else s64(r[rs]) >= 0
                if rt in (0x10, 0x11, 0x12, 0x13): setr(31, sx32(pc + 8))
                if rt not in (0, 1, 2, 3, 0x10, 0x11, 0x12, 0x13): raise RuntimeError('regimm %x at %08X' % (rt, pc))
                if c: tgt = (pc + 4 + (simm << 2)) & M32
                elif rt in (2, 3, 0x12, 0x13): likely_skip = True
            elif op in (2, 3):
                tgt = ((pc + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
                if op == 3: setr(31, sx32(pc + 8))
            elif op in (4, 5, 6, 7, 0x14, 0x15, 0x16, 0x17):
                x, y = s64(r[rs]), s64(r[rt])
                c = {4: x == y, 5: x != y, 6: x <= 0, 7: x > 0}[op & 7 if op < 8 else op - 0x10]
                if c: tgt = (pc + 4 + (simm << 2)) & M32
                elif op >= 0x14: likely_skip = True
            elif op in (8, 9): setr(rt, sx32(r[rs] + simm))
            elif op == 0xA: setr(rt, int(s64(r[rs]) < simm))
            elif op == 0xB: setr(rt, int(r[rs] < (simm & M64)))
            elif op == 0xC: setr(rt, r[rs] & imm)
            elif op == 0xD: setr(rt, r[rs] | imm)
            elif op == 0xE: setr(rt, r[rs] ^ imm)
            elif op == 0xF: setr(rt, sx32(imm << 16))
            elif op == 0x11:
                fmt = rs; fs = (w >> 11) & 31; fd = (w >> 6) & 31; ft = rt
                if fmt == 0: setr(rt, sx32(f[fs]))
                elif fmt == 2: setr(rt, sx32(st['fcsr']))
                elif fmt == 4: f[fs] = r[rt] & M32
                elif fmt == 6: st['fcsr'] = r[rt] & M32
                elif fmt == 8:
                    c = st['cc'] if (rt & 1) else not st['cc']
                    if c: tgt = (pc + 4 + (simm << 2)) & M32
                    elif rt & 2: likely_skip = True
                elif fmt in (16, 17):
                    if fmt == 16: x, y = f32(f[fs]), f32(f[ft]); put = lambda v: f.__setitem__(fd, b32(v))
                    else: x, y = f64(gd(fs)), f64(gd(ft)); put = lambda v: sd(fd, b64(v))
                    if fn == 0: put(x + y)
                    elif fn == 1: put(x - y)
                    elif fn == 2: put(x * y)
                    elif fn == 3: put(x / y if y != 0 else (math.copysign(math.inf, x) * math.copysign(1, y) if x == x and x != 0 else math.nan))
                    elif fn == 4: put(math.sqrt(x) if x >= 0 else math.nan)
                    elif fn == 5:
                        if fmt == 16: f[fd] = f[fs] & 0x7FFFFFFF
                        else: sd(fd, gd(fs) & (M64 >> 1))
                    elif fn == 6:
                        if fmt == 16: f[fd] = f[fs]
                        else: sd(fd, gd(fs))
                    elif fn == 7:
                        if fmt == 16: f[fd] = f[fs] ^ 0x80000000
                        else: sd(fd, gd(fs) ^ (1 << 63))
                    elif fn in (0xC, 0xD, 0xE, 0xF, 0x24):
                        rm = (fn - 0xC) if fn != 0x24 else st['fcsr'] & 3
                        if x != x or abs(x) >= 2147483648.0:
                            st['fcsr'] |= 0x10040; f[fd] = 0x7FFFFFFF
                        else:
                            st['fcsr'] &= ~0x3F000
                            f[fd] = cvt_round(x, rm) & M32
                    elif fn == 0x20 and fmt == 17: f[fd] = b32(x)
                    elif fn == 0x21 and fmt == 16: sd(fd, b64(x))
                    elif fn >= 0x30:
                        un = x != x or y != y
                        st['cc'] = bool(((fn & 4) and not un and x < y) or ((fn & 2) and not un and x == y) or ((fn & 1) and un))
                    else: raise RuntimeError('cop1 fmt %d fn %x at %08X' % (fmt, fn, pc))
                elif fmt == 20:
                    v = s32(f[fs])
                    if fn == 0x20: f[fd] = b32(float(v))
                    elif fn == 0x21: sd(fd, b64(float(v)))
                    else: raise RuntimeError('cop1.w %x at %08X' % (fn, pc))
                else: raise RuntimeError('cop1 fmt %x at %08X' % (fmt, pc))
            elif op == 0x20: v = rd(ea(rs, simm), 1); setr(rt, (v - 0x100 if v & 0x80 else v) & M64)
            elif op == 0x21: v = rd(ea(rs, simm), 2); setr(rt, (v - 0x10000 if v & 0x8000 else v) & M64)
            elif op == 0x23: setr(rt, sx32(rd(ea(rs, simm), 4)))
            elif op == 0x24: setr(rt, rd(ea(rs, simm), 1))
            elif op == 0x25: setr(rt, rd(ea(rs, simm), 2))
            elif op in (0x22, 0x26):   # lwl / lwr
                ad = ea(rs, simm); k = ad & 3; word = rd(ad & ~3, 4); cur = r[rt] & M32
                if op == 0x22: v = ((word << (8 * k)) & M32) | (cur & ((1 << (8 * k)) - 1))
                else: v = (word >> (8 * (3 - k))) | (cur & ~(M32 >> (8 * (3 - k))) & M32)
                setr(rt, sx32(v))
            elif op in (0x1A, 0x1B):   # ldl / ldr
                ad = ea(rs, simm); k = ad & 7; dw = rd(ad & ~7, 8); cur = r[rt]
                if op == 0x1A: v = ((dw << (8 * k)) & M64) | (cur & ((1 << (8 * k)) - 1))
                else: v = (dw >> (8 * (7 - k))) | (cur & ~(M64 >> (8 * (7 - k))) & M64)
                setr(rt, v)
            elif op == 0x28: wr(ea(rs, simm), 1, r[rt])
            elif op == 0x29: wr(ea(rs, simm), 2, r[rt])
            elif op == 0x2B: wr(ea(rs, simm), 4, r[rt])
            elif op in (0x2A, 0x2E):   # swl / swr
                ad = ea(rs, simm); k = ad & 3; v = r[rt] & M32
                if op == 0x2A:
                    for i in range(4 - k): wr(ad + i, 1, v >> (8 * (3 - i)))
                else:
                    for i in range(k + 1): wr(ad - i, 1, v >> (8 * i))
            elif op == 0x31: f[rt] = rd(ea(rs, simm), 4)
            elif op == 0x39: wr(ea(rs, simm), 4, f[rt])
            elif op == 0x35: sd(rt, rd(ea(rs, simm), 8))
            elif op == 0x3D: wr(ea(rs, simm), 8, gd(rt))
            elif op == 0x37: setr(rt, rd(ea(rs, simm), 8))
            elif op == 0x3F: wr(ea(rs, simm), 8, r[rt])
            elif op == 0x2F: pass   # cache
            else: raise RuntimeError('op %x at %08X' % (op, pc))
            if likely_skip: pc, npc = npc + 4, npc + 8; continue
            pc, npc = npc, (tgt if tgt is not None else npc + 4)

class Cand:
    def __init__(self, elf='build_nm/conker.eu.elf', data_from='build/conker.eu.elf'):
        self.s = syms(elf)
        mu = Uc(UC_ARCH_MIPS, UC_MODE_MIPS32 | UC_MODE_BIG_ENDIAN)
        mu.mem_map(0x15000000, 0x400000, UC_PROT_ALL)
        mu.mem_map(0x10000000, 0x100000, UC_PROT_ALL)
        mu.mem_map(0x80000, RAM - 0x80000, UC_PROT_ALL)   # not page 0 (P18 Unicorn TLB bug)
        for n in ('.init', '.game'):
            v, b = section(elf, n); mu.mem_write(v, b)
        self.nmro = section(elf, '.nm_rodata')
        # Unicorn 2.0.1's FPR reg_read / reg_write are no-ops (P18): FPRs go through SCR with real lwc1 / swc1 code
        K0 = 26
        lw = lambda ft, off: (49 << 26) | (K0 << 21) | (ft << 16) | off
        sw = lambda ft, off: (57 << 26) | (K0 << 21) | (ft << 16) | off
        lk0 = [0x3C1A0000 | (SCR >> 16), 0x375A0000 | (SCR & 0xFFFF)]
        pro = lk0 + [lw(i, 4 * i) for i in range(32)] + [0x03600008, 0]                     # jr k1
        epi = lk0 + [sw(i, 0x80 + 4 * i) for i in range(32)] + [0x3C1B0000 | (RET >> 16), 0x03600008, 0]
        mu.mem_write(PRO, b''.join(struct.pack('>I', x) for x in pro))
        mu.mem_write(EPI, b''.join(struct.pack('>I', x) for x in epi))
        self.mu = mu
        self.hook = None
    def run(self, mem, a=(), fa=None, stack=(), entry=None, regs=None, stubs=None, maxi=50000000, sp=SP0):
        mu = self.mu
        if self.nmro:
            v, b = self.nmro; mem[phys(v):phys(v) + len(b)] = b
        mu.mem_write(0x80000, bytes(mem[0x80000:RAM]))
        for k in range(32): mu.reg_write(UC_MIPS_REG_0 + k, 0) if k else None
        fin = [0] * 32
        for k, v in (fa or {}).items(): fin[k] = v & M32
        mu.mem_write(phys(SCR), b''.join(struct.pack('>I', x) for x in fin))
        for k, v in enumerate(a): mu.reg_write(UC_MIPS_REG_A0 + k, v & M32)
        for k, v in (regs or {}).items(): mu.reg_write(UC_MIPS_REG_0 + k, v & M32)
        for k, v in enumerate(stack): mu.mem_write(phys(sp) + 0x10 + 4 * k, struct.pack('>I', v & M32))
        mu.reg_write(UC_MIPS_REG_SP, sp); mu.reg_write(UC_MIPS_REG_RA, EPI)
        mu.reg_write(UC_MIPS_REG_K1, entry if isinstance(entry, int) else self.s[entry])
        if self.hook is not None: mu.hook_del(self.hook); self.hook = None
        if stubs:
            def hk(uc, addr, size, ud):
                if addr in stubs:
                    rr = [uc.reg_read(UC_MIPS_REG_0 + i) for i in range(32)]
                    ff = [uc.reg_read(UC_MIPS_REG_F0 + i) for i in range(32)]
                    m2 = bytearray(uc.mem_read(0x80000, RAM - 0x80000)); m2 = bytearray(0x80000) + m2
                    rv = stubs[addr](rr, ff, m2)
                    uc.mem_write(0x80000, bytes(m2[0x80000:]))
                    if rv is not None: uc.reg_write(UC_MIPS_REG_V0, rv & M32)
                    for i in range(32): uc.reg_write(UC_MIPS_REG_F0 + i, ff[i] & M32)
                    uc.reg_write(UC_MIPS_REG_PC, uc.reg_read(UC_MIPS_REG_RA))
            self.hook = mu.hook_add(UC_HOOK_CODE, hk, begin=min(stubs), end=max(stubs) + 4)
        try:
            mu.emu_start(PRO, RET, count=maxi)
        except Exception as e:
            raise RuntimeError('cand %s at pc %08X ra %08X' % (e, mu.reg_read(UC_MIPS_REG_PC), mu.reg_read(UC_MIPS_REG_RA)))
        if mu.reg_read(UC_MIPS_REG_PC) != RET: raise RuntimeError('cand timeout at %08X' % mu.reg_read(UC_MIPS_REG_PC))
        mem[0x80000:RAM] = bytes(mu.mem_read(0x80000, RAM - 0x80000))
        fo_keep = bytes(mem[phys(SCR):phys(SCR) + 0x100])
        if self.nmro:
            v, b = self.nmro; mem[phys(v):phys(v) + len(b)] = bytes(len(b))
        fo = list(struct.unpack('>32I', fo_keep[0x80:0x100])); mem[phys(SCR):phys(SCR) + 0x100] = bytes(0x100)
        return dict(v0=mu.reg_read(UC_MIPS_REG_V0), v1=mu.reg_read(UC_MIPS_REG_V1), f0=fo[0],
                    gpr=[mu.reg_read(UC_MIPS_REG_0 + i) & M32 for i in range(32)], fpr=fo)

def memdiff(m1, m2, skip=()):
    """first differing addresses (kseg0), outside the [lo, hi) ranges in skip"""
    out = []
    if m1 == m2: return out
    for i in range(0, RAM, 0x1000):
        if m1[i:i + 0x1000] != m2[i:i + 0x1000]:
            for j in range(i, i + 0x1000):
                a = 0x80000000 + j
                if m1[j] != m2[j] and not any(lo <= a < hi for lo, hi in skip):
                    out.append(a)
                    if len(out) > 8: return out
    return out
