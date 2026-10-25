#!/usr/bin/env python3
"""P251: whole-function harness for the MP3 Huffman group of game_eu_226870: the hand asm func_151F9184 (big values)
and func_151F933C (count1 quads) with their register-ABI helpers func_151F9060 / func_151F911C (ROM code
0x151F9060..0x151F94E0, run for real) against the NON_MATCHING C (build_nm: two C functions + static helpers).

Both sides run in Unicorn MIPS32 (pinned 2.0.1 from port_work/pyuc201): reference = build/conker.eu.elf's .game,
candidate = build_nm/conker.eu.elf's .game (+ .nm_rodata). The code is integer only and calls nothing outside the group.
Tables: the real ROM assets func_151F2960 loads with func_1502B5C8(0, 2, 0x17, 4 / 5 / 6): D_800E0E20 (34 tree
offsets, entries 1..33 relocated by D_800E0E28 like func_151F3DE0), D_800E0E24 (fast lookup + lengths), D_800E0E28
(trees). Streams: real MP3 frames found in the ROM (runs of consecutive layer III headers), the bit reservoir
rebuilt from main_data_begin, side info and scale-factor lengths parsed (MPEG-1 and MPEG-2 LSF), then the decode
sequence of func_151F63C4: three big-value regions (func_151F9184, zero fill for tables without a tree) and count1
(func_151F933C, endBit = part2_3_length). Random modes: random bytes with random table / i / end / linbits / endBit
(incl. end <= i, i >= 576, odd i, endBit before the start).
Compared after every call: v0, *bitpos, *out, *signs, the stream / output / sign buffers and the callee-saved
registers (s0-s7, fp, gp, sp); every 50th trial also all RDRAM except the stack. Stats: how many real granules end
exactly at part2_3_length (proves the inputs are decoded as real MP3 data).

Run in the container from /conker/conker after both builds:
  python3 ../docs/port/sessions/p251/nmasm_huff.py ../baserom.eu.z64 [frames] [random] [seed]"""
import os, sys, struct, random, zlib, subprocess
_UC = os.environ.get('DIFFTEST_UNICORN', '/conker/port_work/pyuc201')
if os.path.isdir(_UC): sys.path.insert(0, _UC)
from unicorn import Uc, UcError, UC_ARCH_MIPS, UC_MODE_MIPS32, UC_MODE_BIG_ENDIAN, UC_PROT_ALL
from unicorn.mips_const import *

RET = 0x153F0000
SP0 = 0x807FE000
RAM = 0x800000
LOW = 0x1000
phys = lambda a: a & 0x1FFFFFFF
T20, T24, T28 = 0x80300000, 0x80310000, 0x80320000
BUF, OUT, SGN, VAR = 0x80400000, 0x80420000, 0x80430000, 0x80440000   # VAR: +0 bitpos, +4 out ptr, +8 signs ptr
LINBITS = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 8, 10, 13, 4, 5, 6, 7, 8, 9, 11, 13, 0, 0]
SAVED = [UC_MIPS_REG_S0 + k for k in range(8)] + [UC_MIPS_REG_FP, UC_MIPS_REG_GP, UC_MIPS_REG_SP]


def section(elf, name):
    out = '/tmp/p251_%s_%s.bin' % (elf.replace('/', '_'), name)
    subprocess.check_call(['mips-linux-gnu-objcopy', '-O', 'binary', '-j', name, elf, out])
    for l in subprocess.check_output(['mips-linux-gnu-objdump', '-h', elf]).decode().split('\n'):
        f = l.split()
        if len(f) > 3 and f[1] == name: return int(f[3], 16), open(out, 'rb').read()
    return None


def syms(elf):
    d = {}
    for l in subprocess.check_output(['mips-linux-gnu-nm', elf]).decode().split('\n'):
        f = l.split()
        if len(f) == 3: d[f[2]] = int(f[0], 16)
    return d


def asset(rom, keys):   # func_1502B5C8 in Python (as nmasm_level.py)
    p = 0xAB2240
    info = 0
    for k in keys:
        off, info = struct.unpack('>iI', rom[p + 8 * k:p + 8 * k + 8])
        if not info & 0x0FFFFFFF: return None
        p += off
    size = ((info & 0x0FFFFFFF) + 1) & ~1
    raw = rom[p:p + size]
    if (info & 0x70000000) == 0x10000000:
        n = struct.unpack('>I', raw[:4])[0] & 0x7FFFFFFF
        return bytearray(zlib.decompressobj(-15).decompress(raw[4:])[:n])
    return bytearray(raw)


