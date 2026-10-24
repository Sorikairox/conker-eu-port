#!/usr/bin/env python3
# P206: setups for func_150F8EAC fire_burn_update (knobs.sh: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW).
# EU: D_800CC2D0 -> 800CC6F0 (stride 0x32C), D_800BE9E4 -> 800BEE04, D_800BE9A4 -> 800BEDC4. Jal keys: rng 150ADF00,
# randf 150ADF48, func_15143874 -> 15143DE4, func_15143794 -> 15143D04, func_10010F88 -> 10011278, func_151DB5D0 ->
# 151DBB80.
import struct
def fh(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
OBJ, A0, PARTS = 0x800CC6F0, 0x80410000, 0x80420000

def setup(name, match=(3, 7), extra=(), flags=1, timer=5, stage=2, crackle=2, accs=(1.5, 2.5, 3.5, 1.2),
          step=3, rate=1.0, rng='5;77;123;9;200;31;1;2;3;FFFFFFF0;64;7;8;9;A;B;C;D;E;F;10',
          randf='3F000000;3E800000;3F400000;0;3F7FFFFF', a1=5, ac=2):
    p = {}
    for i in range(25):
        b = OBJ + i * 0x32C
        idv, model, lit = 0, 0, 0
        if i in match: idv, model, lit = 0x98, 0x1EB, 0
        for (j, v, m, l) in extra:
            if j == i: idv, model, lit = v, m, l
        p[b + 4] = (idv << 24) | 0x00010203
        p[b + 0x84] = (model << 16) | 0x1234
        p[b + 0x220] = 0x11000022 | (lit << 8)
    p[A0] = (a1 & 0xFF) << 16
    p[A0 + 0xC] = (ac & 0xFF) << 24
    p[A0 + 0x2C] = ((flags & 0xFF) << 16) | (timer & 0xFFFF)
    p[A0 + 0x30] = (stage & 0xFF) << 24
    for k in range(8):
        p[A0 + 0x34 + 4 * k] = PARTS + k * 0x100
        p[PARTS + k * 0x100 + 0x10] = ((100 + k) << 16) | ((-100 - k) & 0xFFFF)
        p[PARTS + k * 0x100 + 0x14] = (500 + k) << 16
        p[PARTS + k * 0x100 + 0x6C] = 0x00005500
    for k, a in enumerate(accs):
        p[A0 + 0x54 + 4 * k] = int(fh(a), 16)
    p[A0 + 0x64] = (crackle & 0xFFFF) << 16
    p[A0 + 0x68], p[A0 + 0x6C], p[A0 + 0x70] = int(fh(100.0), 16), int(fh(-200.0), 16), int(fh(50.0), 16)
    p[0x800BEE04] = step
    p[0x800BEDC4] = int(fh(rate), 16)
    poke = ','.join('%08X=%08X' % (a, v) for a, v in sorted(p.items()))
    outa = '15143D04=3:3F800000;C0000000;40400000'
    outw = '15143DE4=2:42200000;C1200000;41000000/3:41A00000;C2480000;3F000000'
    print('%s ! 0=%X ! %s ! 150ADF00=%s ! 150ADF48=%s ! %s ! %s' % (name, A0, poke, rng, randf, outa, outw))

setup('all')
setup('none', match=())
setup('excluded', match=(), extra=((5, 0x98, 0x1EB, 1), (6, 0x98, 0x1EA, 0), (8, 0x97, 0x1EB, 0)))
setup('one', match=(24,), extra=((5, 0x98, 0x1EB, 1),))
setup('stage7', stage=7)
setup('stage6', stage=6, timer=-3)
setup('stage0', stage=0, flags=0)
setup('timer_zero', timer=6, crackle=6)
setup('timer_big', timer=0x7000, crackle=0x7000, accs=(0.5, 0.5, 0.5, 0.5))
setup('mirror0', flags=0xFE)
setup('acc_one', rate=0.0, accs=(1.0, 1.0, 1.0, 1.0))
setup('acc_loops', match=(0, 1, 2), rate=2.0, accs=(4.5, 3.2, 2.7, 5.9), step=1)
setup('rng_big', rng='FFFFFFFF;FFFFFFFE;80000000;7FFFFFFF;FFFFFF00;12345678;9ABCDEF0;3;FFFFFFF7;FFFFFF86')
setup('rng_zero', rng='0', randf='0')
setup('randf_one', randf='3F7FFFFF;3F800000')
setup('neg_rate', rate=-1.0, accs=(1.5, 1.5, 1.5, 1.5))
setup('step_big', step=0x10000, timer=0x7FFF, crackle=0x7FFF)
setup('bytes', a1=0xFF, ac=0x80)
# accumulators from 0 (a 1-ulp difference of the rate constants shows in the stored accumulator), long random
# sequences (alternating flip bits)
setup('acc_zero', accs=(0.0, 0.0, 0.0, 0.0), randf='0', rate=0.5)
x = 12345
rs, fs = [], []
for _ in range(400):
    x = (x * 1103515245 + 12345) & 0xFFFFFFFF
    rs.append('%X' % (((x >> 16) | (x << 16)) & 0xFFFFFFFF))  # rotated: the LCG's low bit alternates
    fs.append(fh(((x >> 8) & 0xFFFF) / 65536.0))
setup('rand_long', rng=';'.join(rs), randf=';'.join(fs[:150]), accs=(2.5, 3.5, 3.5, 2.5))
setup('acc_zero2', accs=(0.0, 0.0, 0.0, 0.0), randf='3F7FFFFF', rate=0.5)
