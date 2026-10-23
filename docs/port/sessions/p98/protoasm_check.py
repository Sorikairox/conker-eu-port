#!/usr/bin/env python3
"""P98: C prototypes in scope at calls to still-asm functions vs. what the callee's EU asm really reads / returns.

Why: an asm-only callee keeps the N64 calling convention of its original C. When the port's C passes a float
where the asm reads an int register (or the reverse), passes fewer arguments than the asm reads, or expects a
float return where the asm leaves v0 (or the reverse), the port gets garbage the moment the callee becomes C
(and the stub/difftest arity is taken from the prototype today).  P95's floatint_scan only checked literals.

C side  : every conker/src_eu C file with the NON_MATCHING branches selected (what the port compiles; each row
          is tagged [NM] = call only in the NM build, [M] = call compiled in both).  For each call to an asm-only
          function (tools/port/progress_nm.py --list) the prototype in scope = the TU's declarations (any scope;
          `f()` = unprototyped), else conker/include/**/*.h; none -> unprototyped (only the arity is checked).
asm side: the EU ELF disassembly (port_work/p93/eu.dis).  Forward may-dataflow (CFG from arity_scan.py, P79)
          with value tags: Ek = entry value of argument word k (a0..a3, stack word k loaded from frame+4k),
          EF0 / EF1 = entry f12 / f14, W = written here, R:f = return value of callee f.  Moves and sp spills /
          reloads carry the tags.  Each use of an entry tag classifies the word:
            F  mtc1 to an FPR, lwc1 of the spill / stack slot           (float bits)
            I  ALU operand, load/store base, branch compare, jalr/jr    (integer / pointer)
            A  stored to memory (not sp) / returned in v0               (bits only: ambiguous)
            P  still in a0..a3 at a jal -> resolved by the callee's own class of that word (fixpoint)
          f12 / f14 read with their entry tag = float parameter 0 / 1 (FP register class, definitive).
          Return: tags of v0 and f0 reaching `jr ra` (W / entry / R:callee resolved recursively).
Prototype layout: o32 (param 0 FP -> f12, param 1 FP after FP param 0 -> f14, doubles 8-aligned, 2 words).
Verdicts (one row per file x callee x issue, `n` = call sites):
  FREG    a param in f12/f14 per the prototype, the asm reads the a-register of that word instead (or the
          prototype has an int where the asm reads f12/f14): register class differs -> wrong value on N64 too.
  FLOAT   prototype says float for a word the asm uses as an integer (I).
  INT     prototype says int / pointer for a word the asm uses as float bits (F).
  ARITY   the asm reads argument words the C call does not pass (prototype or, unprototyped, the call).
  RETF    prototype returns float, the asm never sets f0 (only v0).   RETI  prototype returns int / pointer,
          the asm sets f0 and never v0.   RETNONE  non-void prototype, neither v0 nor f0 set (info).
usage: protoasm_check.py [--dis port_work/p93/eu.dis] [--func NAME] [--why NAME]   (TSV on stdout, counts on stderr)
"""
import os, re, sys, glob, struct, collections, subprocess

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.abspath(os.path.join(HERE, '..', '..', '..', '..'))
SRC = os.path.join(REPO, 'conker', 'src_eu')
INC = os.path.join(REPO, 'conker', 'include')
args = sys.argv[1:]
def opt(n, d=None):
    return args[args.index(n) + 1] if n in args else d
SRC = opt('--src', SRC); INC = opt('--inc', INC)
DIS = opt('--dis', os.path.join(REPO, 'port_work', 'p93', 'eu.dis'))
ONLY = opt('--func'); WHY = opt('--why')
FLOAT_T = {'f32', 'float', 'f64', 'double'}
DBL_T = {'f64', 'double', 's64', 'u64'}

