#!/usr/bin/env python3
"""P85: knob setups for func_15041A9C (text drawer). Writes s1a9c.txt (p85/knobs.sh format:
name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB). All addresses EU (undefined_syms_auto.txt).
usage: gen1a9c.py > s1a9c.txt"""
import random, struct

def fb(f): return '%08X' % struct.unpack('>I', struct.pack('>f', f))[0]

GDL, STR, VIEW, TEX, MET = 0x80500000, 0x80520000, 0x80540000, 0x80560000, 0x80570000
CODES = list(range(0xA1, 0xBC))          # control codes (A1..A7 effects, A8..BB icon selectors)
rng = random.Random(85)

def setup(name, glyphs, strbytes=None, x=40.0, y=48.0, sx=4096.0, sy=4096.0, cap=0x7FFFFFFF, d30c0=0,
          wave=0, flash=0, met=None, rgba=(0x80, 0x40, 0x20, 0xC0), view=(0.0, 240.0, 0.0, 320.0), scale=(1.0, 1.0),
          icon=(16, 12, 2.0, 0, 1.0), cos=0.5, cc16e=0x0000, vscale=(1.0, 1.0), nullgdl=False, length=None):
    n = length if length is not None else len(strbytes or glyphs)
    sb = strbytes or [0x41] * min(n, 32)
    sb = (sb + [0] * 4)[:((len(sb) + 3) // 4) * 4]
    pokes = ['80083334=00000000',                                  # D_80082FA4: view 0
             '800BEA48=%08X' % VIEW,                               # D_800BE628
             '%08X=%s' % (VIEW + 0x14, fb(vscale[0])), '%08X=%s' % (VIEW + 0x18, fb(vscale[1])),
             '%08X=%s' % (VIEW + 0x24, fb(view[0])), '%08X=%s' % (VIEW + 0x28, fb(view[1])),
             '%08X=%s' % (VIEW + 0x2C, fb(view[2])), '%08X=%s' % (VIEW + 0x30, fb(view[3])),
             '80038400=%s' % fb(scale[0]), '80038404=%s' % fb(scale[1]),
             '80085D20=%08X' % TEX, '80085D24=%08X' % MET,
             '800BEDE0=00000000', '800BEDE8=%08X' % GDL, '800BEFC4=%08X' % cap,   # D_800BE9C0, D_800BEDE8, D_800BEFC4
             '800BEE04=00000003',                                  # D_800BE9E4
             '800CC16C=%08X' % cc16e,                              # D_800CC16E (low half)
             '800CC17C=%02X%02X%02X00' % (0x10, wave, 0x20),       # D_800CC17C phase, D_800CC17D wave, D_800CC17E
             '800CC178=00000000',
             '800D30C0=%08X' % d30c0]
    if flash: pokes.append('800CC178=000000%02X' % flash)
    if met is None:
        pokes.append('%08X=0C0E0102*256' % MET)
    else:
        for k, v in met.items(): pokes.append('%08X=%08X' % (MET + 4 * k, v))
    for i in range(0, len(sb), 4):
        pokes.append('%08X=%02X%02X%02X%02X' % (STR + i, sb[i], sb[i + 1], sb[i + 2], sb[i + 3]))
    args = ['0=%08X' % (0 if nullgdl else GDL), '1=%s' % fb(x), '2=%s' % fb(y), '3=%08X' % STR,
            '4=%X' % rgba[0], '5=%X' % rgba[1], '6=%X' % rgba[2], '7=%X' % rgba[3],
            '8=%s' % fb(sx), '9=%s' % fb(sy), '10=%X' % n]
    ret = '15042F30=' + ';'.join('%X' % g for g in glyphs) + ',15095380=80510000,15095E58=80518000'   # icon stubs return a usable gdl
    retf = '15047EF0=%s' % fb(cos)
    w, h, dy, flip, sc = icon
    outw = '150418D0=1:%X/2:%X/3:%s/4:%X/5:%s' % (w, h, fb(dy), flip, fb(sc))
    print(' ! '.join([name, ','.join(args), ','.join(pokes), ret, retf, '', outw, '']))

# plain glyphs, different sizes / positions / scales
setup('g_plain', [0x01, 0x02, 0x03, 0x10, 0x20, 0x30])
setup('g_space', [0x01, 0x60, 0x02, 0x60, 0x60, 0x03])
setup('g_metvar', [0, 1, 2, 3, 4, 5], met={0: 0x0C0E0102, 1: 0x0C0E0304, 2: 0x080E0000, 3: 0x08100506, 4: 0x08100000, 5: 0x10FF0708})
setup('g_scale2', [1, 2, 3, 4], sx=8192.0, sy=2048.0)
setup('g_scale_odd', [1, 2, 3, 4], sx=3000.5, sy=5000.25, x=17.3, y=9.7)
setup('g_vscale', [1, 2, 3], vscale=(1.5, 0.75), scale=(1.25, 0.8))
setup('g_negx', [1, 2, 3, 4, 5], x=-20.0, view=(0.0, 240.0, -100.0, 320.0))
setup('g_negy', [1, 2, 3, 4, 5], y=-20.5, view=(-100.0, 240.0, 0.0, 320.0))
setup('g_negxy_negsc', [1, 2, 3], x=-30.25, y=-12.75, sx=-4096.0, sy=-4096.0, view=(-100.0, 240.0, -100.0, 320.0))
setup('g_clip_r', [1, 2, 3], x=310.0)
setup('g_clip_l', [1, 2, 3], x=-40.0)
setup('g_clip_t', [1, 2, 3], y=-40.0)
setup('g_clip_b', [1, 2, 3], y=239.0)
setup('g_edge', [1, 2, 3], x=-12.0, y=-14.0, met={1: 0x0C0E0000, 2: 0x0C0E0000, 3: 0x0C0E0000})
setup('g_big', [1, 2], met={1: 0xFFFF0000, 2: 0x40400000})
# 0xBC bytes (glyph from the previous character)
setup('bc', [1, 2, 3, 4], strbytes=[0x41, 0xBC, 0x42, 0xBC, 0xBC, 0x43, 0x44])
setup('bc_first', [5, 6], strbytes=[0xBC, 0x41, 0xBC, 0x42])
# control codes one by one, each followed by glyphs
for c in range(0xA1, 0xA8):
    setup('c%02X' % c, [1, c, 2, 3, 0xA1, 4], flash=0)
setup('flash', [1, 0xA6, 2, 3, 0xA6, 4], cos=0.25)
setup('flash_on', [1, 2, 3], flash=1, cos=-0.5)
setup('flash_pos', [0xA6, 2, 3], cos=0.9, rgba=(0x10, 0x20, 0x30, 0x40))
setup('wave', [1, 0xA7, 2, 3, 4, 0xA1, 5], cos=0.3)
setup('wave_on', [1, 2, 3], wave=1, cos=-0.7)
setup('colours', [0xA2, 1, 0xA3, 2, 0xA4, 3, 0xA5, 4, 0xA1, 5])
# icons: selector then icon code
for c in range(0xA8, 0xBC):
    setup('i%02X' % c, [1, c, 0xC0, 2, 0xC8, 3], cc16e=0x1234 if c % 2 else 0x0B00, icon=(15, 13, 1.5, c & 1, 0.75))
setup('i_wave', [0xA7, 0xA8, 0xC0, 0xC1, 2], icon=(20, 10, 3.0, 0, 2.0), cos=0.1)
setup('i_d30c0', [0xA8, 0xC0, 0xB1, 0xFF], d30c0=0x80000000, cc16e=0x2500)
setup('i_d30c0_flip', [0xBB, 0xC0, 0xC4], d30c0=0x80000000, cc16e=0x0400, icon=(9, 7, 0.5, 1, 1.25))
setup('i_nosel', [0xC0, 1, 0xC2])
setup('i_vscale', [0xA9, 0xC3, 1], vscale=(2.0, 0.5), scale=(0.5, 1.5))
setup('i_flash', [0xA6, 0xA8, 0xC0, 1], cos=-0.2)
# display list full: commands of the character dropped
setup('ovf3', [1, 2, 3, 4, 5], cap=3)
setup('ovf8', [1, 2, 3, 4, 5], cap=8)
setup('ovf_icon', [0xA8, 0xC0, 1], cap=6)
setup('ovf_null', [1, 2, 3], cap=0, nullgdl=True)
setup('len0', [1], length=0)
setup('lenneg', [1], length=0xFFFFFFFF)
# random mixes
pool = [0, 1, 2, 3, 0x10, 0x5F, 0x60, 0x7F, 0x9F, 0xA0, 0xBC, 0xFE, 0xFF] + CODES
for k in range(12):
    gl = [rng.choice(pool) for _ in range(rng.randint(6, 14))]
    sb = [rng.choice([0x41, 0x42, 0xBC, 0x20]) for _ in range(len(gl) + 2)]
    setup('mix%02d' % k, gl, strbytes=sb, x=rng.uniform(-30, 300), y=rng.uniform(-20, 230),
          sx=rng.choice([4096.0, 2048.0, 6144.0, 5000.0]), sy=rng.choice([4096.0, 3072.0, 8192.0]),
          wave=rng.choice([0, 1]), flash=rng.choice([0, 1]), cos=rng.uniform(-1, 1), cc16e=rng.randrange(0x10000),
          icon=(rng.randrange(1, 40), rng.randrange(1, 40), rng.uniform(-3, 3), rng.choice([0, 1]), rng.uniform(0.5, 2)),
          rgba=tuple(rng.randrange(256) for _ in range(4)), cap=rng.choice([0x7FFFFFFF, 0x7FFFFFFF, 20]),
          met={g: rng.randrange(1 << 32) & 0x3F3F0F0F for g in range(256)} if k % 3 == 0 else None)
# P85 targeted (mutants that the first set did not reach)
setup('space_sc', [1, 0x60, 2, 0x60, 3], scale=(1.25, 0.8))
setup('flash_hi', [1, 2, 3], flash=1, cos=0.9, rgba=(0x10, 0x20, 0x30, 0xC0))
setup('flash_hi2', [0xA6, 2, 3, 4], cos=0.9, rgba=(0x10, 0x20, 0x30, 0xF0))
setup('g_sx4095', [1, 2, 3], sx=4095.0, sy=4095.0)
