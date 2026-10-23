#!/usr/bin/env python3
"""P133: whole-function test of the hand-asm sprite billboard func_150A6D40 (game_eu_D4550) against its NON_MATCHING C.
The asm uses 64-bit registers (dsll32 / dsll / sd of the vertices, a 64-bit leftover compare) and odd FPRs (FR=1),
so difftest / 32-bit Unicorn cannot run it.

Reference: the VR4300 interpreter of tools/port/difftest/nmasm_vis5858.py on build/conker.eu.elf, extended with
mult / mflo / dsll and with stubs for the three callees. Candidate: build_nm/conker.eu.elf in Unicorn; the callee
entries are patched with a trampoline (lwc1 f0 / lw v0 from a scratch slot, jr ra) that also logs the call (see main).
Stubs: func_15048A40 / func_150489B0 return deterministic floats (keyed by call number), func_15095380 returns
a0 + 0x28. Logged and compared per call: callee, a0..a3 and the stack words sp+0x10..0x1C (func_15095380's 9th
argument, the asm's stale caller s0, is logged but not compared).
Inputs: random sprite records (flags with each mode bit, angles 0 / random, sizes, positions, frame buffer index
D_800BE9C0 -4..3), the descriptor table entry (texture id or a frame table at 0x10000000+), the last-state globals
D_800DD5E4/E8/EC/EE/F6 equal or not, D_800D30BC, the yaw D_800DD600, the hide word at &D_800DBFF0 + idx * 0x9A0 +
0x5F0. Compared: v0, the call log and all RDRAM except the stack page and the scratch slot.

Run in the container from /conker/conker after both builds: python3 ../docs/port/sessions/p133/whole6d40.py [N] [seed]"""
import os, sys, random, struct, inspect, textwrap
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '../../../../tools/port/difftest'))
import nmasm_vis5858 as V
from nmasm_vis5858 import Cand, RAM, SP0, P, syms
from unicorn.mips_const import *

FTAB = 0x7E0000           # RDRAM backing of the 0x10000000 frame tables (both runners)
SCRATCH = 0x807F0000      # trampoline slot: f0, v0
def phys(a):
    a &= 0xFFFFFFFF
    if 0x10000000 <= a < 0x10010000: return FTAB + (a & 0xFFFF)
    return a & 0x1FFFFFFF

src = textwrap.dedent(inspect.getsource(V.Ref))
src = src.replace("elif fn == 0x21: setr(rdr, sx32(r[rs] + r[rt]))",
                  "elif fn in (0x20, 0x21): setr(rdr, sx32(r[rs] + r[rt]))\n"
                  "                elif fn == 0x18: self.lo = sx32((s64(sx32(r[rs])) * s64(sx32(r[rt]))) & 0xFFFFFFFF)\n"
                  "                elif fn == 0x12: setr(rdr, self.lo)\n"
                  "                elif fn == 0x38: setr(rdr, (r[rt] << sa) & M64)", 1)
src = src.replace("            if pc == RET: return r[2] & 0xFFFFFFFF\n",
                  "            if pc == RET: return r[2] & 0xFFFFFFFF\n"
                  "            if pc in self.stubs:\n"
                  "                v0, f0 = self.stub(self.stubs[pc], [r[4], r[5], r[6], r[7]], lambda o: rd((r[29] + o) & 0xFFFFFFFF, 4))\n"
                  "                r[2] = sx32(v0); f[0] = f0; pc = r[31] & 0xFFFFFFFF; npc = pc + 4; continue\n", 1)
assert 'fn == 0x18' in src and 'self.stubs' in src and 'fn == 0x38' in src
ns = dict(V.__dict__); ns['phys'] = phys; exec(src, ns); Ref = ns['Ref']

CALLEES = ('func_15048A40', 'func_150489B0', 'func_15095380')
REC, GFX, SPR = 0x80300000, 0x80340000, 0x80350000

class Log:
    def __init__(self, seed):
        self.calls = []; self.seed = seed
    def stub(self, name, regs, stk):
        n = len(self.calls)
        st = [stk(0x10 + 4 * k) for k in range(5)] if name == 'func_15095380' else []
        self.calls.append((name, [x & 0xFFFFFFFF for x in regs] if name == 'func_15095380' else [regs[0] & 0xFFFFFFFF], st[:4]))
        v0, f = self.val(n)
        if name == 'func_15095380': v0 = (regs[0] & 0xFFFFFFFF) + 0x28
        return v0, f
    def val(self, n):
        rng = random.Random(self.seed * 7919 + n)
        f = struct.unpack('>I', struct.pack('>f', rng.choice([rng.uniform(-1, 1), 0.0, 1.0, -1.0])))[0]
        return rng.getrandbits(32), f

