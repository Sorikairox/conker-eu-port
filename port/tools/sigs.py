"""One wasm signature per game function (docs/port/MEMORY.md, "Calls").

IDO accepted calls through implicit `int f()` declarations and local prototypes that disagree with
the definition; in wasm a direct call whose type differs from the callee's is linked as a trap.
Before the vbe rewrite, vbe_build.py collects every non-static `define` and every direct call site
over all game TUs (scan()), and picks the canonical signature of each function: the definition's,
or for asm-only functions (stubs) the most common call-site signature. normalize() then rewrites
each mismatching call site and `declare` in a TU to the canonical type, converting arguments
(int<->int sext/trunc, ptr<->int, float<->int bitcast, missing -> 0, extra -> dropped) and the
result (void -> 0). This reproduces what the MIPS o32 call would do for integer/pointer arguments;
an f32/int mix is wrong either way (different registers on MIPS too) and is reported.
"""
import collections, json, re
from vbe import split_top, take_type

DEFINE = re.compile(r'^define ((?:[\w()]+ )*?)(\S+|\{[^}]*\}) (@[\w.$-]+)\((.*?)\)( [^{]*)?\{?\s*$')
CALL = re.compile(r'^(\s*)(?:(%[\w.$-]+) = )?((?:tail |musttail |notail )?call )(.*?)(@[\w.$-]+)\((.*)\)([^)]*)$')
DECLARE = re.compile(r'^declare (.*?)(@[\w.$-]+)\((.*)\)(.*)$')
PATTR = {'noundef', 'signext', 'zeroext', 'inreg', 'nonnull', 'noalias', 'nocapture', 'readonly', 'returned',
         'writeonly', 'immarg', 'noused'}


def ptypes(params):
    out = []
    for p in split_top(params):
        if not p:
            continue
        if p == '...':
            out.append('...')
            continue
        t, _ = take_type(p)
        out.append(t)
    return out


def site_ret(mid):
    """'noundef i32 ' or 'i32 (i32, ...) ' -> 'i32'"""
    mid = mid.strip()
    if '(' in mid:
        mid = mid[:mid.index('(')].strip()
    toks = [t for t in mid.split() if t not in PATTR and not t.startswith(('align', 'dereferenceable'))]
    return toks[-1] if toks else None


def site_args(args):
    out = []
    for a in split_top(args):
        if not a:
            continue
        t, rest = take_type(a)
        toks = rest.split()
        # strip attributes (noundef, signext, align N, byval(T)...) -> value is the remainder
        while len(toks) > 1 and (toks[0] in PATTR or toks[0].startswith(('byval', 'sret', 'align', 'dereferenceable'))):
            if toks.pop(0) == 'align':
                toks.pop(0)  # its number
        out.append((t, ' '.join(toks)))
    return out


def scan(text, defs, sites):
    for l in text.split('\n'):
        if l.startswith('define '):
            m = DEFINE.match(l)
            if m and 'internal' not in m[1] and 'private' not in m[1]:
                defs[m[3]] = (m[2], ptypes(m[4]))
        elif l.startswith('declare ') and '...' in l:
            m = DECLARE.match(l)
            if m and not m[2].startswith('@llvm.') and ptypes(m[3])[:-1]:
                defs.setdefault(m[2], (site_ret(m[1]), ptypes(m[3])))  # prototyped variadic
        elif 'call ' in l and l.startswith('  '):
            m = CALL.match(l)
            if m and not m[5].startswith('@llvm.'):
                r = site_ret(m[4])
                if r:
                    sites[m[5]][json.dumps([r, [t for t, _ in site_args(m[6])]])] += 1


def canonical(defs, sites):
    can = {k: list(v) for k, v in defs.items()}
    for f, c in sites.items():
        if f not in can:
            r, ps = json.loads(c.most_common(1)[0][0])
            can[f] = [r, ps]
    return can


ZERO = {'ptr': 'null', 'float': '0.0', 'double': '0.0'}


def zero(t):
    return ZERO.get(t, '0' if t.startswith('i') else 'zeroinitializer')


def conv(ind, v, src, dst, tmp, out):
    if src == dst:
        return v
    if v in ('undef', 'poison'):
        return v
    isint = lambda t: re.match(r'^i\d+$', t)
    t = tmp()
    if isint(src) and isint(dst):
        a, b = int(src[1:]), int(dst[1:])
        out.append(f'{ind}{t} = {"sext" if a < b else "trunc"} {src} {v} to {dst}')
    elif src == 'ptr' and isint(dst):
        out.append(f'{ind}{t} = ptrtoint ptr {v} to {dst}')
    elif isint(src) and dst == 'ptr':
        out.append(f'{ind}{t} = inttoptr {src} {v} to ptr')
    elif {src, dst} in ({'float', 'i32'}, {'double', 'i64'}):
        out.append(f'{ind}{t} = bitcast {src} {v} to {dst}')
    elif src == 'float' and dst == 'double':
        out.append(f'{ind}{t} = fpext float {v} to double')
    elif src == 'double' and dst == 'float':
        out.append(f'{ind}{t} = fptrunc double {v} to float')
    else:
        return zero(dst)
    return t


