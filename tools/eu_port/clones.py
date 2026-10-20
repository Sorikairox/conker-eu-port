#!/usr/bin/env python3
"""Template families: find functions with the same instruction skeleton and clone solved C onto GLOBAL_ASM siblings.
usage:
  clones.py [--refresh] [--min N] [--top K]    cluster report (stats + best clusters)
  clones.py --draft [OUTDIR] [--min N] [--per K] [--only f1,f2]
        write drafts for GLOBAL_ASM functions whose skeleton equals an already-matched C function:
        OUTDIR/v0/<func>.c, v1/... (default conker/build/cl), screen with  m2c/screenall build/cl
  (both draft modes run declfix.py on every draft; --nofix switches that off)
  clones.py --asm-clusters [--min N] list asm-only clusters (no C sibling), smallest member first
Skeleton = opcodes + registers per instruction; immediates, branch targets and reloc symbols are abstracted
(sp-relative offsets and `addiu sp/aN,sp,K` are kept so the frame must agree).  Source of instructions:
objdump of conker/build/src_eu/*.o (one docker exec, cached in conker/build/clones.dump; --refresh redoes it)."""
import re, sys, os, glob, subprocess, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import declfix
import sys as _gsys
def _conker_guard():
    # refuse to run on a checkout other than CONKER_ROOT (e.g. a worktree shell without the wt.sh env)
    import os as _o, subprocess as _s
    if _o.path.exists("/.dockerenv"):
        return  # inside a build container: paths are /conker, not the host checkout
    try:
        top = _s.run(["git", "rev-parse", "--show-toplevel"], capture_output=True, text=True).stdout.strip()
    except Exception:
        return
    root = _o.path.realpath(_o.path.expanduser(_o.environ.get("CONKER_ROOT", "~/conker")))
    if top and _o.path.realpath(top) != root:
        _gsys.stderr.write("refusing: cwd repo %s != CONKER_ROOT %s (eval the wt.sh env)\n" % (top, root))
        _gsys.exit(3)
_conker_guard()
R = os.path.expanduser(os.environ.get('CONKER_ROOT','~/conker')+'/conker')
DUMP = R + '/build/clones.dump'
args = sys.argv[1:]
def opt(n, d=None):
    if n in args:
        i = args.index(n)
        if i + 1 < len(args) and not args[i + 1].startswith('--'): return args[i + 1]
        return True
    return d
LAX = bool(opt('--lax')); MIN = int(opt('--min', 6)); TOP = int(opt('--top', 15)); PER = int(opt('--per', 2))

if opt('--refresh') or not os.path.exists(DUMP):
    env = dict(os.environ, PATH='/Applications/Docker.app/Contents/Resources/bin:' + os.environ['PATH'])
    out = subprocess.run(['docker', 'exec', os.environ.get('CONKERDEV','conkerdev'), 'sh', '-c',
        'cd /conker/conker; for f in build/src_eu/*.o; do echo "#FILE $f"; mips-linux-gnu-objdump -dr --no-show-raw-insn $f; done'],
        capture_output=True, text=True, env=env).stdout
    open(DUMP, 'w').write(out)

# ---- live (GLOBAL_ASM) set and C sources
live = {}; srcs = {}
for f in glob.glob(R + '/src_eu/*.c'):
    t = open(f).read(); srcs[os.path.basename(f)[:-2]] = t
    for m in re.findall(r'GLOBAL_ASM\("[^"]*/(\w+)\.s"\)', t): live[m] = os.path.basename(f)[:-2]

# ---- parse dump
HDR = re.compile(r'^[0-9a-f]+ <(\w+)>:')
INS = re.compile(r'^\s+([0-9a-f]+):\t(\S+)(?:\t(.*))?$')
REL = re.compile(r'^\s+([0-9a-f]+): (R_MIPS_\w+)\t(.*)$')
funcs = {}   # name -> dict(file, ins=[(op, opnds, reloc)])
cur = None; fil = None
for line in open(DUMP):
    if line.startswith('#FILE'): fil = os.path.basename(line.split()[1])[:-4]; continue  # xxx.c
    m = HDR.match(line)
    if m: cur = m.group(1); funcs[cur] = dict(file=fil, ins=[]); continue
    if cur is None: continue
    m = REL.match(line)
    if m: i = funcs[cur]['ins'][-1]; funcs[cur]['ins'][-1] = (i[0], i[1], (m.group(2), m.group(3)));  continue
    m = INS.match(line)
    if m: funcs[cur]['ins'].append((m.group(2), (m.group(3) or '').split('#')[0].strip(), None))

