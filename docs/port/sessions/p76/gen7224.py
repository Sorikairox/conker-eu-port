#!/usr/bin/env python3
"""P76: knob setups for func_15037224 (p76/knobs.sh): every case kind x slot D_800C441A 0..2 plus default kinds.
EU: D_800C3E78 0x800C4298 (byte 0), D_800C441A 0x800C441A (byte 2 of 0x800C4418), D_800BE616 0x800BEA36 (byte 2 of
0x800BEA34), D_800CC2D0 0x800CC6F0 (0x32C), D_800C4408 0x800C4408."""
import random, struct
r = random.Random(0x7224)
def fw(x): return struct.unpack('>I', struct.pack('>f', x))[0]
KINDS = [0x82, 0xA2, 0xA4, 0x5E, 0x97, 0x31, 0x8B, 0x87, 0xB5, 0x86, 0x99, 0x11, 0x14, 0x79, 0x21, 0x7B, 0x7C, 0x6C,
         0x34, 0x76, 0x69, 0x8A, 0x5A, 0x5F, 0x74, 0x7A, 0x8D, 0x58, 0x5B, 0x54, 0x29, 0x4B, 0x50, 0x9A, 0x9B, 0x4A, 0x47,
         0x44, 0x28, 0x2B, 0x3A, 0x3D, 0x53, 0xA5, 0x36, 0x2D, 0x0C, 0x16, 0x22, 0xB3, 0x7D, 0x20, 0x8C, 0x93, 0x05,
         0xAD, 0xAE, 0xAF, 0x12]
OTHER = [0, 4, 6, 0x13, 0xB6, 0xFF]
n = 0
for kind in KINDS + OTHER:
    for slot in (0, 1, 2):
        vs = [None]
        if kind == 0x7B: vs = [7, 9, 0x14, 3]
        if kind == 0x8A: vs = ['a', 'b', 'c']
        for v in vs:
            i = r.choice([0, 1, 4]); obj = 0x800CC6F0 + 0x32C * i
            p = ['800C4298=%08X' % (i << 24), '800C4418=%08X' % (slot << 8), '%08X=%08X' % (obj + 4, kind << 24)]
            p += ['800C44%02X=%08X' % (8 + 4 * k, fw(r.uniform(-500, 500))) for k in range(3)]
            p.append('%08X=%08X' % (obj + 0x84, ((v if isinstance(v, int) else r.randint(0, 0x20)) << 16)))
            p.append('800BEA34=%08X' % ((1 if v == 'a' else 0) << 8))
            p.append('%08X=%08X' % (obj + 0x2E8, 1 if v == 'b' else r.choice([0, 2])))
            print('k%03d_%02X_s%d_%s ! ! %s ! ! ! ! ! ' % (n, kind, slot, v, ','.join(p))); n += 1
