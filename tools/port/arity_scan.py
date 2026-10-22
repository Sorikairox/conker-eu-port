#!/usr/bin/env python3
"""arity_scan.py (P79): find calls where the C passes FEWER arguments than the N64 code provides.

Why: IDO code often leaves a value in a0..a3 that the callee uses although the decomp's C call passes nothing
(`f()` through a K&R `void f();` declaration, or a `void (*)(void)` pointer). On N64 it works by accident; in the
port sigs.py fills missing arguments with 0 (direct) or the icall passes none (indirect) -> wrong object / NULL
writes. Known cases: func_1503BCAC() in func_1503482C (P75), D_80082ECC[idx]() in func_1501396C (P78).

Usage (from the worktree root, after `eval "$(tools/eu_port/wt.sh env <wt>)"`):
    python3 tools/port/arity_scan.py [--out docs/port/arity_scan.tsv] [--top 30] [--func NAME] [--redis]

Method
  C side  : clang IR of the browser build, port/build/ll/*.c.ll and port__*.ll (the -O0 IR *before* sigs.py,
            so a K&R call shows exactly what the C passes: `call void @func_1503BCAC()`). For every defined
            function: its parameter count, and its call sites in source order (direct callee + nargs, or
            indirect + nargs + the global the pointer was loaded from, traced back through load/store/gep).
  asm side: the matching EU ELF (conker/build/conker.eu.elf == ROM) disassembled once with the container's
            mips-linux-gnu-objdump into port/build/arity/eu_elf.dis (cached; --redis forces a refresh).
            Forward may-dataflow per function over a0..a3, f12/f14 and the outgoing stack slots 0x10..0x2C(sp):
            tags E (entry value, never written), W (written since the last call), X (clobbered by a call).
            At each jal/jalr (state after its delay slot) arg slot i counts as PROVIDED when a_i is W, or E and
            i < the caller's own arity (C definition if the caller is C, else its asm live-in arity). f12/f14
            are not counted at calls (IDO uses them as FP temps). Stack slots 0x10.. extend the count only
            when a0..a3 are all provided and the slot is never loaded back in the function (else it is a
            local). Function asm live-in arity = highest a-reg / f12,f14 / stack arg slot read while still E,
            plus a fixpoint for pass-through wrappers (a0.. never written and handed to a callee that reads
            them, e.g. func_15084000 -> func_1505EEF4).
            asm_regs column: per provided reg W (written since last call) and/or E (caller's entry value).
  tables  : the ELF data sections (objdump -s) and symbols (-t) give, for an indirect call whose pointer the
            IR traces to a global table, the functions stored in that table (words up to the next data
            symbol, max 1 KiB); callee_asm_in is then the max live-in over those targets.
  matching: k-th C direct call to f <-> k-th `jal f` in the caller's asm; k-th C indirect call <-> k-th jalr.
            When the counts differ the site uses the max over all asm sites (match=loose; none = no asm call).
Findings (kind column)
  D1  direct, callee is C and passed < its C definition (port passes 0 for the rest: P75's missing_args.txt
      method). Includes byval-struct vs scalar-list mismatches (func_15049350: 1 struct of 9 words < 9).
  D2  direct, callee is still asm/stub, passed < callee asm live-in and the asm site provides more (latent:
      becomes a bug when the callee is converted).
  D3  direct, callee is C, passed == its definition (no byval/double/i64 params) but callee asm live-in AND
      the site provide more (the C definition itself is too narrow).
  I   indirect, the asm at the jalr provides more arguments than the C passes.
severity = min(asm_n, what the callee/targets read) - passed; severity <= 0 (asm provides nothing more, or no
known target reads more) sorts last: the port matches N64 there. Unknown table ('?'/no targets) uses asm_n.
Rank (after severity>0): tier 3 = caller, callee or a table target is named in the browser boot logs
(docs/port/sessions/p75, p78: stub hits and traces); tier 2 = caller statically reachable from those or
port__game_* through direct edges (C calls + asm jal; table edges excluded, they reach ~everything) AND the
callee / a target is C; tier 1 = one of the two; then kind (D1, I, D3, D2) and severity.
Columns of docs/port/arity_scan.tsv:
  rank tier kind caller callee_or_table TU passed declC callee_asm_in asm_n match site severity asm_regs
Caveats: may-analysis (a W on any path counts; an a-reg written for a later use or by a loop back edge is a
false "provided"); E only means the caller's value is still there, not that the C meant to pass it;
indirect pointers that are struct fields show '?'. Every row needs a look at the asm before a fix.
"""
import os, re, sys, glob, subprocess, collections