class Emu:
    def __init__(self, elf):
        self.s = syms(elf)
        mu = Uc(UC_ARCH_MIPS, UC_MODE_MIPS32 | UC_MODE_BIG_ENDIAN)
        mu.mem_map(LOW, RAM - LOW, UC_PROT_ALL)
        mu.mem_map(0x15000000, 0x400000, UC_PROT_ALL)
        for n in ('.game', '.nm_rodata'):
            x = section(elf, n)
            if x: mu.mem_write(x[0] if x[0] < 0x80000000 else phys(x[0]), x[1])
        self.mu = mu

    def call(self, fn, args, maxi=2000000):
        mu = self.mu
        for k, a in enumerate(args[:4]): mu.reg_write(UC_MIPS_REG_A0 + k, a & 0xFFFFFFFF)
        for k, a in enumerate(args[4:]): mu.mem_write(phys(SP0) + 0x10 + 4 * k, struct.pack('>I', a & 0xFFFFFFFF))
        for k, r in enumerate(SAVED[:-1]): mu.reg_write(r, 0x5A5A0000 + k)
        mu.reg_write(UC_MIPS_REG_SP, SP0); mu.reg_write(UC_MIPS_REG_RA, RET)
        try:
            mu.emu_start(self.s[fn], RET, count=maxi)
        except UcError as e:
            return ('fault %s' % e, )
        if mu.reg_read(UC_MIPS_REG_PC) != RET: return ('timeout', )
        return (mu.reg_read(UC_MIPS_REG_V0) & 0xFFFFFFFF, tuple(mu.reg_read(r) for r in SAVED))

    def snap(self, full=False):
        rd = lambda a, n: bytes(self.mu.mem_read(phys(a), n))
        if full:
            return rd(0x80000000 + LOW, phys(SP0) - 0x8000 - LOW) + rd(SP0 + 0x100, RAM - phys(SP0) - 0x100)
        return rd(BUF, 0x1000), rd(OUT, 0x600), rd(SGN, 0x300), rd(VAR, 12)

    def poke(self, a, b): self.mu.mem_write(phys(a), bytes(b))


class Bits:
    def __init__(self, b, pos=0): self.b, self.p = b, pos
    def get(self, n):
        v = 0
        for _ in range(n):
            v = (v << 1) | ((self.b[self.p >> 3] >> (7 - (self.p & 7))) & 1); self.p += 1
        return v


BR = {1: [0, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320],
      0: [0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160]}
SR = {3: [44100, 48000, 32000], 2: [22050, 24000, 16000], 0: [11025, 12000, 8000]}
SFB_LONG = {44100: [0, 4, 8, 12, 16, 20, 24, 30, 36, 44, 52, 62, 74, 90, 110, 134, 162, 196, 238, 288, 342, 418, 576],
            48000: [0, 4, 8, 12, 16, 20, 24, 30, 36, 42, 50, 60, 72, 88, 106, 128, 156, 190, 230, 276, 330, 384, 576],
            32000: [0, 4, 8, 12, 16, 20, 24, 30, 36, 44, 54, 66, 82, 102, 126, 156, 194, 240, 296, 364, 448, 550, 576],
            22050: [0, 6, 12, 18, 24, 30, 36, 44, 54, 66, 80, 96, 116, 140, 168, 200, 238, 284, 336, 396, 464, 522, 576],
            24000: [0, 6, 12, 18, 24, 30, 36, 44, 54, 66, 80, 96, 114, 136, 162, 194, 232, 278, 330, 394, 464, 540, 576],
            16000: [0, 6, 12, 18, 24, 30, 36, 44, 54, 66, 80, 96, 116, 140, 168, 200, 238, 284, 336, 396, 464, 522, 576]}
SFB_LONG[11025] = SFB_LONG[12000] = SFB_LONG[22050]; SFB_LONG[8000] = [0, 12, 24, 36, 48, 60, 72, 88, 108, 132, 160, 192, 232, 280, 336, 400, 476, 566, 568, 570, 572, 574, 576]
SFB_S3 = {44100: 4, 48000: 4, 32000: 4, 8000: 8}   # short band 3 start (x 3 = region0 end of short blocks)
NR_SFB = [[[6, 5, 5, 5], [9, 9, 9, 9], [6, 9, 9, 9]], [[6, 5, 7, 3], [9, 9, 12, 6], [6, 9, 12, 6]],
          [[11, 10, 0, 0], [18, 18, 0, 0], [15, 18, 0, 0]], [[7, 7, 7, 0], [12, 12, 12, 0], [6, 15, 12, 0]],
          [[6, 6, 6, 3], [12, 9, 9, 6], [6, 12, 9, 6]], [[8, 8, 5, 0], [15, 12, 9, 0], [6, 18, 9, 0]]]
