#!/usr/bin/env python3
"""stubcalls.py (P107): which still-stub (asm) functions does each C function of the browser port reach?

Why: a correct C conversion still breaks the port when it feeds or dispatches to code that is still a stub
(P72 / P92: inputs from a stubbed producer; P100 / P105: the new C particle spawner impact_spark_spawn dispatched to
the asm-stub type handlers func_15148428 / func_151485AC through D_8008A5A0 / D_8008A644 -> null-zone writes,
trap). orchestrator rule since P97: before committing a frame-path function, list the stubs it calls directly
or through tables. This script makes that list.

Usage (worktree root, after `eval "$(tools/eu_port/wt.sh env <wt>)"`; needs a port build: port/build/ll/*.ll
from vbe_build.py and port/stubs/asm_stubs.c from gen_stubs.py, i.e. `port/web/run.sh build`):
    python3 port/tools/stubcalls.py [--log NODE_LOG] [--out docs/port/stubcalls.tsv] [--all] [--depth N]
                                    [--top 25] [--func NAME ...]
  --log    node / Chrome log with a `[stubs] N distinct asm stubs hit` census (node_run.js); default: the newest
           port_work/p*/*.log that has one. Hit counts come from its LAST census block.
  --all    rows for every C function (default: only NON_MATCHING C, i.e. converted functions)
  --depth  how far `deep` follows C->C direct calls (default 3)
  --func   print the full report of these functions (conversion slots: run this on the functions you are about
           to commit, after building the port with them; every stub listed must be C already, be committed in
           the same unit, or be shown harmless)
Before committing a conversion: build the port, then
    python3 port/tools/stubcalls.py --func func_XXXXXXXX
and check the direct / table / addr / deep stub lists.

Method
  stubs : port/stubs/asm_stubs.c (generated weak stubs; kind asm:<TU> / absolute / missing). Names a --wrap guard
          replaces (port/Makefile -Wl,--wrap=) are marked with `!` (their C body exists but a guard may run).
  C     : functions defined in the -O0 IR port/build/ll/*.c.ll and port__*.ll of TUs in the link (census ok,
          not in port/exclude.txt). NON_MATCHING = a `#pragma GLOBAL_ASM` for it sits in the #else branch of
          `#ifdef NON_MATCHING` in conker/src_eu (gen_stubs.py's scan, inverted).
  per C function F:
    direct : `call @S` with S a stub.
    table  : indirect calls whose pointer the IR traces to a global table @T (load/store/gep chain, as in
             tools/port/arity_scan.py); the table's words in the EU ELF data (from its symbol to the next
             symbol, max 1 KiB) that are function addresses give the targets; stub targets listed.
    addr   : stubs whose address F takes (`ptr @S` as a value: callbacks it registers / stores).
    unk    : number of indirect calls with an unknown pointer origin (struct field, argument) - not resolved.
    deep   : stubs found (direct / table / addr) in C functions F reaches through C->C direct calls, up to
             --depth levels, as STUB<C callee (the first C callee on the path).
  hits  : calls per stub in the census of --log; `hit` column = sum over direct + table + addr stubs.
Output docs/port/stubcalls.tsv, sorted by hit then number of stubs:
    func TU nm hit n_stubs direct table addr unk deep
  each stub as NAME:HITS (HITS 0 = not hit in that run; `!` = --wrap guard).
Caveats: one IR file per TU (static functions with the same name in two TUs are merged); ELF tables use the US
symbol names the source uses (mapped to EU addresses by the ELF symbol table); a struct-field pointer (`unk`)
can reach any stub - read the C.
"""
import os, re, sys, glob, subprocess, collections, bisect

ROOT = os.environ.get('CONKER_ROOT') or os.getcwd()
os.chdir(ROOT)
for need in ('port/build/ll', 'port/stubs/asm_stubs.c', 'port/build/census/files.tsv'):
    if not os.path.exists(need):
        sys.exit(f'{need} missing under {ROOT}: eval "$(tools/eu_port/wt.sh env <wt>)" and build the port first')
