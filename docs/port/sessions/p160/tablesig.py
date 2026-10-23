#!/usr/bin/env python3
# P160: function-pointer table signature scan. For every run of >= 2 consecutive function addresses in the EU ELF's
# data sections (.init_data / .game_data), look up each entry's NM C definition (NON_MATCHING branches selected)
# and compare it with how the table's dispatchers use it:
#   - asm dispatchers (a still-GLOBAL_ASM function referencing the table): is v0 read after the jalr before it is
#     written (= the caller uses a return value)?
#   - C dispatchers (NM C referencing the table symbol): the line is listed for review (call used in an expression?).
# Reports: (a) tables whose C entries disagree on return kind (void / value) or parameter count,
#          (b) void C entries in tables whose asm dispatcher reads v0 after the jalr (P159 func_151C1EF0 case).
# Run from the worktree root: python3 docs/port/sessions/p160/tablesig.py  (needs docker container conkerdev-portb)
import re, glob, struct, subprocess, sys, os
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
sh = subprocess.run(['docker', 'exec', '-w', '/conker/conker', 'conkerdev-portb', 'mips-linux-gnu-readelf', '-SW',
                     'build/conker.eu.elf'], capture_output=True, text=True).stdout
# P160: split runs at addresses that some code names (D_xxxxxxxx referenced in asm or C): adjacent tables otherwise merge
named = set()
for a in glob.glob('conker/asm/nonmatchings/**/*.s', recursive=True) + glob.glob('conker/src_eu/**/*.c', recursive=True):
    for m in re.finditer(r'\bD_([0-9A-F]{8})\b', open(a, errors='replace').read()):
        named.add(int(m.group(1), 16))
tables = []   # (va, [fn...])
for l in sh.split('\n'):
    m = re.search(r'\]\s+(\.\w*data)\s+PROGBITS\s+([0-9a-f]+)\s+([0-9a-f]+)\s+([0-9a-f]+)', l)
    if not m: continue
    va, off, sz = (int(m.group(i), 16) for i in (2, 3, 4))
    run = []
    for i in range(0, sz - 3, 4):
        w = struct.unpack('>I', data[off + i:off + i + 4])[0]
        if w in addr2fn and not (run and va + i in named):
            run.append((va + i, addr2fn[w]))
            continue
        if len(run) >= 2: tables.append((run[0][0], [f for _, f in run]))
        run = [(va + i, addr2fn[w])] if w in addr2fn else []
    if len(run) >= 2: tables.append((run[0][0], [f for _, f in run]))

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

def asm_uses_v0(path, tsym):
    """True / False / None: after the jalr through tsym's entry, is v0 read before it is written / a call / return?"""
    L = [re.sub(r'/\*.*?\*/', '', x).strip() for x in open(path, errors='replace')]
    if not any(tsym in x for x in L): return None
    res = None
    for i, x in enumerate(L):
        if not x.startswith('jalr'): continue
        j = i + 2   # skip the delay slot
        while j < len(L):
            y = L[j]
            if not y or y.endswith(':') or y.startswith('.') or y.startswith('glabel'): j += 1; continue
            op = y.split()[0]
            args = y[len(op):].split(',')
            if op in ('jal', 'jalr', 'jr'): res = res or False; break
            if '$v0' in ','.join(args[1:]) or (op.startswith('b') and '$v0' in y) or (op.startswith('s') and '$v0' in args[0]):
                return True
            if args and args[0].strip() == '$v0': res = res or False; break
            j += 1
    return res

asmfiles = glob.glob('conker/asm/nonmatchings/**/*.s', recursive=True)
out = []
nprob = 0
for va, fns in tables:
    sym = 'D_%08X' % va
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
        if sym in s: adisp.append((fn, asm_uses_v0(a, sym)))
    cdisp = [(p, l.strip()) for p, t in code_by_file.items() for l in t.split('\n') if sym in l and 'extern' not in l]
    probs = []
    if len(kinds) > 1: probs.append('mixed return kinds %s' % sorted(kinds))
    if len(arities) > 1: probs.append('mixed arities %s' % sorted(arities))
    uses = [fn for fn, u in adisp if u]
    if uses and 'void' in kinds:
        probs.append('void entries %s but asm dispatcher(s) %s read v0' % (
            ','.join(f for f, d in cent.items() if d[0] == 'void'), ','.join(uses)))
    if probs: nprob += 1
    out.append('%s %d entries (%d C) %s | asm disp: %s | C disp: %d%s' % (
        sym, len(fns), len(cent), ' ; '.join(probs) or 'ok',
        ' '.join('%s%s' % (f, '(v0)' if u else '') for f, u in adisp) or '-', len(cdisp),
        ''.join('\n      C: %s: %s' % (os.path.basename(p), l[:150]) for p, l in cdisp[:4]) if probs else ''))
    if probs:
        for f in fns:
            d = defs.get(f)
            out.append('      %s %s' % (f, '%s/%d %s' % (d[0], d[1], os.path.basename(d[2])) if d else 'asm'))
print('tables:', len(tables), 'with C entries:', sum(1 for l in out if l.startswith('D_')), 'flagged:', nprob)
print('\n'.join(l for l in out))
