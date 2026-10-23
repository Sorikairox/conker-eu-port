#!/usr/bin/env python3
"""P117: setups for func_151DF6A4 (title_press_start_page). jal keys: func_15083E90 150842F8, func_150ADA20 150ADF00,
func_151F2CDC 151F349C, func_1000EA94 1000ED84. Objects D_800CC2D0 (EU 800CC6F0, 0x32C each)."""
S = []
OBJ = 0x800CC6F0 + 3 * 0x32C
def add(n, pk, ret):
    S.append('%s ! ! %s ! %s ! ! ! ! !' % (n, ','.join(pk), ','.join(ret)))
def base(ec5=0x80, ec6=0xFF, a4=0, a8=0, d4=0, inp=0, f188='00000000', ff=0, x=5, y=5, sx=5, sy=5, pr=0, e9d=0, step=1):
    return ['80090174=80480000', '80480020=%04X0000' % inp, '800E0EC4=C0%02X%02X33' % (ec5, ec6), '800902A4=%02X000000' % a4,
            '800902A8=%02X000000' % a8, '800901D4=%02X000000' % d4, '80090188=' + f188, '800BEE04=%08X' % step,
            '%08X=0000%02X00' % ((OBJ + 0x1FC), ff), '800E1024=000000%02X' % (x & 0xFF), '800E1028=%02X00%02X%02X' % (y & 0xFF, sx & 0xFF, sy & 0xFF),
            '800BED50=%04X0000' % pr, '800EA130=%08X' % e9d]
R = lambda obj=OBJ, rnd=5, f2=1: ['150842F8=%08X' % obj, '150ADF00=%08X' % rnd, '151F349C=%08X' % f2, '1000ED84=00000007']
# fade-out paths
for ec6 in (0, 1, 2, 0xFF, 3):
    for ec5 in (0x10, 0x20, 0x21, 0xF0):
        for a4 in (0, 1):
            for rnd in (4, 5, 7):
                add('fo_%X_%X_%d_%d' % (ec6, ec5, a4, rnd), base(ec5=ec5, ec6=ec6, a4=a4, inp=0x3F), R(rnd=rnd))
    add('fo_null_%X' % ec6, base(ec5=0x10, ec6=ec6, inp=0x30), R(obj=0))
    add('fo_a8_%X' % ec6, base(ec5=0x10, ec6=ec6, a8=1, inp=0x30), R())
add('fo_step', base(ec5=0x90, ec6=1, step=5), R())
for ec5 in (0, 0xDF, 0xE0, 0xFF):
    add('fi_%X' % ec5, base(ec5=ec5), R())
# plain page
for d4 in (9, 0x15, 0x19, 0):
    for inp in (0, 4, 8, 0x10, 0x20, 0x30, 0x3C):
        for f in ('00000000', '3F800000'):
            add('pl_%X_%X_%s' % (d4, inp, f[:2]), base(d4=d4, inp=inp, f188=f), R())
for f2, ff in ((1, 0), (1, 1), (0, 1), (2, 0)):
    add('f2_%d_%d' % (f2, ff), base(ff=ff), R(f2=f2))
    add('f2n_%d_%d' % (f2, ff), base(ff=ff), R(obj=0, f2=f2))
# info screen
for e9 in (0, 0x400000, 0x800000, 0xC00000, 0xFF3FFFFF):
    for inp in (0, 0x20, 0x10):
        add('info_%X_%X' % (e9, inp), base(a4=1, e9d=e9, inp=inp), R())
# screen position
for (x, y, sx, sy) in ((0, 0, 0, 0), (5, 5, 5, 5), (0x20, 0x10, 0x10, 0x10), (0x1F, 0xF, 0xF, 0xF), (1, 1, 1, 1), (-3, -3, 0x7F, -1)):
    for inp in (0, 1, 2, 4, 8, 0xF, 0x20):
        for pr in (0, 1, 2, 4, 8, 0xF):
            if inp and pr: continue
            add('sp_%d_%d_%X_%X' % (x, sx, inp, pr), base(a8=1, x=x, y=y, sx=sx, sy=sy, inp=inp, pr=pr), R())
print('\n'.join(S))
