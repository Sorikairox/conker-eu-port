#!/usr/bin/env python3
"""P76: knob setups for func_150314B4 (p76/knobs.sh). EU: D_800CC2D0 0x800CC6F0 (0x32C), D_800B0DF0 0x800B1200,
D_800DCD7C 0x800DD1AC, D_800DD714, D_800BEDE8, D_800BEFC4 same, D_800BE9C0 0x800BEDE0 (byte 0). jal:
func_1506196C 15061D18, func_15031360, func_1502CF24 (10 colour outs = stack args 4..13), func_1510D66C same.
Args: 0 gfx 1 att 2 obj 3 player 4 special."""
import random
r = random.Random(0x14B4)
N = 72
for t in range(N):
    i = r.choice([0, 1, 5]); obj = 0x800CC6F0 + 0x32C * i; att = 0x804A0000; gfx = 0x80480000
    pl = r.randint(0, 3); special = int(r.random() < 0.3)
    p = []; ret = []; outw = []
    vis = 0 if t % 12 == 0 else 1
    p.append('%08X=%02X%02X%02X%02X' % (att, r.getrandbits(8), r.getrandbits(8), r.getrandbits(8), r.choice([0xFF, 0x80, 0x10])))
    p.append('%08X=%02X%02X%04X' % (att + 4, r.choice([0, 1, 3]), vis, r.getrandbits(16)))
    p.append('%08X=%08X' % (att + 0x10, r.getrandbits(24) << 8 | r.choice([0, 0x05, 0xFF, 0x10, 2])))  # +0x13 hidden mask
    p.append('%08X=%08X' % (att + 0x14, (r.choice([0, 1, 3, 6]) << 24) | r.getrandbits(24)))  # +0x14 part count
    p.append('%08X=%04X%04X' % (att + 0x18, r.choice([0, 0, 0x123]), r.choice([0, 0x456])))
    p.append('%08X=804A1000' % (att + 0x24))
    p += ['%08X=%08X' % (att + 0x28 + 4 * k, 0x06000000 + 0x100 * k) for k in range(2)]
    p += ['%08X=%08X' % (0x804A1000 + 4 * k, 0x07000000 + 0x40 * k) for k in range(8)]
    ret.append('15061D18=%X' % r.choice([0xFF, 0xFF, 0x80, 0]))
    ret.append('15031360=%X' % (0 if t % 12 == 1 else 1))
    outw.append('15031360=2:%08X' % r.getrandbits(32))
    outw.append('1502CF24=' + '/'.join('%d:%X' % (n, r.choice([0, 0x7F, 0xFF, 0x1FF, r.getrandbits(32)])) for n in range(4, 14)))
    ret.append('1510D66C=%X;%X' % (r.getrandbits(32), r.getrandbits(32)))
    p.append('800B1200=804C0000')
    p.append('804C003C=%08X' % r.choice([0, 0, 1, 0xFFFF]))
    m66 = r.choice([0, 4, 8, 0xC])
    p.append('%08X=%08X' % (obj + 0x64, m66 << 8))
    p.append('%08X=%08X' % (obj + 4, r.choice([5, 4, 0]) << 16))
    p.append('%08X=%08X' % (obj + 0x304 + 4 * pl, r.choice([0x804D0000, 0x804D0000, 0])))
    p.append('%08X=%08X' % (obj + 0x2FC, r.choice([0, 1]) << 16))
    p.append('%08X=%08X' % (obj + 0x300, (r.choice([0, 7]) << 16) | (r.choice([0, 3]) << 8)))
    p.append('%08X=804D1000' % (obj + 0x314))
    p.append('%08X=%08X' % (obj + 0x184, r.getrandbits(32)))
    p.append('800DD1AC=%08X' % r.choice([0, 1]))
    p.append('800DD714=%08X' % r.getrandbits(32))
    b = r.choice([0, 1]); p.append('800BEDE0=%08X' % (b << 24))
    p.append('%08X=%08X' % (0x800BEDE8 + 4 * b, 0x80480000 - 8 * r.choice([0, 10, 1000])))
    p.append('800BEFC4=%08X' % r.choice([5, 14, 20, 1000, 2000]))
    print('k%02d_i%d_p%d_s%d_m%X ! 0=%X,1=%X,2=%X,3=%X,4=%X ! %s ! %s ! ! ! %s ! ' % (t, i, pl, special, m66, gfx, att, obj, pl, special, ','.join(p), ','.join(ret), ','.join(outw)))
