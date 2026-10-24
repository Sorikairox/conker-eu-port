#!/usr/bin/env python3
# P237: setups for func_1508C600 (rail_pair_sight). Records (func_1505EEF4 = jal 1505F2A0, RET per call): A 80450000,
# B 80460000 (+0 kind, +0x14 pos, +0x1A4 s16 point, +0x31C state); states SA 80470000 / SB 80480000 (+0x84 flag,
# +0x114 s16 height, +0x75 kind). Rail D_800D27D0 = 80490000 (+0x16C0 masks). D_800E1000 difficulty (ROM D_80087664:
# 0 / 1 -> -1, 2 -> 600). func_150ACEA0 (RET hit flag; OUTW stack arg 11 = hit distance), func_15087204 (RETF).
import struct
def f(x): return struct.unpack('>I', struct.pack('>f', x))[0]
A, B, SA, SB, RAIL = 0x80450000, 0x80460000, 0x80470000, 0x80480000, 0x80490000
def setup(name, a=1, b=3, na=False, nb=False, fa=1, fb=1, ka=0, kb=0, sta=0, stb=0, dif=2, hit=0, hd=100.0, wall=-1.0):
    pk = {0x800D27D0: RAIL, 0x800E1000: (dif & 0xFF) << 24, RAIL + 0x16C0 + 4 * a: 0x00400040, RAIL + 0x16C0 + 4 * b: 0x00200020,
          A: ka, A + 0x14: f(10.0), A + 0x18: f(5.0), A + 0x1C: f(-20.0), A + 0x1A4: 0x00640032, A + 0x1A8: 0xFFCE0000,
          A + 0x31C: SA, B: kb, B + 0x14: f(40.0), B + 0x18: f(7.0), B + 0x1C: f(20.0), B + 0x1A4: 0xFF9C0014,
          B + 0x1A8: 0x00460000, B + 0x31C: SB,
          SA + 0x74: (sta & 0xFF) << 16, SA + 0x84: (fa & 0xFF) << 24, SA + 0x114: 0x00300000,
          SB + 0x74: (stb & 0xFF) << 16, SB + 0x84: (fb & 0xFF) << 24, SB + 0x114: 0xFFF00000}
    ret = '1505F2A0=%X;%X,150ACEA0=%X' % (0 if na else A, 0 if nb else B, hit)
    print('%s ! 0=%X,1=%X ! %s ! %s ! 15087204=%08X ! ! 150ACEA0=11:%08X !' % (
        name, a, b, ','.join('%08X=%08X' % kv for kv in sorted(pk.items())), ret, f(wall), f(hd)))
setup('nullA', na=True)
setup('nullB', nb=True)
setup('ff_clear')
setup('ff_wall', wall=2.0)
setup('ff_hitfar', hit=1, hd=100.0)
setup('ff_hitnear', hit=1, hd=10.0)
setup('ff_k9', sta=0x89, stb=9)
setup('f0_1F', fa=0, ka=0x1F)
setup('f0_pt', fa=0, dif=2)
setup('f0_dif0', fa=0, dif=0)
setup('0f_1F', fb=0, kb=0x1F)
setup('0f_pt', fb=0, dif=3)
setup('0f_dif1', fb=0, dif=1)
setup('00', fa=0, fb=0)
setup('00_1F', fa=0, fb=0, ka=0x1F, kb=0x1F, hit=1, hd=30.0)
setup('ff_ab', a=0, b=2, sta=9, hit=1, hd=60.0, wall=0.0)
setup('ids_hi', a=0x5001, b=0xA003)
setup('ff_hit60', hit=1, hd=60.0)
