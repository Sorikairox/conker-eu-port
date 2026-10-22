#!/usr/bin/env python3
"""P86: knob setups for func_10011624 (sound entry update). Writes s1624.txt. a0 = entries (0x30 each) at ENT, a1 = count
word at CNT, a2 first, a3 end. jal targets: func_1000F3D0 1000F6C0, func_1000A750 1000AA40 (out: 10 pan, 11 vol, 12 dist),
func_100114D0 100117C0 (out: 6 pan, 7 vol, 8 dist), func_1000FE88 10010178, alCents2Ratio 10019DA0 (RETF),
func_10010BE8 10010ED8, func_1000F85C 1000FB4C, func_100111C8 100114B8. Callback unk14 = 0x15024910 (a stub; RET).
EU: D_800BEA35 800BEA35, D_80041FD9 = 80042379, D_80042308 80042308, D_800BE9E4 = 800BEE04."""
import random, struct
def fb(f): return '%08X' % struct.unpack('>I', struct.pack('>f', f))[0]
ENT, CNT, CB = 0x80480000, 0x80470000, 0x15024910
out = []
def ent(sound=0x55, pos=(100, -200, 300), u8=0x1234, uA=-5, uC=0x7FFF, flags=0x2, cb=0, pitch=-120, u22=0x45, u23=3, voice=0, u26=0x100, u28=500, r2c=1.0):
    return dict(sound=sound, pos=pos, u8=u8, uA=uA, uC=uC, flags=flags, cb=cb, pitch=pitch, u22=u22, u23=u23, voice=voice, u26=u26, u28=u28, r2c=r2c)
def setup(name, ents, count=None, first=0, end=None, alive=1, ret4d0=7, pan=0x30, vol=0x2000, dist=480, ratio=1.25, be8=0x77,
          cbret=0, mute=0, fx=1, dt=2, nopan=False):
    w = {}
    for i, e in enumerate(ents):
        b = ENT + 0x30 * i
        w[b] = '%04X%04X' % (e['sound'], e['pos'][0] & 0xFFFF)
        w[b + 4] = '%04X%04X' % (e['pos'][1] & 0xFFFF, e['pos'][2] & 0xFFFF)
        w[b + 8] = '%04X%04X' % (e['u8'], e['uA'] & 0xFFFF)
        w[b + 0xC] = '%08X' % (e['uC'] & 0xFFFFFFFF)
        w[b + 0x10] = '%08X' % e['flags']
        w[b + 0x14] = '%08X' % (CB if e['cb'] else 0)
        w[b + 0x20] = '%04X%02X%02X' % (e['pitch'] & 0xFFFF, e['u22'], e['u23'])
        w[b + 0x24] = '%04X%04X' % (e['voice'], e['u26'])
        w[b + 0x28] = '%04X0000' % e['u28']
        w[b + 0x2C] = fb(e['r2c'])
    w[CNT] = '%08X' % (len(ents) if count is None else count)
    w[0x800BEA34] = '0000%02X00' % mute      # D_800BEA35 = byte 1 of the word at 800BEA34
    w[0x80042378] = '00%02X0000' % fx       # D_80041FD9 = byte 1 of the word at 80042378
    w[0x800BEE04] = '%08X' % dt
    for k, v in enumerate((11, -22, 33, 1000, -2000, 3000)):
        w[0x80042308 + 4 * k] = '%08X' % (v & 0xFFFFFFFF)
    w[0x80042308 + 0x18] = fb(0.75)
    pokes = ','.join('%08X=%s' % kv for kv in sorted(w.items()))
    args = '0=%08X,1=%08X,2=%X,3=%X' % (ENT, CNT, first & 0xFFFFFFFF, (len(ents) if end is None else end) & 0xFFFFFFFF)
    ret = '1000F6C0=%X,100117C0=%X,1000AA40=%X,10010ED8=%X,%08X=%X' % (alive, ret4d0, ret4d0 + 1, be8, CB, cbret)
    retf = '10019DA0=%s' % fb(ratio)
    p = '' if nopan else '6:%X/' % pan
    outw = '100117C0=%s7:%X/8:%X,1000AA40=10:%X/11:%X/12:%X' % (p, vol, dist, pan, vol, dist)
    out.append(' ! '.join([name, args, pokes, ret, retf, '', outw, '']))

