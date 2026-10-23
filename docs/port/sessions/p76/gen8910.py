#!/usr/bin/env python3
"""P76: knob setups for func_15038910 (p76/knobs.sh). usage: gen8910.py [N]
EU: D_800CC2D0 0x800CC6F0 (0x32C), D_800C441A 0x800C441A (byte 2 of 0x800C4418), D_800BEAC0 0x800BEEE0,
D_800BEE2C 0x800BEE2C, D_800BE9B4 0x800BEDD4, D_800BE9E4 0x800BEE04, D_800C35EA 0x800C3A0A, D_800C3E78 0x800C4298.
jal: func_15021E60 15021E60, func_15038758 15038758, func_1503A1C0 1503A1C0, func_150A8050 150A8530,
func_150A7A48 150A7F28, bcopy 10023E80, func_15049FA8 15049FA8. Args: 0 joint 1 parent 2 target 3 id 4 lookArg
5 limits 6 slot 7 keepMask 8 wrap 9 postMul 10 yawBias 11 unused 12 axis."""
import random, struct, sys
r = random.Random(0x8910)
def fw(x): return struct.unpack('>I', struct.pack('>f', x))[0]
def ang(): return r.choice([0.0, 30.0, -45.5, 120.0, -150.0, 200.0, 95.0, -99.0, 185.0, -85.0, r.uniform(-250, 250)])
N = int(sys.argv[1]) if len(sys.argv) > 1 else 80
for t in range(N):
    kind = t % 10 if t < 80 else 10 + t % 2  # 10: hold blend (no target), 11: wrap
    i = r.choice([0, 1, 3]); obj = 0x800CC6F0 + 0x32C * i
    slot = r.randint(0, 2); joint = r.randint(0, 3); parent = r.randint(0, 3)
    axis = r.choice([0, 1, 2, 3, 0, 1, 2, 3, 5])
    args = {0: joint, 1: parent, 2: 0x804A0000, 3: i, 4: r.randint(0, 5), 5: r.randint(0, 4), 6: slot,
            7: r.randint(0, 3), 8: int(kind in (6, 7) or r.random() < 0.2), 9: int(r.random() < 0.3),
            10: r.choice([0, 5, 0xFFFFFFFD, 20]), 11: 0, 12: axis}
    p = []; ret = []; outw = []; outa = []
    lt = 0x804B0000 if (kind != 0 or r.random() < 0.5) else 0
    p.append('%08X=%08X' % (obj + 0x324, lt))
    for k in range(3):
        p += ['%08X=%08X' % (lt + 4 * k, fw(r.choice([-99999.0, ang(), ang()]))),
              '%08X=%08X' % (lt + 0xC + 4 * k, fw(r.choice([-99999.0, ang(), ang()]))),
              '%08X=%08X' % (lt + 0x18 + 4 * k, fw(r.choice([0.0, 0.5, -3.0, 12.0]))),
              '%08X=%08X' % (lt + 0x24 + 4 * k, fw(r.choice([0.0, 0.5, -3.0, 12.0])))]
    by = [r.choice([0, 0, 1, 5, 9, 12, 40]) for _ in range(3)] + [r.choice([0, 0, 1, 2, 3, 10]) for _ in range(3)] + \
         [r.choice([0, 4]) for _ in range(3)] + [0]
    for k in range(0, 8, 4):
        p.append('%08X=%02X%02X%02X%02X' % (lt + 0x30 + k, *by[k:k + 4]))
    if kind == 10: by[slot] = r.choice([3, 5, 9]); by[3 + slot] = 0
    hw = [r.choice([0, 0, 5, -300, 40, 3]) & 0xFFFF for _ in range(6)]
    p.append('%08X=%02X%02X%04X' % (lt + 0x38, by[8], by[9], hw[0]))
    p += ['%08X=%04X%04X' % (lt + 0x3C, hw[1], hw[2]), '%08X=%04X%04X' % (lt + 0x40, hw[3], hw[4]), '%08X=%04X0000' % (lt + 0x44, hw[5])]
    p.append('%08X=%08X' % (obj + 0x2F8, 0 if kind == 10 else r.choice([0, 4, 0x11, 0x15])))
    if kind == 10: args[7] = 3
    if kind == 11:
        args[8] = 1; p.append('%08X=%08X' % (lt + 4 * slot, fw(r.choice([-85.0, 85.0, -95.0, 95.0]))))
    m = 0x804C0000
    p.append('%08X=%08X' % (obj + 0x1D4, m))
    for k in range(64):
        p.append('%08X=%08X' % (m + 4 * k, fw(r.uniform(-100, 100) if (k % 16) in (12, 13, 14) else r.choice([r.uniform(-1.5, 1.5), 1.0, 0.0]))))
    tg = 0x804A0000
    tk = r.choice(['none', 'pt', 'pt', 'part']) if kind not in (1, 2, 10) else ('none' if kind in (1, 10) else 'pt')
    tv = {'none': [-99999.0] * 3, 'pt': [r.uniform(-300, 300) for _ in range(3)], 'part': [-99999.0, -99999.0, 4.0]}[tk]
    p += ['%08X=%08X' % (tg + 4 * k, fw(tv[k])) for k in range(3)]
    fixed = int(kind in (3, 4) or (kind < 10 and r.random() < 0.1))
    ret.append('15021E60=%X' % fixed)
    outw.append('15021E60=0:%08X/1:%08X/2:%08X' % (fw(ang()), fw(ang()), fw(r.choice([0.0, 15.0]))))
    outw.append('15038758=0:%s/1:%s' % (';'.join('%08X' % fw(ang()) for _ in range(3)), ';'.join('%08X' % fw(ang()) for _ in range(3))))
    outa.append('150A7F28=2:%s' % ';'.join('%08X' % fw(r.choice([r.uniform(-2, 2), 1.0, 0.5])) for _ in range(16)))
    outa.append('150A8530=0:%s' % ';'.join('%08X' % fw(r.uniform(-1, 1)) for _ in range(16)))
    p.append('800C4418=%08X' % (r.choice([0, 0, 1]) << 8))
    p.append('800BEEE0=%08X' % ((1 if kind == 8 else 0) << 24))
    if kind == 11: outw[-1] = '15038758=0:%08X/1:%08X' % (fw(r.choice([95.0, -95.0])), fw(185.0))
    p.append('800BEE2C=%08X' % ((1 if (kind == 9 and r.random() < 0.5) else 0) << 24))
    p.append('800BEDD4=%08X' % ((1 if kind == 5 else 0) << 24))
    p.append('800BEE04=%08X' % r.choice([1, 2, 3]))
    p.append('800C3A08=%08X' % (r.choice([0, 0, 1]) << 8))
    pl = r.choice([0, 2]); p.append('800C4298=%08X' % (pl << 24))
    p.append('%08X=%08X' % (0x800CC6F0 + 0x32C * pl + 0x318, r.choice([0, 0x804A8000])))
    p.append('804A802C=%08X' % r.choice([0x100, 0x100, 0]))
    a = ','.join('%d=%X' % kv for kv in args.items())
    print('k%02d_t%d_i%d_s%d_ax%d_%s_f%d ! %s ! %s ! %s ! ! %s ! %s ! ' % (t, kind, i, slot, axis, tk, fixed, a, ','.join(p), ','.join(ret), ';'.join([]) or ','.join(outa), ','.join(outw)))
