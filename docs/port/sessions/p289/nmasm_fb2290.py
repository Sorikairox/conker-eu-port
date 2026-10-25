#!/usr/bin/env python3
"""P289: func_150B2290 (hand asm, 64-bit ld/sd: Unicorn MIPS32 cannot run it) vs its NON_MATCHING C.
Reference = a Python model of the asm, instruction by instruction (ld/and/dsll/dsrl/or/sd on two doublewords per
16-byte step, do-while with a signed slt on the pointers), with the masks read from the reference ELF's data
(D_8009FCA0 / D_8009FCA8) and the reference's instruction words checked against the asm listing first.
Candidate = the NM build's compiled C, run whole in Unicorn on the same buffer. The whole buffer + 64 guard bytes
after it are compared. Run in the container from /conker/conker: python3 ../docs/port/sessions/p289/nmasm_fb2290.py [N] [seed]"""
import struct, subprocess, random, sys, re, os
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '../../../../port_work/pyuc201'))  # pinned Unicorn 2.0.1
from unicorn import Uc, UC_ARCH_MIPS, UC_MODE_MIPS32, UC_MODE_BIG_ENDIAN, UC_PROT_ALL
from unicorn.mips_const import *

def section(elf, name):
    out = '/tmp/p289_%s_%s.bin' % (elf.replace('/', '_'), name)
    subprocess.check_call(['mips-linux-gnu-objcopy', '-O', 'binary', '-j', name, elf, out])
    for l in subprocess.check_output(['mips-linux-gnu-objdump', '-h', elf]).decode().split('\n'):
        f = l.split()
        if len(f) > 3 and f[1] == name: return int(f[3], 16), open(out, 'rb').read()
def syms(elf):
    d = {}
    for l in subprocess.check_output(['mips-linux-gnu-nm', elf]).decode().split('\n'):
        f = l.split()
        if len(f) == 3: d[f[2]] = int(f[0], 16)
    return d
phys = lambda a: a & 0x1FFFFFFF if 0x80000000 <= a < 0xC0000000 else a
def rd(secs, addr, n):
    for v, b in secs:
        if v <= addr < v + len(b): return b[addr - v:addr - v + n]
    raise KeyError(hex(addr))

REF, CAND = 'build/conker.eu.elf', 'build_nm/conker.eu.elf'
rs, cs = syms(REF), syms(CAND)
rsec = [section(REF, n) for n in ('.game', '.game_data')]
csec = [section(CAND, n) for n in ('.game', '.game_data')]
# the reference words must be the listing's (the model below transcribes exactly these 28 instructions)
lst = [int(m, 16) for m in re.findall(r'/\* \w+ \w+ ([0-9A-F]{8}) \*/', open('asm/nonmatchings/game_eu_DFAA0/func_150B2290.s').read())]
ra = rs['func_150B2290']
assert ra == 0x150B2290 and struct.unpack('>28I', rd(rsec, ra, 112)) == tuple(lst[:28]), 'reference words differ from the listing'
assert cs['func_150B2290'] != ra or rd(csec, cs['func_150B2290'], 112) != rd(rsec, ra, 112), 'NM build still has the asm'
M1 = struct.unpack('>Q', rd(rsec, rs['D_8009FCA0'], 8))[0]
M2 = struct.unpack('>Q', rd(rsec, rs['D_8009FCA8'], 8))[0]
assert (M1, M2) == (0x07C007C007C007C0, 0x07C107C107C107C1), (hex(M1), hex(M2))
U64 = (1 << 64) - 1
def s32(x): return x - (1 << 32) if x & 0x80000000 else x

def model(mem, base, a0, a1):
    """the asm on bytearray mem (mem[0] = address base)"""
    t1, t6 = M1, M2
    while True:
        o = a0 - base
        t2, t3 = struct.unpack('>QQ', bytes(mem[o:o + 16]))
        t7 = t2 & t6; t2 = t2 & t1; t4 = (t2 << 5) & U64; t4 = t7 | t4; t2 = t2 >> 5; t2 = t2 | t4
        t8 = t3 & t6; t3 = t3 & t1; t5 = (t3 << 5) & U64; t5 = t8 | t5; t3 = t3 >> 5; t3 = t3 | t5
        mem[o:o + 16] = struct.pack('>QQ', t2, t3)
        a0 = (a0 + 0x10) & 0xFFFFFFFF
        if not s32(a0) < s32(a1): break

BUF, TR, SP = 0x80400000, 0x153F0000, 0x80700000
cmu = Uc(UC_ARCH_MIPS, UC_MODE_MIPS32 | UC_MODE_BIG_ENDIAN)
cmu.mem_map(0x15000000, 0x400000, UC_PROT_ALL)
cmu.mem_map(0x80000, 0x800000 - 0x80000, UC_PROT_ALL)
for v, b in csec: cmu.mem_write(phys(v), b)
ct = cs['func_150B2290']
cmu.mem_write(TR, struct.pack('>4I', 0x0C000000 | ((ct >> 2) & 0x3FFFFFF), 0, 0, 0))
rng = random.Random(int(sys.argv[2]) if len(sys.argv) > 2 else 1)
n = int(sys.argv[1]) if len(sys.argv) > 1 else 300
bad = 0; cls = {}
for t in range(n):
    span = rng.choice([16, 32, 48, 160, 0x1ECC0, rng.randrange(1, 40) * 16, rng.randrange(1, 600), 0, -32])
    off = rng.randrange(0, 64) * 8
    a0 = BUF + off; a1 = (a0 + span) & 0xFFFFFFFF
    steps = max(1, -(-span // 16)) if span > 0 else 1
    size = steps * 16 + 64
    kind = rng.choice(['rand', 'ones', 'zero', 'pix'])
    data = bytes(rng.getrandbits(8) for _ in range(min(size, 4096)))
    if kind == 'ones': data = b'\xff' * size
    elif kind == 'zero': data = bytes(size)
    data = (data * (size // len(data) + 1))[:size] if data else bytes(size)
    ref = bytearray(data); model(ref, a0, a0, a1)
    cmu.mem_write(phys(a0), data)
    cmu.reg_write(UC_MIPS_REG_A0, a0); cmu.reg_write(UC_MIPS_REG_A1, a1); cmu.reg_write(UC_MIPS_REG_SP, SP)
    cmu.emu_start(TR, TR + 8, count=5000000)
    got = bytes(cmu.mem_read(phys(a0), size))
    c = 'span%s' % ('neg' if span <= 0 else '16k' if span % 16 == 0 else 'odd'); cls[c] = cls.get(c, 0) + 1
    if got != bytes(ref):
        bad += 1
        if bad <= 5:
            i = next(k for k in range(size) if got[k] != ref[k])
            print('DIFF trial %d span %d off %d: first byte %d ref %s cand %s' % (t, span, off, i, bytes(ref[i:i+8]).hex(), got[i:i+8].hex()))
print('%s: %d trials, %d differences, classes %s' % ('EQUIV' if bad == 0 else 'DIFFER', n, bad, cls))
