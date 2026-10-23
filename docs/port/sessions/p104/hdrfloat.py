#!/usr/bin/env python3
"""P104: NM bodies that call a function whose float-parameter prototype is only in include/**.h (no declaration in
the .c file). Before P100, difftest compared no FP argument registers for such callees. Also writes, per body, the
whole NM block (prototypes + body) to OUT/<func>.c as a difftest candidate.
usage: hdrfloat.py [OUTDIR]   (run from conker/)"""
import re, glob, sys, os
FL = re.compile(r'\b(f32|f64|float|double)\b(?!\s*\*)')
def nocomment(t): return re.sub(r'/\*.*?\*/', ' ', re.sub(r'//[^\n]*', '', t), flags=re.S)
hdr = {}
for f in glob.glob('include/**/*.h', recursive=True):
    t = nocomment(open(f, errors='replace').read())
    for m in re.finditer(r'(?m)^\s*(?:extern\s+)?[A-Za-z_][\w \*]*?\b(\w+)\s*\(([^;{}()]*)\)\s*;', t):
        ps = m.group(2)
        if any(FL.search(p) and '*' not in p and '(' not in p for p in ps.split(',')):
            hdr.setdefault(m.group(1), (f, ps.strip()))
out = sys.argv[1] if len(sys.argv) > 1 else None
rows = []
for f in sorted(glob.glob('src_eu/*.c')):
    src = open(f, errors='replace').read(); nc = nocomment(src)
    for m in re.finditer(r'#ifdef NON_MATCHING\n(.*?)\n#(else|endif)', src, re.S):
        blk = m.group(1)
        bnc = nocomment(blk)
        defs = re.findall(r'(?m)^[A-Za-z_][\w \*]*?\b(func_\w+|\w+)\s*\([^;{]*\)\s*\{', bnc)
        if not defs: continue
        calls = set(re.findall(r'\b(\w+)\s*\(', bnc)) & set(hdr)
        hits = []
        for c in sorted(calls):
            if c in defs: continue
            decl = re.search(r'(?m)^\s*(?:extern\s+)?(?:static\s+)?[A-Za-z_][\w \*]*?[\s\*]%s\s*\([^;{}]*\)\s*;' % re.escape(c), nc)
            if not decl: hits.append(c)
        if hits:
            fn = defs[-1]
            rows.append((fn, os.path.basename(f), ','.join(hits)))
            if out:
                os.makedirs(out, exist_ok=True); open(os.path.join(out, fn + '.c'), 'w').write(blk + '\n')
for r in rows: print('\t'.join(r))
print('# %d bodies, %d header float prototypes' % (len(rows), len(hdr)), file=sys.stderr)
