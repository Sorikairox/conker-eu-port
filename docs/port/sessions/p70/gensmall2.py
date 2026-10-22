#!/usr/bin/env python3
"""P70: knob setups for func_1503A968 (sa968.txt) and func_1503216C (s216c.txt). EU data addresses.
usage: gensmall2.py a968|216c"""
import random, struct, sys
R = random.Random(0xA968)
F = lambda v: struct.unpack('>I', struct.pack('>f', v))[0]
EU_OBJS = 0x800CC6F0
lines = []
if sys.argv[1] == 'a968':
    for n in range(40):
        idx = R.choice([0, 1, 3]); O = EU_OBJS + idx * 0x32C; cnt = R.choice([0, 0, 1, 2, 4])
        pk = {0x800C4298: idx << 24, 0x800C4418: cnt << 8, O + 4: R.choice([0x22, 0x22, 0x22, 0x21]) << 24,
              O + 0x208: R.choice([0, 1, 64, 200, 255]) << 8, O + 0x1D4: 0x804B0000}
        for j in (1, 4, 0xE, 0x12, 0x16):
            for w in range(16):
                pk[0x804B0000 + j * 0x40 + 4 * w] = F(R.uniform(-50, 50))
        poke = ','.join('%08X=%08X' % kv for kv in sorted(pk.items()))
        lines.append('a%02d_i%d_c%d ! ! %s ! !' % (n, idx, cnt, poke))
else:
    for n in range(40):
        O = 0x80480000; DLP = 0x80490000; DL = 0x804A0000
        anim = R.choice([0x55, 0x56, 0, 0, 0x10]); y = R.choice([-1.0, 0.0, 30.0, 60.0, 119.0, 120.0, 121.0])
        pk = {O + 0x84: anim << 16, O + 0x2D0: R.choice([0x804C0000] * 5 + [0]), 0x804C0008: F(y),
              0x804D0024: DLP, DLP: R.choice([DL] * 5 + [0])}
        # display list: 12 commands, four or more G_SETTILESIZE (0xF2) at random slots
        slots = sorted(R.sample(range(12), R.choice([4, 5, 6])))
        for k in range(12):
            pk[DL + 8 * k] = (0xF2000000 | R.randint(0, 0xFFFFFF)) if k in slots else R.choice([0xFD100000, 0xE7000000, 0x06000000, 0xF5000000])
            pk[DL + 8 * k + 4] = R.randint(0, 0xFFFFFFFF)
        poke = ','.join('%08X=%08X' % kv for kv in sorted(pk.items()))
        lines.append('t%02d_a%X_y%g ! 0=804D0000,1=%08X ! %s ! !' % (n, anim, y, O, poke))
print('\n'.join(lines))
