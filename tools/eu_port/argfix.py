#!/usr/bin/env python3
"""argfix.py (s50): rewrite the callee prototypes of an m2c draft from the CALLER's asm argument registers.
usage: argfix.py [--tail] [--stats] FUNC < draft.c > fixed.c        (FUNC = the function the draft replaces)
       argfix.py [--tail] FUNC in.c out.c
For every prototype line in the draft head (`ret callee(types);`) whose callee is not defined in C, scan the asm of FUNC
(conker/asm/nonmatchings/*/FUNC.s) at every `jal callee`:
  * arity = highest a0..a3 set in the segment since the previous call (+ untouched entry a-regs below it = pass-through,
    + stack slots written at 0x10(sp).. ); max over call sites.
  * f12 / f14 set -> leading f32 params (O32); `mfc1 aN,fM` -> f32 in a GPR;  `lui/ori` or `li` constant -> s32 (even if m2c said f32/ptr).
  * other kinds keep m2c's type for that position (new positions: s32).
  --tail also adds consecutive untouched entry a-regs after the last set one, up to the draft function's own param count (pass-through guess).
The call expressions in the body are padded (own argK / 0) or truncated to the new arity. Uses protocheck's asm parser.
"""
import re, sys, os, glob
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import protocheck as P

_defs = None
def cdefs():
    global _defs
    if _defs is None:
        _defs = set()
        for p in glob.glob(P.SRC + '/**/*.c', recursive=True):
            d, _, _ = P.scan_c(p)
            _defs |= set(f for f, s in d)
    return _defs

def find_asm(f):
    g = glob.glob('%s/*/%s.s' % (P.ASM, f))
    return g[0] if g else None

AREGS = ['a0', 'a1', 'a2', 'a3']

def defs_of(op, ops):
    try: d, u = P.defuse(op, ops)
    except Exception: return []
    return d

