#!/usr/bin/env python3
# P207: setups for func_150867D4 (rail_route_next). nodes at 0x80450000 (D_800D2778), targets 0x80460000, avoid 0x80460100.
import struct
N, TG, AV = 0x80450000, 0x80460000, 0x80460100
G = [((0, 0, 0), (1, 4)), ((100, 0, 0), (0, 2)), ((200, 0, 0), (1, 3, 5)), ((300, 0, 0), (2, 6)), ((0, 0, 150), (0, 5)),
     ((200, 0, 120), (4, 2, 6)), ((300, 0, 100), (5, 3, 7)), ((400, 0, 100), (6,)), ((900, 50, 900), ())]
def words(bs, base):
    bs = bs + b'\0' * (-len(bs) % 4)
    return ['%08X=%08X' % (base + i, struct.unpack('>I', bs[i:i + 4])[0]) for i in range(0, len(bs), 4)]
def setup(name, start, targets, avoid=(), count=None, zone='0', seg='42C80000', g=G, nt=None):
    nb = b''
    for (x, y, z), l in g:
        links = list(l) + [0xFF] * (5 - len(l))
        nb += struct.pack('>hhhBBB5BBB', x, y, z, 0, 0, 0, *links, 0, 0)
    pk = words(nb, N) + words(bytes(targets) or b'\xEE', TG) + words(bytes(avoid) or b'\xEE', AV)
    pk += ['80087630=%04X0000' % ((count if count is not None else len(g)) & 0xFFFF), '80087638=11000000', '800D2778=%08X' % N, '800D277C=12345678']
    nt = len(targets) if nt is None else nt
    return '%s ! 0=%X,1=%X,2=%X,3=%X,4=%X ! %s ! 150870E0=%s ! 15087040=%s' % (name, start & 0xFFFFFFFF, nt & 0xFFFFFFFF,
        len(avoid), TG, AV, ','.join(pk), zone, seg)
rows = [
 setup('nt0', 0, [7], nt=0), setup('ntneg', 0, [7], nt=0x80), setup('ntwrap', 0, [7], nt=0x101),
 setup('sneg', -1, [7]), setup('sbig', 9, [7]), setup('seq', 9, [7], count=9), setup('starget', 2, [5, 2]),
 setup('far', 0, [7]), setup('far_av', 0, [7], avoid=[3]), setup('far_av2', 0, [7], avoid=[9, 3, 2]),
 setup('near', 0, [1]), setup('two', 0, [2]), setup('multi', 0, [6, 5]), setup('back', 7, [0]), setup('mid', 2, [4]),
 setup('unreach', 0, [8]), setup('unreach2', 7, [8, 9]),
 setup('z_all', 0, [7], zone='1'), setup('z_first', 0, [7], zone='0;0;0;0;1;0'), setup('z_run', 0, [7], zone='0;1;1;1;0;0'),
 setup('z_run2', 0, [7], zone='0;0;1;1;0;1'), setup('z_end', 0, [7], zone='1;1;0;0;0;0'), setup('z_alt', 0, [7], zone='1;0;1;0;1;0'),
 setup('z_lead', 0, [7], zone='0;0;0;1;1;1'), setup('z_two', 0, [2], zone='1;1;0'), setup('z_two2', 0, [2], zone='0;1;1'),
 setup('z_near', 0, [1], zone='1;1'),
 setup('seg', 0, [7], zone='0;1;0;1;0;1', seg='3F800000;40000000;40400000;40800000;40A00000'),
 setup('seg2', 7, [0], zone='1;0;0;1;1;0', seg='3FC00000;41200000;42C80000'),
]
GB = [((-30000, 0, 0), (1, 4)), ((0, 9000, 0), (0, 2)), ((30000, 0, 0), (1, 3, 5)), ((30000, 30000, 0), (2, 6)), ((-30000, 0, 30000), (0, 5)),
      ((0, 0, 30000), (4, 2, 6)), ((30000, 20000, 30000), (5, 3, 7)), ((32000, 32000, 32000), (6,)), ((0, 0, 0), ())]
GT = [((0, 0, 0), (1, 2)), ((100, 0, 0), (0, 3)), ((0, 0, 100), (0, 3)), ((100, 0, 100), (1, 2, 4)), ((200, 0, 100), (3,))]
rows += [
 setup('big', 0, [7], g=GB), setup('big_av', 0, [7], avoid=[6], g=GB), setup('big_z', 0, [7], zone='0;1;1;0;0;0;0', g=GB),
 setup('tie', 0, [4], g=GT), setup('tie_av', 0, [4], avoid=[1], g=GT), setup('tie_av2', 0, [4], avoid=[2], g=GT),
 setup('tie_nt', 0, [4, 3], nt=1, g=GT), setup('tie_av_s8', 0, [4], avoid=[1] * 0x81, g=GT),
 setup('tie_z', 0, [4], zone='1;1;0;0', g=GT), setup('tie_z2', 0, [4], zone='0;1;1;1', g=GT),
]
pass
pass
