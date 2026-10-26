#!/usr/bin/env python3
"""P28: compare the hand-asm blob world_objects_transform_mesh.s (entry points world_objects_transform_mesh and func_150A4ED4; reference build
build/conker.eu.elf, with the asm sin/cos) with the NON_MATCHING C (build_nm/conker.eu.elf, C sin/cos), whole, in
Unicorn. difftest cannot do this: the asm keeps values in f1-f13 across its sin/cos calls (the hand-written sin/cos
leave them alone) and difftest's stubs return random f2.
allocate_memory / heap_free (free) are hooked in both images. Random scenes: objects at 0x80400000 (D_800DBEF4),
both transform paths (kind 0xFF = D_800DC338 matrix, else rotation/scale/translation), cached vertices (flags70 & 1),
force on/off, flags6F & 0x80, per-triangle bounds. Compared: 0x80400000-0x80600000 and 0x800DBE00-0x800DC400.
Run in the container from /conker/conker after both builds: python3 ../tools/port/difftest/nmasm_blob49D0.py [N] [seed]"""
import struct, random, sys, os
from unicorn import Uc, UC_ARCH_MIPS, UC_MODE_MIPS32, UC_MODE_BIG_ENDIAN, UC_PROT_ALL, UC_HOOK_CODE
from unicorn.mips_const import *
import subprocess

def section(elf, name):
    out = '/tmp/p28_%s_%s.bin' % (elf.replace('/', '_'), name)
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

f2b = lambda x: struct.pack('>f', x)
RET = 0x153F0000      # magic return address (mapped, never executed)
ALLOC0 = 0x80500000   # allocate_memory hands out 0x800-byte zeroed blocks from here
W = lambda mu, a, fmt, *v: mu.mem_write(phys(a), struct.pack('>' + fmt, *v))

class Img:
    def __init__(self, elf, data_from=None):
        self.secs = [section(data_from if (data_from and n == '.game_data') else elf, n)
                     for n in ('.game', '.game_data', '.nm_rodata') if n != '.nm_rodata' or 'build_nm' in elf]
        self.s = syms(elf)
    def mu(self):
        mu = Uc(UC_ARCH_MIPS, UC_MODE_MIPS32 | UC_MODE_BIG_ENDIAN)
        mu.mem_map(0x15000000, 0x400000, UC_PROT_ALL)
        mu.mem_map(0x80000, 0x800000 - 0x80000, UC_PROT_ALL)   # not page 0 (P18 Unicorn TLB bug)
        mu.mem_map(0x10000000, 0x100000, UC_PROT_ALL)
        for v, b in self.secs: mu.mem_write(phys(v), b)
        self.log = []
        def alloc(mu, addr, size, ud):
            n = len([l for l in self.log if l[0] == 'A'])
            a0 = mu.reg_read(UC_MIPS_REG_A0)
            self.log.append(('A', a0, mu.reg_read(UC_MIPS_REG_A1), mu.reg_read(UC_MIPS_REG_A2), mu.reg_read(UC_MIPS_REG_A3)))
            p = ALLOC0 + 0x800 * n if self.fail_alloc != n else 0
            if p: mu.mem_write(phys(p), bytes(0x800))
            mu.reg_write(UC_MIPS_REG_V0, p)
        def free(mu, addr, size, ud):
            self.log.append(('F', mu.reg_read(UC_MIPS_REG_A0)))
        for name, cb in (('allocate_memory', alloc), ('heap_free', free)):
            # the hook only sets v0 / logs; the stub `jr $ra; nop` returns (writing PC in a hook crashes Unicorn)
            a = self.s[name]; mu.mem_write(a, struct.pack('>II', 0x03E00008, 0)); mu.hook_add(UC_HOOK_CODE, cb, begin=a, end=a)
        return mu
    def run(self, mu, fn, args):
        for k, v in enumerate(args): mu.reg_write(UC_MIPS_REG_A0 + k, v & 0xFFFFFFFF)
        mu.reg_write(UC_MIPS_REG_SP, 0x806FF000); mu.reg_write(UC_MIPS_REG_RA, RET)
        try:
            mu.emu_start(self.s[fn], RET, count=2000000)
            return 'ok' if mu.reg_read(UC_MIPS_REG_PC) == RET else 'timeout'
        except Exception as e:
            return 'fault'

