#!/usr/bin/env python3
# P210: wraps each converted function's GLOBAL_ASM pragma in an NM block holding the draft (one block per function).
import re, sys
D = 'docs/port/sessions/p210/'
JOBS = [('game_83300', 'func_1505B9C4', 'b9c4'), ('game_83300', 'func_1505C1E4', 'c1e4'),
        ('game_83300', 'func_150585F0', '85f0'), ('game_A28B0', 'func_15076D3C', '6d3c'), ('game_A28B0', 'func_15079FBC', '9fbc'), ('game_A28B0', 'func_1507602C', '602c'),
        ('game_A28B0', 'func_150768DC', '68dc'), ('game_A28B0', 'func_15078544', '8544'), ('game_A28B0', 'func_1507AA48', 'aa48'),
        ('game_A28B0', 'func_15079B30', '9b30'), ('game_1944C0', 'func_15167C58', '7c58'), ('game_1944C0', 'func_15167E0C', '7e0c')]
only = set(sys.argv[1:])
for f, fn, tag in JOBS:
    if only and tag not in only: continue
    p = 'conker/src_eu/%s.c' % f
    s = open(p).read()
    body = open(D + 'd_%s.c' % tag).read().rstrip('\n')
    if tag == 'c1e4':   # HitDesc is defined in func_1505B9C4's block (earlier in the file)
        body = re.sub(r'/\* P210: one hit descriptor.*?\} HitDesc;\n\n', '/* HitDesc: see func_1505B9C4 */\n', body, flags=re.S)
    prag = '#pragma GLOBAL_ASM("asm/nonmatchings/%s/%s.s")' % (f, fn)
    assert s.count(prag) == 1, (fn, s.count(prag))
    i = s.index(prag)
    assert '#ifdef NON_MATCHING' not in s[max(0, i - 40):i] and not s[:i].rstrip().endswith('#else'), fn
    s = s.replace(prag, '#ifdef NON_MATCHING\n%s\n#else\n%s\n#endif' % (body, prag))
    open(p, 'w').write(s)
    print('ok', fn)
