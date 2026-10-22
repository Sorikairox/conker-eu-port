#!/usr/bin/env python3
"""P76: knob setups for func_15037CCC (p76/knobs.sh). EU: D_800C35EA 0x800C3A0A, D_800CC2D0 0x800CC6F0 (0x32C),
D_800BE9C0 0x800BEDE0, D_800C6A70 / 74 same, D_80084790 / D_80084770 same (.data: poked to the ROM lists
10 21 22 23 19 20 25 72), D_800DD280 same (2 x 104 heads). jal: func_15037B70 0x15037B70, func_15031CBC 0x15031CBC,
func_15083E90 0x150842F8, func_15043FF0 0x150442E0, func_15037988 0x15037988, func_150383B0 0x150383B0."""
import random, struct, sys
r = random.Random(0x7CCC)
def fw(x): return struct.unpack('>I', struct.pack('>f', x))[0]
LISTS = [10, 21, 22, 23, 19, 20, 25, 72]
N = int(sys.argv[1]) if len(sys.argv) > 1 else 64
for t in range(N):
    kind = t % 8
    i = r.choice([0, 0, 1, 3, 7]) if kind != 3 else 0
    obj = 0x800CC6F0 + 0x32C * i
    p = []; ret = []; outw = []; outa = []
    cut = [0, 0]
    if kind == 0:
        cut = r.choice([[1, 0], [0, 1], [1, 1], [2, 0]])
    p.append('800C3A08=%08X' % (0xAB000000 | cut[0] << 8 | cut[1]))
    sx, sy, sz = r.uniform(-200, 200), r.uniform(-100, 100), r.uniform(-200, 200)
    p += ['%08X=%08X' % (obj + 0x14, fw(sx)), '%08X=%08X' % (obj + 0x18, fw(sy)), '%08X=%08X' % (obj + 0x1C, fw(sz))]
    # sub-object +0x318
    if kind == 1:
        e = 0x804A8000
        p += ['%08X=%08X' % (obj + 0x318, e), '%08X=%08X' % (e + 0x2C, r.choice([0x100, 0x100, 0x101, 0])),
              '%08X=%08X' % (e + 0x73C, r.choice([0x00010000, 0x80000000, 0x0000FFFF])),
              '%08X=%08X' % (e + 0x740, fw(1.5)), '%08X=%08X' % (e + 0x744, fw(-2.5)), '%08X=%08X' % (e + 0x748, fw(7.0))]
    else:
        p.append('%08X=00000000' % (obj + 0x318))
    ret.append('15037B70=%X' % (1 if kind == 2 else 0))
    # object 0 / state 0x81 / attachment 0x1F
    p.append('%08X=%08X' % (obj + 0x84, (r.choice([0x81, 0x81, 0x80]) if kind == 3 else r.choice([0x81, 0])) << 16))
    sub, mt, oth = 0x804A0000, 0x804A1000, 0x804A2000
    ret.append('15031CBC=%X' % r.choice([sub, sub, sub, 0]))
    p += ['%08X=%08X' % (sub, r.getrandbits(8) << 24), '%08X=%08X' % (sub + 0x48, r.choice([mt, mt, mt, 0])),
          '%08X=%08X' % (mt + 0x3F4, r.choice([0x0100, 0x0100, 0])), '800BEDE0=%08X' % (r.choice([0, 1]) << 24),
          '%08X=%08X' % (mt + 0x3E8, r.choice([0x804A3000, 0])), '%08X=%08X' % (mt + 0x3EC, r.choice([0x804A3000, 0, 0x804A3000])),
          '%08X=%08X' % (oth + 4, r.choice([0x00050000, 0x00040000])),
          '%08X=%08X' % (oth + 0x14, fw(10.0)), '%08X=%08X' % (oth + 0x18, fw(20.0)), '%08X=%08X' % (oth + 0x1C, fw(30.0))]
    ret.append('150842F8=%X' % r.choice([oth, oth, 0]))
    outa.append('150442E0=0:%08X;%08X;%08X' % (fw(4.0), fw(5.0), fw(6.0)))
    ret.append('15037988=' + ';'.join(r.choice('0111') for _ in range(12)))
    ret.append('150383B0=%X' % r.choice([0, 0, 3, 0x11]))
    if r.random() < 0.6:
        outw.append('150383B0=6:%08X' % fw(r.choice([1.6e9, 900.0, 40000.0, 1e6])))
    # look points
    cnt = r.choice([0, 1, 3, 6]) if kind >= 4 else r.choice([0, 2])
    tab = 0x804B0000
    p += ['800C6A70=%08X' % tab, '800C6A74=%08X' % cnt, '80084790=%08X' % r.choice([0, 1, 2, 5, 9])]
    sxi = int(sx)
    for k in range(cnt):
        b = tab + 0x14 * k
        x, y, z = [r.randint(-300, 300) for _ in range(3)]
        xmax = sxi + r.choice([1, 50, 0, -5]); xmin = sxi - r.choice([1, 50, 0, -5])
        p += ['%08X=%08X' % (b, (x & 0xFFFF) << 16 | (y & 0xFFFF)), '%08X=%08X' % (b + 4, (z & 0xFFFF) << 16 | r.choice([0, 0, 0, 2])),
              '%08X=%08X' % (b + 8, r.choice([0xFFFFFFF0, 400000, 30000, 2000000])),
              '%08X=%08X' % (b + 12, r.getrandbits(16) << 16 | (xmax & 0xFFFF)),
              '%08X=%08X' % (b + 16, (xmin & 0xFFFF) << 16 | r.choice([0, 0, 4, 1]))]
    # nodes
    p.append('80084770=%s' % '00000000*0')
    p = [q for q in p if not q.endswith('*0')]
    p += ['%08X=%08X' % (0x80084770 + 4 * k, LISTS[k]) for k in range(8)]
    p.append('800DD280=00000000*208')
    nn = 0
    if kind >= 4 or r.random() < 0.3:
        for g in range(2):
            for k in LISTS:
                if r.random() < 0.35:
                    prev = 0
                    for _ in range(r.choice([1, 1, 2, 3])):
                        nd = 0x804C0000 + 0x100 * nn; nn += 1
                        p += ['%08X=%08X' % (nd + 8, prev), '%08X=%08X' % (nd + 0x64, r.choice([0, 0, 1])),
                              '%08X=%08X' % (nd + 0x38, fw(sx + r.uniform(-400, 400))), '%08X=%08X' % (nd + 0x3C, fw(sy + r.uniform(-50, 50))),
                              '%08X=%08X' % (nd + 0x40, fw(sz + r.uniform(-400, 400))),
                              '%08X=%08X' % (nd + 0x98, fw(sx + r.uniform(-500, 500))), '%08X=%08X' % (nd + 0x9C, fw(sy + r.uniform(-50, 50))),
                              '%08X=%08X' % (nd + 0xA0, fw(sz + r.uniform(-500, 500)))]
                        prev = nd
                    p.append('%08X=%08X' % (0x800DD280 + g * 0x1A0 + k * 4, prev))
    print('k%02d_t%d_i%d_c%d_n%d ! 3=%X ! %s ! %s ! ! %s ! %s ! ' % (t, kind, i, cnt, nn, i, ','.join(p), ','.join(ret), ','.join(outa), ','.join(outw)))
