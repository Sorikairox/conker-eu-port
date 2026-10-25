#!/usr/bin/env python3
"""P314: setups for func_15175EC8 (ambient_flyer_update). Writes s5EC8.txt next to this script.
Object a0 = 80460000; type row / table / globals poked at EU addresses."""
import os, struct
O = 0x80460000
def fb(x): return struct.unpack('>I', struct.pack('>f', x))[0]
# EU addresses
ROW, DDF78, TBL = 0x800DE2B0, 0x800DE3A8, 0x8008D450
LVL, EVW, TMR = 0x800BEE10, 0x800C3A08, 0x800C39D0   # D_800BE9F0, word holding D_800C3A08 (+0) / D_800C35EA (+2)
DF5C, DF60, DT, D2138 = 0x800DE38C, 0x800DE390, 0x800BEE04, 0x800D2558
DBE5C, DC26C = 0x800DC28C, 0x800DC26C
RAND, KILL, SNDQ, SNDU, CHIRP = '150ADF00', '15169C9C', '1000F6C0', '1000FC0C', '10011278'
ATAN2, DIR, COS, SIN, DIST, VIS, FLOOR = '15048790', '15049398', '150ADC60', '150ADC6C', '150ADE40', '1510B460', '1510FE58'

BASE = dict(kind=0, slot=2, state=2, flags=0, model=0x1111, x=100.0, y=200.0, z=-50.0, speed=5, accel=1,
            pitch=10.0, heading=90.0, roll=5.0, pvel=0.5, tvel=1.0, rvel=0.5, floor=0.0, hx=0, hy=150, hz=0,
            rmax=500, rmin=100, yr=50, timer=10, climb=5, th=45.0, ty=180.0, surf=0, type=3, sound=0, alpha=0x80,
            fading=0,
            # type table / rows / globals
            smax=20, smin=2, wander=30, home=40, rollmax=15.0, pitchmax=20.0, turnmax=3.0, flapa=1.0, flapb=2.0,
            en=1, up=0x1111, down=0x2222, on78=1, lvl=0, ev=0, ev35=0, evt=0, f5c=1, f60=1, dt=2, d2138=0)

def h16(v): return v & 0xFFFF
def pokes(c):
    o, t = O, c['type']
    p = {}
    p[o + 0x00] = (c['kind'] & 0xFF) << 24
    p[o + 0x90] = (c['slot'] << 24) | (c['state'] << 16) | h16(c['flags'])
    p[o + 0x94] = c['model']
    for off, k in ((0x98, 'x'), (0x9C, 'y'), (0xA0, 'z'), (0xA8, 'pitch'), (0xAC, 'heading'), (0xB0, 'roll'),
                   (0xB4, 'pvel'), (0xB8, 'tvel'), (0xBC, 'rvel'), (0xC8, 'floor'), (0xE0, 'th'), (0xE4, 'ty')):
        p[o + off] = fb(c[k])
    p[o + 0xA4] = (h16(c['speed']) << 16) | h16(c['accel'])
    p[o + 0xD0] = (h16(c['hx']) << 16) | h16(c['hy'])
    p[o + 0xD4] = (h16(c['hz']) << 16) | h16(c['rmax'])
    p[o + 0xD8] = (h16(c['rmin']) << 16) | h16(c['yr'])
    p[o + 0xDC] = (h16(c['timer']) << 16) | h16(c['climb'])
    p[o + 0xE8] = c['surf']
    p[o + 0xEC] = (0x5A << 24) | (t << 16) | h16(c['sound'])
    p[o + 0xF0] = (c['alpha'] << 24) | (c['fading'] << 16) | 0x7777
    tb = TBL + t * 0x38
    p[tb] = (c['smax'] << 24) | (c['smin'] << 16) | (c['wander'] << 8) | c['home']
    for off, k in ((4, 'rollmax'), (8, 'pitchmax'), (0x10, 'turnmax'), (0x18, 'flapa'), (0x20, 'flapb')):
        p[tb + off] = fb(c[k])
    r = ROW + t * 0x14
    p[r], p[r + 4], p[r + 8] = c['en'], c['up'], c['down']
    p[DDF78 + t * 4] = c['on78']
    p[LVL], p[TMR], p[DT], p[D2138] = c['lvl'], c['evt'], c['dt'] & 0xFFFFFFFF, c['d2138']
    p[EVW] = ((c['ev'] & 0xFF) << 24) | ((c['ev35'] & 0xFF) << 8)
    p[DF5C] = c['f5c'] * 0x01010101
    p[DF60] = c['f60'] * 0x01010101
    p[DBE5C], p[DC26C] = 0x80450000, 0x80440000
    p[0x80450000 + 4 * 3] = 0x000000A7
    return ','.join('%08X=%08X' % (a, v & 0xFFFFFFFF) for a, v in sorted(p.items()))