def case(rng, mem, addrs):
    for k in range(0x100): mem[phys(REC) + k] = rng.getrandbits(8)
    s = REC + 0x10
    fl = 0
    for bit in (0x8000, 0x200, 0x4000, 0x8, 0x10, 0x400, 0x1000, 0x2000, 0x800, 0x20):
        if rng.random() < 0.25: fl |= bit
    fl |= rng.getrandbits(16) & ~0xFE38 if rng.random() < 0.3 else 0
    if rng.random() < 0.1: fl = rng.getrandbits(16)
    P(mem, s + 0x98, 'H', fl)
    ang = lambda: rng.choice([0, rng.randrange(0, 0x100), rng.randrange(0x100, 0x10000)])
    P(mem, s + 0x9C, 'H', ang()); P(mem, s + 0x9E, 'H', ang())
    P(mem, s + 0x92, 'h', rng.choice([rng.randrange(-300, 300), rng.randrange(-0x8000, 0x8000), 0]))
    P(mem, s + 0x94, 'h', rng.choice([rng.randrange(-300, 300), rng.randrange(-0x8000, 0x8000), 0]))
    for o in (0x8C, 0x8E, 0x90): P(mem, s + o, 'h', rng.randrange(-0x8000, 0x8000))
    frm = rng.choice([0, rng.randrange(0, 4) << 8, rng.randrange(-0x8000, 0x8000)])
    P(mem, s + 0x88, 'h', frm)
    sidx = rng.randrange(0, 0x100); mem[phys(s + 0xA0)] = sidx
    for a in addrs['D_8008CDEC']: P(mem, a + 4 * sidx, 'I', SPR)
    if rng.random() < 0.3:
        P(mem, SPR, 'I', 0x10000000)
        fi = (frm & 0xFFFFFFFF) >> 8 if frm >= 0 else 0
        for k in range(4): P(mem, 0x80000000 + FTAB + 4 * k, 'I', rng.choice([rng.randrange(0, 0x2000), 0x80123450]))
        if frm < 0: P(mem, s + 0x88, 'h', rng.randrange(0, 4) << 8)
        tex = None
    else:
        tex = rng.choice([rng.randrange(0, 0x2000), 0x80123450, rng.randrange(-0x8000, 0x8000) & 0xFFFFFFFF])
        P(mem, SPR, 'I', tex)
    t5e4 = rng.choice([tex if tex is not None else 0, rng.randrange(0, 0x2000)]) & 0xFFFF
    t5e8 = rng.choice([0, (frm >> 8) & 0xFFFF, rng.getrandbits(16)])
    for a in addrs['D_800DD5E4']: P(mem, a, 'HH', t5e4, rng.getrandbits(16))
    for a in addrs['D_800DD5E8']: P(mem, a, 'HH', t5e8, rng.getrandbits(16))
    for k, vals in (('D_800DD5EE', [0, 1, 2, 4, 5, 6, 3]), ('D_800DD5EC', [1, 2, 3, 0]),
                    ('D_800DD5F6', [mem[phys(s + 0xA4)], 0, 0xFF, -1])):
        v = rng.choice(vals)
        for a in addrs[k]: P(mem, a, 'h', v)
    for a in addrs['D_800D30BC']: P(mem, a, 'I', rng.choice([0, 0x8000, rng.getrandbits(32)]))
    yaw = rng.uniform(0, 6.283)
    import math
    for a in addrs['D_800DD600']: P(mem, a, 'ff', math.sin(yaw), math.cos(yaw))
    for a in addrs['D_800BE9C0']: mem[phys(a)] = rng.choice([0, 1, 1, 0, -1, 2]) & 0xFF
    idx = rng.randrange(0, 4)
    for a in addrs['D_800DBFF0']: P(mem, a + idx * 0x9A0 + 0x5F0, 'I', rng.choice([0, 1, rng.getrandbits(32)]))
    return [GFX, REC, idx]

