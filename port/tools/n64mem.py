"""N64 memory model for the wasm build (docs/port/MEMORY.md). Called by gen_stubs.py.

Build time (this file):
  * finds the pointer words in the three data segments (init_data, game_data after rzip inflate,
    debugger_data) by scanning every aligned big-endian word for values that land in a known
    data range or exactly on a known function start (see classify());
  * writes n64mem_labels.s: the N64 data symbols that have no C definition become *labels inside
    two mirror arrays* (n64_rdram = KSEG0 0x80000000..+8 MB, n64_seg16 = TLB 0x16000000..+64 KB),
    so the N64 layout is preserved byte for byte;
  * writes n64mem_tab.c: the relocation list, the N64-address -> wasm-function table (exact
    prototypes, so wasm-ld takes the real function's table slot) and the table of C-defined data
    objects that blob pointers reach.
Run time (port/ultra/pc_mem.c): copy the segments from the user's ROM into the mirrors in
word-swapped layout, then rewrite every relocation word with port_n64_to_wasm().
"""
import bisect, collections, os, re, struct, zlib
import elf32

ELF = 'conker/build/conker.eu.elf'
ROM = os.environ.get('CONKER_ROM', 'baserom.eu.z64')
# (name, vram, size, rom offset, rzip?)  -- EU ROM; see conker.eu.yaml / conker/conker.eu.yaml
SEGS = [('init_data', 0x80029400, 0x4410, 0x29400, False),
        ('game_data', 0x80082EB0, 0x2E320, 0x427B0 + 0x145ED8, True),
        ('debugger_data', 0x16003700, 0x1658, 0x19EDE8 + (0x259B50 - 0x256450), False)]
CODE = [(0x10001000, 0x10029400), (0x15000000, 0x151FA920), (0x16000000, 0x16003700)]
RDRAM = (0x80000000, 0x800000)
SEG16 = (0x16000000, 0x10000)
CT = {'i32': 'int', 'i64': 'long long', 'f32': 'float', 'f64': 'double'}


def segment_bytes(rom, seg):
    name, vram, size, off, rz = seg
    if not rz:
        return rom[off:off + size]
    n, = struct.unpack('>I', rom[off:off + 4])
    d = zlib.decompressobj(-15).decompress(rom[off + 4:off + 4 + 0x40000])
    assert n == size and len(d) >= size, (name, hex(n), len(d))
    return d[:size]


def proto(name, sig):
    ps, rs = sig
    ret = CT.get(rs[0], 'int') if rs else 'void'
    args = ', '.join(CT.get(t, 'int') for t in ps) or 'void'
    return f'{ret} {name}({args});'


