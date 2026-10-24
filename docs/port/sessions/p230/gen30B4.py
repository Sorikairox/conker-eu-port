#!/usr/bin/env python3
# P230: setups for func_150130B4 (record_particle_emitter_start). ARG 0 = record 80450000.
# Keys (decoded jal words): func_150A8050 150A8530, func_150A7E40 150A7E40 (OUTW the rotated point through stack
# args 4..6), func_1510F800 1510FD80, func_1510FD20 151102A0 (RET sound handle), func_151407D0 15140D40 (RET emitter),
# func_151149AC 15114F2C (RET object 80480000, s16 x / y / z at +0x10), memcpy 10023360.
import struct
def fb(f): return struct.unpack('>I', struct.pack('>f', f))[0]
def setup(name, typ=1, idx=0, rgb=(0x11, 0x22, 0x33), opts=(0, 0, 0x80, 0x40), pos=(100, -20, 300), rng=(50, 70),
          ang=(0.5, 1.25), fl16=0x10, emit=0x80460000, obj=0x80480000, opos=(-7, 9, 1234), snd=0x1234, pt=(10.0, -20.0, 30.0)):
    m = {}
    def w(a, v): m[a] = v & 0xFFFFFFFF
    w(0x80450000, (pos[0] & 0xFFFF) << 16 | (pos[1] & 0xFFFF)); w(0x80450004, (pos[2] & 0xFFFF) << 16 | (rng[0] & 0xFFFF))
    w(0x80450008, (rng[1] & 0xFFFF) << 16 | 0x5555); w(0x8045000C, fb(ang[0])); w(0x80450010, fb(ang[1]))
    w(0x80450014, 0x77770077 | fl16 << 8); w(0x80450018, idx << 24 | rgb[2] << 16 | rgb[1] << 8 | rgb[0])
    w(0x8045001C, typ); w(0x80450020, opts[0] << 24 | opts[1] << 16 | opts[2] << 8 | opts[3])
    w(0x80480010, (opos[0] & 0xFFFF) << 16 | (opos[1] & 0xFFFF)); w(0x80480014, (opos[2] & 0xFFFF) << 16)
    pk = ','.join('%08X=%08X' % kv for kv in sorted(m.items()))
    ret = '15140D40=%X,15114F2C=%X,151102A0=%X' % (emit, obj, snd)
    outw = '150A7E40=4:%08X/5:%08X/6:%08X' % (fb(pt[0]), fb(pt[1]), fb(pt[2]))
    print('%s ! 0=80450000 ! %s ! %s ! ! ! %s !' % (name, pk, ret, outw))
for t in range(0, 21):
    setup('t%d' % t, typ=t)
for t in (1, 5, 8, 9, 13, 18, 19):
    setup('t%d_snd' % t, typ=t, opts=(1, 0, 0x80, 0x40))
for t in (2, 6, 8, 11, 14, 19):
    setup('t%d_f16' % t, typ=t, opts=(0, 3, 0xFF, 0))
setup('t8_null', typ=8, emit=0)
setup('t13_null', typ=13, emit=0)
setup('t15_noobj', typ=15, obj=0)
setup('t16_noobj_snd', typ=16, obj=0, opts=(0x80, 1, 0, 0))
for i in range(1, 5):
    setup('idx%d' % i, typ=3, idx=i, rgb=(0xF0, 0x0F, 0xAA))
setup('snd_neg', typ=7, opts=(0xFF, 0xFF, 0xFF, 0xFF), pos=(-1000, 5, -32000))
setup('big_t', typ=0x7FFFFFFF)
setup('neg_t', typ=-3)
setup('fl16_4', typ=4, fl16=0xFB)
