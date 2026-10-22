#!/usr/bin/env python3
"""P74: setups for func_1503E238 (p74/knobs.sh): slot i record (0x800C6A80 + 16 * i: unk0 pieces, +0xC word with
kind byte +0xE and state byte +0xF), object unk1D4 (0x800CC6F0 + 0x32C * i + 0x1D4) and flag byte +0x74, piece count
D_80098CC4[kind], exclusion table D_800847E4[kind] -> 0x804B8000, callback tables D_800847C0 / CC / D8 poked to
fixed stub addresses; RET allocate_memory 0x10003E90 (buffer or NULL), func_1503E4E4 0x1503E4E4 (bit per piece)."""
import random
r = random.Random(0xE238)
t = 0
for state in (0, 1, 2, 3, 4):
    for v in range(8):
        i = r.randint(0, 3); kind = r.randint(0, 2); n = r.choice([0, 1, 3, 6, 8]); ob = 0x800CC6F0 + 0x32C * i
        unk0 = r.choice([0, 0x804B0000]); alloc = r.choice(['804B0000', '804B0000', '00000000'])
        p = ['%08X=%08X' % (0x800C6A80 + 16 * i, unk0), '%08X=%08X' % (0x800C6A8C + 16 * i, (r.getrandbits(16) << 16) | (kind << 8) | state),
             '%08X=%08X' % (ob + 0x1D4, r.choice([0, 0x804D0000, 0x804D0000])), '%08X=%08X' % (ob + 0x74, r.getrandbits(32)),
             '80098CC4=%08X' % ((n << 24 | n << 16 | n << 8) | r.getrandbits(8)), '%08X=804B8000' % (0x800847E4 + 4 * kind)]
        att = [r.choice([0xFE, 0xFF, 0, 1]) for _ in range(8)]
        p += ['804B8000=%02X%02X%02X%02X' % tuple(att[:4]), '804B8004=%02X%02X%02X%02X' % tuple(att[4:])]
        for tb in range(3):
            for k in range(3):
                p.append('%08X=%08X' % (0x800847C0 + 12 * tb + 4 * k, 0x15600000 + 0x100 * tb + 0x10 * k))
        for k in range(8):
            p.append('%08X=%08X' % (0x804B0064 + 0x68 * k, r.choice([0, 0x01000000, 0xFF000000])))
        bits = ';'.join(r.choice('01') for _ in range(8))
        ret = '10003E90=%s,1503E4E4=%s' % (alloc, bits)
        print('k%02d_s%d_i%d_n%d ! 0=%X ! %s ! %s ! ! ! ! ' % (t, state, i, n, i, ','.join(p), ret))
        t += 1
