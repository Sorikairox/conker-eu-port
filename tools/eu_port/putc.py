#!/usr/bin/env python3
# usage: putc.py <func> <draft.c> [--dry]  replace `#pragma GLOBAL_ASM(.../<func>.s)` in conker/src_eu with the draft text (s69).
import sys, os, re, glob
f, d = sys.argv[1], sys.argv[2]
root = os.environ.get('CONKER_ROOT', os.path.expanduser('~/conker'))
pat = re.compile(r'#pragma GLOBAL_ASM\("[^"]*/%s\.s"\)\n' % re.escape(f))
for p in glob.glob(root + '/conker/src_eu/**/*.c', recursive=True):
    s = open(p).read()
    if pat.search(s):
        body = open(d).read().rstrip('\n') + '\n'
        if '--dry' not in sys.argv:
            open(p, 'w').write(pat.sub(lambda m: body, s, count=1))
        print(f, '->', os.path.relpath(p, root)); break
else:
    print(f, 'not found'); sys.exit(1)