def trim(ins):
    last = max((i for i, x in enumerate(ins) if x[0] == 'jr' and x[1] == 'ra'), default=None)
    if last is None: return ins
    ins = ins[:last + 2]
    if len(ins) >= 4 and ins[-4][0] == 'jr' and ins[-4][1] == 'ra' and ins[-3][0] == 'nop' and ins[-2][0] == 'jr': ins = ins[:-2]
    return ins
for f in funcs.values(): f['ins'] = trim(f['ins'])

REG = r'(?:zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f\d+|fcc\d)'
def split_ops(o):
    return [x for x in re.split(r',(?![^(]*\))', o)] if o else []
def norm(op, o, rel):
    """-> (skeleton string, list of immediates [value or None])"""
    ps = split_ops(o); sk = []; im = []
    for p in ps:
        p = p.strip()
        m = re.match(r'^(-?(?:0x)?[0-9a-fA-F]+)\((\w+)\)$', p)
        if m:
            v = int(m.group(1), 0) if not re.match(r'^-?[0-9a-fA-F]*[a-fA-F]', m.group(1)) or 'x' in m.group(1) else int(m.group(1), 16)
            if m.group(2) == 'sp': sk.append('%d(sp)' % v)
            else: sk.append('#(%s)' % m.group(2)); im.append(v)
        elif re.match(r'^' + REG + '$', p): sk.append(p)
        elif re.match(r'^[0-9a-f]+ <', p): sk.append('T')
        elif re.match(r'^-?(0x)?[0-9a-fA-F]+$', p):
            v = int(p, 0) if ('x' in p or re.match(r'^-?\d+$', p)) else int(p, 16)
            if op == 'addiu' and len(ps) == 3 and ps[1].strip() == 'sp': sk.append(str(v))
            elif op == 'addiu' and len(ps) == 3 and ps[0].strip() == 'sp': sk.append(str(v))
            else: sk.append('#'); im.append(v)
        else: sk.append(p)
    r = rel[0] if rel else ''
    return op + ' ' + ','.join(sk) + (' ' + r if r else ''), im
for n, f in funcs.items():
    f['sk'] = []; f['im'] = []
    for op, o, rel in f['ins']:
        s, im = norm(op, o, rel); f['sk'].append(s); f['im'].append(im)
    f['key'] = hash(tuple(f['sk']))
    f['live'] = n in live

# ---- clusters
by = collections.defaultdict(list)
for n, f in funcs.items():
    if len(f['sk']) >= MIN: by[f['key']].append(n)

def report():
    a_all = [n for n, f in funcs.items() if f['live']]
    print('functions in objects: %d, GLOBAL_ASM: %d, C: %d (min skeleton length %d)' % (len(funcs), len(a_all), len(funcs) - len(a_all), MIN))
    cl_asm = [(k, [n for n in v if funcs[n]['live']], [n for n in v if not funcs[n]['live']]) for k, v in by.items()]
    asm_only = [(k, a, c) for k, a, c in cl_asm if len(a) >= 2 and not c]
    mixed = [(k, a, c) for k, a, c in cl_asm if a and c]
    n_in_asm_only = sum(len(a) for _, a, _ in asm_only)
    n_mixed = sum(len(a) for _, a, _ in mixed)
    b_mixed = sum(len(funcs[n]['sk']) * 4 for _, a, _ in mixed for n in a)
    print('(a) asm-only clusters (>=2 members, no C sibling): %d clusters, %d functions' % (len(asm_only), n_in_asm_only))
    sz = collections.Counter(len(a) for _, a, _ in asm_only)
    print('    cluster size histogram:', ' '.join('%d:%d' % (k, sz[k]) for k in sorted(sz)))
    print('(b) GLOBAL_ASM functions with a matched C sibling skeleton: %d functions in %d clusters, %d bytes' % (n_mixed, len(mixed), b_mixed))
    print('best asm-only clusters (size x insns), smallest member shown:')
    for k, a, c in sorted(asm_only, key=lambda x: -len(x[1]) * len(funcs[x[1][0]]['sk']))[:TOP]:
        s = min(a, key=lambda n: len(funcs[n]['sk']))
        print('  %3d members, %3d insns, total %5d bytes: smallest %s (%s)' % (len(a), len(funcs[s]['sk']), len(a) * len(funcs[s]['sk']) * 4, s, ' '.join(sorted(a)[:3])))
    print('best clusters with C sibling:')
    for k, a, c in sorted(mixed, key=lambda x: -len(x[1]) * len(funcs[x[1][0]]['sk']))[:TOP]:
        print('  %3d asm, %2d C, %3d insns: C %s -> %s' % (len(a), len(c), len(funcs[a[0]]['sk']), c[0], ' '.join(sorted(a)[:4])))

