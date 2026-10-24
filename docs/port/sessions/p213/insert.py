#!/usr/bin/env python3
# P213 copy of p210/insert.py with the P213 jobs: wraps each converted function's GLOBAL_ASM pragma in an NM block holding the draft (one block per function).
import re, sys
D = 'docs/port/sessions/p213/'
JOBS = [('game_83300', 'func_150562FC', '62fc'), ('game_83300', 'func_1505E874', 'e874'),
        ('game_eu_1BAF40', 'func_15190A2C', '0a2c'), ('game_eu_F6060', 'func_150CA0DC', 'a0dc')]
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
