#!/usr/bin/env python3
# P160: function-pointer table signature scan. For every run of >= 2 consecutive function addresses in the EU ELF's
# data sections (.init_data / .game_data), look up each entry's NM C definition (NON_MATCHING branches selected)
# and compare it with how the table's dispatchers use it:
#   - asm dispatchers (a still-GLOBAL_ASM function referencing the table): is v0 read after the jalr before it is
#     written (= the caller uses a return value)?
#   - C dispatchers (NM C referencing the table symbol): the line is listed for review (call used in an expression?).
# Reports: (a) tables whose C entries disagree on return kind (void / value) or parameter count,
#          (b) void C entries in tables whose asm dispatcher reads v0 after the jalr (P159 object_filter_not_listed case).
# P162: D_ names resolved to EU addresses via undefined_syms.eu.txt (US names like D_80082FA4 live elsewhere in EU);
#       each jalr is tied to the table it loads from (register trace), only those jalrs are checked for v0 / f0 use.
# Run from the worktree root: python3 tools/port/tablesig.py (P253: moved from docs/port/sessions/p214; the container
# comes from $CONKERDEV, i.e. eval "$(tools/eu_port/wt.sh env <name>)" first; it was hard-coded to conkerdev-port)
import re, glob, struct, subprocess, sys, os
import os as _os
CTR = _os.environ.get('CONKERDEV')
if not CTR:
    raise SystemExit('tablesig: set CONKERDEV (eval "$(tools/eu_port/wt.sh env <name>)")')
sys.path.insert(0, os.path.dirname(__file__))
ELF = 'conker/build/conker.eu.elf'
MAP = 'conker/build/conker.eu.map'

def nm_select(t):
    out, st = [], []
    for l in t.split('\n'):
        s = l.strip()
        if s.startswith('#if'):
            st.append('NM' if 'NON_MATCHING' in s and not s.startswith('#ifndef') else ('NOTNM' if 'NON_MATCHING' in s else 'X'))
        elif s.startswith('#else') and st:
            st[-1] = {'NM': 'NOTNM', 'NOTNM': 'NM'}.get(st[-1], st[-1])
        elif s.startswith('#endif') and st: st.pop()
        elif 'NOTNM' not in st: out.append(l)
    return '\n'.join(out)

# EU address -> function name (map file) ; names are what the sources use
addr2fn = {}
for l in open(MAP, errors='replace'):
    m = re.match(r'\s+0x([0-9a-f]{8})\s+(func_[0-9A-Fa-f]{8}\w*)\s*$', l)
    if m: addr2fn[int(m.group(1), 16)] = m.group(2)
data = open(ELF, 'rb').read()
sh = subprocess.run(['docker', 'exec', '-w', '/conker/conker', CTR, 'mips-linux-gnu-readelf', '-SW',
                     'build/conker.eu.elf'], capture_output=True, text=True).stdout
# P160: split runs at addresses that some code names (D_xxxxxxxx referenced in asm or C): adjacent tables otherwise merge
eu_of = {}   # P162: source name -> EU address
for l in open('conker/undefined_syms.eu.txt', errors='replace'):
    m = re.match(r'\s*(D_\w+)\s*=\s*0x([0-9A-Fa-f]+)', l)
    if m: eu_of[m.group(1)] = int(m.group(2), 16)
def sym_addr(s):
    if s in eu_of: return eu_of[s]
    m = re.match(r'D_(?:eu_)?([0-9A-F]{8})$', s)
    return int(m.group(1), 16) if m else None
names_at = {}
named = set()
for a in glob.glob('conker/asm/nonmatchings/**/*.s', recursive=True) + glob.glob('conker/src_eu/**/*.c', recursive=True):
    for m in re.finditer(r'\bD_(?:eu_)?[0-9A-F]{8}\b', open(a, errors='replace').read()):
        ad = sym_addr(m.group(0))
        if ad is None: continue
        named.add(ad); names_at.setdefault(ad, set()).add(m.group(0))
secs = []
def word_at(a):
    for va0, off0, sz0 in secs:
        if va0 <= a < va0 + sz0: return struct.unpack('>I', data[off0 + a - va0:off0 + a - va0 + 4])[0]
    return None
