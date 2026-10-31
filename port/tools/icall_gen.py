"""Generate port/stubs/icall_tab.c (docs/port/MEMORY.md, "Indirect calls"; see port/tools/icall.py).

  * registers the functions of the objects that do not go through the vbe pass (asm stubs,
    n64mem function stubs, the PC layer) with their exact wasm signatures;
  * `__port_icall_slow`: one case per wasm signature that any registered function has (the game
    TUs list theirs in port/build/ll/*.v.ll.isig), calling the target with its own type.
usage: icall_gen.py OUT.c OBJ...   (inside the conker-emsdk container)"""
import glob, sys, os
sys.path.insert(0, os.path.dirname(__file__))
import wasmobj
from icall import sig_id

LETTER = {'i32': 'i', 'i64': 'I', 'f32': 'f', 'f64': 'd'}
CT = {'i': 'int', 'I': 'long long', 'f': 'float', 'd': 'double', 'v': 'void'}


# Function-pointer tables in the ROM's game_data (N64 address, entries) used by the self-test:
# effect handlers (characterflamethrower), a 256-entry handler table, two object tables.
TEST_TABLES = [(0x8008FC10, 12), (0x80084840, 256), (0x8008A860, 262), (0x80089E10, 76), (0x80086634, 48)]


def expectations(regs):
    """port_icall_check(): for each ROM table entry whose target has a known signature, the
    registry must give that signature for the relocated pointer (relocation + registration chain)."""
    import json, re, struct
    import n64mem
    from icall import wsig
    syms = n64mem.portsyms.elf_symbols()   # P328: frozen table (was the matching ELF)
    fstart = {}
    for nm, val, size, typ, bind, shndx, sec in syms:
        if typ == 2 and val and re.match(r'[A-Za-z_]\w*$', nm) and not nm.startswith(('L', 'jtbl')):
            fstart.setdefault(val, nm)
    can = json.load(open('port/build/sigdb.json'))
    gd = n64mem.segment_bytes(open(n64mem.ROM, 'rb').read(), n64mem.SEGS[1])
    rows = []
    for tab, n in TEST_TABLES:
        for i in range(n):
            v, = struct.unpack('>I', gd[tab - 0x80082EB0 + 4 * i:][:4])
            nm = fstart.get(v)
            ws = None
            if nm and '@' + nm in can:
                r, ps = can['@' + nm][:2]
                ws = None if '...' in ps else wsig(r, ps)
            elif nm in regs:
                ws = regs[nm]
            if ws:
                rows.append(f'    {{0x{tab + 4 * i:08X}u, {sig_id(ws)}u, "{nm}"}},')
    return ['', '/* self-test rows: N64 address of a table entry, expected signature id, target */',
            'static const struct { unsigned n64; unsigned sig; const char *name; } expect[] = {'] + rows + [
            '    {0, 0, 0}};', 'int port_icall_check(void) {',
            '    int bad = 0, n = 0;',
            '    for (int i = 0; expect[i].n64; i++, n++) {',
            '        void *fp = *(void **)port_n64_to_wasm(expect[i].n64);',
            '        unsigned got = __port_fsig(fp);',
            '        if (got != expect[i].sig && bad++ < 10)',
            '            port_log("[icall] check %08X %s: fn #%u registered as %s, want %s\\n", expect[i].n64,',
            '                     expect[i].name, (unsigned)(unsigned long)fp, port_fsig_name(got), port_fsig_name(expect[i].sig));',
            '    }',
            f'    port_log("[icall] registry check over {len(TEST_TABLES)} ROM function tables: %d/%d entries OK\\n", n - bad, n);',
            '    return bad;', '}']


AUDIT = 'port/tools/icall_void_audit.tsv'


