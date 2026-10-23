# P151: setups for func_100114D0. D_80082FA0 = 0x80083330, listeners D_80042308 (0x1C each), func_1000A420 jal 1000A710.
import struct
def fb(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
def h(v): return '%X' % (v & 0xFFFFFFFF)
def setup(name, n, ears, src=(100, 20, -50), gain=0x4000, vol=0x6000, ret=0x321):
    pk = ['80083330=%s' % h(n)]
    for i, e in enumerate(ears):
        b = 0x80042308 + 0x1C * i
        vals = [e[0] + 3, e[1] - 2, e[2] + 1, e[0], e[1], e[2]]
        pk += ['%X=%s' % (b + 4 * k, h(v)) for k, v in enumerate(vals)] + ['%X=%s' % (b + 0x18, fb(10. * i + 1))]
    a = '0=%s,1=%s,2=%s,3=%s,4=1000,5=100,6=80481000,7=80481010,8=80481020' % (h(src[0]), h(src[1]), h(src[2]), h(gain))
    print(' ! '.join([name, a, ','.join(pk), '1000A710=%s' % h(ret), '', '', '1000A710=10:%s' % h(vol), '']))
E = [(0, 0, 0), (90, 10, -40), (-500, 0, 0), (100, 20, -51), (5000, 0, 0)]
setup('n0', 0, E)
setup('n1', 1, E)
setup('n1b', 1, [(100, 20, -50), (0, 0, 0)])
setup('n2', 2, E)
setup('n3', 3, E)
setup('n4', 4, E)
setup('n4far', 4, E, src=(-3000, 0, 9000))
setup('tie', 2, [(0, 0, 0), (0, 0, 0), (0, 0, 0)])
setup('tie2', 2, [(10, 0, 0), (-10, 0, 0), (0, 10, 0)], src=(0, 0, 0))
setup('gain', 0, E, gain=0x8000, vol=0x7FFF)
setup('gainneg', 0, E, gain=0xFFFFFFFF, vol=0x7FFF)
setup('gainbig', 0, E, gain=0x30000, vol=0x7000)
setup('huge', 1, [(0x10000, 0, 0), (0x20000, 0, 0)], src=(0, 0, 0))
setup('big1', 1, [(47000, 0, 0), (1000, 0, 0)], src=(0, 0, 0))
setup('big2', 1, [(48000, 0, 0), (47000, 0, 0)], src=(0, 0, 0))
