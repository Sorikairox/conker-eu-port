#!/usr/bin/env python3
"""usage: draftcheck.py <func> [draft.c]   -> hint lines ("HINT ...") for an m2c/permuter draft vs the target asm.

Checks the session-16 call patterns:
  * a0..a3 untouched before a `jal` (in the first call segment, and used by the function itself) are
    pass-through args: the draft's call must pass them (m2c drops them) / must not invent extra ones;
  * a float following int args travels in a1..a3 as bits: `mfc1 aN` -> param is f32, `lw aN` -> param is s32,
    f12/f14 set by a call whose first param is not a float;
  * `*(&D + (i * k))` / `*(&D + i*k)` on a non-byte extern scales twice (byte offsets want (u8 *)&D + ...).
Prototypes come from the draft itself, then include/functions.h and the other src_eu files. Compact output.
"""
import sys, re, os, glob
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
func = sys.argv[1]
draft = sys.argv[2] if len(sys.argv) > 2 else os.path.expanduser(os.environ.get('CONKER_ROOT','~/conker')+'/tools/decomp-permuter/repair/%s.c' % func)

def find_s(f):
    g = glob.glob(R + '/asm/nonmatchings/*/%s.s' % f)
    return g[0] if g else None

sp = find_s(func)
src = open(draft).read() if os.path.exists(draft) else ''
hints = []

# ---- prototypes
_protos = {}
_prov = {}
def protos():
    # order of trust: C definitions in src_eu, functions.h, other declarations in src_eu, the draft's own
    if _protos: return _protos
    dpat = re.compile(r'^[A-Za-z_][\w \*]*?\b(\w+)\(([^)]*)\)\s*\{', re.M)
    ppat = re.compile(r'^[A-Za-z_][\w \*]*?\b(\w+)\(([^)]*)\)\s*;', re.M)
    srcs_ = glob.glob(R + '/src_eu/*.c')
    texts = {}
    for fn in srcs_ + [R + '/include/functions.h', draft]:
        try: texts[fn] = open(fn).read()
        except Exception: pass
    for fn in srcs_:
        for m in dpat.finditer(texts.get(fn, '')):
            if m.group(1) not in _protos: _prov[m.group(1)] = 'def'
            _protos.setdefault(m.group(1), m.group(2))
    for fn in [R + '/include/functions.h'] + srcs_ + [draft]:
        for m in ppat.finditer(texts.get(fn, '')):
            if m.group(1) not in _protos: _prov[m.group(1)] = 'draft' if fn == draft else ('hdr' if fn.endswith('functions.h') else 'decl')
            _protos.setdefault(m.group(1), m.group(2))
    return _protos

def params(name):
    p = protos().get(name)
    if p is None: return None
    p = p.strip()
    if p == '': return None   # old-style ()
    if p == 'void': return []
    return [x.strip() for x in p.split(',')]

def is_float(t): return bool(re.search(r'\b(f32|f64|float|double)\b', t)) and '*' not in t

def draft_call_args(name):
    """argument counts of calls to name in the draft (not the prototype line)"""
    out = []
    for m in re.finditer(r'(?<![\w])%s\(' % re.escape(name), src):
        i = m.end(); d = 1; n = 0; any_ = False
        while i < len(src) and d:
            c = src[i]
            if c == '(': d += 1
            elif c == ')': d -= 1
            elif c == ',' and d == 1: n += 1
            elif not c.isspace(): any_ = True
            i += 1
        if not any_: n = -1
        line_start = src.rfind('\n', 0, m.start()) + 1
        if re.match(r'\s*(extern|static)?\s*[\w\* ]+\s*$', src[line_start:m.start()]) and src[i:i+2].strip().startswith(';') and re.match(r'\s*[A-Za-z_]', src[line_start:m.start()]) and not re.search(r'=|return', src[line_start:m.start()]) and src[line_start:m.start()].strip().split(' ')[0] in ('s32','void','f32','u8','u16','s16','u32','s8','extern','static'):
            continue  # prototype/definition line
        out.append(n + 1)
    return out

