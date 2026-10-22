#!/usr/bin/env python3
"""P70: knob setups for func_1503CE88 (tail joint matrices) -> sce88.txt. idx 1 (EU obj 0x800CCA1C), rec 0x804A0000,
joint matrices 0x804B0000 (rows 1 = up vectors, +0x30 = animated positions)."""
import random, struct
R = random.Random(0xCE88)
F = lambda v: struct.unpack('>I', struct.pack('>f', v))[0]
O = 0x800CC6F0 + 0x32C
REC, JM = 0x804A0000, 0x804B0000
lines = []
for n in range(60):
    mode = R.choice([0, 1, 2, 2]); fade = R.choice([0.0, 0.5, 1.0, 0.25])
    pk = {O + 0xB8: F(R.uniform(-30, 30)), O + 0x40: F(R.uniform(0, 360)), O + 0xC4: F(R.uniform(-30, 30)),
          O + 0x14C: F(R.choice([1.0, 0.8])), O + 0x150: F(R.choice([1.0, 1.3])), O + 0x1D4: JM,
          REC + 0x4C: R.choice([0, 0x00000A00, 0x0000FF00])}
    for j in range(23, 28):
        zero = R.random() < 0.1
        for c in range(3):
            pk[JM + j * 0x40 + 0x10 + 4 * c] = F(0.0 if zero else R.uniform(-1, 1))
            pk[JM + j * 0x40 + 0x30 + 4 * c] = F(R.uniform(-60, 60))
    same = R.random() < 0.3
    for k in range(5):
        x, z = R.uniform(-50, 50), R.uniform(-50, 50)
        if same: x, z = 5.0, -7.0
        for c, v in enumerate([x, R.uniform(0, 60), z]):
            pk[REC + 12 * k + 4 * c] = F(v)
    poke = ','.join('%08X=%08X' % kv for kv in sorted(pk.items()))
    lines.append('c%02d_m%d_f%g%s ! 0=00000001,1=%08X,2=%08X,3=%08X ! %s ! !' % (
        n, mode, fade, '_same' if same else '', mode, F(fade), REC, poke))
print('\n'.join(lines))
