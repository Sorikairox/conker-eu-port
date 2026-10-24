#!/usr/bin/env python3
"""progress_nm.py [progress.csv]: C coverage including NON_MATCHING bodies, per segment.

  matched   C in the default (byte-identical) build      (progress.csv language=c)
  nm        asm in the default build, but has a NON_MATCHING C body (#ifdef NON_MATCHING ... #else GLOBAL_ASM)
  asm-only  still only GLOBAL_ASM
progress.csv comes from `make VERSION=eu progress` (verify_all.sh regenerates it in conker/).
Run from the repo root or conker/ (host or container).  --list prints the asm-only functions (name, insns, file).
"""
import sys as _pgs, os as _pgo; _pgs.path.insert(0, _pgo.path.dirname(_pgo.path.abspath(__file__))); import portguard  # wrong-checkout guard (P7)
import sys, os, re, csv, glob, collections

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
C = os.path.join(ROOT, 'conker')


_DIR = re.compile(r'^\s*#\s*(ifdef|ifndef|if|elif|else|endif)\b(.*)$')
_PRAGMA = re.compile(r'^\s*#pragma GLOBAL_ASM\("[^"]*/(\w+)\.s"\)')


def nm_funcs_scan(text):
    """P234: every GLOBAL_ASM pragma that the NON_MATCHING build leaves out (its code is C there: an NM body, or a
    private entry folded into another function's NM C, e.g. func_1000661C.. in func_1000654C's inflate, the
    func_150A5480 loop pieces in D2DB0, func_150A661C in D3880). A conditional stack: each level says whether its current branch is live
    with NON_MATCHING defined (None = unrelated condition, inherits). Before P234 one regex required `#endif` right
    after the pragma: func_150E394C (game_eu_110DB0) keeps `extern s32 func_150E394C;` in the #else part and was
    counted asm-only although its NM body exists (P190). --old = the old regex."""
    lines = text.split('\n')
    stack = []   # (nm_live_in_branch: True / False / None)
    excluded = []
    for ln in lines:
        m = _DIR.match(ln)
        if m:
            k, rest = m.group(1), re.sub(r'/\*.*?\*/|//.*', '', m.group(2)).strip()
            if k == 'ifdef': stack.append(True if rest == 'NON_MATCHING' else None)
            elif k == 'ifndef': stack.append(False if rest == 'NON_MATCHING' else None)
            elif k == 'if':
                stack.append(True if re.fullmatch(r'defined\s*\(?\s*NON_MATCHING\s*\)?', rest) else
                             False if re.fullmatch(r'!\s*defined\s*\(?\s*NON_MATCHING\s*\)?', rest) else None)
            elif k == 'elif':
                if stack: stack[-1] = None
            elif k == 'else':
                if stack and stack[-1] is not None: stack[-1] = not stack[-1]
            elif k == 'endif':
                if stack: stack.pop()
            continue
        p = _PRAGMA.match(ln)
        if p and any(s is False for s in stack): excluded.append(p.group(1))
    return excluded


def nm_funcs():
    out = {}
    if '--old' not in sys.argv:
        for p in glob.glob(os.path.join(C, 'src_eu/**/*.c'), recursive=True):
            for f in nm_funcs_scan(open(p).read()): out[f] = os.path.relpath(p, C)
        return out
    pat = re.compile(r'^#ifdef NON_MATCHING\n(?:(?!^#endif).*\n)*?#else\n#pragma GLOBAL_ASM\("[^"]*/(\w+)\.s"\)\n#endif', re.M)
    for p in glob.glob(os.path.join(C, 'src_eu/**/*.c'), recursive=True):
        for m in pat.finditer(open(p).read()):
            out[m.group(1)] = os.path.relpath(p, C)
    return out


def main():
    a = [x for x in sys.argv[1:] if not x.startswith('--')]
    path = a[0] if a else os.path.join(C, 'progress.csv')
    rows = [r for r in csv.DictReader(open(path)) if r['length'] != 'length']
    nm = nm_funcs()
    t = collections.OrderedDict()
    asm_only = []
    for r in rows:
        s = t.setdefault(r['section'], dict(n=0, c=0, nm=0, asm=0, b=0, bc=0, bnm=0))
        n = int(r['length']); s['n'] += 1; s['b'] += n
        if r['language'] == 'c': s['c'] += 1; s['bc'] += n
        elif r['function'] in nm: s['nm'] += 1; s['bnm'] += n
        else: s['asm'] += 1; asm_only.append((r['function'], n // 4, r['filename']))
    tot = dict(n=0, c=0, nm=0, asm=0, b=0, bc=0, bnm=0)
    for s in t.values():
        for k in tot: tot[k] += s[k]
    print('%-9s %6s %8s %6s %8s %9s   %s' % ('segment', 'funcs', 'matched', 'nm', 'asm-only', 'C total', 'C bytes'))
    for name, s in list(t.items()) + [('total', tot)]:
        print('%-9s %6d %8d %6d %8d %5d %4.1f%%   %d/%d (%.1f%%)' % (
            name, s['n'], s['c'], s['nm'], s['asm'], s['c'] + s['nm'], 100.0 * (s['c'] + s['nm']) / max(1, s['n']),
            s['bc'] + s['bnm'], s['b'], 100.0 * (s['bc'] + s['bnm']) / max(1, s['b'])))
    missing = [f for f in nm if f not in {r['function'] for r in rows}]
    if missing: print('note: %d NON_MATCHING functions not in progress.csv (renamed?): %s' % (len(missing), ' '.join(missing[:5])))
    small = sum(1 for f in asm_only if f[1] < 60)
    print('asm-only under 60 insns: %d' % small)
    if '--list' in sys.argv:
        for f in sorted(asm_only, key=lambda x: x[1]): print('%s\t%d\t%s' % f)


if __name__ == '__main__':
    main()