args = sys.argv[1:]
def opt(name, dflt=None):
    return args[args.index(name) + 1] if name in args else dflt
OUT = opt('--out', 'docs/port/stubcalls.tsv')
TOP = int(opt('--top', '25'))
DEPTH = int(opt('--depth', '3'))
FUNCS = list(dict.fromkeys(a for i, a in enumerate(args) if (i and args[i - 1] == '--func') or
                            re.fullmatch(r'func_[0-9A-F]{8}', a)))
ELF = 'conker/build/conker.eu.elf'
SYM, DAT = 'port/build/arity/eu_elf.sym', 'port/build/arity/eu_elf.data'

# ------------------------------------------------------------------ stubs, guards
stubs = {}
for l in open('port/stubs/asm_stubs.c'):
    m = re.search(r'\b(\w+)\([^)]*\)\s*\{\s*port_stub_hit\("(\w+)", "([^"]*)"', l)
    if m and not m[2].startswith('__real_'):
        stubs[m[2]] = m[3]
guards = set(re.findall(r'--wrap=(\w+)', open('port/Makefile').read()))

# ------------------------------------------------------------------ NON_MATCHING C functions (source scan)
nm = set()
for path in glob.glob('conker/src_eu/**/*.c', recursive=True):
    st = []
    for line in open(path, errors='replace'):
        s = line.strip()
        if s.startswith('#if'):
            st.append('nm' if re.match(r'#ifdef\s+NON_MATCHING\b', s) else
                      'nnm' if re.match(r'#ifndef\s+NON_MATCHING\b', s) else 'other')
        elif s.startswith('#else') and st:
            st[-1] = {'nm': 'nm_else', 'nnm': 'nnm_else'}.get(st[-1], st[-1])
        elif s.startswith('#endif') and st:
            st.pop()
        m = re.match(r'#pragma\s+GLOBAL_ASM\("([^"]+)"\)', s)
        if m and any(x in ('nm_else', 'nnm') for x in st):
            nm.add(os.path.splitext(os.path.basename(m[1]))[0])

# ------------------------------------------------------------------ IR of the linked TUs
linked = set()
excl = {l.split('\t')[0] for l in open('port/exclude.txt') if l.strip() and not l.startswith('#')}
for l in list(open('port/build/census/files.tsv'))[1:]:
    c = l.rstrip('\n').split('\t')
    if len(c) >= 4 and c[3] == 'ok' and c[0] not in excl:
        linked.add(c[0].replace('/', '__'))

def split_top(s):
    out, d, cur = [], 0, ''
    for ch in s:
        if ch in '([{<': d += 1
        elif ch in ')]}>': d -= 1
        if ch == ',' and d == 0: out.append(cur); cur = ''
        else: cur += ch
    if cur.strip(): out.append(cur)
    return [x.strip() for x in out]