tables = []   # (va, [fn...] up to the next named address, [fn...] to the end of the raw run)
# P162: raw runs of function words; a table starts at the run start and at every named address inside it. A single
# named entry counts (D_80089EB8: one word, then D_80089EBC, but point_emitter_update indexes D_80089EB8 by a byte).
def flush(run):
    starts = [k for k, (a0, _) in enumerate(run) if k == 0 or a0 in named]
    for n, k in enumerate(starts):
        nxt = starts[n + 1] if n + 1 < len(starts) else len(run)
        if len(run) - k >= 2 or run[k][0] in named:
            tables.append((run[k][0], [f for _, f in run[k:nxt]], [f for _, f in run[k:]]))
for l in sh.split('\n'):
    m = re.search(r'\]\s+(\.\w*data)\s+PROGBITS\s+([0-9a-f]+)\s+([0-9a-f]+)\s+([0-9a-f]+)', l)
    if not m: continue
    va, off, sz = (int(m.group(i), 16) for i in (2, 3, 4))
    secs.append((va, off, sz))
    run = []
    for i in range(0, sz - 3, 4):
        w = struct.unpack('>I', data[off + i:off + i + 4])[0]
        if w in addr2fn: run.append((va + i, addr2fn[w])); continue
        if run: flush(run)
        run = []
    if run: flush(run)

# NM C definitions: name -> (return type text, nparams)
defs = {}
code_by_file = {}
for p in glob.glob('conker/src_eu/**/*.c', recursive=True):
    t = re.sub(r'/\*.*?\*/', '', open(p, errors='replace').read(), flags=re.S)
    t = re.sub(r'//[^\n]*', '', nm_select(t))
    code_by_file[p] = t
    for m in re.finditer(r'^(?:static\s+)?([A-Za-z_][\w\s\*]*?)\s*\**\s*\b(func_[0-9A-Fa-f]{8})\s*\(([^)]*)\)\s*\{', t, re.M):
        ret = m.group(1).strip()
        star = '*' in t[m.start():m.start(2)]
        prm = m.group(3).strip()
        n = 0 if prm in ('', 'void') else len(prm.split(','))
        defs[m.group(2)] = ('ptr' if star else ret, n, p)

def jalr_table(L, i):
    """P162: symbol whose address feeds the jalr at L[i] (lw $t9, %lo(SYM)(..) or lw $t9, off(base) with base built
    from a register loaded with %hi/%lo(SYM)); None if not resolved."""
    def defn(reg, k):
        for j in range(k - 1, -1, -1):
            y = L[j]
            if not y or y.startswith('glabel'): continue
            op = y.split()[0]; a = [x.strip() for x in y[len(op):].split(',')]
            if a and a[0] == reg and not op.startswith('s') and not op.startswith('b') and op not in ('jr',):
                return j, op, a
        return None
    def from_reg(reg, k, depth=0):
        d = defn(reg, k)
        if not d or depth > 4: return None
        j, op, a = d
        m = re.search(r'%(?:lo|hi)\((D_\w+)\)', L[j])
        if m: return m.group(1)
        if op in ('addu', 'or', 'move', 'addiu') :
            for r in a[1:]:
                if r.startswith('$') and r != '$zero':
                    s = from_reg(r, j, depth + 1)
                    if s: return s
        if op == 'lw':
            m = re.search(r'\((\$\w+)\)', a[1] if len(a) > 1 else '')
            if m: return from_reg(m.group(1), j, depth + 1)
        return None
    r = L[i].split()[1].strip()
    return from_reg(r, i)