ROOT = os.environ.get('CONKER_ROOT') or os.getcwd()
if not os.path.isdir(os.path.join(ROOT, 'port/build/ll')):
    sys.exit('run from the worktree root after eval "$(tools/eu_port/wt.sh env <wt>)" (no port/build/ll under %s)' % ROOT)
LL = os.path.join(ROOT, 'port/build/ll')
ELF = os.path.join(ROOT, 'conker/build/conker.eu.elf')
DIS = os.path.join(ROOT, 'port/build/arity/eu_elf.dis')
LOGDIRS = [os.path.join(ROOT, 'docs/port/sessions', d) for d in ('p75', 'p78')]
args = sys.argv[1:]
def opt(name, dflt=None):
    return args[args.index(name) + 1] if name in args else dflt
OUT = opt('--out', os.path.join(ROOT, 'docs/port/arity_scan.tsv'))
TOP = int(opt('--top', '30'))
ONLY = opt('--func')

# ------------------------------------------------------------------ C side (IR)
def split_top(s):
    out, d, cur = [], 0, ''
    for ch in s:
        if ch in '([{<': d += 1
        elif ch in ')]}>': d -= 1
        if ch == ',' and d == 0: out.append(cur); cur = ''
        else: cur += ch
    if cur.strip(): out.append(cur)
    return [x.strip() for x in out]

def call_args(line, start):
    """argument string of the call whose '(' is at index start."""
    d = 0
    for j in range(start, len(line)):
        if line[j] == '(': d += 1
        elif line[j] == ')':
            d -= 1
            if d == 0: return line[start + 1:j]
    return ''

DEF = re.compile(r'^define\s.*?@([\w.$]+)\((.*)\)[^(]*\{\s*$')
CALL = re.compile(r'\b(?:call|invoke)\b.*?\s(@[\w.$]+|%[\w.$]+)\(')
cdefs = {}            # func -> (nparams, variadic, tu)
csites = {}           # func -> [(callee or None, nargs, table)]
for p in sorted(glob.glob(LL + '/*.c.ll') + glob.glob(LL + '/port__*.ll')):
    if p.endswith('.v.ll'): continue
    tu = os.path.basename(p).replace('.c.ll', '').replace('.ll', '')
    cur = None; body = []
    for line in open(p, errors='replace'):
        if cur is None:
            m = DEF.match(line)
            if m:
                ps = split_top(m.group(2))
                var = '...' in ps
                plain = not any(re.search(r'byval|\bdouble\b|\bi64\b', x) for x in ps)   # 1 param == 1 O32 word
                cur = m.group(1); cdefs[cur] = (len([x for x in ps if x != '...']), var, tu, plain); body = []
            continue
        if line.startswith('}'):
            # resolve indirect-call pointer origins: %x = load ptr, ptr %y / store ptr %a, ptr %y / gep @G
            defs = {}
            stores = {}
            for l in body:
                m = re.match(r'\s*(%[\w.$]+) = (.*)', l)
                if m: defs[m.group(1)] = m.group(2)
                m = re.match(r'\s*store ptr (%[\w.$]+|@[\w.$]+), ptr (%[\w.$]+)', l)
                if m: stores.setdefault(m.group(2), []).append(m.group(1))
            def origin(v, depth=0):
                if depth > 12: return None
                if v.startswith('@'): return v[1:]
                e = defs.get(v, '')
                g = re.search(r'@([\w.$]+)', e)
                if g and not e.startswith('call'): return g.group(1)
                m = re.match(r'load ptr, ptr (%[\w.$]+)', e)
                if m:
                    src = m.group(1)
                    if src in stores: return origin(stores[src][-1], depth + 1)
                    return origin(src, depth + 1)
                m = re.match(r'(?:getelementptr\b.*?|bitcast )?.*?ptr (%[\w.$]+)', e)
                if m and m.group(1) != v: return origin(m.group(1), depth + 1)
                return None
            sites = []
            for l in body:
                if 'call' not in l and 'invoke' not in l: continue
                m = CALL.search(l)
                if not m: continue
                tgt = m.group(1)
                if tgt.startswith('@llvm.') or tgt.startswith('@__'): continue
                n = len(split_top(call_args(l, m.end() - 1)))
                if tgt.startswith('@'): sites.append((tgt[1:], n, None))
                else: sites.append((None, n, origin(tgt) or '?'))
            csites[cur] = sites
            cur = None
            continue
        body.append(line)

