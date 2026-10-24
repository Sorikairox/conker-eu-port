#!/usr/bin/env python3
# P198: setups for func_150877C0 (rail_track_update). records D_80087640 (EU 80087640) -> 80460000 + i * 0x84,
# objects D_800CC2D0 (EU 800CC6F0) + k * 0x32C, D_800D2104 (EU 800D2524) -> 80480000, D_800BE9E4 (EU 800BEE04),
# D_800D18A0 (EU 800D1CC0, u16), D_800D27B8 / B9 bytes. jal keys: 150893AC, 15049B94, 15049AD0, 15088E84,
# func_15042D78 = 15043068, sinf = 15048050, cosf = 15047EF0, func_1508849C, bcopy = 10023E80.
R = 0x80460000
def rec(i, t0=0x3F000000, t4=0x3F400000, t8=0x3E800000, seg=0x00030000, w28=0x00007F00, w30=0x01000203, w48=0):
    b = R + i * 0x84
    return {b: t0, b + 4: t4, b + 8: t8, b + 0x24: seg, b + 0x28: w28, b + 0x30: w30, b + 0x48: w48}
def obj(k, x=0x41200000, z=0x41A00000, cam=3, flag=0):
    b = 0x800CC6F0 + k * 0x32C
    return {b + 0x14: x, b + 0x18: 0x42480000, b + 0x1C: z, b + 0x2C: 0x41F00000, b + 0x34: 0x42200000, b + 0x40: 0x42B40000,
            b + 0x13C: cam, b + 0x31C: 0x80490000 + k * 0x100, 0x80490084 + k * 0x100: flag, b + 0x20: 0x3F800000, b + 0x44: 0}
base = {0x80087640: R, 0x800D27B8: 0x02010000, 0x800D27B0: 0, 0x800D2524: 0x80480000, 0x8048000C: 0x80481000,
        0x80480004: 0x80482000, 0x800BEE04: 0x00000105, 0x800D1CC0: 0x00020000}
OUTA = '150893AC=1:44480000;447A0000;44960000;44AF0000/2:41000000;41100000;41200000;41300000/3:42C80000;43480000;43960000;43C80000'
def setup(name, a='0=0,1=0,2=3F000000', upd=None, ret='15088E84=1', retf='15049B94=42C80000;0;43480000;0;41A00000,15049AD0=42C80000;43480000;43960000;41200000,15048050=3F000000,15047EF0=3F5DB3D7',
          outw='15049B94=3:3F800000', outb=''):
    d = dict(base)
    d.update(rec(0)); d.update(rec(1, t8=0x3F000000, seg=0x00020000, w28=0x00000300, w30=0x00010000)); d.update(obj(0)); d.update(obj(1, x=0x42C80000, cam=1))
    if upd: d.update(upd)
    poke = ','.join('%08X=%08X' % kv for kv in sorted(d.items()))
    return '%s ! %s ! %s ! %s ! %s ! %s ! %s ! %s' % (name, a, poke, ret, retf, OUTA, outw, outb)