setup('start', [ent()])
setup('start_fx0', [ent(flags=0x2)], fx=0)
setup('start_400', [ent(flags=0x402)])
setup('start_800', [ent(flags=0x802)])
setup('start_C00', [ent(flags=0xC02)])
setup('start_fail', [ent()], be8=0)
setup('start_mirror', [ent(flags=0x202)], pan=0x50)
setup('mirror0', [ent(flags=0x202)], pan=0x80)
setup('mirror_hi', [ent(flags=0x202, voice=9)], pan=0xC0)
setup('fixedpan', [ent(flags=0x102)], nopan=True)
setup('fixedpan_lis', [ent(flags=0x142, voice=9)])
setup('lis', [ent(flags=0x42, voice=9)], vol=0x12345)
setup('lis_start', [ent(flags=0x42)])
setup('mute', [ent(flags=0x0B, voice=9)], mute=1)
setup('silent_keep', [ent(flags=0x0B, voice=9)], vol=0)
setup('silent_keep0', [ent(flags=0x0A, voice=0)], vol=0)
setup('vol1', [ent(flags=0x0B, voice=9)], vol=1)
setup('silent_free', [ent(flags=0x03, voice=9)], vol=0)
setup('nosound', [ent(sound=0, voice=9)])
setup('free', [ent(flags=0x82, voice=9)])
setup('skip', [ent(flags=0x1003, voice=9)])
setup('ended', [ent(flags=0x03, voice=9)], alive=0)
setup('ended_keep', [ent(flags=0x0B, voice=9)], alive=0)
setup('alive_noref', [ent(flags=0x01, voice=9)])
setup('noref_voice0', [ent(flags=0x01, voice=0)])
setup('playing_same', [ent(flags=0x03, voice=9, u26=0x2000, u22=0x30, u23=3, r2c=1.25)], ratio=1.25)
setup('playing_diff', [ent(flags=0x03, voice=9, u26=0x2001, u22=0x31, u23=4, r2c=1.0)])
setup('playing_hi', [ent(flags=0x03, voice=9, u26=0x2000, u22=0xB0, u23=3)], pan=0x30)
for d, u28 in ((2, 500), (2, 480), (10, 300), (1, 2000), (3, 0), (0, 500), (40, 40000), (5, 520), (3, 847), (1, 1300)):
    setup('smooth_%d_%d' % (d, u28), [ent(flags=0x07, voice=9, u28=u28, r2c=1.5)], dt=d, dist=480)
setup('smooth_ratio', [ent(flags=0x07, voice=9, u28=490, r2c=0.25)], dt=7, ratio=3.0)
setup('cb0', [ent(flags=0x13, voice=9, cb=1)])
setup('cb1', [ent(flags=0x13, voice=9, cb=1)], cbret=1)
setup('cb_null', [ent(flags=0x13, voice=9, cb=0)])
setup('range', [ent(), ent(flags=0x82), ent(flags=0x03, voice=7), ent(flags=0x1002)], first=1, end=3)
setup('range_cnt', [ent(), ent(), ent()], count=2, end=3)
setup('range_end', [ent(), ent(), ent()], count=3, end=1)
setup('range_none', [ent()], first=1)
rng = random.Random(1624)
for k in range(12):
    es = [ent(sound=rng.choice([0, 0x31, 0xFFFF]), pos=tuple(rng.randrange(-30000, 30000) for _ in range(3)), u8=rng.randrange(0x10000),
              uA=rng.randrange(-30000, 30000), uC=rng.randrange(0, 0x10000), flags=rng.randrange(0x2000) & ~0x10 | rng.choice([0, 0x10]),
              cb=rng.choice([0, 1]), pitch=rng.randrange(-2400, 2400), u22=rng.randrange(256), u23=rng.randrange(256),
              voice=rng.choice([0, 0, 5, 0x8001]), u26=rng.randrange(0x10000), u28=rng.randrange(0x10000), r2c=rng.uniform(0.3, 2.5)) for _ in range(4)]
    setup('mix%02d' % k, es, alive=rng.choice([0, 1]), pan=rng.randrange(256), vol=rng.choice([0, 1, 0x7FFF, 0x12345]), dist=rng.randrange(0x20000),
          ratio=rng.uniform(0.2, 3), be8=rng.choice([0, 0x44]), cbret=rng.choice([0, 0, 1]), mute=rng.choice([0, 0, 1]), fx=rng.randrange(3),
          dt=rng.randrange(0, 8), nopan=any((e['flags'] & 0x140) == 0x100 for e in es))
open(__file__.replace('gen1624.py', 's1624.txt'), 'w').write('\n'.join(out) + '\n')
print(len(out))
