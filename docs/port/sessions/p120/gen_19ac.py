#!/usr/bin/env python3
# P120: setups for func_151E19AC (players page). Run with DIFFTEST_VARARGS_REF=1.
L = []
def setup(name, ec6=0xFF, ec5=0xFF, joined=2, queue=(0, 1), pads=(0, 0, 0, 0), d140=0, inp=0, x42=0):
    q = list(queue) + [0x7F] * (16 - len(queue))
    p = ['80090174=80480000', '80480020=%04X%04X' % (inp, pads[0]), '80480024=%04X%04X' % (pads[1], pads[2]),
         '80480028=%04X0000' % pads[3], '80480040=0000%02X00' % x42, '800E0EC4=00%02X%02X00' % (ec5, ec6),
         '800901E0=%02X000000' % joined, '80090140=%02X000000' % (d140 & 0xFF), '800BEE04=00000002']
    p += ['%08X=%s' % (0x800901E4 + i, ''.join('%02X' % (b & 0xFF) for b in q[i:i + 4])) for i in range(0, 16, 4)]
    L.append('%s ! ! %s ! ! ! ! !' % (name, ','.join(p)))
for ec6, ec5 in ((0xFF, 0x10), (0xFF, 0xF0), (0xFF, 0xFF), (4, 0x40), (4, 0x41), (2, 0x20), (0, 0x80)):
    for inp in (0, 0x10, 0x20, 0x30):
        setup('fade_e%X_a%X_i%X' % (ec6, ec5, inp), ec6=ec6, ec5=ec5, inp=inp)
for x42 in (0, 1, 2):
    for joined in (0, 1, 2, 3, 4):
        for d140 in (-1, 0, 1, 3, 12):
            for pads in ((0, 0, 0, 0), (9, 0, 0, 0), (0, 6, 0, 0), (1, 8, 4, 2), (0xF, 0, 0, 0), (6, 6, 6, 6)):
                q = [(k * 3) % 4 for k in range(joined)]
                if joined >= 3: q[1] = -1
                setup('q_s%d_j%d_d%d_p%X%X%X%X' % (x42, joined, d140, *pads), joined=joined, queue=q, pads=pads, d140=d140, x42=x42)
print('\n'.join(L))
