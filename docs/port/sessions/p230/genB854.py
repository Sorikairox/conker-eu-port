#!/usr/bin/env python3
# P230: setups for func_1508B854 (rail_events_assign_nodes). D_800D27D0 -> 80450000 (slots +0x55C, flags +0x5C,
# event count byte +0x1745, events +0x1748: f32 radius, s16 x / y / z). D_800D2778 -> 80470000 (nodes, 0x10: s16 x +0,
# s16 z +4, u8 +7). Racers D_800CC2D0 = EU 800CC6F0 (x +0x14, y +0x18, z +0x1C). D_80090130 80090130, D_8008FD8C
# EU 8009012C. Keys: func_15086218 15086218 (RET), func_15086268 15086268 (RET near node / FFFFFFFF), bzero 10022A10,
# func_1508B704 1508B704 (OUTA through a1: the zone words x, z, radius, lim[8], count / node bytes).
import struct
def fb(f): return struct.unpack('>I', struct.pack('>f', f))[0]
def setup(name, nh=1, n=5, slots=None, evs=None, racers=None, near=7, zone=None, nodes=None, band=3):
    m = {}
    def w(ad, v): m[ad] = v & 0xFFFFFFFF
    w(0x800D27D0, 0x80450000); w(0x800D2778, 0x80470000)
    w(0x80090130, (nh & 0xFF) << 24); w(0x8009012C, (n & 0xFF) << 24)
    slots = slots or [-1, 3, -1, 4, -1, 6, -1, -1, 2, -1, -1, -1, -1, -1, -1, -1]
    for i, v in enumerate(slots):
        w(0x8045055C + 4 * i, v); w(0x8045005C + 4 * i, 0)
    evs = evs if evs is not None else [(2000.0, 130, 5, 70)]
    w(0x80451744, (len(evs) & 0xFF) << 16)
    for j, (r, x, y, z) in enumerate(evs):
        a = 0x80451748 + 0xC * j
        w(a, fb(r)); w(a + 4, (x & 0xFFFF) << 16 | (y & 0xFFFF)); w(a + 8, (z & 0xFFFF) << 16)
    racers = racers or [(100.0, 0.0, 100.0)] * 16
    for i, (x, y, z) in enumerate(racers):
        r = 0x800CC6F0 + i * 0x32C
        w(r + 0x14, fb(x)); w(r + 0x18, fb(y)); w(r + 0x1C, fb(z))
    nodes = nodes or [(100 + 3 * i, 100 - 2 * i, 0x40 + i) for i in range(16)]
    for i, (x, z, b7) in enumerate(nodes):
        w(0x80470000 + 16 * i, (x & 0xFFFF) << 16); w(0x80470004 + 16 * i, (z & 0xFFFF) << 16 | b7)
    zone = zone or dict(cnt=3, nodes=[1, 2, 3, 0, 0, 0, 0, 0], lim=[50.0, 50.0, 50.0, 0, 0, 0, 0, 0], r=2000.0)
    nd = zone['nodes'] + [0] * 8
    lim = (list(zone['lim']) + [0.0] * 8)[:8]
    zw = [fb(1.0), fb(2.0), fb(zone['r'])] + [fb(x) for x in lim] + \
         [(zone['cnt'] & 0xFFFF) << 16 | nd[0] << 8 | nd[1], nd[2] << 24 | nd[3] << 16 | nd[4] << 8 | nd[5], nd[6] << 24 | nd[7] << 16]
    pk = ','.join('%08X=%08X' % kv for kv in sorted(m.items()))
    print('%s ! ! %s ! 15086218=%X,15086268=%X ! ! 1508B704=1:%s ! ! !' % (name, pk, band, near & 0xFFFFFFFF, ';'.join('%08X' % x for x in zw)))
