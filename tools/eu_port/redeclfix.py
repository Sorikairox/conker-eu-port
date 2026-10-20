#!/usr/bin/env python3
"""redeclfix.py <func> <draft.c> <out.c> [maxiter]
Compile-loop on a CERR draft: while the first error is "redeclaration of 'X'", delete the draft's own
declaration lines for X (prototype / extern before the function definition) so the file's / header's
declaration wins. Prints the final result line and the remaining first error (s56)."""
import sys, os, re, subprocess
func, src, out = sys.argv[1:4]
maxit = int(sys.argv[4]) if len(sys.argv) > 4 else 8
root = os.environ.get('CONKER_ROOT', os.path.expanduser('~/conker'))
lines = open(src).read().split('\n')
def defline(ls):
    for i, l in enumerate(ls):
        if re.match(r'^[A-Za-z_][\w \*]*\b%s\(' % re.escape(func), l) and not l.rstrip().endswith(';'):
            return i
    return len(ls)
res = ''
for it in range(maxit):
    open(out, 'w').write('\n'.join(lines))
    r = subprocess.run([root + '/tools/eu_port/repair_try.sh', func, out], capture_output=True, text=True, env=os.environ)
    txt = r.stdout
    res = txt.split('\n')[0]
    m = re.search(r"redeclaration of '(\w+)'", txt)
    if not res.split()[-1:] == ['CERR'] or not m:
        break
    x = m.group(1)
    d = defline(lines)
    new = [l for i, l in enumerate(lines) if not (i < d and re.search(r'\b%s\b' % re.escape(x), l) and l.rstrip().endswith(';'))]
    if len(new) == len(lines):
        # nothing of ours to delete: the callee is defined later in the file -> add its real prototype
        pr = None
        import glob
        for fn in glob.glob(root + '/conker/src_eu/*.c'):
            mm = re.search(r'^([A-Za-z_][\w \*]*?\b%s\([^)]*\))\s*\{' % re.escape(x), open(fn).read(), re.M)
            if mm: pr = mm.group(1) + ';'; break
        if not pr or pr in lines:
            break
        lines = [pr] + lines
        continue
    lines = new
open(out, 'w').write('\n'.join(lines))
print(res)
print('\n'.join(txt.split('\n')[1:3])[:400])
