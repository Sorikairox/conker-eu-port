#!/usr/bin/env python3
# P232: setups for func_15006BEC (save_slot_pack). ARG 0 = slot. EU addresses: D_800BE818 records 800BE818 (+8
# stamp, +0xE area), D_8002AC5C 8002AF9C (EEPROM off), D_800BE810 800BE810 (widths ptr -> 80460000),
# D_800C3A60 800C3E80 (69 s64), D_800D2E4C 800D326C (ptr -> 80470000, 27 bytes), D_800D2E60 800D3280 (9 bytes),
# D_800BE3DF 800BE7FF, D_800BE800, D_800BE3E8 800BE808. func_150859AC jal 15085E1C (RET).
import random
def setup(name, slot, stamps=(5, 9, -1), areas=(0, 1, 2), off=0, wseed=1, wmax=7, widths_null=False):
    rnd = random.Random(wseed)
    w = {}
    for k in range(3):
        w[0x800BE818 + 16 * k + 8] = stamps[k] & 0xFFFFFFFF
        w[0x800BE818 + 16 * k + 0xC] = 0x11220000 | ((areas[k] & 0xFF) << 8) | 0x33
    w[0x8002AF9C] = off << 24
    w[0x800BE810] = 0 if widths_null else 0x80460000
    wd = [rnd.randint(1, wmax) for _ in range(69)]
    for i in range(0, 72, 4):
        b = (wd + [0, 0, 0])[i:i + 4]
        w[0x80460000 + i] = (b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3]
    for i in range(69):
        v = rnd.getrandbits(64)
        w[0x800C3E80 + 8 * i] = v >> 32; w[0x800C3E80 + 8 * i + 4] = v & 0xFFFFFFFF
    w[0x800D326C] = 0x80470000
    for i in range(0, 28, 4): w[0x80470000 + i] = rnd.getrandbits(32)
    for i in range(0x800D3280, 0x800D328C, 4): w[i] = rnd.getrandbits(32)
    w[0x800BE7FC] = rnd.getrandbits(32); w[0x800BE800] = rnd.getrandbits(32); w[0x800BE808] = rnd.getrandbits(32)
    pk = ','.join('%08X=%08X' % (a, v) for a, v in sorted(w.items()))
    print('%s ! 0=%X ! %s ! 15085E1C=%X,1502B8B8=8045FFF8 ! ! ! ! !' % (name, slot & 0xFFFFFFFF, pk, 0xABCD1234))
setup('s0', 0)
setup('s1', 1, wseed=2)
setup('s2', 2, wseed=3)
setup('s0_off', 0, off=1)
setup('all_live', 1, stamps=(1, 2, 3), areas=(0, 1, 2), wseed=4)
setup('none_live', 0, stamps=(-1, -2, -5), wseed=5)
setup('area3_used', 2, stamps=(1, 2, 3), areas=(3, 1, 0), wseed=6)
setup('all_used', 0, stamps=(1, 2, 3), areas=(3, 2, 1), wseed=7)
setup('dup_areas', 1, stamps=(1, 2, -1), areas=(2, 2, 3), wseed=8)
setup('stamp_wrap', 0, stamps=(0x7FFFFFFF, 2, 3), wseed=9)
setup('stamp_big', 0, stamps=(0x5FFFFFFF, 2, 3), wseed=9)
setup('stamp_neg', 2, stamps=(4, 2, -2), wseed=10)
setup('wide', 1, wseed=11, wmax=8)
setup('narrow', 0, wseed=12, wmax=1)
setup('widths_alloc', 1, wseed=13, widths_null=True)
setup('rec2_area3', 0, stamps=(1, 2, 3), areas=(1, 0, 3), wseed=14)
setup('stamp0', 1, stamps=(0, 2, -1), areas=(3, 1, 2), wseed=15)