sys.path.insert(0, os.path.join(REPO, 'docs', 'port', 'sessions', 'p95'))
# helpers shared with P95's scanner (copied: floatint_scan runs its scan at import)
def nm_select(text):
    out, stack, active = [], [], True
    for line in text.split('\n'):
        m = re.match(r'#\s*(ifdef|ifndef|if|elif|else|endif)\b(.*)', line.strip())
        if m:
            d, rest = m.group(1), m.group(2).strip()
            if d in ('ifdef', 'ifndef', 'if'):
                nm = None
                if d == 'ifdef' and rest == 'NON_MATCHING': nm = True
                elif d == 'ifndef' and rest == 'NON_MATCHING': nm = False
                elif d == 'if' and re.fullmatch(r'defined\s*\(?\s*NON_MATCHING\s*\)?', rest): nm = True
                elif d == 'if' and re.fullmatch(r'!\s*defined\s*\(?\s*NON_MATCHING\s*\)?', rest): nm = False
                elif d == 'if' and rest == '0': nm = False
                stack.append(('nm' if nm is not None else 'o', nm, active))
                if nm is not None: active = active and nm
            elif d == 'else' and stack and stack[-1][0] == 'nm':
                k, nm, par = stack[-1]; stack[-1] = (k, not nm, par); active = par and not nm
            elif d == 'endif' and stack:
                active = stack.pop()[2]
            out.append(''); continue
        out.append(line if active else '')
    return '\n'.join(out)

def nm_lines(text):
    res, stack = set(), []
    for n, line in enumerate(text.split('\n'), 1):
        m = re.match(r'#\s*(ifdef|ifndef|if|else|endif)\b(.*)', line.strip())
        if m:
            d, rest = m.group(1), m.group(2).strip()
            if d in ('ifdef', 'ifndef', 'if'):
                k = None
                if rest == 'NON_MATCHING' or re.fullmatch(r'defined\s*\(?\s*NON_MATCHING\s*\)?', rest): k = (d != 'ifndef')
                stack.append(k)
            elif d == 'else' and stack and stack[-1] is not None: stack[-1] = not stack[-1]
            elif d == 'endif' and stack: stack.pop()
            continue
        if any(x is True for x in stack): res.add(n)
    return res

def strip_comments(t):
    t = re.sub(r'/\*.*?\*/', lambda m: re.sub(r'[^\n]', ' ', m.group(0)), t, flags=re.S)
    return re.sub(r'//[^\n]*', '', t)

def split_args(s):
    parts, depth, cur = [], 0, ''
    for ch in s:
        if ch in '([{': depth += 1
        elif ch in ')]}': depth -= 1
        if ch == ',' and depth == 0: parts.append(cur.strip()); cur = ''
        else: cur += ch
    if cur.strip(): parts.append(cur.strip())
    return parts

def match_paren(t, i):
    depth = 0
    for j in range(i, len(t)):
        if t[j] == '(': depth += 1
        elif t[j] == ')':
            depth -= 1
            if depth == 0: return j
    return -1

def ptype(p):
    """parameter text -> 'F' float, 'D' double, 'L' 64-bit int, 'I' int / pointer, 'S' struct by value, '...'"""
    if p == '...': return '...'
    if '*' in p or '(' in p or '[' in p: return 'I'
    q = re.sub(r'\b(const|volatile|register)\b', ' ', p).split()
    if not q: return 'I'
    if q[0] in ('struct', 'union') : return 'S'
    if q[0] in ('f32', 'float'): return 'F'
    if q[0] in ('f64', 'double'): return 'D'
    if q[0] in ('s64', 'u64') or ' '.join(q[:2]) == 'long long': return 'L'
    if re.match(r'^[A-Z]\w*$', q[0]) and q[0] not in ('OSTime', 'OSPri', 'OSId', 'OSMesg', 'OSEvent', 'OSIntMask',
                                                      'OSYieldResult', 'OSPageMask'):
        return 'S?'       # capitalised typedef by value: maybe a struct
    return 'I'

def rkind(ret):
    r = ret.replace('static', '').replace('extern', '').replace('inline', '').strip()
    if '*' in r: return 'I'
    w = r.split()
    if not w: return 'I'
    if w[-1] == 'void': return 'V'
    if w[-1] in ('f32', 'float'): return 'F'
    if w[-1] in ('f64', 'double'): return 'D'
    return 'I'

