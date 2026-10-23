#!/usr/bin/env python3
"""P86: knob setups for func_151552F0 (2D sprite -> scissored texture rectangle). Writes s52f0.txt (knobs.sh format:
name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB). EU addresses: D_800BE628 = 800BEA48 (view records, 0x180),
D_80082FA4 = 80083334 (.data: pokes reach it on even trials only, so all four records get the same values),
D_800C35EA = 800C3A0A. D_80090F10 / D_800A4EA8 are left at their ROM values. jal targets (decoded): func_15142E24
15143394, func_15142B7C 151430EC, func_151441A4 15144714, func_151442FC 1514486C, func_15142C10 15143180,
func_15142CF0 15143260, func_1513F4E4 1513FA54, func_15142FBC 1514352C, func_15182238 / func_1517F470 same."""
import random, struct

def fb(f): return '%08X' % struct.unpack('>I', struct.pack('>f', f))[0]

GDL, SPR, VIEW = 0x80500000, 0x80520000, 0x80540000
out = []

def setup(name, view=0, flags=0, tex=5, x=160.0, y=120.0, hw=16.0, hh=8.0, player=0, c35ea=0, on=1, life=0,
          sc=(1.0, 1.0), off=(0.0, 0.0), vs=(1.0, 1.0), vo=(0.0, 0.0), rm=1, cols=None, gdlret=0x80510000):
    pk = {}
    w = {}
    def b(addr, val):
        a = addr & ~3
        pk.setdefault(a, [0, 0, 0, 0])[addr & 3] = val & 0xFF
    b(0x800C3A0A, c35ea)
    w[0x800BEA48] = '%08X' % VIEW
    w[0x80083334] = '%08X' % 0
    for k in range(4):
        base = VIEW + k * 0x180
        w[base + 0x14] = fb(vs[0]); w[base + 0x18] = fb(vs[1])
        w[base + 0x34] = fb(vo[0]); w[base + 0x38] = fb(vo[1])
    for off_, v in ((0x10, x), (0x14, y), (0x18, hw), (0x1C, hh), (0x58, sc[0]), (0x5C, sc[1]), (0x60, off[0]), (0x64, off[1])):
        w[SPR + off_] = fb(v)
    b(SPR + 0x20, tex)
    b(SPR + 0x24, flags >> 8); b(SPR + 0x25, flags)
    cols = cols or [0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xF0, 0xE1]
    for i, c in enumerate(cols[:9]):
        b(SPR + 0x2B + i, c)
    w[SPR + 0x34] = '00000010'; w[SPR + 0x38] = '00000200'; w[SPR + 0x3C] = '00040000'; w[SPR + 0x40] = '%08X' % rm
    b(SPR + 0x47, 0x07)
    w[SPR + 0x48] = '00100000'; w[SPR + 0x4C] = '00000001'
    b(SPR + 0x50, cols[9]); b(SPR + 0x51, cols[10]); b(SPR + 0x54, player)
    pokes = ['%08X=%02X%02X%02X%02X' % ((a,) + tuple(v)) for a, v in sorted(pk.items()) if a not in w]
    pokes += ['%08X=%s' % (a, v) for a, v in sorted(w.items())]
    args = '0=%08X,1=%08X,2=%X' % (GDL, SPR, view & 0xFFFF)
    g = '%08X' % gdlret
    ret = ','.join('%s=%s' % (f, g) for f in ('15143394', '151430EC', '15143180', '15143260', '1513FA54', '1514352C'))
    ret += ',15182238=%X,1517F470=%X' % (on, life)
    outb = '15144714=0:00;12/1:FF;F4/2:01;30/3:00;FF,1514486C=0:00;40/1:00;00/2:80;01/3:7F;FF'
    out.append(' ! '.join([name, args, ','.join(pokes), ret, '', '', '', outb]))

