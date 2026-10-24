#!/usr/bin/env python3
# P188: setups for func_15177410 (model_light_create). allocate_memory (jal 10003E90) returns heap blocks in turn,
# func_151149AC (jal 15114F2C) the model 80450000 (origin +0x10.., count u16 +0x16, vertices +0x28 -> 80460000).
# EU data: D_800DD410 list = 800DD830, D_800DD418 count byte = 800DD838.
import struct
def fb(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
def setup(name, flags=0, lid=7, pos=(100, -50, 300), ang=30.0, rng=15000, inten=80.0, a8=77, sc=15, cnt=5,
          lights=(), alloc='80400000;80410000;80420000;80430000', org=(10, 20, -30)):
    p = {0x80450010: ((org[0] & 0xFFFF) << 16) | (org[1] & 0xFFFF), 0x80450014: ((org[2] & 0xFFFF) << 16) | cnt,
         0x80450028: 0x80460000, 0x800DD838: len(lights) << 24}
    for j, l in enumerate(lights):
        p[0x800DD830 + 4 * j] = 0x80470000 + 0x100 * j
        p[0x80470000 + 0x100 * j] = l << 24
    pk = ','.join('%08X=%08X' % kv for kv in p.items())
    arg = '0=%X,1=%X,2=%X,3=%X,4=%X,5=%s,6=%X,7=%s,8=%X,9=%X,10=11,11=22,12=33,13=44,14=55,15=66' % (
        flags, lid, pos[0] & 0xFFFFFFFF, pos[1] & 0xFFFFFFFF, pos[2] & 0xFFFFFFFF, fb(ang), rng, fb(inten),
        a8 & 0xFFFFFFFF, sc & 0xFFFFFFFF)
    return '%s ! %s ! %s ! 10003E90=%s,15114F2C=80450000 ! 15048790=3F000000;BF000000;3F99999A;C0000000;40400000 ! ! !' % (name, arg, pk, alloc)
out = [
    setup('f0'), setup('f1', flags=1), setup('f2', flags=2), setup('f4', flags=4), setup('f6', flags=6),
    setup('f12', flags=0x12), setup('f16', flags=0x16), setup('f15', flags=0x15), setup('f14', flags=0x14),
    setup('fE3', flags=0xE3), setup('r0', flags=4, rng=0), setup('rsm', flags=6, rng=300),
    setup('rsm16', flags=0x16, rng=300, ang=-200.0), setup('angneg', flags=0x12, ang=-0.5),
    setup('angbig', flags=0x12, ang=400.0), setup('neg', flags=6, sc=-3, a8=-5),
    setup('same', flags=2, lights=(7,)), setup('other', flags=2, lights=(9,)), setup('two', flags=2, lights=(9, 7)),
    setup('cnt0', flags=6, cnt=0), setup('cnt1', flags=0x16, cnt=1), setup('null', alloc='0'),
    setup('o0', flags=6, org=(100, -50, 300)),
    setup('f8', flags=0x0A),
]
print('\n'.join(out))