def void_audit(regs):
    """P373: port_icall_void_audited(fp) for the void functions that AUDIT lists as called through a value-returning
    pointer with a harmless result (verdict `ok`: the caller ignores it, or the asm's v0 is 0 too) or a known unfixed one
    (verdict `open`, see the row's note). pc_icall.c logs every other void target such a site meets ("[icall]
    UNAUDITED ..."). Build-time checks: an `ok` / `open` row must name a void function the build defines (else the row
    is stale: a rename, or the function got a return type), a `fixed` row must name a function that is no longer void
    (the P372 / P373 fixes stay fixed)."""
    import json
    from icall import wsig
    can = json.load(open('port/build/sigdb.json'))

    def ret_of(nm):
        if '@' + nm in can:
            r, ps = can['@' + nm][:2]
            return r, (wsig('void', ps) or 'v:?').split(':')[1]
        if nm in regs:
            r, ps = regs[nm].split(':')
            return ('void' if r == 'v' else r), ps
        return None, None
    rows, errs = [], []
    for ln, l in enumerate(open(AUDIT), 1):
        f = l.rstrip('\n').split('\t')
        if not f[0] or f[0].startswith('#') or f[0] == 'function':
            continue
        nm, verdict = f[0], f[1]
        r, ps = ret_of(nm)
        if r is None:
            errs.append(f'{AUDIT}:{ln}: {nm} is not a function of this build (renamed? update the row)')
        elif verdict in ('ok', 'open') and r != 'void':
            errs.append(f'{AUDIT}:{ln}: {nm} returns {r} now: change its verdict to fixed')
        elif verdict == 'fixed' and r == 'void':
            errs.append(f'{AUDIT}:{ln}: {nm} is void again, but the audit found the caller needs its result')
        elif verdict not in ('ok', 'open', 'fixed'):
            errs.append(f'{AUDIT}:{ln}: verdict must be ok, open or fixed, not {verdict!r}')
        elif verdict in ('ok', 'open'):
            rows.append((nm, ps))
    if errs:
        sys.exit('icall_gen: ' + '\n'.join(errs))
    L = ['', f'/* P373: audited void targets of value-returning indirect calls ({AUDIT}) */']
    for j, (nm, ps) in enumerate(rows):
        L.append(f'void iva_{j}({", ".join(CT[p] for p in ps) or "void"}) __asm__("{nm}");')
    L += ['const char *port_icall_void_audited(void *fp) {']
    L += [f'    if (fp == (void *)iva_{j}) return "{nm}";' for j, (nm, ps) in enumerate(rows)]
    L += ['    return 0;', '}']
    return L, len(rows)


