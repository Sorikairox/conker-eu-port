#!/usr/bin/env python3
"""P62: rom_read_direct (init_4470, blocking cartridge read through KSEG1) asm vs its NON_MATCHING C.
Both sides run in Unicorn MIPS32 (the asm is plain mips2 code): reference = .init of build/conker.eu.elf (EU
0x10004A5C), candidate = .init of build_nm/conker.eu.elf. Emulated hardware: PI_STATUS (0xA4600010) reads 0 (idle),
a fake cartridge of random bytes at physical 0x10200000 (read as 0xB0200000 + off), D_80000308 = 0x10000000 (ROM
base, ORed in), D_8003A8D3 = 0 (no waiting), D_8003A8D5 random (osStartThread is hooked and its a0 recorded).
Inputs: devAddr = 0x00200000 + off (word- or halfword-aligned; odd faults on both sides), size 1..0x120 (biased to small and to
size & 2), dramAddr word-aligned (and halfword-aligned on the devAddr & 2 path, which only stores halfwords).
Not tested: rounded size 0 (both, and 2 on the devAddr & 2 path): the copy loop's end is size - 2 compared unsigned,
so it runs over all memory in the asm and the C alike.
Compared: all RDRAM outside the stack page, the osStartThread calls, s0-s7 / sp.
Run in the container from /conker/conker: python3 ../tools/port/difftest/pi480C.py [N] [seed]"""
import sys, os, random, struct
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from nmasm_vr import section, syms, base_image, phys, RAM
from unicorn import Uc, UC_ARCH_MIPS, UC_MODE_MIPS32, UC_MODE_BIG_ENDIAN, UC_PROT_ALL, UC_HOOK_CODE
from unicorn.mips_const import *

RET, SP0 = 0x153F0000, 0x807FE000
ROMP = 0x10200000

class Side:
    def __init__(self, elf, entry=None):
        s = syms(elf)
        self.entry = entry or s['rom_read_direct']
        self.ost = s['osStartThread']
        self.init = section(elf, '.init')
    def run(self, mem, rom, a):
        mu = Uc(UC_ARCH_MIPS, UC_MODE_MIPS32 | UC_MODE_BIG_ENDIAN)
        mu.mem_map(0, RAM, UC_PROT_ALL)
        mu.mem_map(0x04600000, 0x1000, UC_PROT_ALL)
        mu.mem_map(0x10000000, 0x400000, UC_PROT_ALL)
        mu.mem_map(0x15000000, 0x400000, UC_PROT_ALL)
        v, b = self.init; mu.mem_write(v, b)
        mu.mem_write(ROMP, bytes(rom))
        mu.mem_write(0, bytes(mem))
        calls = []
        def hk(uc, addr, size, ud):
            if addr == self.ost:
                calls.append(uc.reg_read(UC_MIPS_REG_A0))
                uc.reg_write(UC_MIPS_REG_PC, uc.reg_read(UC_MIPS_REG_RA))
        mu.hook_add(UC_HOOK_CODE, hk, begin=self.ost, end=self.ost + 4)
        for k, v in enumerate(a): mu.reg_write(UC_MIPS_REG_A0 + k, v)
        for i in range(8): mu.reg_write(UC_MIPS_REG_S0 + i, 0x1000 * (i + 1) + 0x11)
        mu.reg_write(UC_MIPS_REG_SP, SP0); mu.reg_write(UC_MIPS_REG_RA, RET)
        mu.emu_start(self.entry, RET, count=2000000)
        if mu.reg_read(UC_MIPS_REG_PC) != RET: raise RuntimeError('timeout at %08X' % mu.reg_read(UC_MIPS_REG_PC))
        regs = [mu.reg_read(UC_MIPS_REG_S0 + i) for i in range(8)] + [mu.reg_read(UC_MIPS_REG_SP)]
        return bytearray(mu.mem_read(0, RAM)), calls, regs

def main():
    args = [x for x in sys.argv[1:] if not x.startswith('--')]
    n = int(args[0]) if args else 1000
    rng = random.Random(int(args[1]) if len(args) > 1 else 1)
    ref = Side('build/conker.eu.elf', 0x10004A5C)
    cand = Side('build_nm/conker.eu.elf')
    base = base_image()
    struct.pack_into('>I', base, 0x308, 0x10000000)
    base[phys(0x8003A8D3)] = 0
    rom = bytes(rng.randrange(256) for _ in range(0x10000))
    bad = 0; hist = {}
    for t in range(n):
        mem = bytearray(base)
        off = rng.randrange(0, 0xF000)
        k = rng.random()
        off = off & ~3 | (2 if k < 0.5 else 0)
        size = rng.choice([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 16]) if rng.random() < 0.4 else rng.randint(1, 0x120)
        rs = (size + 1) & ~1
        if rs == 0 or (((0x00200000 + off) & 2) and rs == 2): continue
        dst = 0x80500000 + 4 * rng.randrange(0, 0x100)
        if (off & 2) and rng.random() < 0.5: dst += 2
        for i in range(0x600): mem[phys(0x80500000) + i] = (0xA5 + 3 * i) & 0xFF
        mem[phys(0x8003A8D5)] = rng.choice([0, 0, 1, 0x80])
        mem[phys(0x8003A8D2)] = rng.choice([0, 7])
        a = (0x00200000 + off, dst, size)
        m1, c1, g1 = ref.run(mem, rom, a)
        m2, c2, g2 = cand.run(mem, rom, a)
        lo, hi = phys(SP0) - 0x400, phys(SP0) + 0x100
        d = [0x80000000 + i for i in range(RAM) if m1[i] != m2[i] and not lo <= i < hi][:8] if m1 != m2 else []
        key = ('half' if (off & 2) else 'word') + ('+tail' if rs & 2 else '')
        hist[key] = hist.get(key, 0) + 1
        if d or c1 != c2 or g1 != g2:
            bad += 1
            if bad <= 6: print('DIFF', t, hex(a[0]), hex(dst), size, [hex(x) for x in d], c1, c2, g1 == g2)
    print('rom_read_direct trials', sum(hist.values()), 'diffs', bad, hist)

if __name__ == '__main__':
    main()