SLEN1 = [(0, 0), (0, 1), (0, 2), (0, 3), (3, 0), (1, 1), (1, 2), (1, 3), (2, 1), (2, 2), (2, 3), (3, 1), (3, 2), (3, 3), (4, 2), (4, 3)]


def hdr(h):
    if (h >> 21) & 0x7FF != 0x7FF: return None
    ver, lay, bri, sri, pad = (h >> 19) & 3, (h >> 17) & 3, (h >> 12) & 15, (h >> 10) & 3, (h >> 9) & 1
    if lay != 1 or bri in (0, 15) or sri == 3 or ver == 1: return None
    sr = SR[ver][sri]; m1 = ver == 3
    n = (144 if m1 else 72) * BR[1 if m1 else 0][bri] * 1000 // sr + pad
    return dict(m1=m1, sr=sr, len=n, crc=not (h >> 16) & 1, mode=(h >> 6) & 3, mext=(h >> 4) & 3)


def frames(rom):
    """runs of >= 5 consecutive layer III frames"""
    i, n = 0, len(rom) - 4
    while i < n:
        if rom[i] == 0xFF and rom[i + 1] & 0xE0 == 0xE0:
            j, run = i, []
            while j < n:
                h = hdr(struct.unpack('>I', rom[j:j + 4])[0])
                if not h or h['len'] < 24: break
                h['off'] = j; run.append(h); j += h['len']
            if len(run) >= 5: yield run; i = j; continue
        i += 1


def granules(rom, run):
    """per granule / channel: (main-data bytes from the granule's frame start, start bit, side info)"""
    res = bytearray()
    for h in run:
        nch = 1 if h['mode'] == 3 else 2
        so = h['off'] + 4 + (2 if h['crc'] else 0)
        b = Bits(rom[so:so + 40])
        if h['m1']:
            mdb = b.get(9); b.get(5 if nch == 1 else 3); scfsi = [[b.get(1) for _ in range(4)] for _ in range(nch)]; ngr = 2
            silen = 17 if nch == 1 else 32
        else:
            mdb = b.get(8); b.get(1 if nch == 1 else 2); scfsi = [[0] * 4] * nch; ngr = 1
            silen = 9 if nch == 1 else 17
        gi = []
        for gr in range(ngr):
            for ch in range(nch):
                g = dict(p23=b.get(12), bv=b.get(9), gain=b.get(8), sfc=b.get(4 if h['m1'] else 9), ws=b.get(1), ch=ch, gr=gr)
                if g['ws']:
                    g['bt'], g['mixed'] = b.get(2), b.get(1); g['ts'] = [b.get(5), b.get(5), 0]; [b.get(3) for _ in range(3)]
                    g['r0'], g['r1'] = 7 if g['bt'] != 2 or g['mixed'] else 8, 0
                else:
                    g['bt'] = g['mixed'] = 0; g['ts'] = [b.get(5), b.get(5), b.get(5)]; g['r0'], g['r1'] = b.get(4), b.get(3)
                if h['m1']: b.get(1)
                b.get(1); g['c1'] = b.get(1)
                gi.append(g)
        payload = rom[so + silen:h['off'] + h['len']]
        start = len(res) - mdb
        res += payload
        if start < 0 or mdb > 511: continue
        bit = 0
        for g in gi:
            g['part2'] = part2(h, g, scfsi[g['ch']])
            yield res, start, bit, h, g
            bit += g['p23']


