#!/usr/bin/env python3
"""P70: knob setups for func_1503BCAC (tail chain) -> sbcac.txt. Object index 1 (0x800CCA1C; EU data addresses); +0x31C -> 0x80490000,
its +0x11C -> the tail record 0x804A0000; joint matrices 0x804B0000; camera 0x804C0000.
Stubs (EU addresses from the jal words): sinf 15048050, cosf 15047EF0, func_15048360 (acos) 15048650,
func_150484A0 (atan2) 15048790, func_15048A70 (angle difference) 15048D60, func_1503BC4C (mode) 1503BC4C."""
import random, struct
R = random.Random(0xBCAC)
F = lambda v: struct.unpack('>I', struct.pack('>f', v))[0]
O = 0x800CC6F0 + 0x32C   # EU D_800CC2D0 = 0x800CC6F0 (undefined_syms_auto.txt)
REC, JM, CAM = 0x804A0000, 0x804B0000, 0x804C0000
lines = []
def setup(n, mode, reset, pause, idv, anim, air, spd, cam, b78, timer, fade, step, fe, d40bd):
    pk = {}
    pk[O + 4] = idv << 24
    pk[O + 0x14] = F(R.uniform(-50, 50)); pk[O + 0x1C] = F(R.uniform(-50, 50))
    pk[O + 0x28] = F(air); pk[O + 0x3C] = F(spd); pk[O + 0x40] = F(R.uniform(0, 360))
    pk[O + 0x74] = R.randint(0, 0xFFFF); pk[O + 0x84] = anim << 16
    pk[O + 0xB8] = F(R.choice([0.0, 2.0, -1.0]))
    pk[O + 0x14C] = F(R.choice([1.0, 1.0, 0.8])); pk[O + 0x150] = F(R.choice([1.0, 1.2]))
    pk[O + 0x1D4] = JM; pk[O + 0x2FC] = (1 << 16) if reset == 'obj' else 0
    pk[O + 0x318] = CAM if cam else 0; pk[O + 0x31C] = 0x80490000
    pk[0x80490078] = b78 << 24; pk[0x8049011C] = REC
    pk[0x800C4420] = (1 << 25) if reset == 'bit' else 0          # bit 1 << arg0 of the u8 D_800C4000
    pk[0x800DC424] = 1 if reset == 'glob' else 0
    pk[0x800BEEE0] = (1 << 24) if pause == 'ac0' else 0
    pk[0x800BEE2C] = (1 << 24) if pause == 'e2c' else 0
    pk[0x800BEE04] = step
    pk[0x800C3A08] = fe << 8; pk[0x800C40BC] = d40bd << 16
    if cam:
        pk[CAM + 0x2C] = 0x100 if cam != 'mode' else 0x80
        pk[CAM + 0x388] = F(-10.0 if cam != 'low' else -20.0)
        for o in (0x2F8, 0x300, 0x74C, 0x754): pk[CAM + o] = F(R.uniform(-100, 100))
    for j in [0, 24, 25, 26, 27]:
        k = 0 if j == 0 else j - 23
        for c, v in enumerate([R.uniform(-3, 3), 50 - 8 * k + R.uniform(-2, 2), -12 * k + R.uniform(-3, 3)]):
            pk[JM + j * 0x40 + 0x30 + 4 * c] = F(v)
    for k in range(5):
        for c, v in enumerate([R.uniform(-15, 15), 40 - 6 * k + R.uniform(-10, 10), -40 * k + R.uniform(-15, 15)]):
            pk[REC + 12 * k + 4 * c] = F(v)
    pk[REC + 0x3C] = F(R.choice([0.0, 100.0, 355.0])); pk[REC + 0x40] = F(R.choice([0.0, 20.0, 355.0, -358.0]))
    pk[REC + 0x44] = F(R.choice([5.0, -20.0, 30.0])); pk[REC + 0x48] = F(R.choice([10.0, 100.0]))
    pk[REC + 0x4C] = (timer & 0xFFFF) << 16 | fade << 8
    poke = ','.join('%08X=%08X' % kv for kv in sorted(pk.items()))
    ret = '1503BC4C=%X' % mode
    acos = ';'.join('%08X' % F(R.choice([0.2, 0.5, 1.0, 1.4, 0.05])) for _ in range(4))
    retf = ('15048050=%08X;%08X;%08X;%08X;%08X,15047EF0=%08X,15048650=%s,15048790=%08X,15048D60=%08X'
            % tuple([F(R.uniform(-1, 1)) for _ in range(5)] + [F(R.uniform(-1, 1)), acos, F(R.uniform(-3, 3)),
                                                              F(R.choice([0.2, 8.0, -10.0, 40.0, -89.0, 120.0]))]))
    lines.append('%s ! 0=00000001 ! %s ! %s ! %s' % (n, poke, ret, retf))
n = 0
for mode in (0, 1, 2):
    for reset in ('none', 'bit', 'glob', 'obj'):
        for fade in (0, 1, 10):
            if mode != 0 and fade == 1: continue
            setup('m%d_%s_f%d_%d' % (mode, reset, fade, n), mode, reset, R.choice(['no', 'no', 'ac0']), 0, 0, 0.0,
                  R.choice([0.0, 10.0]), None, 0, R.choice([0, 3]), fade, R.choice([1, 2]), 0, 0); n += 1
for i in range(110):
    anim = R.choice([0, 0, 0x24, 0x22, 0xD1, 0x1B, 0x18B, 0x122, 0x12A, 0x5])
    setup('r%03d_a%X' % (i, anim), R.choice([1, 1, 2]), R.choice(['none'] * 4 + ['bit', 'obj']),
          R.choice(['no'] * 4 + ['ac0', 'e2c']), R.choice([0, 0, 0x80, 0xB0, 0x12]), anim,
          R.choice([0.0, 0.0, 0.2, 1.0, 5.0]), R.choice([0.0, 0.0, -1.0, 10.0, 25.0, 45.0, 80.0]),
          R.choice([None, None, 'close', 'close', 'low', 'mode']), R.choice([0, 0x3B]),
          R.choice([0, 0, 1, 3, 40, 0x8001 - 0x10000 & 0xFFFF]), R.choice([0, 10]), R.choice([1, 2]),
          R.choice([0, 1]), R.choice([0, 50, 200]))
print('\n'.join(lines))
