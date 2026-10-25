#!/usr/bin/env python3
# P300: generates sDABFC.txt (func_150DABFC setups). obj 80480000 (+0x98 data 80478000: +0x40 smoke, +0x44 dust,
# +0x48 spark accumulators), hit 80460000 (+0 object 80430000 (kind +4), +4 dist, +8 pos, +0x44 surface, +0x59 count),
# dir 80450000. EU keys: 150ADF48 func_150ADA68 (RETF), 150ADF00 func_150ADA20 (RET), 151307F0 (RET particle),
# 150475B0, 1515423C, 151541F4, 151DA13C func_151D9B8C, 10023360 memcpy. D_800BE9A4 = EU 800BEDC4 (frame step).
import struct
def f(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
def setup(name, count, kind=0x33, a40=0.0, a44=0.0, a48=0.0, step=1.0, part=0x80420000, rf=(0.5, 0.25, 0.75, 0.125),
          r=(0x12345, 0xFFFFFFFF, 7, 0x81, 0x64, 0xA, 3)):
    pk = ['80480098=80478000', '8048000C=%08X' % 0x07000000, '80480000=%08X' % 0x00090000,
          '80478040=%s' % f(a40), '80478044=%s' % f(a44), '80478048=%s' % f(a48), '800BEDC4=%s' % f(step),
          '80460000=80430000', '80460004=%s' % f(12.5), '80460008=%s' % f(1.5), '8046000C=%s' % f(-2.5), '80460010=%s' % f(3.5),
          '80460044=11223344', '80460048=55667788', '8046004C=99AABBCC', '80460050=DDEEFF01', '80460054=0203A5A5',
          '80460058=%08X' % (0x5A005A5A | (count << 16)), '80430004=%08X' % (kind << 24),
          '80450000=%s' % f(0.6), '80450004=%s' % f(-0.8), '80450008=%s' % f(0.0)]
    ret = '150ADF00=' + ';'.join('%X' % x for x in r) + ',151307F0=%X' % part
    retf = '150ADF48=' + ';'.join(f(x) for x in rf)
    print('%s ! 0=80480000,1=80460000,2=80450000 ! %s ! %s ! %s !  !  !' % (name, ','.join(pk), ret, retf))
setup('none', 0, a40=5, a44=5, a48=5)
setup('spark33', 2, kind=0x33, a48=2.5)
setup('spark3A', 3, kind=0x3A, a48=1.5, part=0)
setup('sparklow', 2, kind=0x3A, a48=0.1)
setup('sparkstep', 2, kind=0x33, a48=0.9, step=4.0, r=(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11))
setup('dustobj', 2, kind=0x10, a44=3.0)
setup('dustobj34', 4, kind=0x34, a44=1.0, step=20.0)
setup('dustwall', 1, a44=3.0, a40=2.0)
setup('wallsmoke', 1, a44=0.0, a40=1.5, r=(0xFFFFFFFF, 0x80000000, 100, 80, 81, 0))
setup('walllow', 1, a44=0.5, a40=0.5)
# survivor setups: distinct D_800A5860 vector (POKE), flag bit 0x40 set then cleared over two sparks
def setup2(name, extra, **k):
    import io, sys, contextlib
    b = io.StringIO()
    with contextlib.redirect_stdout(b): setup(name, **k)
    l = b.getvalue().rstrip('\n').split(' ! '); l[2] += ',' + extra; print(' ! '.join(l))
setup2('dirpoke', '800A5860=3F800000,800A5864=40000000,800A5868=40400000', count=2, kind=0x33, a48=1.5)
setup2('dirpokeobj', '800A5860=3F800000,800A5864=40000000,800A5868=40400000', count=2, kind=0x10, a44=1.5)
setup('flags2', 2, kind=0x33, a48=2.5, r=(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1))
