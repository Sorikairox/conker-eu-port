#!/usr/bin/env python3
"""P85: knob setups for func_15180AF0 (sniper scope overlay). Writes s0af0.txt (p85/knobs.sh format:
name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB). EU addresses (undefined_syms_auto.txt):
D_800DDE40 = 800DE270 (u8), D_800C35EA = 800C3A0A (u8), D_800DDDC8 = 800DE1F8 (f32[view]), D_800DDE1C = 800DE24C
(u8[view]), D_800DE1A8 (u8[view]), D_800DE218 (f32[view][2]), D_800BE628 = 800BEA48 (view records, 0x180 each).
D_800A766C / D_800A7670 are .game_data (0.01 / -399.0 in the ROM): poked with the same values (POKE only reaches
them on even trials)."""
import random, struct

def fb(f): return '%08X' % struct.unpack('>I', struct.pack('>f', f))[0]

GDL, VIEW, PTRS = 0x80500000, 0x80540000, 0x80560000

def bytepoke(pk, addr, val):
    """set one byte inside a word poke (pk: dict word address -> 4 bytes)"""
    w = addr & ~3
    pk.setdefault(w, [0, 0, 0, 0])[addr & 3] = val

def setup(name, view=0, dde40=0, c35ea=1, zoom=0.5, raw=50.0, aim=(10.0, -6.0), mode=0, frame=0,
          rec=(160.0, 120.0, 0.0, 240.0, 0.0, 320.0), rec0=(1.0, 1.0), centre=(3.0, -2.0)):
    pk = {}
    words = {}
    bytepoke(pk, 0x800DE270, dde40)
    bytepoke(pk, 0x800C3A0A, c35ea)
    for v in range(4):
        bytepoke(pk, 0x800DE24C + v, mode if v == view else 0x5A)
        bytepoke(pk, 0x800DE1A8 + v, frame if v == view else 0x77)
    words[0x800DE1F8 + 4 * view] = fb(zoom)
    words[0x800DE218 + 8 * view] = fb(centre[0])
    words[0x800DE218 + 8 * view + 4] = fb(centre[1])
    words[0x800DE274] = '%08X' % PTRS
    words[0x800DE278] = '%08X' % (PTRS + 4)
    words[0x800DE27C] = '%08X' % (PTRS + 8)
    words[PTRS] = fb(raw)
    words[PTRS + 4] = fb(aim[0])
    words[PTRS + 8] = fb(aim[1])
    words[0x800A766C] = fb(0.01)
    words[0x800A7670] = fb(-399.0)
    words[0x800BEA48] = '%08X' % VIEW
    words[VIEW + 4] = fb(rec0[0])
    words[VIEW + 8] = fb(rec0[1])
    base = VIEW + view * 0x180
    for off, val in zip((0xC, 0x10, 0x24, 0x28, 0x2C, 0x30), rec):
        words[base + off] = fb(val)
    pokes = ['%08X=%02X%02X%02X%02X' % ((a,) + tuple(b)) for a, b in sorted(pk.items())]
    pokes += ['%08X=%s' % (a, v) for a, v in sorted(words.items())]
    args = '0=%08X,1=%X' % (GDL, view)
    ret = '1517FF64=80510000,1518010C=80514000,1510D66C=80600000'
    print(' ! '.join([name, args, ','.join(pokes), ret, '', '', '', '']))

# zoom source / clamps
setup('z0', zoom=0.0)
setup('zneg', zoom=-0.5)
setup('z1', zoom=1.0)
setup('z15', zoom=1.5)
setup('z_q', zoom=0.25)
setup('z_999', zoom=0.999)
setup('a_on', dde40=1, raw=50.0)
setup('a_hi', dde40=1, raw=150.0)
setup('a_neg', dde40=1, raw=-20.0)
setup('a_zero', dde40=1, raw=0.0)
setup('a_rec0', dde40=1, raw=30.0, rec0=(1.5, 0.75), aim=(-7.5, 12.25))
setup('a_off', dde40=1, c35ea=0)
setup('a_off2', dde40=1, c35ea=2, zoom=0.3)
# modes and frames, per view
for v in range(4):
    for m in range(4):
        setup('v%d_m%d' % (v, m), view=v, mode=m, zoom=0.1 + 0.2 * m, frame=m % 3)
for f in range(4):
    setup('m2_f%d' % f, mode=2, frame=f)
setup('m1_off', mode=1, centre=(-40.5, 33.25), rec=(100.0, 80.0, 10.0, 200.0, 5.0, 300.0))
setup('m2_odd', mode=2, zoom=0.77, rec=(161.7, 119.3, -3.5, 241.9, -7.25, 329.6), centre=(0.5, -0.5))
setup('m1_v3_a', view=3, dde40=1, raw=40.0, mode=1, aim=(20.0, 30.0))
# fill path (zoom >= 1) with odd bounds
setup('fill_odd', zoom=1.0, rec=(0.0, 0.0, 12.7, 250.2, 5.9, 330.1))
setup('fill_neg', zoom=2.0, rec=(0.0, 0.0, -5.0, 1500.0, -12.0, 2000.0))
setup('fill_v2', view=2, zoom=1.0, rec=(0.0, 0.0, 120.0, 240.0, 160.0, 320.0))
# s16 truncation of the corners
setup('big', mode=1, zoom=0.5, rec=(40000.0, -40000.0, -50000.0, 50000.0, -70000.0, 70000.0), centre=(0.0, 0.0))
setup('big2', mode=2, zoom=0.2, rec=(32767.0, 32800.0, -32768.0, 32767.5, -32769.0, 65535.0))
setup('huge', mode=1, zoom=0.6, rec=(3e9, -3e9, -3e9, 3e9, -1e10, 1e10))
rng = random.Random(850)
for k in range(10):
    setup('mix%02d' % k, view=rng.randrange(4), dde40=rng.choice([0, 1]), c35ea=rng.choice([0, 1, 1]),
          zoom=rng.choice([0.0, 0.3, 0.6, 0.95, 1.0, 1.2]), raw=rng.uniform(-10, 120), mode=rng.randrange(4),
          frame=rng.randrange(4), aim=(rng.uniform(-50, 50), rng.uniform(-50, 50)),
          rec=(rng.uniform(0, 320), rng.uniform(0, 240), rng.uniform(-20, 20), rng.uniform(200, 260),
               rng.uniform(-20, 20), rng.uniform(280, 340)),
          rec0=(rng.uniform(0.5, 2), rng.uniform(0.5, 2)), centre=(rng.uniform(-60, 60), rng.uniform(-60, 60)))
