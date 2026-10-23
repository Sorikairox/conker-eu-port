#!/usr/bin/env python3
"""P117: setups for func_1502457C (scene event walker). Tracks at D_800C3AA8 + slot * 0x78 (pointer per track),
counts D_800C39F8[slot] -> u16 per track, window (D_800C39D8 * 60 / 50, D_800C39D0 * 60 / 50]."""
import random
S = []
def setup(name, a0, slot, ntr, cur=200, prev=100, end=1000, null=(), seed=1):
    rnd = random.Random(seed)
    pk = ['800C40AC=00000000', '800C3A08=00000101', '800C40B8=00000001',
          '800C3A58=0000%02X%02X' % (ntr if slot == 0 else 0, ntr if slot == 1 else 0),
          '%08X=%08X' % (0x800C39D0 + 4 * slot, cur), '%08X=%08X' % (0x800C39D8 + 4 * slot, prev),
          '%08X=%08X' % (0x800C3A60 + 4 * slot, end), '800C3A68=00000190',
          '%08X=80480000' % (0x800C39F8 + 4 * slot)]
    cnts = []
    for k in range(ntr):
        t = 0x80490000 + 0x200 * k
        pk.append('%08X=%08X' % (0x800C3AA8 + slot * 0x78 + 4 * k, 0 if k in null else t))
        pk.append('%08X=%04X%04X' % (t, 0x1100 + k, 100 + 10 * k))      # +2 start time
        ev = []
        tm = 100 + 10 * k
        for e in range(6):
            kind = rnd.choice([5, 0x11, 3, 0, 7])
            dt = rnd.choice([0, 0, 5, 20, 40])
            if kind == 0 and dt == 0:
                w = tm + rnd.choice([10, 30, 60]); ev.append((0, 0, w))
            else:
                ev.append((kind, dt, 0x40 + k * 8 + e))
        for e, (a, b, w) in enumerate(ev):
            pk.append('%08X=%02X%02X%04X' % (t + 0x20 + 8 * e, a, b, w & 0xFFFF))
            pk.append('%08X=%08X' % (t + 0x24 + 8 * e, 0xA0000000 + (k << 8) + e))
        cnts.append(6)
    for k in range(0, ntr, 2):
        pk.append('%08X=%04X%04X' % (0x80480000 + 2 * k, cnts[k], cnts[k + 1] if k + 1 < ntr else 0))
    S.append('%s ! 0=%X,1=%X ! %s ! ! ! ! ! !' % (name, a0, slot, ','.join(pk)))
for a0 in (0, 1):
    for slot in (0, 1):
        for ntr in (1, 2, 4, 6):
            for sd in (1, 2):
                setup('w%d_s%d_n%d_r%d' % (a0, slot, ntr, sd), a0, slot, ntr, seed=sd + ntr)
        setup('w%d_s%d_null' % (a0, slot), a0, slot, 4, null=(1,), seed=7)
        setup('w%d_s%d_end' % (a0, slot), a0, slot, 3, cur=1200, prev=150, end=1000, seed=9)
        setup('w%d_s%d_same' % (a0, slot), a0, slot, 3, cur=150, prev=150, seed=11)
        setup('w%d_s%d_wide' % (a0, slot), a0, slot, 5, cur=600, prev=0, seed=12)
print('\n'.join(S))