def generate(outdir, defined_f, defined_d, stubbed, undef_data, addr):
    """defined_f: name -> wasm sig of C-defined functions; defined_d: C-defined data names;
    stubbed: name -> sig of generated function stubs; undef_data: data names needing storage;
    addr: N64 symbol -> address. Returns {name: sig} of extra stubs needed for data-referenced
    functions with neither C body nor stub, and the set of data names placed in the mirrors."""
    syms = elf32.symbols(ELF)
    fstart = {}
    for nm, val, size, typ, bind, shndx, sec in syms:
        if typ == 2 and val and re.match(r'[A-Za-z_]\w*$', nm) and not nm.startswith(('L', 'jtbl')):
            fstart.setdefault(val, nm)  # (.L* code labels are typed FUNC in the ELF too)
    for nm, a in addr.items():
        if re.match(r'func_[0-9A-F]{8}$', nm):
            fstart.setdefault(a, nm)
    # C-defined data objects with their N64 extent (the wasm copy is authoritative)
    cobj = sorted((val, max(size, 1), nm) for nm, val, size, typ, bind, shndx, sec in syms
                  if nm in defined_d and val >= 0x80000000)
    cstarts = [c[0] for c in cobj]
    known_d = sorted(a for n, a in addr.items() if a >= 0x80000000 and not n.startswith('func_'))
    kseg_hi = 0x80400000  # 4 MB: game RAM (heap/framebuffers included); expansion area unused by the EU game
    rom = open(ROM, 'rb').read()
    relocs, stats, ftargets, ctargets, jt = [], collections.Counter(), {}, {}, collections.Counter()
    for seg in SEGS:
        data = segment_bytes(rom, seg)
        vram = seg[1]
        for o in range(0, len(data) - 3, 4):
            w, = struct.unpack_from('>I', data, o)
            kind = classify(w, fstart, kseg_hi)
            if kind is None:
                continue
            stats[(seg[0], kind)] += 1
            if kind == 'F':
                if fstart[w] in undef_data or fstart[w] in defined_d:
                    stats[(seg[0], 'F-data')] += 1  # name used as *data* by some TU: wasm-ld type clash
                    continue
                ftargets[w] = fstart[w]
            elif kind == 'J':
                jt[seg[0]] += 1
                continue  # jump-table / label words: used only by asm, left as N64 addresses
            elif kind == 'D':
                i = bisect.bisect_right(cstarts, w) - 1
                if i >= 0 and w < cobj[i][0] + cobj[i][1]:
                    ctargets[cobj[i][0]] = cobj[i]
                    stats[(seg[0], 'D->C')] += 1
            relocs.append(vram + o)

    # ---- labels
    mir = {}
    for n in undef_data:
        a = addr.get(n)
        if a is None:
            m = re.match(r'D_([0-9A-F]{8})$', n)
            a = int(m[1], 16) if m else None
        if a is None:
            continue
        for base, size, sec in ((RDRAM[0], RDRAM[1], 'n64_rdram'), (SEG16[0], SEG16[1], 'n64_seg16')):
            if base <= a < base + size:
                mir.setdefault(sec, []).append((a - base, n))
    L = ['# GENERATED by port/tools/n64mem.py - do not edit. N64 data symbols as labels in the mirrors.']
    for sec, size in (('n64_rdram', RDRAM[1]), ('n64_seg16', SEG16[1])):
        ents = sorted(mir.get(sec, []))
        L += [f'\t.section\t.bss.{sec},"",@', f'\t.globl\t{sec}', '\t.p2align\t4', f'{sec}:']
        pos = 0
        for i, (off, n) in enumerate(ents):
            if off > pos:
                L.append(f'\t.skip\t{off - pos}'); pos = off
            nxt = next((e[0] for e in ents[i + 1:] if e[0] > off), size)
            L += [f'\t.globl\t{n}', f'{n}:', f'\t.size\t{n}, {max(1, nxt - off)}']
        L += [f'\t.skip\t{size - pos}', f'\t.size\t{sec}, {size}']
    open(f'{outdir}/n64mem_labels.s', 'w').write('\n'.join(L) + '\n')

    # ---- tables
    extra = {}
    T = ['/* GENERATED by port/tools/n64mem.py - do not edit. */', '#include "../ultra/pc_mem.h"', '']
    ftab = []
    for a, n in sorted(ftargets.items()):
        sig = defined_f.get(n) or stubbed.get(n)
        if sig is None:
            sig = ((), ())
            extra[n] = sig
        T.append(proto(n, sig))
        ftab.append((a, n))
    for a, size, n in sorted(ctargets.values()):
        T.append(f'extern char {n}[];')
    T += ['', f'const unsigned port_reloc_count = {len(relocs)};', 'const unsigned port_reloc[] = {']
    for i in range(0, len(relocs), 8):
        T.append('    ' + ', '.join(f'0x{r:08X}' for r in relocs[i:i + 8]) + ',')
    T += ['};', '', f'const unsigned port_functab_count = {len(ftab)};', 'const PortFn port_functab[] = {']
    T += [f'    {{0x{a:08X}, (void *){n}, "{n}"}},' for a, n in ftab]
    T += ['};', '', f'const unsigned port_cdata_count = {len(ctargets)};', 'const PortCData port_cdata[] = {']
    T += [f'    {{0x{a:08X}, 0x{size:X}, {n}, "{n}"}},' for a, size, n in sorted(ctargets.values())]
    T += ['};']
    open(f'{outdir}/n64mem_tab.c', 'w').write('\n'.join(T) + '\n')
    with open(f'{outdir}/n64mem_report.txt', 'w') as f:
        f.write(f'relocations: {len(relocs)}  function targets: {len(ftab)} (new stubs {len(extra)})  '
                f'C-data targets: {len(ctargets)}  mirror labels: '
                + ', '.join(f'{k}={len(v)}' for k, v in mir.items()) + '\n')
        for k, v in sorted(stats.items()):
            f.write(f'  {k[0]:14s} {k[1]:5s} {v}\n')
        f.write('jump-table/label words left as N64 addresses: ' + ', '.join(f'{k}={v}' for k, v in jt.items()) + '\n')
    return extra, {n for v in mir.values() for _, n in v}


