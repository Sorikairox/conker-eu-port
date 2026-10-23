#!/usr/bin/env python3
"""P80: knob setups for func_150322B8 (p80/knobs.sh). usage: gen22b8.py [full|quick]
Args: 0 att (0x804A0000), 1 obj (0x804B0000). att+0x48 = anim state 0x804C0000, obj+0x2D0 = source anim 0x804D0000.
Bytes: att[1] model id, att[2] mode; obj[4] kind, obj[5] state, obj+0x84 (u16) animation id.
D_80090680 / D_80090684 (EU addresses equal) poked. Callees func_1503F8A8 / func_1505E060 are stubs: the index shows
in func_1503F8A8's a2.
'full' sweeps every key of every jump table (all animation ids 0xA0..0x360 for model 0x8F); 'quick' samples them."""
import random
import struct
import sys

full = len(sys.argv) > 1 and sys.argv[1] == 'full'
r = random.Random(0x22B8)
ATT, OBJ, ANIM, SRC = 0x804A0000, 0x804B0000, 0x804C0000, 0x804D0000
KINDS_DEFAULT = [0x00, 0x59, 0x5C, 0x73, 0x75, 0x7B, 0x87, 0x8B, 0x99, 0xB5, 0xFF]


def f2h(x):
    return struct.unpack('>I', struct.pack('>f', x))[0]


cases = []   # (kind, model, id, extra)
cases.append((0x58, 0x9B, 2, 'nullanim'))
cases.append((0x5A, 0x8F, 0x200, 'nullanim'))
for m in [0x9B, 0x9A, 0x00]:
    for i in [2, 3, 0x27, 0x28, 0, 0x29, 0x9B, 0x300]:
        cases.append((0x58, m, i, ''))
cases.append((0x5B, 0x9B, 2, ''))
cases.append((0x5B, 0x8F, 0x200, ''))
for k in [0x5A, 0x74, 0x7A]:
    ids = list(range(0, 0x2B)) + [0x2B, 0x4F, 0x50, 0x51, 0x52, 0xFFFF] if (full or k == 0x5A) else [0, 4, 0x13, 0x2A, 0x2B, 0x50, 0x51, 0x52]
    for i in ids:
        cases.append((k, r.choice([0x8F, 0x9B, 0x83]), i, ''))
per_model = {
    0x83: [0x5E, 0x5F, 0x60, 0xB3, 0xFA, 0x61, 0],
    0x85: [0x13E, 0x13F, 0x7C, 0, 0x140, 0x7D],
    0x87: list(range(0x16F, 0x17D)),
    0x88: [0x11, 0x26, 0, 0x27],
    0x89: [0x47, 0x49, 0x81, 0x48, 0],
    0x8D: [0x323, 0x324, 0x325, 0],
    0x8E: [0xB4, 0xB5, 0xB6, 0xDD, 0xDE, 0xDF, 0xB3],
    0x91: [0x10, 0x12, 0x11, 0],
    0x98: [0x12C, 0x12D, 0x12E, 0x142, 0x2AA, 0x358, 0x12F, 0],
    0x9A: [1, 5, 0, 2] + list(range(0x12, 0x26)),
    0x9B: [0xC, 0x13, 0x1B7, 0x1B8, 0x22E, 0, 0x14],
    0x9C: [0, 7],
    0x9D: [0x13, 0x20, 0x22, 0x21C, 0x241, 0, 0x21],
    0x9E: [0x1D6, 0x1D7, 0x1D8, 0x257, 0x275, 0, 0x1D9],
    0x9F: [0x34, 0x35, 0x36, 0x37, 0x33, 0x38, 0],
    0x84: [0, 0x200], 0x8A: [0], 0x99: [0], 0x82: [0], 0xA0: [0],
}
for m, ids in per_model.items():
    for i in ids:
        kinds = KINDS_DEFAULT if not full else KINDS_DEFAULT
        for k in (r.sample(kinds, 3) if m in (0x9A, 0x9B, 0x9D, 0x9F, 0x98) else [r.choice(kinds)]):
            cases.append((k, m, i, ''))
    if m in (0x9A, 0x9B, 0x9D, 0x9F, 0x98):   # the kind-specific branches
        for i in ids:
            cases.append(({0x9A: r.choice([0x87, 0x99]), 0x9B: 0x8B, 0x9D: 0x8B, 0x9F: 0xB5, 0x98: 0x8B}[m], m, i, ''))
    if m == 0x9A:
        for i in ids:
            cases.append((0x99, m, i, ''))
            cases.append((0x87, m, i, ''))
