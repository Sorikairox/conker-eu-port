#!/usr/bin/env python3
"""romabs_check.py (P233): every `D_<hex>` data symbol that the NON_MATCHING C references and whose N64 link value is
NOT a RAM address (below 0x80000000: a ROM offset, a texture id, a size, or a physical/segment address) must be handled
by port/tools/vbe.py, or the port links it as a zero-filled data stub and the C passes a wasm address instead of the
N64 value (P37 D_D11 / D_A4A, P228 D_88C / D_87B barrel-menu trap, P228 D_89810 shadow view matrix).

Two kinds:
  absolute  the value is used as a number (texture id, ROM offset): needs a vbe.py ROM_ABS entry {name: value}.
  alias     KSEG0 | value is exactly the address of a known RAM data symbol (D_89810 -> g_identity_mtx, the identity
            matrix used through its physical address in a gSPMatrix): needs a vbe.py RAM_ALIAS entry {name: target}.

Sources of "referenced from NM C":
  - port/build/ll/*.c.ll (the clang IR before vbe.py, i.e. the real NON_MATCHING preprocessed build): `@D_x = external`
  - plus a source scan of conker/src_eu/**/*.c that skips `#ifndef NON_MATCHING` / `#else` of `#ifdef NON_MATCHING`
    regions and GLOBAL_ASM lines (catches new C before the next port build).
Link values: the frozen port symbol table port/symbols/symbols.tsv (P328; before: conker/undefined_syms_auto.txt,
undefined_syms.eu.txt, symbol_addrs.eu.txt, undefined_funcs_auto.txt), the same values gen_stubs.py uses, else the
name itself for D_<8 hex>.

Symbols at or above 0x10000000 (TLB-mapped segments) are real data handled by n64mem.py and are not listed.
An alias-shaped symbol that is really a number (D_2D810, a ROM offset that collides with a RAM symbol) is listed in
REVIEWED_ABS below with the reason (kind `absolute*`).

Fails (rc 1) on: a low symbol in neither table; a ROM_ABS value that differs from the link value; a RAM_ALIAS target
that is not the KSEG0 address of the link value; an alias-shaped symbol in ROM_ABS (it would be a number, not the data).
Stale table entries (no NM reference any more) are reported as INFO only.

Usage: port/tools/romabs_check.py [--quiet]     (needs CONKER_ROOT; the census / checks.sh run it)
"""
import glob, importlib.util, os, re, sys

ROOT = os.environ.get('CONKER_ROOT')
if not ROOT:
    sys.exit('set CONKER_ROOT (eval "$(tools/eu_port/wt.sh env web)")')
os.chdir(ROOT)
QUIET = '--quiet' in sys.argv

spec = importlib.util.spec_from_file_location('vbe', 'port/tools/vbe.py')
vbe = importlib.util.module_from_spec(spec); spec.loader.exec_module(vbe)
ROM_ABS = vbe.ROM_ABS
RAM_ALIAS = getattr(vbe, 'RAM_ALIAS', {})


def addresses():
    """P328: link values from the frozen port symbol table (port/symbols/symbols.tsv), as gen_stubs.py"""
    sys.path.insert(0, 'port/symbols')
    import symbols
    return symbols.link_addresses()


# Values at or above 0x10000000 are TLB-mapped segment addresses (init 0x10xxxxxx, game 0x15xxxxxx, debugger
# 0x16xxxxxx): real data that n64mem.py mirrors / relocates. Below that: ROM offsets, ids, physical addresses.
LOW_LIMIT = 0x10000000
# Symbols whose KSEG0 address happens to equal a RAM data symbol but that the C uses as a number (reviewed by hand).
REVIEWED_ABS = {'D_2D810': 'ROM offset handed to the PI DMA rom_dma_read (game_eu_4A070.c); 0x8002D810 = g_boot_idle_stack_alias is a coincidence'}
SYM = re.compile(r'\bD_[0-9A-Fa-f]+\b')


def src_refs():
    """name -> set of files, NM-active C only (rough preprocessor tracking, as gen_stubs.asm_only)."""
    refs = {}
    for path in glob.glob('conker/src_eu/**/*.c', recursive=True):
        stack = []
        text = re.sub(r'/\*.*?\*/', lambda m: '\n' * m[0].count('\n'), open(path, errors='replace').read(), flags=re.S)
        for line in text.split('\n'):
            s = line.strip()
            if s.startswith('#if'):
                stack.append('nm' if re.match(r'#ifdef\s+NON_MATCHING\b', s) else
                             'nnm' if re.match(r'#ifndef\s+NON_MATCHING\b', s) else 'other')
                continue
            if s.startswith('#else') and stack:
                stack[-1] = {'nm': 'nm_else', 'nnm': 'nnm_else'}.get(stack[-1], stack[-1]); continue
            if s.startswith('#endif') and stack:
                stack.pop(); continue
            if any(x in ('nm_else', 'nnm') for x in stack) or 'GLOBAL_ASM' in s:
                continue
            code = re.sub(r'//.*', '', line)
            for n in SYM.findall(code):
                refs.setdefault(n, set()).add(os.path.relpath(path, 'conker/src_eu'))
    return refs


