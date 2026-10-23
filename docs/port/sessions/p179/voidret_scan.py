#!/usr/bin/env python3
# P179: dropped-return audit (browser P174 bug class: batch m2c bodies declared `void` that lost a return value).
# For every C function (NM branch and matching C) declared `void` in the given source files, look at the default
# EU ELF (byte-identical to the ROM, so every caller's asm is ground truth):
#   callee side: on some path into `jr $31`, is v0 / f0 last written by a non-call instruction ("set") or by a
#                callee's return ("pass" = return g(...)), or never ("none")?
#   caller side: after each `jal F` (past its delay slot), is v0 / f0 read before it is overwritten or another call
#                happens? (bounded forward walk over both branch arms; a `jr $31` reached with v0 live = "ret").
#   tables:      the function's name used as a value in C / .data (dispatchers are covered by p162/tablesig.py).
# A suspect = a void function whose callers read v0/f0 (or that is table-referenced and whose asm sets v0/f0).
# Usage (worktree root): docker exec ... mips-linux-gnu-objdump -d --no-show-raw-insn -M reg-names=numeric
#        conker/build/conker.eu.elf > port_work/p179/dis.txt ; python3 docs/port/sessions/p179/voidret_scan.py [--files a b ..] [--all]
import re, glob, sys, os
from collections import defaultdict

DIS = 'port_work/p179/dis.txt'
PORTB = set("""game_eu_170760 game_169510 game_eu_4A070 game_eu_78230 game_eu_C2B60 game_eu_C5530 game_eu_CE0A0 game_14FF90
game_eu_48B10 game_eu_158110 game_eu_15A210 game_34F20 game_eu_1EC610 game_A28B0 game_eu_175B20 game_eu_15C660 game_eu_E0430
game_eu_156560 game_eu_156A30 game_eu_15C370 game_eu_13DC30 game_eu_1A5190 game_eu_1ACBC0 game_eu_1B1010 game_eu_1B1ED0
game_eu_13A8A0 game_eu_15B2E0 game_D5030 game_eu_F5580 game_eu_D4C90 game_eu_13B700 game_eu_1772D0 game_eu_1A6C30 game_1944C0
game_eu_193A00 game_eu_1A7B30 game_eu_138E00 game_eu_1B5C40 game_BC510 game_eu_186A80 game_eu_D3880 game_eu_D4550
game_eu_197680 game_eu_EF6D0 game_eu_EF410 game_eu_EF370 game_eu_1CE7D0 game_eu_E0170 game_eu_E17A0 game_eu_1D9C00
game_eu_11CB90 game_eu_12A7C0 game_eu_12E390 game_eu_AF2A0 game_eu_E7BC0 game_eu_1B7D70 game_eu_1DDE10 game_eu_1BE5C0
game_eu_1D3420 game_2062D0 game_eu_AE930 game_eu_17D3C0 game_eu_1EDA00 game_eu_1D5710 game_eu_1984F0 game_eu_1D4CC0 game_eu_201240
game_eu_125200 game_eu_12C0B0 game_eu_12BB30 game_eu_12D5D0 game_eu_1F4090
game_eu_F6060 game_eu_192500 game_eu_1BAF40 game_eu_1FB080 game_40490 game_eu_1F4F60 game_39750 game_1897A0 game_eu_126330""".split())

def branches(t):
    """yield (line, branch) with branch in NM / MATCH / X for each source line"""
    st = []
    for l in t.split('\n'):
        s = l.strip()
        if s.startswith('#if'):
            st.append('NM' if 'NON_MATCHING' in s and not s.startswith('#ifndef') else ('NOTNM' if 'NON_MATCHING' in s else 'X'))
            continue
        if s.startswith('#else') and st:
            st[-1] = {'NM': 'NOTNM', 'NOTNM': 'NM'}.get(st[-1], st[-1]); continue
        if s.startswith('#endif') and st:
            st.pop(); continue
        yield l, ('NM' if 'NM' in st else ('NOTNM' if 'NOTNM' in st else 'MATCH'))