# ---- draft generation
def cfunc_text(name):
    t = srcs.get(funcs[name]['file'])
    if t is None: return None
    m = re.search(r'^(?!\s)[^\n;{}]*\b%s\s*\([^;{]*\)\s*\n?\{' % re.escape(name), t, re.M)
    if not m: return None
    i = t.index('{', m.end() - 1); d = 0; j = i
    while j < len(t):
        if t[j] == '{': d += 1
        elif t[j] == '}':
            d -= 1
            if d == 0: break
        j += 1
    return t[m.start():j + 1]

def diffs(c, a, pairs=None):
    """aligned diffs between C-function c and asm function a: imm [(pos, k, old, new, posA)], sym [(old, new, type)].
    pairs = aligned (i, j) instruction indices (default: identity)"""
    fc, fa = funcs[c], funcs[a]; imm = []; sym = []; same = collections.defaultdict(list)
    if pairs is None: pairs = [(i, i) for i in range(len(fc['sk']))]
    for i, j in pairs:
        if fc['ins'][i][0] != fa['ins'][j][0] or len(fc['im'][i]) != len(fa['im'][j]): continue
        for k, (x, y) in enumerate(zip(fc['im'][i], fa['im'][j])):
            if x != y: imm.append((i, k, x, y, j))
            else: same[x].append(i)
        rc, ra = fc['ins'][i][2], fa['ins'][j][2]
        if rc and ra and rc[1] != ra[1]: sym.append((rc[1], ra[1], rc[0]))
    return imm, sym, same

def lits(text, v):
    """token spans of integer literal v in C text (decimal or hex, optional U/L suffix), comments ignored"""
    pats = [r'(?<![\w.])%d(?![\w.])' % v] if v >= 0 else []
    if v >= 0: pats.append(r'(?<![\w.])0[xX]0*%X(?![0-9a-zA-Z_.])' % v)
    if v >= 0: pats.append(r'(?<![\w.])unk%X(?![0-9a-zA-Z_])' % v)
    if v < 0: pats.append(r'(?<![\w.])-\s*%d(?![\w.])' % -v)
    out = []
    for p in pats:
        for m in re.finditer(p, text):
            # include trailing U/L suffix inside token
            e = m.end()
            while e < len(text) and text[e] in 'uUlL' and not text[m.start():].startswith('unk'): e += 1
            out.append((m.start(), e))
    return sorted(out)

def fmt(v, like):
    if like.startswith('unk'): return 'unk%X' % v
    s = like.lstrip('-').rstrip('uUlL')
    suf = like[len(like.rstrip('uUlL')):]
    if v < 0: return '-%d' % -v
    return ('0x%X' % v if s[:2] in ('0x', '0X') else '%d' % v) + suf

HDR_TXT = ''.join(open(p).read() for p in glob.glob(R + '/include/*.h') + glob.glob(R + '/src_eu/*.h') + list(srcs and []))
ALL_SRC = '\n'.join(srcs.values())
def find_decl(sym):
    m = re.search(r'^extern\s+([^;()]*?\b%s\b[^;()]*);' % re.escape(sym), HDR_TXT + '\n' + ALL_SRC, re.M)
    return m.group(1) if m else None
def find_proto(name):
    m = re.search(r'^(\w[\w \*]*?)\s*\b%s\s*\(([^)]*)\);' % re.escape(name), HDR_TXT, re.M)
    return m

