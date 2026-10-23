# P115: setups for func_15129220 (camera_process_events). usage: gen9220.py N > 9220.txt
# EU addresses: D_800DBFF0 800DC420, D_800DC440 800DC440, D_800BE728 800BEB48, D_800BEB30 800BEB30,
# D_800DBFF4 800DC424, D_800BEAC0 800BEEE0, D_800C35EA 800C3A0A, D_800D2DB0 800D31D0, D_800D34B8 800D34B8.
# jal keys: func_1512DC20 1512DC20, func_1512DB74 1512DB74, func_1509BE40 1509C250, func_15048A70 15048D60,
# sinf 15048050, cosf 15047EF0.
import sys, random, struct
random.seed(1152)
F = lambda f: '%08X' % struct.unpack('>I', struct.pack('>f', f))[0]
C = 0x80430000
for i in range(int(sys.argv[1])):
    pk = {}; ret = {}; retf = {}
    pl = random.randrange(4)
    pk[C + 0x23C] = (random.randrange(2) << 24) | (pl << 16) | (random.randrange(0x30) << 8) | random.randrange(256)
    pk[C + 0x3D4] = 0x80438000; pk[C + 0x3D0] = 0x80439000; pk[C + 0x36C] = 0x8043A000
    pk[0x80438078] = random.choice([0, 0, 0xC, 0x1B, 5]) << 24
    pk[0x80438194] = random.randrange(1 << 32); pk[0x80438198] = random.randrange(1 << 32)
    pk[0x80439040] = F(random.uniform(-180, 180)); pk[0x80439084] = random.choice([0x76, 0x75, 0]) << 16
    pk[0x8043A000] = random.choice([0, 0x10, 0xFFEF]) << 16
    pk[C + 0x2C] = random.choice([0x40000, 0x40000, 0, 1, 0x40001])
    pk[C + 0x5F0] = random.randrange(8)
    pk[C + 0x834] = random.choice([0, 0, 5]) << 16
    pk[C + 0x84C] = random.randrange(2) << 24
    pk[C + 0x734] = random.choice([0, 0, 0x1003, 0x2007]); pk[C + 0x738] = random.randrange(2)
    for o in (0x3A4, 0x774, 0x37C, 0x2BC, 0x2C0, 0x2C4, 0x2F8, 0x2FC, 0x300, 0x19C, 0x1A0):
        pk[C + o] = F(random.uniform(-500, 500))
    pk[0x800DC420] = 0x80450000; pk[0x800DC440] = 0x80460000; pk[0x800BEB48] = 0x8043B000
    pk[0x800DC424] = random.randrange(2) << 24; pk[0x800BEEE0] = random.randrange(2) << 24
    pk[0x800C3A08] = random.randrange(3) << 8; pk[0x800C3A90] = random.randrange(2) << 8
    pk[0x800D31D0] = random.choice([F(999.0), F(random.uniform(-180, 180))])
    pk[0x800898C0] = random.choice([0, 0, 2])
    for k in range(4):
        pk[0x800898C4 + 4 * k] = random.choice([0, 3]); pk[0x800898D4 + 4 * k] = random.choice([0, 0, 1])
    pk[0x800D34B8] = 0x8043C000
    n = random.choice([1, 1, 2, 3])
    evs = []
    for k in range(n):
        t = random.choice([1, 5, 6, 6, 7, 7, 8, 9, 10, 2, 11, 0])
        ea = 0x80440000 + 0x40 * k; da = 0x80441000 + 0x100 * k
        pk[ea] = t; pk[ea + 4] = da if t not in (5, 6) else random.randrange(3)
        if t in (7,): pk[da] = random.choice([0, 2, 1, 3])
        elif t in (10,): pk[da + 0xC] = random.choice([F(999.0), F(random.uniform(-90, 90))])
        else: pk[da] = random.randrange(1 << 32)
        if t == 7: pk[da + 4] = random.randrange(4)
        for o in range(8, 0x38, 4):
            if da + o not in pk: pk[da + o] = F(random.choice([random.uniform(-400, 400), random.uniform(170, 900)]))
        if t == 10: pk[da + 0x10] = random.randrange(1 << 32)
        evs.append('%X' % ea)
    pre = [] if pk[C + 0x734] == 0 else [random.choice(['0', '1'])]
    ret['1512DC20'] = ';'.join(pre + ['0', '0'] + ['0'] * (n - 1) + ['1'])
    ret['1512DB74'] = ';'.join(evs)
    ret['1509C250'] = random.choice(['0', '1'])
    retf['15048D60'] = F(random.uniform(-90, 90)); retf['15048050'] = F(random.uniform(-1, 1)); retf['15047EF0'] = F(random.uniform(-1, 1))
    poke = ','.join('%08X=%s' % (k, v if isinstance(v, str) else '%08X' % v) for k, v in sorted(pk.items()))
    print('s9220_%d ! 0=%X ! %s ! %s ! %s !  !  ! ' % (i, C, poke, ','.join('%s=%s' % kv for kv in ret.items()), ','.join('%s=%s' % kv for kv in retf.items())))
