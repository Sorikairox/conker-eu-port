#!/usr/bin/env python3
# P119: setups for func_15181A6C (hud_lens_update). usage: gen1a6c.py N SEED
import random, struct, sys
n, seed = int(sys.argv[1]), int(sys.argv[2]); R = random.Random(seed)
def f(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
def bw(b): return ''.join('%02X' % x for x in b)
for s in range(n):
    np_ = R.choice([1, 1, 2, 4]); pk = {0x80083330: '%08X' % (np_ - 1), 0x800BEE04: '%08X' % R.choice([1, 2, 3, 30]),
                                       0x800BEDD4: '%02X000000' % R.choice([0, 0, 1])}
    de20 = [0] * 4; de3c = [0] * 4; t = [0] * 4; ang = [0] * 4; hold = [0] * 4; rets = []; outw = []
    for p in range(np_):
        o = 0x800CC6F0 + p * 0x32C; kind = R.choice(['s', 's', 'l', 'l', 'l', 'o'])
        pk[0x800DE1F8 + 4 * p] = f(R.choice([0.0, 0.5, 0.79, 0.8, 0.85, 0.9, 0.91, 0.96, 0.962, 0.97, 1.0, 1.2, -0.1]))
        pk[0x800DE208 + 4 * p] = f(R.choice([0.0, 0.0, 0.01, -0.01, 0.009, -0.2]))
        t[p] = R.choice([0, 1, 5, 29, 30, 31, 32, 33, 60, 200]); ang[p] = R.randint(0, 255); hold[p] = R.choice([0, 1, 2, 3, 30, 50])
        pk[o + 0x14] = f(R.uniform(-500, 500)); pk[o + 0x18] = f(R.uniform(-500, 500)); pk[o + 0x1C] = f(R.uniform(-500, 500))
        pk[o + 0x150] = f(R.choice([1.0, 1.5])); pk[o] = '%08X' % R.choice([0, 1, 2])
        if kind == 's':
            de20[p] = R.choice([1, 2])
            if R.random() < 0.15: pk[o + 0x31C] = '00000000'
            else:
                r = 0x80460000 + p * 0x200; pk[o + 0x31C] = '%08X' % r
                pk[r + 0x120] = '%02X000000' % R.choice([3, 3, 4, 4, 5, 6, 6, 8, 8, 7])
        elif kind == 'l':
            de3c[p] = R.choice([1, 1, 2, 2, 3, 3, 4, 5])
            pk[o + 0x1D4] = R.choice(['00000000', '%08X' % (0x80470000 + p * 0x400)])
            pk[0x800DE218 + 8 * p] = f(R.uniform(-30, 30)); pk[0x800DE21C + 8 * p] = f(R.uniform(-30, 30))
            outw.append((p, f(R.uniform(-40, 40)), f(R.uniform(-40, 40))))
    pk[0x800DE250] = bw(de20); pk[0x800DE26C] = bw(de3c); pk[0x800DE1A0] = bw(t); pk[0x800DE1A4] = bw(ang)
    pk[0x800DE1B0] = '%04X%04X' % (hold[0], hold[1]); pk[0x800DE1B4] = '%04X%04X' % (hold[2], hold[3])
    sins = ';'.join(f(R.uniform(-1, 1)) for _ in range(5))
    proj = ';'.join('%s' % f(R.uniform(-100, 100)) for _ in range(5))
    ow = '150A7E40=4:%s/5:%s/6:%s' % (proj, proj, proj)
    # func_1517FD84 writes D_800DE218[p]: one absolute target per lens player
    for p, a, b in outw: ow += ',1517FD84=@%08X:%s/@%08X:%s' % (0x800DE218 + 8 * p, a, 0x800DE21C + 8 * p, b) if p == outw[0][0] else ''
    print('s1a6c_%d ! 0=0 ! %s !  ! 15048D30=%s !  ! %s ! ' % (s, ','.join('%08X=%s' % kv for kv in sorted(pk.items())), sins, ow))
