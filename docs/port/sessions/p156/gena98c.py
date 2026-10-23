#!/usr/bin/env python3
# P156: setups for func_1510A98C (vent_smoke_emitter_update). emitter 0x80480000, owner 0x80460000, model 0x80470000.
# D_800BE9A4 (frame scale) EU 0x800BEDC4. RETF 150ADF48 = func_150ADA68's f0.
E = 0x80480000; O = 0x80460000; M = 0x80470000
def setup(name, st=1, uid=5, ouid=5, model=1, accum=0x3F000000, rate=0x3F800000, rr=0x3F000000, dt=0x3F800000, retf='', ret=''):
    pk = ['%X=%08X' % (E + 0x28, O), '%X=%08X' % (E + 0x2C, uid << 24), '%X=%08X' % (E + 0x30, accum), '%X=%08X' % (E + 0x34, rate),
          '%X=%08X' % (E + 0x38, rr), '%X=%08X' % (E + 0xC, 0x07AB1234), '%X=%08X' % (E, 0x00330000), '%X=%08X' % (O, st),
          '%X=%08X' % (O + 0x38, ouid), '%X=%08X' % (O + 0x1D4, M if model else 0), '800BEDC4=%08X' % dt]
    print(' ! '.join([name, '0=%X' % E, ','.join(pk), ret, retf, '', '', '']))
setup('dead', st=0)
setup('uid', ouid=6)
setup('uid_dead', st=0, ouid=6)
setup('below', accum=0, rate=0x3E800000, rr=0, retf='150ADF48=3F000000')
setup('one', accum=0x3E800000, rate=0x3F800000, rr=0, retf='150ADF48=3F000000')
setup('three', accum=0x40200000, retf='150ADF48=3F000000;3E800000;3F400000;0;3F7FFFFF')
setup('nomodel', model=0, accum=0x40200000)
setup('nomodel_lo', model=0, accum=0)
for i, r in enumerate(('0', '1', '2', '3', 'FFFFFFFF', '5', 'A', 'F')):
    setup('rnd%d' % i, accum=0x40000000, ret='150ADF00=%s' % r, retf='150ADF48=3F19999A;3E4CCCCD')
setup('dt2', accum=0x3F000000, dt=0x40000000, retf='150ADF48=3F800000')
setup('neg', st=-1, accum=0x40800000)
