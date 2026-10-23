#!/usr/bin/env python3
# P124: put the handler-C chain candidates into their NM blocks (run from the worktree root)
import re
C = 'docs/port/sessions/p124/c/%s.c'
def put(path, fn, pre=''):
    s = open(path).read()
    tag = '#pragma GLOBAL_ASM("asm/nonmatchings/%s/%s.s")\n' % (path.split('/')[-1][:-2], fn)
    assert s.count(tag) == 1, (path, fn)
    i = s.index(tag)
    if s[max(0, i - 6):i] == '#else\n':
        raise SystemExit('%s already NM' % fn)
    body = pre + open(C % fn).read()
    s = s[:i] + '#ifdef NON_MATCHING\n' + body + '#else\n' + tag + '#endif\n' + s[i + len(tag):]
    open(path, 'w').write(s)
put('conker/src_eu/game_eu_51190.c', 'func_15023988')
put('conker/src_eu/game_eu_51190.c', 'func_15023EC4')
put('conker/src_eu/game_eu_51190.c', 'func_15029EA8')
put('conker/src_eu/init_EB00.c', 'func_1000FA64')
put('conker/src_eu/game_eu_1B6590.c', 'func_15188D80')
print('ok')
