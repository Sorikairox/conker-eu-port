#!/usr/bin/env python3
# P128: setups for func_1510CE28 (texture scrollers). EU: count byte D_800D9E64 = 800DA284, record pointer array
# D_800DA280 = 800DA280 (array[1] overlaps the count, so at most one record is testable), D_800B1220 vertex buffers,
# D_800BE9E4 (frame delta) = 800BEE04. Record at 80410000, buffers 80420000 / 80430000, base pairs 80440000 / 80450000.
import random
random.seed(28)
def pairs(a, n):
    return ['%08X=%08X' % (a + 4 * i, random.getrandbits(32)) for i in range(n)]
for n, (cnt, dis, p0, p1, n0, n1, s0, s1, ang, spd, rad, dt) in enumerate([
        (1, 0, 1, 1, 4, 3, 2, 5, 0x1234, 0x0100, 0x40, 2), (1, 0, 1, 0, 8, 0, 0, 0, 0xFFF0, 0x0333, 0x200, 1),
        (1, 0, 1, 1, 1, 6, 7, 1, 0x8000, 0xFFFF, 0xFFFF, 3), (1, 0, 1, 1, 0, 2, 0, 3, 0x4000, 0x10, 0x8000, 1),
        (1, 1, 1, 1, 4, 4, 0, 0, 0x1000, 0x10, 0x40, 1), (0, 0, 1, 1, 4, 4, 0, 0, 0x1000, 0x10, 0x40, 1),
        (1, 0, 1, 1, 5, 0, 1, 2, 0x0000, 0x0000, 0x7F, 7), (1, 0, 1, 1, 3, 3, 0, 0, 0xC000, 0x1001, 0x123, 0x10)]):
    poke = ['800DA284=%02X000000' % cnt, '800DA280=80410000', '800B1220=80420000', '800B1224=80430000', '800BEE04=%08X' % dt,
            '80410000=%08X' % (0x80440000 if p0 else 0), '80410004=%08X' % (0x80450000 if p1 else 0),
            '80410008=%02X%02X%02X%02X' % (n0, n1, s0, s1), '8041000C=%02X00%04X' % (dis, ang), '80410010=%04X%04X' % (spd, rad)]
    poke += pairs(0x80440000, 8) + pairs(0x80450000, 8)
    poke += ['%08X=%08X' % (0x80420000 + 4 * i, random.getrandbits(32)) for i in range(0, 64, 3)]
    print('s%d !  ! %s ! ! ! ! ' % (n, ','.join(poke)))
