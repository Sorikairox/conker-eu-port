#!/usr/bin/env python3
"""P95: fixes for floatint_scan.py --protos rows (TU prototype int where the callee's C definition takes f32; the
caller passes a word holding float bits). Each edit: (file, line no. at HEAD+floatint_fix, old, new). A line inside a
NON_MATCHING block is edited in place, any other line is duplicated under #ifdef NON_MATCHING / #else / #endif, so the
default build is unchanged by construction. Applied bottom-up per file so line numbers stay valid. Run once."""
import os, re, sys
sys.argv = [sys.argv[0], '--dry']
HERE = os.path.dirname(os.path.abspath(__file__))
exec(open(os.path.join(HERE, 'floatint_fix.py')).read().split('\nfor f, fixes in FIX.items()')[0])

E = [
    ('game_2062D0.c', 904, 's32 func_15131E88(u8 *, s32);', 's32 func_15131E88(u8 *, f32);'),
    ('game_2062D0.c', 912, '*(s32 *)(arg0 + 0xAC)', '*(f32 *)(arg0 + 0xAC)'),
    ('game_eu_106830.c', 269, 'void func_15131EC8(s32, s32, u8 *);', 'void func_15131EC8(s32, f32, u8 *);'),
    ('game_eu_106830.c', 278, '(*(s32 *)((u8 *)temp_a2 + 0xC))', '(*(f32 *)((u8 *)temp_a2 + 0xC))'),
    ('game_eu_1BF960.c', 129, 's32 func_151321F4(u8 *, u8 *, s32,', 's32 func_151321F4(u8 *, u8 *, f32,'),
    ('game_eu_1BF960.c', 132, '(*(s32 *)((u8 *)arg0 + 0xA8))', '(*(f32 *)((u8 *)arg0 + 0xA8))'),
    ('game_eu_15FF50.c', 344, 's32 func_151424F4(s32, s32, s32, s32,', 's32 func_151424F4(s32, f32, f32, f32,'),
    ('game_eu_15FF50.c', 346, '*(s32 *)(arg1 + 0x18), *(s32 *)(arg1 + 0x1C), *(s32 *)(arg1 + 0x20)',
     '*(f32 *)(arg1 + 0x18), *(f32 *)(arg1 + 0x1C), *(f32 *)(arg1 + 0x20)'),
    ('game_eu_15FF50.c', 380, 's32 func_15142838(s32, s32, s32, s32,', 's32 func_15142838(s32, f32, f32, f32,'),
    ('game_eu_15FF50.c', 382, '*(s32 *)(arg1 + 0x18), *(s32 *)(arg1 + 0x1C), *(s32 *)(arg1 + 0x20)',
     '*(f32 *)(arg1 + 0x18), *(f32 *)(arg1 + 0x1C), *(f32 *)(arg1 + 0x20)'),
    ('game_eu_133A70.c', 265, 's32 func_15143794(s16, s16, s32, u8 *);', 's32 func_15143794(s16, s16, f32, u8 *);'),
    ('game_eu_133A70.c', 274, 'func_15143794(arg1, arg2, sp28, arg3);', 'func_15143794(arg1, arg2, *(f32 *)&sp28, arg3);'),
    ('game_eu_133A70.c', 305, 'func_15143794(arg1, arg2, sp1C, sp2C);', 'func_15143794(arg1, arg2, *(f32 *)&sp1C, sp2C);'),
    ('game_eu_ECC80.c', 277, 's32 func_15134108(u8 *, s32, s32, s32, f32, s32);', 's32 func_15134108(u8 *, f32, f32, f32, f32, s32);'),
    ('game_eu_ECC80.c', 457, 'func_15134108(arg0, arg1, arg2, arg3, arg4, arg5)',
     'func_15134108(arg0, *(f32 *)&arg1, *(f32 *)&arg2, *(f32 *)&arg3, arg4, arg5)'),
    ('game_eu_183F10.c', 538, 's32 func_1503F8A8(u8 *, s32, s32, s32, f32, s32);', 's32 func_1503F8A8(u8 *, s32, s32, f32, f32, s32);'),
    ('game_eu_183F10.c', 542, 's32 arg1, s32 arg2, s32 arg3', 's32 arg1, f32 arg2, s32 arg3'),
    ('game_eu_204730.c', 106, 's32 func_15157580(s8 *, s32, s32, s32,', 's32 func_15157580(s8 *, s32, f32, s32,'),
    ('game_eu_204730.c', 198, '0x3F800000', '1.0f'),
    ('game_eu_132370.c', 6, 'void func_15104B60(s32 arg0, s32 arg1, s32 arg2) {', 'void func_15104B60(s32 arg0, s32 arg1, f32 arg2) {'),
]
byfile = {}
for f, ln, old, new in E:
    byfile.setdefault(f, []).append((ln, old, new))
for f, lst in byfile.items():
    p = os.path.join(SRC, f)
    L = open(p).read().split('\n')
    fl = nm_flags(L)
    for ln, old, new in sorted(lst, reverse=True):
        x = L[ln - 1]
        assert old in x, (f, ln, x)
        y = x.replace(old, new) + ' /* P95: f32 (float bits were passed as an int) */'
        if fl[ln - 1] is True:
            L[ln - 1] = y
        else:
            assert fl[ln - 1] == 'both', (f, ln, fl[ln - 1])
            L[ln - 1:ln] = ['#ifdef NON_MATCHING', y, '#else', x, '#endif']
        print('%s:%d %s' % (f, ln, 'NM in place' if fl[ln - 1] is True else 'wrapped'))
    open(p, 'w').write('\n'.join(L))
