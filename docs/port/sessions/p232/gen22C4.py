#!/usr/bin/env python3
# P232: setups for func_151922C4 (obj_dust_effect_update). ARG 0 = effect 80450000; ObjDustData at +0x28: obj
# (80460000, word 0 nonzero, +0x3B id, +0x1D4 model 80470000), objId +0x2C, kind +0x3C, u18 +0x40, u1C +0x44, u20
# +0x48, ground +0x4C, u48 +0x70, u4C +0x74, u50 +0x78, u52 +0x7A, u54 +0x7C, u55 +0x7D, u58 +0x80, u5C +0x84,
# u60 +0x88, u64 +0x8C; fx +1 / +0xC bytes. D_800BE9A4 = EU 800BEDC4. Callees: func_150ADA68 150ADF48 (RETF),
# func_150ADA20 150ADF00 (RET), func_1514672C 15146C9C (RET), func_15047274 15047274 (RET; OUTW ground[0] via a3),
# func_15143134 151436A4 (OUTA pos), func_151925AC (arguments compared).
import struct
def f(v): return struct.unpack('>I', struct.pack('>f', v))[0]
FX, OBJ = 0x80450000, 0x80460000
def setup(name, acc=1.5, r1c=0.0, r20=0.0, step=1.0, alive=1, idmatch=True, model=True, u60=0.5, inlvl=1, floor=1,
          u50=10, u52=5, u54=3, u55=2, rnd=(0.5, 0.25, 0.75, 0.125), ri=(13, 7), consts=False):
    w = {}
    w[FX] = 0x00AB0000; w[FX + 0xC] = 0xCD000000
    w[FX + 0x28] = OBJ; w[FX + 0x2C] = 0x42000000; w[FX + 0x3C] = 0x40
    w[FX + 0x40] = f(acc); w[FX + 0x44] = f(r1c); w[FX + 0x48] = f(r20); w[FX + 0x4C] = f(-77.0)
    w[FX + 0x70] = f(12.0); w[FX + 0x74] = f(4.0); w[FX + 0x78] = ((u50 & 0xFFFF) << 16) | (u52 & 0xFFFF)
    w[FX + 0x7C] = (u54 << 24) | (u55 << 16); w[FX + 0x80] = f(1.5); w[FX + 0x84] = f(0.5); w[FX + 0x88] = f(u60)
    w[FX + 0x8C] = 0x77000000
    w[OBJ] = alive; w[OBJ + 0x38] = 0x000000 | (0x42 if idmatch else 0x43); w[OBJ + 0x1D4] = 0x80470000 if model else 0
    w[0x800BEDC4] = f(step)
    if consts: w[0x800A84C8] = f(-111.0); w[0x800A84CC] = f(-222.0); w[0x800A84D0] = f(-333.0)
    pk = ','.join('%08X=%08X' % (a, v & 0xFFFFFFFF) for a, v in sorted(w.items()))
    ret = '15146C9C=%X,15047274=%X,150ADF00=%s' % (inlvl, floor, ';'.join('%X' % (x & 0xFFFFFFFF) for x in ri))
    retf = '150ADF48=' + ';'.join('%X' % f(x) for x in rnd)
    print('%s ! 0=%X ! %s ! %s ! %s ! 151436A4=1:%X;%X;%X ! 15047274=3:%X ! !' % (
        name, FX, pk, ret, retf, f(5.0), f(6.0), f(7.0), f(321.5)))
setup('dead', alive=0)
setup('other_id', idmatch=False)
setup('below1', acc=0.25, r1c=0.1, r20=0.2)
setup('exact1', acc=1.0)
setup('nomodel', acc=3.5, model=False)
setup('one', ri=(13, 8))
setup('three', acc=3.25, rnd=(0.5, 0.1, 0.9, 0.2, 0.7, 0.3, 0.6, 0.4, 0.8, 0.0, 0.3, 0.99, 0.5))
setup('accum', acc=0.5, r1c=0.25, r20=0.5, step=2.0, rnd=(0.5, 0.25, 0.75, 0.125, 0.3))
setup('u60_0', u60=0.0, consts=True)
setup('u60_neg', u60=-1.0)
setup('outside', inlvl=0, consts=True)
setup('nofloor', floor=0, consts=True)
setup('ground_chance', u60=0.6, rnd=(0.5, 0.59, 0.75, 0.125))
setup('ground_eq', u60=0.5, rnd=(0.5, 0.5, 0.75, 0.125))
setup('mods', u50=-3, u52=0x7FFE, u54=0xFF, u55=0xFF, ri=(0xFFFFFFFF, 0x80000001))
setup('mods2', u50=0x7FFF, u52=0, u54=0, u55=0, ri=(5, 9))
setup('mods3', u52=99, u55=200, ri=(1234567, 7654321))
setup('two_exact', acc=2.0, rnd=(0.5, 0.1, 0.9, 0.2, 0.7, 0.3, 0.6, 0.4, 0.8))