# ---- asm parsing
ARG = {'$a0': 0, '$a1': 1, '$a2': 2, '$a3': 3}
def parse(sp):
    ins = []
    for l in open(sp):
        m = re.match(r'\s*/\* [0-9A-F]+ [0-9A-F]+ [0-9A-F]+ \*/\s*(\S+)\s*(.*)', l)
        if m: ins.append((m.group(1), [x.strip() for x in m.group(2).split(',')] if m.group(2).strip() else [], m.group(2)))
        elif re.match(r'\s*\.L\w+:', l): ins.append(('label', [], l.strip()))
    return ins

LOADS = ('lw', 'lh', 'lhu', 'lb', 'lbu', 'lwc1', 'ldc1')
STORES = ('sw', 'sh', 'sb', 'swc1', 'sdc1')
def dest(op, a):
    if not a: return None
    if op in STORES or op in ('beq', 'bne', 'beql', 'bnel', 'bgez', 'bltz', 'bgtz', 'blez', 'bc1f', 'bc1t', 'bc1fl', 'bc1tl', 'jr', 'j', 'jal', 'nop', 'mtc1', 'c.eq.s', 'c.lt.s', 'c.le.s'): return None
    return a[0]
def srcs(op, a):
    if not a: return []
    regs = re.findall(r'\$\w+', ' '.join(a[1:] if op not in STORES + ('beq', 'bne', 'beql', 'bnel', 'bgez', 'bltz', 'bgtz', 'blez') else a))
    if op == 'mtc1': regs = re.findall(r'\$\w+', a[0])
    return regs

def kind(op):
    if op in LOADS: return 'lw' if op == 'lw' else 'ld'
    if op == 'mfc1': return 'mfc1'
    if op in ('li', 'ori', 'lui', 'addiu') : return 'imm'
    if op in ('move', 'or', 'addu'): return 'move'
    return 'other'

if sp:
    ins = parse(sp)
    # live-in arg regs: read before written anywhere (linear)
    written = set(); livein = set()
    for op, a, raw in ins:
        for r in srcs(op, a):
            if r in ARG and r not in written: livein.add(ARG[r])
        d = dest(op, a)
        if d in ARG: written.add(d)
        if op == 'jal': break
    seg_w = {}; seg_k = {}; fw = set(); first = True; seg_stk = set()
    nargs_seen = {}
    i = 0
    while i < len(ins):
        op, a, raw = ins[i]
        if op == 'jal':
            # delay slot executes before the call
            if i + 1 < len(ins):
                dop, da, _ = ins[i + 1]
                dd = dest(dop, da)
                if dd in ARG: seg_w[ARG[dd]] = 1; seg_k[ARG[dd]] = kind(dop)
                if dop in STORES and len(da) > 1:
                    mm = re.match(r'(0x[0-9A-Fa-f]+|\d+)\(\$sp\)', da[1])
                    if mm: seg_stk.add(int(mm.group(1), 0))
                if dop == 'mtc1' and re.search(r'\$f1[24]', ' '.join(da)): fw.add(re.search(r'\$f1[24]', ' '.join(da)).group())
            name = a[0] if a else '?'
            pass_ = [n for n in range(4) if n not in seg_w and first and n in livein]
            used = sorted(set(seg_w) | set(pass_))
            k = (max(used) + 1) if used else 0
            stk = 0
            while (0x10 + 4 * stk) in seg_stk: stk += 1
            if stk and k == 4: k = 4 + stk
            # contiguous from 0 (a gap means garbage regs)
            ps = params(name)
            dc = draft_call_args(name)
            msgs = []
            if pass_ and dc and (ps is None or len(ps) >= max(pass_) + 1) and min(dc) < k:
                msgs.append('pass-through %s untouched before the call -> pass them (asm uses %d reg args, draft passes %s)' % (','.join('a%d' % n for n in pass_), k, '/'.join(map(str, sorted(set(dc))))))
            elif dc and used and not stk and k < max(dc) and ps is not None and len(ps) <= max(dc):
                msgs.append('draft passes %d args, asm sets only a0..a%d (%s) -> extra args invented?' % (max(dc), k - 1, 'garbage regs'))
            if ps is not None:
                if seg_w and len(ps) < max(seg_w) + 1 + (stk if max(seg_w) == 3 else 0) and not any('...' in p for p in ps):
                    msgs.append('proto has %d params, asm passes a0..a%d' % (len(ps), k - 1))
                for n in range(min(4, len(ps))):
                    kd = seg_k.get(n)
                    if kd in ('lw', 'ld') and is_float(ps[n]) and n > 0 and _prov.get(name) in ('draft', 'decl'):
                        msgs.append('lw/ld into a%d but param %d is %s -> s32 param' % (n, n, ps[n]))
                    if kd == 'mfc1' and not is_float(ps[n]):
                        msgs.append('mfc1 into a%d: param %d should be f32 (float after int args)' % (n, n))
                if fw and ps and not is_float(ps[0]) and not any(n for n in range(4) if seg_k.get(n) == 'mfc1'):
                    msgs.append('f12/f14 set before call but param 0 is %s -> f32 first param' % ps[0])
            elif used:
                msgs.append('no prototype found (asm passes a0..a%d)' % (k - 1))
            for m in msgs: hints.append('HINT jal %s: %s' % (name, m))
            seg_w = {}; seg_k = {}; fw = set(); first = False; seg_stk = set()
            i += 2; continue
        if op in STORES and len(a) > 1:
            mm = re.match(r'(0x[0-9A-Fa-f]+|\d+)\(\$sp\)', a[1])
            if mm: seg_stk.add(int(mm.group(1), 0))
        d = dest(op, a)
        if d in ARG:
            seg_w[ARG[d]] = 1; seg_k[ARG[d]] = kind(op)
        if op == 'mtc1' and len(a) > 1 and re.match(r'\$f1[24]$', a[1]): fw.add(a[1])
        if op in ('lwc1', 'mov.s', 'ldc1', 'cvt.s.w', 'add.s', 'mul.s') and a and re.match(r'\$f1[24]$', a[0]): fw.add(a[0])
        i += 1
