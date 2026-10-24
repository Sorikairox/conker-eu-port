#!/usr/bin/env python3
# P182: difftest setups for func_1517C11C (ambient_emitters_update). Run with DIFFTEST_ROMDATA=1 (D_8008D258 updaters,
# D_8008D2A0 rows, D_80096090 sound info are .game_data). Fields: name ! ARG ! POKE ! RET ! RETF ! OUTA. EU addresses
# (from the asm's %hi/%lo words). Records: 14 bytes at 80460000 in the layout func_1500AF08 writes (P180); rows of
# D_8008D2A0 (ROM): 0 = null updaters, 1 = 1517BA70, 2 = 1517BC58, 3 = 1517BD18, 4 = 1517BD68.
import os, struct
D = os.path.dirname(os.path.abspath(__file__))
REC = 0x80460000; QUADS = 0x80480000
SLOTS = 0x800DD8A8; VOICES = 0x800DDEC0
def f2h(v): return '%08X' % struct.unpack('>I', struct.pack('>f', v))[0]
def h(v): return '%X' % (v & 0xFFFFFFFF)
def words(addr, b):
    b = bytes(b) + bytes(-len(b) % 4)
    return ['%08X=%s' % (addr + i, b[i:i + 4].hex().upper()) for i in range(0, len(b), 4)]
def rec(x, y, z, slot, phase=0, kind=0, flare=0, hw=0x14, ht=0x20, mode=1, sound=0x1234):
    return struct.pack('>hhhBBHBBbb', x, y, z, (mode << 5) | slot, phase, sound, kind, flare, hw, ht)
# default per-slot state
def slot_state(slot0=None, voices=None, ids=None, rows=None, periods=None, phases=None, c04=0, c08=0, flags=None,
               de010=None, de020=None, tex=None, beac0=0, dt=2, dd8a0=(0, 0, 0)):
    p = []
    slot0 = slot0 or [0x80470000 + 0x100 * v for v in range(15)]
    for v in range(15): p.append('%08X=%08X' % (SLOTS + 0x68 * v, slot0[v]))
    voices = voices or [(0x00A00000 + 0x1000 * v, 0x800 + v, 0x80490000 + v, 0) for v in range(15)]
    for v, (ra, sz, hd, hr) in enumerate(voices):
        p += ['%08X=%08X' % (VOICES + 16 * v, ra), '%08X=%08X' % (VOICES + 16 * v + 4, sz),
              '%08X=%08X' % (VOICES + 16 * v + 8, hd), '%08X=%02X000000' % (VOICES + 16 * v + 12, hr)]
    p += words(0x800DDFF0, ids or [1, 0, 4, 0, 5, 0, 7, 0, 9, 0, 1, 2, 0, 3, 6, 0])
    p += words(0x800DE0B0, rows or [1, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 1, 2, 3, 0])
    p += words(0x800DE000, periods or [0x10, 1, 2, 3, 0x20, 0x10, 0x40, 0x10, 0x10, 0x18, 0x10, 0x10, 0x30, 0x10, 0x10, 0])
    p += words(0x800DE010, de010 or [3 + v for v in range(16)])
    p += words(0x800DE020, de020 or [0x40 + v for v in range(16)])
    p += words(0x800DE040, flags or [0x5, 0xA, 0xF, 0, 3, 0xC, 9, 6, 1, 2, 4, 8, 0xE, 7, 0xB, 0])
    ph = phases or [(0x123 * k + 0x80) & 0xFFF for k in range(60)]
    p += words(0x800DE0C0, b''.join(struct.pack('>h', v) for v in ph))
    p += words(0x800DDFB0, b''.join(struct.pack('>hh', tex or 0x400 + 0x20 * v, -0x200 + 3 * v) for v in range(15)))
    p += ['800DE034=%08X' % c04, '800DE038=%08X' % c08, '800BEEE0=%02X000000' % beac0, '800BEE04=%08X' % dt]
    p += words(0x800DD8A0, struct.pack('>hhh', *dd8a0) + b'\0\0')
    return p
RNG = '151EFDD0=7;23;FFFFFFF5;14;0;3;1;FFFFFFF1;B;64;5;2;9'
CB = ['1517BA70', '1517BC58', '1517BD18', '1517BD68']
def setup(name, recs, angle, cam=(0, 0, 0), radius=0x5DC, player=(5000, 0, 5000), dist='100;200', key=None,
          count=None, cap=0x10, buf=0, alloc=QUADS, c3c='80490000;804A0000;804B0000', cbret='0', outa='', rng=RNG, extra=(),
          **kw):
    byz = not ((45 < angle < 135) or (225 < angle < 315))
    a = '0=%s,1=%s,2=%s,3=%s,4=%s,5=%s,6=%s,7=%s' % (h(cam[0]), h(cam[1]), h(cam[2]), h(radius), f2h(angle),
                                                      h(player[0]), h(player[1]), h(player[2]))
    p = ['800DE148=%08X' % REC, '800DE150=%08X' % (len(recs) if count is None else count), '800DE13C=%08X' % cap,
         '8008D254=%08X' % (int(byz) if key is None else key), '800BEDE0=%02X000000' % buf]
    p += words(REC, b''.join(recs)) + slot_state(**kw) + list(extra)
    r = ['10003E90=%X' % alloc, '150ADE80=' + dist, '10003EBC=' + c3c, rng] + ['%s=%s' % (c, cbret) for c in CB]
    am = ','.join('%s=1:64,%s=2:4' % (c, c) for c in CB)
    return [name, a, ','.join(p), ','.join(r), '', outa], am
