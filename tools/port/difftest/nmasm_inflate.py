#!/usr/bin/env python3
"""P36: compare Rare's inflater (init_eu_5DA0 hand asm: rzip_inflate_impl .. rzip_inflate_codes + rzip_build_fixed_tables, the fixed
table builder) with its NON_MATCHING C, whole, on real packed assets from the ROM.

Both run in Unicorn MIPS32: the reference on build/conker.eu.elf's .init words, the candidate on build_nm's. The
only 64-bit instructions in the asm are the 8 `sd $zero` that clear huft_build's c[] (0x10006C8C..0x10006CA8);
they are patched into a jump to a trampoline of 32-bit stores. Both use the reference .init_data (mask / base / extra tables).

Per trial: RAM is filled with a random pattern (so stale table memory is the same on both sides), the packed
record (BE u32 size + deflate, or the BE halfword 0x1172 + deflate) is placed at src, rzip_build_fixed_tables builds the
fixed tables at D_8003C230, then rzip_inflate_impl(src, dst, work) runs. Compared: v0 and all of RDRAM except the stack.
The reference output is also checked against Python's zlib (raw deflate) and the header size.
Modes per trial (random): normal (work just past the output or far away), 0x1172 header, output limit too small
(error path: v0 = 0, partial output), src above dst (limit = src - dst), corrupted stream (both must agree;
skipped when both fault or time out).

Run in the container from /conker/conker after both builds:
  python3 ../tools/port/difftest/nmasm_inflate.py ASSETS.json ROM [N] [seed]
ASSETS.json: [[rom_offset, size, packed_len], ...] (tools/port/difftest/scan_assets.py ROM 25C000 OUT.json; 5869 found in the EU ROM)."""
import struct, random, sys, os, json, zlib, subprocess
_UC = os.environ.get('DIFFTEST_UNICORN', os.path.join(os.path.dirname(os.path.abspath(__file__)), '../../../port_work/pyuc201'))
if os.path.isdir(_UC): sys.path.insert(0, os.path.abspath(_UC))
from unicorn import Uc, UcError, UC_ARCH_MIPS, UC_MODE_MIPS32, UC_MODE_BIG_ENDIAN, UC_PROT_ALL
from unicorn.mips_const import *

RET = 0x153F0000
SP0 = 0x807FE000
RAM = 0x800000
LOW = 0x1000   # not page 0 (P18 Unicorn TLB bug)
STACK_LO, STACK_HI = SP0 - 0x6000, SP0 + 0x100
phys = lambda a: a & 0x1FFFFFFF


def section(elf, name):
    out = '/tmp/p36_%s_%s.bin' % (elf.replace('/', '_'), name)
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


class Emu:
    def __init__(self, elf, ref_elf, is_ref):
        self.s = syms(elf)
        mu = Uc(UC_ARCH_MIPS, UC_MODE_MIPS32 | UC_MODE_BIG_ENDIAN)
        mu.mem_map(LOW, RAM - LOW, UC_PROT_ALL)
        mu.mem_map(0x10000000, 0x100000, UC_PROT_ALL)
        mu.mem_map(0x15000000, 0x400000, UC_PROT_ALL)
        v, b = section(elf, '.init'); mu.mem_write(v, b)
        self.init_data = section(ref_elf, '.init_data')
        if is_ref:   # 8 x `sd $zero` + `sw $zero, 0x40($sp)` -> j trampoline (17 x sw $zero) -> back to 0x10006CB0
            j = lambda t: struct.pack('>I', (2 << 26) | ((t >> 2) & 0x3FFFFFF))
            mu.mem_write(0x10006C8C, j(0x10080000) + b'\0' * 4)
            mu.mem_write(0x10080000, b''.join(struct.pack('>I', 0xAFA00000 | (4 * k)) for k in range(17)) + j(0x10006CB0) + b'\0' * 4)
        self.mu = mu
        self.last = []
        if os.environ.get('NMINF_TRACE'):
            from unicorn import UC_HOOK_CODE
            def tr(uc, addr, size, ud):
                self.last.append((addr, uc.reg_read(UC_MIPS_REG_RA), uc.reg_read(UC_MIPS_REG_SP)))
                if len(self.last) > 30: del self.last[0]
            mu.hook_add(UC_HOOK_CODE, tr)

    def call(self, fn, args, maxi):
        mu = self.mu
        for k, a in enumerate(args): mu.reg_write(UC_MIPS_REG_A0 + k, a & 0xFFFFFFFF)
        mu.reg_write(UC_MIPS_REG_SP, SP0); mu.reg_write(UC_MIPS_REG_RA, RET); mu.reg_write(UC_MIPS_REG_GP, 0)
        mu.emu_start(self.s[fn], RET, count=maxi)
        if mu.reg_read(UC_MIPS_REG_PC) != RET: raise RuntimeError('timeout')
        return mu.reg_read(UC_MIPS_REG_V0) & 0xFFFFFFFF

    def run(self, mem, src, dst, work, maxi):
        mu = self.mu
        mu.mem_write(LOW, bytes(mem[LOW:RAM]))
        v, b = self.init_data; mu.mem_write(phys(v), b)
        try:
            self.call('rzip_build_fixed_tables', [], 2000000)
            r = self.call('rzip_inflate_impl', [src, dst, work], maxi)
        except (UcError, RuntimeError) as e:
            pc = mu.reg_read(UC_MIPS_REG_PC)
            if self.last: print(' '.join('%08X/%08X/%08X' % x for x in self.last[-8:]))
            return ('fault', '%s at %08X' % (e, pc)), None
        out = mu.mem_read(LOW, RAM - LOW)
        return r, out


