#!/usr/bin/env python3
# P206: setups for func_15093B58 radar_draw (knobs.sh format: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW).
# EU addresses: D_800BE628 -> 800BEA48, D_800CC2D0 -> 800CC6F0, D_800DBFF0 -> 800DC420, D_8008FD8C -> 8009012C.
# Jal keys (decoded): func_1510D66C 1510D66C, func_150859AC 15085E1C, func_15086218 15086218, sinf 15048050,
# cosf 15047EF0.
import struct, sys
def fh(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
OBJ, STRIDE = 0x800CC6F0, 0x32C
VIEWS, YAW, TAB, CAM, P31C = 0x80420000, 0x80430000, 0x80450000, 0x80440000, 0x80460000

def setup(name, players=1, fscale=1.0, big=0, size=0x400, tex=0x80480000, objs=None, nplayers=4, mask=0,
          views=((300.0, 40.0), (150.0, 160.0)), tab=(7, 0x10, 21, 0x18), cam23d=None, state0=1,
          ret859='1', levels='2;2;3;1;2;4;0;2;5;1', mode=0x2C30, yaw=(30.0, -45.0)):
    p = {}
    p[0x80090130] = players << 24
    p[0x800901BC] = int(fh(fscale), 16)
    p[0x8009012C] = nplayers << 24
    p[0x800E0FFC] = mask << 16
    p[0x800BEA48] = VIEWS
    p[0x800DC420] = YAW
    for k, (x, y) in enumerate(views):
        p[VIEWS + k * 0x180 + 0x30] = int(fh(x), 16)
        p[VIEWS + k * 0x180 + 0x24] = int(fh(y), 16)
        p[YAW + k * 0x9A0 + 0x37C] = int(fh(yaw[k]), 16)
    # table: s16 entries 7, 16, 21, 24 (others 0)
    t = {}
    t[7], t[16], t[21], t[24] = tab
    for w in range(0, 0x34, 4):
        p[TAB + w] = ((t.get(w // 2, 0) & 0xFFFF) << 16) | (t.get(w // 2 + 1, 0) & 0xFFFF)
    p[CAM + 0x23C] = ((cam23d or 0) & 0xFF) << 16
    # objects: (state, x, y, z, team, health, st31c) per slot; defaults: slot 0/1 players, rest empty
    objs = objs or {}
    for i in range(25):
        st, x, y, z, team, hp, s75 = objs.get(i, (0, 0.0, 0.0, 0.0, 0, 0, 0))
        if i == 0: st = state0 if 0 not in objs else st
        b = OBJ + i * STRIDE
        p[b] = st
        p[b + 0x14], p[b + 0x18], p[b + 0x1C] = int(fh(x), 16), int(fh(y), 16), int(fh(z), 16)
        p[b + 0x328] = (team & 0xFF) << 24
        p[b + 0x1C8] = (hp & 0xFF) << 8
        p[b + 0x318] = CAM if (cam23d is not None and i in (0, 1)) else 0
        p[b + 0x31C] = P31C + i * 0x100
        p[P31C + i * 0x100 + 0x74] = (s75 & 0xFF) << 16
    arg = '0=80410000,1=%X,2=%X,3=%X,4=%X' % (size & 0xFFFFFFFF, TAB, mode, big)
    poke = ','.join('%08X=%08X' % (a, v) for a, v in sorted(p.items()))
    ret = '1510D66C=%X,15085E1C=%s,15086218=%s' % (tex, ret859, levels)
    retf = '15048050=3F000000,15047EF0=3F5DB3D7'
    print('%s ! %s ! %s ! %s ! %s' % (name, arg, poke, ret, retf))

# a scene around player 0 at (100, 0, 200): slots 1..3 players (team 1..3), 4..8 other objects
base = {
    0: (1, 100.0, 0.0, 200.0, 1, 50, 0),
    1: (1, 900.0, 10.0, -400.0, 2, 50, 0),
    2: (1, -1500.0, 0.0, 1200.0, 3, 50, 0),
    3: (1, 300.0, 0.0, 2600.0, 4, 50, 0),
    4: (5, 2000.0, 0.0, 2000.0, 2, 0, 0x21),
    5: (5, 5000.0, 0.0, 200.0, 1, 0, 0),
    6: (5, -2500.0, 0.0, -2500.0, 5, 0, 0),
    7: (5, 150.0, 0.0, 180.0, 0, 0, 0),
    8: (0, 120.0, 0.0, 220.0, 2, 0, 0),
    9: (5, 2900.0, 0.0, -2900.0, 3, 0, 0),
    24: (5, -100.0, 0.0, 100.0, 6, 0, 0),
}
def mod(**kw):
    o = dict(base); o.update({int(k): v for k, v in kw.items()}); return o

setup('p1', objs=base)
setup('p1_scale', objs=base, fscale=1.5)
setup('p2', players=2, objs=base)
setup('p3', players=3, objs=base, ret859='1;1;1;1;1;1;1;0;1;1;1;1;1;1;1;1;1;1;1;1;1;1;1')
setup('p1_big', objs=base, big=1)
setup('p2_big', players=2, objs=base, big=1, fscale=0.75)
setup('big_low', objs=base, big=0x101)   # only the low byte counts
setup('notex', objs=base, tex=0x80000000)
setup('noplayers', players=0, objs=base)
setup('p0_out', players=2, objs=base, ret859='0;1;1;1;1;1;1;1;1;1;1;1;1;1;1;1')
setup('m3_out', objs=base, ret859='1;0;1;1;1;1;1;1;1;1')
setup('m4_out', objs=base, ret859='1;1;0;1;1;1;1;1;1;1')
setup('m3_neg', objs=base, ret859='1;FFFFFFFF;1;1;FFFFFFFF;1;1;1;1')
setup('mask', objs=base, mask=0x000A)
setup('mask_hi', objs=base, mask=0x8001, nplayers=25)
setup('dead', objs=mod(**{'1': (1, 900.0, 10.0, -400.0, 2, 0, 0)}))
setup('st21', objs=mod(**{'2': (1, -1500.0, 0.0, 1200.0, 3, 50, 0xA1)}))
setup('np0', objs=base, nplayers=0)
setup('np_neg', objs=base, nplayers=0x80)
setup('veh_cam3', objs=mod(**{'0': (0x25, 100.0, 0.0, 200.0, 1, 50, 0)}), cam23d=3, levels='1;2;3;1;0;4;1;2')
setup('veh_cam2', objs=mod(**{'0': (0x25, 100.0, 0.0, 200.0, 1, 50, 0)}), cam23d=2)
setup('veh_nocam', objs=mod(**{'0': (0x25, 100.0, 0.0, 200.0, 1, 50, 0)}))
setup('veh_p2', players=2, objs=mod(**{'0': (0x25, 100.0, 0.0, 200.0, 1, 50, 0), '1': (0x25, 900.0, 10.0, -400.0, 2, 50, 0)}), cam23d=3)
setup('levels_eq', objs=base, levels='2;2;2;2;2;2;2;2;2;2;2;2')
setup('levels_neg', objs=base, levels='FFFFFFFE;FFFFFF80;7F;FE;1FE;FFFFFFFE;3;FFFFFF01')
setup('corner', objs=base, views=((1.0, 1.0), (0.0, 0.0)), tab=(40, 0x10, -50, 0x18))
setup('corner_big', objs=base, views=((1.0, 1.0), (0.0, 0.0)), tab=(40, 0x10, -50, 0x18), big=1, size=-0x300)
setup('neg_size', objs=base, size=-0x400, views=((5.0, 2.0), (0.0, 0.0)), tab=(20, 0x10, -10, 0x18))
setup('far_corner', objs=base, views=((2000.0, 1500.0), (0.0, 0.0)), tab=(-900, 0x10, 900, 0x18))
setup('size_odd', players=2, objs=base, size=0x3FF)
setup('size_neg_2p', players=2, objs=base, size=-0x401)
setup('mode', objs=base, mode=0xFF123450)
setup('yaw0', objs=base, yaw=(0.0, 90.0))
# range edges (scaled distance just above 56 / 88: inside 3137 / 7745, outside 3136 / 7744)
setup('edge2p', players=2, objs=mod(**{'10': (5, 100.0 + 4148.44, 0.0, 200.0, 2, 0, 0)}))
setup('edge1p', objs=mod(**{'10': (5, 100.0 + 4345.83, 0.0, 200.0, 2, 0, 0)}))
