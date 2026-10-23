#!/usr/bin/env python3
"""P95: find IEEE-float bit patterns written as integer literals where the port would see a float.

On N64 an m2c/IDO matching body can pass `0x3F800000` in an integer register (or store the word) and still be
byte-identical; in the port (wasm, NON_MATCHING) the C semantics apply, so the literal becomes the integer 1065353216
converted to float, or an int passed where the callee reads a float.

Scans every C file under conker/src_eu with the NON_MATCHING branches selected (= what the port compiles).
Candidates: hex literals (8 digits) or big decimal literals whose exponent field is 0x60..0x9F.
  strength S = low 12 mantissa bits zero (typical float constant), W = otherwise.
For call arguments the parameter type is resolved from (1) the TU's prototypes, (2) the callee's C definition
(any src_eu file, NM branch), (3) include/functions.h, (4) the callee's asm in the EU disassembly
(arg in a0..a3 moved by mtc1, or stored then lwc1-loaded from the same slot; stack arg lwc1-loaded).
Assignments / initializers: f32 lvalue by `*(f32 *)` cast, `f32` local/global declarations, f32 array initializers.

Verdicts:
  BUG-F32PROTO   TU prototype says f32 for that parameter: the literal is converted numerically (wrong everywhere
                 except on IDO when the call site passes in an int register -- never byte-identical, so rare).
  BUG-MISMATCH   TU prototype / call passes int but the callee's real parameter is a float (definition or asm).
  OK-INT         callee really takes an int (definition/asm agree): bits pass through, port-safe.
  ASSIGN-F32     stored into an f32 lvalue: wrong in C.
  REVIEW         type unknown; check by hand.
usage: floatint_scan.py [--dis port_work/p93/eu.dis] [--all]   (prints TSV; --all includes OK rows)
"""
import os, re, sys, glob, struct

ROOT = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.abspath(os.path.join(ROOT, '..', '..', '..', '..'))
SRC = os.path.join(REPO, 'conker', 'src_eu')
INC = os.path.join(REPO, 'conker', 'include')
args = sys.argv[1:]
DIS = os.path.join(REPO, 'port_work', 'p93', 'eu.dis')
if '--dis' in args:
    DIS = args[args.index('--dis') + 1]
SHOW_ALL = '--all' in args

FLOAT_T = {'f32', 'float', 'f64', 'double'}


NMLINES = {}


def nm_lines(text):
    """1-based line numbers inside an active `#ifdef NON_MATCHING` branch (code that only the NM build compiles)."""
    res, depth_nm, stack = set(), 0, []
    for n, line in enumerate(text.split('\n'), 1):
        s = line.strip()
        m = re.match(r'#\s*(ifdef|ifndef|if|else|endif)\b(.*)', s)
        if m:
            d, rest = m.group(1), m.group(2).strip()
            if d in ('ifdef', 'ifndef', 'if'):
                k = None
                if rest in ('NON_MATCHING',) or re.fullmatch(r'defined\s*\(?\s*NON_MATCHING\s*\)?', rest):
                    k = (d != 'ifndef')
                stack.append(k)
            elif d == 'else' and stack and stack[-1] is not None:
                stack[-1] = not stack[-1]
            elif d == 'endif' and stack:
                stack.pop()
            continue
        if any(x is True for x in stack):
            res.add(n)
    return res


def nm_select(text):
    """Blank out the branches not compiled with NON_MATCHING defined (other #if: keep everything)."""
    out = []
    stack = []  # entries: (kind, active_now, parent_active); kind 'nm' or 'other'
    active = True
    for line in text.split('\n'):
        s = line.strip()
        m = re.match(r'#\s*(ifdef|ifndef|if|elif|else|endif)\b(.*)', s)
        if m:
            d, rest = m.group(1), m.group(2).strip()
            if d in ('ifdef', 'ifndef', 'if'):
                nm = None
                if d == 'ifdef' and rest == 'NON_MATCHING':
                    nm = True
                elif d == 'ifndef' and rest == 'NON_MATCHING':
                    nm = False
                elif d == 'if' and re.fullmatch(r'defined\s*\(?\s*NON_MATCHING\s*\)?', rest):
                    nm = True
                elif d == 'if' and re.fullmatch(r'!\s*defined\s*\(?\s*NON_MATCHING\s*\)?', rest):
                    nm = False
                elif d == 'if' and rest == '0':
                    nm = False
                stack.append(('nm' if nm is not None else 'other', nm, active))
                if nm is not None:
                    active = active and nm
            elif d == 'else' and stack:
                kind, nm, par = stack[-1]
                if kind == 'nm':
                    stack[-1] = (kind, not nm, par)
                    active = par and (not nm)
            elif d == 'endif' and stack:
                kind, nm, par = stack.pop()
                active = par
            out.append('')
            continue
        out.append(line if active else '')
    return '\n'.join(out)


