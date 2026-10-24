#!/usr/bin/env python3
# P232: setups for func_15073FA0 (event_spawn_helper_object). EU addresses: D_800D1580 800D19A0 (command word),
# D_800D154C 800D196C (me), D_800BE616 800BEA36, D_800C3E78 800C4298, D_800CC2D0 800CC6F0 (stride 0x32C),
# D_800D20FC 800D251C, D_800D2104 800D2524, D_800D252C 800D252C. Callees (jal words): func_15083E0C 15084274,
# func_15082E44 15082E44, func_15031C4C 15031C4C, func_150ADA20 150ADF00, func_1505A184 1505A504 (out a3 / sp10 /
# sp14), func_15143134 151436A4 (writes obj x/y/z through a1), func_100100E0 100103D0, func_151A3940,
# func_1506B04C, func_150F1C5C.
import struct
def f(v): return struct.unpack('>I', struct.pack('>f', v))[0]
ME, CTL, TBL, FLG, RECS, MDLS, MDL, SND = 0x80450000, 0x80460000, 0x80470000, 0x80480000, 0x80490000, 0x804A0000, 0x804B0000, 0x804C0000
def setup(name, kind=0x75, cmd=0x10, rec=3, n=3, tbl=True, be=1, ctl=True, c198=1, charge=50, ang=0x1234, c12=0x100,
          rnd=(0x12345, 0x6789A), c3e78=7, m13f=2):
    mem = {}
    def w8(a, v): mem[a] = v & 0xFF
    def w16(a, v): w8(a, v >> 8); w8(a + 1, v)
    def w32(a, v): w16(a, v >> 16); w16(a + 2, v)
    w32(0x800D19A0, cmd); w32(0x800D196C, ME); w8(0x800BEA36, be); w8(0x800C4298, c3e78)
    w32(0x800D251C, RECS); w32(0x800D2524, MDLS); w32(0x800D252C, FLG)
    w8(ME + 4, kind); w32(ME + 0x14, f(10.5)); w32(ME + 0x18, f(-20.25)); w32(ME + 0x1C, f(300.0))
    w32(ME + 0x20, f(3.5)); w32(ME + 0x3C, f(12.0)); w16(ME + 0x76, 0x4321); w16(ME + 0x7A, ang)
    w32(ME + 0x1D4, TBL if tbl else 0); w8(ME + 0x222, 0x5C); w32(ME + 0x31C, CTL if ctl else 0)
    w16(CTL + 0x12, c12); w32(CTL + 0x170, f(30.0)); w8(CTL + 0x198, c198); w16(CTL + 0x19C, charge)
    w8(CTL + 0x19B, 0x77); w8(CTL + 0x78, 0x66)
    if n > 0:
        o = 0x800CC6F0 + (n - 1) * 0x32C
        w8(o + 0x13F, m13f); w8(o + 0x1CA, 0x15); w32(o + 0x18, f(7.0))
        w32(MDLS + 4 * m13f, MDL)
    w32(SND + 0x3C, 0xABCD1234)
    pk = ','.join('%08X=%02X%02X%02X%02X' % (a, mem.get(a, 0), mem.get(a + 1, 0), mem.get(a + 2, 0), mem.get(a + 3, 0))
                  for a in sorted({a & ~3 for a in mem}))
    ret = '15084274=%X,15082E44=%X,15031C4C=%X,150ADF00=%s' % (rec & 0xFFFFFFFF, n, SND, ';'.join('%X' % r for r in rnd))
    outw = '1505A504=3:%X/4:%X/5:%X' % (f(1.5), f(-2.75), f(4.0))
    outa = '151436A4=1:%X;%X;%X' % (f(111.0), f(222.0), f(333.0))
    print('%s ! ! %s ! %s ! ! %s ! %s ! !' % (name, pk, ret, outa, outw))
setup('rec_none', rec=-1)
setup('obj_none', n=0)
setup('k75_tbl', kind=0x75)
setup('k80_tbl', kind=0x80)
setup('k5A_tbl', kind=0x5A)
setup('k7B_10_tbl', kind=0x7B, cmd=0x00AB0010)
setup('k7B_10_tbl_bit16', kind=0x7B, cmd=0x00A50010)
setup('k7B_A', kind=0x7B, cmd=0xA)
setup('k7B_A_notbl', kind=0x7B, cmd=0xA, tbl=False)
setup('k7B_other', kind=0x7B, cmd=0x33)
setup('k7B_10_n1', kind=0x7B, cmd=0x00030010, n=1, m13f=5)
setup('k4A', kind=0x4A)
setup('k4A_nobe', kind=0x4A, be=0)
setup('k9A', kind=0x9A, rnd=(0x1F37, 0x12345))
setup('k9A_hi', kind=0x9A, rnd=(0xFFFFFFFF, 0xFFFFFFFF))
setup('k9A_nobe', kind=0x9A, be=0, rnd=(0x800, 799))
setup('other_kind', kind=0x01)
setup('notbl', kind=0x75, tbl=False)
setup('nobe', kind=0x75, be=0)
setup('nobe_noctl', kind=0x01, be=0, ctl=False)
setup('nobe_noctl_7B', kind=0x7B, cmd=0x10, be=0, ctl=False)
setup('c198_0', kind=0x75, c198=0)
setup('c198_0_k01', kind=0x01, c198=0)
setup('bit16', kind=0x75, cmd=0x10010)
setup('charge_big', kind=0x5A, charge=0xFFF0)
setup('charge_200', kind=0x5A, charge=200, ang=0xFFFF, c12=0x8000)
setup('cmd_hi', kind=0x80, cmd=0xFFFF1234, c3e78=0xFF)
setup('n26', kind=0x5A, n=26, m13f=0)
setup('k7B_1010', kind=0x7B, cmd=0x00AB1010)
