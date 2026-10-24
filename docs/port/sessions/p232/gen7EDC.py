#!/usr/bin/env python3
# P232: setups for func_151D7EDC (trail_points_update). ARG 0 = object 80450000: +0x1E flags, +0x25 ring size,
# +0x2C count, +0x2D oldest, +0x2E cursor, +0x94 ring 80460000 (0x1C-byte entries, ROM-free heap: positions set
# here). Callee func_151D8CC8 (jal 151D8CC8, arguments compared). D_800BE9A4 = EU 800BEDC4.
O, R = 0x80450000, 0x80460000
def setup(name, cnt, old, cur, size=8, fl=0):
    pk = ['%08X=0000%04X' % (O + 0x1C, fl), '%08X=00%02X0000' % (O + 0x24, size),
          '%08X=%02X%02X%02X00' % (O + 0x2C, cnt & 0xFF, old & 0xFF, cur & 0xFF), '%08X=%08X' % (O + 0x94, R),
          '800BEDC4=3F400000']
    for i in range(10):
        for k in range(3): pk.append('%08X=%08X' % (R + i * 0x1C + 4 * k, 0x41000000 + i * 0x10000 + k * 0x1000))
    print('%s ! 0=%X ! %s ! ! ! ! ! !' % (name, O, ','.join(pk)))
setup('empty', 0, 0, 0)
setup('one', 1, 2, 3)
setup('wrap', 5, 6, 3)
setup('wrap0', 4, 4, 0)
setup('full', 8, 3, 3)
setup('flag8_one', 1, 2, 3, fl=8)
setup('flag8_two', 2, 1, 3, fl=8)
setup('flag8_zero', 0, 3, 3, fl=0xFFFF)
setup('flag7', 1, 1, 4, fl=0xFFF7)
setup('neg_count', 0xFE, 1, 3)
setup('size3', 3, 2, 1, size=3)
setup('old_at_cur', 3, 5, 5)
