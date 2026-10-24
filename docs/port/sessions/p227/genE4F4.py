#!/usr/bin/env python3
# P227: setups for func_1511E4F4 (pickup_update, world-object type 0x28 callback). ARG 0 = obj 80450000 (+0x7C state
# -> 80460000, or 0: allocate_memory jal 10003E90 returns 80460000). Players D_800CC2D0 (EU 800CC6F0, stride 0x32C;
# count D_8008FD8C = 8009012C byte; D_800BE9E4 = EU 800BEE04, D_800BE9F0 = EU 800BEE10), ctl +0x31C -> 80470000 + i * 0x400. D_800BE9E4 = dt, D_800BE9F0 = level.
# Keys: cosf 15047EF0 (RETF), func_1507C7C0 1507C7C0 (OUTB height through a1), func_15031C4C 15031C4C,
# func_1509B570 1509B980 (-> 80490000, +0x1FE4), func_1511E320 / func_151D6F20.
import struct
def fb(f): return '%08X' % struct.unpack('>I', struct.pack('>f', f))[0]
def setup(name, st=(0x1234, 0xF000, 0, 0x100, 0.25, 2.0), alloc=0, kind=0x10, filt=0, dt=2, lvl=1, b1fe4=5,
          pos=(100, 50, -100), np=2, pl=None, h=0x40, has=0, cosv=0.5, sc=(3.0, 4.0, 5.0)):
    m = {}
    def w(a, v): m[a] = v & 0xFFFFFFFF
    w(0x80450000, 0x3F800000); w(0x80450004, 0x40000000); w(0x80450018, 0)
    w(0x80450010, (pos[0] & 0xFFFF) << 16 | (pos[1] & 0xFFFF)); w(0x80450014, (pos[2] & 0xFFFF) << 16)
    w(0x8045002C, int(fb(sc[0]), 16)); w(0x80450030, int(fb(sc[1]), 16)); w(0x80450034, int(fb(sc[2]), 16))
    w(0x80450054, kind << 16); w(0x8045006C, 0); w(0x8045007C, 0 if alloc else 0x80460000); w(0x80450080, 0x77)
    w(0x80450084, filt)
    w(0x80460000, st[0] << 16 | st[1]); w(0x80460004, st[2] << 16 | st[3])
    w(0x80460008, int(fb(st[4]), 16)); w(0x8046000C, int(fb(st[5]), 16))
    w(0x800BEE04, dt); w(0x800BEE10, lvl); w(0x80491FE4, b1fe4); w(0x8009012C, np << 24)
    if pl is None:
        pl = [dict(), dict(x=100.0, z=-100.0)]
    for i, d in enumerate(pl):
        r = 0x800CC6F0 + i * 0x32C; c = 0x80470000 + i * 0x400
        w(r, d.get('act', 1)); w(r + 0x1C8, d.get('hp', 3) << 8); w(r + 0x124, d.get('b127', 0))
        w(r + 0x128, d.get('team', 0) << 24); w(r + 0x300, d.get('play', 1) << 24); w(r + 0x38, d.get('id', 0x12 + i))
        w(r + 0x14, int(fb(d.get('x', 5000.0)), 16)); w(r + 0x18, int(fb(d.get('y', 40.0)), 16))
        w(r + 0x1C, int(fb(d.get('z', 5000.0)), 16)); w(r + 0x17C, int(fb(d.get('top', 1000.0)), 16)); w(r + 0x31C, c)
        w(c + 0x1AC, d.get('size', 64)); w(c + 0x84, d.get('big', 0) << 24)
    pk = ','.join('%08X=%08X' % kv for kv in sorted(m.items()))
    ret = '10003E90=80460000,1509B980=80490000,15031C4C=%X,1507C7C0=0' % has
    print('%s ! 0=80450000 ! %s ! %s ! 15047EF0=%s ! ! ! 1507C7C0=1:%02X;%02X !' % (name, pk, ret, fb(cosv), (h >> 8) & 0xFF, h & 0xFF))
