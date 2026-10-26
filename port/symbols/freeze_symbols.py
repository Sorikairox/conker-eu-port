#!/usr/bin/env python3
"""ONE-TIME generator (P328) of the frozen port symbol tables, from the last byte-matching decomp build.

Run once, on port-web at the split from branch exact-byte-decomp-wip (P328), with a fresh matching build:
    python3 port/symbols/freeze_symbols.py      (from the repo root; needs conker/build/conker.eu.elf + the
                                                  conker/*symbol/undefined txt files + conker/conker.eu.yaml)
Writes port/symbols/symbols.tsv and port/symbols/segments.tsv; with --cc DUMP, port/symbols/ido_cc.tsv. After P328 these files are the source of truth for
names and addresses of the port tools (port/symbols/symbols.py reads them); a rename edits symbols.tsv (rename.py
--port), never splat. Do not re-run once the matching build is gone: there is nothing left to read.

symbols.tsv, one row per symbol, in the ELF symbol-table order (tools pick the FIRST name at an address, so the
order is part of the data), then the link-file names that have no ELF symbol:
  name     symbol name
  addr     value (hex): vram for code/data, the plain number for absolute symbols (ROM offsets, texture ids)
  size     ELF st_size (hex; 0 = unknown)
  type     func | data | none   (ELF STT_FUNC / STT_OBJECT / STT_NOTYPE; link-only rows: func for func_*, else none)
  bind     local | global | weak | -   (- = link-only row)
  section  ELF section (.init .game .game_data ...), abs for symbols outside any section, - for link-only rows
  segment  init | init_data | game | game_data | debugger | debugger_data | abs, from the address
  link     position (0..) of the name in the old linker symbol files (undefined_syms_auto.txt, undefined_funcs_auto
           .txt, undefined_syms.eu.txt, undefined_funcs.eu.txt, symbol_addrs.eu.txt; first occurrence), or - when the
           name came from the ELF only. These names are the "link values" (gen_stubs.addresses, romabs_check, difftest).
ido_cc.tsv (written with --cc MAKE_N_DUMP, the output of `make -n -B VERSION=eu` run in conker/ inside the dev
container): per game TU, the IDO compile command difftest used to derive with `make -n` from conker/Makefile
(path relative to conker/, then the shlex-joined command without -o and the source). Difftest still compiles its
candidate with that IDO (part 2 decides whether IDO stays for difftest).
segments.tsv: the code/data segments of the extracted ROM image (port/symbols/romimage.py): name, rom start, rom
end, vram, rodata start (data segments; - otherwise). Was read from conker/conker.eu.yaml (tools/eu_port/datarefs).
"""
import os, re, sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, '..', 'tools'))
sys.path.insert(0, os.path.join(HERE, '..', '..', 'tools', 'eu_port'))
import elf32

ELF = 'conker/build/conker.eu.elf'
LINK_FILES = ('undefined_syms_auto.txt', 'undefined_funcs_auto.txt', 'undefined_syms.eu.txt',
              'undefined_funcs.eu.txt', 'symbol_addrs.eu.txt')
TYPES = {0: 'none', 1: 'data', 2: 'func'}
BINDS = {0: 'local', 1: 'global', 2: 'weak'}
# address ranges -> segment (code vram, data vram incl. bss; conker.eu.yaml / port/tools/n64mem.py)
SEGRANGES = [('init', 0x10001000, 0x10029400), ('game', 0x15000000, 0x151FA920), ('debugger', 0x16000000, 0x16003700),
             ('debugger_data', 0x16003700, 0x16010000), ('init_data', 0x80029400, 0x80082EB0),
             ('game_data', 0x80082EB0, 0x80400000)]


def segment_of(a):
    for n, lo, hi in SEGRANGES:
        if lo <= a < hi:
            return n
    return 'abs'


def main():
    link = {}
    for f in LINK_FILES:
        for line in open('conker/' + f):
            m = re.match(r'\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+|\d+)', line)
            if m:
                v = int(m[2], 0)
                assert link.setdefault(m[1], v) == v, ('conflicting link values', m[1])
    order = {n: i for i, n in enumerate(link)}
    rows, seen = [], set()
    for nm, val, size, typ, bind, shndx, sec in elf32.symbols(ELF):
        if typ == 4:          # STT_FILE
            continue
        assert nm not in link or link[nm] == val, ('ELF and link values differ', nm)
        rows.append((nm, val, size, TYPES.get(typ, str(typ)), BINDS.get(bind, str(bind)), sec or 'abs',
                     segment_of(val), order.get(nm, '-')))
        seen.add(nm)
    for nm, v in link.items():
        if nm not in seen:
            rows.append((nm, v, 0, 'func' if nm.startswith('func_') else 'none', '-', '-', segment_of(v), order[nm]))
    with open(os.path.join(HERE, 'symbols.tsv'), 'w') as f:
        f.write('# name\taddr\tsize\ttype\tbind\tsection\tsegment\tlink   (frozen P328 from the matching build; '
                'see port/symbols/freeze_symbols.py)\n')
        for r in rows:
            f.write(f'{r[0]}\t{r[1]:08X}\t{r[2]:X}\t' + '\t'.join(str(x) for x in r[3:]) + '\n')
    import datarefs
    with open(os.path.join(HERE, 'segments.tsv'), 'w') as f:
        f.write('# name\trom_start\trom_end\tvram\trodata_rom   (frozen P328 from conker/conker.eu.yaml; offsets into '
                'port/symbols/romimage.py image)\n')
        for nm, sg in datarefs.segments().items():
            if 'vram' not in sg or sg.get('end') is None or nm in ('header', 'boot'):
                continue
            ro = next((r for r, t, _ in sg['subs'] if t and 'rodata' in t), None) if nm.endswith('_data') else None
            f.write(f"{nm}\t{sg['start']:X}\t{sg['end']:X}\t{sg['vram']:08X}\t{'-' if ro is None else f'{ro:X}'}\n")
    print(f'symbols.tsv: {len(rows)} rows ({len(link)} link names); segments.tsv written')


def freeze_cc(dump):
    import shlex
    rows = {}
    for l in open(dump):
        if '/cc ' in l and ' -c ' in l:      # same selection as difftest.py _cc_cmd()
            a = shlex.split(l)
            if '-o' not in a:
                continue
            i = a.index('-o')
            m = re.match(r'build/(.*\.c)\.o$', a[i + 1])
            if m:
                rows.setdefault(m.group(1), [x for x in a[:i] + a[i + 2:] if not x.endswith('.c')])
    with open(os.path.join(HERE, 'ido_cc.tsv'), 'w') as f:
        f.write('# tu\tcommand   (frozen P328 from `make -n -B VERSION=eu` in conker/; difftest candidate compile)\n')
        for k in sorted(rows):
            f.write(k + '\t' + shlex.join(rows[k]) + '\n')
    print(f'ido_cc.tsv: {len(rows)} TUs')


if __name__ == '__main__':
    if sys.argv[1:2] == ['--cc']:
        freeze_cc(sys.argv[2])
    else:
        main()