# ---- disassembly
funcs, order = {}, []
cur = None
for l in open(DIS):
    m = re.match(r'^([0-9a-f]{8}) <([\w.]+)>:', l)
    if m:
        cur = m.group(2); funcs[cur] = []; order.append(cur); continue
    m = re.match(r'^\s*([0-9a-f]+):\s+(\S+)\s*(.*)$', l)
    if m and cur:
        ops = m.group(3).split('<')[0].strip()
        funcs[cur].append((int(m.group(1), 16), m.group(2), [o.strip() for o in ops.split(',')] if ops else [], m.group(3)))

BR = re.compile(r'^(b|beq|bne|beqz|bnez|blez|bgtz|bltz|bgez|bc1t|bc1f|beql|bnel|beqzl|bnezl|blezl|bgtzl|bltzl|bgezl|bc1tl|bc1fl)$')
STORE = re.compile(r'^(sw|sh|sb|swc1|sdc1|swl|swr|sd)$')
NODEST = re.compile(r'^(mult|multu|div|divu|jr|jalr|jal|j|c\.\w+\.[sd]|ctc1|mtc1|mthi|mtlo|teq|tne|break|nop|syscall|cache|sync)$')

def regs(o): return re.findall(r'\$(f?\d+)', o)

def dest_src(mn, ops):
    if BR.match(mn) or STORE.match(mn) or mn in ('jr',) or NODEST.match(mn):
        d = []
        if mn == 'mtc1' and len(ops) == 2: d = regs(ops[1])
        if mn in ('jal', 'jalr'): d = ['2', '3', 'f0', 'f2']
        s = [r for o in (ops if mn != 'mtc1' else ops[:1]) for r in regs(o)]
        return d, s
    if not ops: return [], []
    return regs(ops[0])[:1], [r for o in ops[1:] for r in regs(o)] + (regs(ops[0])[1:] if '(' in ops[0] else [])

def target(ops, raw):
    m = re.search(r'([0-9a-f]{6,8}) <', raw)
    return int(m.group(1), 16) if m else None

def cfg(name):
    ins = funcs[name]
    idx = {a: i for i, (a, *_) in enumerate(ins)}
    succ = defaultdict(list)
    n = len(ins)
    for i, (a, mn, ops, raw) in enumerate(ins):
        if i > 0 and (BR.match(ins[i-1][1]) or ins[i-1][1] in ('jr', 'j', 'jal', 'jalr')):
            continue  # delay slots handled with their branch
        if BR.match(mn):
            t = idx.get(target(ops, raw))
            likely = mn.endswith('l') and mn not in ('bal',)
            uncond = mn == 'b' or (mn == 'beq' and ops[:2] == ['$0', '$0'])
            if likely:
                succ[i] += [i + 1] + ([] if uncond else [i + 2])
                if t is not None: succ[i + 1].append(t)
            else:
                succ[i].append(i + 1)
                if t is not None: succ[i + 1].append(t)
                if not uncond: succ[i + 1].append(i + 2)
        elif mn in ('jr', 'j'):
            succ[i].append(i + 1)
            if mn == 'j':
                t = idx.get(target(ops, raw))
                if t is not None: succ[i + 1].append(t)
            elif ops and ops[0] != '$31':
                pass  # jump table: successors unknown (rare in returns path); ignored
        elif mn in ('jal', 'jalr'):
            succ[i].append(i + 1); succ[i + 1].append(('call', i + 2))
        else:
            succ[i].append(i + 1)
    return ins, succ