def sites(f):
    """-> (frame, {callee: [site]}) ; site = dict(slots={idx: kind}, entry=set(idx), nstack, fl={'f12','f14'})"""
    p = find_asm(f)
    if not p: return None
    ins, labels = P.parse_s(p)
    frame = 0
    for op, ops in ins[:3]:
        if op == 'addiu' and ops[:2] == ['$sp', '$sp'] and ops[2].startswith('-'): frame = int(ops[2][1:], 0)
    out = {}
    prevcall = -1
    pro = 0
    while pro < len(ins):
        o, os_ = ins[pro]
        if (o == 'addiu' and os_[:2] == ['$sp', '$sp']) or (o in ('sw', 'sd', 'swc1', 'sdc1') and re.match(r'\$(ra|s\d|fp|a[0-3]|f\d+)$', os_[0]) and '($sp)' in os_[-1]): pro += 1
        else: break
    for j, (op, ops) in enumerate(ins):
        if op != 'jal': continue
        lo = prevcall + 2 if prevcall >= 0 else 0
        hi = min(j + 1, len(ins) - 1)
        last = {}      # reg -> index of last def
        for k in range(lo, hi + 1):
            o, os_ = ins[k]
            for r in defs_of(o, os_): last[r] = k
        s = dict(slots={}, entry=set(), stack=set(), fl=set())
        for n, r in enumerate(AREGS):
            if r in last:
                k = last[r]; o, os_ = ins[k]
                kind = 'u'
                if o == 'mfc1': kind = 'f'
                elif o in ('ori', ) and os_[1] == '$zero' or o == 'li' or (o == 'addiu' and os_[1] == '$zero'): kind = 'i'
                elif o == 'ori' and os_[1] == os_[0]: kind = 'i'
                elif o == 'addiu' and '%lo' in os_[-1]: kind = 'p'
                elif o == 'lui': kind = 'c'
                s['slots'][n] = kind
            elif prevcall < 0:
                s['entry'].add(n)
        for r in ('f12', 'f14'):
            if r in last: s['fl'].add(r)
        for k in range(lo, hi + 1):
            o, os_ = ins[k]
            if o in ('sw', 'swc1') and re.match(r'(0x[0-9A-Fa-f]+|\d+)\(\$sp\)$', os_[-1]):
                off = int(os_[-1].split('(')[0], 0)
                if 0x10 <= off < 0x80 and (not frame or off < frame) and k >= pro: s['stack'].add((off - 0x10) // 4)
        out.setdefault(os_ if False else ops[-1], []).append(s)
        prevcall = j
    return frame, out

PROTO = re.compile(r'^(?P<pre>(?:extern\s+)?)(?P<ret>[\w\s\*\?]*?[\w\*\?])\s*\b(?P<name>func_\w+|D_\w+)\s*\((?P<params>.*)\)\s*;\s*$')

def class_of(t):
    t = t.strip()
    return 'f32' if t == 'f32' else 'ptr' if '*' in t else 'int'

def infer(callee_sites, oldtypes, ownn, tail):
    """-> list of type strings"""
    n = 0; kinds = {}
    for s in callee_sites:
        m = 0
        for i, kd in s['slots'].items():
            m = max(m, i + 1)
        if s['fl']:
            m = max(m, 1 if 'f14' not in s['fl'] else 2)
        top = m
        for i in s['entry']:
            if i < top: kinds.setdefault(i, 'e')
        st = sorted(s['stack'])
        c = 0
        while c in s['stack']: c += 1
        st = list(range(c))
        if st and top == 4 or (st and m >= 4): m = 4 + max(st) + 1
        elif st: m = 4 + max(st) + 1; 
        if tail and st == []:
            k = m
            while k in s['entry'] and k < ownn and k < 4: k += 1
            m = k
        n = max(n, m)
        for i, kd in s['slots'].items():
            if kd in 'fi' or kinds.get(i) in (None, 'e', 'u', 'c'): kinds[i] = kd
        if 'f12' in s['fl']: kinds[0] = 'F'
        if 'f14' in s['fl']: kinds[1] = 'F'
    types = []
    for i in range(n):
        old = oldtypes[i] if i < len(oldtypes) else None
        kd = kinds.get(i)
        if kd in ('F', 'f'): t = 'f32'
        elif kd == 'i': t = 's32' if old is None or class_of(old) != 'int' else old
        elif kd == 'p': t = old if old and class_of(old) != 'f32' else 'u8 *'
        else: t = old if old not in (None, '?') else 's32'
        types.append(t)
    return types

def split_args(s):
    return [a.strip() for a in P.split_top(s)] if s.strip() else []

_hdr = None
def hdr_protos():
    global _hdr
    if _hdr is None:
        _hdr = set()
        for h in glob.glob(P.R + '/include/**/*.h', recursive=True):
            try:
                _, pr, _ = P.scan_c(h)
                _hdr |= set(n for n, sg in pr)
            except Exception: pass
    return _hdr

def target_lines(f):
    for p in glob.glob(P.SRC + '/**/*.c', recursive=True):
        t = open(p, errors='replace').read()
        if re.search(r'GLOBAL_ASM\("[^"]*/%s\.s"\)' % re.escape(f), t): return t.split('\n')
    return []

def fix(body, f, tail=False):
    r = sites(f)
    if r is None: return body, ['noasm']
    frame, st = r
    notes = []
    m = re.search(r'^\S[^;{]*\b%s\s*\([^;]*\)\s*\{' % re.escape(f), body, re.M)
    ownn = 0
    if m:
        hd = body[m.start():m.end()]
        ps = hd[hd.index('(') + 1: hd.rindex(')')]
        ownn = len(split_args(ps)) if ps.strip() != 'void' else 0
    newn = {}
    lines = body.split('\n')
    tl = target_lines(f)
    drops = []
    for li, l in enumerate(lines):
        m = PROTO.match(l)
        if not m or m.group('name') not in st or m.group('name').startswith('D_'): continue
        name = m.group('name')
        if name in newn: lines[li] = '//USE-EXISTING ' + l; continue
        fl = [x for x in tl if PROTO.match(x) and PROTO.match(x).group('name') == name]
        if name in cdefs() or (name in hdr_protos() and not fl):
            lines[li] = '//USE-EXISTING ' + l; notes.append('%s: existing prototype kept' % name); continue
        for x in fl:
            drops.append('//DROP ' + x); notes.append('%s: drop file prototype' % name)
        ps = m.group('params').strip()
        old = [] if ps in ('', 'void') else split_args(ps)
        old = [re.sub(r'\s*\b\w+$', '', p) if re.search(r'[\w\*\]]\s+\w+$', p) and '(' not in p and not re.fullmatch(r'(unsigned\s+)?\w+', p.strip()) else p for p in old]
        types = infer(st[name], old, ownn, tail)
        ret = m.group('ret').strip()
        if ret == '?': ret = 's32'
        lines[li] = '%s%s %s(%s);' % (m.group('pre'), ret, name, ', '.join(types) if types else 'void')
        newn[name] = len(types)
        if types != old: notes.append('%s: %d -> %d [%s]' % (name, len(old), len(types), ', '.join(types)))
    body = '\n'.join(drops + [x for x in lines if not x.startswith('//USE-EXISTING ')])
    # pad / truncate call expressions
    for name, n in newn.items():
        out = []; i = 0
        pat = re.compile(r'\b%s\s*\(' % name)
        while True:
            m = pat.search(body, i)
            if not m: out.append(body[i:]); break
            ls = body.rfind('\n', 0, m.start()) + 1
            if PROTO.match(body[ls: body.find('\n', m.end())]) : out.append(body[i:m.end()]); i = m.end(); continue
            j = m.end(); d = 1
            while j < len(body) and d:
                d += {'(': 1, ')': -1}.get(body[j], 0); j += 1
            args = split_args(body[m.end(): j - 1])
            if len(args) > n: args = args[:n]
            while len(args) < n:
                k = len(args)
                args.append('arg%d' % k if k < ownn else '0')
            out.append(body[i:m.end()] + ', '.join(args) + ')'); i = j
        body = ''.join(out)
    return body, notes

if __name__ == '__main__':
    a = sys.argv[1:]
    tail = '--tail' in a; a = [x for x in a if x != '--tail']
    stats = '--stats' in a; a = [x for x in a if x != '--stats']
    f = a[0]
    src = open(a[1]).read() if len(a) > 1 else sys.stdin.read()
    body, notes = fix(src, f, tail)
    if stats: print('\n'.join(notes), file=sys.stderr)
    if len(a) > 2: open(a[2], 'w').write(body)
    else: sys.stdout.write(body)
