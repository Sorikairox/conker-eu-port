#!/usr/bin/env python3
# P227: setups for func_1509D590 (event_effect_command, D_800887C0 handler 14). ARG 0 = id, 1 = args 80450000,
# 2 = operand 80460000. Object lookups func_1505EEF4 (jal 1505F2A0) return 80470000 (x / y / z at +0x14 / +0x18 /
# +0x1C) or 0. Other keys = their names (decoded jal), except func_15083E90 150842F8, func_15136C3C 151371AC,
# func_151616D0 15161C40, func_15163A60 15163FD0, func_1000E7A0 1000EA90. ARGMEM (registry knob) compares the hit
# record, position and direction passed to func_151C0434 / func_151C0648 / func_150DF240.
import struct
def fb(f): return '%08X' % struct.unpack('>I', struct.pack('>f', f))[0]
ARGS = [0x7000, 0x1123, 0x00020005, 0x0003FFF6, 0x2456, 0x0000FF07, 0x66, 0x77, 0x88, 0x99]
def setup(name, id, args=ARGS, obj='80470000', ret=''):
    pk = ['%08X=%08X' % (0x80450000 + 4 * i, v & 0xFFFFFFFF) for i, v in enumerate(args)]
    pk += ['80470014=%s' % fb(12.5), '80470018=%s' % fb(-3.0), '8047001C=%s' % fb(1000.0)]
    r = '1505F2A0=%s' % obj + (',' + ret if ret else '')
    print('%s ! 0=%08X,1=80450000,2=80460000 ! %s ! %s ! ! ! !' % (name, id & 0xFFFFFFFF, ','.join(pk), r))
for c in (0, 1, 2, 3, 0xF, 0x10, 0x12, 0x13, 0x14, 0x16, 0x17, 0x1B, 0x20, 0x23, 0x24, 0x25, 0x2A, 0x2B, 0x2C,
          0x2E, 0x2F, 0x30, 0x31, 0x33):
    setup('c%02X' % c, c, ret='150F7364=80490000')
for c in (0x21, 0x24, 0x2A, 0x2E, 0x2F, 0x5):
    setup('c%02X_null' % c, c, obj='0')
for c in (8, 0xE, 0x11, 0x15, 0x19, 0x26, 0x32, 0x34, 0x7FFF, -1):
    setup('gap%X' % (c & 0xFFFF), c)
setup('c04', 4, ret='150E3788=5')
setup('c04_zero', 4, ret='150E3788=0')
setup('c04_big', 4, ret='150E3788=03FFFFFF')
setup('c05', 5, ret='150E3850=7')
setup('c05_zero', 5, ret='150E3850=0')
setup('c06', 6, ret='150E3994=9')
setup('c06_zero', 6, ret='150E3994=0')
setup('c07_999', 7, args=[0x7000, 999, -40, 70, 123456, 1, 2, 3, 4, 5])
setup('c07_other', 7, args=[0x7000, 0x1234, 1, 2, 3, 4, 5, 6, 7, 8])
setup('c07_998', 7, args=[0x7000, 998, 1, 2, 3, 4, 5, 6, 7, 8])
setup('c18', 0x18, args=[0x7000, 0x1203, 0, 0x0001FFFE, 1, 2, 3, 4, 5, 6])
setup('c21', 0x21)
setup('c22_hit', 0x22, args=[0x7000, -1234, 5678, 1, 2, 3, 4, 5, 6, 7], ret='15046F70=1')
setup('c22_miss', 0x22, args=[0x7000, 1234, -5678, 1, 2, 3, 4, 5, 6, 7], ret='15046F70=0')
setup('gap10001', 0x10001)
