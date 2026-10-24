#!/usr/bin/env python3
# P203: setups for func_151D3A30 impact_effect_spawn. jal keys (decoded jal words): ray 150ACEA0, material 15146200, rng 150ADF00,
# randf 150ADF48, sound 1000FD54 / 10011168, sparks 151530A8, angles 15145EE4, normal 15145698, particle 15132FBC,
# memcpy 10023360, decal 15102EA0. Globals EU: D_800DCE50 (byte, word 800DCE50), D_800DCE54 (f32), D_80082FA0 = 80083330.
import sys, struct
def fb(x): return struct.unpack('>I', struct.pack('>f', x))[0]
R = []
P, D, H = 0x80410000, 0x80410010, 0x80410020
def add(name, kind=0, hit=0, ray=1, mat=3, rng='2;5;7;9', randf=(0.25, 0.5, 0.75, 0.1, 0.9, 0.2, 0.6), chance=0.5,
        shift=0, players=0, nrm=1, part=0x80470000, a4=0xFF, a5=1, pos=(100.5, -200.25, 3000.75), dr=(1.0, -0.5, 0.25)):
    args = {0: P, 1: D, 2: hit, 3: kind, 4: a4, 5: a5}
    p = {P: fb(pos[0]), P + 4: fb(pos[1]), P + 8: fb(pos[2]), D: fb(dr[0]), D + 4: fb(dr[1]), D + 8: fb(dr[2]),
         H: 0x11223344, H + 4: 0x55667788, H + 8: 0x99AABBCC, H + 12: 0xDDEEFF01, H + 16: 0x23450000,
         0x800DCE50: shift << 24, 0x800DCE54: fb(chance), 0x80083330: players}
    pk = ','.join('%08X=%08X' % (a, v) for a, v in sorted(p.items()))
    ag = ','.join('%d=%X' % (k, v) for k, v in sorted(args.items()))
    ret = '150ACEA0=%X,15146200=%X,150ADF00=%s,15145698=%X,15132FBC=%X' % (ray, mat, rng, nrm, part)
    retf = '150ADF48=%s' % ';'.join('%08X' % fb(v) for v in randf)
    outw = '150ACEA0=6:%08X/8:%08X/9:%08X/10:%08X/11:%08X/12:%X,15145EE4=1:%08X/2:%08X' % (
        fb(0.3), fb(-50.5), fb(60.25), fb(-70.0), fb(0.8), 0x2A, fb(1.25), fb(-0.75))
    outa = '15145698=1:%08X;%08X;%08X/2:%08X/3:%08X' % (fb(0.6), fb(-0.8), fb(0.1), fb(2.0), fb(3.0))
    outb = '150ACEA0=7:' + ';'.join('%X' % (0x31 + i) for i in range(18))
    R.append('%s ! %s ! %s ! %s ! %s ! %s ! %s ! %s' % (name, ag, pk, ret, retf, outa, outw, outb))
add('k0_ray_big', rng='3;5')
add('k0_ray_small')
add('k0_miss', ray=0, mat=0)
add('k0_miss_mat', ray=0, mat=3, rng='2')
add('k1_big_1p', kind=1, rng='1;7;123;9')
add('k1_big_2p', kind=1, rng='1;7;123;9', players=1)
add('k1_small', kind=1, rng='2;777;9')
add('k1_nomat', kind=1, mat=0, rng='4;8;1234')
add('k2', kind=2)
add('k3_big', kind=3, rng='5;9')
add('k4', kind=4)
add('k5', kind=5)
add('k6', kind=6)
add('k_ff', kind=0xFF)
add('k_102', kind=0x102)
add('hitrec', hit=H, mat=2)
add('hitrec_nomat', hit=H, mat=0)
add('hitrec_k1', hit=H, kind=1, rng='1;2;3;4')
add('nospark', randf=(0.6, 0.5, 0.75, 0.1, 0.9))
add('spark_eq', randf=(0.5, 0.5, 0.75, 0.1))
add('shift1', shift=1)
add('shift2', shift=2, randf=(0.0, 0.3))
add('players2', players=2)
add('players2_k1', players=2, kind=1, rng='3;1;8')
add('nonormal', rng='1;5', nrm=0)
add('noparticle', part=0)
add('a4_wide', a4=0x1FF, a5=0x12345)
add('rnd_big', rng='FFFFFFFF;FFFFFFFE;FFFFFFFD', kind=1)
add('neg_pos', pos=(-1000.0, -32000.5, 12.0), dr=(-0.2, 0.9, -0.4), rng='7;3;2')
add('randf_ext', randf=(0.0, 1.0, 0.999, 0.0, 1.0, 0.5, 0.5), rng='9;9;9')
add('randf_ext2', randf=(0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0), rng='2;2;2')
add('trail_rng', rng='2;33')
open(sys.argv[1], 'w').write('\n'.join(R) + '\n'); print(len(R))