big = list(range(0xA0, 0x361)) if full else sorted(set([0xA8, 0xAE, 0xB9, 0xDA, 0xDB, 0x103, 0x104, 0x107, 0x151,
                                                        0x152, 0x17E, 0x17F, 0x34D, 0x34E, 0x2AA] +
                                                       r.sample(range(0x104, 0x152), 20) + r.sample(range(0x17F, 0x34E), 60)))
for i in big:
    cases.append((r.choice(KINDS_DEFAULT), 0x8F, i, ''))
for i in (r.sample(range(0xA0, 0x361), 40) if full else [0xA8, 0x104, 0x17F, 0x2E0]):
    cases.append((r.choice(KINDS_DEFAULT), 0x90, i, ''))

for t, (kind, model, aid, extra) in enumerate(cases):
    p = []
    o5 = r.choice([5, 5, 0, 1, 4]) if r.random() < 0.6 else r.getrandbits(8)
    mode = r.getrandbits(8)
    p.append('%08X=%02X%02X%02X%02X' % (ATT, r.getrandbits(8), model, mode, r.getrandbits(8)))
    p.append('%08X=%08X' % (ATT + 0x18, r.getrandbits(32)))
    p.append('%08X=%08X' % (ATT + 0x1C, r.getrandbits(32)))
    p.append('%08X=%08X' % (ATT + 0x20, r.getrandbits(32)))
    p.append('%08X=%08X' % (ATT + 0x48, 0 if extra == 'nullanim' else ANIM))
    p.append('%08X=%08X' % (OBJ + 4, (kind << 24) | (o5 << 16) | r.getrandbits(16)))
    p.append('%08X=%08X' % (OBJ + 0x24, f2h(r.choice([0.0, 0.0, -0.0, 1.5, -2.0]))))
    p.append('%08X=%08X' % (OBJ + 0x3C, f2h(r.choice([0.0, 0.5, -0.5, 3.0]))))
    p.append('%08X=%04X%04X' % (OBJ + 0x84, aid, r.getrandbits(16)))
    hassrc = r.random() < 0.8
    p.append('%08X=%08X' % (OBJ + 0x2D0, SRC if hassrc else 0))
    p.append('%08X=%08X' % (OBJ + 0x2E8, r.choice([0, 0, 1, 0x100])))
    # animation state: current index sometimes equal to the chosen one (func_1505E060 path)
    cur = r.choice([0, 1, 2, 3, 4, 5, 6, 0x1A, 0x44, 0x8000, 0x8003, r.getrandbits(16)])
    p.append('%08X=%04X%04X' % (ANIM + 4, cur, r.getrandbits(16)))
    fr = r.choice([0.0, 5.0, 9.0, 10.0, 20.0])
    p.append('%08X=%08X' % (ANIM + 8, f2h(fr)))
    p.append('%08X=%08X' % (ANIM + 0x18, f2h(r.choice([10.0, 10.0, 1.0, 30.0]))))
    p.append('%08X=%02X%02X%04X' % (ANIM + 0x38, r.getrandbits(8), r.choice([0, 0, 1, 0x80]), r.getrandbits(16)))
    p.append('%08X=%08X' % (ANIM + 0x3C, r.getrandbits(32)))
    p.append('%08X=%02X%02X%02X%02X' % (ANIM + 0x214, r.getrandbits(8), r.choice([0, 0, 1]), r.getrandbits(8), r.getrandbits(8)))
    p.append('%08X=%08X' % (SRC + 8, f2h(r.choice([0.0, 4.0, 9.0, 9.5, 12.0, 25.0]))))
    p.append('%08X=%08X' % (SRC + 0x38, r.getrandbits(32)))
    p.append('%08X=%04X%04X' % (SRC + 0x3C, r.choice([0x3FF, 0x3FF, 0, 0x3FE]), r.getrandbits(16)))
    p.append('80090680=%08X' % r.getrandbits(32))
    p.append('80090684=%08X' % r.getrandbits(32))
    print('k%03d_k%02X_m%02X_i%X ! 0=%X,1=%X ! %s ! ! ! ! ! ' % (t, kind, model, aid, ATT, OBJ, ','.join(p)))