def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 500
    seed = int(sys.argv[2]) if len(sys.argv) > 2 else 1
    R, C = 'build/conker.eu.elf', os.environ.get('NM_ELF', 'build_nm/conker.eu.elf')
    ref, cand = Ref(R), Cand(C, R)
    sr, sc = syms(R), syms(C)
    names = ['D_8008CDEC', 'D_800DD5E4', 'D_800DD5E8', 'D_800DD5EE', 'D_800DD5EC', 'D_800DD5F6', 'D_800D30BC',
             'D_800DD600', 'D_800BE9C0', 'D_800DBFF0']
    addrs = {k: sorted({sr[k], sc[k]}) for k in names}
    base = bytearray(RAM)
    for v, bb in cand.data(): base[V.phys(v):V.phys(v) + len(bb)] = bb
    # .nm_rodata is NOBITS in the NM ELF (zeros here): C under test must not use switch jump tables
    from elftools.elf.elffile import ELFFile
    with open(C, 'rb') as fh:
        sec = ELFFile(fh).get_section_by_name('.nm_rodata')
        base[V.phys(sec['sh_addr']):V.phys(sec['sh_addr']) + sec['sh_size']] = sec.data()
    ref.stubs = {sr[k]: k for k in CALLEES}
    # candidate trampolines (no code hooks: Unicorn 2.0.1 mis-runs a hooked callee entered from a jal with an FPU
    # delay slot). Each logs (id, a0..a3, sp+0x10..0x1C) at SCRATCH + 0x100 + n * 0x40 (n = call number, counter at
    # SCRATCH) and returns f0 / v0 from SCRATCH + 0x800 + n * 0x40 (func_15095380: v0 = a0 + 0x28).
    def tramp(k):
        w = [0x3C01807F, 0x8C380000, 0x0018C980, 0x0321C821, 0x27180001, 0xAC380000, 0x240F0000 | k,
             0xAF2F0100, 0xAF240104, 0xAF250108, 0xAF26010C, 0xAF270110]
        for o in range(4): w += [0x8FAF0010 + 4 * o, 0xAF2F0114 + 4 * o]
        w += [0xC7200800, 0x8F220804]
        if k == 2: w += [0x24820028]
        w += [0x03E00008, 0]
        return struct.pack('>%dI' % len(w), *w)
    mu = cand.mu
    for i, k in enumerate(CALLEES): mu.mem_write(sc[k], tramp(i))
    bad = 0; st = {}
    for t in range(n):
        res = []
        for who in ('ref', 'cand'):
            rng = random.Random(seed * 100003 + t)
            mem = bytearray(base)
            args = case(rng, mem, addrs)
            log = Log(seed * 100003 + t)
            if who == 'ref':
                ref.stub = log.stub
                v0 = ref.run(mem, args, entry='func_150A6D40')
            else:
                for c in range(8):
                    vv, ff = Log(seed * 100003 + t).val(c)
                    P(mem, SCRATCH + 0x800 + 0x40 * c, 'II', ff, vv)
                mu.mem_write(0x10000000, bytes(mem[FTAB:FTAB + 0x10000]))
                v0 = cand.run(mem, args, entry='func_150A6D40')
                o = V.phys(SCRATCH)
                for c in range(struct.unpack('>I', mem[o:o + 4])[0]):
                    e = struct.unpack('>9I', mem[o + 0x100 + 0x40 * c:o + 0x124 + 0x40 * c])
                    nm = CALLEES[e[0]]
                    log.calls.append((nm, list(e[1:5]) if nm == 'func_15095380' else [e[1]], list(e[5:9]) if nm == 'func_15095380' else []))
            mem[V.phys(SCRATCH):V.phys(SCRATCH) + 0x1000] = bytes(0x1000)
            mem[V.phys(SP0) - 0x1000:V.phys(SP0) + 0x100] = bytes(0x1100)
            res.append((v0, mem, log.calls))
        k = ((res[0][0] - GFX) // 8, len(res[0][2]))
        st[k] = st.get(k, 0) + 1
        if res[0][0] != res[1][0] or res[0][1] != res[1][1] or res[0][2] != res[1][2]:
            bad += 1
            if bad <= 5:
                d = next((i for i in range(RAM) if res[0][1][i] != res[1][1][i]), None)
                print('DIFF trial %d: v0 ref %08X cand %08X, first byte %s, calls %s / %s' %
                      (t, res[0][0], res[1][0], d if d is None else hex(d), res[0][2], res[1][2]))
    print('%s func_150A6D40: %d differences in %d trials, (gfx words, calls) %d kinds' % ('EQUIV' if bad == 0 else 'DIFFER', bad, n, len(st)))
    print(' ', dict(sorted(st.items())[:30]))

if __name__ == '__main__':
    main()