# ------------------------------------------------------------------ asm side (EU ELF)
if '--redis' in args or not os.path.exists(DIS) or os.path.getmtime(DIS) < os.path.getmtime(ELF):
    os.makedirs(os.path.dirname(DIS), exist_ok=True)
    rel = os.path.relpath(ELF, ROOT)
    dk = '/Applications/Docker.app/Contents/Resources/bin/docker'
    cont = os.environ.get('CONKERDEV', 'conkerdev')
    with open(DIS, 'w') as fo:
        subprocess.run([dk, 'exec', cont, 'mips-linux-gnu-objdump', '-d', '--no-show-raw-insn', '/conker/' + rel],
                       stdout=fo, check=True)

afuncs = collections.OrderedDict()   # name -> [(addr, op, ops)]
cur = None
for line in open(DIS):
    m = re.match(r'^([0-9a-f]{8}) <([^>]+)>:', line)
    if m: cur = m.group(2); afuncs[cur] = []; continue
    m = re.match(r'^\s*([0-9a-f]+):\t(\S+)\t?(.*)$', line)
    if m and cur:
        afuncs[cur].append((int(m.group(1), 16), m.group(2), m.group(3).strip()))

GPR = set('zero at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 t8 t9 s0 s1 s2 s3 s4 s5 s6 s7 s8 k0 k1 gp sp fp ra'.split())
STORES = {'sb', 'sh', 'sw', 'swl', 'swr', 'sd', 'swc1', 'sdc1'}
NODEF = STORES | {'jr', 'mult', 'multu', 'div', 'divu', 'dmult', 'dmultu', 'ddiv', 'ddivu', 'mtlo', 'mthi',
                  'teq', 'tne', 'break', 'nop', 'j', 'b', 'jal', 'sync', 'cache', 'eret'}
TRK = ['a0', 'a1', 'a2', 'a3', '$f12', '$f13', '$f14', '$f15']
SLOT = {'a0': 0, 'a1': 1, 'a2': 2, 'a3': 3, '$f12': 0, '$f13': 0, '$f14': 1, '$f15': 1}

def regs(s):
    return [r for r in re.findall(r'\$?\w+', s) if r in GPR or re.match(r'\$f\d+$', r)]

def defuse(op, ops):
    o = split_top(ops) if ops else []
    rs = [regs(x) for x in o]
    flat = [r for x in rs for r in x]
    dbl = op.endswith('.d') or op in ('ldc1', 'sdc1')
    def pair(rr):
        return rr + ['$f%d' % (int(r[2:]) + 1) for r in rr if dbl and r.startswith('$f')]
    if op in NODEF or (op.startswith('b') and op not in ('bal', 'bgezal', 'bltzal')) or op.startswith('c.'):
        return [], pair(flat)
    if op in ('jalr', 'bal', 'bgezal', 'bltzal'): return ['ra'], flat
    if op in ('mtc1', 'ctc1', 'dmtc1'): return (rs[1] if len(rs) > 1 else []), rs[0] if rs else []
    if not o: return [], []
    return pair(rs[0]), pair([r for x in rs[1:] for r in x])

