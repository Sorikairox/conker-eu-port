#!/usr/bin/env python3
"""P70: knob setups for func_1502FED8 (model switch) -> sfed8.txt. EU addresses: objects 0x800CC6F0,
D_800D1588 0x800D19A8 (s32 per id), D_800C5A90 0x800C5EB0 (s16 per model), D_800C35EA 0x800C3A0A."""
import random
R = random.Random(0xFED8)
lines = []
for n in range(50):
    idx = R.choice([0, 1, 5]); O = 0x800CC6F0 + idx * 0x32C
    idv = R.choice([3, 10, 20]); models = [R.choice([3, 10, 20, 31]) for _ in range(4)]
    cnt = R.choice([2, 4]); cur = R.choice([0, 1, 2]); req = R.choice([0, 0xFF, 1, 2, 3, 5])
    pk = {O + 4: idv << 24, O + 0x1C8: (cur << 24) | (req << 16) | R.randint(0, 0xFFFF), O + 0x2C8: (R.randint(0, 255) << 24) | (cnt << 16),
          O + 0x2C4: 0x80490000, 0x80490000: (models[0] << 24) | (models[1] << 16) | (models[2] << 8) | models[3],
          O + 0x84: R.choice([0, 5, 40, 100]) << 16, 0x800C3A08: R.choice([0, 1]) << 8}
    for i in (3, 10, 20, 31):
        pk[0x800D19A8 + 4 * i] = R.choice([0x80600000, 0x80610000])
    for i in (2, 3, 10, 11, 20, 21, 30, 31):
        a = 0x800C5EB0 + 2 * i; w = a & ~3
        pk[w] = pk.get(w, 0) | (R.choice([10, 50, 0x8005]) << (16 if a == w else 0))
    poke = ','.join('%08X=%08X' % kv for kv in sorted(pk.items()))
    lines.append('f%02d_r%X_c%d ! 0=%08X ! %s ! !' % (n, req, cur, O, poke))
print('\n'.join(lines))
