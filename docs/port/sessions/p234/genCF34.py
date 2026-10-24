#!/usr/bin/env python3
# P234: setups for func_1508CF34 (rail_racer_steer). Racer i: record D_800CC2D0 (EU 800CC6F0, 0x32C each): +0x318
# vehicle 80460000 (control block +0x36C = 80490000), +0x31C state 80450000 (+0x78 kind). Rail D_800D27D0 = 80470000
# (+0x16BC race, +0x16B4 scale, per racer +0x17A8 / +0x1828 / +0x17E8 aim, +0x1868 rate, +0x29C time, +0x16C0 mask).
# Node record (func_1505EEF4, jal 1505F2A0) = 80480000 or NULL. func_1505A630 = jal 1505A9B0 (u16 angles),
# func_15144BC8 = jal 15145138 (RETF: base, cur, diff, dp), sinf = jal 15048050. D_800BE628 = EU 800BEA48,
# D_800BE9E4 = EU 800BEE04 (frame time), D_800E1000 difficulty, D_800BEDCC frame counter.
O0, ST, VEH, CTL, RAIL, REC = 0x800CC6F0, 0x80450000, 0x80460000, 0x80490000, 0x80470000, 0x80480000
def f(x):
    import struct; return struct.unpack('>I', struct.pack('>f', x))[0]
def setup(name, i=0, node=5, limit=0, replan=0, ox=0, oz=0, kind=0x10, veh=False, dif=0, race=0, rec0=0, rate=0.5, ft=1,
          r29c=0, mask=0, ang='2000;1000', F=(10.0, 20.0, 30.0, 5.0), recnull=False, near=False, rpos=(512.0, 64.0, 256.0),
          st170=20.0, objx=None, v76=0x1234):
    o = O0 + i * 0x32C
    pk = {o + 0x318: VEH if veh else 0, o + 0x31C: ST, ST + 0x78: kind << 24, 0x800D27D0: RAIL, 0x800E1000: (dif & 0xFF) << 24,
          RAIL + 0x16BC: (race & 0xFFFF) << 16, RAIL + 0x16B4: f(2.0), REC: rec0, 0x800BEE04: ft, 0x800BEA48: 0x804A0000,
          0x804A006C: f(320.0), 0x804A0070: f(240.0), 0x800BEDCC: 0x25,
          RAIL + 0x1868 + 4 * i: f(rate), RAIL + 0x29C + 4 * i: r29c & 0xFFFFFFFF, RAIL + 0x16C0 + 4 * i: mask,
          RAIL + 0x17A8 + 4 * i: f(100.0), RAIL + 0x1828 + 4 * i: f(50.0), RAIL + 0x17E8 + 4 * i: f(10.0),
          o + 0x14: f(rpos[0] if near else 0.0), o + 0x18: f(5.0), o + 0x1C: f(rpos[2] if near else 0.0), o + 0x40: f(30.0),
          o + 0x74: v76, o + 0x78: 0x00005678,
          REC + 0x14: f(rpos[0]), REC + 0x18: f(rpos[1]), REC + 0x1C: f(rpos[2]), REC + 0x2C: f(rpos[0] - 6.0), REC + 0x34: f(rpos[2] + 4.0),
          REC + 0x1A4: 0x01200080, REC + 0x1A8: 0xFF200000,
          ST + 0x16C: f(15.0), ST + 0x170: f(st170), ST + 0x140: f(40.0), ST + 0x88: 0x00000101, ST + 0x8C: 0x12345678, ST + 0x90: f(-60.0),
          VEH + 0x36C: CTL, VEH + 0x1A4: f(-70.0), CTL: 0x01000000}
    if near:
        pk[RAIL + 0x17A8 + 4 * i] = f(rpos[0]); pk[RAIL + 0x1828 + 4 * i] = f(rpos[2])
    if objx is not None: pk[o + 0x14] = f(objx)
    a = '0=%X,1=%X,2=%X,3=%X,4=%X,5=%X' % (i, node & 0xFFFFFFFF, limit, replan, ox & 0xFFFFFFFF, oz & 0xFFFFFFFF)
    ret = '1505F2A0=%X,1505A9B0=%s' % (0 if recnull else REC, ang)
    retf = '15145138=%s,15048050=3F000000' % ';'.join('%08X' % f(x) for x in F)
    print('%s ! %s ! %s ! %s ! %s ! ! ! !' % (name, a, ','.join('%08X=%08X' % kv for kv in sorted(pk.items())), ret, retf))