def make_draft(c, a, lax=False, pairs=None):
    body = cfunc_text(c)
    if body is None: return None, 'nosrc'
    imm, sym, same = diffs(c, a, pairs)
    if lax:   # alias data symbols (same address, other name) link identically: keep the sibling's names
        sym = [x for x in sym if x[2] == 'R_MIPS_26']
        imm = [x for x in imm if not (funcs[c]['ins'][x[0]][2] and funcs[a]['ins'][x[4]][2] and funcs[c]['ins'][x[0]][2][1] != funcs[a]['ins'][x[4]][2][1])
               and not (not funcs[a]['ins'][x[4]][2] and funcs[c]['ins'][x[0]][2]) and not (x[3] == 0)]
    prs = pairs if pairs is not None else [(i, i) for i in range(len(funcs[c]['ins']))]
    if not lax and any(funcs[c]['ins'][i][2] and funcs[c]['ins'][i][2][1].startswith('.rodata') or
           funcs[a]['ins'][j][2] and funcs[a]['ins'][j][2][1].startswith('.rodata') for i, j in prs
           if (funcs[c]['ins'][i][2] or funcs[a]['ins'][j][2]) and
              (funcs[c]['ins'][i][2] or ('', ''))[1] != (funcs[a]['ins'][j][2] or ('', ''))[1]):
        return None, 'rodata'
    body = re.sub(r'\b%s\b' % re.escape(c), a, body)
    smap = {}
    stype = {}
    for o, n, ty in sym:
        stype[o] = ty
        if smap.get(o, n) != n: return None, 'ambig-sym'
        smap[o] = n
    for o, n in smap.items():
        if '+' in o or '+' in n or '.' in o or '.' in n: return None, 'sym-addend'
        body = re.sub(r'(?<![\w])%s(?!\w)' % re.escape(o), '@@' + n + '@@', body)
    # immediates grouped by old value, in instruction order
    byold = collections.defaultdict(list)
    for (i, k, x, y, _j) in imm: byold[x].append(y)
    missing = []
    edits = []
    for x, news in byold.items():
        spans = lits(body, x)
        uns = len(same.get(x, []))    # unchanged occurrences of the same value
        if not spans: missing.append(x); continue
        tot = len(news) + uns
        if (len(spans) == len(news) or uns == 0) and len(set(news)) == 1: tgt = [(s, news[0]) for s in spans]
        elif len(spans) == tot and uns == 0: tgt = list(zip(spans, news))
        elif len(spans) == 1 and len(set(news)) == 1: tgt = [(spans[0], news[0])]
        else: return None, 'ambig-imm(%d: %d lits, %d chg, %d same)' % (x, len(spans), len(news), uns)
        edits += tgt
    for (s, e), nv in sorted(edits, reverse=True):
        body = body[:s] + fmt(nv, body[s:e]) + body[e:]
    body = body.replace('@@', '')
    pre = ''
    for o, n in smap.items():
        if stype[o] != 'R_MIPS_26' and (o in body or n in body):
            d = find_decl(n)
            if d is None:
                d0 = find_decl(o)
                d = re.sub(r'\b%s\b' % re.escape(o), n, d0) if d0 else None
            if d is None: return None, 'nodecl'
            if not re.search(r'^extern\s[^;]*\b%s\b' % n, HDR_TXT, re.M): pre += 'extern %s;\n' % d
    m = find_proto(a)
    if m:   # adopt the prototype's return type if the draft's differs
        mm = re.match(r'^([^\n(]*?)\b%s\s*\(' % re.escape(a), body)
        if mm and mm.group(1).split() != m.group(1).split():
            body = m.group(1).strip() + ' ' + body[len(mm.group(1)):].lstrip()
    tgt = srcs.get(funcs[a]['file'], '')
    for ln in re.findall(r'^(?:extern|static|const)[^;{}()]*;', srcs.get(funcs[c]['file'], ''), re.M):
        ids = re.findall(r'\w+', ln)[-3:]
        nm = re.findall(r'(\w+)(?:\[[^\]]*\])?\s*;$', ln)
        if nm and re.search(r'\b%s\b' % nm[0], body) and not re.search(r'\b%s\b' % nm[0], HDR_TXT + tgt) and ln not in pre:
            pre += ln.replace('static ', '') + '\n'
    for ln in re.findall(r'^[A-Za-z_][^\n;{}=]*\([^\n;{}]*\);[ \t]*(?://[^\n]*)?$', srcs.get(funcs[c]['file'], ''), re.M):
        nm = re.search(r'(\w+)\s*\(', ln).group(1)
        if nm != a and nm != c and re.search(r'\b%s\s*\(' % nm, body) and not re.search(r'\b%s\s*\(' % nm, HDR_TXT + tgt) and ln not in pre:
            pre += ln + '\n'
    body = pre + body
    return body, ('missing:' + ','.join(hex(m) for m in missing)) if missing else 'ok'