setup('base')
setup('alloc', alloc=1)
setup('k59', kind=0x59)
setup('k5A', kind=0x5A, st=(1, 2, 1, 3, 0.25, 2.0))
setup('k54', kind=0x54)
setup('k54_has', kind=0x54, has=1)
setup('k54_l2d_off', kind=0x54, lvl=0x2D, b1fe4=0)
setup('k54_l2d_on', kind=0x54, lvl=0x2D, b1fe4=1)
setup('k54_l2d_neg', kind=0x54, lvl=0x2D, b1fe4=-1)
setup('st0_grow', st=(0, 0, 0, 0x100, 0.25, 2.0), sc=(1.0, 1.0, 1.0), pl=[dict(act=0)])
setup('st0_full', st=(0, 0, 0, 0x100, 0.25, 2.0), sc=(1.0, 1.0, 1.9), pl=[dict(act=0)])
setup('st1', st=(0, 0, 1, 0x100, 0.5, 2.0), pl=[dict(act=0)])
setup('st1_end', st=(0, 0, 1, 0x100, 0.01, 2.0), pl=[dict(act=0)])
setup('st2', st=(0, 0, 2, 0x100, 0.5, 2.0), pl=[dict(act=0)])
setup('st3', st=(0, 0, 3, 0x100, 0.5, 2.0))
setup('st3_end', st=(0, 0, 3, 0x100, 0.5, 2.0), sc=(1.0, 1.0, 0.3))
setup('st4', st=(0, 0, 4, 0x100, 0.5, 2.0))
setup('take', pl=[dict(), dict(x=110.0, z=-90.0)])
setup('take_p0', pl=[dict(x=101.0, z=-99.0), dict(x=110.0, z=-90.0)])
setup('dead', pl=[dict(hp=0, x=100.0, z=-100.0), dict(x=110.0, z=-90.0)])
setup('inactive', pl=[dict(act=0, x=100.0, z=-100.0), dict(b127=0xFF, x=110.0, z=-90.0)])
setup('noplay', pl=[dict(play=0, x=100.0, z=-100.0), dict(x=5000.0)])
setup('filt1', filt=1, pl=[dict(team=1, x=100.0, z=-100.0), dict(team=0, x=110.0, z=-90.0)])
setup('filt1b', filt=1, pl=[dict(team=0, x=100.0, z=-100.0), dict(team=2, x=110.0, z=-90.0)])
setup('filt2', filt=2, pl=[dict(team=0, x=100.0, z=-100.0), dict(team=2, x=110.0, z=-90.0)])
setup('filt3', filt=3, pl=[dict(team=2, x=100.0, z=-100.0), dict(team=3, x=110.0, z=-90.0)])
setup('filt3b', filt=3, pl=[dict(team=1, x=100.0, z=-100.0), dict(team=2, x=110.0, z=-90.0)])
setup('edge_in', pl=[dict(x=100.0 + 99.0, z=-100.0), dict()])
setup('edge_out', pl=[dict(x=100.0 + 101.0, z=-100.0), dict()])
setup('big', pl=[dict(x=100.0 + 139.0, z=-100.0, big=1), dict()])
setup('size32', pl=[dict(x=100.0 + 51.0, z=-100.0, size=32), dict(x=100.0, z=-100.0 + 49.0, size=32)])
setup('size_hi', pl=[dict(x=100.0, z=-100.0 + 300.0, size=0xC0), dict()])
setup('above_top', pl=[dict(x=100.0, z=-100.0, top=40.0), dict(x=100.0, z=-100.0, top=60.0)])
setup('too_high', pl=[dict(x=100.0, z=-100.0, y=150.0), dict(x=100.0, z=-100.0, y=149.0)])
setup('too_low', pl=[dict(x=100.0, z=-100.0, y=-150.0), dict(x=100.0, z=-100.0, y=-80.0)], h=0x10)
setup('low_h', pl=[dict(x=100.0, z=-100.0, y=-60.0), dict()], h=0x20)
setup('three', np=3, pl=[dict(act=0), dict(hp=0), dict(x=100.0, z=-100.0)])
setup('np0', np=0)
setup('dt0', dt=0, st=(0xFFFF, 0x8000, 1, 0xFFFF, 0.5, 2.0), pl=[dict(act=0)])
setup('edge_99_9', pl=[dict(x=100.0 + 99.9, z=-100.0), dict()])
setup('top_eq', pl=[dict(x=100.0, z=-100.0, top=50.0), dict()])
setup('st0_zero', st=(0, 0, 0, 0x100, 0.25, 0.0), sc=(0.0, 0.0, 0.0), pl=[dict(act=0)])
