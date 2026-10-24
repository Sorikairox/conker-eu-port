#!/usr/bin/env python3
# P226: setups for func_15086268 (rail_node_nearest). ARG 0..2 = x, y, z float bits (100, 50, -20), 3 = kind, 4 = band.
# D_800D2778 (EU 800D2778) -> nodes at 80450000 (stride 0x10: s16 x y z, +6 band, +0xE kind); D_80087630 (EU 80087630)
# s16 count; D_8008763C (EU 8008763C) remembered node. key: func_15087204 jal 15087204 (RETF wall test, < 0 = free).
NODES = [(200, 50, -20, 0, 2), (110, 60, -20, 1, 0), (90, 50, -25, 1, 2), (100, 50, -20, 2, 1)]
def setup(name, kind=-1, band=-1, nodes=NODES, cached=0xFF, wall='', n=None):
    p = {0x800D2778: '80450000', 0x80087630: '%04X0000' % (len(nodes) if n is None else n),
         0x8008763C: '%02X000000' % cached, 0x800D277C: '5A5A5A5A'}
    for i, (x, y, z, b, k) in enumerate(nodes):
        a = 0x80450000 + 16 * i
        p[a] = '%04X%04X' % (x & 0xFFFF, y & 0xFFFF)
        p[a + 4] = '%04X%02X00' % (z & 0xFFFF, b)
        p[a + 8] = '00000000'
        p[a + 12] = '0000%02X00' % k
    poke = ','.join('%08X=%s' % kv for kv in sorted(p.items()))
    arg = '0=42C80000,1=42480000,2=C1A00000,3=%08X,4=%08X' % (kind & 0xFFFFFFFF, band & 0xFFFFFFFF)
    print('%s ! %s ! %s ! ! %s ! ! ! !' % (name, arg, poke, ('15087204=' + wall) if wall else ''))
setup('any')
setup('band1', band=1)
setup('band2', band=2)
setup('kind2', kind=2)
setup('kind1', kind=1)
setup('kind0_free', kind=0, wall='BF800000')
setup('kind0_walls', kind=0, wall='3F800000;BF800000;3F800000;BF800000;3F800000')
setup('kind0_walls2', kind=0, wall='BF800000;BF800000;3F800000;3F800000')
setup('kind0_zero', kind=0, wall='00000000')
setup('cached', cached=2)
setup('cached_far', cached=0, nodes=[(200, 50, -20, 0, 2), (190, 50, -20, 1, 0), (196, 50, -20, 1, 2)])
setup('cached_walls', kind=0, cached=1, wall='3F800000;BF800000')
setup('cached_free', kind=0, cached=1, wall='BF800000;3F800000')
setup('far', nodes=[(20000, 0, 0, 0, 0), (0, 15000, 0, 1, 0)])
setup('n0', n=0)
setup('tie', nodes=[(110, 50, -20, 0, 0), (90, 50, -20, 0, 0), (100, 60, -20, 0, 0)])
setup('band_s8', band=0x80, nodes=[(110, 50, -20, 0x80, 0), (120, 50, -20, 0x80, 0)])
setup('kind_hi', kind=0x102, band=0x101)
setup('dy', nodes=[(100, 60, -20, 0, 0), (100, 50, -10, 0, 0), (109, 50, -20, 0, 0)])
setup('cached_fe', cached=0xFE, nodes=[(20000, 0, 0, 0, 0), (0, 15000, 0, 1, 0)])
setup('cached_bar', cached=0, band=1, nodes=[(200, 50, -20, 0, 2), (200, 52, -19, 1, 0)])
setup('first', nodes=[(101, 50, -20, 0, 2), (110, 60, -20, 1, 0), (90, 50, -25, 1, 2)])