setup('node_neg', node=-1)
setup('rec_null', recnull=True)
setup('plain', kind=0x10)
setup('plain_veh', kind=0x10, veh=True)
setup('plain_limit', kind=0x10, limit=1)
setup('plain_yaw200', F=(10.0, 20.0, 200.0, 5.0))
setup('plain_yawneg', F=(10.0, 20.0, -60.0, 5.0))
setup('plain_yaw45', F=(10.0, 20.0, 45.0, 5.0))
setup('plain_dp450', F=(10.0, 20.0, 3.0, 450.0), st170=900.0)
setup('plain_dp600', F=(10.0, 20.0, 3.0, 600.0))
setup('plain_big', F=(10.0, 20.0, 30.0, -20.0))
setup('special_limit', kind=0x24, limit=1)
setup('special_nolimit', kind=0x23, limit=0)
setup('special_veh', kind=0x24, veh=True)
setup('special_18_race', kind=0x18, race=0xB9)
setup('special_41_dif3', kind=0x41, dif=3)
setup('k14_race', kind=0x14, race=0xB9)
setup('k3F_dif3', kind=0x3F, dif=4)
setup('k16_race', kind=0x16, race=0xB9)
setup('k10_race', kind=0x10, race=0xB9)
setup('k9_neg', kind=9, r29c=-1)
setup('k9_0', kind=9, r29c=0, veh=True)
setup('k9_big', kind=9, r29c=1000)
setup('k9_ox', kind=9, ox=20)
setup('k38_limit', kind=0x38, limit=1)
setup('k38_nolimit', kind=0x38, limit=0)
setup('k38_neg', kind=0x38, r29c=-5)
setup('k15', kind=0x15, veh=True)
setup('k15_nov', kind=0x15)
setup('k1B_bit', kind=0x1B, mask=0x10001 << 5, veh=True)
setup('k1B_nobit', kind=0x1B, mask=0x10001 << 4)
setup('k1B_race', kind=0x1B, race=0xB9, mask=0xFFFFFFFF)
setup('k1B_high', kind=0x1B, mask=0xFFFFFFFF, F=(10.0, 20.0, 40.0, 25.0))
setup('k3', kind=3, veh=True)
setup('k3_nov', kind=3, oz=4, ox=0)
setup('k3_near', kind=3, near=True)
setup('rec1F', rec0=0x1F, replan=1)
setup('replan', replan=1)
setup('replan_veh', replan=1, veh=True, kind=0x16)
setup('rate2', rate=2.0)
setup('ft3', rate=0.25, ft=3)
setup('near', near=True)
setup('oz_close', oz=3, ox=0, rpos=(10.0, 64.0, 20.0))
setup('oz_ox', oz=3, ox=-20, rpos=(60.0, 64.0, 40.0))
setup('oz_far', oz=3, ox=7)
setup('ox_only', ox=-30)
setup('racer1', i=1, kind=0x38, limit=1, veh=True)
setup('racer2_k9', i=2, kind=9, ox=10, oz=2, r29c=3)
setup('ang_hi', ang='FFFF;8000')
setup('near07', near=True, objx=512.0 - 0.7)
setup('plain_small', F=(10.0, 20.0, 5.0, 2.0))
setup('plain_tiny', F=(10.0, 20.0, 1.0, 1.0))
setup('k1B_bit_small', kind=0x1B, mask=0x10001 << 5, veh=True, F=(10.0, 20.0, 1.0, 1.0))
setup('k1B_nobit_small', kind=0x1B, mask=0x10001 << 4, F=(10.0, 20.0, 1.0, 1.0))
setup('k1B_mid', kind=0x1B, mask=0xFFFFFFFF, F=(10.0, 20.0, 3.0, 2.25))
setup('k1B_low', kind=0x1B, mask=0x0FFFFFFF, F=(10.0, 20.0, 1.0, -1.0))
setup('k3_far', kind=3, rpos=(2000.0, 64.0, 100.0))
setup('k3_neg', kind=3, v76=0x5000, veh=True)
setup('k9_eq', kind=9, r29c=10)
setup('k15_dp600', kind=0x15, F=(10.0, 20.0, 3.0, 600.0))
