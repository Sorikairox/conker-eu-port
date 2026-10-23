#!/usr/bin/env python3
# P130: setups for func_15186A9C (knobs.sh format: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB)
# Cells at 0x80400000 + 0x1000 * k hold a triangle list at +0xE; flags table at 0x80420000 (D_800D3668 -> it).
import random
rng = random.Random(130)
CELL, FLAGS, BUF = 0x80400000, 0x80420000, 0x80440000
def pokes_bytes(addr, bs):
    # word-aligned pokes covering addr .. addr+len(bs), other bytes 0
    a0 = addr & ~3; data = bytearray(addr - a0) + bytearray(bs)
    data += bytearray((-len(data)) % 4)
    return ['%08X=%08X' % (a0 + i, int.from_bytes(data[i:i + 4], 'big')) for i in range(0, len(data), 4)]
def rle(rng, kind):
    out = []; idx = 0
    for _ in range(rng.randrange(1, 25)):
        r = rng.random()
        if r < 0.3 or kind == 'abs':
            t = rng.choice([rng.randrange(0, 0x1760), rng.randrange(0x1700, 0x8000), 0x175F, 0x1760, 0])
            out += [0x80 | (t >> 8), t & 0xFF]; idx = t
        else:
            out.append(rng.randrange(1, 0x80))
    return out + [0]
for s in range(40):
    n = rng.choice([1, 2, 3, rng.randrange(1, 17), 16])
    flag = rng.choice([0, 0, 1, 0x80])
    pk = ['800DE470=%08X' % (flag << 16), '800D3A88=%08X' % FLAGS]
    cells = []
    for k in range(n):
        c = CELL + 0x1000 * k; cells.append('%08X' % c)
        pk += pokes_bytes(c + 0xE, rle(rng, rng.choice(['mix', 'abs'])))
    # flags: random 0 / 1 / 2 words over the first 0x1760 bytes would be too many pokes: one word repeated
    pk.append('%08X=%s*%d' % (FLAGS, rng.choice(['01010101', '01000102', '00010001', '01020100']), 0x1760 // 4))
    x, z, r = rng.randrange(-3000, 3000), rng.randrange(-3000, 3000), rng.choice([0xE6, rng.randrange(0, 500)])
    k = rng.randrange(0, 6)
    args = '0=%X,1=%X,2=%X,3=%X,4=80450000,5=%X' % (x & 0xFFFFFFFF, z & 0xFFFFFFFF, r, BUF, BUF + 0x1000)
    ret = '1510FCA0=%X,150A6070=%X' % (n if s else 0, BUF + 0x3C * k)
    print('s%d ! %s ! %s ! %s ! ! 1510FCA0=3:%s ! !' % (s, args, ','.join(pk), ret, ';'.join(cells)))
