#!/usr/bin/env python3
# P95: knob setups for func_15035220 (mirrored draw matrices + entry alpha). Args: 0 obj, 1 e, 2 mode, 3 model, 4 mtx,
# 5 nmtx, 6 a, 7 b, 8 c, 9 d, 10 f, 11 x, 12 y, 13 z, 14 g, 15 h, 16 alpha, 17 fixed, 18 tofixed (floats as bits).
import struct
fb = lambda v: '%08X' % struct.unpack('>I', struct.pack('>f', v))[0]
def setup(name, mode=1, y=150.0, nmtx=2, fixed=0, tof=0, obj=True, u9c=1, dist=100, alpha=200.0, g=20.0, h=300.0):
    a = {0: 0x80450000 if obj else 0, 1: 0x804B0000, 2: mode, 3: 0x80460000, 4: 0x80470000, 5: nmtx}
    f = {6: 100.0, 7: 50.0, 8: 200.0, 9: 7.0, 10: 0.5, 11: 120.0, 12: y, 13: 210.0, 14: g, 15: h, 16: alpha}
    args = ','.join('%d=%X' % kv for kv in a.items()) + ',' + ','.join('%d=%s' % (k, fb(v)) for k, v in f.items())
    args += ',17=%X,18=%X' % (fixed, tof)
    p = {0x8045009C: u9c, 0x804501D4: 0x80455550}
    for i in range(2):   # src matrices: identity-ish with a translation
        base = 0x80460000 + i * 0x40
        for k in range(16):
            p[base + 4 * k] = int(fb([1.0, 0.25, 0.0, 3.0][k % 4] if k < 12 else [10.0 + i, 60.0, -30.0, 2.0][k - 12]), 16)
    poke = ','.join('%08X=%08X' % kv for kv in p.items())
    print('%s ! %s ! %s ! 150ADE40=%X !  !  !  ! ' % (name, args, poke, dist))
for m in (0, 1):
    setup('m%d_far' % m, mode=m, y=400.0)
    setup('m%d_near5' % m, mode=m, y=55.0)
    setup('m%d_near15' % m, mode=m, y=65.0)
    setup('m%d_lin' % m, mode=m, y=150.0)
    setup('m%d_neg20' % m, mode=m, y=30.0)
    setup('m%d_negh' % m, mode=m, y=49.5)
    setup('m%d_fixed' % m, mode=m, fixed=1, tof=1)
    setup('m%d_tof' % m, mode=m, tof=1)
setup('m0_alphafrac', mode=0, y=150.0, alpha=200.7)
setup('m1_nm0', mode=1, nmtx=0)
setup('m1_noobj', mode=1, obj=False)
setup('m1_u9c0', mode=1, u9c=0)
setup('m2_far', mode=2, dist=400)
setup('m2_near', mode=2, dist=10)
setup('m2_lin', mode=2, dist=100)
setup('m2_fixed', mode=2, fixed=1, tof=1)
setup('m2_tof', mode=2, tof=1)
setup('m2_nm1', mode=2, nmtx=1, fixed=1)
setup('m3', mode=3)
setup('m3_noobj', mode=7, obj=False)
setup('m1_hedge', mode=1, y=70.5, g=20.0, h=21.0)
setup('m1_gedge', mode=1, y=75.0)