def strip_comments(t):
    t = re.sub(r'/\*.*?\*/', lambda m: re.sub(r'[^\n]', ' ', m.group(0)), t, flags=re.S)
    return re.sub(r'//[^\n]*', '', t)


def split_args(s):
    parts, depth, cur = [], 0, ''
    for ch in s:
        if ch in '([{':
            depth += 1
        elif ch in ')]}':
            depth -= 1
        if ch == ',' and depth == 0:
            parts.append(cur.strip()); cur = ''
        else:
            cur += ch
    if cur.strip():
        parts.append(cur.strip())
    return parts


def match_paren(t, i):
    """t[i] == '(' -> index of matching ')'."""
    depth = 0
    for j in range(i, len(t)):
        if t[j] == '(':
            depth += 1
        elif t[j] == ')':
            depth -= 1
            if depth == 0:
                return j
    return -1


def param_types(plist):
    ps = split_args(plist)
    if ps == ['void'] or not ps:
        return []
    res = []
    for p in ps:
        if p == '...':
            res.append('...'); continue
        p = re.sub(r'\b(const|volatile|unsigned|signed|register)\b', ' ', p).strip()
        base = p.split()[0] if p.split() else p
        res.append('ptr' if '*' in p or '(' in p or '[' in p else base)
    return res


DECL_RE = re.compile(r'(?:^|[;}\n])\s*(?:static\s+|extern\s+)?([A-Za-z_]\w*)(?:\s+|\s*\*+\s*)(func_[0-9A-Fa-f]{8}|[A-Za-z_]\w*)\s*\(')


def protos(text):
    """name -> list of (param types, is_definition)."""
    res = {}
    for m in DECL_RE.finditer(text):
        ret, name = m.group(1), m.group(2)
        if ret in ('return', 'else', 'goto', 'case', 'sizeof') or name in ('if', 'while', 'for', 'switch', 'return', 'sizeof'):
            continue
        i = m.end() - 1
        j = match_paren(text, i)
        if j < 0:
            continue
        k = j + 1
        while k < len(text) and text[k] in ' \t\n':
            k += 1
        nxt = text[k:k + 1]
        if nxt not in (';', '{'):
            continue
        res.setdefault(name, []).append((param_types(text[i + 1:j]), nxt == '{'))
    return res


def floatlike(v):
    v &= 0xFFFFFFFF
    if v < 0x10000000:
        return None
    e = (v >> 23) & 0xFF
    if not (0x60 <= e <= 0x9F):
        return None
    f = struct.unpack('>f', struct.pack('>I', v))[0]
    return ('S' if (v & 0xFFF) == 0 else 'W'), f


LIT_RE = re.compile(r'^(?:\(\s*(?:s32|u32|int|f32|float)\s*\)\s*)?(0x[0-9A-Fa-f]{8}|\d{9,10})[uUlL]*$')

# --- asm (EU disassembly) ---
asm = {}
if os.path.exists(DIS):
    cur = None
    with open(DIS) as fh:
        for line in fh:
            m = re.match(r'^[0-9a-f]+ <(\w+)>:', line)
            if m:
                cur = m.group(1); asm[cur] = []; continue
            if cur and '\t' in line:
                p = line.split('\t')
                if len(p) >= 3:
                    asm[cur].append((p[1].strip(), p[2].strip()))


