#!/usr/bin/env python3
# P156: setups for func_1507CD64 (player_hit_reaction). EU: D_800CC2D0 0x800CC6F0 (0x32C), D_8008FD8C 0x8009012C (s8),
# D_800BE616 0x800BEA36 (u8), D_8009015C 0x8009015C (u16), D_800BE9F0 0x800BEE10, D_800E0F00 0x800E0F00 (s16[]).
B = 0x800CC6F0; CTL = 0x80450000
def setup(name, idx=1, kind=0, n=4, mp=0, flags=0, c120=0, c121=0, c1ac=0, st=1, u5=0, u65=0, u128=0, u13c=0, mode=0):
    o = B + idx * 0x32C
    pk = ['%X=%08X' % (o + 0x31C, CTL), '%X=%08X' % (CTL + 0x120, (c120 << 24) | (c121 << 16)), '%X=%08X' % (CTL + 0x1AC, c1ac << 24),
          '9001012C=%08X' % (n << 24), '800BEA34=%08X' % (mp << 8), '8009015C=%08X' % (flags << 16), '800BEE10=%08X' % mode,
          '%X=%08X' % (o, st), '%X=%08X' % (o + 4, u5 << 16), '%X=%08X' % (o + 0x64, u65 << 16), '%X=%08X' % (o + 0x128, u128 << 24),
          '%X=%08X' % (o + 0x13C, u13c << 24), '%X=%08X' % (o + 0xF8, 0x12345001)]
    pk[3] = '8009012C=%08X' % (n << 24)
    print(' ! '.join([name, '0=%X,1=%X' % (o, kind & 0xFFFFFFFF), ','.join(pk), '', '', '', '', '']))
for k in list(range(18)) + [-1, 0x100]:
    setup('k%d' % k, kind=k)
    setup('k%d_mp' % k, kind=k, mp=1, flags=0x20, c1ac=1)
for k in (1, 9):
    for c121 in (0, 9, 3):
        setup('busy%d_%d' % (k, c121), kind=k, c120=2, c121=c121, mp=1, flags=0x20)
setup('mp_u128', kind=2, mp=1, flags=0x20, u128=1)
setup('mp_noflag', kind=2, mp=1, flags=0xDF)
setup('mp_idx20', idx=20, n=25, kind=3, mp=1)
setup('mp_idx15', idx=15, n=25, kind=3, mp=1)
setup('idx_ge_n', idx=4, n=4, kind=3)
setup('idx_neg_n', idx=0, n=0xFF, kind=3)
for st, u5, u65 in ((1, 0, 0), (0x15, 0, 0), (2, 3, 0), (2, 0, 7), (2, 0, 0), (0, 2, 0)):
    setup('k6_%x_%d_%d' % (st, u5, u65), kind=6, st=st, u5=u5, u65=u65)
for k in (0, 4, 9, 15, 16):
    setup('p0m4_%d' % k, idx=0, kind=k, mode=4)
    setup('p0m3_%d' % k, idx=0, kind=k, mode=3)
setup('p2m4', idx=2, kind=0, mode=4)
for k in (0, 5, 15):
    setup('u13c_%d' % k, kind=k, u13c=1)