DECL_RE = re.compile(r'(?:^|[;}{\n])[ \t]*((?:(?:static|extern|inline|const|volatile|unsigned|signed|struct|union|enum)\s+)*'
                     r'[A-Za-z_]\w*[\s*]+)([A-Za-z_]\w*)\s*\(')
def protos(text):
    """name -> list of (ret kind, [param kinds] or None (unprototyped), is_definition)"""
    res = {}
    for m in DECL_RE.finditer(text):
        ret, name = m.group(1), m.group(2)
        if ret.split()[0] in ('return', 'else', 'goto', 'case', 'sizeof', 'do') or name in ('if', 'while', 'for', 'switch', 'return', 'sizeof'):
            continue
        i = m.end() - 1; j = match_paren(text, i)
        if j < 0: continue
        k = j + 1
        while k < len(text) and text[k] in ' \t\n': k += 1
        nxt = text[k:k + 1]
        if nxt not in (';', '{', ','): continue
        inner = text[i + 1:j].strip()
        if inner == '': pk = None
        elif inner == 'void': pk = []
        else:
            ps = split_args(inner)
            if all(re.fullmatch(r'\w+', p) for p in ps) and nxt == '{':
                pk = None                # K&R definition
            else: pk = [ptype(p) for p in ps]
        res.setdefault(name, []).append((rkind(ret), pk, nxt == '{'))
    return res

# ------------------------------------------------------------------ asm side
G, afuncs = [], {}        # global instruction list in address order (hand asm falls / branches across symbols)
for line in open(DIS):
    m = re.match(r'^([0-9a-f]+) <([^>]+)>:', line)
    if m: afuncs[m.group(2)] = len(G); continue
    m = re.match(r'^\s*([0-9a-f]+):\t(\S+)\t?(.*)$', line)
    if m: G.append((int(m.group(1), 16), m.group(2), m.group(3).strip()))
ADDR2I = {a: i for i, (a, _, _) in enumerate(G)}
GPR = set('zero at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 t8 t9 s0 s1 s2 s3 s4 s5 s6 s7 s8 k0 k1 gp sp fp ra'.split())
STORES = {'sb', 'sh', 'sw', 'swl', 'swr', 'sd', 'swc1', 'sdc1'}
LOADS = {'lb', 'lbu', 'lh', 'lhu', 'lw', 'lwl', 'lwr', 'ld', 'lwc1', 'ldc1', 'lwu'}
CALLER_SAVED = ['at', 'v0', 'v1', 'a0', 'a1', 'a2', 'a3'] + ['t%d' % i for i in range(10)] + \
               ['$f%d' % i for i in range(0, 20)]
def regs(s):
    return [r for r in re.findall(r'\$?\w+', s) if r in GPR or re.match(r'\$f\d+$', r)]

def split_ops(s):
    return [x.strip() for x in s.split(',')] if s else []

GN = len(G)
SUCC, CALLAT = [None] * GN, {}
def bt(ops):
    m = re.search(r'([0-9a-f]+) <', ops)
    return ADDR2I.get(int(m.group(1), 16)) if m else None
i = 0
while i < GN:
    _, op, ops = G[i]; nx = i + 1
    if op in ('jal', 'jalr', 'bal', 'bgezal', 'bltzal'):
        if op == 'jal':
            m = re.search(r'<([^>+]+)>', ops); t = m.group(1) if m else '?'
        else: t = '?'
        SUCC[i] = [nx]
        if i + 1 < GN: SUCC[i + 1] = [i + 2]; CALLAT[i + 1] = t
        i += 2; continue
    if (op.startswith('b') and op != 'break') or op in ('j', 'jr'):
        likely = op.endswith('l') and op not in ('b', 'bal')
        if op == 'jr': tt = [-1] if ops == 'ra' else []
        else:
            t = bt(ops); tt = [t] if t is not None else []
        unc = op in ('b', 'j', 'jr') or (op == 'beq' and ops.startswith('zero,zero'))
        fall = [] if unc else [i + 2]
        if i + 1 < GN:
            if likely: SUCC[i] = [i + 1] + fall; SUCC[i + 1] = tt
            else: SUCC[i] = [i + 1]; SUCC[i + 1] = tt + fall
        i += 2; continue
    SUCC[i] = [] if op in ('syscall', 'break') else [nx]; i += 1