def scene(rng, mu):
    """writes a random scene into mu; returns (count, ids ptr, force)"""
    mu.mem_write(0x400000, bytes(0x100000))
    nobj = rng.randrange(1, 6)
    W(mu, 0x800BEDE0, 'B', rng.randrange(2))                     # D_800BE9C0 (frame buffer)
    W(mu, 0x800DC324, 'I', 0x80400000)                           # D_800DBEF4 objects
    W(mu, 0x800DC328, 'I', 0x80410000)                           # D_800DC328 slots
    W(mu, 0x800DC32C, 'I', 0x80418000)                           # D_800DC32C flags
    W(mu, 0x800DC26C, 'I', 0x80420000)                           # D_800DC26C tri vertex offsets
    W(mu, 0x800DC270, 'I', 0x80430000)                           # D_800DC270 xz bounds
    W(mu, 0x800DC274, 'I', 0x80438000)                           # D_800DC274 y bounds
    for k in range(32): W(mu, 0x800DC338 + 4 * k, 'f', rng.uniform(-3, 3) if k % 4 != 3 else rng.uniform(-500, 500))
    for t in range(64 * 3): W(mu, 0x80420000 + 4 * t, 'I', 16 * rng.randrange(8))
    for i in range(nobj):
        o = 0x80400000 + 0xA0 * i
        mu.mem_write(phys(o), bytes(rng.getrandbits(8) for _ in range(0xA0)))
        nv = rng.randrange(1, 9)
        for k in range(3): W(mu, o + 4 * k, 'f', rng.choice([rng.uniform(-720, 720), 0.0, 90.0, 180.0, -45.0]))
        for k in range(3): W(mu, o + 0x10 + 2 * k, 'h', rng.randrange(-3000, 3000))
        W(mu, o + 0x16, 'H', nv)
        W(mu, o + 0x18, 'f', rng.uniform(-100, 100))
        W(mu, o + 0x20, 'II', 0x80480000 + 0x200 * i, 0x80490000 + 0x200 * i)
        W(mu, o + 0x28, 'I', 0x80440000 + 0x1000 * i)
        for k in range(3): W(mu, o + 0x2C + 4 * k, 'f', rng.choice([1.0, rng.uniform(0.25, 3.0)]))
        W(mu, o + 0x4E, 'B', rng.choice([0xFF, 3, 0, 7]))
        W(mu, o + 0x56, 'HH', rng.randrange(1, 5), rng.randrange(0, 40))
        W(mu, o + 0x6F, 'BB', rng.choice([0, 0x80, 0x7F]), rng.choice([0, 1, 0xFE]))
        for k in range(nv * 8): W(mu, 0x80440000 + 0x1000 * i + 2 * k, 'h', rng.randrange(-2000, 2000))
        for c in (0x80480000, 0x80490000):
            for k in range(0x100): W(mu, c + 0x200 * i + 2 * k, 'h', rng.randrange(-2000, 2000))
        if rng.random() < 0.15: W(mu, 0x80410000 + 4 * i, 'I', 0x80470000)   # slot already set: skipped
    ids = [rng.randrange(nobj) for _ in range(rng.randrange(1, 6))]
    for k, v in enumerate(ids): W(mu, 0x80460000 + 2 * k, 'H', v)
    return len(ids), 0x80460000, rng.choice([0, 0, 1])

def dump(mu):
    return bytes(mu.mem_read(0x400000, 0x200000)) + bytes(mu.mem_read(phys(0x800DBE00), 0x600))

ref, cand = Img('build/conker.eu.elf'), Img('build_nm/conker.eu.elf', 'build/conker.eu.elf')
n = int(sys.argv[1]) if len(sys.argv) > 1 else 500
seed = int(sys.argv[2]) if len(sys.argv) > 2 else 1
bad = 0; stats = {'49D0': 0, '4ED4': 0, 'allocfail': 0}
mr, mc = ref.mu(), cand.mu()
for t in range(n):
    outs = []
    fail = random.Random(seed * 7919 + t).choice([-1] * 9 + [0])
    for img, mu in ((ref, mr), (cand, mc)):
        rng = random.Random(seed * 100003 + t)
        img.log = []; img.fail_alloc = fail
        args = scene(rng, mu)
        r = img.run(mu, 'world_objects_transform_mesh', args)
        outs.append((dump(mu), img.log, r))
    stats[outs[0][2]] = stats.get(outs[0][2], 0) + 1
    stats['49D0'] += 1; stats['allocfail'] += fail == 0
    if outs[0] != outs[1]:
        bad += 1
        if bad <= 5:
            d = next((i for i in range(len(outs[0][0])) if outs[0][0][i] != outs[1][0][i]), None)
            print('DIFF world_objects_transform_mesh trial %d: first byte %s, logs equal %s, ref %s cand %s' % (
                t, d if d is None else hex(d), outs[0][1] == outs[1][1], outs[0][2], outs[1][2]))
# func_150A4ED4: area tables -> current-area globals
for t in range(n // 5):
    outs = []
    for img, mu in ((ref, mr), (cand, mc)):
        rng = random.Random(seed * 31 + t)
        for base in (0x800DC208, 0x800DC218, 0x800DC228, 0x800DBE08, 0x800DBE18):
            for k in range(4): W(mu, base + 4 * k, 'I', rng.getrandbits(32))
        img.run(mu, 'func_150A4ED4', [rng.randrange(4)])
        outs.append(dump(mu))
    stats['4ED4'] += 1
    if outs[0] != outs[1]:
        bad += 1
        if bad <= 5: print('DIFF func_150A4ED4 trial %d' % t)
print('%s: %d differences, %s' % ('EQUIV' if bad == 0 else 'DIFFER', bad, stats))
