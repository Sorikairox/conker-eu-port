#!/usr/bin/env python3
# P300: generates sD99AC.txt (func_150D99AC setups). obj 80480000, points 80470000 (0x24 each), data 80478000,
# owner 80440000 (or a D_800CC2D0 slot, EU 800CC6F0), hit object 80430000. EU keys: 151443D4 func_15143E64 (RETF
# segment lengths), 15081A90 (OUTA 7 = hit record words 0..0x5B), 150DABFC, 15144A98 func_15144528 (RETF),
# 15048790 func_150484A0 (RETF), 1505A5D0 func_1505A250, 1505D3D0 func_1505D024, 1000FC0C func_1000F91C.
import struct
def f(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
def pts(n):
    p = []
    for i in range(n):
        b = 0x80470000 + i * 0x24
        p += ['%X=%s' % (b, f(100.0 * i + 3.25)), '%X=%s' % (b + 4, f(50.0 - 7.5 * i)), '%X=%s' % (b + 8, f(-20.0 * i - 1.5)),
              '%X=%s' % (b + 0x18, f(9.0)), '%X=%08X' % (b + 0x1C, 0x11000000), '%X=%s' % (b + 0x20, f(0.5))]
    return p
def hit(count, obj=0x80430000, dist=33.5, pos=(11.0, -22.0, 44.5)):
    w = ['%08X' % obj, f(dist), f(pos[0]), f(pos[1]), f(pos[2])] + ['%08X' % (0x01010101 * (i + 5)) for i in range(17)]
    w.append('%08X' % ((count << 16) | 0x5A5A))
    return '15081A90=7:' + ';'.join(w)
def setup(name, lens, cnt=6, n=6, tail=1, head=0, flags=0, hitc=0, kind=0x3A, s232=0, s251=0, s125=0, sound=0,
          owner=0x80440000, ret44=None):
    pk = ['8048001C=%08X' % flags, '80480024=%08X' % (cnt << 16), '8048002C=%02X%02X%02X00' % (n & 0xFF, tail, head),
          '80480094=80470000', '80480098=80478000', '80478000=%08X' % owner, '80478030=%08X' % (sound << 16),
          '80478038=%s' % f(1234.5), '80480010=%s' % f(-60.0), '80480014=%s' % f(70.0), '80480018=%s' % f(15.0),
          '80430004=%08X' % (kind << 24), '80430230=%08X' % (s232 << 8), '80430250=%08X' % (s251 << 16),
          '80430124=%08X' % (s125 << 16), '8043003C=%s' % f(2.0), '80430014=%s' % f(5.0), '8043001C=%s' % f(-9.0),
          '80440014=%s' % f(-3.0), '8044001C=%s' % f(8.0)] + pts(cnt)
    retf = ['151443D4=' + ';'.join(f(x) for x in lens), '15144A98=' + (ret44 or ';'.join(f(x) for x in (300.5, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0))),
            '15048790=' + f(1.5707964)]
    print('%s ! 0=80480000 ! %s !  ! %s ! %s !  !' % (name, ','.join(pk), ','.join(retf), hit(hitc)))
setup('nohit', [100, 200, 300, 400])
setup('cut', [500, 500, 500, 400], tail=0)
setup('cutzero', [500, 800, 0, 400], tail=0)
setup('zero', [0, 100, 0, 50])
setup('live', [100, 200, 300, 400, 10], flags=2, head=3, tail=4)
setup('few', [100], n=1)
setup('h3A', [100, 200, 300, 400], hitc=2, kind=0x3A, sound=0x123)
setup('h10p', [100, 200, 300, 400], hitc=2, kind=0x10, s251=1, s232=0xF)
setup('h10p2', [100, 200, 300, 400], hitc=3, kind=0x10, s251=1, s232=0xE)
setup('h10a', [100, 200, 300, 400], hitc=2, kind=0x10, s232=0x10)
setup('h10b', [100, 200, 300, 400], hitc=2, kind=0x10, s232=5, s125=1)
setup('h91', [100, 200, 300, 400], hitc=2, kind=0x91)
setup('h90', [100, 200, 300, 400], hitc=2, kind=0x90)
setup('hdmg', [100, 200, 300, 400], hitc=2, kind=0x22, owner=0x800CC6F0 + 2 * 0x32C)
setup('hdmg2', [900, 200, 300, 400], hitc=4, kind=0x23, owner=0x800CC6F0 + 5 * 0x32C, sound=0xFFFF)
setup('h1', [100, 200, 300, 400], hitc=1, sound=7)
setup('cuthit', [700, 800, 100, 400], hitc=2, kind=0x91, tail=0, cnt=8, n=7, head=6)
setup('fadeall', [10, 20, 30, 40], cnt=5, n=5, tail=0, head=0)
# boundary setups for the first mutant run's survivors
setup('n2', [100], n=2, head=0, tail=4)
setup('near', [400, 400, 350, 10])
setup('wrap', [1300, 10, 10, 10], head=3, tail=4)
setup('h10p251', [100, 200, 300, 400], hitc=2, kind=0x10, s251=2, s232=0xF)
setup('fade', [100, 100, 77, 79])  # sum 9 + 100 + 100 + 77 = 286 is 0.49 past fade (0.802 * 356)
