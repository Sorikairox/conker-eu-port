#!/usr/bin/env python3
# P207: setups for func_150B1200 (wake_spray_update). fx 0x80450000, obj 0x80460000, owner = objects[3] (0x800CC6F0 + 3 * 0x32C).
import struct
def fb(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
FX, OBJ, OWN, MODE, GR = 0x80450000, 0x80460000, 0x800CC6F0 + 3 * 0x32C, 0x80470000, 0x80480000
def setup(name, alive=1, idmatch=1, mode=2, ospeed=30.0, wspeed=1.0, acc=0.5, dt=2.0, ground=1, ada68=(0.5,), ada20=(7,), r3low=False):
    pk = {FX + 0x0: 0x00090000, FX + 0xC: 0x04000000, FX + 0x28: OBJ, FX + 0x2C: 0x2A000000 if idmatch else 0x2B000000,
          FX + 0x30: fb(acc), OBJ + 0x0: 0x11 if alive else 0, OBJ + 0x38: 0x0000002A, OBJ + 0x124: 0x03000000,
          OBJ + 0x3C: fb(ospeed), OBJ + 0x40: fb(5.0), OWN + 0x31C: MODE, OWN + 0x44: fb(wspeed), MODE + 0x4C: mode,
          0x800BEDC4: fb(dt), GR: fb(1000.3), GR + 4: fb(-7.0), GR + 8: fb(-11.0), 0x800A5860: 0, 0x800A5864: 0, 0x800A5868: 0}
    poke = ','.join('%08X=%s' % (a, v if isinstance(v, str) else '%08X' % v) for a, v in sorted(pk.items()))
    ret = '1515C668=%d,150ADF00=%s' % (ground, ';'.join('%X' % v for v in ada20))
    vals = list(ada68)
    if r3low: vals = [v if i % 4 != 0 or i == 0 else 0.01 for i, v in enumerate(vals)]
    retf = '150ADF48=%s,15143CAC=0' % ';'.join(fb(v) for v in vals)
    outa = '150B0F40=4:%s;%s;%s,15143D04=3:%s;%s;%s' % (fb(100.0), fb(20.0), fb(-50.0), fb(1.5), fb(9.0), fb(-2.5))
    outw = '1514373C=2:%s/3:%s,1515C668=1:%08X' % (fb(0.6), fb(0.8), GR)
    outw = outw.replace('1514373C', '15143CAC')
    outb = '150B0F40=5:FF;C0'
    return '%s ! 0=%X ! %s ! %s ! %s ! %s ! %s ! %s' % (name, FX, poke, ret, retf, outa, outw, outb)
rows = [
 setup('dead', alive=0), setup('mode3', mode=3), setup('objfast', ospeed=30.0, wspeed=1.0), setup('reused', idmatch=0), setup('mode1', mode=1), setup('slow', ospeed=20.0, wspeed=10.0),
 setup('eq26', ospeed=26.0, wspeed=1.0), setup('boost', ospeed=10.0, wspeed=25.0), setup('boost_eq', ospeed=10.0, wspeed=26.0 / 1.35),
 setup('one', acc=0.0, dt=0.8, ada68=(0.1, 0.3, 0.7, 0.2, 0.9)), setup('none', acc=0.0, dt=0.3, ada68=(0.1,)),
 setup('exact1', acc=0.0, dt=1.0 / 1.2590001, ada68=(0.0,)),
 setup('multi', acc=0.5, dt=2.0, ada68=(0.5, 0.25, 0.75, 0.125, 0.03, 0.9, 0.6, 0.4, 0.2, 0.8), ada20=(7, 100, 2000, 0xFFFFFFFF, 25, 26, 101)),
 setup('noground', ground=0, ada68=(0.5, 0.3, 0.6, 0.2, 0.01)),
 setup('r3low', ada68=(0.5, 0.3, 0.6, 0.2, 0.01), ada20=(0x29, 20, 0x64)),
 setup('r3eq', ada68=(0.5, 0.3, 0.6, 0.2, 0.044000003), ada20=(0x28, 21, 0x65)),
]
print('# P207 func_150B1200 setups (gen_1200.py); run with DIFFTEST_ROMDATA=1 DIFFTEST_ARGMEM=151D95C4=0:12,151D95C4=1:12,150B0F40=2:8,150B0F40=3:8')
print('\n'.join(rows))
