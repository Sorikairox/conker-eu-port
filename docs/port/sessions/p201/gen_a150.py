# P201: setups for func_150CA150 landing_dust_burst (obj 0x80410000). jal keys (EU): ground 15046F70, hit init 1504744C,
# rumble 1512DCB8, colour 150CD2A0, shake 151D59B4, ring 150C8DD0, sin 15142948, randf 150ADF48, rng 150ADF00,
# puff 1513CB20, 150CAE30, spray 1514CBE8. D_800BEE08 = 800BEE08 (player).
import sys, struct
def fb(x): return struct.unpack('>I', struct.pack('>f', x))[0]
O = 0x80410000
R = []
def add(name, x=10.0, y=20.0, z=-30.0, floor=-55.0, yaw=0x1234, player=0, ground=1, hity=-40.0, rgb=(255.0, 100.0, 10.0),
        sin=(0.5, -0.25), randf=0.75, rng=1000, arg0=O, hinit=None):
    p = {O + 0x14: fb(x), O + 0x18: fb(y), O + 0x1C: fb(z), O + 0x180: fb(floor), O + 0x78: yaw & 0xFFFF,
         0x800BEE08: player}
    pk = ','.join('%08X=%08X' % (a, v) for a, v in sorted(p.items()))
    ret = '15046F70=%X,150ADF00=%X' % (ground, rng)
    retf = '15142948=%s,150ADF48=%08X' % (';'.join('%08X' % fb(s) for s in sin), fb(randf))
    outw = '15046F70=3:%08X,150CD2A0=1:%08X/2:%08X/3:%08X' % (fb(hity), fb(rgb[0]), fb(rgb[1]), fb(rgb[2]))
    if hinit is not None: outw = '1504744C=0:%08X,150CD2A0=1:%08X/2:%08X/3:%08X' % (fb(hinit), fb(rgb[0]), fb(rgb[1]), fb(rgb[2]))
    R.append('%s ! 0=%08X ! %s ! %s ! %s ! ! %s !' % (name, arg0, pk, ret, retf, outw))
add('base')
add('noground', ground=0)
add('null', arg0=0)
add('p1', player=1)
add('p3_yaw', player=3, yaw=0xC0FF)
add('yaw0', yaw=0)
add('yawff', yaw=0xFFFF)
add('rgb_big', rgb=(300.0, 3.0e9, 255.9))
add('rgb_neg', rgb=(-5.0, 0.0, 1.5))
add('rgb_neg_ng', rgb=(-5.0, 2.5e9, 77.0), ground=0)
add('sin_other', sin=(-0.9, 0.1), randf=0.0)
add('sin_big', sin=(3.0, 7.0), randf=1.0)
add('rng0', rng=0)
add('rng_max', rng=0xFFFFFFFF)
add('rng_28', rng=40)
add('rng_20', rng=20)
add('far', x=-5000.0, y=12000.0, z=8000.0, floor=11000.0, hity=11900.0)
add('ground2', ground=2, hity=1.0)
# P201: the HitInfo func_1504715C starts (t = its y) is what func_15046F70 leaves when it writes nothing
add('hitinit', hinit=-77.5)
add('rgb_negb', rgb=(12.0, 34.0, -3.0))
add('rgb_bigb', rgb=(12.0, 34.0, 3.5e9))
add('hitinit_ng', hinit=-77.5, ground=0)
open(sys.argv[1], 'w').write('\n'.join(R) + '\n'); print(len(R))
