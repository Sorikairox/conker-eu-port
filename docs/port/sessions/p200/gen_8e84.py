#!/usr/bin/env python3
# P200: setups for func_15088E84 (rail_param_step). record at 80480000, nodes D_800D2778 -> 80470000.
import struct
def f(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
def rec(t=0.5, start=0x100, time=0x300, cnt=7, laplen=4, lap=1, best=1, nodes=(1,2,3,4), alt=0, rail=0, player=0):
    w = {0: f(0.25), 4: f(0.75), 8: f(t), 0x18: '%08X' % (start & 0xFFFFFFFF), 0x1C: '%08X' % (time & 0xFFFFFFFF),
         0x20: '0000BEEF', 0x24: '%04X%02X%02X' % (cnt & 0xFFFF, laplen & 0xFF, lap & 0xFF),
         0x28: '%02X0000%02X' % (best & 0xFF, nodes[0]), 0x2C: '%02X%02X%02X%02X' % (nodes[1], nodes[2], nodes[3], alt & 0xFF),
         0x30: '%02X%02X0000' % (rail, player)}
    return ['%08X=%s' % (0x80480000 + k, v) for k, v in sorted(w.items())]
def nodes(types):
    return ['%08X=%08X' % (0x8047000C + 16 * n, ty) for n, ty in types.items()]
def g(name, dt, r, types={}, mirror=0, b616=0, laps=3, humans=1, bestl=(0, 0), totals=(0, 0), ret='9'):
    poke = ['800D2778=80470000', '800D27B0=AA000000', '800D27C8=%02X000000' % mirror, '800BEA34=0000%02X00' % b616,
            '800E1014=000000%02X' % laps, '80090130=%02X000000' % humans,
            '800E1040=%04X%04X' % (bestl[0] & 0xFFFF, bestl[1] & 0xFFFF), '800E1044=11112222',
            '800E1048=%08X' % totals[0], '800E104C=%08X' % totals[1]] + r + nodes(types)
    print('%s ! 0=80480000,1=%s ! %s ! 15088D24=%s ! ! ! !' % (name, f(dt), ','.join(poke), ret))
print('# P200 func_15088E84 (gen_8e84.py)')
g('none', 0.1, rec(t=0.5))
g('none_hi', 0.49, rec(t=0.5))
g('back', -0.3, rec(t=0.1, cnt=8, lap=2, best=2))
g('back_wrap0', -0.6, rec(t=0.1, cnt=0, lap=0, best=0))
g('back_alt', -0.3, rec(t=0.1, alt=0x81), ret='FF')
g('fwd_t1', 0.5, rec(t=0.5), types={3: 5})
for ty in (0, 5, 6, 7, 8, 9):
    g('fwd_ty%d' % ty, 0.6, rec(t=0.5), types={3: ty})
    g('fwdm_ty%d' % ty, 0.6, rec(t=0.5), types={3: ty}, mirror=1)
g('fwd_ty5_n2', 0.6, rec(t=0.5), types={2: 5, 3: 6})
# laps: cnt 7 -> 8 / 4 = lap 2 > best 1
g('lap_new', 0.6, rec(t=0.5, cnt=7, lap=1, best=1, start=0x100, time=0x300), bestl=(0x500, 0))
g('lap_new_bestworse', 0.6, rec(t=0.5, cnt=7, best=1, start=0x100, time=0x300), bestl=(0x100, 0))
g('lap_new_best0', 0.6, rec(t=0.5, cnt=7, best=1), bestl=(0, 0))
g('lap_new_bestneg', 0.6, rec(t=0.5, cnt=7, best=1), bestl=(0x8001, 0))
g('lap_new_cap', 0.6, rec(t=0.5, cnt=7, best=1, start=0x10, time=0x9000), bestl=(0x7FFF, 0))
g('lap_new_eq', 0.6, rec(t=0.5, cnt=7, best=1, start=0x10, time=0x7D10), bestl=(0x7FFF, 0))
g('lap_p1', 0.6, rec(t=0.5, cnt=7, best=1, player=1), humans=2, bestl=(0x500, 0x500), totals=(5, 6))
g('lap_p1_cpu', 0.6, rec(t=0.5, cnt=7, best=1, player=1), humans=1, bestl=(0x500, 0x500))
g('lap_rail', 0.6, rec(t=0.5, cnt=7, best=1, rail=1), bestl=(0x500, 0))
g('lap_time0', 0.6, rec(t=0.5, cnt=7, best=1, time=0), bestl=(0x500, 0))
g('lap_timeneg', 0.6, rec(t=0.5, cnt=7, best=1, time=-5), bestl=(0x500, 0))
g('lap_same', 0.6, rec(t=0.5, cnt=7, best=2), bestl=(0x500, 0))
g('lap_nochange', 0.6, rec(t=0.5, cnt=5, best=1), bestl=(0x500, 0))
g('lap_back', -0.6, rec(t=0.1, cnt=8, best=1, lap=2), bestl=(0x500, 0))
# last lap: laps 3, cnt 11 -> 12 / 4 = 3
g('last', 0.6, rec(t=0.5, cnt=11, best=2, start=0x1000, time=0x5000), bestl=(0x5000, 0), totals=(1, 2))
g('last_bigtotal', 0.6, rec(t=0.5, cnt=11, best=2, start=0x50000, time=0x60000), bestl=(0x5000, 0))
g('last_total_eq', 0.6, rec(t=0.5, cnt=11, best=2, start=0x50000, time=0x57E40), bestl=(0x5000, 0))
g('last_total_eq1', 0.6, rec(t=0.5, cnt=11, best=2, start=0x50000, time=0x57E41), bestl=(0x5000, 0))
g('last_cpu', 0.6, rec(t=0.5, cnt=11, best=2, player=2), humans=1)
# beyond laps: cnt 15 -> 16 / 4 = 4 > laps 3
g('over', 0.6, rec(t=0.5, cnt=15, best=3), bestl=(0x500, 0))
g('over_cap', 0.6, rec(t=0.5, cnt=19, best=3), b616=1, bestl=(0x500, 0))
g('over_cap_b', 0.6, rec(t=0.5, cnt=19, best=4), b616=1, bestl=(0x500, 0))
g('cap_below', 0.6, rec(t=0.5, cnt=7, best=1), b616=1, bestl=(0x500, 0))
g('laplen_neg', 0.6, rec(t=0.5, cnt=7, laplen=0xFE, best=0x80), bestl=(0x500, 0))
g('cnt_neg', -0.6, rec(t=0.1, cnt=0, laplen=4, best=0x80), bestl=(0x500, 0))
g('laps_neg', 0.6, rec(t=0.5, cnt=7, best=1), laps=0xFF, b616=1)
g('player_neg', 0.6, rec(t=0.5, cnt=7, best=1, player=0xFF), humans=1, bestl=(0x500, 0x500))