def main():
    a = sys.argv[1:]
    assets = json.load(open(a[0])); rom = open(a[1], 'rb').read()
    N = int(a[2]) if len(a) > 2 else 200
    seed = int(a[3]) if len(a) > 3 else 1
    rng = random.Random(seed)
    ref = Emu('build/conker.eu.elf', 'build/conker.eu.elf', True)
    cand = Emu('build_nm/conker.eu.elf', 'build/conker.eu.elf', False)
    assert ref.s['D_8003C230'] == 0x8003C230
    # cover the size range: sort and pick evenly, plus random picks
    srt = sorted(assets, key=lambda x: x[1])
    picks = [srt[int(i * (len(srt) - 1) / max(1, N // 2 - 1))] for i in range(N // 2)] + [rng.choice(assets) for _ in range(N - N // 2)]
    picks += [x for x in assets if (rom[x[0] + 4] >> 1) & 3 == 0]   # the stored-first assets
    picks += sorted(assets, key=lambda x: -x[1])[:8]                  # the largest (multi-block)
    stats = dict(ok=0, diff=0, skip=0, err0=0, bytes=0)
    modes = {}
    for t, (off, size, clen) in enumerate(picks):
        mode = rng.choice(['normal'] * 5 + ['magic', 'limit', 'above', 'corrupt'])
        modes[mode] = modes.get(mode, 0) + 1
        packed = bytearray(rom[off:off + 4 + clen + 16])
        if mode == 'magic':
            packed = bytearray(b'\x11\x72') + packed[4:]
        if mode == 'corrupt':
            for _ in range(rng.randint(1, 4)):
                k = rng.randrange(4, 4 + clen); packed[k] ^= 1 << rng.randrange(8)
        mem = bytearray(rng.getrandbits(8) for _ in range(256)) * (RAM // 256)
        dst = 0x80200000 + rng.randrange(0, 64)
        if mode == 'above':
            src = dst + size + rng.choice([1, 2, 16])     # limit = src - dst
            work = dst + size + 0x40000
        else:
            src = 0x80100000 + 2 * rng.randrange(0, 64)
            work = dst + size + rng.choice([1, 4, 0x100, 0x30000])
        if mode == 'limit':
            work = dst + rng.randrange(0, size)
        work = (work + 3) & ~3 if mode != 'limit' else work & ~3   # the table area is word-aligned (sh / sw of huft entries)
        mem[phys(src):phys(src) + len(packed)] = packed
        maxi = 400 * size + 2000000
        only = os.environ.get('NMINF_ONLY')
        if only and int(only, 16) != off: continue
        r1, m1 = ref.run(mem, src, dst, work, maxi)
        if mode not in ('corrupt', 'limit') and isinstance(r1, tuple):
            print('REF FAULT', hex(off), mode, r1); stats['diff'] += 1; continue
        r2, m2 = cand.run(mem, src, dst, work, maxi)
        if isinstance(r1, tuple) or isinstance(r2, tuple):
            if isinstance(r1, tuple) and isinstance(r2, tuple): stats['skip'] += 1; continue
            print('DIFF fault', hex(off), size, mode, r1, r2); stats['diff'] += 1; continue
        # sanity on the reference: zlib output and header size
        if mode in ('normal', 'magic', 'above'):
            exp = zlib.decompress(bytes(rom[off + 4:off + 4 + clen]), -15)
            got = bytes(m1[phys(dst) - LOW:phys(dst) - LOW + size])
            if r1 != size or got != exp:
                print('REF != zlib', hex(off), size, mode, r1); stats['diff'] += 1; continue
        if r1 == 0: stats['err0'] += 1
        lo, hi = phys(STACK_LO) - LOW, phys(STACK_HI) - LOW
        same = r1 == r2 and m1[:lo] == m2[:lo] and m1[hi:] == m2[hi:]
        if same:
            stats['ok'] += 1; stats['bytes'] += r1
        else:
            stats['diff'] += 1
            first = next((i for i in range(len(m1)) if m1[i] != m2[i] and not lo <= i < hi), None)
            print('DIFF', hex(off), size, mode, 'v0 %X/%X' % (r1, r2), 'first mem diff', None if first is None else hex(0x80000000 + LOW + first))
            if only:
                d = [i for i in range(len(m1)) if m1[i] != m2[i] and not lo <= i < hi]
                print('  %d bytes differ, %X..%X; dst %X work %X src %X' % (len(d), 0x80000000 + LOW + d[0], 0x80000000 + LOW + d[-1], dst, work, src))
                print('  ref ', bytes(m1[d[0] - 8:d[0] + 24]).hex()); print('  cand', bytes(m2[d[0] - 8:d[0] + 24]).hex())
            if stats['diff'] > 10: break
    print('trials', len(picks), 'modes', modes, stats)
    print('EQUIV' if stats['diff'] == 0 else 'DIFFER')


if __name__ == '__main__':
    main()
