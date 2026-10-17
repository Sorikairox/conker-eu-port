#!/usr/bin/env python3
"""usage: switchinline.py indir outdir -- m2c writes `temp = expr; switch (temp) {`; IDO keeps the
switch value in its own temp register only when the expression is written in the switch
(`switch (expr)`), which is what the ROM usually has. Writes only the drafts that change
(the temp must not be used anywhere else; its declaration is dropped)."""
import os, re, sys, glob

ind, outd = sys.argv[1], sys.argv[2]
os.makedirs(outd, exist_ok=True)
n = 0
for p in glob.glob(os.path.join(ind, 'func_*.c')):
    c = open(p).read()
    orig = c
    for m in list(re.finditer(r'\n(\s*)(\w+) = ([^;\n]+);\n\s*switch \(\2\) \{', c))[::-1]:
        v = m.group(2)
        rest = c[:m.start()] + c[m.end():]
        if len(re.findall(r'\b%s\b' % v, rest)) != 1:  # only the declaration may remain
            continue
        c = c[:m.start()] + '\n%sswitch (%s) {' % (m.group(1), m.group(3)) + c[m.end():]
        c = re.sub(r'\n\s*[\w ]+\*?\s*\b%s;\n' % v, '\n', c, count=1)
    if c != orig:
        open(os.path.join(outd, os.path.basename(p)), 'w').write(c)
        n += 1
print(n)