def analyse(name, own_arity=None):
    """-> (livein_arity, [(target or None, provided_slots set)])"""
    ins = afuncs[name]; N = len(ins)
    addr2i = {a: i for i, (a, _, _) in enumerate(ins)}
    frame = 0
    readback = set(int(m.group(1)) for _, op, ops in ins if op[0] == 'l'
                   for m in [re.search(r'(-?\d+)\(sp\)$', ops)] if m)   # locals, not outgoing args
    for _, op, ops in ins[:4]:
        m = re.match(r'sp,sp,-(\d+)$', ops)
        if op == 'addiu' and m: frame = int(m.group(1))
    succ = [[] for _ in range(N + 1)]
    callat = {}
    def btarget(ops):
        m = re.search(r'([0-9a-f]+) <', ops)
        return addr2i.get(int(m.group(1), 16)) if m else None
    i = 0
    while i < N:
        _, op, ops = ins[i]
        nx = i + 1 if i + 1 < N else N
        if op in ('jal', 'jalr', 'bal', 'bgezal', 'bltzal'):
            if op == 'jal':
                m = re.search(r'<([^>+]+)>', ops); t = m.group(1) if m else '?'
            elif op == 'jalr': t = None
            else: t = '?'
            succ[i] = [nx]
            if i + 1 < N:
                succ[i + 1] = [i + 2 if i + 2 < N else N]; callat[i + 1] = t
            i += 2; continue
        isbr = (op.startswith('b') and op not in ('break',)) or op in ('j', 'jr')
        if isbr:
            likely = op.endswith('l') and op not in ('b', 'bal')
            if op == 'jr': tt = [N] if ops == 'ra' else []
            else:
                t = btarget(ops); tt = [t] if t is not None else ([N] if op == 'j' else [])
            uncond = op in ('b', 'j', 'jr') or (op == 'beq' and ops.startswith('zero,zero'))
            fall = [] if uncond else [i + 2 if i + 2 < N else N]
            if i + 1 < N:
                if likely: succ[i] = [i + 1] + fall; succ[i + 1] = tt
                else: succ[i] = [i + 1]; succ[i + 1] = tt + fall
            else: succ[i] = tt + fall
            i += 2; continue
        succ[i] = [nx]; i += 1
    init = {r: frozenset('E') for r in TRK}
    for k in range(4, 12): init['s%d' % k] = frozenset()
    states = [None] * (N + 1); states[0] = init
    work = [0]; livein = set(); calls = {}
    while work:
        i = work.pop()
        if i >= N: continue
        st = dict(states[i])
        _, op, ops = ins[i]
        d, u = defuse(op, ops)
        for r in u:
            if r in st and 'E' in st[r]: livein.add(SLOT[r])
        m = re.search(r'(-?\d+)\(sp\)$', ops)
        if m:
            off = int(m.group(1))
            if op in STORES and 0x10 <= off < 0x30 and off not in readback:
                st['s%d' % (4 + (off - 0x10) // 4)] = frozenset('W')
            elif op[0] == 'l' and off >= frame + 0x10:
                livein.add((off - frame) // 4)
        for r in d:
            if r in st: st[r] = frozenset('W')
        if i in callat:
            pr = set(); how = []
            for r in ('a0', 'a1', 'a2', 'a3'):     # f12/f14 are free FP temps in IDO code: not counted at a call
                w = 'W' in st[r]; e = 'E' in st[r] and own_arity is not None and SLOT[r] < own_arity
                if w or e: pr.add(SLOT[r]); how.append(r + ':' + ('W' if w else '') + ('E' if e else ''))
            n = 0
            while n < 4 and n in pr: n += 1
            hi = max(pr) + 1 if pr else 0
            if n == 4:
                while 's%d' % n in st and 'W' in st['s%d' % n]: n += 1
                if n > 4: how.append('stk:%d' % (n - 4))
            ein = set()                 # contiguous prefix a0.. of never-written entry regs (pass-through)
            for r in ('a0', 'a1', 'a2', 'a3'):
                if st[r] != frozenset('E'): break
                ein.add(SLOT[r])
            calls[i] = (callat[i], max(n, hi), ' '.join(how) or '-', ein)
            for r in TRK: st[r] = frozenset('X')
            for k in range(4, 12): st['s%d' % k] = frozenset()
        for j in succ[i]:
            if j is None: continue
            old = states[j]
            if old is None: states[j] = st; work.append(j); continue
            ch = False; new = dict(old)
            for k, v in st.items():
                w = new.get(k, frozenset()) | v
                if w != new.get(k): new[k] = w; ch = True
            if ch: states[j] = new; work.append(j)
    return (max(livein) + 1 if livein else 0), [calls[k] for k in sorted(calls)]

# ELF symbols and data words: function-pointer tables (targets that can be stored in a table)
SYM = DIS.replace('.dis', '.sym'); DAT = DIS.replace('.dis', '.data')
for path, cmd in ((SYM, ['-t']), (DAT, ['-s', '-j', '.init_data', '-j', '.game_data', '-j', '.debugger_data'])):
    if '--redis' in args or not os.path.exists(path) or os.path.getmtime(path) < os.path.getmtime(ELF):
        with open(path, 'w') as fo:
            subprocess.run(['/Applications/Docker.app/Contents/Resources/bin/docker', 'exec',
                            os.environ.get('CONKERDEV', 'conkerdev'), 'mips-linux-gnu-objdump'] + cmd +
                           ['/conker/' + os.path.relpath(ELF, ROOT)], stdout=fo, check=True)
fstart, dsym = {}, {}
for line in open(SYM):
    m = re.match(r'^([0-9a-f]{8}) (.{7}) (\S+)\s+[0-9a-f]+ (\S+)$', line)
    if not m: continue
    a = int(m.group(1), 16)
    if 'F' in m.group(2) and m.group(3) in ('.init', '.game', '.debugger'): fstart[a] = m.group(4)
    elif a >= 0x80000000 or m.group(3).endswith('_data'): dsym[m.group(4)] = a
words = {}
for line in open(DAT):
    m = re.match(r'^ ([0-9a-f]{8}) ((?:[0-9a-f]{8} ?){1,4})', line)
    if m:
        a = int(m.group(1), 16)
        for j, w in enumerate(m.group(2).split()): words[a + 4 * j] = int(w, 16)
import bisect
daddrs = sorted(set(dsym.values()))
def table_targets(t):
    if t not in dsym: return []
    a = dsym[t]; k = bisect.bisect_right(daddrs, a)
    end = min(daddrs[k] if k < len(daddrs) else a + 1024, a + 1024)
    return [fstart[words[x]] for x in range(a, end, 4) if words.get(x) in fstart]

asm_in, base = {}, {}
for f in afuncs:
    try: asm_in[f], base[f] = analyse(f)
    except Exception: pass
for _ in range(20):     # pass-through wrappers: an entry a-reg handed unchanged to a callee that reads it
    ch = False
    for f, cl in base.items():
        for t, _, _, ein in cl:
            for sl in ein:
                if t in asm_in and sl < asm_in[t] and sl >= asm_in[f]: asm_in[f] = sl + 1; ch = True
    if not ch: break
asm_calls = {}
def asm_sites(f):
    if f not in asm_calls:
        own = cdefs[f][0] if f in cdefs else asm_in.get(f)
        asm_calls[f] = analyse(f, own)[1] if f in afuncs else None
    return asm_calls[f]

# ------------------------------------------------------------------ reachability
logged = set()
for d in LOGDIRS:
    for p in glob.glob(d + '/*.log'):
        logged |= set(re.findall(r'\b(func_[0-9A-F]{8})\b', open(p, errors='replace').read()))
roots = set(f for f in cdefs if cdefs[f][2].startswith('port__game')) | logged
def edges(f, tables=False):
    for t, _, tab in csites.get(f, []):
        if t: yield t
        elif tab and tables: yield from table_targets(tab)
    if f in afuncs and f not in cdefs:
        for t, _, _, _ in asm_sites(f) or []:
            if t and t != '?': yield t
reach = set(); stack = list(roots)      # direct edges only (C calls + asm jal); tables explode to ~everything
while stack:
    f = stack.pop()
    if f in reach: continue
    reach.add(f)
    stack.extend(t for t in edges(f) if t not in reach)

# ------------------------------------------------------------------ findings
rows = []
for caller, sites in csites.items():
    if ONLY and caller != ONLY: continue
    asites = asm_sites(caller)
    tu = cdefs[caller][2]
    seen = collections.Counter()
    for callee, n, table in sites:
        key = callee or '<jalr>'
        k = seen[key]; seen[key] += 1
        asm_n, match, how = '-', '-', '-'
        if asites is not None:
            cand = [(c, h) for t, c, h, _ in asites if (t == callee if callee else t is None)]
            tot = sum(1 for c, _, _ in sites if (c == callee if callee else c is None))
            if cand:
                if len(cand) == tot: (asm_n, how), match = cand[k], 'exact'
                else: (asm_n, how), match = max(cand), 'loose'
            else: match = 'none'
        an = asm_n if isinstance(asm_n, int) else None
        if callee:
            declc = cdefs[callee][0] if callee in cdefs and not cdefs[callee][1] else None
            ain = asm_in.get(callee)
            kind = None
            if declc is not None and n < declc: kind = 'D1'
            elif declc is None and callee not in cdefs and ain is not None and n < ain and an is not None and an > n: kind = 'D2'
            elif declc is not None and n == declc and cdefs[callee][3] and ain is not None and ain > n and an is not None and an > n: kind = 'D3'
            if not kind: continue
            name = callee
        else:
            declc, ain = None, None
            if an is None or an <= n: continue
            kind, name = 'I', table
            tg = table_targets(table)
            ain = max((asm_in.get(x, 0) for x in tg), default=None)
            if tg: name = '%s[%s]' % (table, ','.join(tg[:4]) + (',+%d' % (len(tg) - 4) if len(tg) > 4 else ''))
        tg = [callee] if callee else table_targets(table)
        anyc = any(x in cdefs for x in tg)
        tier = 3 if (caller in logged or any(x in logged for x in tg)) else 2 if (caller in reach and anyc) \
            else 1 if (caller in reach or anyc) else 0
        # severity: extra words the callee can see that the port drops; 0 = harmless (asm or callee uses none)
        uses = ain if isinstance(ain, int) else (declc if isinstance(declc, int) else 99)
        if kind == 'D1': uses = max(uses, declc)
        gap = min(an if an is not None else uses, uses) - n
        rows.append([tier, kind, caller, name, tu, n, '-' if declc is None else declc, '-' if ain is None else ain,
                     asm_n, match, k, gap, how])

korder = {'D1': 0, 'I': 1, 'D3': 2, 'D2': 3}
# D1 sites where the asm provides nothing more are still port deviations but harmless: rank them last in tier
rows.sort(key=lambda r: (r[11] <= 0, -r[0], korder[r[1]], -r[11], r[2]))
os.makedirs(os.path.dirname(OUT), exist_ok=True)
with open(OUT, 'w') as fo:
    fo.write('rank\ttier\tkind\tcaller\tcallee_or_table\tTU\tpassed\tdeclC\tcallee_asm_in(I:max_of_table)\tasm_n\tmatch\tsite\tseverity\tasm_regs\n')
    for i, r in enumerate(rows):
        fo.write('\t'.join(str(x) for x in [i + 1] + r[:13]) + '\n')
cnt = collections.Counter(r[1] for r in rows)
real = collections.Counter(r[1] for r in rows if r[11] > 0)
print('C funcs %d, asm funcs %d, logged %d, reachable %d' % (len(cdefs), len(afuncs), len(logged), len(reach)))
print('findings', dict(cnt), '| severity>0 (asm provides AND callee/targets read more than passed)', dict(real))
print('wrote', os.path.relpath(OUT, ROOT))
print('rank\ttier\tkind\tcaller\tcallee/table\tTU\tpassed\tdeclC\tcallee_in\tasm_n\tmatch')
for i, r in enumerate(rows[:TOP]):
    print('\t'.join(str(x) for x in [i + 1] + r[:10] + [r[12]]))