ENT = ('a0', 'a1', 'a2', 'a3')
def analyse(name):
    """-> dict(cls={word: set of classes}, freg={0,1 read via f12/f14}, dbl=bool, v0=tags, f0=tags)"""
    s0 = afuncs[name]; N = -1
    frame = 0
    for _, op, ops in G[s0:s0 + 6]:
        m = re.match(r'sp,sp,-(\d+)$', ops)
        if op == 'addiu' and m: frame = int(m.group(1)); break
    init = {'a%d' % k: frozenset(['E%d' % k]) for k in range(4)}
    init['$f12'] = frozenset(['EF0']); init['$f13'] = frozenset(['EF0']); init['$f14'] = frozenset(['EF1']); init['$f15'] = frozenset(['EF1'])
    states = {s0: init}
    cls = collections.defaultdict(set); freg = set(); dbl = [False]
    work = [s0]
    def classify(tags, c):
        for t in tags:
            if t.startswith('EF'): freg.add(int(t[2:]))
            elif t[0] in 'EM': cls[int(t[1:])].add(c)
    def mtag(tags):     # GPR / stack bits moved into an FPR: classified by the FP use (cvt.s.w = int)
        return frozenset(['M' + t[1:] if (t[0] == 'E' and not t.startswith('EF')) else t for t in tags]) or frozenset(['W'])
    while work:
        i = work.pop()
        if i < 0 or i >= GN: continue
        st = dict(states[i])
        _, op, ops = G[i]
        o = split_ops(ops)
        T = lambda r: frozenset(['W']) if r == 'zero' else st.get(r, frozenset())
        dsts = []
        m = re.search(r'(-?\d+)\((\w+)\)$', ops)
        if op in STORES and m and len(o) == 2:
            val, base, off = o[0], m.group(2), int(m.group(1))
            if base == 'sp':
                st['sp%d' % off] = T(val)
                if op == 'sdc1': classify(T(val), 'F')
            else:
                classify(T(base), 'I')
                classify(T(val), 'F' if op == 'sdc1' else 'A')
        elif op in LOADS and m and len(o) == 2:
            d, base, off = o[0], m.group(2), int(m.group(1))
            if base == 'sp':
                if ('sp%d' % off) in st: tg = st['sp%d' % off]
                elif off >= frame + 16 and frame and (off - frame) % 4 == 0: tg = frozenset(['E%d' % ((off - frame) // 4)])
                elif off >= frame + 16 and frame and op in ('lh', 'lhu', 'lb', 'lbu'): tg = frozenset(['E%d' % ((off - frame) // 4)])
                else: tg = frozenset(['W'])
                if op in ('lwc1', 'ldc1'):
                    if op == 'ldc1': dbl[0] = True; classify(tg, 'F'); st[d] = frozenset(['W'])
                    else: st[d] = mtag(tg)
                    if op == 'ldc1': st['$f%d' % (int(d[2:]) + 1)] = frozenset(['W'])
                elif op in ('lw', 'ld'):
                    st[d] = tg
                else:
                    classify(tg, 'I'); st[d] = frozenset(['W'])
            else:
                classify(T(base), 'I'); st[d] = frozenset(['W'])
                if op == 'ldc1': st['$f%d' % (int(d[2:]) + 1)] = frozenset(['W'])
        elif op in ('move',) or (op in ('or', 'addu', 'daddu') and len(o) == 3 and 'zero' in o[1:]):
            s = o[1] if o[1] != 'zero' else o[2]
            st[o[0]] = T(s) if s != 'zero' else frozenset(['W'])
        elif op in ('mov.s', 'mov.d'):
            st[o[0]] = T(o[1])
            if op == 'mov.d': st['$f%d' % (int(o[0][2:]) + 1)] = T('$f%d' % (int(o[1][2:]) + 1)); dbl[0] = True
        elif op in ('mtc1', 'dmtc1'):
            st[o[1]] = mtag(T(o[0]))
        elif op in ('mfc1',):
            classify(set(t for t in T(o[1]) if t.startswith('EF')), 'F')
            st[o[0]] = frozenset(['E' + t[1:] if t[0] == 'M' else 'W' for t in T(o[1])]) or frozenset(['W'])
        elif op in ('jal',):
            pass                                  # handled at the delay slot (callat)
        elif op == 'jr':
            if o and o[0] != 'ra': classify(T(o[0]), 'I')
        elif op == 'jalr':
            classify(T(o[-1]), 'I'); st['ra'] = frozenset(['W'])
        else:
            rs = [regs(x) for x in o]
            isbr = (op.startswith('b') and op != 'break') or op.startswith('c.') or op in ('mult', 'multu', 'div', 'divu',
                   'dmult', 'dmultu', 'ddiv', 'ddivu', 'mtlo', 'mthi', 'teq', 'tne', 'ctc1')
            if isbr: uses, defs = [r for x in rs for r in x], []
            elif not o: uses, defs = [], []
            else: uses, defs = [r for x in rs[1:] for r in x], rs[0]
            isfp = '.' in op or op.startswith('c.')
            if op.endswith('.d') or '.d.' in op or op.startswith('cvt.s.d'): dbl[0] = True
            for r in uses:
                if isfp and re.match(r'cvt\.[sd]\.w$', op): classify(T(r), 'I')
                else: classify(T(r), 'F' if isfp else 'I')
            for r in defs:
                st[r] = frozenset(['W'])
                if op.endswith('.d') and r.startswith('$f'): st['$f%d' % (int(r[2:]) + 1)] = frozenset(['W'])
        if i in CALLAT:
            t = CALLAT[i]
            if t != '?':
                for k, r in enumerate(ENT):
                    for tg in T(r):
                        if tg[0] == 'E' and not tg.startswith('EF'): cls[int(tg[1:])].add(('P', t, k))
                for k, r in ((0, '$f12'), (1, '$f14')):
                    classify(set(x for x in T(r) if x[0] == 'M'), 'F')
                    for tg in T(r):
                        if tg.startswith('EF'): cls[('f', int(tg[2:]))].add(('PF', t, k))
            for r in CALLER_SAVED: st[r] = frozenset(['X'])
            st['v0'] = st['v1'] = frozenset(['R:' + t]); st['$f0'] = st['$f1'] = frozenset(['R:' + t])
        for j in (SUCC[i] or []):
            if j is None: continue
            old = states.get(j)
            if old is None: states[j] = st; work.append(j); continue
            ch = False; new = dict(old)
            for k, v in st.items():
                w = new.get(k, frozenset()) | v
                if w != new.get(k): new[k] = w; ch = True
            for k in list(new):
                if k not in st and k.startswith('sp'): pass
            if ch: states[j] = new; work.append(j)
    ex = states.get(-1) or {}
    return dict(cls=cls, freg=freg, dbl=dbl[0], v0=ex.get('v0', frozenset()), f0=ex.get('$f0', frozenset()))

AN = {}
def an(f):
    if f not in AN:
        AN[f] = analyse(f) if f in afuncs else None
    return AN[f]

def word_kind(f, k, depth=0, seen=None):
    """resolved classes of argument word k of f: subset of {'F','I','A'} (empty = unused)"""
    a = an(f)
    if a is None or depth > 8: return set()
    out = set()
    for c in a['cls'].get(k, ()):
        if isinstance(c, tuple):
            if c[0] == 'P' and c[1] != f:
                sub = word_kind(c[1], c[2], depth + 1)
                out |= sub
                if c[2] == 0 and 0 in fp_read(c[1], depth + 1): pass
        else: out.add(c)
    return out

def fp_read(f, depth=0):
    a = an(f)
    if a is None or depth > 8: return set()
    out = set(a['freg'])
    for key in (('f', 0), ('f', 1)):
        for c in a['cls'].get(key, ()):
            if c[1] != f and c[2] in fp_read(c[1], depth + 1): out.add(key[1])
    return out

def words_read(f):
    a = an(f)
    if a is None: return set()
    return set(k for k in a['cls'] if isinstance(k, int) and word_kind(f, k))

def ret_sets(f, depth=0):
    """-> (v0 set here?, f0 set here?) resolving R:callee"""
    a = an(f)
    if a is None or depth > 8: return (False, False)
    def res(tags, which):
        r = False
        for t in tags:
            if t == 'W' or (t[0] == 'E'): r = True
            elif t.startswith('R:') and t[2:] not in ('?', f): r = r or ret_sets(t[2:], depth + 1)[which]
            elif t == 'R:?': r = True
        return r
    return (res(a['v0'], 0), res(a['f0'], 1))

# ------------------------------------------------------------------ C side
asm_only = set(); CFILE = {}
for line in open(os.path.join(REPO, 'port_work', 'p98', 'asmonly.txt')):
    p = line.rstrip('\n').split('\t')
    if len(p) == 3 and p[1].isdigit(): asm_only.add(p[0]); CFILE[p[0]] = p[2]

files = sorted(glob.glob(os.path.join(SRC, '**', '*.c'), recursive=True))
texts, NML = {}, {}
for f in files:
    raw = open(f, errors='replace').read()
    NML[f] = nm_lines(raw); texts[f] = strip_comments(nm_select(raw))
for f, t in texts.items():
    for n, lst in protos(t).items():
        if any(d[2] for d in lst): asm_only.discard(n)
hdr = {}
for h in glob.glob(os.path.join(INC, '**', '*.h'), recursive=True):
    for n, lst in protos(strip_comments(open(h, errors='replace').read())).items():
        for r, pk, isdef in lst:
            if pk is not None: hdr.setdefault(n, (r, pk, os.path.relpath(h, INC)))
        if n not in hdr: hdr[n] = (lst[0][0], None, os.path.relpath(h, INC))

def layout(pk):
    """o32: [(param index, kind, location)] location = 'f12'/'f14' or word index; None if unknown (struct)"""
    out, w = [], 0
    fp0 = bool(pk) and pk[0] in ('F', 'D')
    for i, k in enumerate(pk):
        if k in ('S', '...'): return out, None
        if k in ('D', 'L'): w = (w + 1) & ~1
        if i < 2 and fp0 and k in ('F', 'D'): out.append((i, k, 'f12' if i == 0 else 'f14', w))
        else: out.append((i, k, w, w))
        w += 2 if k in ('D', 'L') else 1
    return out, w

CALL_RE = re.compile(r'\b(func_[0-9A-Fa-f]{8}|_?_?os\w+|[A-Za-z_]\w*)\s*\(')
rows = collections.OrderedDict()
def add(verdict, base, nm, line, callee, detail, src):
    key = (verdict, base, nm, callee, detail)
    if key not in rows: rows[key] = [0, line, src]
    rows[key][0] += 1

ncalls = 0; callees_seen = set()
for f, t in texts.items():
    base = os.path.relpath(f, SRC)
    tp = protos(t)
    lines_at = [0] + [i + 1 for i, ch in enumerate(t) if ch == '\n']
    import bisect
    lineno = lambda pos: bisect.bisect_right(lines_at, pos)
    for m in CALL_RE.finditer(t):
        name = m.group(1)
        if name not in asm_only or (ONLY and name != ONLY): continue
        # skip declarations themselves
        pre = t[max(0, m.start() - 40):m.start()]
        i = m.end() - 1; j = match_paren(t, i)
        if j < 0: continue
        after = t[j + 1:j + 40].lstrip()
        if re.search(r'(?:^|[;}{\n])[ \t]*(?:(?:static|extern|const|unsigned|signed|struct|union)\s+)*[A-Za-z_]\w*[\s*]+$', pre) \
                and after[:1] in (';', '{', ','):
            continue
        ln = lineno(m.start()); nm = '[NM]' if ln in NML[f] else '[M]'
        ncalls += 1; callees_seen.add(name)
        decls = [d for d in tp.get(name, []) if not d[2]]
        pro = [d for d in decls if d[1] is not None]
        if pro: r, pk, src = pro[-1][0], pro[-1][1], 'tu'
        elif name in hdr and hdr[name][1] is not None: r, pk, src = hdr[name][0], hdr[name][1], 'h:' + hdr[name][2]
        else:
            r = decls[-1][0] if decls else (hdr[name][0] if name in hdr else 'I'); pk = None
            src = 'tu-knr' if decls else ('h-knr' if name in hdr else 'implicit')
        if an(name) is None: continue
        wr = words_read(name); fr = fp_read(name)
        if pk is None:
            n = len(split_args(t[i + 1:j]))
            hi = [k for k in wr if k >= n]
            if hi: add('ARITY', base, nm, ln, name, 'unprototyped call passes %d, asm reads word(s) %s' % (n, sorted(wr)), src)
        else:
            lay, nw = layout(pk)
            if nw is None: continue
            for pi, k, loc, w in lay:
                if loc in ('f12', 'f14'):
                    if (0 if loc == 'f12' else 1) not in fr and word_kind(name, w):
                        add('FREG', base, nm, ln, name, 'param %d %s in %s, asm reads a%d (%s)' % (pi, k, loc, w, ''.join(sorted(word_kind(name, w)))), src)
                    continue
                wk = word_kind(name, w)
                if pi < 2 and w < 2 and (w in fr) and not (pk and pk[0] in ('F', 'D')):
                    add('FREG', base, nm, ln, name, 'param %d %s in a%d, asm reads $f%d' % (pi, k, w, 12 + 2 * w), src)
                elif k in ('F', 'D') and 'I' in wk and 'F' not in wk:
                    add('FLOAT', base, nm, ln, name, 'param %d f32 (word %d), asm uses it as int' % (pi, w), src)
                elif k in ('I', 'L', 'S?') and 'F' in wk and 'I' not in wk:
                    add('INT', base, nm, ln, name, 'param %d int (word %d), asm uses float bits' % (pi, w), src)
            hi = sorted(k for k in wr if k >= nw)
            if len(fr) and not pk: hi = hi or ['f12']
            if hi: add('ARITY', base, nm, ln, name, 'prototype %d word(s), asm reads word(s) %s' % (nw, hi), src)
        v0, f0 = ret_sets(name)
        if r in ('F', 'D') and not f0:
            add('RETF', base, nm, ln, name, 'returns f32 per prototype, asm sets %s' % ('v0 only' if v0 else 'nothing'), src)
        elif r == 'I' and f0 and not v0:
            add('RETI', base, nm, ln, name, 'returns int per prototype, asm sets f0 only', src)
        elif r != 'V' and not f0 and not v0:
            add('RETNONE', base, nm, ln, name, 'non-void prototype, asm sets neither v0 nor f0', src)

if WHY:
    a = an(WHY)
    print('words', {k: sorted(map(str, v)) for k, v in a['cls'].items()}, 'freg', a['freg'], 'dbl', a['dbl'],
          'v0', sorted(a['v0']), 'f0', sorted(a['f0']), 'resolved', {k: word_kind(WHY, k) for k in words_read(WHY)},
          'fp', fp_read(WHY), 'ret', ret_sets(WHY), file=sys.stderr)
order = ['FREG', 'FLOAT', 'INT', 'ARITY', 'RETF', 'RETI', 'RETNONE']
print('verdict\tfile\tnm\tline\tcallee\tn\tdetail\tproto_src\tcallee_file')
cnt = collections.Counter()
for key in sorted(rows, key=lambda k: (order.index(k[0]), k[1], k[3])):
    v, base, nm, callee, detail = key
    n, ln, src = rows[key]
    cnt[v] += 1
    cf = CFILE.get(callee, '?')
    if not os.path.exists(os.path.join(SRC, cf + '.c')): cf += '(hand .s)'
    print('\t'.join(map(str, (v, base, nm, ln, callee, n, detail, src, cf))))
print('# %d calls to %d asm-only callees; rows: %s' % (ncalls, len(callees_seen), ', '.join('%s %d' % (k, cnt[k]) for k in order)), file=sys.stderr)