def asm_uses_v0(path, tsyms):
    """True / False / None: after a jalr through one of tsyms (names of the table), is v0 (or f0) read before it is
    written / a call / return?"""
    L = [re.sub(r'/\*.*?\*/', '', x).strip() for x in open(path, errors='replace')]
    if not any(s in x for x in L for s in tsyms): return None
    res = None
    for i, x in enumerate(L):
        if not x.startswith('jalr'): continue
        if jalr_table(L, i) not in tsyms: continue
        j = i + 2   # skip the delay slot
        while j < len(L):
            y = L[j]
            if not y or y.endswith(':') or y.startswith('.') or y.startswith('glabel'): j += 1; continue
            op = y.split()[0]
            args = y[len(op):].split(',')
            if op in ('jal', 'jalr', 'jr'): res = res or False; break
            if op in ('mtc1', 'dmtc1') and args[1].strip() in ('$f0',): res = res or False; break   # f0 written
            for rg in ('$v0', '$f0'):
                if rg in ','.join(args[1:]) or (op.startswith('b') and rg in y) or (op.startswith('s') and rg in args[0]):
                    return rg
            if args and args[0].strip() in ('$v0', '$f0'): res = res or False; break
            j += 1
    return res

asmfiles = glob.glob('conker/asm/nonmatchings/**/*.s', recursive=True)
out = []
nprob = 0
for va, fns, full in tables:
    sym = 'D_%08X' % va
    syms = set(names_at.get(va, set())) | ({sym} if sym_addr(sym) == va else set())
    for back in (4, 8):   # P162: leading NULL entries (D_80082BFC = EU 0x80082F8C holds 0, entries from 0x80082F90)
        if word_at(va - back) != 0: break
        syms |= names_at.get(va - back, set())
    cent = {f: defs[f] for f in fns if f in defs}
    if not cent: continue
    kinds = {('void' if d[0] == 'void' else 'value') for d in cent.values()}
    arities = {d[1] for d in cent.values()}
    # dispatchers: asm (non-C) functions mentioning the symbol, C files mentioning it
    adisp = []
    for a in asmfiles:
        fn = os.path.basename(a)[:-2]
        if fn in defs: continue
        try: s = open(a, errors='replace').read()
        except OSError: continue
        if any(x in s for x in syms): adisp.append((fn, asm_uses_v0(a, syms)))
    cdisp = [(p, l.strip()) for p, t in code_by_file.items() for l in t.split('\n') if any(re.search(r'\b%s\b' % x, l) for x in syms) and 'extern' not in l]
    probs = []
    if len(kinds) > 1: probs.append('mixed return kinds %s' % sorted(kinds))
    if len(arities) > 1: probs.append('mixed arities %s' % sorted(arities))
    centf = {f: defs[f] for f in full if f in defs}   # entries the dispatcher can index (to the end of the raw run)
    uses = [fn for fn, u in adisp if u]
    fuses = [fn for fn, u in adisp if u == '$f0']
    if fuses:
        bad = [f for f, d in cent.items() if d[0] not in ('f32', 'f64')]
        if bad: probs.append('entries %s not float but asm dispatcher(s) %s read f0' % (','.join(bad), ','.join(fuses)))
    voids = [f for f, d in cent.items() if d[0] == 'void']
    vmore = [f for f, d in centf.items() if d[0] == 'void' and f not in cent and f not in fns]
    if uses and voids:
        probs.append('void entries %s but asm dispatcher(s) %s read v0/f0' % (','.join(voids), ','.join(uses)))
    if uses and vmore and not voids:   # only if the dispatcher indexes past the next named address (unknown extent)
        probs.append('maybe: void entries past the next named address %s' % ','.join(vmore[:6]))
    if probs: nprob += 1
    out.append('%s%s %d entries (%d C) %s | asm disp: %s | C disp: %d%s' % (
        sym, ('=' + '/'.join(sorted(syms - {sym}))) if syms - {sym} else '', len(fns), len(cent), ' ; '.join(probs) or 'ok',
        ' '.join('%s%s' % (f, '(%s)' % u[1:] if u else '') for f, u in adisp) or '-', len(cdisp),
        ''.join('\n      C: %s: %s' % (os.path.basename(p), l[:150]) for p, l in cdisp[:4]) if probs else ''))
    if probs:
        for f in fns:
            d = defs.get(f)
            out.append('      %s %s' % (f, '%s/%d %s' % (d[0], d[1], os.path.basename(d[2])) if d else 'asm'))
print('tables:', len(tables), 'with C entries:', sum(1 for l in out if l.startswith('D_')), 'flagged:', nprob)
print('\n'.join(l for l in out))
