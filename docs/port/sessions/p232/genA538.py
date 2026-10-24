#!/usr/bin/env python3
# P232: setups for func_1510A538 (segment_effect_update). ARG 0 = effect 80450000: +0x28 owner (80460000), +0x2C
# accumulator, +0x30 rate, +0x34 end handler (s8; D_80089000[0] is NULL in the ROM, so only -1 is used here),
# +0x35 point handler (s8; D_80089004 = {func_15109DC8, func_1510A1A0}). D_800BE9A4 = EU 800BEDC4 (frame step);
# D_800A28EC = 351.86 (ROM). Callees: func_150ADA68 150ADF48 (RETF: weight pick, lerp, lerp per unit),
# func_150A7E40 (OUTW a4..a6 = stack args 4..6), func_15114E8C, func_15145698 (= func_15145128).
import struct
def f(v): return struct.unpack('>I', struct.pack('>f', v))[0]
def setup(name, acc, rate=0.0, ph=0, eh=-1, step=1.0, rnd=(0.0, 0.5, 0.25)):
    pk = '80450028=80460000,8045002C=%08X,80450030=%08X,80450034=%02X%02X0000,800BEDC4=%08X' % (
        f(acc), f(rate), eh & 0xFF, ph & 0xFF, f(step))
    retf = '150ADF48=' + ';'.join('%X' % f(r) for r in rnd)
    outw = '150A7E40=4:%X;%X;%X;%X/5:%X;%X;%X;%X/6:%X;%X;%X;%X' % tuple(
        f(v) for v in (1.0, 2.0, 3.0, 4.0, 10.0, 20.0, 30.0, 40.0, -5.0, 6.5, 7.25, -8.0))
    print('%s ! 0=80450000 ! %s ! ! %s ! ! %s ! !' % (name, pk, retf, outw))
setup('none', 0.5)
setup('one_h0', 1.5)
setup('one_h1', 1.5, ph=1)
setup('three_h0', 3.25, rnd=(0.0, 0.5, 0.25, 0.5, 0.1, 0.9, 0.99, 0.3, 0.7))
setup('exact1', 1.0)
setup('rate', 0.5, rate=0.01, step=0.5)
setup('rate_neg', 2.5, rate=-0.002, step=2.0)
setup('noh_drop', 3.5, ph=-1)
setup('noh_rate', 0.25, ph=-1, rate=0.01)
setup('pick2', 1.5, rnd=(0.5, 0.75, 0.6))
setup('pick5', 1.5, rnd=(0.99, 0.2, 0.8))
setup('pick1', 1.5, rnd=(0.45, 0.0, 1.0))
setup('pick_eq', 1.5, rnd=(138.29312133789062 / 351.8638916015625, 0.5, 0.5))
# tie: after the first segment the remaining weight equals segment 1's (rand bits 3EE8108B, searched in f32)
setup('pick_tie', 1.5, rnd=(struct.unpack('>f', bytes.fromhex('3EE8108B'))[0], 0.5, 0.5))
