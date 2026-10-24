#!/usr/bin/env python3
# P188: setups for func_15112074 (sky_box_draw). gdl 80480000; stubs return heap gdl pointers.
# EU data: sky D_800B0DF0 = 800B1200 -> 80400000 (+5..7 colour, +9 sky index); player word D_80082FA4 = 80083334
# (low half = D_80083336), mode D_80082FA0 = 80083330, camera records D_800BE628 = 800BEA48 -> 80410000,
# frame D_800BE9C0 = 800BEDE0 (byte), level D_800BE9F0 = 800BEE10, D_800C3A08 byte / D_800C35EA = 800C3A0A byte,
# Mtx base D_800DC2E0 = 800DC2E0 -> 80420000, vertex buffers D_800DC2B8 = 800DC2B8 (words).
import struct
def fb(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
def setup(name, lvl=5, mode=0, player=0, frame=0, col=(0x40, 0x80, 0xC0), skyidx=2, b3a08=0, m3a0a=0,
          yaw=0.0, pitch=10.0, roll=33.0, dist=500, count=8, first=2, loads='80460000;0;80461000;1;80462000;1;80463000;0',
          extra='', last=None):
    p = {0x800B1200: 0x80400000, 0x80400004: (col[0] << 8) | 0x11, 0x80400008: (col[1] << 24) | (col[2] << 16) | (skyidx << 0) * 0 | 0x0000,
         0x80083334: (player << 0) | 0x0, 0x80083330: mode, 0x800BEA48: 0x80410000, 0x800BEDE0: frame << 24,
         0x800BEE10: lvl, 0x800C3A08: (b3a08 << 24) | (m3a0a << 8), 0x800DC2E0: 0x80420000,
         0x800DC2B8: 0x80430000, 0x800DC2BC: 0x80431000, 0x800DC2C0: 0x80432000, 0x800DC2C4: 0x80433000}
    # sky +4..+0xB: +5 = c0, +6 = c1, +7 = c2, +9 = index
    p[0x80400004] = (0x11 << 24) | (col[0] << 16) | (col[1] << 8) | col[2]
    p[0x80400008] = (0x22 << 24) | (skyidx << 16) | 0x3344
    p[0x80083334] = (player << 16) | 0x5F60 if False else player   # low half (D_80083336) stays the player word's
    for o, v in ((0x24, 10.0), (0x28, 230.0), (0x2C, 20.0), (0x30, 300.0)):
        for b in (0x80410000, 0x80410180):
            p[b + o] = int(fb(v), 16)
    p[0x804100B8] = 0x01234567; p[0x80410238] = 0x89ABCDEF
    pk = ','.join('%08X=%08X' % kv for kv in p.items()) + extra
    arg = '0=80480000,1=41200000,2=42C80000,3=C1200000,4=%s,5=%s,6=%s,7=%X' % (fb(yaw), fb(pitch), fb(roll), dist & 0xFFFFFFFF)
    ret = '1501A470=80440000,1501A660=80440100,15110AC4=80440200,1511127C=80450000'
    outa = '1511127C=15:%X/16:%X/17:%s' % (count & 0xFFFFFFFF, first, loads)
    if last is not None: outa += '/18:%X' % last
    return '%s ! %s ! %s ! %s ! ! %s ! !' % (name, arg, pk, ret, outa)
out = [
    setup('base'),
    setup('white', col=(255, 255, 255)),
    setup('mode1', mode=1, pitch=90.0),
    setup('p1f1', player=1, frame=1, skyidx=5),
    setup('l65', lvl=65, pitch=100.0),
    setup('l65b', lvl=65, pitch=150.0),
    setup('l60', lvl=60),
    setup('l60p1', lvl=60, player=1),
    setup('l19a', lvl=19, m3a0a=1, b3a08=2),
    setup('l19b', lvl=19, m3a0a=1, b3a08=1),
    setup('l19c', lvl=19, m3a0a=1, b3a08=3),
    setup('l19d', lvl=19, m3a0a=0, b3a08=1),
    setup('l12', lvl=12, yaw=120.0),
    setup('l25', lvl=25, yaw=-100.0),
    setup('p200', pitch=200.0),
    setup('p80', pitch=80.0),
    setup('p280', pitch=280.0),
    setup('p190', pitch=190.0),
    setup('p350', pitch=350.0),
    setup('p260', pitch=260.0),
    setup('p100', pitch=100.0),
    setup('p170', pitch=170.0),
    setup('p180', pitch=180.0),
    setup('p181', pitch=181.0),
    setup('ym100', yaw=-100.0),
    setup('ym170', yaw=-170.0),
    setup('ym10', yaw=-10.0),
    setup('y120', lvl=12, yaw=120.0, dist=300),
    setup('y10', lvl=12, yaw=10.0),
    setup('y170', lvl=12, yaw=170.0),
    setup('d299', lvl=12, yaw=120.0, dist=299),
    setup('dneg', lvl=12, yaw=120.0, dist=-5),
    setup('c0', count=0),
    setup('c4', count=4, first=0),
    setup('c6', count=6),
    setup('c16', count=16, first=7),
    setup('cneg', count=-4),
    setup('fmt11', loads='80460000;1;80461000;1;80462000;0;80463000;0', count=16),
    setup('mode1b', mode=1, pitch=92.0),
    setup('p95', pitch=95.0),
    setup('cn128', count=-128),
    setup('last1', loads='80460000;1;80461000;0', last=1),
]
print('\n'.join(out))
