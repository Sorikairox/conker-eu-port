#!/usr/bin/env python3
"""P74: setups for func_1503E5F8 (p74/knobs.sh). bcopy (0x10023E80) writes a random matrix through a1 (OUTA);
RETF: func_150AD930 0x150ADE10 (row lengths, 0 = degenerate), func_150ADDE0 0x150ADDE0 (dot sign),
func_150AD780 0x150ADC60 (cos == 0 gimbal case), func_150487E0 0x15048AD0, func_150484A0 0x15048790."""
import random, struct, itertools
r = random.Random(0xE5F8)
def f(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
t = 0
for zero_row, dot, cos in itertools.product([-1, 0, 1, 2], [-1.5, 0.0, 2.0], [0.0, 0.5]):
    m = ';'.join(f(r.choice([0.0, 1.0, -1.0, r.uniform(-100, 100)])) for _ in range(16))
    lens = [r.choice([1.0, 2.5, 0.25]) for _ in range(3)]
    if zero_row >= 0: lens[zero_row] = 0.0
    retf = ['150ADE10=' + ';'.join(f(x) for x in lens), '150ADDE0=' + f(dot), '150ADC60=' + f(cos),
            '15048AD0=' + f(r.uniform(-1.5, 1.5)), '15048790=' + f(r.uniform(-3, 3)) + ';' + f(r.uniform(-3, 3))]
    print('k%02d_z%d_d%g_c%g ! ! ! ! %s ! 10023E80=1:%s ! ! ' % (t, zero_row, dot, cos, ','.join(retf), m))
    t += 1
