#!/usr/bin/env python3
# P311: writes s6c8.txt, the func_151206C8 (player_camera_update) setups. Player at 0x80480000 (a0), camera block
# +0x740, player object +0x3D0 = 0x80490000 (+0x31C -> 0x804C0000), camera object +0x3D4 = 0x804A0000, controller
# +0x36C = 0x804B0000 (buttons, stick x, stick y). EU: D_800D1940 = 0x800D1D60, D_800BE616 = 0x800BEA36,
# D_800BE9E4 = 0x800BEE04. EU jal keys: sinf 15048050, cosf 15047EF0, func_15048A70 15048D60, func_1510ED24 (floor
# height out through a2). Line: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB
import struct, os
def f(x): return struct.unpack('>I', struct.pack('>f', x))[0]
BASE = dict(mode=5, state=2, snap=0, b23D=7, b600=0, f604=0.5, b3E8=0, b84C=0, t84A=0, f5F0=0, f84=0,
            follow=1, force=0, dir=0xFF, lock=0, btn=0, sx=20, sy=-12, g42=0, g616=0, delta=2,
            yawT=30.0, pitchT=10.0, pitch=20.0, dist=300.0, dlim=100.0, f370=0, f360=0.0, yawG=45.0)
def words(d):
    w = {}
    def F(o, v): w[0x80480000 + o] = f(v)
    W = lambda a, v: w.__setitem__(a, v & 0xFFFFFFFF)
    W(0x80480084, d['f84']); W(0x80480134, 0x11); W(0x8048013C, 0x22)
    for i, o in enumerate((0x18C, 0x190, 0x194, 0x198)): F(o, 11.0 + 7 * i)
    W(0x8048023C, (d['snap'] << 24) | (d['b23D'] << 16) | (d['mode'] << 8))
    for i, o in enumerate((0x2BC, 0x2C0, 0x2C4, 0x2F8, 0x2FC, 0x300, 0x304, 0x308, 0x30C)): F(o, [100.5, 40.25, -60.0, 130.0, 55.5, -20.0, 140.0, 66.0, -30.0][i])
    F(0x360, d['f360']); W(0x8048036C, 0x804B0000); F(0x37C, 33.0); W(0x804803D0, 0x80490000); W(0x804803D4, 0x804A0000)
    W(0x804803E8, d['b3E8'] << 24); W(0x804805F0, d['f5F0']); W(0x80480600, d['b600'] << 24); F(0x604, d['f604'])
    W(0x8048073C, (d['state'] << 16) | 0x1234); F(0x7B4, 0.75); W(0x80480848, d['t84A'] & 0xFFFF); W(0x8048084C, d['b84C'] << 24)
    F(0x8B4, 12.5)
    F(0x760, d['yawG']); F(0x764, 210.0); F(0x768, 77.0); F(0x770, 5.5); F(0x774, d['yawT']); F(0x778, d['pitchT'])
    F(0x77C, d['pitch']); F(0x784, d['dist']); F(0x788, d['dlim']); W(0x8048078C, (d['force'] << 24) | (d['follow'] << 16) | (d['dir'] << 8))
    W(0x804807A4, d['lock'])
    W(0x80490040, f(123.0)); W(0x80490078, 0x9876); W(0x80490180, f(48.0)); W(0x8049031C, 0x804C0000); W(0x804C01A0, 0x5A00)
    W(0x804A0010, 0x0400); W(0x804B0000, ((d['btn'] & 0xFFFF) << 16) | ((d['sx'] & 0xFF) << 8) | (d['sy'] & 0xFF))
    W(0x800D1D60, d['g42'] << 24); W(0x800BEA34, d['g616'] << 8)  # D_800BE616 = byte 0x800BEA36; W(0x800BEE04, d['delta'])
    w.update(d.get('extra', {}))
    return ','.join('%08X=%08X' % kv for kv in sorted(w.items()))
S = []
TRIG = '15048050=3F000000;BF000000;3E800000;3F400000;BE800000,15047EF0=3F5DB3D7;BF000000;3F400000;3E000000'
def add(name, retf='', outw='1510ED24=2:42480000', **kw):
    d = dict(BASE); d.update(kw)
    r = TRIG + (',' + retf if retf else ',15048D60=41F00000')
    S.append('%s ! 0=80480000 ! %s !  ! %s !  ! %s !' % (name, words(d), r, outw))
