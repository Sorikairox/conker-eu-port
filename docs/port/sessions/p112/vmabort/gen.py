#!/usr/bin/env python3
"""P112: build a host test of the VM abort path: the C VM func_150ADFD0 + native func_150AE60C + func_150AE760 +
func_1509FD30, extracted from the NM blocks. s32 is `long` so pointers fit in the VM's s32 slots (semantics only)."""
import re, sys
R = sys.argv[1]
def ext(path, f):
    src = open(path).read()
    m = re.search(r'^[A-Za-z_][^\n;#/]*\b%s\s*\([^;{]*?\)\s*\{' % f, src, re.M); i = m.end() - 1; d = 0
    while True:
        d += {'{': 1, '}': -1}.get(src[i], 0); i += 1
        if d == 0: break
    return src[m.start():i]
db = R + '/conker/src_eu/game_eu_DB7E0.c'; cd = R + '/conker/src_eu/game_eu_CD540.c'
out = [open(sys.argv[2]).read()]
out += [ext(db, 'func_150ADFD0'), ext(db, 'func_150AE60C'), ext(db, 'func_150AE760'), ext(cd, 'func_1509FD30')]
out.append(open(sys.argv[3]).read())
open(sys.argv[4], 'w').write('\n'.join(out))