def callee_kind(name, reg):
    """how reg ('2' or 'f0') is last defined on paths reaching jr $31: set of 'set' / 'pass' / 'none'"""
    ins, succ = cfg(name)
    pred = defaultdict(list)
    for i, ss in succ.items():
        for s in ss:
            if isinstance(s, tuple): pred[s[1]].append(('call', i))
            else: pred[s].append(i)
    kinds, seen, setat = set(), set(), []
    work = []
    for i, (a, mn, ops, raw) in enumerate(ins):
        if mn == 'jr' and ops == ['$31'] and i + 1 < len(ins):
            work.append((i + 1, 0))
    while work:
        i, k = work.pop()
        if i in seen: continue
        seen.add(i)
        a, mn, ops, raw = ins[i]
        d, s = dest_src(mn, ops)
        if reg in d and mn not in ('jal', 'jalr'):
            # 'near' = within the epilogue (only lw ra / addiu sp / jr / nop / moves between it and jr ra)
            kinds.add('set'); setat.append((k, '%x:%s %s' % (a, mn, ','.join(ops)))); continue
        ps = pred.get(i, [])
        if i == 0 and not ps: kinds.add('none')
        epi = mn in ('jr', 'nop') or (mn == 'lw' and ops[:1] == ['$31']) or (mn == 'addiu' and ops[:1] == ['$29']) \
            or re.match(r'^l[wd]c1$', mn) and ops[:1] and ops[0] in ('$f20', '$f21', '$f22', '$f23', '$f24', '$f25') \
            or (mn == 'lw' and ops[:1] and ops[0] in ('$16', '$17', '$18', '$19', '$20', '$21', '$22', '$23', '$30'))
        for p in ps:
            if isinstance(p, tuple): kinds.add('pass')
            else: work.append((p, k + (0 if epi else 1)))
        if i == 0: kinds.add('none')
    return kinds, setat

def caller_reads(name, start, reg, limit=60):
    """after a call returning at index start, is reg read before written / next call? 'read' / 'ret' / None"""
    ins, succ = cfg(name)
    work, seen, res = [(start, 0)], set(), set()
    while work:
        i, k = work.pop()
        if i in seen or i >= len(ins) or k > limit: continue
        seen.add(i)
        a, mn, ops, raw = ins[i]
        d, s = dest_src(mn, ops)
        if reg in s: res.add('read@%x' % a); continue
        if mn == 'jr' and ops == ['$31']:
            # the delay slot runs first
            if i + 1 < len(ins):
                d2, s2 = dest_src(ins[i+1][1], ins[i+1][2])
                if reg in s2: res.add('read@%x' % ins[i+1][0]); continue
                if reg in d2: continue
            res.add('ret'); continue
        if reg in d: continue
        for sx in succ.get(i, []):
            if isinstance(sx, tuple): continue  # a call clobbers
            work.append((sx, k + 1))
    return res

# jal sites
calls = defaultdict(list)
for f in order:
    for i, (a, mn, ops, raw) in enumerate(funcs[f]):
        if mn == 'jal':
            m = re.search(r'<([\w.]+)>', raw)
            if m and '+' not in m.group(1): calls[m.group(1)].append((f, i + 2, a))

# ---- sources
files = sys.argv[sys.argv.index('--files') + 1:] if '--files' in sys.argv else None
srcs = sorted(glob.glob('conker/src_eu/**/*.c', recursive=True))
alltext = ''
alltext_nm = ''
voids = []  # (file, func, branch)
for p in srcs:
    base = os.path.basename(p)[:-2]
    t = re.sub(r'/\*.*?\*/', lambda m: '\n' * m.group(0).count('\n'), open(p, errors='replace').read(), flags=re.S)
    lines = list(branches(t))
    alltext += '\n'.join(re.sub(r'//.*', '', l) for l, b in lines if b != 'NOTNM') + '\n'
    alltext_nm += '\n'.join(re.sub(r'//.*', '', l) for l, b in lines if b != 'NOTNM') + '\n'
    alltext += '\n'.join(re.sub(r'//.*', '', l) for l, b in lines if b == 'NOTNM') + '\n'
    if files is not None:
        if base not in files: continue
    elif base not in PORTB: continue
    for l, b in lines:
        m = re.match(r'^(?:static\s+)?void\s+(func_[0-9A-F]{8})\s*\(([^;]*)$', l)
        if m and '{' in l or (m and not l.rstrip().endswith(';')):
            voids.append((base, m.group(1), b))