r0 = R; r1 = R + 0x84; r2 = R + 0x108; r3 = R + 0x18C
L = [
 setup('h_mode0'),
 setup('h_mode1_fov1', a='0=0,1=1,2=3F000000', outb='15088E84=@800D27B0:01'),
 setup('h_mode2_fov2', a='0=0,1=2,2=40000000', outb='15088E84=@800D27B0:02'),
 setup('h_fov3', a='0=0,1=5,2=3F000000', outb='15088E84=@800D27B0:03'),
 setup('h_fov4', a='0=0,1=5,2=3F000000', outb='15088E84=@800D27B0:04'),
 setup('h_p1', a='0=1,1=0,2=3F000000', upd={r1 + 0x30: 0x01010000, r1 + 0x48: 0}),
 setup('h_p2_out', a='0=2,1=0,2=3F000000', upd={r2: 0x3F000000, r2 + 4: 0x3E000000, r2 + 8: 0x3F000000, r2 + 0x30: 0x01000000, 0x800D27B8: 0x02010000}),
 setup('cpu_p1', a='0=1,1=3,2=3F000000'),
 setup('cpu_p1_flagged', a='0=1,1=3,2=3F000000', upd={0x800D1CC0: 0x00010000}),
 setup('cpu_p1_mode0', a='0=1,1=0,2=3F000000'),
 setup('cpu_short', a='0=1,1=3,2=3F000000', retf='15049B94=0,15049AD0=41200000;41A00000;41300000;41A00000'),
 setup('cpu_p0', a='0=0,1=3,2=3F000000', upd={r0 + 0x30: 0x00000000}),
 setup('state2', a='0=0,1=1,2=3F000000', upd={r0 + 0x30: 0x02000203}),
 setup('state2_busy', a='0=0,1=1,2=3F000000', upd={r0 + 0x30: 0x02000203, 0x80490084: 0x01000000}),
 setup('state_neg', a='0=0,1=1,2=3F000000', upd={r0 + 0x30: 0xFF000203}),
 setup('far11', retf='15049B94=44FA0000;0'),
 setup('far_nok', ret='15088E84=0', retf='15049B94=44FA0000;0;44FA0000;0;41200000'),
 setup('grow', retf='15049B94=42C80000;0;43C80000;0;44480000;0;41200000'),
 setup('neg_d', retf='15049B94=C2C80000;0;C3480000;0;41200000', outw='15049B94=3:BF800000'),
 setup('step_clamp', retf='15049B94=461C4000;0;41200000'),
 setup('ease_hi', upd={r0: 0, r0 + 4: 0x3F800000}),
 setup('ease_lo', upd={r0: 0x3F800000, r0 + 4: 0}),
 setup('ease_mid', upd={r0: 0x3F000000, r0 + 4: 0x3F0CCCCD}),
 setup('rank4', upd={0x800D27B8: 0x04000000, 0x800D1CC0: 0x00040000, r1 + 0x30: 0x00010000, r2 + 8: 0x3F400000, r2 + 0x24: 0x00030000,
     r2 + 0x28: 0x00000100, r2 + 0x30: 0x00020000, r3 + 8: 0x3E000000, r3 + 0x24: 0x00050000, r3 + 0x28: 0x00007F00, r3 + 0x30: 0x00030000}),
 setup('rank_tie', upd={0x800D27B8: 0x03000000, r1 + 8: 0x3E800000, r1 + 0x24: 0x00030000, r1 + 0x28: 0x00007F00, r2 + 8: 0x3E800000,
     r2 + 0x24: 0x00030000, r2 + 0x28: 0x00007F00, r2 + 0x30: 0x00020000}),
 setup('rank1', upd={0x800D27B8: 0x01000000}),
 setup('rank0', upd={0x800D27B8: 0x00000000}),
 setup('no_records', upd={0x80087640: 0}),
]

r2b = R + 0x108
def rk(seg1, w28_1, seg2, w28_2=0x00007F00, flags=0):
    return {0x800D27B8: 0x03000000, 0x800D1CC0: flags << 16, r1 + 8: 0, r1 + 0x24: seg1 << 16, r1 + 0x28: w28_1, r1 + 0x30: 0x00010000,
            r2b + 8: 0, r2b + 0x24: seg2 << 16, r2b + 0x28: w28_2, r2b + 0x30: 0x00020000, r0 + 0x24: 0x00030000}
L += [
 setup('ease_065', upd={r0: 0, r0 + 4: 0x3F051EB8}),
 setup('ease_m065', upd={r0: 0x3F051EB8, r0 + 4: 0}),
 setup('tangent2', retf='15049B94=42C80000;42480000;43480000;41F00000;41A00000;41200000,15049AD0=42C80000;43480000;43960000;41200000,15048050=3F000000,15047EF0=3F5DB3D7', outw='15049B94=3:3F800000;40000000;3F000000;40400000'),
 setup('cpu_p1_mode0_clr', a='0=1,1=0,2=3F000000', upd={0x800D1CC0: 0}),
 setup('rank_7e', upd=rk(10, 0x00007E00, 5)),
 setup('rank_30k', upd=rk(0, 0x00000000, 25000)),
 setup('rank_1k', upd=rk(0, 0x00000300, 28000)),
 setup('rank_10k', upd=rk(15000, 0x00007F00, 7000, flags=2)),
]
L += [setup('d55', retf='15049B94=42D78F5C;0;41F00000;0'), setup('dm55', retf='15049B94=C23F1EB8;0;41F00000;0')]
open('150877C0_setups.txt', 'w').write('# generated by gen_77c0.py\n' + '\n'.join(L) + '\n')
print(len(L))
