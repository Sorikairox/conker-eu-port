#!/usr/bin/env python3
"""P22: compare func_150AB278 (hand asm in asm/D5E90.s, build/conker.eu.elf) with its NON_MATCHING C
(src_eu/nm_asm/D5E90.c, build_nm/conker.eu.elf) in Unicorn. The asm uses private register conventions
between its helpers, so difftest (which stubs every callee) cannot test it; here both run whole.
Inputs: box half extents + diagonal ratios (D_800CC64C..5C), 9 vertex floats (a0-a3 + 5 stack words).
Outputs compared: v0, and the plane D_800CC630..3C. Run in the container from /conker/conker."""
import struct, subprocess, random, sys
from unicorn import Uc, UC_ARCH_MIPS, UC_MODE_MIPS32, UC_MODE_BIG_ENDIAN, UC_PROT_ALL
from unicorn.mips_const import *

def section(elf, name):
    out = '/tmp/p22_%s_%s.bin' % (elf.replace('/', '_'), name)
    subprocess.check_call(['mips-linux-gnu-objcopy', '-O', 'binary', '-j', name, elf, out])
    h = subprocess.check_output(['mips-linux-gnu-objdump', '-h', elf]).decode()
    for l in h.split('\n'):
        f = l.split()
        if len(f) > 3 and f[1] == name: return int(f[3], 16), open(out, 'rb').read()

def sym(elf, s):
    for l in subprocess.check_output(['mips-linux-gnu-nm', elf]).decode().split('\n'):
        f = l.split()
        if len(f) == 3 and f[2] == s and f[1] in 'Tt': return int(f[0], 16)

def phys(a): return a & 0x1FFFFFFF if 0x80000000 <= a < 0xC0000000 else a
f2w = lambda x: struct.unpack('>I', struct.pack('>f', x))[0]

class Img:
    def __init__(self, elf, data_from=None):
        # P24: the NM build's .game_data moved (absolute D_ symbols such as D_8009FAB0 point into other data),
        # so the candidate runs on the reference's data image
        self.secs = [section(data_from if (data_from and n == '.game_data') else elf, n)
                     for n in ('.game', '.game_data', '.nm_rodata') if n != '.nm_rodata' or 'build_nm' in elf]
        self.entry = sym(elf, 'func_150AB278')
    def run(self, box, verts):
        mu = Uc(UC_ARCH_MIPS, UC_MODE_MIPS32 | UC_MODE_BIG_ENDIAN)
        mu.mem_map(0x15000000, 0x400000, UC_PROT_ALL)
        mu.mem_map(0x00000000 + 0x80000, 0x800000 - 0x80000, UC_PROT_ALL)   # kseg0 0x80080000..0x80800000
        for v, b in self.secs: mu.mem_write(phys(v), b)
        for k, x in enumerate(box): mu.mem_write(phys(0x800CC64C + 4 * k), struct.pack('>f', x))
        mu.mem_write(phys(0x800CC630), bytes(16))
        sp = 0x80700000
        mu.reg_write(UC_MIPS_REG_SP, sp)
        for k in range(4): mu.reg_write(UC_MIPS_REG_A0 + k, f2w(verts[k]))
        for k in range(5): mu.mem_write(phys(sp + 0x10 + 4 * k), struct.pack('>f', verts[4 + k]))  # sp+0x10.. of 9 words: a0-a3 homes at 0x0-0xC
        mu.reg_write(UC_MIPS_REG_RA, 0x80790000)
        mu.mem_write(phys(0x80790000), bytes(8))
        mu.reg_write(UC_MIPS_REG_V0, 0xDEAD)
        mu.emu_start(self.entry, 0x80790000, count=200000)
        return mu.reg_read(UC_MIPS_REG_V0), bytes(mu.mem_read(phys(0x800CC630), 16))

ref, cand = Img('build/conker.eu.elf'), Img('build_nm/conker.eu.elf', 'build/conker.eu.elf')
assert ref.entry == 0x150AB278, hex(ref.entry or 0)
rng = random.Random(int(sys.argv[2]) if len(sys.argv) > 2 else 1)
n = int(sys.argv[1]) if len(sys.argv) > 1 else 2000
bad = 0; hist = {}
for t in range(n):
    hx, hy, hz = [rng.choice([1.0, 0.5, 2.0, rng.uniform(0.2, 3)]) for _ in range(3)]
    box = [hx, hy, hz, hy / hx, hz / hx]
    sc = rng.choice([1.5, 3, 6, 20])
    verts = [rng.uniform(-sc, sc) for _ in range(9)]
    if rng.random() < 0.2:      # a big triangle through the box
        c = [rng.uniform(-hx, hx), rng.uniform(-hy, hy), rng.uniform(-hz, hz)]
        verts = [c[i % 3] + rng.uniform(-30, 30) for i in range(9)]
    r, c = ref.run(box, verts), cand.run(box, verts)
    key = (r[0], r[1] != bytes(16))
    hist[key] = hist.get(key, 0) + 1
    if r != c:
        bad += 1
        if bad <= 5: print('DIFF', t, box, verts, r, c)
print('trials', n, 'diffs', bad, 'outcomes(v0, plane written)', hist)