# P46 mechanism (port-web): o32 leaves a missing argument in its register. Calls listed here pass
# the CALLER's first parameter (still in a0 in the asm) instead of zero. Add an entry only as a
# TEMPORARY fix, and remove it when the port branch fixes the call in source.
#   P49: the func_15127FEC -> func_1512A390 entry is gone (P47 passes arg0 in game_14FF90.c).
A0_KEEP = set()
DEFINE_A0 = re.compile(r'^define [^@]*(@[\w.$]+)\((ptr|i32)[^%,)]*(%[\w.]+)?')


def normalize(lines, can, tmp, stats):
    out = []
    cur = (None, None, None)
    for l in lines:
        if l.startswith('define '):
            m = DEFINE_A0.match(l)
            cur = (m[1], m[2], m[3]) if m else (None, None, None)
        if l.startswith('declare '):
            m = DECLARE.match(l)
            if m and m[2] in can and not m[2].startswith('@llvm.'):
                r, ps = can[m[2]]
                if '...' not in ps or ps[:-1]:
                    out.append(f'declare {r} {m[2]}({", ".join(ps)})')
                    continue
        elif l.startswith('  ') and 'call ' in l:
            m = CALL.match(l)
            if m and m[5] in can and not m[5].startswith('@llvm.'):
                r, ps = can[m[5]]
                sr = site_ret(m[4])
                sa = site_args(m[6])
                var = ps and ps[-1] == '...'
                fixed = ps[:-1] if var else ps
                if var and sr and (sr != r or [t for t, _ in sa][:len(fixed)] != fixed or '...' not in m[4]):
                    ind, res, new, args = m[1], m[2], [], []
                    for i, p in enumerate(fixed):
                        args.append(f'{p} {conv(ind, sa[i][1], sa[i][0], p, tmp, new) if i < len(sa) else zero(p)}')
                    args += [f'{t} {v}' for t, v in sa[len(fixed):]]
                    call = f'{m[3]}{r} ({", ".join(fixed + ["..."])}) {m[5]}({", ".join(args)})'
                    if res and sr != 'void' and r != 'void':
                        t = tmp(); new.append(f'{ind}{t} = {call}')
                        c = conv(ind, t, r, sr, tmp, new)
                        new.append(f'{ind}{res} = select i1 true, {sr} {c}, {sr} {c}')
                    elif res and sr != 'void':
                        new.append(f'{ind}{call}'); new.append(f'{ind}{res} = select i1 true, {sr} {zero(sr)}, {sr} {zero(sr)}')
                    else:
                        new.append(f'{ind}{tmp()} = {call}' if r != 'void' else f'{ind}{call}')
                    out += new
                    stats['call_fixed_var'] += 1
                    continue
                if not var and sr and (sr != r or [t for t, _ in sa] != ps):
                    ind, res = m[1], m[2]
                    new = []
                    args = []
                    for i, p in enumerate(ps):
                        if i < len(sa):
                            if {sa[i][0], p} == {'float', 'i32'}:
                                stats['fp_int_arg'] += 1
                            args.append(f'{p} {conv(ind, sa[i][1], sa[i][0], p, tmp, new)}')
                        elif i == 0 and (cur[0], m[5]) in A0_KEEP and cur[2] and cur[1] == p:
                            args.append(f'{p} {cur[2]}')
                            stats['a0_keep'] += 1
                        else:
                            args.append(f'{p} {zero(p)}')
                    call = f'{m[3]}{r} {m[5]}({", ".join(args)})'
                    if res and sr != 'void':
                        if r == 'void':
                            new.append(f'{ind}{call}')
                            new.append(f'{ind}{res} = select i1 true, {sr} {zero(sr)}, {sr} {zero(sr)}')
                        else:
                            t = tmp()
                            new.append(f'{ind}{t} = {call}')
                            c = conv(ind, t, r, sr, tmp, new)
                            new.append(f'{ind}{res} = select i1 true, {sr} {c}, {sr} {c}')
                    elif r != 'void':  # an unnamed non-void call would take an implicit %N slot
                        new.append(f'{ind}{tmp()} = {call}')
                    else:
                        new.append(f'{ind}{call}')
                    out += new
                    stats['call_fixed'] += 1
                    continue
        out.append(l)
    return out