def line(rx, axis, n, step=40, base=-100):
    """n records sorted along axis (0 = x, 2 = z), the other coordinates spread"""
    out = []
    for i in range(n):
        c = [37 * i - 50, 5 * i, -29 * i + 60]
        c[axis] = base + step * i
        out.append(c)
    return out
def recs_of(coords, slots=None, kinds=None, flares=None, phases=None):
    return [rec(x, y, z, (slots or list(range(15)))[i % len(slots or range(15))], phase=(phases or [3 * i])[i % len(phases or [1])],
                kind=(kinds or [i % 8 for i in range(32)])[i], flare=(flares or [0])[i % len(flares or [0])],
                hw=0x10 + 3 * i, ht=((0x18 + 5 * i - (60 if i == 3 else 0) + 128) & 0xFF) - 128) for i, (x, y, z) in enumerate(coords)]
S = []
def add(r): S.append(r[0]); return r[1]
Z8 = recs_of(line(0, 2, 8)); X8 = recs_of(line(0, 0, 8))
# distances: dist(e) then dist2(e) (player) [then the D_800DD8A0 flare distance]
D_ALL = '100;F0;64;1F4;2C;F0;300;200;10;400;5DB;F0;0;F0;7;F0'
D_MIX = '5DC;64;8C;64;8D;200;EF;10;F0;100;FFFFFFFF;F0;5DD;20;2F;8D'
am = add(setup('z1', Z8, 10.0, cam=(0, 0, 0), dist=D_ALL))
add(setup('x1', X8, 80.0, dist=D_MIX))
add(setup('zm', Z8, 180.0, cam=(0, 0, 200), dist=D_ALL))
add(setup('xm', X8, 250.0, cam=(150, 0, 0), dist=D_MIX))
for ang in (45.0, 135.0, 225.0, 315.0, 90.0, 270.0, 0.0, 359.0):
    add(setup('a%d' % ang, Z8 if not ((45 < ang < 135) or (225 < ang < 315)) else X8, ang, cam=(60, 0, 60), dist=D_MIX))
