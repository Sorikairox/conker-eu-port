#!/usr/bin/env python3
# P180: difftest setups for the func_1500BEC0 unit (run with DIFFTEST_ROMDATA=1: D_80096090 / D_80096014 / D_80083110 /
# D_8008D258 / D_8008D2A0 are .game_data). Fields: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW. EU addresses.
import os
D = os.path.dirname(os.path.abspath(__file__))
def h16(v): return '%04X' % (v & 0xFFFF)
def tri_pokes(vs, base=0x80440000):
    p = []
    for k, (x, y, z) in enumerate(vs):
        va = base + 0x100 * (k + 1)
        p += ['%08X=%08X' % (base + 4 * k, va), '%08X=%s%s' % (va, h16(x), h16(y)), '%08X=%s0000' % (va + 4, h16(z))]
    return p
TRIS = {'a': [(100, -50, 7), (200, 20, -9), (-30, 400, 5)], 'b': [(-3000, 12, -700), (-2990, -14, -650), (-3100, 5, -820)],
        'c': [(30000, -30000, 32000), (-32000, 31000, -31000), (31500, 200, 100)], 'd': [(5, 5, 5), (5, 5, 5), (5, 5, 5)]}
RNG = '151EFDD0=1234;7;FFFFFFF3;80000000;3;55'
def w(name, rows): open(os.path.join(D, name), 'w').write('\n'.join(' ! '.join(r) for r in rows) + '\n')

