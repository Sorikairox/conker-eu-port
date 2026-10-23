#!/usr/bin/env python3
# P148: setups for func_1513100C (particle_draw_sprite). p 0x80490000, gfx 0x804A0000, view 0, camera 0x80480000.
import struct
def f(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
P = 0x80490000
def setup(name, flags=0, sx=160.0, sy=120.0, inv=0.5, oz=100.0, ret=1, extra=None, w76=0, w74=None, k6c=0, view=0):
    pk = {0x800BEA48: 0x80480000, 0x800BEDE0: 0,  # EU addresses of D_800BE628 / D_800BE9C0
          0x8048001C: f(1.0), 0x80480020: f(1.0), 0x80480024: f(0.0),
          0x80480028: f(240.0), 0x8048002C: f(0.0), 0x80480030: f(320.0), 0x80480044: 0x01000000, 0x8048004C: 0x00200000,
          P + 0x10: 0x00001234, P + 0x14: 0x00000010, P + 0x18: 0x03020000, P + 0x1C: 0x00020000, P + 0x28: 0x000000C8,
          P + 0x2C: 0x00050000, P + 0x38: f(10.0), P + 0x3C: f(8.0), P + 0x40: f(1.0), P + 0x44: f(2.0), P + 0x48: f(3.0),
          P + 0x4C: f(10.0), P + 0x50: f(20.0), P + 0x54: f(30.0), P + 0x68: flags, P + 0x6C: k6c,
          P + 0x74: (0xFF000000 if w74 is None else w74 << 24) | w76 << 8, P + 0x78: 0x00C80000, P + 0x7C: f(20.0),
          0x80470000: 0x00000001}
    pk.update(extra or {})
    pks = ','.join('%08X=%s' % (a, v if isinstance(v, str) else '%08X' % v) for a, v in pk.items())
    rets = '1514525C=%X,1513FA54=804A1000,151430EC=804A2000,15143260=804A3000,15143180=804A4000,15143394=804A5000,1514352C=804A6000,15102D9C=%d' % (ret, 1 if name != 'h74no' else 0)
    outa = '1514525C=1:%s;%s;%s/2:%s/3:%s/4:%s' % (f(sx), f(sy), f(5.0), f(oz), f(1.0), f(inv))
    outb = '151318EC=0:00;80/1:00;40/2:00;20/3:00;FF,1515EDF8=5:11;22;33,15131BBC=0:00;81/1:00;41/2:00;21/3:00;F1/4:00;12/5:00;13/6:00;14/7:00;F5'
    print('%s ! 0=804A0000,1=80490000,2=%X ! %s ! %s ! ! %s ! ! %s' % (name, view, pks, rets, outa, outb))
setup('base'); setup('light', 0x10000); setup('flipS', 0x40); setup('flipT', 0x80); setup('flipST', 0xC0)
setup('offs', 0x1000); setup('max', 0x200000); setup('min', 0x400000); setup('minmax', 0x600000, inv=0.05)
setup('mode3e', 0x800000); setup('f100', 0x100); setup('clipL', sx=10.0); setup('clipLS', 0x40, sx=10.0)
setup('clipT', sy=5.0); setup('clipTT', 0x80, sy=5.0); setup('clipLT', 0xC0, sx=3.0, sy=2.0); setup('clipLT2', sx=3.0, sy=2.0)
setup('cullR', sx=-200.0); setup('cullL', sx=600.0); setup('cullB', sy=-200.0); setup('cullT', sy=500.0)
setup('noproj', ret=0); setup('vm0', 0x40000, w76=0); setup('vm1', 0x40000, w76=1); setup('vm2v1', 0x40000, w76=2, view=1)
setup('h74m1', 0x8000); setup('h74', 0x8000, w74=0); setup('h74no', 0x8000, w74=0)
setup('own0', 0x20000); setup('own1', 0x20000, k6c=0x80470000); setup('own2v1', 0x20000, k6c=0x80470000, view=1)
setup('topm1', sy=67.496); setup('topm1T', 0x80, sy=67.496)
setup('tiny', inv=0.0); setup('all', 0xF191C0); setup('allc', 0xF191C0, sx=3.0, sy=2.0)