# ---- fuzzy mode: closest matched C function by skeleton edit distance
def align(sa, sb, K):
    """banded edit distance between skeleton lists (insert/delete/substitute = 1). -> (dist, pairs[(i in sa, j in sb)], ops) or None if > K"""
    n, m = len(sa), len(sb)
    if abs(n - m) > K: return None
    INF = 99
    D = [[INF] * (m + 1) for _ in range(n + 1)]
    for j in range(min(m, K) + 1): D[0][j] = j
    for i in range(1, n + 1):
        lo, hi = max(0, i - K), min(m, i + K)
        if lo == 0: D[i][0] = i
        for j in range(max(1, lo), hi + 1):
            v = D[i - 1][j - 1] + (0 if sa[i - 1] == sb[j - 1] else 1)
            if D[i - 1][j] + 1 < v: v = D[i - 1][j] + 1
            if D[i][j - 1] + 1 < v: v = D[i][j - 1] + 1
            D[i][j] = v
        if min(D[i][lo:hi + 1]) > K: return None
    d = D[n][m]
    if d > K: return None
    i, j = n, m; pairs = []; ops = []
    while i > 0 or j > 0:
        if i > 0 and j > 0 and D[i][j] == D[i - 1][j - 1] + (0 if sa[i - 1] == sb[j - 1] else 1):
            pairs.append((i - 1, j - 1))
            if sa[i - 1] != sb[j - 1]: ops.append(('chg', i - 1, j - 1))
            i -= 1; j -= 1
        elif i > 0 and D[i][j] == D[i - 1][j] + 1: ops.append(('del', i - 1, None)); i -= 1
        else: ops.append(('ins', None, j - 1)); j -= 1
    return d, pairs[::-1], ops[::-1]

def near_pairs(K, maxlen, only=None):
    """-> {asm func: (dist, sibling C func, pairs, ops)} for the closest C sibling (dist 1..K; exact skeleton matches are the exact mode's job)"""
    cs = [n for n, f in funcs.items() if not f['live'] and len(f['sk']) >= MIN]
    cnt = {n: collections.Counter(funcs[n]['sk']) for n in cs}
    bylen = collections.defaultdict(list)
    for n in cs: bylen[len(funcs[n]['sk'])].append(n)
    res = {}
    for a, fa in funcs.items():
        if not fa['live'] or len(fa['sk']) < MIN or len(fa['sk']) > maxlen: continue
        if only and a not in only: continue
        if any(not funcs[x]['live'] for x in by.get(fa['key'], ())): continue   # exact sibling exists
        ca = collections.Counter(fa['sk']); best = None
        for L in range(len(fa['sk']) - K, len(fa['sk']) + K + 1):
            for c in bylen.get(L, ()):
                lb = sum((ca - cnt[c]).values())
                if lb > K or (best and lb > best[0]): continue
                r = align(funcs[c]['sk'], fa['sk'], K if not best else best[0])
                if r and (best is None or r[0] < best[0] or (r[0] == best[0] and c < best[1])): best = (r[0], c, r[1], r[2])
        if best and best[0] >= 1: res[a] = best
    return res

