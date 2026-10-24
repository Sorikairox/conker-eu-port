#!/usr/bin/env python3
# P226: setups for func_1509F4D0 (event_sound_command). ARG 0 = id, 1 = args (VM stack) 80450000, 2 = operand 80460000.
# D_800D3C60 (EU 800D3C60) = sound mode. keys (decoded jal): FB90 1509FB90, F834 1509F834, F95C 1509F95C, F9C8 1509F9C8,
# FA88 1509FA88, FAD4 1509FAD4, FBC8 1509FBC8, func_15103C14 15104194. Values passed to u16 / s16 callee parameters stay
# below 0x8000 (the C call truncates them, the asm passes the word and the callee uses the low half: random DIFFERs
# like `func_1509FBC8: a2 ref=0x805B3330 cand=0x3330` are that artefact).
def setup(name, mode, kind1, kind5=0x1005, a6=0x111, ret=''):
    a = [0x7000, kind1 & 0xFFFFFFFF, 0x1ABC, 0x2345, 0x0456, kind5, a6, 0x0222]
    poke = ','.join(['800D3C60=%08X' % mode] + ['%08X=%08X' % (0x80450000 + 4 * i, v) for i, v in enumerate(a)])
    print('%s ! 0=00012345,1=80450000,2=80460000 ! %s ! %s ! ! ! !' % (name, poke, ret))
R = '1509FB90=5,1509FA88=7,1509FBC8=9,1509F834=12345678,1509F9C8=BEEF'
R0 = '1509FB90=0,1509FA88=0,1509FBC8=0,1509F834=0,1509F9C8=0'
setup('mode1', 1, 0, ret=R)
setup('mode1_zero', 1, 3, ret=R0)
setup('c0_2000', 3, 0, 0x2ABC, ret=R)
setup('c0_3000', 3, 0, 0x3123, ret=R)
setup('c0_4000', 3, 0, 0x4FFF, ret=R)
setup('c0_1000', 3, 0, 0x1005, ret=R)
setup('c0_5000', 3, 0, 0x5005, ret=R0)
setup('c0_0', 3, 0, 0x0F05, ret=R)
setup('c1_m3', 3, 1, ret=R)
setup('c1_m4', 4, 1, ret=R)
setup('c1_m5', 5, 1, ret=R)
setup('c1_m6', 6, 1, ret=R)
setup('c1_zero', 5, 1, ret=R0)
setup('c2_m6', 6, 2, a6=1, ret=R)
setup('c2_m7', 7, 2, a6=1, ret=R)
setup('c2_m7z', 7, 2, a6=0, ret=R)
setup('c3', 3, 3, ret=R)
setup('c3_zero', 3, 3, ret=R0)
setup('c4', 3, 4, ret=R)
setup('c5', 3, 5, ret=R)
setup('cneg', 3, -1, ret=R)
setup('mode0', 0, 1, ret=R)
setup('mode2_c0', 2, 0, 0x2001, ret=R)
setup('c0_a000', 3, 0, 0xA005, ret=R)
setup('c9', 3, 9, ret=R)
