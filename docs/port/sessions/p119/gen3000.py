#!/usr/bin/env python3
# P119: setups for func_15113000 (world_records_build_visible). usage: gen3000.py N SEED > 3000.txt
import random, struct, sys
n, seed = int(sys.argv[1]), int(sys.argv[2]); R = random.Random(seed)
def f(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
for s in range(n):
    nrec = R.randint(1, 6); pk = {}; np = 2 if s % 3 == 2 else 1
    if np == 2: pk[0x80083330] = '00000001'; pk[0x800DC304] = '80470400'; pk[0x804803D4 + 0x9A0] = '80490000'
    pk[0x800BEA48] = '80400000'; pk[0x800DC320] = '%08X' % nrec; pk[0x800DC324] = '80450000'
    pk[0x800C3A08] = '0000%02X00' % R.choice([0, 1, 1, 2]); pk[0x800C3A7C] = '%02X000000' % R.choice([0, 1])
    pk[0x800DC420] = '80480000'; pk[0x804803D4] = '80490000'; pk[0x80490194] = '000000%02X' % R.choice([0, 0, 0, 1])
    pk[0x800D9F3C] = f(R.choice([8000.0, 3000.0])); pk[0x800DC300] = '80470000'; pk[0x800DC318] = '00000000'
    pk[0x800BEE04] = '%08X' % R.choice([1, 3, 30])
    i = 0; depths = []
    while i < nrec:
        g = R.choice([0, 0, 1, 2, 3])
        for k in range(i, i + g + 1):
            a = 0x80450000 + k * 0xA0
            pk[a + 0x10] = '%04X%04X' % (R.randint(0, 0xFFFF), R.randint(0, 0xFFFF)); pk[a + 0x14] = '%04X0000' % R.randint(0, 0xFFFF)
            pk[a + 0x18] = f(R.choice([0.0, 12.5, -40.0])); pk[a + 0x4C] = '000000%02X' % R.choice([1, 1, 1, 0, 3])
            pk[a + 0x50] = '%04X%04X' % (R.randint(0, 0xFFFF), R.randint(0, 0xFFFF))
            pk[a + 0x6C] = '%04X%02X%02X' % (R.choice([0, 0x100, 0x101]), R.choice([0, 0, 0, 1, 2]), R.choice([0, 1, 0xFF, 0x0E]))
            pk[a + 0x70] = '%02X000000' % (((g - (k - i)) << 4 if k == i else R.randint(0, 3) << 4) | R.choice([0, 0, 0, 8]))
            near = R.choice([0, 0, 500, 2000]); far = R.choice([0, 1, 1500, 6000])
            pk[a + 0x88] = '%04X%02X%02X' % (near, R.choice([1, 1, 1, 0]), R.choice([0, 0x10, 0x80, 0xF8, 0xFF]))
            pk[a + 0x90] = '%04X0000' % far; pk[a + 0x8C] = '%02X000000' % R.choice([0, 0x10, 0xFF])
            depths.append(R.choice([1300, 1500, 5800, 6000, 7800, 8000, 2800, 3000, 0, 100, -300, 900, 1400, 1450, 1499, 1500, 1501, 2500, 5900, 5999, 7000, 7900, 8001, -7950, 30000, 39900, 40001]))
        i += g + 1
    ret = '15085E1C=%s,150A6840=%s,15022BB0=%s,1503FAF0=%s' % (
        ';'.join(R.choice(['1', '1', '1', '0'] if s % 2 else ['1']) for _ in range(np)), ';'.join('%X' % (d & 0xFFFFFFFF) for d in depths * np),
        ';'.join(R.choice('01') for _ in range(np * (2 * nrec + 2))), ';'.join(R.choice('001') for _ in range(np * (nrec + 1))))
    print('s3000_%d ! 0=0 ! %s ! %s !  !  !  ! ' % (s, ','.join('%08X=%s' % kv for kv in sorted(pk.items())), ret))
