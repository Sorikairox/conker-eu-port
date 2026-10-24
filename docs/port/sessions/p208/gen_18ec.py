#!/usr/bin/env python3
"""P208: setups for func_150918EC (mp_hud_draw). Output: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB
EU addresses: D_80082FA0 80083330, D_80087270 80087610, D_800BE628 800BEA48, D_800CC2D0 800CC6F0, D_800BE9F0 800BEE10,
D_800BEAC1 800BEEE1, D_8008FD8C 8009012C. Jal keys: func_1510D66C 1510D66C, func_150859AC 15085E1C,
func_15091534 15091994, func_15093B58 15093F6C, func_15042D94 15043084, func_150916B4 15091B14, func_1504332C 1504361C."""
import struct

def fw(x):
    return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]

VIEWS = 0x80420000
OBJ = 0x800CC6F0
ST = 0x80460000

def base(nv=2, flags=0, f=1.0, skip=(), views=None):
    p = {}
    p[0x80083330] = '%08X' % (nv - 1)
    b = [0, 0, 0, 0]
    for s in skip:
        b[s] = 10
    p[0x80087610] = ''.join('%02X' % x for x in b)
    p[0x800BEA48] = '%08X' % VIEWS
    p[0x800901BC] = fw(f)
    p[0x80090160] = '%04X0000' % flags
    p[0x800BEE10] = '00000005'
    p[0x800BEEE0] = '00000000'
    p[0x80090174] = '80470000'
    p[0x800E1008] = '80480000'
    p[0x800E0EF0] = '00010203'
    p[0x80087640] = '00000000'
    p[0x8009015C] = '00000000'
    p[0x80090130] = '%02X000000' % nv
    p[0x8009012C] = '%02X000000' % nv
    vs = views or [(10 + 160 * (i % 2), 230 + 160 * (i % 2), 8 + 120 * (i // 2), 112 + 120 * (i // 2)) for i in range(4)]
    for i, (l, r, t, bt) in enumerate(vs):
        a = VIEWS + i * 0x180
        p[a + 0x24], p[a + 0x28], p[a + 0x2C], p[a + 0x30] = fw(t), fw(bt), fw(l), fw(r)
    for i in range(4):
        p[0x80470044 + 0] = '0000000C'
        p[0x80470048] = 'FFFD0063'
        p[0x8047004C] = '00070000'
    for i in range(26):
        p[0x80480000 + i * 4] = '%08X' % (0x80481000 + i * 0x10)
    for i in range(25):
        o = OBJ + i * 0x32C
        p[o] = '00000001'
        p[o + 4] = '%02X000000' % (0x10 + i)
        p[o + 0x14] = fw(-300.0 + 37.5 * i)
        p[o + 0x1C] = fw(250.0 - 21.25 * i)
        p[o + 0x13C] = '00000000'
        p[o + 0x1C8] = '00000100'  # health 1
        p[o + 0x31C] = '%08X' % (ST + i * 0x200)
        p[o + 0x328] = '%02X000000' % (i % 3)
        s = ST + i * 0x200
        p[s + 0x74] = '00000000'
        p[s + 0x128] = '00000000'
        p[s + 0x12C] = '01230000'
        p[s + 0x198] = '00000000'
        p[s + 0x1AC] = '00000000'
    return p

def obj(p, i, state=None, st=None, id=None, k128=None, v12c=None, n19a=None, c1ae=None, b13c=None, health=None, t328=None):
    o = OBJ + i * 0x32C; s = ST + i * 0x200
    if state is not None: p[o] = '%08X' % (state & 0xFFFFFFFF)
    if id is not None: p[o + 4] = '%02X000000' % id
    if st is not None: p[s + 0x74] = '00%02X0000' % st
    if k128 is not None: p[s + 0x128] = '%02X000000' % k128
    if v12c is not None: p[s + 0x12C] = '%04X0000' % v12c
    if n19a is not None: p[s + 0x198] = '0000%02X00' % n19a
    if c1ae is not None: p[s + 0x1AC] = '0000%02X00' % (c1ae & 0xFF)
    if b13c is not None: p[o + 0x13C] = '%02X000000' % b13c
    if health is not None: p[o + 0x1C8] = '0000%02X00' % health
    if t328 is not None: p[o + 0x328] = '%02X000000' % (t328 & 0xFF)

out = []
def emit(name, p, ret=None, outb='15091994=2:01', retf=''):
    r = {'1510D66C': '80500000', '15085E1C': '1', '15091994': '80418000', '15093F6C': '80419000'}
    r.update(ret or {})
    out.append('%s ! 0=80410000 ! %s ! %s ! %s ! ! ! %s' % (
        name, ','.join('%08X=%s' % (a, v) for a, v in sorted(p.items())), ','.join('%s=%s' % kv for kv in r.items()), retf, outb))

# 1. placing digit / score / team name
for nm, fl, f, nv, skip, k, tex in [('dig1', 0x2, 1.0, 2, (), '5;B', None), ('dig2', 0xC02, 1.5, 4, (2,), '0;7;FFFFFFFF;D', None),
                                   ('dig3', 0x2, 1.0, 3, (), '3', '80000000'), ('txt1', 0xC00, 1.0, 4, (1,), '1', None),
                                   ('txt2', 0x400, 0.75, 1, (), '1', None), ('txt3', 0x800, 1.5, 2, (), '1', None),
                                   ('dig4', 0x802, 0.75, 2, (), '2;6', None)]:
    p = base(nv, fl, f, skip)
    ret = {'15085E1C': k}
    if tex: ret['1510D66C'] = tex
    emit(nm, p, ret)
# negative x for the scis clamp
p = base(2, 0x2, 1.5, views=[(-40, 100, -20, 80), (-3, 50, 5, 60), (0, 1, 0, 1), (0, 1, 0, 1)])
emit('dig_neg', p, {'15085E1C': '4;9'})
p = base(2, 0x2, 1.0, views=[(-40, 100, -20, 80), (-3, 50, 5, 60), (0, 1, 0, 1), (0, 1, 0, 1)])
emit('dig_negb', p, {'15085E1C': '4;9'})

# 2. state icons (sheet 0), 4 views each
groups = [(0x09, 0x16, 0x14, 0x3F), (0x20, 0x18, 0x41, 0x15), (0x22, 0x23, 0x21, 0x24), (0x25, 0x40, 0x38, 0x10),
          (0x32, 0x33, 0x26, 0x3A), (0x11, 0x00, 0x7F, 0x42), (0x89, 0x96, 0xA0, 0xC1)]
for gi, g in enumerate(groups):
    for f in (1.0, 1.5):
        p = base(4, 0x4 if gi % 2 == 0 else 0x14, f)
        for i, s in enumerate(g):
            obj(p, i, st=s, c1ae=[3, 0, -2, 2][i], health=[1, 0, 2, 0][i])
        emit('ico%d%s' % (gi, 'h' if f != 1.0 else ''), p, {'15085E1C': '3;0;5;8;1;2;7;4'})
p = base(4, 0x4)
for i, s in enumerate((0x11, 0x26, 0x3A, 0x22)):
    obj(p, i, st=s, health=[1, 1, 0, 1][i])
p[0x800BEE10] = '0000001A'
obj(p, 3, state=0x1F)
emit('ico_1a', p)
p = base(4, 0x4)
for i, s in enumerate((0x09, 0x16, 0x14, 0x40)):
    obj(p, i, st=s, b13c=[1, 0, 2, 0][i])
emit('ico_13c', p)
p = base(3, 0x4, skip=(1,))
for i, s in enumerate((0x32, 0x33, 0x16, 0x09)):
    obj(p, i, st=s, c1ae=[5, 1, 0, 0][i])
emit('ico_cnt', p, outb='15091994=2:00')
p = base(3, 0x14)
for i, s in enumerate((0x32, 0x40, 0x21, 0x09)):
    obj(p, i, st=s, c1ae=[3, 0, 0, 0][i])
emit('ico_cntb', p, outb='15091994=2:00')
# 3. lives bars
for nm, k, ob in [('liv1', '0;1;2;3', '01'), ('liv2', '4;5;6;FFFFFFFF', '01'), ('liv3', '2;3;9;C', '00'), ('liv4', '1;8;A;0', '01')]:
    p = base(4, 0x10, 1.5 if nm == 'liv4' else 1.0)
    emit(nm, p, {'15085E1C': k}, outb='15091994=2:' + ob)
# 4. vehicle / weapon icons, second sheet, bars
for nm, conf, f in [('veh1', [(0x1E, 0, 1, 0x1F0), (0x1E, 0, 2, 0x50), (0x1E, 0, 0x80, 0x4D2), (0x1E, 0, 0x10, 0x11)], 1.0),
                    ('veh2', [(0x1E, 0, 0x13, 0xFFFF), (0x1E, 0, 0x92, 0x800), (0x1E, 0, 0x90, 0x7), (0x1E, 0, 0x0, 0x30)], 1.5),
                    ('sh2a', [(1, 0x30, 0, 0), (1, 0x31, 0, 0), (1, 0x37, 0, 0), (1, 0x38, 0, 0)], 1.0),
                    ('sh2b', [(1, 0x39, 0, 0), (1, 0x3E, 0, 0x2A0), (1, 0x3D, 0, 0), (1, 0x2F, 0, 0)], 1.0),
                    ('sh2c', [(1, 0x3E, 0, 0x45), (0x1E, 0, 1, 0x100), (1, 0x32, 0, 0), (1, 0xB9, 0, 0)], 1.5),
                    ('sh2d', [(1, 0x30, 0, 0), (0x1E, 0, 0x10, 0x2), (1, 0x3E, 0, 0x0), (1, 0xBE, 0, 0x3F0)], 1.0)]:
    p = base(4, 0x4, f)
    for i, (sta, st, k, v) in enumerate(conf):
        obj(p, i, state=sta, st=st, k128=k, v12c=v, c1ae=[3, -1, 2, 0][i])
    emit(nm, p)
    emit(nm + 'n', p, outb='15091994=2:00')
# 5. fire counter
for nm, be, ids, ns in [('fire1', 5, (0x75, 0xB1, 0x3B, 0x10), (1, 2, 3, 0)), ('fire2', 0x1A, (0x75, 0x10, 0x3B, 0x10), (2, 1, 1, 4)),
                        ('fire3', 0x3F, (0x10, 0x10, 0x10, 0x10), (3, 0, 1, 2)), ('fire4', 7, (0x3B, 0x75, 0xB1, 0x11), (1, 1, 1, 1))]:
    for f in (1.0, 1.5):
        p = base(4, 0x4, f)
        p[0x800BEE10] = '%08X' % be
        for i in range(4):
            obj(p, i, st=[0x26, 0x3A, 0x26, 0x3A][i] if i != 3 or nm != 'fire4' else 0x27, id=ids[i], n19a=ns[i], health=1)
        emit(nm + ('h' if f != 1.0 else ''), p)
p = base(2, 0x4, 1.5, views=[(-40, 20, -20, 80), (-3, 1, 5, 60), (0, 1, 0, 1), (0, 1, 0, 1)])
for i in range(2):
    obj(p, i, st=0x26, id=0x75, n19a=3, health=1)
emit('fire_neg', p)
p = base(2, 0x4, 1.0)
obj(p, 0, st=0x26, health=1, n19a=2)
obj(p, 1, st=0x3A, health=0, n19a=2)
p[0x80087610] = '0A000000'
emit('fire_skip', p)
# 6. race
for nm, laps, recs, f in [('race1', 3, [(500, 1234, 0), (0, 99, 2), (-5, 7, 3), (12, 0, 1)], 1.0),
                          ('race2', 2, [(1, 2, 1), (0, 0, 2), (100, 200, 0x7F), (3, 4, -1)], 1.5)]:
    p = base(4, 0x80, f)
    p[0x80087640] = '80490000'
    p[0x800E1014] = '000000%02X' % laps
    for i, (b, c, lp) in enumerate(recs):
        a = 0x80490000 + i * 0x84
        p[a + 0x1C] = '%08X' % (c & 0xFFFFFFFF)
        p[a + 0x20] = '%08X' % (b & 0xFFFFFFFF)
        p[a + 0x24] = '000000%02X' % (lp & 0xFF)
    emit(nm, p)
p = base(2, 0x80)
emit('race_null', p)
# 7. overview map and radar
for nm, f, nv, fd, bit, k, ac1 in [('map1', 1.0, 2, 2, 0, '1;0;1;FFFFFFFF;1', 0), ('map2', 1.5, 3, 4, 0x40, '1;1;0;1;0;1;1', 0),
                                   ('map3', 1.0, 4, 1, 0x40, '0;1;1;1;0;1;1;1;1', 0), ('map4', 1.0, 2, 2, 0, '1', 1),
                                   ('map5', 0.75, 1, 0, 0, '1;1', 0)]:
    p = base(nv, 0x1020, f)
    p[0x8009015C] = '%04X0000' % bit
    p[0x8009012C] = '%02X000000' % fd
    p[0x800BEEE0] = '00%02X0000' % ac1
    for i in range(25):
        if i % 4 == 3:
            obj(p, i, t328=0)
    emit(nm, p, {'15085E1C': k})
p = base(2, 0x1020, 1.0, views=[(-40, 20, -20, 80), (-3, 1, 5, 60), (0, 1, 0, 1), (0, 1, 0, 1)])
for i in range(25):
    obj(p, i, t328=1)
    o = OBJ + i * 0x32C
    p[o + 0x14] = fw(-9000.0 + 700 * i)
    p[o + 0x1C] = fw(-8000.0 + 650 * i)
emit('map_neg', p, {'15085E1C': '1'})
p = base(2, 0x20, 1.5)
emit('radar', p)
p = base(2, 0xFFFF, 1.0)
for i, s in enumerate((0x26, 0x16, 0x30, 0x3E)):
    obj(p, i, st=s, health=1, n19a=1, v12c=0x99)
p[0x80087640] = '80490000'
emit('all', p, {'15085E1C': '2;5;1;0;3;1;1;1;0;1'})
print('\n'.join(out))
