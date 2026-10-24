#!/usr/bin/env python3
# P200: setups for func_15086508 (rail_point_pick). nodes D_800D2778 -> 80470000; RET func_15086218 (band),
# func_15086268 (nearest node), func_150870E0 (zone), func_150A3794 (inside), func_150867D4 (choice).
import struct
def f(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
N = {2: (0, 0, 10, [3, 4, 5]), 3: (100, 0, 0, []), 4: (0, 100, 0, []), 5: (-100, 0, 0, []), 6: (30, -40, 0, []), 7: (100, 100, 0, [])}
def g(name, pos, count=2, first=1, near=2, zone=0, inside=0, choice=3, nodes=N, ret68=None):
    p = ['800D2778=80470000']
    for i, (x, z, rad, ln) in nodes.items():
        ln = list(ln) + [0xFF] * (5 - len(ln)); b = 0x80470000 + 16 * i
        p += ['%08X=%04X0007' % (b, x & 0xFFFF), '%08X=%04X0200' % (b + 4, z & 0xFFFF),
              '%08X=%02X%02X%02X%02X' % (b + 8, rad, ln[0], ln[1], ln[2]), '%08X=%02X%02X0100' % (b + 12, ln[3], ln[4])]
    x, y, z = pos
    ret = '15086218=2,15086268=%X,150870E0=%X,150A3794=%X,150867D4=%s' % (near, zone, inside, ret68 or ('%X' % choice))
    print('%s ! 0=%s,1=%s,2=%s,3=%X,4=%X,5=80450000,6=80450010 ! %s ! %s ! ! ! ! ' % (name, f(x), f(y), f(z), count & 0xFFFFFFFF, first & 0xFFFFFFFF, ','.join(p), ret))
print('# P200 func_15086508 (gen_6508.py)')
g('ahead3', (50, 5, 10))
g('ahead3_wrong', (50, 5, 10), choice=4)
g('ahead3_ff', (50, 5, 10), choice=0xFF)
g('ahead4', (10, 5, 50), choice=4)
g('ahead4_wrong', (10, 5, 50), choice=3)
g('behind', (0, 5, -50))
g('ahead5', (-60, 5, 3), choice=5)
g('diag', (40, 5, 40), choice=3)
g('diag4', (39, 5, 40), choice=4)
g('on_node', (0, 5, 0))
g('count0', (50, 5, 10), count=0)
g('countneg', (50, 5, 10), count=0x80)
g('count1FF', (50, 5, 10), count=0x1FF)
g('count100', (50, 5, 10), count=0x100)
g('none', (50, 5, 10), near=0xFF)
g('near1FF', (50, 5, 10), near=0x1FF)
g('zone_in', (50, 5, 10), zone=0x80460000, inside=1, choice=7)
g('zone_in_ff', (50, 5, 10), zone=0x80460000, inside=1, choice=0xFF)
g('zone_out', (50, 5, 10), zone=0x80460000, inside=0)
g('nozone_in', (50, 5, 10), zone=0, inside=1)
g('first_neg', (50, 5, 10), first=0x1FE, zone=0x80460000, inside=1, choice=6)
g('rad_big', (50, 5, 10), nodes={**N, 2: (0, 0, 0xFF, [3, 4, 5])}, choice=6)
g('rad_5000', (50, 5, 10), nodes={**N, 2: (0, 0, 0x80, [3, 4, 5])}, choice=3)
g('rad_ff_first', (50, 5, 10), first=0x81, nodes={**N, 2: (0, 0, 0xFF, [3])}, choice=0xFF)
g('links_ff', (50, 5, 10), nodes={**N, 2: (0, 0, 10, [])})
g('link_last', (50, 5, 10), nodes={**N, 2: (0, 0, 10, [0xFF, 0xFF, 0xFF, 0xFF, 3])})
g('link6', (35, 5, -45), nodes={**N, 2: (0, 0, 10, [3, 6, 4])}, choice=6)
g('link_tie', (50, 5, 0), nodes={**N, 2: (0, 0, 10, [3, 7]), 7: (100, 0, 0, [])}, choice=7)
g('link_tie3', (50, 5, 0), nodes={**N, 2: (0, 0, 10, [3, 7]), 7: (100, 0, 0, [])}, choice=3)
g('far', (20000, 5, 20000), choice=3)