add('m1run', state=1, dir=0xFF, f370=0)            # f370 computed: player-camera distance (~33) < 100 -> reach
add('m1far', state=1, dir=1)                         # 100 < 33 false, force 0
add('m1force', state=1, dir=1, force=1, b600=1)
add('m1timer', state=1, t84A=5)
add('m1expire', state=1, t84A=2)
add('m1nofol', state=1, follow=0)
add('m1snap', state=1, snap=1, g42=0x42, mode=0x1A)
add('m1snap2', state=1, snap=1, mode=6)
add('m2base', state=2)
add('m2mode0', state=2, mode=0)
add('m2lock', state=2, follow=0, sx=50)
add('m2lockL', state=2, follow=0, sx=-50)
add('m2lock0', state=2, follow=0, sx=0, sy=0)
add('m2lock3E8', state=2, follow=0, b3E8=1, lock=3)
add('m2lockset', state=2, follow=0, lock=1, sx=-40)
add('m2lockset2', state=2, follow=0, lock=2, sx=40)
add('m2lockp', state=2, follow=0, lock=1, sx=40)
add('m2ride', state=2, mode=9, pitchT=-30.0, b84C=0)
add('m2ride616', state=2, mode=0x38, b84C=1, g616=1, btn=0x2000, pitchT=-30.0)
add('m2ride38', state=2, mode=0x38, b84C=0, btn=0x0000, pitchT=-10.0)
add('m2leave', state=2, b84C=1)
add('m2special', state=2, mode=0x1A, g42=0x42)
add('m2m1A', state=2, mode=0x1A)
add('m2aim', state=2, mode=2, f5F0=2, pitchT=50.0)
add('m2aimb', state=2, mode=0xA, pitchT=-50.0)
add('m2m34', state=2, mode=0x34, pitchT=-10.0, sx=-7)
add('m2m34b', state=2, mode=0x34, pitchT=20.0)
add('m2m12', state=2, mode=0x12, pitchT=20.0)
add('m2m12b', state=2, mode=0x12, pitchT=-50.0)
add('m2hi', state=2, pitchT=100.0, pitch=400.0)
add('m2lo', state=2, pitchT=-60.0, pitch=-400.0)
add('m2p180', state=2, pitch=180.0)
add('m2snap', state=2, snap=1)
add('m2snapS', state=2, snap=1, mode=0x1A, g42=0x42)
add('m2modeD', state=2, mode=0xD)
add('m2modeF', state=2, mode=0xF)
add('m2mode3', state=2, mode=3, b600=1, f604=1.5)
add('m2mode3n', state=2, mode=3, b600=1, f604=-1.5)
add('m2m2A', state=2, mode=0x2A)
add('m3', state=3, follow=1, f5F0=0x40)
add('m3done', '15048D60=3C23D70A', state=3, follow=1)
add('m3far', '15048D60=C2B40000', state=3, follow=1)
add('m3f360', state=3, follow=1, f360=0.0)
add('m3f360b', state=3, follow=1, f360=2.0)
add('m3expire', state=3, t84A=1)
add('m3timer', state=3, t84A=9)
add('m3ride', state=3, mode=9)
add('m3flag', state=3, f84=0x200000)
add('m0', state=0, mode=0x13, snap=1)
add('m0b', state=0, mode=7)
add('m0aim', state=0, mode=0x34, f5F0=2)
add('m3state', state=3, mode=3)
add('m1near', state=1, dir=0xFF, dlim=40.0)       # 49.7 < 40 false: no easing
add('m2lock4', state=2, follow=0, lock=4, sx=-30)  # neither lock bit
add('m2m34c', state=2, mode=0x34, pitchT=14.5, sy=0) # no stick y: inside the 15 limit
add('m2p185', state=2, pitch=185.0)
add('m2lo2', state=2, pitch=-800.0)
open(os.path.join(os.path.dirname(os.path.abspath(__file__)), 's6c8.txt'), 'w').write(
    '# func_151206C8 setups (generated by gen6c8.py): see the header of gen6c8.py\n' + '\n'.join(S) + '\n')