# return types of C definitions the NM build compiles (asm-only functions are missing = unknown)
rtype = {}
for m in re.finditer(r'^(?:static\s+)?([A-Za-z_][\w\s\*]*?)\s*\**\b(func_[0-9A-F]{8})\s*\([^;{]*\)\s*\{', alltext_nm, re.M):
    rtype.setdefault(m.group(2), 'void' if re.sub(r'\s+', ' ', m.group(1)).strip() in ('void', 'static void') else 'value')
datarefs = defaultdict(int)
for p in glob.glob('conker/asm/data/**/*.s', recursive=True):
    for m in re.finditer(r'\.word\s+(func_[0-9A-F]{8})\b', open(p, errors='replace').read()):
        datarefs[m.group(1)] += 1
crefs = defaultdict(int)
for m in re.finditer(r'(?<![\w])&?(func_[0-9A-F]{8})\b(?!\s*\()', alltext):
    crefs[m.group(1)] += 1

memo = {}
def used(f, depth=0):
    # does any caller (transitively through `return f(...)` callers) read f's v0 / f0
    if f in memo: return memo[f]
    if depth > 6: return False
    memo[f] = False
    r = False
    for caller, st, a in calls.get(f, []):
        x = caller_reads(caller, st, '2') | caller_reads(caller, st, 'f0')
        if any(y.startswith('read') for y in x) or ('ret' in caller_reads(caller, st, '2') and used(caller, depth + 1)): r = True; break
    memo[f] = r
    return r

seenf = set()
out = []
nv = 0
for base, fn, b in voids:
    if (fn, b) in seenf or b == 'NOTNM': continue  # NOTNM = default-build-only twin (the NM side is compiled in the port)
    seenf.add((fn, b))
    nv += 1
    if fn not in funcs:
        out.append(('NOELF', base, fn, b, '', '', '')); continue
    k2, at2 = callee_kind(fn, '2')
    kf, atf = callee_kind(fn, 'f0')
    rd = []
    for caller, st, a in calls.get(fn, []):
        r2 = caller_reads(caller, st, '2'); rf = caller_reads(caller, st, 'f0')
        if any(x.startswith('read') for x in r2 | rf):
            rd.append('%s@%x:%s' % (caller, a, '/'.join(sorted(r2 | rf))))
        elif 'ret' in r2:  # (f0 'ret' ignored: an int-returning caller leaves f0 stale)
            rd.append('%s@%x:ret' % (caller, a))
    tab = datarefs.get(fn, 0) + crefs.get(fn, 0)
    hard = [r for r in rd if 'read' in r]
    near = [x[1] for x in at2 + atf if x[0] <= 1]
    if hard: cls = 'SUSPECT'
    elif [r for r in rd if r.endswith(':ret') and rtype.get(r.split('@')[0]) == 'value' and used(r.split('@')[0])]: cls = 'SUSPECT2'
    elif near: cls = 'NEAR'
    elif [r for r in rd if r.endswith(':ret') and rtype.get(r.split('@')[0]) is None and used(r.split('@')[0])]: cls = 'ASMPASS'
    elif tab and near: cls = 'TABLE'
    elif rd: cls = 'RETPASS'
    else: cls = 'ok'
    out.append((cls, base, fn, b, 'v0=' + '+'.join(sorted(k2)) + ' f0=' + '+'.join(sorted(kf)) + (' near=' + ';'.join(near[:3]) if near else ''),
                'calls=%d tabrefs=%d' % (len(calls.get(fn, [])), tab), ' '.join(rd[:6]), ))
from collections import Counter
print('void C functions scanned:', nv, Counter(o[0] for o in out))
for o in sorted(out):
    if o[0] != 'ok' or '--all' in sys.argv:
        print('\t'.join(o))
