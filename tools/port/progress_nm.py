#!/usr/bin/env python3
"""progress_nm.py [progress.csv]: C coverage including NON_MATCHING bodies, per segment.

  matched   C in the default (byte-identical) build      (progress.csv language=c)
  nm        asm in the default build, but has a NON_MATCHING C body (#ifdef NON_MATCHING ... #else GLOBAL_ASM)
  asm-only  still only GLOBAL_ASM
progress.csv comes from `make VERSION=eu progress` (verify_all.sh regenerates it in conker/).
Run from the repo root or conker/ (host or container).  --list prints the asm-only functions (name, insns, file).
P279: functions of raw asm segments (asm/D5E90.s) count as nm when the Makefile lists them in NM_ASM_C_FUNCS_X or
tools/port/nm_folded.tsv lists them (private entries folded into another function's NM C; kind asm2c = register-level
translation, reported separately). tools/port/platform_replaced.tsv rows (privileged / OS / padding code the port's
platform layer replaces, one reason per row) count as done, in a `plat` column (P281, user decision 2026-10-25: this
is the default; --strict = the old count without them; --platform is accepted and does nothing).
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
    after the pragma: zap_sound_release_cb (game_eu_110DB0) keeps `extern s32 zap_sound_release_cb;` in the #else part and was
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


def tsv_rows(name):
    p = os.path.join(ROOT, 'tools/port', name)
    if not os.path.exists(p): return []
    rows = [l.rstrip('\n').split('\t') for l in open(p) if l.strip() and not l.startswith('#')]
    return [dict(zip(rows[0], r)) for r in rows[1:]]


def nm_asm_funcs():
    """P279: NM_ASM_C_FUNCS_X names from the Makefile + nm_folded.tsv; returns {func: kind}"""
    out = {}
    mk = os.path.join(C, 'Makefile')
    if os.path.exists(mk):
        for m in re.finditer(r'^NM_ASM_C_FUNCS_\w+\s*[:+]?=\s*(.*)$', open(mk).read(), re.M):
            for f in m.group(1).split(): out[f] = 'nm_asm'
    for r in tsv_rows('nm_folded.tsv'): out[r['func']] = r['kind']
    return out


def main():
    a = [x for x in sys.argv[1:] if not x.startswith('--')]
    path = a[0] if a else os.path.join(C, 'progress.csv')
    rows = [r for r in csv.DictReader(open(path)) if r['length'] != 'length']
    nm = nm_funcs()
    nma = nm_asm_funcs()
    for f in nma: nm.setdefault(f, 'asm/D5E90.s')
    plat = {r['func'] for r in tsv_rows('platform_replaced.tsv')} if '--strict' not in sys.argv else set()
    t = collections.OrderedDict()
    asm_only = []
    for r in rows:
        s = t.setdefault(r['section'], dict(n=0, c=0, nm=0, asm=0, b=0, bc=0, bnm=0, pl=0, bpl=0))
        n = int(r['length']); s['n'] += 1; s['b'] += n
        if r['language'] == 'c': s['c'] += 1; s['bc'] += n
        elif r['function'] in nm: s['nm'] += 1; s['bnm'] += n
        elif r['function'] in plat: s['pl'] += 1; s['bpl'] += n
        else: s['asm'] += 1; asm_only.append((r['function'], n // 4, r['filename']))
    tot = dict(n=0, c=0, nm=0, asm=0, b=0, bc=0, bnm=0, pl=0, bpl=0)
    for s in t.values():
        for k in tot: tot[k] += s[k]
    if plat:
        print('%-9s %6s %8s %6s %6s %8s %9s   %s' % ('segment', 'funcs', 'matched', 'nm', 'plat', 'asm-only', 'done', 'bytes'))
        for name, s in list(t.items()) + [('total', tot)]:
            d = s['c'] + s['nm'] + s['pl']; db = s['bc'] + s['bnm'] + s['bpl']
            print('%-9s %6d %8d %6d %6d %8d %5d %4.1f%%   %d/%d (%.1f%%)' % (
                name, s['n'], s['c'], s['nm'], s['pl'], s['asm'], d, 100.0 * d / max(1, s['n']), db, s['b'], 100.0 * db / max(1, s['b'])))
    else:
        print('%-9s %6s %8s %6s %8s %9s   %s' % ('segment', 'funcs', 'matched', 'nm', 'asm-only', 'C total', 'C bytes'))
        for name, s in list(t.items()) + [('total', tot)]:
            print('%-9s %6d %8d %6d %8d %5d %4.1f%%   %d/%d (%.1f%%)' % (
                name, s['n'], s['c'], s['nm'], s['asm'], s['c'] + s['nm'], 100.0 * (s['c'] + s['nm']) / max(1, s['n']),
                s['bc'] + s['bnm'], s['b'], 100.0 * (s['bc'] + s['bnm']) / max(1, s['b'])))
    if plat: print('plat %d: asm-only functions counted as done because the port replaces them (tools/port/platform_replaced.tsv; --strict = without)' % tot['pl'])
    a2c = [f for f, k in nma.items() if k == 'asm2c']
    if a2c: print('nm includes %d asm2c register-level entries (nm_folded.tsv kind asm2c, still to be rewritten readably)' % len(a2c))
    missing = [f for f in nm if f not in {r['function'] for r in rows}]
    if missing: print('note: %d NON_MATCHING functions not in progress.csv (renamed?): %s' % (len(missing), ' '.join(missing[:5])))
    small = sum(1 for f in asm_only if f[1] < 60)
    print('asm-only under 60 insns: %d' % small)
    if '--list' in sys.argv:
        for f in sorted(asm_only, key=lambda x: x[1]): print('%s\t%d\t%s' % f)


if __name__ == '__main__':
    main()