def asm_arg_kind(fn, idx):
    ins = asm.get(fn)
    if not ins:
        return None
    frame = 0
    for op, a in ins[:4]:
        m = re.match(r'sp,sp,(-\d+)', a)
        if op == 'addiu' and m:
            frame = -int(m.group(1))
    if idx < 4:
        reg = 'a%d' % idx
        slots = set()
        for op, a in ins:
            if op == 'mtc1' and a.startswith(reg + ','):
                return 'float(mtc1)'
            m = re.match(reg + r',(\d+)\(sp\)', a)
            if op == 'sw' and m:
                slots.add(int(m.group(1)))
        for op, a in ins:
            m = re.match(r'\$f\d+,(\d+)\(sp\)', a)
            if op == 'lwc1' and m and int(m.group(1)) in slots:
                return 'float(spill)'
        # integer use: any read of the register before it is written is hard to model; report int if used at all
        for op, a in ins:
            if re.search(r'\b' + reg + r'\b', a):
                return 'int'
        return 'unused'
    off = frame + 4 * idx
    for op, a in ins:
        m = re.match(r'\$f\d+,(\d+)\(sp\)', a)
        if op == 'lwc1' and m and int(m.group(1)) == off:
            return 'float(stack)'
    for op, a in ins:
        m = re.match(r'\w+,(\d+)\(sp\)', a)
        if op in ('lw', 'lh', 'lhu', 'lb', 'lbu') and m and int(m.group(1)) in (off, off + 2, off + 3):
            return 'int'
    return 'unused'


# --- sources ---
files = sorted(glob.glob(os.path.join(SRC, '**', '*.c'), recursive=True))
texts = {}
for f in files:
    with open(f, errors='replace') as fh:
        raw = fh.read()
        NMLINES[f] = nm_lines(raw)
        texts[f] = strip_comments(nm_select(raw))
defs = {}
for f, t in texts.items():
    for n, lst in protos(t).items():
        for pt, isdef in lst:
            if isdef:
                defs.setdefault(n, []).append((pt, os.path.basename(f)))
hdr = {}
for h in glob.glob(os.path.join(INC, '*.h')):
    with open(h, errors='replace') as fh:
        for n, lst in protos(strip_comments(fh.read())).items():
            hdr.setdefault(n, lst[0][0])

