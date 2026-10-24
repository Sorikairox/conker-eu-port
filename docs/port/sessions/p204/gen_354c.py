#!/usr/bin/env python3
# P204: setups for func_1518354C (water_wave_push). pl 80450000; D_800DE284 bytes (kind per water); D_800DE290[w] ->
# 80460000 (12-byte samples); D_800DBEF4 (EU 800DC324) -> 80470000 (0xA0 per model); OUTW ox / oz of func_150A7E40
# (args 4 / 6); RETF func_151834C8 = own slot (float). Water types D_8008D3F0 from the ROM (DIFFTEST_ROMDATA=1).
import struct
def F(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
def g(name, u28=0.0, y=50.0, x=300.0, z=400.0, kind=0, water=1, slot=5, own=5.7, ox=10.0, oz=-10.0, samp=160.0,
      mh=40, mx=100, mz=200, model1=False):
    p = ['800DE284=%02X%02X%02X%02X' % (kind, kind, kind, kind), '800DE290=80460000', '800DE294=80460000',
         '800DC324=80470000',
         '80450014=' + F(x), '80450018=' + F(y), '8045001C=' + F(z), '80450028=' + F(u28)]
    p.append('%08X=%s' % (0x80460000 + slot * 12 + 8, F(samp)))
    for m in (0, 1):
        b = 0x80470000 + m * 0xA0
        p.append('%08X=%04X%04X' % (b + 0x10, mx & 0xFFFF, (mh + 7 * m) & 0xFFFF))
        p.append('%08X=%04X0000' % (b + 0x14, mz & 0xFFFF))
    print('%s ! 0=80450000,1=%X,2=%X ! %s ! ! 151834C8=%s ! ! 150A7E40=4:%s/6:%s ! ' % (name, slot & 0xFFFFFFFF, water,
          ','.join(p), F(own), F(ox), F(oz)))
print('# P204 func_1518354C setups (gen_354c.py); run with DIFFTEST_ROMDATA=1')
g('hit')
g('hit_k1', kind=1)
g('hit_k2', kind=2)
g('hit_w0', water=0)
g('rise3', u28=3.0)
g('rise35', u28=3.5)
g('rise_neg', u28=-20.0)
g('above', y=50.0 + 10 + 40 + 301)
g('above_eq', y=10.0 + 40 + 300)
g('below', y=10.0 + 40 - 301)
g('below_eq', y=10.0 + 40 - 300)
g('samp_neg', samp=-4000.0, y=-200.0)
g('oz_pos', oz=0.5)
g('oz_zero', oz=0.0)
g('oz_lim', oz=-672.0)
g('oz_out', oz=-672.5)
g('ox_neg', ox=-0.5)
g('ox_zero', ox=0.0)
g('ox_lim', ox=209.0)
g('ox_out', ox=209.5)
g('k2_ox', kind=2, ox=375.0, oz=-2368.0)
g('k2_out', kind=2, ox=376.0)
g('own_p1', own=6.2)
g('own_m1', own=4.9)
g('own_p2', own=7.0)
g('own_m2', own=3.0)
g('slot0', slot=0, own=0.3)
g('slot0_1', slot=0, own=1.0)
g('slot39', slot=39, own=38.0)
