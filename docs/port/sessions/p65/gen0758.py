import random, itertools
R = random.Random(65)
def rec(B, sub, mtx, tgt, xf, mode, spin, own, timer, cb, nxt):
    w = {B+0: 0x03000100, B+4: cb, B+8: own[0], B+0xC: (own[1] << 16) | own[2], B+0x10: 0, B+0x14: mode << 8, B+0x18: 0,
         B+0x1C: (timer << 16) | sub, B+0x20: (1 << 16) | spin, B+0x34: mtx, B+0x40: 0x3FC00000, B+0x44: xf, B+0x48: tgt, B+0x54: nxt}
    return w
lines = []
for n in range(72):
    sub = R.choice([0, 0, 2]); mtx = R.choice([0, 0x80520000, 0x80520000]); tgt = R.choice([0, 0x80530000])
    xf = R.choice([0, 0x80540000]); mode = R.choice([0, 4]); spin = R.choice([0, 0x1000, 0xC000])
    own = R.choice([(0, 0, 0), (5, 0, 7), (0, 7, 0), (5, 6, 8)]); timer = R.choice([0xFFFF, 0, 1, 3]); cb = R.choice([0, 0, 0, 1])
    two = R.choice([0, 1]); m84 = R.choice([7, 9]); joints = R.choice([0x80480000, 0x80480000, 0])
    sret = R.choice(['80490000', '0']); s1360 = R.choice(['1', '0'])
    w = rec(0x80510000, sub, mtx, tgt, xf, mode, spin, own, timer, cb, 0x80510100 if two else 0)
    if two:
        w.update(rec(0x80510100, 2 - sub if sub in (0, 2) else 0, 0x80520100, tgt, 0, 4 - mode, 0x2000, (0, 0, 0), 2, 0, 0))
    w.update({0x800C4300: 0x80510000, 0x800BEDE0: R.choice([0, 0x01000000]), 0x800BEE04: 2, 0x80470084: m84 << 16,
              0x804701D4: joints, 0x80490048: R.choice([0, 1])})
    name = 'n%02d_s%d_m%d_t%d_x%d_md%d_sp%X_o%d_tm%X_cb%d_2%d' % (n, sub, mtx != 0, tgt != 0, xf != 0, mode, spin, own[2], timer, cb, two)
    poke = ','.join('%08X=%08X' % kv for kv in sorted(w.items()))
    lines.append('%s ! ! %s ! 150842F8=80470000,15031C4C=%s,15031360=%s !' % (name, poke, sret, s1360))
print('\n'.join(lines))