def classify(w, fstart, kseg_hi):
    """A word is a pointer if it is (a) exactly a function start, (b) inside the KSEG0 game RAM
    window [0x80000400, kseg_hi) or its KSEG1 alias, or (c) inside the TLB-mapped debugger data.
    Code-range words that are not function starts are jump-table entries / code labels ('J').
    False positives: floats in 0x8000_0400..0x8040_0000 are negative denormals (never real data);
    ints there are < -2^31+4M (no plausible counter/flag). Exact function starts in 0x10/0x15/0x16
    ranges as floats are ~1e-26..1e-29. The residual risk is bit masks such as 0x80000400 itself."""
    if w in fstart:
        return 'F'
    if 0x80000400 <= w < kseg_hi or 0xA0000400 <= w < kseg_hi + 0x20000000:
        return 'D'
    if 0x16003700 <= w < 0x16004D58:
        return 'D'
    for lo, hi in CODE:
        if lo <= w < hi:
            return 'J'
    return None


def write_memtest(outdir, gd):
    """Expected values for port_memtest (port/boot/game_entry.c), decoded here with big-endian
    semantics straight from the ROM bytes (independent of the wasm loader): difftest-style."""
    def be(a, n):
        o = a - 0x80082EB0
        return int.from_bytes(gd[o:o + n], 'big')
    rows = []
    for i in range(8):  # D_800877D0[i], struct_eu_800877D0 (0x14 bytes)
        b = 0x800877D0 + i * 0x14
        rows.append(f'    {{{i}, 0x{be(b, 4):08X}, 0x{be(b + 4, 4):08X}, 0x{be(b + 8, 2):04X}, 0x{be(b + 10, 2) & 0xFFF:03X}}},')
    o = 0x80084C60 - 0x80082EB0
    tbl = gd[o:o + 0x50]
    chars = []
    for c in b'adum.\x00Zq' + bytes([tbl[0x4F], tbl[0x20]]):
        chars.append(f'    {{0x{c:02X}, {tbl.index(c) if c in tbl else 0x50}}},')
    open(f'{outdir}/memtest_expect.h', 'w').write('\n'.join([
        '/* GENERATED by port/tools/n64mem.py from the ROM (big-endian decode) - do not edit. */',
        'typedef struct { int i; unsigned unk0, unk4, unk8, unkA; } MemtestRow;',
        f'#define MEMTEST_N {len(rows)}', 'static const MemtestRow memtest_rows[] = {'] + rows + ['};',
        'typedef struct { unsigned char c; int idx; } MemtestChar;',
        f'#define MEMTEST_NC {len(chars)}', 'static const MemtestChar memtest_chars[] = {'] + chars + ['};']) + '\n')


if __name__ == '__main__':  # n64mem.py OUTDIR : only the memtest expectations (needed before the vbe build)
    import sys
    write_memtest(sys.argv[1], segment_bytes(open(ROM, 'rb').read(), SEGS[1]))
