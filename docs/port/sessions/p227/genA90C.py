#!/usr/bin/env python3
# P227: setups for func_151EA90C (mp_scoreboard_draw). ARG 0 = DL 80480000, 1 = y, 2 = alpha, 3 = hud. EU addresses
# (port_work/p28h/euaddr.sh): D_80090174 -> 80450000 (+0x42 mode, +0x46 s16 score per player, rows i * 12: +0x66 hits,
# +0x6A lives, +0x6C shots), D_800E0B94 800E0FC4, D_80087270 80087610, D_800E1008 -> 80460000 (string pointers),
# D_800CC2D0 (EU 800CC6F0) +0x31C -> 80470000 + i * 0x400 (+0x1AA shots in the HUD), D_800ABEA0 team colours.
# Keys (decoded jal): func_1510D66C 1510D66C (texture; 80000000 = fail), func_151E8E94 151E8E94, func_151EA4C8
# 151EA4C8, func_151E9E1C 151E9E1C, func_15042D94 15043084 (text), func_1504332C 1504361C (colour).
def setup(name, mode=0, hud=0, y=0x50, alpha=0x1C0, f160=1, b94=0, d168=0, e1003=0, queue=(0, 1, 2, 3),
          state=(0, 0, 0, 0), teams=(1, 2, 3, 4), place=(1, 2, 3, 4, 2, 0, 1, 3), score=(5, -3, 0, 7), hits=(3, 0, 50, 7),
          lives=(3, 2, 1, 0), shots=(4, 0, 100, -2), hshots=(8, 1, 0, 3), tsc=(11, 22, 33, 44, 55), f00=(9, 8, 7, 6),
          s11c=0, tex='80440000;80441000;80442000'):
    m = {}
    def s8(a, v): m[a] = v & 0xFF
    def s16(a, v): s8(a, v >> 8); s8(a + 1, v)
    def s32(a, v): s16(a, v >> 16); s16(a + 2, v)
    s32(0x80090174, 0x80450000); s8(0x80450042, mode); s16(0x80090160, f160); s8(0x800E0FC4, b94); s8(0x80090168, d168)
    s8(0x800E1003, e1003); s8(0x8009011C, s11c); s32(0x800E1008, 0x80460000)
    for i in range(0x60): s32(0x80460000 + 4 * i, 0x80500000 + i)
    for i in range(4):
        s8(0x800901E4 + i, queue[i]); s8(0x80087610 + i, state[i]); s8(0x800E1030 + i, teams[i])
        s16(0x80450046 + 2 * i, score[i]); r = 0x80450000 + i * 12
        s16(r + 0x66, hits[i]); s16(r + 0x6A, lives[i]); s16(r + 0x6C, shots[i]); s16(0x800E0F00 + 2 * i, f00[i])
        s32(0x800CC6F0 + i * 0x32C + 0x31C, 0x80470000 + i * 0x400); s16(0x80470000 + i * 0x400 + 0x1AA, hshots[i])
    for i in range(5): s16(0x800E0ED0 + 2 * i, tsc[i]); s32(0x800ABEA0 + 4 * i, 0x11223300 + i * 0x10101000)
    for i in range(8): s8(0x800E0EF0 + i, place[i])
    words = sorted(set(a & ~3 for a in m))
    pk = ','.join('%08X=%02X%02X%02X%02X' % ((w,) + tuple(m.get(w + k, 0) for k in range(4))) for w in words)
    ret = '1510D66C=%s,151E8E94=%s,151EA4C8=80490000,151E9E1C=80491000' % (
        tex, ';'.join('%08X' % (0x80481000 + 0x100 * k) for k in range(24)))
    print('%s ! 0=80480000,1=%08X,2=%08X,3=%08X ! %s ! %s ! ! ! !' % (name, y & 0xFFFFFFFF, alpha, hud, pk, ret))
setup('base')
setup('noteamcol', f160=0)
setup('mode1', mode=1)
setup('mode8', mode=8, teams=(0, 2, 0, 1))
setup('team0', teams=(0, 2, 0, 1))
setup('m11', mode=11, queue=(0, -1, 2, 3))
setup('m12', mode=12, queue=(-1, 1, -1, 3))
setup('m12_hud', mode=12, hud=1)
setup('m11_notex', mode=11, tex='80000000')
setup('spect', state=(0, 10, 9, 0))
setup('state9_p0', s11c=9, state=(0, 0, 0, 9))
setup('state9_p1', s11c=9, queue=(-1, 1, 2, 3))
setup('hud', hud=1, f160=0x6341)
setup('hud_noteam', hud=1, f160=0x0040, hits=(30000, 2, 3, 4), hshots=(1, -1, 2, 0))
setup('clamp', hits=(30000, 99, 101, 1), shots=(1, 1, 1, 1))
setup('wide', e1003=2, f160=0x6340)
setup('wide_hud', e1003=2, f160=0x6341, hud=1)
setup('b94', b94=1, d168=1, place=(0, 1, 2, 3, 4, 0, 0, 0))
setup('b94only', b94=1, d168=0)
setup('d168only', b94=0, d168=1)
setup('fail887', tex='80000000')
setup('fail888', tex='80440000;80000000')
setup('fail843', tex='80440000;80441000;80000000')
setup('noqueue', queue=(-1, -1, -1, -1), f160=0x6340)
setup('place0', place=(0, 0, 5, 1, 1, 1, 1, 1), y=-3)
setup('mode1_hud', mode=1, hud=1, f160=0x0001)
setup('clamp_eq', hits=(100, 200, 1, 1), shots=(1, 2, 1, 1))