add(setup('sort', Z8, 80.0, key=1, dist=D_ALL))            # key differs: func_1517BE0C(0, n - 1)
add(setup('sortz', X8, 10.0, key=0, dist=D_ALL))
# voice loading: every slot empty, voices with / without ROM data, allocation results
V = [(0x00A00000 + 0x1000 * v if v % 4 else 0, 0x800 + v, 0, 0) for v in range(15)]
add(setup('load', Z8, 10.0, dist=D_ALL, slot0=[0] * 15, voices=V, c3c='80490000;804A0000'))
add(setup('loadf2', Z8, 10.0, dist=D_ALL, slot0=[0] * 15, voices=V, c3c='80490000;0;804B0000;804C0000;0'))
add(setup('loadf1', Z8, 10.0, dist=D_ALL, slot0=[0] * 15, voices=V, c3c='0;80490000;804A0000;0;0;804D0000'))
add(setup('heard', Z8, 10.0, dist=D_ALL, voices=[(0x00A00000, 0x800, 0x80490000 + v, v & 1) for v in range(15)]))
# flare-ups: D_800DD8A0 set, flare distances, states 0x21 / 0x22 / 0x25 / 0 / 0x20
F = recs_of(line(0, 2, 8), flares=[0, 0x21, 0x22, 0x25, 0x20, 0, 0x30, 0x21])
DF = '100;F0;20;64;F0;10;2C;F0;4F;300;F0;50;10;F0;0;2F;F0;30;5DB;F0;1;0;F0;0'
add(setup('flare', F, 10.0, dist=DF, dd8a0=(100, 20, -30)))
add(setup('flare0', F, 10.0, dist=DF, dd8a0=(0, 20, -30), ids=[0] * 16))
add(setup('flareid', F, 10.0, dist=DF, dd8a0=(-5, 0, 0), ids=[0, 1] * 8))
# updater results: skip (1) / keep, and updaters writing the quad base and the phase
add(setup('cbret', Z8, 10.0, dist=D_ALL, cbret='0;1;0;FFFFFFFF;0'))
add(setup('cbout', Z8, 10.0, dist=D_ALL, outa=','.join('%s=1:00120034;0056FFFF/2:00000A40' % c for c in CB)))
add(setup('cbneg', Z8, 10.0, dist=D_ALL, outa=','.join('%s=2:FFFFF000' % c for c in CB)))
add(setup('rows', Z8, 10.0, dist=D_ALL, rows=[0, 2, 3, 4, 1] * 3 + [0]))
# capacity / allocation / empty / out of range
add(setup('cap2', Z8, 10.0, dist=D_ALL, cap=2))
add(setup('cap1', Z8, 10.0, dist='5DC;0;5DC;64;F0', cap=1))
add(setup('capbig', Z8, 10.0, dist=D_ALL, cap=0x40))
add(setup('allocf', Z8, 10.0, dist=D_ALL, alloc=0))
add(setup('none', Z8, 10.0, cam=(0, 0, 5000)))
add(setup('nonem', Z8, 180.0, cam=(0, 0, -5000)))
add(setup('empty', Z8, 10.0, count=0))
add(setup('emptym', Z8, 180.0, count=0))
add(setup('buf1', Z8, 10.0, dist=D_ALL, buf=1))
add(setup('exact', Z8, 10.0, cam=(0, 0, 0x5DC - 100 + 80), dist=D_ALL))   # zmin == a record's z
add(setup('one', [Z8[0]], 10.0, dist=D_ALL))
add(setup('big', recs_of(line(0, 2, 24, step=17)), 10.0, dist=D_ALL + ';' + D_MIX + ';' + D_ALL))
add(setup('bigm', recs_of(line(0, 0, 24, step=17)), 250.0, cam=(200, 0, 0), dist=D_MIX + ';' + D_ALL))
# phase animation: ping-pong / random flips / wrap, frozen
P2 = [0, 1, -3, 0xFFF, 0xFFE, 0x7FFF, -0x8000, 2] * 7 + [0x100, 0x200, 0x300, 0x400]
add(setup('anim', Z8, 10.0, dist=D_ALL, c04=0x5A5A, c08=0x3C3C, phases=P2))
add(setup('animr', Z8, 10.0, dist=D_ALL, c04=0x7FFF, c08=0x7FFF, phases=P2,
          rng='151EFDD0=0;7;1;FFFFFFF9;A;FFFFFFF6;B;5;14;3;FFFFFFFF;C;0;10;1;20;2'))
add(setup('animw', Z8, 10.0, dist=D_ALL, c04=0, c08=0xFFFF, phases=P2, dt=0x50))
add(setup('animdt', Z8, 10.0, dist=D_ALL, c04=0xFFFF, c08=0, phases=P2, dt=0xFFFFFFF0))
add(setup('animoff', Z8, 10.0, dist=D_ALL, c04=0xFFFF, c08=0xFFFF, phases=P2, beac0=1))
add(setup('per', Z8, 10.0, dist=D_ALL, c04=0x1111, periods=[1, 2, 0xFF, 0x80, 3] * 3 + [0], phases=P2))
# spark: random quad index, frame % 26 == 0 and sound id 0
add(setup('spark', Z8, 10.0, dist=D_ALL, ids=[0] * 16, phases=[0] * 60, rng='151EFDD0=0;1;2;3;4;5;6;7;8;9;A;B;C;D;E;F;3'))
add(setup('spark2', Z8, 10.0, dist=D_ALL, ids=[0] * 16, phases=[0x40] * 60, rng='151EFDD0=FFFFFFFF'))
add(setup('neg', recs_of(line(0, 2, 8, base=-32000, step=9000)), 10.0, cam=(-3000, 100, -31000), dist=D_ALL))
# P182 mutant follow-ups: fade-in distances (0x8D <= dist2 < 0xF0), flare-up at 0x2F / 0x30, spark index == count
add(setup('fade', Z8, 10.0, dist='100;8D;64;EF;2C;C0;300;90;10;F0;5DB;A0;0;8D;7;EF'))
add(setup('fadex', X8, 80.0, dist='5DB;8D;1;EF;5DB;EF;300;BC;1F4;8E;5DB;A0;0;8D;7;EF'))
add(setup('near', Z8, 10.0, dist='2F;F0;30;F0;2E;F0;0;F0;31;F0;2F;100;30;200;1;F0', ids=[0] * 16))
add(setup('spark3', Z8, 10.0, dist=D_ALL, ids=[0] * 16, phases=[0] * 60, rng='151EFDD0=8', extra=['80480204=00000000']))
open(os.path.join(D, '7c11c_setups.txt'), 'w').write('\n'.join(' ! '.join(r) for r in S) + '\n')
open(os.path.join(D, '7c11c_argmem.txt'), 'w').write(am + '\n')
print(len(S), 'setups')
