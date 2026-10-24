#!/usr/bin/env python3
# P230: setups for func_1508CA14 (rail_pair_rivals). ARG 0 = who, 1 = refresh. D_800D27D0 -> 80450000 (team +0xE64,
# target +0x11C, masks +0x16C0, cursor bytes +0x1700 / +0x1701). Racers D_800CC2D0 = EU 800CC6F0 (stride 0x32C;
# x +0x14, z +0x1C, team byte +0x128). D_80090130 (humans, s8) 80090130, D_8008FD8C (racers, s8) EU 8009012C,
# D_800D18A0 (u16) EU 800D1CC0. func_1508C600 = jal 1508C600 (stub; arguments compared).
import struct
def fb(f): return struct.unpack('>I', struct.pack('>f', f))[0]
def setup(name, who=0, refresh=1, nh=2, n=6, teams=None, tgt=None, masks=None, a=0, b=0, busy=0, xz=None, rteam=None):
    m = {}
    def w(ad, v): m[ad] = v & 0xFFFFFFFF
    w(0x800D27D0, 0x80450000); w(0x80090130, (nh & 0xFF) << 24); w(0x8009012C, (n & 0xFF) << 24)
    w(0x800D1CC0, busy << 16); w(0x80451700, a << 24 | b << 16)
    teams = teams or [i % 2 for i in range(16)]
    tgt = tgt or [-1] * 16
    masks = masks or [0] * 16
    rteam = rteam or [i % 3 for i in range(16)]
    xz = xz or [(100.0 + 10 * i, -50.0 + 3 * i) for i in range(16)]
    for i in range(16):
        w(0x80450E64 + 4 * i, teams[i]); w(0x8045011C + 4 * i, tgt[i]); w(0x804516C0 + 4 * i, masks[i])
        r = 0x800CC6F0 + i * 0x32C
        w(r + 0x14, fb(xz[i][0])); w(r + 0x1C, fb(xz[i][1])); w(r + 0x128, rteam[i] << 24)
    pk = ','.join('%08X=%08X' % kv for kv in sorted(m.items()))
    print('%s ! 0=%X,1=%X ! %s ! ! ! ! ! !' % (name, who & 0xFFFFFFFF, refresh & 0xFFFFFFFF, pk))
setup('base')
setup('r0', refresh=0, who=3, masks=[0x10 * i + 1 for i in range(16)])
setup('who5', who=5, masks=[0xFFFF0000 | i for i in range(16)])
setup('nh0', nh=0)
setup('nh1_n8', nh=1, n=8)
setup('same_team', teams=[0] * 16)
setup('masked', masks=[0x00000028, 0x00010000 << 3] + [0] * 14)
setup('masked_lo', masks=[0x00000004, 0x00000010] + [0] * 14)
setup('tgt', tgt=[-1, -1, -1, 0, 1, 0, 0, 1] + [-1] * 8)
setup('tgt_order', n=9, teams=[0, 0] + [1] * 14, tgt=[-1, -1, -1, -1, -1, 0, -1, 0, 0] + [-1] * 7)
setup('xz_eq', xz=[(5.0, 5.0)] * 16)
setup('xz_eq_tgt', xz=[(5.0, 5.0)] * 16, tgt=[-1, -1, 0, -1, 0] + [-1] * 11)
setup('two_ai', nh=2, n=4, teams=[0, 1, 1, 0] + [0] * 12)
setup('one_ai', nh=2, n=3)
setup('rr4', refresh=4, a=1, b=2)
setup('rr_wrap', refresh=3, n=4, a=2, b=3)
setup('rr_wrap_a', refresh=2, n=5, a=3, b=4)
setup('rr_busy', refresh=2, busy=0x0006, a=0, b=0)
setup('rr_busy_all', refresh=1, busy=0xFFFF)
setup('rr_team', refresh=2, rteam=[1] * 16)
setup('rr_team_mix', refresh=3, rteam=[0, 0, 1, 0, 1, 1, 0, 0] + [2] * 8, a=0, b=0)
setup('rr_n2', refresh=3, n=2, nh=1, a=0, b=1)
setup('rr_hi', refresh=2, n=16, nh=4, a=13, b=15, teams=[i % 4 for i in range(16)])
setup('rr_cursor_big', refresh=1, n=6, a=0xFE, b=0xFF)
setup('n16', n=16, nh=3, teams=[i % 3 for i in range(16)], tgt=[(i * 7) % 3 for i in range(16)])
# P230 second round (survivors of the first mutant run)
setup('masked_hi', masks=[0x00080000, 0] + [0] * 14)
setup('far_xz', xz=[(25000.0, 0.0)] * 16)
setup('far_tgt', xz=[(60000.0, 0.0)] * 16, tgt=[-1, -1, -1, 0, -1, 0] + [-1] * 10)
setup('tgt_one', n=9, teams=[0, 0] + [1] * 14, tgt=[-1, -1, -1, -1, -1, 0, -1, -1, -1] + [-1] * 7)
setup('kmask', n=9, teams=[0, 0] + [1] * 14, masks=[0, 0] + [0xFFFF0000] * 14)
setup('rr_team_ab', refresh=2, a=1, b=3, rteam=[0, 1, 0, 2, 1, 1, 0, 0] + [2] * 8, masks=[-1] * 16)
setup('rr_wrap_m', refresh=3, n=4, a=2, b=3, masks=[-1] * 16)
setup('rr4_m', refresh=4, a=1, b=2, masks=[-1] * 16)