DEF = re.compile(r'^define\s.*?@([\w.$]+)\(')
CALL = re.compile(r'\b(?:call|invoke)\b.*?\s(@[\w.$]+|%[\w.$]+)\(')
REF = re.compile(r'@(func_[0-9A-Fa-f]{8}\w*)\b')
cdef = {}                                   # func -> TU
info = {}                                   # func -> dict(direct=set, tabs=Counter(table), addr=set, unk=int)
for p in sorted(glob.glob('port/build/ll/*.c.ll') + glob.glob('port/build/ll/port__*.ll')):
    if p.endswith('.v.ll'): continue
    tu = os.path.basename(p).replace('.c.ll', '').replace('.ll', '')
    if not tu.startswith('port__') and tu + '.c' not in linked: continue
    cur, body = None, []
    for line in open(p, errors='replace'):
        if cur is None:
            m = DEF.match(line)
            if m: cur, body = m[1], []
            continue
        if not line.startswith('}'):
            body.append(line); continue
        defs, stores = {}, {}
        for l in body:
            m = re.match(r'\s*(%[\w.$]+) = (.*)', l)
            if m: defs[m[1]] = m[2]
            m = re.match(r'\s*store ptr (%[\w.$]+|@[\w.$]+), ptr (%[\w.$]+)', l)
            if m: stores.setdefault(m[2], []).append(m[1])
        def origin(v, depth=0):
            if depth > 12: return None
            if v.startswith('@'): return v[1:]
            e = defs.get(v, '')
            g = re.search(r'@([\w.$]+)', e)
            if g and not e.startswith('call'): return g[1]
            m = re.match(r'load ptr, ptr (%[\w.$]+)', e)
            if m:
                return origin(stores[m[1]][-1], depth + 1) if m[1] in stores else origin(m[1], depth + 1)
            m = re.match(r'(?:getelementptr\b.*?|bitcast )?.*?ptr (%[\w.$]+)', e)
            if m and m[1] != v: return origin(m[1], depth + 1)
            return None
        d = dict(direct=set(), tabs=collections.Counter(), addr=set(), unk=0, ccall=set())
        for l in body:
            m = CALL.search(l) if ('call' in l or 'invoke' in l) else None
            tgt = m[1] if m else None
            if tgt and tgt.startswith('@'):
                d['ccall' if tgt[1:] not in stubs else 'direct'].add(tgt[1:])
            elif tgt:
                o = origin(tgt)
                if o: d['tabs'][o] += 1
                else: d['unk'] += 1
            for r in REF.findall(l if not tgt or not tgt.startswith('@') else l.replace(tgt + '(', '(', 1)):
                if r in stubs: d['addr'].add(r)
        cdef[cur] = tu; info[cur] = d
        cur = None

# ------------------------------------------------------------------ ELF tables
def objdump(path, cmd):
    if os.path.exists(path) and os.path.getmtime(path) >= os.path.getmtime(ELF): return
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w') as fo:
        subprocess.run(['/Applications/Docker.app/Contents/Resources/bin/docker', 'exec',
                        os.environ.get('CONKERDEV', 'conkerdev'), 'mips-linux-gnu-objdump'] + cmd + ['/conker/' + ELF],
                       stdout=fo, check=True)
objdump(SYM, ['-t'])
objdump(DAT, ['-s', '-j', '.init_data', '-j', '.game_data', '-j', '.debugger_data'])
fstart, dsym = {}, {}
for line in open(SYM):
    m = re.match(r'^([0-9a-f]{8}) (.{7}) (\S+)\s+[0-9a-f]+ (\S+)$', line)
    if not m: continue
    a = int(m[1], 16)
    if 'F' in m[2] and m[3] in ('.init', '.game', '.debugger'): fstart[a] = m[4]
    elif a >= 0x80000000 or m[3].endswith('_data'): dsym[m[4]] = a
words = {}
for line in open(DAT):
    m = re.match(r'^ ([0-9a-f]{8}) ((?:[0-9a-f]{8} ?){1,4})', line)
    if m:
        a = int(m[1], 16)
        for j, w in enumerate(m[2].split()): words[a + 4 * j] = int(w, 16)
daddrs = sorted(set(dsym.values()))
def table_targets(t):
    if t not in dsym: return []
    a = dsym[t]; k = bisect.bisect_right(daddrs, a)
    end = min(daddrs[k] if k < len(daddrs) else a + 1024, a + 1024)
    return [fstart[words[x]] for x in range(a, end, 4) if words.get(x) in fstart]

# ------------------------------------------------------------------ census hits
logp = opt('--log')
if not logp:
    cands = sorted(glob.glob('port_work/p*/*.log'), key=os.path.getmtime, reverse=True)
    logp = next((c for c in cands if 'distinct asm stubs hit' in open(c, errors='replace').read()), None)
hits = {}
if logp:
    L = open(logp, errors='replace').read().splitlines()
    starts = [i for i, l in enumerate(L) if 'distinct asm stubs hit' in l]
    if starts:
        for l in L[starts[-1] + 1:]:
            m = re.match(r'\s+\d+\.\s+(\w+)\s+(\d+)\s', l)
            if not m: break
            hits[m[1]] = int(m[2])