# func_1500AF08 (index, slot, mode, x, y, z, spread, kind, phase); capacity 0x40 at D_800B0DF0 +0x18
def af08(n, idx, slot, spread, rng0=2, rng1=3, ddc00=0, id_=0, phase=5, cap=0x40):
    de000 = ['%08X=%02X%02X%02X%02X' % (0x800DE000 + 4 * (s // 4), *[rng0] * 4) for s in range(0, 16, 4)]
    ids = ['%08X=%02X%02X%02X%02X' % (0x800DDFF0 + 4 * (s // 4), *[id_] * 4) for s in range(0, 16, 4)]
    pk = ['800B1200=80450000', '80450018=%04X0000' % cap, '800DE148=80460000', '800DE030=%08X' % ddc00,
          '800BE858=%s%s' % (h16(0x123), h16(-0x77)), '800BE85C=%s%s' % (h16(0x400), h16(0x40))] + de000 + ids
    for s in range(15): pk.append('%08X=%s%s' % (0x800BE858 + 4 * s, h16(0x100 + s * 0x31), h16(-0x40 + s * 9)))
    return [n, '0=%X,1=%X,2=2,3=FF85,4=1234,5=FFFFFF80,6=%X,7=AB,8=%X' % (idx, slot, spread, phase), ','.join(pk),
            '151EFDD0=%X;%X' % (rng1, 0x7FFF1)]
w('af08_setups.txt', [af08('lim', 0x3F, 1, 0x80), af08('over', 0x50, 1, 0x80), af08('neg', 0xFFFFFFFF, 1, 0x80),
    af08('zero', 0, 0, 0), af08('sp0', 7, 3, 0), af08('sp80', 7, 3, 0x80), af08('spneg', 9, 2, 0x80, rng1=0xFFFFFF01),
    af08('flag4', 9, 2, 0x80, id_=0x15), af08('flag4b', 0x3E, 14, 0x23, id_=0x17), af08('r1', 4, 5, 0x80, rng0=1),
    af08('ddc', 6, 4, 0x80, ddc00=0x10, phase=7), af08('ddcp0', 6, 4, 0x80, ddc00=0x10, phase=6), af08('ddcoff', 6, 4, 0x80, ddc00=0xFFEF),
    af08('cap1', 0, 1, 0x80, cap=1), af08('cap0', 0, 1, 0x80, cap=0), af08('cap2', 0, 3, 0x80, cap=2)])

# placers (param, kind, slot, mode, index, tri); func_1500AF08 stub returns index + 1 ...
def plc(n, param, tri, idx=5, ret='1500AEB8=6;7;8;9;A;B;C;D'):
    return [n, '0=%X,1=3,2=4,3=2,4=%X,5=80440000' % (param & 0xFFFF, idx), ','.join(tri_pokes(TRIS[tri])), ret]
rows = [plc('n%d%s' % (c, t), c, t) for t in 'abcd' for c in (1, 3, 7)] + [plc('cap', 4, 'a', ret='1500AEB8=3F')]
for k in ('b1f4', 'b8f4', 'bab8', 'bc7c'): w(k + '_setups.txt', rows)
w('b714_setups.txt', [plc('v%X%s' % (v, t), v, t) for t in 'abcd' for v in (0x1F4, 0x3E, 0x3F, 0x0F, 0xFFFF, 0x8000)])
# shape placer: plane via D_800CC630..63C (func_15049350 is a stub), D_800BE850 phase bits
def b3b0(n, shape, tri, plane, be850=0x5A5A, slot=4):
    pk = tri_pokes(TRIS[tri]) + ['800CC630=%08X' % plane[0], '800CC634=%08X' % plane[1], '800CC638=%08X' % plane[2],
                                 '800CC63C=%08X' % plane[3], '800BE850=%04X0000' % be850]
    return [n, '0=%X,1=3,2=%X,3=2,4=5,5=80440000' % (shape, slot), ','.join(pk), '1500AEB8=6;7;8;9;A;B;C;D;E;F;10']
P1 = (0x3F000000, 0x40000000, 0xBF800000, 0x44FA0000); P0 = (0x3F000000, 0, 0x3E800000, 0x42C80000)
w('b3b0_setups.txt', [b3b0('s%d%s%s' % (s, t, pn), s, t, pl, slot=s * 5) for s in (0, 1, 2) for t in 'abc' for pn, pl in (('p', P1), ('z', P0))])

# func_1500AD84 (slot, id, flags): ids with info flags 0x10 (0, 4), 0x80 (0x12), 8 (1, 0x1D), 1, 4 (0x15)
w('ad84_setups.txt', [['s%X_i%X_f%X' % (s, i, f), '0=%X,1=%X,2=%X' % (s, i, f), '800DE030=00000101,800DE034=00010000,800DE038=80000000', ''] for s, i, f in
    ((0, 0, 3), (5, 1, 0x84), (14, 0x12, 0x7F), (3, 0xFF, 0x81), (7, 4, 0xFF80), (2, 0x1D, 0x180), (9, 0x15, 0), (1, 0x3B, 0x82), (6, 0x47, 0xFFFF))])

# func_1517BE0C (lo, hi): records at 80460000 (14 bytes), key D_8008D254 (run WITHOUT ROMDATA: .game_data word poked)
def be0c(n, keys, lo, hi, zkey, dup=False):
    import struct
    b = bytearray()
    for k, v in enumerate(keys):
        b += struct.pack('>hhhBBBBBBBB', v if not zkey else 7 * k, -k, v if zkey else 3 * k, k, 0x11, k + 1, 0, 0x22, 0x33, 0x44, 0x55)
    b += bytes(-len(b) % 4)
    pk = ['800DE148=80460000', '8008D254=%08X' % (1 if zkey else 0)] + ['%08X=%s' % (0x80460000 + i, b[i:i + 4].hex().upper()) for i in range(0, len(b), 4)]
    return [n, '0=%X,1=%X' % (lo & 0xFFFFFFFF, hi & 0xFFFFFFFF), ','.join(pk), '']
K1 = [50, -3, 700, 12, 12, -900, 4, 33, 1, 0]; K2 = [5, 4, 3, 2, 1, 0, -1, -2]; K3 = [1, 2, 3, 4, 5, 6, 7]; K4 = [9, 9, 9, 9, 9]
w('be0c_setups.txt', [be0c('x1', K1, 0, 9, 0), be0c('z1', K1, 0, 9, 1), be0c('x2', K2, 0, 7, 0), be0c('z2', K2, 0, 7, 1), be0c('x3', K3, 0, 6, 0),
    be0c('x4', K4, 0, 4, 0), be0c('sub', K1, 2, 7, 0), be0c('zsub', K1, 3, 8, 1), be0c('one', K1, 4, 4, 0), be0c('neg', K1, 0, -1, 0), be0c('two', K1, 0, 1, 1)])

# func_1500BEC0: capacity 0x20, slots D_800BE4A0, triangle flags D_800DBE5C (80470000), triangles D_800DC26C (80480000)
def bec0(n, scene=1, flag38=0, cap=0x20, nflags=None, rows=(0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4), de000=(0, 3, 1, 0x57, 2, 0, 8, 1, 0, 0x21, 3, 2, 0, 1, 6),
         flagsptr=0x80470000, ddd20=0, rh=None):
    fl = nflags if nflags is not None else [0x00010000, 0x00000000, 0x00120040, 0x00230060, 0x00340020, 0x00450000, 0x00F60000, 0x00710000, 0x000F0000, 0x80000000]
    pk = ['800B1200=80450000', '80450018=%04X0000' % cap, '800BEE10=%08X' % scene, '800383E0=%02X000000' % flag38,
          '800DC28C=%08X' % flagsptr, '800DC27C=%08X' % len(fl), '800DC26C=80480000', '800DE150=%08X' % ddd20]
    pk += ['%08X=%04X%04X' % (0x800BE8C0 + 4 * s, (s * 3) & 0xFF if s != 4 else 0xFF, 0x80 | s if s % 3 == 0 else s) for s in range(15)]
    r = list(rows) + [0]; d = list(de000) + [0]
    pk += ['%08X=%02X%02X%02X%02X' % (0x800DE0B0 + i, *r[i:i + 4]) for i in range(0, 16, 4)]
    pk += ['%08X=%02X%02X%02X%02X' % (0x800DE000 + i, *d[i:i + 4]) for i in range(0, 16, 4)]
    pk += ['%08X=%08X' % (0x80470000 + 4 * i, f) for i, f in enumerate(fl)]
    ret = rh or '1500B1A4=3;5,1500B6C4=6,1500B8A4=9;A,1500BA68=C,1500B360=10,1500BC2C=14'
    return [n, '', ','.join(pk), '10003E90=80460000,151EFDD0=1234;FFFFFFF3;7;80000001;55,' + ret]
w('bec0_setups.txt', [bec0('base'), bec0('s6off', scene=6), bec0('s6on', scene=6, flag38=1), bec0('s1d', scene=0x1D), bec0('cap0', cap=0),
    bec0('noflags', flagsptr=0), bec0('nflag0', nflags=[]), bec0('neg', rh='1500B1A4=FFFFFFFE,1500B6C4=0,1500B8A4=0,1500BA68=0,1500B360=0,1500BC2C=0'),
    bec0('one', nflags=[0x00610000]), bec0('rows0', rows=(0,) * 15), bec0('rows3', rows=(3,) * 15, de000=(0,) * 15), bec0('pre', ddd20=7)])
