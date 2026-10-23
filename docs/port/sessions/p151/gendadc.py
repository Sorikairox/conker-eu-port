# P151: setups for func_1505DADC. rec = D_800CC2D0[0] (EU 0x800CC6F0), players i at +i*0x32C.
import struct
def fb(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
B = 0x800CC6F0
def setup(name, valid, stunned=(), d2=(500.,), ray=(0,), t=(0.,), skip=0, pitch=0, cone=0x20, dirb=(0, 0), a630=(0,), heading=0, h2=(400.,), dy=(10.,), selfvalid=True):
    pk = []
    for i in range(25):
        a = B + i * 0x32C
        v = i in valid or (i == 0 and selfvalid)
        pk.append('%X=%08X' % (a, 1 if v else 0))
        if v:
            pk += ['%X=00000100' % (a + 0x1C8), '%X=00000040' % (a + 0xF8), '%X=00000100' % (a + 0x2F8),
                   '%X=%08X' % (a + 0x104, 0x01000000 if i in stunned else 0)]
            pk += ['%X=%s' % (a + 0x14 + 4 * k, fb(100. * (i + 1) + 7 * k)) for k in range(3)]
    pk.append('%X=%08X' % (B + 0x78, heading))
    arg = '0=800CC6F0,1=80481000,2=%X,3=%X,4=%X' % (pitch, skip, cone)
    ret = '1505A9B0=%s,150ACEA0=%s' % (';'.join('%X' % x for x in a630), ';'.join('%X' % x for x in ray))
    retf = '1505E2BC=%s' % ';'.join(fb(x) for x in d2)
    outw = '1505E2BC=3:%s/4:%s,150ACEA0=11:%s' % (';'.join(fb(x) for x in h2), ';'.join(fb(x) for x in dy), ';'.join(fb(x) for x in t))
    outb = '1505E2BC=2:%02X;%02X' % dirb
    print(' ! '.join([name, arg, ','.join(pk), ret, retf, '', outw, outb]))
setup('one', [1])
setup('three', [1, 2, 3], d2=(500., 300., 800.))
setup('three_inc', [1, 2, 3], d2=(100., 300., 800.))
setup('far', [1, 2], d2=(2e7, 5e6))
setup('fe_far', [1, 2], d2=(50000., 30000.), skip=0xFE)
setup('fe_near', [1, 2], d2=(50000., 50000.), skip=0xFE)
setup('skip2', [1, 2, 3], d2=(500., 300., 800.), skip=2)
setup('self_skip', [1, 2], d2=(500., 300.), skip=0, selfvalid=False)
setup('stun_pref', [1, 2, 3], stunned=(1,), d2=(100., 300., 50.))
setup('stun_both', [1, 2, 3], stunned=(1, 2), d2=(100., 300., 50.))
setup('stun_late', [1, 2, 3], stunned=(2,), d2=(100., 300., 500.))
setup('ray_block', [1, 2], d2=(500., 300.), ray=(1, 1), t=(10., 30.))
setup('ray_beyond', [1, 2], d2=(500., 300.), ray=(1, 1), t=(30., 10.))
setup('ray_eq', [1, 2], d2=(400., 900.), ray=(1, 0), t=(20., 0.))
setup('cone_out', [1, 2], d2=(500., 300.), dirb=(0x20, 0), cone=0x20)
setup('cone_edge', [1, 2], d2=(500., 300.), dirb=(0x1F, 0xFF), cone=0x20)
setup('cone_neg', [1, 2], d2=(500., 300.), dirb=(0xE0, 0), cone=0x20)
setup('cone_neg2', [1, 2], d2=(500., 300.), dirb=(0xE1, 0), cone=0x20, heading=0)
setup('cone_head', [1, 2], d2=(500., 300.), dirb=(0x10, 0), cone=0x08, heading=0x0C00)
setup('cone_big', [1, 2], d2=(500., 300.), dirb=(0x90, 0), cone=0xC0)
setup('cone0', [1, 2], d2=(500., 300.), cone=0)
setup('cone_hi', [1, 2], d2=(500., 300.), dirb=(0x7F, 0), cone=0x180)
setup('pitch_out', [1, 2], d2=(500., 300.), a630=(0x1000, 0x1100))
setup('pitch_in', [1, 2], d2=(500., 300.), a630=(0x0F00, 0xF000), pitch=0)
setup('pitch_p', [1, 2], d2=(500., 300.), a630=(0x3000, 0x2F00), pitch=0x20)
setup('pitch_lo', [1, 2], d2=(500., 300.), a630=(0xF000, 0xEF00), pitch=0)
setup('pitch_big', [1, 2], d2=(500., 300.), a630=(0x0500, 0x0600), pitch=0x1F5)
setup('h2dy', [1, 2], d2=(500., 300.), h2=(400., 900.), dy=(-30., 50.))
setup('many', list(range(1, 25)), stunned=(3, 7, 11), d2=tuple(float(x) for x in (900, 800, 50, 700, 650, 600, 5, 550, 500, 450, 4, 400, 350, 300, 250, 200, 150, 100, 90, 80, 70, 60, 50, 40)), ray=(0, 1, 0, 1), t=(1., 100., 2., 3.))
setup('eq_init', [1, 2], d2=(1e7, 1e7))
setup('eq_two', [1, 2], d2=(300., 300.))
setup('self_in', [1, 2], d2=(100., 300., 50.), skip=9)