# ------------------------------------------------------------------ per-function report
def own(f):
    d = info[f]
    tab = {}
    for t in d['tabs']:
        for s in table_targets(t):
            if s in stubs: tab.setdefault(s, t)
    return sorted(d['direct']), tab, sorted(d['addr'] - d['direct'] - set(tab))

def deep(f):
    seen, res, frontier = {f}, {}, [(c, c) for c in sorted(info[f]['ccall']) if c in info]
    for _ in range(DEPTH):
        nxt = []
        for c, first in frontier:
            if c in seen: continue
            seen.add(c)
            dr, tb, ad = own(c)
            for s in dr + list(tb) + ad: res.setdefault(s, first)
            nxt += [(x, first) for x in sorted(info[c]['ccall']) if x in info]
        frontier = nxt
    return res

def fmt(s):
    return f"{s}{'!' if s in guards else ''}:{hits.get(s, 0)}"

rows = []
for f in info:
    if '--all' not in args and f not in nm: continue
    dr, tb, ad = own(f)
    allst = dr + list(tb) + ad
    dp = {s: c for s, c in deep(f).items() if s not in allst}
    h = sum(hits.get(s, 0) for s in allst)
    rows.append((h, len(allst), f, cdef[f], 'NM' if f in nm else 'C',
                 ','.join(fmt(s) for s in dr), ','.join(f'{fmt(s)}@{t}' for s, t in sorted(tb.items())),
                 ','.join(fmt(s) for s in ad), info[f]['unk'],
                 ','.join(f'{fmt(s)}<{c}' for s, c in sorted(dp.items(), key=lambda x: -hits.get(x[0], 0)))))
rows.sort(key=lambda r: (-r[0], -r[1], r[2]))
os.makedirs(os.path.dirname(OUT), exist_ok=True)
with open(OUT, 'w') as fo:
    fo.write(f'# stubcalls.py: C function -> still-stub callees (census: {logp}, {len(hits)} stubs hit)\n')
    fo.write('func\tTU\tnm\thit\tn_stubs\tdirect\ttable\taddr\tunk\tdeep\n')
    for r in rows:
        if r[1] or r[9]:
            fo.write('\t'.join(str(x) for x in (r[2], r[3], r[4], r[0], r[1], r[5], r[6], r[7], r[8], r[9])) + '\n')
withst = [r for r in rows if r[1]]
print(f'{len(info)} C functions ({sum(1 for f in info if f in nm)} NON_MATCHING), {len(stubs)} stubs, '
      f'census {logp} ({len(hits)} stubs hit). {len(rows)} rows, {len(withst)} call stubs directly / via tables / '
      f'by address, {sum(1 for r in withst if r[0])} of them call a stub hit in the census -> {OUT}')
for f in FUNCS:
    if f not in info:
        print(f'{f}: not a C function of the port build ({"stub " + stubs[f] if f in stubs else "unknown"})'); continue
    dr, tb, ad = own(f)
    print(f'{f} ({cdef[f]}, {"NON_MATCHING" if f in nm else "C"}): indirect calls with unknown target {info[f]["unk"]}')
    print('  direct: ' + (' '.join(f'{fmt(s)} [{stubs[s]}]' for s in dr) or '-'))
    print('  table : ' + (' '.join(f'{fmt(s)}@{t}' for s, t in sorted(tb.items())) or '-'))
    print('  addr  : ' + (' '.join(fmt(s) for s in ad) or '-'))
    print('  deep  : ' + (' '.join(f'{fmt(s)}<{c}' for s, c in sorted(deep(f).items())) or '-'))
if not FUNCS:
    print('top (hit = census calls of the stubs it calls directly / through tables / by address):')
    for r in withst[:TOP]:
        if not r[0]: break
        st = ' '.join(x for x in (r[5], r[6], r[7]) if x)
        print(f'  {r[2]} {r[4]} {r[3]} hit {r[0]}: {st[:160]}')
