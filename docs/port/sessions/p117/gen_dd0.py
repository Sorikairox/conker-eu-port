#!/usr/bin/env python3
"""P117: knob setups for func_151DEDD0 (menu_mode_update). EU addresses. Record D_80090174 -> 80480000."""
B = '80090174=80480000,800DC420=80490000,800E1008=804A0000,800BEE04=00000001,800C3A08=0,800E0FC4=0,80090120=0,80090110=0,800902AC=0,800901D0=0'
def rec(fade='3F800000', tp=0, menu=0, mp=0, inp=0, sx=(0,0,0,0), sy=(0,0,0,0), rx=(0,0,0,0), ry=(0,0,0,0)):
    b = lambda v: '%02X' % (v & 0xFF)
    return ','.join([
        '80480008=' + fade, '80480020=%04X0000' % inp,
        '8048002C=' + b(tp) + '00' + b(sx[0]) + b(sx[1]),
        '80480030=' + b(sx[2]) + b(sx[3]) + b(sy[0]) + b(sy[1]),
        '80480034=' + b(sy[2]) + b(sy[3]) + b(rx[0]) + b(rx[1]),
        '80480038=' + b(rx[2]) + b(rx[3]) + b(ry[0]) + b(ry[1]),
        '8048003C=' + b(ry[2]) + b(ry[3]) + b(menu) + b(mp)])
def pads(p):   # p: list of 4 (button, x, y); new presses D_800BED50 separately
    b = lambda v: '%02X' % (v & 0xFF)
    (b0, x0, y0), (b1, x1, y1), (b2, x2, y2), (b3, x3, y3) = p
    return ','.join(['800BED38=%04X%s%s' % (b0, b(x0), b(y0)), '800BED3C=0000%04X' % b1, '800BED40=%s%s0000' % (b(x1), b(y1)),
                     '800BED44=%04X%s%s' % (b2, b(x2), b(y2)), '800BED48=0000%04X' % b3, '800BED4C=%s%s0000' % (b(x3), b(y3))])
def press(a, b=0, c=0, d=0): return '800BED50=%04X%04X,800BED54=%04X%04X' % (a, b, c, d)
Z = [(0, 0, 0)] * 4
S = []
def add(n, *pk): S.append('%s ! ! %s ! ! ! ! !' % (n, ','.join([B] + [x for x in pk if x])))
F5 = '80090144=05000000'
for f in range(6): add('frame%d' % f, '80090144=%02X000000' % f, rec(), pads(Z), press(0))
add('frame5_d0', F5, '800901D0=01000000', rec(), pads(Z), press(0))
add('frame9', '80090144=09000000', rec(), pads(Z), press(0))
add('scene', F5, '80090120=01000000', rec())
add('scene0', '80090144=00000000', '80090120=01000000', rec())
for n in (1, 3, 7, 8, 9, 0xFF): add('queue%X' % n, F5, '80090110=%02X000000' % n, rec(), pads(Z), press(0))
# sticks: previous value / new value per controller and axis
vals = [(0, -0x31), (0, -0x32), (-0x31, -0x32), (-0x32, -0x40), (0, 0x31), (0, 0x32), (0x31, 0x32), (0x32, 0x40), (0x40, 0x7F), (-0x80, 0)]
for k, (old, new) in enumerate(vals):
    for c in range(4):
        p = [list(x) for x in Z]; p[c][1] = new; add('sx%d_c%d' % (k, c), F5, rec(sx=tuple(old if i == c else 0 for i in range(4))), pads([tuple(x) for x in p]), press(0))
        p = [list(x) for x in Z]; p[c][2] = new; add('sy%d_c%d' % (k, c), F5, rec(sy=tuple(old if i == c else 0 for i in range(4))), pads([tuple(x) for x in p]), press(0))
for btn in (0x1000, 0x8000, 0x4000, 2, 1, 0x20, 0xFFFF):
    for c in range(4): add('btn%X_c%d' % (btn, c), F5, rec(), pads(Z), press(*[btn if i == c else 0 for i in range(4)]))
add('fc6', F5, '800E0FC4=00000100', rec(sx=(0x40, 1, -5, 0x60), sy=(-0x40, 0x50, 2, 0)), pads([(0, 0x40, 0x40)] * 4), press(0x8000, 0x8000, 1, 2))
# auto repeat: stick held, counters near the limit, D_8009017C bits
for mask in (0, 1, 2, 0xF, 0x80):
    for step in (1, 0xB, 0x33):
        add('rep_m%X_s%X' % (mask, step), F5, '8009017C=%02X000000' % mask, '800BEE04=%08X' % step,
            rec(sx=(0x40, -0x40, 0x7F, 0x10), sy=(-0x40, 0x40, 0x10, -0x7F), rx=(0x30, 0x32, 0x20, 0x29), ry=(0x32, 0x28, 0x7F, 0x30)),
            pads([(0, 0x40, -0x40), (0, -0x40, 0x40), (0, 0x7F, 0x10), (0, 0x10, -0x7F)]), press(0))
# demo mode
for t, pr in ((0, 0x10), (0x545, 1), (0x546, 0x10), (0, 0)): add('demo_%X_%X' % (t, pr), F5, '800C3A08=00000100', '800E0EC0=%08X' % t, rec(), pads(Z), press(pr))
add('demo2', F5, '800C3A08=00000200', rec(), pads(Z), press(0x10))
# prompt fade D_800902AC
for t in (1, 0x33, 0x34, 0x64, 0x65, 0x66, 0x96, 0x97, 0x98, 0xB6, 0xC8, 0x200, 0x7FFF, 0x8000):
    for acc in (0, 0x1000):
        add('fade%X_%X' % (t, acc), F5, '800902AC=%04X0000' % t, '804A023C=80470000', rec(), pads(Z), press(acc))
add('fade_step', F5, '800902AC=00700000', '800BEE04=00000040', '804A023C=80470000', rec(), pads(Z), press(0))
# page fade-in and the dispatch
for fd in ('3F800000', '3F7FFFFF', '3F400000', '3F000000', '3EFFFFFF', '3E800000', '00000000', 'BF800000', '40000000', '7FC00000'):
    add('pfade_%s' % fd, F5, rec(fade=fd, tp=5), pads(Z), press(0x1000))
    add('pfade1_%s' % fd, F5, rec(fade=fd, menu=1, mp=2), pads(Z), press(0x1000))
for tp in range(-1, 8):
    for fd in ('3F800000', '3F400000'): add('title%d_%s' % (tp, fd[:3]), F5, rec(fade=fd, tp=tp), pads(Z), press(0x1000))
for mp in (0, 1, 2, 3, 4, 5, 6, 0x80, 0xFF): add('main%X' % mp, F5, rec(menu=1, mp=mp, tp=1), pads(Z), press(0))
for m in (2, -1): add('menu%d' % m, F5, rec(menu=m, mp=1, tp=1), pads(Z), press(0))
add('null', F5, '80090174=00000000')
add('frame4_disp', '80090144=04000000', rec(tp=5), pads(Z), press(0))
print('\n'.join(S))