def main():
    out, objs = sys.argv[1], sys.argv[2:]
    regs, sigs, stubs = {}, set(), set()
    for o in objs:
        for nm, kind, flags, sig in wasmobj.read(o):
            if o.endswith('asm_stubs.o') and nm and kind == wasmobj.SYM_FUNC and not flags & (wasmobj.LOCAL | wasmobj.UNDEF):
                stubs.add(nm)
            if nm is None or kind != wasmobj.SYM_FUNC or flags & (wasmobj.LOCAL | wasmobj.UNDEF):
                continue
            if not nm.replace('_', 'a').isalnum() or nm in ('main',) or nm.startswith('__icall'):
                continue
            ps, rs = sig
            if any(t not in LETTER for t in ps + rs) or len(rs) > 1:
                continue
            ws = (LETTER[rs[0]] if rs else 'v') + ':' + ''.join(LETTER[t] for t in ps)
            regs.setdefault(nm, ws)
    for f in glob.glob('port/build/ll/*.isig'):
        sigs.update(l.strip() for l in open(f) if l.strip())
    sigs.update(regs.values())
    ids = {}
    for s in sorted(sigs):
        i = sig_id(s)
        assert ids.setdefault(i, s) == s, f'signature id collision: {s} {ids[i]}'
    L = ['/* GENERATED by port/tools/icall_gen.py - do not edit. Indirect-call signature table and',
         ' * mismatch dispatcher (docs/port/MEMORY.md, "Indirect calls"). */',
         '#include "../ultra/pc_icall.h"', '#include "../ultra/pc_mem.h"',
         'void port_log(const char *fmt, ...);', '']
    # exact wasm prototypes under local aliases (asm labels), so no declaration clashes with headers
    for j, (nm, ws) in enumerate(sorted(regs.items())):
        r, ps = ws.split(':')
        L.append(f'{CT[r]} icf_{j}({", ".join(CT[p] for p in ps) or "void"}) __asm__("{nm}");')
    L.append('static const PortFsig tab[] = {')
    L += [f'    {{(void *)icf_{j}, {sig_id(ws)}u}},' for j, (nm, ws) in enumerate(sorted(regs.items()))]
    L += ['    {0, 0}};', '__attribute__((constructor)) static void icall_tab_reg(void) {',
          f'    __port_fsig_reg(tab, {len(regs)});', '}', '',
          'const char *port_fsig_name(unsigned id) {', '    switch (id) {']
    # P23: the asm stubs (asm_stubs.o), for the pass-through indirect-call trampolines (icall.py)
    # only real stubs (their body calls port_stub_hit); alias forwarders run a C body
    import re as _re
    src = [o[:-2].replace('/build/stubs/', '/stubs/') + '.c' for o in objs if o.endswith('asm_stubs.o')]
    real = set()
    for f in src:
        if os.path.exists(f):
            real |= set(_re.findall(r'^__attribute__\(\(weak\)\) \w+ (\w+)\([^)]*\) \{ port_stub_hit', open(f).read(), _re.M))
    stubs = stubs & real if real else stubs
    sj = [j for j, (nm, ws) in enumerate(sorted(regs.items())) if nm in stubs]
    S = ['', '/* P23: asm stubs, for icall.py pass-through sites (x = fp(x, ...) returns x when fp is a stub) */',
         'static unsigned stubidx[] = {' + ', '.join(f'(unsigned)(unsigned long)(void *)icf_{j}' for j in sj) + (', 0};' if not sj else '};'),
         f'static const int nstub = {len(sj)};',
         'static int ucmp(const void *a, const void *b) { unsigned x = *(const unsigned *)a, y = *(const unsigned *)b; return x < y ? -1 : x > y; }',
         'void qsort(void *, unsigned long, unsigned long, int (*)(const void *, const void *));',
         'int __port_is_stub(void *fp) {',
         '    static int sorted; unsigned v = (unsigned)(unsigned long)fp; int lo = 0, hi = nstub - 1;',
         '    if (!sorted) { qsort(stubidx, nstub, sizeof(unsigned), ucmp); sorted = 1; }',
         'void port_stub_mark_dl(void);',
         '    while (lo <= hi) { int m = (lo + hi) >> 1; if (stubidx[m] == v) { port_stub_mark_dl(); return 1; } if (stubidx[m] < v) lo = m + 1; else hi = m - 1; }',
         '    return 0;', '}']
    L += [f'    case {i}u: return "{s}";' for i, s in sorted(ids.items())]
    L += ['    }', '    return "?";', '}', '',
          'unsigned long long __port_icall_slow(void *fp, unsigned tsig, const unsigned long long *b, int n,',
          '                                     unsigned k, unsigned rk) {',
          '    port_icall_note(fp, tsig, n, k, rk);', '    switch (tsig) {']
    for i, s in sorted(ids.items()):
        r, ps = s.split(':')
        args = ', '.join(f'A_{p}(b, n, k, {j})' for j, p in enumerate(ps))
        T = f'{CT[r]} (*)({", ".join(CT[p] for p in ps) or "void"})'
        if r == 'v':
            L.append(f'    case {i}u: (({T})fp)({args}); return 0;')
        else:
            L.append(f'    case {i}u: return R_{r}((({T})fp)({args}), rk);')
    L += ['    }', '    return 0;', '}']
    L += S
    L += expectations(regs)
    VA, nva = void_audit(regs)
    L += VA
    open(out, 'w').write('\n'.join(L) + '\n')
    print(f'icall_gen: {len(regs)} registered functions (non-vbe objects), {len(ids)} target signatures, {len(sj)} asm stubs, '
          f'{nva} audited void targets')


if __name__ == '__main__':
    main()
