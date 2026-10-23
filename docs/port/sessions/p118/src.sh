#!/bin/bash
# src.sh FUNC [PATTERN]: NM C body of FUNC (lines matching PATTERN)
cd /Users/sorikairo/conker-wt/web
python3 - "$1" "${2:-.}" <<'PY'
import sys, re, glob
f, pat = sys.argv[1], sys.argv[2]
for p in glob.glob('conker/src_eu/**/*.c', recursive=True):
    t = open(p, errors='replace').read()
    for m in re.finditer(r'^[A-Za-z][^\n;]*\b%s\s*\([^;]*?\)\s*\{' % f, t, re.M):
        e = t.find('\n}', m.end()); body = t[m.start():e]
        if 'GLOBAL_ASM' in body: continue
        ln0 = t.count('\n', 0, m.start()) + 1
        print('==', p, ln0)
        for i, l in enumerate(body.split('\n')):
            if re.search(pat, l): print(ln0 + i, l)
PY
