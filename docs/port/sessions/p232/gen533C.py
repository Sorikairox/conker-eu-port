#!/usr/bin/env python3
# P232: setups for func_151E533C (mp_match_end_continue). D_80090174 -> 80450000 (menu state, +0x42 = mode row);
# D_800ABA70 rows are ROM data (ROMDATA): row 2 [5]=4 [7]=5, row 8 [5]=2 [7]=4, row 1 [5]=-8 [7]=1, row 3 [5]=-1
# [7]=-1, row 11 [5]=-6 [7]=-2, row 16 [5]=5 [7]=-1, row 0 [5]=0 [7]=0. D_800E0EF0..3 placings, D_800E0EB6 quit flag,
# D_80090160 flags. Callees: func_1501C710 1501C710 (arguments compared), func_151E5D28 151E5D28.
def setup(name, row, pl=(2, 3, 4, 5), eb6=0, flags=0xFFFF):
    pk = '80090174=80450000,80450040=0000%02X00,800E0EF0=%02X%02X%02X%02X,800E0EB4=0000%02X00,80090160=%04X0000' % (
        row & 0xFF, pl[0] & 0xFF, pl[1] & 0xFF, pl[2] & 0xFF, pl[3] & 0xFF, eb6, flags)
    print('%s ! ! %s ! ! ! ! ! !' % (name, pk))
for r in (2, 8, 1, 3, 11, 16, 0):
    setup('r%d_none' % r, r)
    setup('r%d_one' % r, r, (1, 2, 3, 4))
    setup('r%d_two' % r, r, (1, 1, 3, 4))
    setup('r%d_two_b' % r, r, (2, 3, 1, 1))
    setup('r%d_four' % r, r, (1, 1, 1, 1))
setup('r1_tie', 1, (1, 1, 1, 0))
setup('r11_quit', 11, eb6=1)
setup('r11_quit_tie', 11, (1, 1, 0, 0), eb6=0x80)
setup('r3_quit', 3, eb6=1)
setup('p0_only', 2, (1, 0, 0, 0))
setup('p1_only', 2, (0, 1, 0, 0))
setup('p2_only', 2, (0, 0, 1, 0))
setup('p3_only', 2, (0, 0, 0, 1))
setup('p01', 2, (1, 1, 0, 0))
setup('p12', 2, (0, 1, 1, 0))
setup('p23', 2, (0, 0, 1, 1))
setup('p03', 2, (1, 0, 0, 1))
setup('p13', 16, (0, 1, 0, 1))
setup('p02', 16, (1, 0, 1, 0))
setup('neg', 2, (0xFF, 0x81, 1, 0x101))
