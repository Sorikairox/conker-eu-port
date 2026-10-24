#!/usr/bin/env python3
# P237: setups for func_151EA4C8 (mp_team_score_draw). buf 80460000, D_80090160 (u16), D_80090174 = 80450000 (+0x42
# mode, +0x46 s16 rows), D_8008FD8C = EU 8009012C (s8 count), D_800CC2D0 = EU 800CC6F0 (0x32C each, +0x128 team),
# D_800E1030 team bytes, D_800E0ED0 stored scores. RET: func_1510D66C (1510D66C) texture, func_150859AC = jal 15085E1C
# (per call), func_151E8E94 (151E8E94, plain C) the DL end.
BAR, BUF = 0x80450000, 0x80460000
def setup(name, flags=0, mode=0, tex=0x80470000, y=0x320, upd=1, n=4, sc='5;FFFFFFFD;7;9', teams=(0, 1, 1, 0), rows=(3, -2, 40, 7)):
    pk = {0x80090160: (flags & 0xFFFF) << 16, 0x80090174: BAR, 0x8009012C: (n & 0xFF) << 24,
          0x800E0ED0: 0x0011FFF5, 0x800E1030: (teams[0] << 24) | (teams[1] << 16) | (teams[2] << 8) | teams[3]}
    pk[BAR + 0x44] = rows[0] & 0xFFFF
    pk[BAR + 0x48] = ((rows[1] & 0xFFFF) << 16) | (rows[2] & 0xFFFF)
    pk[BAR + 0x4C] = (rows[3] & 0xFFFF) << 16
    pk[BAR + 0x40] = ((mode & 0xFF) << 8)
    for i, t in enumerate(teams):
        pk[0x800CC6F0 + i * 0x32C + 0x128] = t << 24
    ret = '1510D66C=%X,15085E1C=%s,151E8E94=80460100;80460200' % (tex, sc)
    print('%s ! 0=%X,1=%X,2=%X ! %s ! %s ! ! ! !' % (name, BUF, y & 0xFFFFFFFF, upd, ','.join('%08X=%08X' % kv for kv in sorted(pk.items())), ret))
setup('notex', tex=0x80000000)
setup('big_rows')
setup('big_rows_n0', n=0)
setup('small_4000', flags=0x4000)
setup('mode8', mode=8)
setup('mode8_4000', flags=0x4000, mode=8, y=0x17)
setup('team6040', flags=0x40)
setup('team2000', flags=0x2000, y=0x100)
setup('pl100', flags=0x100)
setup('pl100_n2', flags=0x100, n=2, sc='FFFFFFFF;3')
setup('stored', upd=0)
setup('stored_4000', upd=0, flags=0x4000, y=3)
setup('pl100_t2', flags=0x100, teams=(0, 1, 2, 0))
