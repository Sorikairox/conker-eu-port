#!/usr/bin/env python3
"""P74: setups for func_15000AD0 (p74/knobs.sh). EU data addresses: D_800B0DF0 0x800B1200 (-> 0x804B0000 header),
D_800BE616 0x800BEA36 (byte), D_80082FA0 0x80083330, D_80038080 0x800383E0 (byte), D_800BE9F0 0x800BEE10,
D_800D2E4C 0x800D326C (-> 0x804B1000), D_8008955C table (same address). allocate_memory 0x10003E90 returns
distinct buffers 0x804C0000 + 0x2000 * k (RET sequence)."""
import random
r = random.Random(0x0AD0)
LEVELS = [0, 0x24, 0x29, 0x2B, 0x2D, 0x30, 0x3C, 0x23, 0x25, 0x2A, 0x31, -1, 0x7F]
i = 0
def setup(mode, f616, np_, lvl, f8080, u9, b14):
    global i
    hdr = (r.getrandbits(8) << 24) | r.getrandbits(24)          # +4..+7 (bytes 5..7 copied)
    w8 = (mode << 24) | (u9 << 16) | r.getrandbits(16)
    p = ['800B1200=804B0000', '804B0004=%08X' % hdr, '804B0008=%08X' % w8,
         '800BEA34=%08X' % ((r.getrandbits(16) << 16) | (f616 << 8) | r.getrandbits(8)),
         '80083330=%08X' % (np_ & 0xFFFFFFFF), '800BEE10=%08X' % (lvl & 0xFFFFFFFF),
         '800383E0=%08X' % ((f8080 << 24) | r.getrandbits(24)),
         '800D326C=804B1000', '804B1014=%08X' % ((b14 << 24) | r.getrandbits(24)),
         '%08X=804B2000' % (0x8008955C + 4 * u9), '804B2000=%08X' % r.choice([0x100, 0x80123450, r.getrandbits(16)])]
    ret = '10003E90=' + ';'.join('%08X' % (0x804C0000 + 0x2000 * k) for k in range(8))
    print('k%02d_m%d_f%d_n%d_l%X_c%d ! ! %s ! %s ! ! ! ! ' % (i, mode, f616, np_ & 0xFF, lvl & 0xFFF, f8080, ','.join(p), ret))
    i += 1
# every mode x D_80082FA0 (0, 1, 2) x D_800BE616, mode 2 over every level group
for mode in (0, 1, 2, 3, 4, 5):
    for np_ in (0, 1, 2):
        for f616 in (0, 1):
            lvls = LEVELS if mode == 2 else [r.choice(LEVELS)]
            if mode == 4 and f616 == 0:
                lvls = [0x3C, 0x24, r.choice(LEVELS)]
            for lvl in lvls:
                setup(mode, f616 if f616 == 0 else r.choice([1, 0x80, 0xFF]), np_, lvl, r.randint(0, 1), r.randint(0, 3), r.choice([0, 1, 0xFE, 0xFF]))
setup(4, 0, -1, 0x3C, 1, 1, 1)
setup(2, 0, -1, 0x24, 0, 2, 0)
setup(4, 0, 1, 0x10, 1, 3, 0)
setup(4, 0, 2, 0x3C, 0, 0, 1)