S = []
def add(name, ret='', retf='', outa='', outw='', outb='', **kw):
    c = dict(BASE); c.update(kw)
    r = ret if ret else ''
    rf = '%s=%08X;%08X,%s=%08X;%08X' % (SIN, fb(0.5), fb(0.25), COS, fb(0.75), fb(-0.5))
    if retf: rf = rf + ',' + retf
    S.append('%-9s! 0=%08X ! %s ! %s ! %s ! %s ! %s ! %s' % (name, O, pokes(c), r, rf, outa, outw, outb))

# removal / gating
add('off', en=0)
add('off78', on78=0)
add('base')
add('flag1', flags=1)
add('dtneg', dt=-3)
# level-6 scatter event (types 8 / 9)
add('ev8wait', type=8, lvl=6, ev=0xF, ev35=1, evt=30, flags=0x4F)
add('ev9go', type=9, lvl=6, ev=0xF, ev35=1, evt=60, flags=0x5F, retf='%s=3F000000' % ATAN2)
add('ev8go', type=8, lvl=6, ev=0xF, ev35=1, evt=99, flags=0x0C, x=-3000.0, z=3000.0, retf='%s=BF800000' % ATAN2)
add('ev8circ', type=8, lvl=6, ev=0xF, ev35=1, evt=99, flags=0x200, pvel=1.0, tvel=0.1, rvel=500.0, y=0.0)
add('ev8sink', type=8, lvl=6, ev=0xF, ev35=1, evt=99, flags=0x200, pvel=1.0, tvel=0.149, rvel=61.0, y=-3090.0)
add('ev8r59', type=8, lvl=6, ev=0xF, ev35=1, evt=99, flags=0x200, pvel=1.0, tvel=0.1, rvel=65.9, y=0.0)
add('ev8lvl5', type=8, lvl=5, ev=0xF, ev35=1, evt=99, flags=0x208, tvel=0.2, rvel=50.0)
add('ev7', type=7, lvl=6, ev=0xF, ev35=1, evt=99, flags=0x208)
add('ev8ev35', type=8, lvl=6, ev=0xF, ev35=0, evt=99, flags=0x208)
add('ev8evE', type=8, lvl=6, ev=0xE, ev35=1, evt=99, flags=0x208)
add('circend', flags=0x200, ev=0xE, ev35=1, rvel=100.0)
add('circ35', flags=0x200, ev=0xF, ev35=0, rvel=100.0)
add('circok', flags=0x202, ev=0xF, ev35=1, rvel=100.0, ret='%s=1;0' % VIS)
# fading
add('fadein', alpha=0xFA)
add('fadeFF', alpha=0xFF)
add('fade8', flags=8, f5c=0)
add('fade8on', flags=8, f5c=1, alpha=0x10)
add('fadeout', fading=1, alpha=0x80)
add('fadeclp', fading=1, alpha=5)
add('fade0', fading=1, alpha=0)
add('fadeFE', alpha=0xFE)
add('fadeFFn', alpha=0xFF, dt=-1)
add('fadeFC', alpha=0xFC, dt=1)
add('fade1', fading=1, alpha=1)
add('fade7', fading=1, alpha=7)
# sound
add('sndon', sound=0x1234, ret='%s=1' % SNDQ, x=-120.7, y=33000.0, z=12.9)
add('sndoff', sound=0x8234, ret='%s=0' % SNDQ)
# tether (flag 4)
add('tfar', flags=4, ret='%s=258,%s=30' % (DIST, DIR))
add('tfarwrap', flags=4, ret='%s=1F5,%s=FF' % (DIST, DIR), x=-300.0, z=400.0, hx=-20, hz=33)
add('tnear', flags=0x14, ret='%s=32,%s=90' % (DIST, DIR))
add('tnear2', flags=0x14, ret='%s=32,%s=10' % (DIST, DIR))
add('tnear3', flags=0x14, ret='%s=32,%s=80' % (DIST, DIR))
add('tnearno', flags=4, ret='%s=32' % DIST)
add('tedge', flags=0x14, ret='%s=1F4' % DIST, rmin=0x1F4)
add('tedge2', flags=0x14, ret='%s=63' % DIST)
add('st3pos', flags=4, state=3, th=100.0, heading=50.0, tvel=0.5, ret='%s=C8' % DIST)
add('st3neg', flags=4, state=3, th=10.0, heading=50.0, tvel=-0.5, ret='%s=C8' % DIST)
add('st3wrap', flags=4, state=3, th=350.0, heading=10.0, tvel=-0.5, ret='%s=C8' % DIST)
add('st3wrap2', flags=4, state=3, th=5.0, heading=300.0, tvel=0.5, ret='%s=C8' % DIST)
add('st3opp', flags=4, state=3, th=100.0, heading=50.0, tvel=-0.5, ret='%s=C8' % DIST)
add('st3opp2', flags=4, state=3, th=10.0, heading=50.0, tvel=0.5, ret='%s=C8' % DIST)
add('st3eq', flags=4, state=3, th=50.0, heading=50.0, tvel=0.5, ret='%s=C8' % DIST)
add('st3d180', flags=4, state=3, th=230.0, heading=50.0, tvel=0.5, ret='%s=C8' % DIST)
add('st2pos', flags=4, state=2, tvel=2.5, timer=10, ret='%s=C8' % DIST)
add('st2posz', flags=4, state=2, tvel=0.5, timer=10, ret='%s=C8' % DIST)
add('st2neg', flags=4, state=2, tvel=-2.5, timer=10, ret='%s=C8' % DIST)
add('st2negz', flags=4, state=2, tvel=-0.5, timer=10, ret='%s=C8' % DIST)
add('st2zero', flags=4, state=2, tvel=0.0, timer=2, ret='%s=C8,%s=12345' % (DIST, RAND))
add('st2tmr', flags=4, state=2, tvel=0.0, timer=3, ret='%s=C8,%s=FFFFFFF0' % (DIST, RAND), wander=77)
add('st2tmr1', flags=4, state=2, tvel=1.0, timer=1, ret='%s=C8,%s=167' % (DIST, RAND))
add('st2posd1', flags=4, state=2, tvel=0.8, timer=10, dt=1, ret='%s=C8' % DIST)
add('st2tmrn', flags=4, state=2, tvel=0.0, timer=1, ret='%s=C8,%s=FFFFFFF0' % (DIST, RAND))
add('st4', flags=4, state=4, tvel=1.0, ret='%s=C8' % DIST)
add('tmaxp', flags=4, state=4, tvel=5.0, turnmax=3.0, ret='%s=C8' % DIST)
add('tmaxn', flags=4, state=4, tvel=-5.0, turnmax=3.0, ret='%s=C8' % DIST)
add('tmaxeq', flags=4, state=4, tvel=-3.0, turnmax=3.0, ret='%s=C8' % DIST)
add('tmax35', flags=4, state=4, tvel=3.5, turnmax=3.0, ret='%s=C8' % DIST)
# floor (flag 0x80)
add('floor0', flags=0x80, ret='%s=7B' % FLOOR, outw='%s=3:0' % FLOOR)
add('floor1', flags=0x80, ret='%s=FFFFFF85' % FLOOR, outw='%s=3:80440024' % FLOOR)
# height bob (flag 0x40)
add('bobexp', flags=0x40, climb=2, ret='%s=1234567' % RAND, y=100.0)
add('bobexp2', flags=0x40, climb=1, ret='%s=FFFFFF00' % RAND, y=400.0, yr=-7)
add('bobexp3', flags=0x40, climb=1, ret='%s=1E' % RAND, y=180.0, yr=50, hy=150)
add('bobup', flags=0x40, climb=9, pitch=3.0)
add('bobdn', flags=0x40, climb=9, pitch=-3.0)
add('bob0', flags=0x40, climb=9, pitch=0.0)
add('bobm1', flags=0x40, climb=-1, pvel=0.5, y=100.0, ty=180.0)
add('bobm2', flags=0x40, climb=-1, pvel=0.5, y=200.0, ty=180.0)
add('bobm3', flags=0x40, climb=-1, pvel=-0.5, y=200.0, ty=180.0)
add('bobm4', flags=0x40, climb=-1, pvel=-0.5, y=100.0, ty=180.0)
add('bobm5', flags=0x40, climb=-1, pvel=0.0, y=100.0, ty=180.0)
# movement
add('plo', pitch=-19.8, pvel=-0.5)
add('phi', pitch=19.8, pvel=0.5)
add('pmid', pitch=-19.0, pvel=-0.5)
add('hwrapn', heading=0.5, tvel=-1.0)
add('hwrapp', heading=359.5, tvel=1.0)
add('hwrap0', heading=359.0, tvel=1.0)
add('turnmin', tvel=0.2, roll=3.0)
add('turnmin2', tvel=-0.2, roll=-3.0)
add('turn21', tvel=0.21, roll=3.0)
add('flag20', flags=0x20, tvel=-1.5, roll=3.0, rvel=9.0)
add('rclhi', tvel=-1.5, roll=14.0)
add('rcllo', tvel=1.5, roll=-14.0)
add('rclmid', tvel=1.5, roll=-13.0, rollmax=14.5)
add('rollp', tvel=0.1, roll=0.5)
add('rolln', tvel=0.1, roll=-0.5)
add('roll0', tvel=0.1, roll=0.0, rvel=7.0)
add('rollbig', tvel=0.1, roll=1.5)
add('rollbign', tvel=-0.1, roll=-1.5)
add('rollz', tvel=0.1, roll=1.2)
add('rollz2', tvel=0.1, roll=1.18)
add('spdlo', speed=1, accel=-3)
add('spdhi', speed=19, accel=4)
add('spdmid', speed=19, accel=1)
add('spdeq', speed=2, accel=0)
# wing model
add('mup', pitch=1.0, model=0x1111)
add('mup0', pitch=0.0, pvel=0.0, model=0x1111)
add('mupx', pitch=1.0, model=0x2222)
add('mdn', pitch=-5.0, model=0x2222)
add('mdnx', pitch=-5.0, model=0x1111)
add('mfa', pitch=1.0, flapa=2.0, flapb=2.0)
add('mfb', pitch=-5.0, model=0x2222, flapa=-2.0, flapb=2.0)
add('mfb2', pitch=-5.0, model=0x2222, flapa=-1.0, flapb=2.0)
add('mfl1', pitch=1.0, flags=1)
# chirp
add('chirp', kind=0x13, f60=0, ret='%s=FF;FFFFFFFF' % RAND)
add('chirp2', kind=0x13, f60=0, ret='%s=3;12' % RAND, x=-5.5, y=-9.9, z=1e4)
add('chirpno', kind=0x13, f60=1)
add('chirpf2', kind=0x13, f60=2)
add('chirpk', kind=0x12, f60=0)
# view cull (flag 2)
add('cull0', flags=2, ret='%s=0' % VIS)
add('cull1', flags=2, ret='%s=1' % VIS)
add('cull2a', flags=2, d2138=1, ret='%s=1;0' % VIS)
add('cull2b', flags=2, d2138=1, ret='%s=1;1' % VIS)
add('cull2c', flags=2, d2138=2, ret='%s=1;0' % VIS)
# everything at once
add('all', flags=0xF6, state=3, kind=0x13, f60=0, sound=7, ret='%s=1,%s=258,%s=40,%s=5;6;7,%s=1;1,%s=9' % (SNDQ, DIST, DIR, RAND, VIS, FLOOR),
    outw='%s=3:80440030' % FLOOR, d2138=1, climb=1)
out = os.path.join(os.path.dirname(os.path.abspath(__file__)), 's5EC8.txt')
with open(out, 'w') as fh:
    fh.write('# func_15175EC8 setups (gen5EC8.py): object a0 = 80460000; name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB\n')
    fh.write('\n'.join(S) + '\n')
print(len(S), 'setups ->', out)
