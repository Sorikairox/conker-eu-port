# P151: setups for func_1000A420. Keys: func_150ADE40 150ADE40, func_150AD9A0 150ADE80, func_150487E0 15048AD0.
import struct
def fb(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
def h(v): return '%X' % (v & 0xFFFFFFFF)
def setup(name, dist=0x500, planar=False, outer=0x1000, inner=0x100, dx=300, dz=-200, yaw=0., acos=1.0, near2=100,
          pan=True, vol=True, od=True):
    args = [dx, 7, dz, None, 11, 12, 13, outer | (0x8000 if planar else 0), inner,
            0x80481000 if pan else 0, 0x80481010 if vol else 0, 0x80481020 if od else 0]
    a = ','.join('%d=%s' % (i, fb(yaw) if v is None else h(v)) for i, v in enumerate(args))
    ret = '150ADE40=%s,150ADE80=%s' % ((h(dist) + ';' + h(near2)) if planar else h(near2), h(dist))
    print(' ! '.join([name, a, '80481000=AAAAAAAA,80481010=BBBBBBBB,80481020=CCCCCCCC', ret, '15048AD0=' + fb(acos), '', '', '']))
for d in (0x80, 0x100, 0x500, 0xE00, 0xF30, 0xF33, 0xF34, 0xFF0, 0x1000, 0x2000):
    setup('d%x' % d, dist=d); setup('p%x' % d, dist=d, planar=True)
setup('nopan', pan=False); setup('nodist', od=False); setup('nopan_lo', pan=False, dist=0xFF0)
for n2 in (0, 30, 31, 32):
    setup('n2_%d' % n2, near2=n2)
for dx, dz in ((300, -200), (0, 0), (0, 5), (-300, 400), (1, 0), (0, 1)):
    for ac in (0.0, 0.5, 1.2, 1.5707964, 2.0, 3.1, -0.7):
        for yaw in (0., 30., 45., -45., 80., -100., 135., 170., -170., 300., -400.):
            setup('a_%d_%d_%g_%g' % (dx, dz, ac, yaw), dx=dx, dz=dz, acos=ac, yaw=yaw)
for d in (0x6F6E, 0x6F6F, 0x6FC1):
    setup('t%x' % d, dist=d, outer=0x7100, inner=-0xF00)
