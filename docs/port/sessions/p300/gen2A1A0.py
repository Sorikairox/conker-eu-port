#!/usr/bin/env python3
# P300: generates s2A1A0.txt (func_1512A1A0 setups). cam 80480000, pad record 80470000 (buttons, stick x, stick y),
# D_800BEA08 (EU 800BEE28) time step. EU keys: 15048050 sinf, 15047EF0 cosf (RETF), 1510ED24 (ARGMEM a2 none: stack buf).
import struct
def f(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
def setup(name, buttons=0, sx=0, sy=0, flags=0, frozen=0, player=1, step=2, yaw=30.0, pitch=10.0, roll=5.0,
          sins=(0.5, 0.25), coss=(0.8660254, 0.9682458, 0.9682458)):
    pk = ['80480368=%08X' % flags, '8048036C=80470000', '8048023C=%08X' % (player << 16),
          '804805F0=%08X' % (0x80000000 if frozen else 0x12345678), '80470000=%04X%02X%02X' % (buttons, sx & 0xFF, sy & 0xFF),
          '800BEE28=%08X' % step, '8048037C=%s' % f(yaw), '80480388=%s' % f(pitch), '804805EC=%s' % f(roll),
          '804802F8=%s' % f(100.5), '804802FC=%s' % f(-20.25), '80480300=%s' % f(300.75)]
    retf = '15048050=%s,15047EF0=%s' % (';'.join(f(x) for x in sins), ';'.join(f(x) for x in coss))
    print('%s ! 0=80480000 ! %s !  ! %s !  !  !' % (name, ','.join(pk), retf))
setup('idle')
setup('frozen', frozen=1, sx=50)
setup('toggle_on', flags=0x400, sx=50, buttons=4)
setup('toggle_off', flags=0x400, frozen=1, sx=-50, sy=60, buttons=0x8000)
setup('stick', sx=5, sy=-5)
setup('stick4', sx=4, sy=-4)
setup('stickm', sx=-80, sy=127, step=3)
setup('stickn', sx=-5, sy=-128)
setup('up', buttons=4)
setup('down', buttons=8 | 0x4000, pitch=89.0)
setup('pitchA', buttons=0x8000, pitch=-89.4)
setup('pitchclamp', buttons=0x4000, pitch=95.0, step=40)
setup('pitchlow', pitch=-95.0, roll=-50.0)
setup('rollR', buttons=0x2000 | 2 | 4, roll=44.0)
setup('rollL', buttons=0x2000 | 1 | 8, roll=-44.0)
setup('rollN', buttons=0x2000 | 0x8000, roll=60.0)
setup('strafeR', buttons=2, sy=100)
setup('strafeL', buttons=1 | 0x4000, sx=-100)
setup('p0', buttons=2 | 4 | 0x8000, player=0, sx=20, sy=20)
setup('p3', buttons=0x2000 | 1 | 4 | 0x4000, player=3, sx=-20, sy=-20, step=7)
# P300 boundary setups for the first mutant run's survivors
setup('sy5', sy=5, sx=-5)
setup('rollnoacc', buttons=0x2000 | 2, roll=10.0)
setup('pitch90', pitch=-90.0)
import subprocess
