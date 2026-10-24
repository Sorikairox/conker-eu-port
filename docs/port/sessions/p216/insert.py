#!/usr/bin/env python3
# P216 copy of p213/insert.py with the P216 jobs: wraps each converted function's GLOBAL_ASM pragma in an NM block holding the draft (one block per function).
import re, sys
D = 'docs/port/sessions/p216/'
JOBS = [('game_eu_201240', 'func_151D5DA8', '5da8'), ('game_eu_90F50', 'func_15065E18', '5e18')]
only = set(sys.argv[1:])
for f, fn, tag in JOBS:
    if only and tag not in only: continue
    p = 'conker/src_eu/%s.c' % f
    s = open(p).read()
    body = open(D + 'd_%s.c' % tag).read().rstrip('\n')
    prag = '#pragma GLOBAL_ASM("asm/nonmatchings/%s/%s.s")' % (f, fn)
    assert s.count(prag) == 1, (fn, s.count(prag))
    i = s.index(prag)
    assert '#ifdef NON_MATCHING' not in s[max(0, i - 40):i] and not s[:i].rstrip().endswith('#else'), fn
    s = s.replace(prag, '#ifdef NON_MATCHING\n%s\n#else\n%s\n#endif' % (body, prag))
    open(p, 'w').write(s)
    print('ok', fn)
