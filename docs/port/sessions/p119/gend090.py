#!/usr/bin/env python3
# P119: setups for func_1510D090 (tint_channels_update). usage: gend090.py N SEED
import random, struct, sys
n, seed = int(sys.argv[1]), int(sys.argv[2]); R = random.Random(seed)
def f(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
def words(base, b):
    return {base + i: ''.join('%02X' % x for x in b[i:i + 4]) for i in range(0, len(b), 4)}
for s in range(n):
    p = R.choice([0, 1, 2, 3]); pk = {0x800DC420: '80480000', 0x80480000 + p * 0x9A0 + 0x5F0: '%08X' % R.choice([1, 1, 1, 3, 0, 2]),
                                      0x800BEE04: '%08X' % R.choice([1, 2, 3, 30, 100])}
    def bytes12(ch): return [R.choice(ch) for _ in range(12)]
    pk.update(words(0x800DA2A8, bytes12([0, 1, 7, 0x40, 0xFF])))
    pk.update(words(0x800DA2B8, bytes12([0, 1, 10, 0x7F, 0xFF])))
    pk.update(words(0x800DA2C8, bytes12([0, 1, 0x40, 0x7F, 0x80, 0xFE, 0xFF])))
    pk.update(words(0x800DA2D4, [R.choice([0, 0x7F, 0xFF, 3]) for _ in range(4)]))
    t = bytes12([0, 0, 1, 0x7F, 0x80, 0xFF, 2]); t[p * 3] = R.choice([0, 0, 1, 0x7F, 0xFF])
    pk.update(words(0x800DA2D8, t))
    pk.update(words(0x800D9F88, bytes12([0, 1, 0x40, 0x7F, 0x80, 0xFF])))
    pk.update(words(0x800D9F98, bytes12([0, 1, 0x40, 0x7F, 0x80, 0xFF])))
    ph = [R.choice([0, 0x10, 0xFF0, 0xFFF, 0x1234, 0x8000, 0x7FF]) for _ in range(12)]
    pk.update({0x800DA290 + 4 * i: '%04X%04X' % (ph[2 * i], ph[2 * i + 1]) for i in range(6)})
    sins = ';'.join(f(R.choice([0.0, 1.0, -1.0, 0.5, -0.25, 0.999])) for _ in range(3))
    print('sd090_%d ! 0=%X ! %s !  ! 15048CA0=%s !  !  ! ' % (s, p, ','.join('%08X=%s' % kv for kv in sorted(pk.items())), sins))