if opt('--near'):
    K = int(opt('--near')); maxlen = int(opt('--maxlen', 200))
    only = set(opt('--only', '').split(',')) - {''} if isinstance(opt('--only'), str) else None
    res = near_pairs(K, maxlen, only)
    hist = collections.Counter(v[0] for v in res.values())
    print('--near %d (live skeleton %d..%d insns): %d GLOBAL_ASM functions with a C sibling within %d edits' % (K, MIN, maxlen, len(res), K))
    cum = 0
    for d in sorted(hist):
        cum += hist[d]
        print('  dist %d: %3d functions (%d cumulative, %d bytes cumulative)' % (d, hist[d], cum,
            sum(len(funcs[a]['sk']) * 4 for a, v in res.items() if v[0] <= d)))
    if opt('--draft'):
        out = opt('--draft'); out = out if isinstance(out, str) else R + '/build/nr'
        import shutil; shutil.rmtree(out, ignore_errors=True)
        rows = []; stat = collections.Counter()
        os.makedirs(out + '/v0', exist_ok=True)
        for a, (d, c, pairs, ops) in sorted(res.items(), key=lambda kv: (kv[1][0], len(funcs[kv[0]]['sk']))):
            body, why = make_draft(c, a, False, pairs)
            if body is None and LAX: body, why = make_draft(c, a, True, pairs); why = 'lax ' + why
            stat[why.split('(')[0].split(':')[0]] += 1
            if body is None: continue
            notes = []
            for op, i, j in ops:
                if op == 'ins': notes.append('asm +%s' % funcs[a]['sk'][j])
                elif op == 'del': notes.append('sib -%s' % funcs[c]['sk'][i])
                else: notes.append('%s -> %s' % (funcs[c]['sk'][i], funcs[a]['sk'][j]))
            body = '/* NEAR %d from %s: %s */\n' % (d, c, '; '.join(notes)) + body
            if not opt('--nofix'): body, fn = declfix.fix(body, a, funcs[c]['file'], live[a]); why += ' fix=' + ','.join(fn)
            open('%s/v0/%s.c' % (out, a), 'w').write(body + '\n')
            rows.append('%s <- %s dist %d %s' % (a, c, d, why))
        open(out + '/clones.txt', 'w').write('\n'.join(rows) + '\n')
        print('near drafts: %d files in %s/v0; reasons: %s' % (len(rows), out, dict(stat)))
    sys.exit(0)

if opt('--draft'):
    out = opt('--draft'); out = out if isinstance(out, str) else R + '/build/cl'
    only = set(opt('--only', '').split(',')) - {''} if isinstance(opt('--only'), str) else None
    import shutil; shutil.rmtree(out, ignore_errors=True)
    n = 0; stat = collections.Counter(); made = collections.defaultdict(int); rows = []
    for k, v in by.items():
        asm = [x for x in v if funcs[x]['live']]; cs = [x for x in v if not funcs[x]['live']]
        if not asm or not cs: continue
        for a in sorted(asm):
            if only and a not in only: continue
            cand = sorted(cs, key=lambda c: (len(diffs(c, a)[0]) + len(diffs(c, a)[1]), c))
            for c in cand:
                if made[a] >= PER: break
                body, why = make_draft(c, a)
                if body is None and LAX: body, why = make_draft(c, a, True); why = 'lax ' + why
                stat[why.split('(')[0].split(':')[0]] += 1
                if body is None: continue
                if not opt('--nofix'): body, fn = declfix.fix(body, a, funcs[c]['file'], live[a]); why += ' fix=' + ','.join(fn)
                d = '%s/v%d' % (out, made[a]); os.makedirs(d, exist_ok=True)
                open('%s/%s.c' % (d, a), 'w').write(body + '\n'); made[a] += 1
                rows.append('%s <- %s %s' % (a, c, why))
    open(out + '/clones.txt', 'w').write('\n'.join(rows) + '\n')
    print('drafts for %d asm functions (%d files) in %s; reasons: %s' % (len(made), sum(made.values()), out, dict(stat)))
elif opt('--asm-clusters'):
    for k, v in sorted(by.items(), key=lambda kv: -len([x for x in kv[1] if funcs[x]['live']]) * len(funcs[kv[1][0]]['sk'])):
        a = [x for x in v if funcs[x]['live']]
        if len(a) >= 2 and len(a) == len(v):
            s = min(a, key=lambda n: len(funcs[n]['sk']))
            print('%3d x %3d insns  smallest %s  others %s' % (len(a), len(funcs[s]['sk']), s, ' '.join(sorted(set(a) - {s})[:8])))
else:
    report()