def ll_refs():
    refs = {}
    ext = re.compile(r'^@(D_[0-9A-Fa-f]+) = external ', re.M)
    for p in glob.glob('port/build/ll/*.c.ll'):
        if p.endswith('.v.ll'):
            continue
        for n in ext.findall(open(p, errors='replace').read()):
            refs.setdefault(n, set()).add(os.path.basename(p)[:-3].replace('__', '/'))
    return refs


def renamed_from():
    """new name -> old D_/func_ name (tools/eu_port/names.tsv): renamed globals still count as KSEG0 data"""
    out = {}
    for line in open('tools/eu_port/names.tsv'):
        f = line.rstrip('\n').split('\t')
        if len(f) >= 2 and not line.startswith('#'):
            out[f[1]] = f[0]
    return out


def main():
    addr = addresses()
    old = renamed_from()
    ram_data = {v: k for k, v in addr.items() if re.match(r'D_8[0-9A-F]{7}$', old.get(k, k))}
    s_refs, l_refs = src_refs(), ll_refs()
    names = set(s_refs) | set(l_refs)
    rows, fails, info = [], [], []
    for n in sorted(names):
        v = addr.get(n)
        if v is None:
            m = re.match(r'D_([0-9A-Fa-f]{8})$', old.get(n, n))
            v = int(m[1], 16) if m else None
        if v is None or v >= LOW_LIMIT:
            continue
        files = sorted(s_refs.get(n, set()) | l_refs.get(n, set()))
        alias_t = ram_data.get(0x80000000 | v)
        kind = 'alias' if alias_t else 'absolute'
        st = 'OK'
        if kind == 'absolute':
            if n in ROM_ABS:
                if ROM_ABS[n] != v:
                    st = f'FAIL ROM_ABS value 0x{ROM_ABS[n]:X} != link 0x{v:X}'
            elif n in RAM_ALIAS:
                st = f'FAIL RAM_ALIAS -> {RAM_ALIAS[n]} but 0x{0x80000000 | v:08X} is no known RAM data symbol'
            else:
                st = 'FAIL missing ROM_ABS entry'
        else:
            if n in RAM_ALIAS:
                if RAM_ALIAS[n] != alias_t:
                    st = f'FAIL RAM_ALIAS -> {RAM_ALIAS[n]}, link value aliases {alias_t}'
            elif n in ROM_ABS and n in REVIEWED_ABS:
                kind = 'absolute*'
                if ROM_ABS[n] != v:
                    st = f'FAIL ROM_ABS value 0x{ROM_ABS[n]:X} != link 0x{v:X}'
            elif n in ROM_ABS:
                st = f'FAIL in ROM_ABS but 0x{0x80000000 | v:08X} is RAM data {alias_t}: alias or number? decide, then RAM_ALIAS or REVIEWED_ABS'
            else:
                st = f'FAIL missing RAM_ALIAS entry -> {alias_t}'
        where = ('src+ll' if n in s_refs and n in l_refs else 'src' if n in s_refs else 'll')
        rows.append((n, v, kind, alias_t or '', st, where, files))
        if st != 'OK':
            fails.append(n)
    for tab, d in (('ROM_ABS', ROM_ABS), ('RAM_ALIAS', RAM_ALIAS)):
        for n in sorted(d):
            if n not in names:
                info.append(f'INFO {tab} {n}: no NM C reference (stale entry or used only by asm/ROM data)')
    print('name\tvalue\tkind\talias_of\tstatus\tseen_in\tfiles')
    for n, v, kind, a, st, where, files in rows:
        if QUIET and st == 'OK':
            continue
        print(f'{n}\t0x{v:X}\t{kind}\t{a}\t{st}\t{where}\t{",".join(files[:4])}{" ..." if len(files) > 4 else ""}')
    for l in info:
        print(l)
    nabs = sum(1 for r in rows if r[2].startswith('absolute')); nal = len(rows) - nabs
    print(f'romabs_check: {len(rows)} low D_ symbols in NM C ({nabs} absolute, {nal} RAM alias); '
          f'ROM_ABS {len(ROM_ABS)}, RAM_ALIAS {len(RAM_ALIAS)}; ll files {"yes" if l_refs else "none (no port build)"}; '
          f'{len(fails)} FAIL' + (': ' + ' '.join(fails) if fails else ''))
    return 1 if fails else 0


if __name__ == '__main__':
    sys.exit(main())