setup('base')
setup('notex', tex=0xFF)
setup('tex0', tex=0)
setup('tex9', tex=9, flags=0x200)
setup('m400', flags=0x400)
setup('m600', flags=0x600, tex=2)
setup('pl_eq', flags=0x10, player=0)
setup('pl_ne', flags=0x10, player=1)
setup('pl_v2', flags=0x10, player=2, view=2)
setup('pl_v3n', flags=0x10, player=2, view=3)
setup('c35_1', flags=0x40, c35ea=1)
setup('c35_0', flags=0x40, c35ea=0)
setup('c35_2', flags=0x40, c35ea=2)
setup('c35_nf', flags=0, c35ea=1)
for v in range(4):
    bit = 1 << (11 + v)
    setup('vb%d_on' % v, view=v, flags=bit, on=1, life=200)
    setup('vb%d_off' % v, view=v, flags=bit, on=0, life=0)
    setup('vb%d_201' % v, view=v, flags=bit, on=1, life=201)
    setup('vb%d_neg' % v, view=v, flags=bit, on=1, life=0xFFFFFF00)
setup('vb_other', view=1, flags=1 << 11, on=0)
setup('flipS', flags=2)
setup('flipT', flags=4)
setup('flipST', flags=6, tex=3)
setup('scale', flags=0x80, sc=(0.5, 2.0))
setup('scale0', flags=0x80, sc=(0.0, 0.0))
setup('scaleneg', flags=0x86, sc=(-1.5, 0.75))
setup('offs', flags=0x100, off=(3.5, -7.25))
setup('offs_fl', flags=0x106, off=(-100.5, 64.0))
setup('w0', hw=-0.125, hh=-0.125)
setup('w0f', hw=-0.125, hh=-0.125, flags=6)
setup('left_neg', x=-5.0, hw=20.0)
setup('left_negS', x=-5.0, hw=20.0, flags=2)
setup('top_neg', y=-3.0, hh=10.0)
setup('top_negT', y=-3.0, hh=10.0, flags=4)
setup('both_neg', x=-30.0, y=-40.0, hw=50.0, hh=60.0, flags=6)
setup('both_neg2', x=-30.0, y=-40.0, hw=50.0, hh=60.0)
setup('small', hw=0.1, hh=0.2)
setup('big', x=9000.0, y=8500.0, hw=500.0, hh=400.0)
setup('bigneg', x=-9000.0, y=-8500.0, hw=500.0, hh=400.0, flags=6)
setup('ybig', y=9000.0, hh=10.0)
setup('ybig2', y=8300.0, hh=200.0, x=8300.0, hw=200.0)
setup('view_sc', vs=(1.25, 0.8), vo=(12.0, -6.5), flags=0x1A6, sc=(1.1, 0.9), off=(1.0, 2.0))
setup('neg_hw', hw=-10.0, hh=-4.0)
setup('rm', rm=3, flags=0x400)
rng = random.Random(860)
for k in range(12):
    v = rng.randrange(4)
    setup('mix%02d' % k, view=v, flags=rng.randrange(0x10000) & ~0x50 | rng.choice([0, 0x10, 0x40]),
          tex=rng.choice([0, 1, 4, 7, 0xFF]), x=rng.uniform(-60, 380), y=rng.uniform(-60, 300),
          hw=rng.uniform(-5, 80), hh=rng.uniform(-5, 80), player=rng.randrange(4), c35ea=rng.choice([0, 1]),
          on=rng.choice([0, 1, 1]), life=rng.choice([0, 150, 200, 201, 255]),
          sc=(rng.uniform(-2, 2), rng.uniform(-2, 2)), off=(rng.uniform(-50, 50), rng.uniform(-50, 50)),
          vs=(rng.uniform(0.5, 2), rng.uniform(0.5, 2)), vo=(rng.uniform(-20, 20), rng.uniform(-20, 20)),
          rm=rng.randrange(6), cols=[rng.randrange(256) for _ in range(11)])
open(__file__.replace('gen52f0.py', 's52f0.txt'), 'w').write('\n'.join(out) + '\n')
print(len(out), 'setups')