else:
    hints.append('HINT no .s found for %s (already C?)' % func)

# ---- (&D + i*k) double scaling
externs = {}
for m in re.finditer(r'extern\s+(?:const\s+)?(\w+)\s+(D_\w+)', src):
    externs[m.group(2)] = m.group(1)
vh = None
def vtype(d):
    global vh
    if d in externs: return externs[d]
    if vh is None: vh = open(R + '/include/variables.h').read()
    m = re.search(r'extern\s+(?:const\s+)?(\w+)\s+%s\b' % d, vh)
    return m.group(1) if m else None
SZ = {'u8': 1, 's8': 1, 'char': 1, 'u16': 2, 's16': 2, 'u32': 4, 's32': 4, 'f32': 4, 'f64': 8, 'u64': 8, 's64': 8}
for m in re.finditer(r'\(\s*&(D_\w+)\s*\+\s*\(?\s*([^;]*?\*\s*(\d+))\s*\)?\s*\)', src):
    d, k = m.group(1), int(m.group(3))
    t = vtype(d)
    sz = SZ.get(t)
    if sz and sz > 1 or t and t not in SZ:
        hints.append('HINT (&%s + ... * %d): %s is %s%s, pointer arithmetic scales again -> ((u8 *)&%s + ...) or index the array' % (d, k, d, t, '' if sz else ' (struct?)', d))
for m in re.finditer(r'\b(D_\w+)\[[^\]]*\*\s*(\d+)\]', src):
    d, k = m.group(1), int(m.group(2))
    sz = SZ.get(vtype(d))
    if sz and sz > 1 and k % sz == 0:
        hints.append('HINT %s[... * %d]: element size %d, the index is scaled twice if %d is a byte stride' % (d, k, sz, k))

for m in re.finditer(r'\*?\(\s*&(D_\w+)\s*\+\s*[A-Za-z_(]', src):
    d = m.group(1); sz = SZ.get(vtype(d))
    if sz and sz > 1 and not any(d in h for h in hints):
        hints.append('HINT *(&%s + idx) on a %d-byte extern: if the asm reads it with lbu/lb (byte stride) declare it u8 %s[]' % (d, sz, d))
seen = set()
for h in hints:
    if h not in seen: print(h); seen.add(h)
