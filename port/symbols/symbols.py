"""Reader of the frozen port symbol tables (P328): port/symbols/symbols.tsv + segments.tsv.

These replace, for the port tools and difftest, everything that used to come from the byte-matching decomp build:
conker/build/conker.eu.elf (+ .map), conker/undefined_*_auto.txt, undefined_*.eu.txt, symbol_addrs.eu.txt and the
segment list of conker/conker.eu.yaml. Columns: see freeze_symbols.py.
  elf_symbols()    -> [(name, value, size, type, bind, shndx, section)] like port/tools/elf32.symbols() on the old ELF
                      (type/bind as ELF numbers; shndx 0 for abs/link-only rows, 1 otherwise)
  link_addresses() -> {name: value} of the old linker symbol files, in their order
  func_sizes()     -> {addr: size} of STT_FUNC symbols with a size (first wins)
  segments()       -> [(name, rom_start, rom_end, vram, rodata_rom or None)]
"""
import os

HERE = os.path.dirname(os.path.abspath(__file__))
SYMBOLS = os.path.join(HERE, 'symbols.tsv')
SEGMENTS = os.path.join(HERE, 'segments.tsv')
_TYPES = {'none': 0, 'data': 1, 'func': 2}
_BINDS = {'local': 0, 'global': 1, 'weak': 2}
_rows = None


def rows():
    """[(name, addr, size, type, bind, section, segment, link)] (link: int position or None)"""
    global _rows
    if _rows is None:
        _rows = []
        for line in open(SYMBOLS):
            if line.startswith('#'):
                continue
            f = line.rstrip('\n').split('\t')
            _rows.append((f[0], int(f[1], 16), int(f[2], 16), f[3], f[4], f[5], f[6], None if f[7] == '-' else int(f[7])))
    return _rows


def elf_symbols():
    out = []
    for nm, a, size, typ, bind, sec, seg, link in rows():
        if bind == '-':
            continue
        out.append((nm, a, size, _TYPES.get(typ, 0), _BINDS.get(bind, 0), 0 if sec == 'abs' else 1,
                    '' if sec == 'abs' else sec))
    return out


def link_addresses():
    ln = sorted((r[7], r[0], r[1]) for r in rows() if r[7] is not None)
    return {nm: a for _, nm, a in ln}


def func_sizes():
    out = {}
    for nm, a, size, typ, bind, sec, seg, link in rows():
        if typ == 'func' and size and bind != '-':
            out.setdefault(a, size)
    return out


def segments():
    out = []
    for line in open(SEGMENTS):
        if line.startswith('#'):
            continue
        f = line.rstrip('\n').split('\t')
        out.append((f[0], int(f[1], 16), int(f[2], 16), int(f[3], 16), None if f[4] == '-' else int(f[4], 16)))
    return out


def global_asm():
    """P329: name -> (file under conker/src_eu, asm_only) for every function that had a `#pragma GLOBAL_ASM` line before
    the pragmas were stripped (global_asm.tsv). asm_only = no C body (platform-replaced code)."""
    out = {}
    for l in open(os.path.join(HERE, 'global_asm.tsv')):
        if l.startswith('#') or '\t' not in l:
            continue
        n, f, a = l.rstrip('\n').split('\t')
        out[n] = (f, a == '1')
    return out
