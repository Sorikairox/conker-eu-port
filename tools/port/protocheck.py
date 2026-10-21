#!/usr/bin/env python3
"""protocheck.py [FUNC...]: prototype consistency of the NON_MATCHING bodies (wasm needs one signature per function).

For every NON_MATCHING body (or the given ones) it checks
  1. its definition against every other prototype of it in src_eu / include (and the //HOIST block);
  2. every prototype the body block declares for a callee (draft-local `T f(...);`, hoisted lines)
     against the callee's C definition (matching or NON_MATCHING) or, failing that, its header prototype;
  3. calls in the body to functions with no visible prototype at all (implicit int f()).
Signatures are compared by ABI class: return (void / int / f32 / f64 / i64) and the parameter list
(int-or-pointer / f32 / f64 / i64; `...` and K&R `()` match anything).  Prints one line per problem;
exit 1 if any.  Run from the repo root.
"""
import sys as _pgs, os as _pgo; _pgs.path.insert(0, _pgo.path.dirname(_pgo.path.abspath(__file__))); import portguard  # wrong-checkout guard (P7)
import sys, os, re, glob

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SIG = re.compile(r'^(?!\s*(?:return|else|if|while|for|switch)\b)[ \t]*((?:extern[ \t]+|static[ \t]+)?[A-Za-z_][\w \t\*]*?)\b(\w+)[ \t]*\(([^;{}\n]*)\)[ \t]*([;{])', re.M)


def cls(t):
    t = re.sub(r'\b(extern|static|const|volatile|register|inline|struct|union|enum)\b', '', t).strip()
    if '*' in t or '[' in t or '(' in t: return 'i'
    if re.search(r'\b(void)\b', t): return 'v'
    if re.search(r'\b(f32|float)\b', t): return 'f'
    if re.search(r'\b(f64|double)\b', t): return 'd'
    if re.search(r'\b(s64|u64|long\s+long)\b', t): return 'l'
    return 'i'


def sig(ret, params):
    ps = params.strip()
    if ps == '': return (cls(ret), None)
    if ps == 'void': return (cls(ret), ())
    out = []
    for p in re.split(r',(?![^()]*\))', ps):
        if p.strip() == '...': out.append('...'); break
        out.append(cls(re.sub(r'\b\w+\s*$', '', p) if re.search(r'[\w\]]\s*$', p) and len(p.split()) > 1 else p))
    return (cls(ret), tuple(out))


def compat(a, b):
    if a[0] != b[0]: return False
    if a[1] is None or b[1] is None: return True
    if '...' in a[1] or '...' in b[1]:
        n = min(a[1].index('...') if '...' in a[1] else 99, b[1].index('...') if '...' in b[1] else 99)
        return a[1][:n] == b[1][:n]
    return a[1] == b[1]


def nm_blocks(src):
    pat = re.compile(r'^#ifdef NON_MATCHING\n((?:(?!^#endif).*\n)*?)#else\n#pragma GLOBAL_ASM\("[^"]*/(\w+)\.s"\)\n#endif', re.M)
    return [(m.group(2), m.group(1)) for m in pat.finditer(src)]


def nm_view(src):
    """the text as the NON_MATCHING build sees it (non-nested #ifdef/#ifndef NON_MATCHING [#else] #endif)"""
    out, mode = [], None   # mode: None outside, (keep_if, in_else) inside
    for ln in src.split('\n'):
        t = ln.strip()
        if mode is None and (t.startswith('#ifdef NON_MATCHING') or t.startswith('#ifndef NON_MATCHING')):
            mode = [t.startswith('#ifdef'), False]; continue
        if mode is not None:
            if t.startswith('#if'): mode = None; out.append(ln); continue   # nested: give up on this block
            if t == '#else': mode[1] = True; continue
            if t.startswith('#endif'): mode = None; continue
            if mode[0] != mode[1]: out.append(ln)
            continue
        out.append(ln)
    return '\n'.join(out)


def main():
    want = set(sys.argv[1:])
    files = glob.glob(os.path.join(ROOT, 'conker/src_eu/**/*.c'), recursive=True)
    hdrs = glob.glob(os.path.join(ROOT, 'conker/include/**/*.h'), recursive=True) + glob.glob(os.path.join(ROOT, 'conker/src_eu/**/*.h'), recursive=True)
    defs, protos, blocks = {}, {}, []
    for p in files + hdrs:
        s = open(p, errors='replace').read()
        nmb = nm_blocks(s) if p.endswith('.c') else []
        for f, b in nmb: blocks.append((f, b, p))
        if p.endswith('.c'): s = nm_view(s)   # the NON_MATCHING side of every #ifdef/#ifndef NON_MATCHING
        # strip GLOBAL_ASM-only: definitions anywhere (matching C and NON_MATCHING) count
        for m in SIG.finditer(s):
            ret, name, ps, end = m.groups()
            if name in ('if', 'while', 'for', 'switch', 'return', 'sizeof'): continue
            sg = sig(ret, ps)
            (defs if end == '{' else protos).setdefault(name, []).append((sg, os.path.relpath(p, ROOT)))
    bad = 0
    for f, body, p in blocks:
        if want and f not in want: continue
        rel = os.path.relpath(p, ROOT)
        d = [x for x in defs.get(f, []) if x[1] == rel]
        if d:
            for sg, where in protos.get(f, []):
                if not compat(d[0][0], sg):
                    print('%s: definition %s vs prototype %s in %s' % (f, d[0][0], sg, where)); bad += 1
        bdef = re.search(r'\b%s\s*\([^;{]*\)\s*\{' % f, body)
        head = body[:bdef.start()] if bdef else body
        for m in SIG.finditer(head):
            ret, name, ps, end = m.groups()
            if end != ';' or name == f: continue
            sg = sig(ret, ps)
            ref = defs.get(name) or protos.get(name)
            if ref and not any(compat(sg, r[0]) for r in ref):
                print('%s: declares %s %s, but %s is %s (%s)' % (f, name, sg, name, ref[0][0], ref[0][1])); bad += 1
        inner = body[bdef.end():] if bdef else ''
        for name in sorted(set(re.findall(r'\b((?:func_[0-9A-F]{8})|[a-z]\w*)\s*\(', inner))):
            if name in ('if', 'while', 'for', 'switch', 'return', 'sizeof') or name in defs or name in protos: continue
            print('%s: calls %s with no prototype anywhere (implicit int)' % (f, name)); bad += 1
    print('# %d NON_MATCHING bodies checked, %d problems' % (len([b for b in blocks if not want or b[0] in want]), bad))
    return 1 if bad else 0


if __name__ == '__main__':
    sys.exit(main())
