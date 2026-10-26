#!/usr/bin/env python3
"""P24: compare func_150AD78C (sinf) / func_150AD780 (cosf) and mtxf_rotate_xyz_deg (rotation matrix) between the hand asm
(build/conker.eu.elf) and the NON_MATCHING C (build_nm/conker.eu.elf), whole, in Unicorn: a small trampoline
loads f12 from memory (Unicorn 2.0.1 ignores FPR reg_write), calls the function and stores f0 back.
Run in the container from /conker/conker after both builds: python3 ../tools/port/difftest/nmasm_sincos.py [N] [seed]"""
import struct, subprocess, random, sys, math
from unicorn import Uc, UC_ARCH_MIPS, UC_MODE_MIPS32, UC_MODE_BIG_ENDIAN, UC_PROT_ALL
from unicorn.mips_const import *

def section(elf, name):
    out = '/tmp/p24_%s_%s.bin' % (elf.replace('/', '_'), name)
    subprocess.check_call(['mips-linux-gnu-objcopy', '-O', 'binary', '-j', name, elf, out])
    h = subprocess.check_output(['mips-linux-gnu-objdump', '-h', elf]).decode()
    for l in h.split('\n'):
        f = l.split()
        if len(f) > 3 and f[1] == name: return int(f[3], 16), open(out, 'rb').read()

def syms(elf):
    d = {}
    for l in subprocess.check_output(['mips-linux-gnu-nm', elf]).decode().split('\n'):
        f = l.split()
        if len(f) == 3 and f[1] in 'TtWw': d[f[2]] = int(f[0], 16)
    return d

phys = lambda a: a & 0x1FFFFFFF if 0x80000000 <= a < 0xC0000000 else a
f2w = lambda x: struct.unpack('>I', struct.pack('>f', x))[0]
SCR, TRAMP = 0x80780000, 0x153F0000   # TRAMP in the jal region of the targets

class Img:
    def __init__(self, elf, data_from=None):
        # the NM build's .game_data is not address-stable (absolute D_ symbols point into moved data), so the
        # candidate runs on the reference's data image (same as the browser's symbolized data)
        self.secs = [section(data_from if (data_from and n == '.game_data') else elf, n)
                     for n in ('.game', '.game_data', '.nm_rodata') if n != '.nm_rodata' or 'build_nm' in elf]
        self.s = syms(elf); self.tramp = {}
    def mu(self):
        mu = Uc(UC_ARCH_MIPS, UC_MODE_MIPS32 | UC_MODE_BIG_ENDIAN)
        mu.mem_map(0x15000000, 0x400000, UC_PROT_ALL)
        mu.mem_map(0x80000, 0x800000 - 0x80000, UC_PROT_ALL)
        for v, b in self.secs: mu.mem_write(phys(v), b)
        mu.reg_write(UC_MIPS_REG_SP, 0x80700000)
        return mu
    def call(self, mu, fn, fl):
        """f12 = fl[0]; a0 = SCR+0x100, a1..a3 = float bits of fl[1:] (mtxf_rotate_xyz_deg's o32 layout); returns f0 bits"""
        mu.mem_write(phys(SCR), struct.pack('>I', fl[0]))
        for k, w in enumerate(fl[1:]): mu.reg_write(UC_MIPS_REG_A1 + k, w)
        mu.reg_write(UC_MIPS_REG_A0, SCR + 0x100)
        tgt = self.s[fn]
        # one trampoline per target: Unicorn caches translated blocks, rewriting the same address is not seen
        tr = self.tramp.setdefault(fn, TRAMP + 0x40 * len(self.tramp))
        code = [0x3C108078, 0xC60C0000, 0x0C000000 | ((tgt >> 2) & 0x3FFFFFF), 0, 0xE6000004, 0, 0]
        mu.mem_write(tr, b''.join(struct.pack('>I', w) for w in code))
        mu.emu_start(tr, tr + 0x14, count=100000)
        return struct.unpack('>I', bytes(mu.mem_read(phys(SCR + 4), 4)))[0]

ref, cand = Img('build/conker.eu.elf'), Img('build_nm/conker.eu.elf', 'build/conker.eu.elf')
assert ref.s['func_150AD780'] == 0x150ADC60 and ref.s['func_150AD78C'] == 0x150ADC6C, 'unexpected asm addresses'
assert cand.s['func_150AD78C'] != ref.s['func_150AD78C'], 'NM build still uses the asm (weaken failed?)'
rng = random.Random(int(sys.argv[2]) if len(sys.argv) > 2 else 1)
n = int(sys.argv[1]) if len(sys.argv) > 1 else 3000
mr, mc = ref.mu(), cand.mu()
bad = 0; cls = {}
specials = [0.0, -0.0, 1e-5, 1.5, 1.4999, math.pi, -math.pi, math.pi / 2, 1e9, 3e8, 2.0 ** 28, float('inf'), float('nan'), 1e-30]
for t in range(n):
    if t < len(specials): x = specials[t]
    else:
        x = rng.choice([rng.uniform(-1.6, 1.6), rng.uniform(-10, 10), rng.uniform(-1000, 1000), rng.uniform(-1e6, 1e6),
                        rng.uniform(-3e8, 3e8), rng.uniform(-1e-3, 1e-3), (rng.randrange(-200, 200) + 0.5) * math.pi])
    for fn in ('func_150AD78C', 'func_150AD780'):
        a, b = ref.call(mr, fn, [f2w(x)]), cand.call(mc, fn, [f2w(x)])
        e = (f2w(x) >> 22) & 0x1FF; c = 'tiny' if e < 0xE6 else 'poly' if e < 0xFF else 'zero' if e >= 0x136 else 'reduce'
        cls[c] = cls.get(c, 0) + 1
        if a != b:
            bad += 1
            if bad <= 10: print('DIFF %s(%r): ref %08X cand %08X' % (fn, x, a, b))
# mtxf_rotate_xyz_deg: whole (it calls the sin/cos above), 16 output words
for t in range(n // 4):
    ang = [f2w(rng.uniform(-720, 720)) for _ in range(3)]
    outs = []
    for img, mu in ((ref, mr), (cand, mc)):
        mu.mem_write(phys(SCR + 0x100), bytes(64))
        img.call(mu, 'mtxf_rotate_xyz_deg', [0] + ang)
        outs.append(bytes(mu.mem_read(phys(SCR + 0x100), 64)))
    cls['mtx'] = cls.get('mtx', 0) + 1
    if outs[0] != outs[1]:
        bad += 1
        if bad <= 10: print('DIFF mtxf_rotate_xyz_deg angles %s' % ang)
print('%s: %d calls, %d differences, classes %s' % ('EQUIV' if bad == 0 else 'DIFFER', sum(cls.values()), bad, cls))
