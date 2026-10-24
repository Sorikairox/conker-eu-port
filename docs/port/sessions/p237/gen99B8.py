#!/usr/bin/env python3
# P237: setups for func_151B99B8 (searchlight_light_update). Effect E = 80450000 (+0x14 light 80460000, +0x18 object
# 80470000, +0x1C beam 80480000 or NULL, +0x20 scale). func_150A8050 = jal 150A8530 (OUTA: the rotation matrix it
# builds), func_150A7E40 = jal 150A7E40 (OUTW: the transformed lamp point through stack args 4 / 5 / 6).
import struct
def f(x): return struct.unpack('>I', struct.pack('>f', x))[0]
E, L, O, B = 0x80450000, 0x80460000, 0x80470000, 0x80480000
def setup(name, beam=True, scale=2.0, sx=1.5, sy=0.75, pos=(100.0, 200.0, -300.0), out=(130.0, 90.0, -310.0), ang=0.3):
    pk = {E + 0x14: L, E + 0x18: O, E + 0x1C: B if beam else 0, E + 0x20: f(scale), O + 0x170: f(ang), O + 0x18: f(sx),
          O + 0x1C: f(sy), O + 0x38: f(pos[0]), O + 0x3C: f(pos[1]), O + 0x40: f(pos[2]), B + 0x34: f(7.0), B + 0x38: f(8.0)}
    mtx = ';'.join('%X' % f(v) for v in (0.8, 0.1, -0.6, 0.0, 0.2, 0.9, 0.3, 0.0, 0.55, -0.25, 0.7, 0.0, 9.0, 9.0, 9.0, 1.0))
    outa = '150A8530=0:' + mtx
    outw = '150A7E40=4:%X/5:%X/6:%X' % tuple(f(v) for v in out)
    print('%s ! 0=%X ! %s ! ! ! %s ! %s !' % (name, E, ','.join('%08X=%08X' % kv for kv in sorted(pk.items())), outa, outw))
setup('beam')
setup('nobeam', beam=False)
setup('beam_neg', scale=-3.0, out=(-20.0, 500.0, 40.0), sy=2.0)
setup('beam_big', scale=150.0, sx=0.5, sy=3.0, pos=(-1000.0, 30.0, 70.0), out=(-990.5, -120.25, 66.0))
setup('nobeam_far', beam=False, out=(-32000.0, 12345.6, 0.5))