setup('base')
setup('none', evs=[])
setup('n0', n=0, nh=0)
setup('near_none', near=-1)
setup('two_ev', evs=[(2000.0, 130, 5, 70), (900.0, 105, 10, 95)], zone=dict(cnt=2, nodes=[4, 5], lim=[200.0, 200.0], r=500.0))
setup('dy_hi', evs=[(2000.0, 130, 0, 70)], racers=[(100.0, 199.0, 100.0), (100.0, 200.0, 100.0)] * 8)
setup('dy_lo', evs=[(2000.0, 130, 0, 70)], racers=[(100.0, -99.0, 100.0), (100.0, -100.0, 100.0)] * 8)
setup('dist', evs=[(1.0, 100, 0, 100)], racers=[(100.0, 0.0, 100.0), (110.0, 0.0, 100.0), (105.0, 0.0, 105.0), (109.0, 0.0, 100.0)] * 4, n=4, nh=0)
setup('rad_edge', evs=[(0.0, 100, 0, 100)], racers=[(110.0, 0.0, 100.0)] * 16, n=3, nh=0)
setup('lim', zone=dict(cnt=4, nodes=[1, 2, 3, 4], lim=[1.0, 40.0, 100.0, 1000.0], r=2000.0))
setup('lim_eq', zone=dict(cnt=2, nodes=[0, 2], lim=[0.0, 52.0], r=2000.0))
setup('tie', nodes=[(100, 100, 9 + i) for i in range(16)], zone=dict(cnt=5, nodes=[3, 1, 2, 4, 5], lim=[10.0] * 5 + [0, 0, 0], r=2000.0))
setup('cnt8', zone=dict(cnt=8, nodes=[8, 7, 6, 5, 4, 3, 2, 1], lim=[5000.0] * 8, r=2000.0))
setup('cnt0', zone=dict(cnt=0, nodes=[1], lim=[50.0], r=2000.0))
setup('cnt_neg', zone=dict(cnt=-1, nodes=[1], lim=[50.0], r=2000.0))
setup('zone_rad', zone=dict(cnt=3, nodes=[1, 2, 3], lim=[50.0] * 3, r=-200.0))
setup('far', racers=[(5000.0, 0.0, 100.0)] * 16)
setup('mixed', n=8, nh=2, racers=[(100.0, 0.0, 100.0), (5000.0, 0.0, 0.0), (101.0, 0.0, 99.0), (100.0, 300.0, 100.0),
      (103.0, 0.0, 97.0), (120.0, 0.0, 100.0), (100.0, 0.0, 130.0), (100.0, -150.0, 100.0)] * 2,
      slots=[-2, 5, -1, 7, 0, -5, 1, -1] + [-1] * 8, zone=dict(cnt=6, nodes=[1, 2, 3, 4, 5, 6], lim=[400.0] * 6, r=2000.0))
# (first draft: lim lists shorter than 8 were not padded, so the count word landed on a node byte and the zone count
# became huge: UNSURE / timeouts. Fixed by padding; the n16 run is split in two anyway.)
setup('n16', n=16, nh=3, zone=dict(cnt=7, nodes=[1, 2, 3, 4, 5, 6, 7], lim=[900.0] * 7, r=2000.0),
      racers=[(100.0 + 3 * i, 0.0, 100.0 - 2 * i) for i in range(16)])
setup('n16_hi', n=16, nh=3, zone=dict(cnt=3, nodes=[13, 14, 15], lim=[900.0] * 3, r=2000.0),
      racers=[(100.0 + 3 * i, 0.0, 100.0 - 2 * i) for i in range(16)])
setup('asym', evs=[(10000.0, 150, -20, 60)], racers=[(110.0, 0.0, 90.0), (140.0, 50.0, 70.0), (100.0, 0.0, 100.0), (95.0, 10.0, 105.0)] * 4,
      zone=dict(cnt=5, nodes=[2, 6, 1, 9, 4], lim=[300.0, 900.0, 120.0, 2000.0, 60.0], r=10000.0))
setup('near_hi', near=0x12B4, zone=dict(cnt=2, nodes=[3, 5], lim=[500.0, 500.0], r=2000.0))
setup('ey_hi', evs=[(2000.0, 130, 150, 70)], racers=[(100.0, 100.0, 100.0)] * 16)
setup('xz_rng', evs=[(1000.0, 130, 0, 70)], racers=[(110.0, 0.0, 90.0)] * 16, zone=dict(cnt=2, nodes=[1, 2], lim=[900.0, 900.0], r=1000.0))
setup('best2', zone=dict(cnt=2, nodes=[1, 6], lim=[5000.0, 5000.0], r=2000.0))
