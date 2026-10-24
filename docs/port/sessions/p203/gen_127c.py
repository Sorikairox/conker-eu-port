#!/usr/bin/env python3
# P203: setups for func_1511127C sky_box_face_build. jal keys (EU): view test 150A66F0, texture 1510D66C.
# Globals (EU = names): D_800DC2DB (byte 3 of word 800DC2D8), D_800DC2DC (byte 0 of 800DC2DC), D_800DC2B0 (format
# table pointer), D_800B0DF0 = 800B1200 (sky record pointer, +9 sky id). usage: gen_127c.py out.txt
import sys, struct
def fb(x): return struct.unpack('>I', struct.pack('>f', x))[0]
R = []
def add(name, axis='x', face=0, w=240, h=240, ss=60, st=30, x=100.0, y=-50.0, z=25.5, dist=300, view='1', db=0, dc=0,
        sky9=1, count=0, first=0, lastfmt=0xFFFFFFFF, fmts=0x00010001, a19=0x01040000, a20=0x01020000, tile=0x00010000,
        tlc=0xFF0F0000, tlo=0x08000400, fmtn=64):
    args = {0: 0x80480000, 1: 0x80410000, 2: 0x100, 5: w, 6: h, 7: ss, 8: st, 9: fb(x), 10: fb(y), 11: fb(z), 12: ord(axis) if isinstance(axis, str) else axis,
            13: 0x80410300, 14: dist & 0xFFFFFFFF, 15: 0x80410004, 16: 0x80410008, 17: 0x80410100, 18: 0x8041000C,
            19: 0x80410200, 20: 0x80410210, 21: 0x80410220, 22: 0x80410230, 23: 0x80410240, 24: face}
    p = {0x80410000: 0x80430000, 0x80410004: count, 0x80410008: first, 0x8041000C: lastfmt,
         0x80410200: a19, 0x80410210: a20, 0x80410220: tlo, 0x80410230: tlc, 0x80410240: tile,
         0x800DC2D8: db, 0x800DC2DC: dc << 24, 0x800DC2B0: 0x80440000, 0x800B1200: 0x80410400,
         0x80410408: sky9 << 16, 0x80410100: 0x80460000, 0x80410104: 1, 0x80410108: 0x80460100, 0x8041010C: 0,
         0x80410110: 0x80460200, 0x80410114: 1}
    pk = ','.join('%08X=%08X' % (a, v) for a, v in sorted(p.items())) + ',80440000=%08X*%d' % (fmts, fmtn)
    ag = ','.join('%d=%X' % (k, v) for k, v in sorted(args.items()))
    ret = '150A66F0=%s,1510D66C=80450000;80450100;80450200;80450300;80450400;80450500;80450600;80450700;80450800' % view
    R.append('%s ! %s ! %s ! %s ! ! ! !' % (name, ag, pk, ret))
add('x_f0')
add('y_f4', axis='y', face=4)
add('z_f3', axis='z', face=3)
add('y_f1', axis='y', face=1, dist=100)
add('x_dist50', dist=50)
add('x_dist50_db', dist=50, db=1)
add('z_dist_big', axis='z', dist=1000)
add('z_dist_neg', axis='z', dist=-5, face=2)
add('x_dist0_db', dist=0, db=1)
add('view_mix', view='0;1;1;0;1;0;0;1;1;1;0;1')
add('view_mix_y', axis='y', face=5, view='1;0;1;1;0;1;1;1;0')
add('view_none', view='0')
add('dc_repl', face=2, dc=1, sky9=1)
add('dc_repl_y', axis='y', face=2, dc=1, sky9=1, dist=1000)
add('dc_sky2', face=2, dc=1, sky9=2)
add('dc_face1', face=1, dc=1, sky9=1)
add('dc_nodc', face=2, dc=0, sky9=1)
add('count8', count=8, first=0x20)
add('count12', axis='y', face=4, count=12, first=0x10, lastfmt=0)
add('count4_z', axis='z', face=4, count=4, first=3, lastfmt=1)
add('fmt_runs', fmts=0x00000101, lastfmt=0)
add('fmt_all1', fmts=0x01010101, lastfmt=1)
add('lrs_clamp', a19=0xFF100000, a20=0x00030000, tile=0x0F090000, tlc=0x12340000, tlo=0xF800FC00)
add('w0', w=0)
add('h0', h=0)
add('steps_odd', w=250, h=100, ss=50, st=25, x=-12.3, y=7.9, z=-1.6)
add('steps_big', axis='y', face=4, w=0x80000010, h=40, ss=0x40000000, st=20)
add('y_edges', axis='y', face=5, w=180, h=60, dist=400)
add('y_one_col', axis='y', face=4, w=60, h=90)
add('neg_coords', axis='z', face=0, x=-3000.0, y=-2000.5, z=-1500.25)
add('big_coords', axis='x', face=1, x=4000.0, y=4000.0, z=4000.0)
add('axis_hi', axis=0x1278, face=4)
add('dist_mid', axis='x', face=0, dist=161, h=270, st=30)
# P203 survivor killers
add('z_f3_d50', axis='z', face=3, dist=50)
add('x_h480_dbig', w=60, h=480, dist=400)
add('x_r3_d107', h=90, dist=107)
add('y_f4_rect', axis='y', face=4, w=240, h=120, fmtn=8)
add('z_f2_rect', axis='z', face=2, w=120, h=240, fmtn=4)
add('lrs_neg', a20=0x0C1F0000, a19=0x05060000)
open(sys.argv[1], 'w').write('\n'.join(R) + '\n'); print(len(R))