def part2(h, g, scfsi):
    sh = g['ws'] and g['bt'] == 2
    if h['m1']:
        s1, s2 = SLEN1[g['sfc']]
        if sh: return (17 if g['mixed'] else 18) * s1 + 18 * s2
        n = 0
        for k, (a, c, sl) in enumerate(((0, 6, s1), (6, 5, s1), (11, 5, s2), (16, 5, s2))):
            if not (g['gr'] == 1 and scfsi[k]): n += c * sl
        return n
    sfc = g['sfc']
    if h['mode'] == 1 and (h['mext'] & 1) and g['ch'] == 1:
        sfc >>= 1
        if sfc < 180: sl, bn = [sfc // 36, (sfc % 36) // 6, sfc % 6, 0], 3
        elif sfc < 244: sfc -= 180; sl, bn = [(sfc & 63) >> 4, (sfc & 15) >> 2, sfc & 3, 0], 4
        else: sfc -= 244; sl, bn = [sfc // 3, sfc % 3, 0, 0], 5
    elif sfc < 400: sl, bn = [(sfc >> 4) // 5, (sfc >> 4) % 5, (sfc & 15) >> 2, sfc & 3], 0
    elif sfc < 500: sfc -= 400; sl, bn = [(sfc >> 2) // 5, (sfc >> 2) % 5, sfc & 3, 0], 1
    else: sfc -= 500; sl, bn = [sfc // 3, sfc % 3, 0, 0], 2
    btn = 0 if not sh else (2 if g['mixed'] else 1)
    return sum(a * b for a, b in zip(sl, NR_SFB[bn][btn]))


def regions(h, g):   # func_151F63C4
    big = g['bv'] * 2; sfb = SFB_LONG[h['sr']]
    if not g['ws'] and g['bt'] == 0:
        r0 = sfb[g['r0'] + 1]
        if r0 > big: r0 = r1 = big
        else: r1 = min(sfb[min(g['r0'] + g['r1'] + 2, 22)], big)
    else:
        r0 = SFB_S3.get(h['sr'], 6) * 3 if g['bt'] == 2 and not g['mixed'] else sfb[8]
        r0 = min(r0, big); r1 = big
    return [r0, r1, big]


class Cmp:
    def __init__(self, ref, cand):
        self.ref, self.cand, self.n, self.bad, self.faults = ref, cand, 0, [], []

    def setup(self, buf, bitpos):
        for e in (self.ref, self.cand):
            e.poke(BUF, buf + bytes(0x1000 - len(buf)))
            e.poke(OUT, b'\xA5' * 0x600); e.poke(SGN, b'\x5A' * 0x300)
            e.poke(VAR, struct.pack('>III', bitpos, OUT, SGN))

    def call(self, what, fn, args, full=False):
        self.n += 1
        r1, r2 = self.ref.call(fn, args), self.cand.call(fn, args)
        s1, s2 = self.ref.snap(full), self.cand.snap(full)
        if r1 != r2 or s1 != s2:
            d = [k for k in range(len(s1)) if s1[k] != s2[k]]
            self.bad.append('%s %s%r: ret %r / %r, differing parts %r' % (what, fn, tuple('%X' % (a & 0xFFFFFFFF) for a in args), r1[:1], r2[:1], d))
            return None
        return r1


def main():
    rom = open(sys.argv[1], 'rb').read()
    NF = int(sys.argv[2]) if len(sys.argv) > 2 else 3000
    NR = int(sys.argv[3]) if len(sys.argv) > 3 else 3000
    rng = random.Random(int(sys.argv[4]) if len(sys.argv) > 4 else 251)
    ref, cand = Emu('build/conker.eu.elf'), Emu('build_nm/conker.eu.elf')
    a20, a24, a28 = asset(rom, [0x17, 4]), asset(rom, [0x17, 5]), asset(rom, [0x17, 6])
    t20 = [struct.unpack('>I', a20[4 * k:4 * k + 4])[0] for k in range(34)]
    trees = [t20[0]] + [(t + T28) & 0xFFFFFFFF for t in t20[1:]]
    print('tables: E20 %d bytes, E24 %d, E28 %d; tree offsets %s' % (len(a20), len(a24), len(a28), ' '.join('%X' % t for t in t20)))
    for e in (ref, cand):
        e.poke(T20, b''.join(struct.pack('>I', t) for t in trees)); e.poke(T24, a24); e.poke(T28, a28)
        e.poke(e.s['D_800E0E20'], struct.pack('>I', T20)); e.poke(e.s['D_800E0E24'], struct.pack('>I', T24))
    print('D_800E0E20 / 24 (US names): ref %X / %X, cand %X / %X' % (ref.s['D_800E0E20'], ref.s['D_800E0E24'], cand.s['D_800E0E20'], cand.s['D_800E0E24']))
    hastree = list(range(1, 32))   # entry 0 is the only NULL tree (entries 1..33 are relocated)
    cmp = Cmp(ref, cand)
    from unicorn import UC_HOOK_CODE
    hits = {0x151F90C4: 0, 0x151F90F8: 0, 0x151F9220: 0, 0x151F9280: 0, 0x151F946C: 0, 0x151F9410: 0}
    names = {0x151F90C4: 'tree walk', 0x151F90F8: 'tree byte wrap', 0x151F9220: 'x linbits', 0x151F9280: 'y linbits',
             0x151F946C: 'count1 give-back a0--', 0x151F9410: 'count1 v sign'}
    def hk(uc, a, sz, ud): hits[a] += 1
    for a in hits: ref.mu.hook_add(UC_HOOK_CODE, hk, begin=a, end=a)
    gl = [x for run in frames(rom) for x in granules(rom, run)] if NF else []
    print('granules found: %d (MPEG-1 %d)' % (len(gl), sum(1 for x in gl if x[3]['m1'])))
    pick = rng.sample(range(len(gl)), min(NF, len(gl)))
    exact = over = 0; hist = {}; tabs = set(); lin = 0
    for t, gi in enumerate(pick):
        res, start, bit, h, g = gl[gi]
        sh = rng.randrange(4)
        buf = bytes(sh) + bytes(res[start:start + 0xF00 - sh])
        pos0 = sh * 8 + bit
        cmp.setup(buf, pos0 + g['part2'])
        i = 0; reg = regions(h, g); ok = True
        for k in range(3):
            tb = g['ts'][k]
            if tb == 0:
                cnt = reg[k] - i
                if cnt > 0:
                    for e in (ref, cand):
                        o, s = struct.unpack('>II', bytes(e.mu.mem_read(phys(VAR + 4), 8)))
                        e.poke(o, bytes(2 * cnt)); e.poke(VAR + 4, struct.pack('>II', o + 2 * cnt, s + cnt))
                i = max(i, reg[k]); continue
            tabs.add(tb); lin += LINBITS[tb] != 0
            r = cmp.call('frame %X gr%d ch%d region %d' % (h['off'], g['gr'], g['ch'], k), 'func_151F9184',
                         [BUF, VAR, tb, i, LINBITS[tb], reg[k], VAR + 4, VAR + 8], full=t % 50 == 0)
            if r is None: ok = False; break
            if len(r) == 1: cmp.faults.append('frame %X region %d: %s' % (h['off'], k, r[0])); ok = False; break
            i = r[0] if r[0] < 0x80000000 else r[0] - (1 << 32)
        if not ok: continue
        end = pos0 + g['p23']
        r = cmp.call('frame %X count1' % h['off'], 'func_151F933C', [BUF, VAR, 32 + g['c1'], i, end, VAR + 4, VAR + 8], full=t % 50 == 0)
        if r is None: continue
        if len(r) == 1: cmp.faults.append('frame %X count1: %s' % (h['off'], r[0])); continue
        p = struct.unpack('>I', bytes(ref.mu.mem_read(phys(VAR), 4)))[0]
        hist[p - end] = hist.get(p - end, 0) + 1
        exact += p == end
    print('real granules: %d run, %d calls, %d differ; ended exactly at part2_3_length: %d; end offset histogram %s; '
          'tables used %s; regions with linbits %d' % (len(pick), cmp.n, len(cmp.bad), exact,
          sorted(hist.items(), key=lambda x: -x[1])[:8], sorted(tabs), lin))
    nb = len(cmp.bad); n0 = cmp.n; h0 = dict(hits)
    for t in range(NR):
        buf = bytes(rng.randrange(256) for _ in range(0x400))
        mode = rng.randrange(10)
        pos = rng.randrange(0x800)
        cmp.setup(buf, pos)
        if mode < 7:
            tb = rng.choice(hastree + [32, 33]) if mode else rng.choice(hastree)
            i = rng.choice([0, rng.randrange(576), rng.randrange(-8, 600)])
            end = rng.choice([i + 2 * rng.randrange(40), i + rng.randrange(-4, 80), rng.randrange(-4, 600)])
            lb = LINBITS[tb] if rng.random() < 0.7 else rng.randrange(14)
            cmp.call('random %d' % t, 'func_151F9184', [BUF, VAR, tb, i, lb, end, VAR + 4, VAR + 8], full=t % 50 == 0)
        else:
            tb = rng.choice([32, 33, 32, 33, rng.choice(hastree)])
            i = rng.choice([0, rng.randrange(576), rng.choice([568, 570, 572, 574, 575, 576, 577, 580])])
            endb = pos + rng.choice([rng.randrange(-8, 8), rng.randrange(400), rng.randrange(-100, 3000)])
            cmp.call('random %d' % t, 'func_151F933C', [BUF, VAR, tb, i, endb, VAR + 4, VAR + 8], full=t % 50 == 0)
    print('ref paths (real granules):', ', '.join('%s %d' % (names[a], h0[a]) for a in sorted(hits)))
    print('random: %d calls, %d differ' % (cmp.n - n0, len(cmp.bad) - nb))
    for l in cmp.bad[:10]: print('DIFF', l)
    print('faults on both sides (same result): %d' % len(cmp.faults), cmp.faults[:3])
    print('RESULT', 'EQUIV' if not cmp.bad else 'DIFFER', '%d calls' % cmp.n)


if __name__ == '__main__':
    main()