rows = []
CALL_RE = re.compile(r'\b(func_[0-9A-Fa-f]{8}|[A-Za-z_]\w*)\s*\(')
KW = {'if', 'while', 'for', 'switch', 'return', 'sizeof', 'defined'}
for f, t in texts.items():
    base = os.path.relpath(f, SRC)
    tp = protos(t)
    lines_at = [0]
    for i, ch in enumerate(t):
        if ch == '\n':
            lines_at.append(i + 1)
    import bisect
    lineno = lambda pos: bisect.bisect_right(lines_at, pos)
    # calls
    for m in CALL_RE.finditer(t):
        name = m.group(1)
        if name in KW:
            continue
        i = m.end() - 1
        j = match_paren(t, i)
        if j < 0:
            continue
        al = split_args(t[i + 1:j])
        for k, a in enumerate(al):
            lm = LIT_RE.match(a)
            if not lm:
                continue
            lit = lm.group(1)
            v = int(lit, 0)
            fl = floatlike(v)
            if not fl:
                continue
            # skip declarations' parameter lists (no literals there anyway)
            tu = [p[0] for p in tp.get(name, [])]
            tu_t = sorted({p[k] for p in tu if k < len(p)})
            d_t = sorted({p[0][k] for p in defs.get(name, []) if k < len(p[0])})
            h_t = hdr[name][k] if name in hdr and k < len(hdr[name]) else ''
            a_k = asm_arg_kind(name, k) or ''
            real_float = any(x in FLOAT_T for x in d_t) or a_k.startswith('float')
            real_int = (d_t and not any(x in FLOAT_T for x in d_t)) or a_k in ('int',)
            tu_float = any(x in FLOAT_T for x in tu_t) or (not tu_t and h_t in FLOAT_T)
            if '(f32)' in a.replace(' ', '') or '(float)' in a.replace(' ', ''):
                tu_float = True
            if tu_float:
                verdict = 'BUG-F32PROTO'
            elif real_float:
                verdict = 'BUG-MISMATCH'
            elif real_int:
                verdict = 'OK-INT'
            else:
                verdict = 'REVIEW'
            rows.append((verdict, fl[0], base + ('[NM]' if lineno(m.start()) in NMLINES[f] else '[M]'), lineno(m.start()), name, k, lit, '%g' % fl[1],
                         '/'.join(tu_t) or '-', '/'.join(d_t) or '-', h_t or '-', a_k or '-'))
    # assignments: lvalue = LIT ;
    f32vars = set()
    for dm in re.finditer(r'\b(?:f32|float)\s+([^;(){}]+);', t):
        for v in dm.group(1).split(','):
            vm = re.match(r'\s*\**\s*(\w+)', v)
            if vm:
                f32vars.add(vm.group(1))
    for am in re.finditer(r'([^;{}\n]*?)\s(?<![=!<>+\-*/&|^])=\s*(0x[0-9A-Fa-f]{8}|\d{9,10})[uUlL]*\s*;', t):
        lhs, lit = am.group(1).strip(), am.group(2)
        fl = floatlike(int(lit, 0))
        if not fl:
            continue
        if re.search(r'\(\s*(f32|float)\s*\*\s*\)', lhs) or re.match(r'^(f32|float)\s', lhs):
            verdict = 'ASSIGN-F32'
        else:
            vm = re.search(r'(\w+)\s*(\[[^\]]*\])?\s*$', lhs)
            if vm and vm.group(1) in f32vars and not re.search(r'->|\.', lhs[-len(vm.group(0)) - 2:]):
                verdict = 'ASSIGN-F32'
            elif re.search(r'\(\s*(s32|u32|int)\s*\*\s*\)', lhs) or re.match(r'^(s32|u32|int)\s', lhs):
                verdict = 'OK-INT'
            else:
                verdict = 'REVIEW'
        rows.append((verdict, fl[0], base + ('[NM]' if lineno(am.start(2)) in NMLINES[f] else '[M]'), lineno(am.start(2)), '=', '', lit, '%g' % fl[1], lhs[-60:], '-', '-', '-'))
    # f32 array / struct initializers
    for im in re.finditer(r'\b(f32|float)\s+\w+(\s*\[[^\]]*\])+\s*=\s*\{', t):
        j = t.find('};', im.end())
        body = t[im.end():j]
        for lm in re.finditer(r'\b(0x[0-9A-Fa-f]{8})\b', body):
            fl = floatlike(int(lm.group(1), 16))
            if fl:
                rows.append(('ASSIGN-F32', fl[0], base + ('[NM]' if lineno(im.end() + lm.start()) in NMLINES[f] else '[M]'), lineno(im.end() + lm.start()), 'init', '', lm.group(1), '%g' % fl[1], t[im.start():im.end()][:60], '-', '-', '-'))

order = {'BUG-F32PROTO': 0, 'BUG-MISMATCH': 1, 'ASSIGN-F32': 2, 'REVIEW': 3, 'OK-INT': 4}
rows.sort(key=lambda r: (order[r[0]], r[2], r[3]))
print('verdict\tstr\tfile[NM=only in the NON_MATCHING build, M=matching C]\tline\tcallee\targ\tliteral\tas_float\ttu_type\tdef_type\thdr_type\tasm')
from collections import Counter
cnt = Counter(r[0] for r in rows)
for r in rows:
    if SHOW_ALL or r[0] != 'OK-INT':
        print('\t'.join(str(x) for x in r))
print('# counts: ' + ', '.join('%s %d' % (k, cnt[k]) for k in order), file=sys.stderr)

# --- --protos: TU prototypes (NM build) whose float / non-float parameter kinds disagree with the C definition ---
if '--protos' in args:
    seen = 0
    print('\n# proto-mismatch\tfile\tcallee\targ\ttu_type\tdef_type(def file)', file=sys.stderr)
    for f, t in texts.items():
        base = os.path.relpath(f, SRC)
        for n, lst in protos(t).items():
            if n not in defs:
                continue
            for pt, isdef in lst:
                if isdef:
                    continue
                for dpt, dfile in defs[n][:1]:
                    for k in range(min(len(pt), len(dpt))):
                        a, b = pt[k] in FLOAT_T, dpt[k] in FLOAT_T
                        if a != b:
                            seen += 1
                            print('PROTO-MISMATCH\t%s\t%s\t%d\t%s\t%s (%s)' % (base, n, k, pt[k], dpt[k], dfile), file=sys.stderr)
    print('# proto-mismatch rows: %d' % seen, file=sys.stderr)
