#!/usr/bin/env python3
# P156: setups for func_150B8020 (object_break_effects). obj at 0x80460000, model at 0x80470000.
O = 0x80460000; M = 0x80470000
F = {'0': 0, '0.3': 0x3E99999A, '0.5': 0x3F000000, '0.7': 0x3F333333, '1': 0x3F800000, '1.5': 0x3FC00000, '2': 0x40000000}
def setup(name, model=0, sx='0.7', sz='0.7', yaw=0x1234, ret=1, outw='', outa='', spd='2'):
    pk = ['%X=%08X' % (O + 0x1D4, M if model else 0), '%X=%08X' % (O + 0x14C, F[sx]), '%X=%08X' % (O + 0x150, F[sz]),
          '%X=%08X' % (O + 0x74, yaw), '%X=%08X' % (O + 0x3C, F[spd]), '%X=44800000' % (O + 0x14), '%X=42C80000' % (O + 0x18),
          '%X=C3480000' % (O + 0x1C), '%X=12345678' % (O + 0x184)]
    print(' ! '.join([name, '0=%X,1=7,2=3' % O, ','.join(pk), '15046F70=%X' % ret, '', outa, outw, '']))
for m in (0, 1):
    for ret in (0, 1):
        setup('m%d_r%d' % (m, ret), model=m, ret=ret)
for sx, sz in (('0.3', '0.3'), ('1.5', '2'), ('0.5', '1'), ('0.7', '1.5'), ('2', '0.3'), ('0', '0')):
    setup('s_%s_%s' % (sx, sz), sx=sx, sz=sz)
    setup('ms_%s_%s' % (sx, sz), model=1, sx=sx, sz=sz)
for yaw in (0, 0x4000, 0xFF00, 0x8080):
    setup('yaw%X' % yaw, yaw=yaw, spd='1.5')
setup('rad0', outw='1515C7B4=2:0')
setup('rad0_h', outw='1515C7B4=2:0/3:3F800000')
setup('rad_h', outw='1515C7B4=2:40000000/3:3F800000')
setup('mrad0', model=1, outa='15143134=1:3F800000;40000000;40400000')
