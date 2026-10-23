# P115: setups for func_15113798 (world_records_update_matrices). usage: gen3798.py N > 3798.txt
# EU: D_80082FA0 80083330, D_800BE9C0 800BEDE0, D_800DBEF4 800DC324, D_800CC2D0 800CC6F0 (0x32C each),
# D_800895E0 / D_800895F0 / D_800DC318 / D_800DC338 same. jal key func_150859AC = 15085E1C.
import sys, random, struct
random.seed(3798)
F = lambda f: '%08X' % struct.unpack('>I', struct.pack('>f', f))[0]
for i in range(int(sys.argv[1])):
    pk = {}
    ng = random.choice([0, 1, 2]); pk[0x80083330] = ng if random.random() > 0.05 else 0xFFFFFFFF
    pl = random.randrange(2); pk[0x800BEDE0] = pl << 24
    pk[0x800DC324] = 0x80470000
    pk[0x800895F0] = 0x80448000; pk[0x800895F4] = 0x80448010
    pk[0x80448000] = 0x80480000; pk[0x80448010] = 0x80490000
    cnts = []
    for g in range(3):
        c = random.randrange(0, 5); cnts.append(c)
        pk[0x800895E0 + 4 * g] = 0x80449000 + 0x100 * g
        pk[0x80449000 + 0x100 * g] = 0x8044A000 + 0x100 * g
        for k in range(c):
            pk[0x8044A000 + 0x100 * g + 4 * k] = (random.randrange(8) << 16) | random.randrange(0x10000)
    pk[0x800DC318] = (cnts[0] << 16) | cnts[1]; pk[0x800DC31C] = cnts[2] << 16
    for r in range(8):
        a = 0x80470000 + 0xA0 * r
        kind = random.choice([0, 1, 2, 3, 4, 0x65, 0x66, 0x70, 0x7C, 0x7D, 0x64, 0x80, 0xFF])
        pk[a + 0x4C] = random.randrange(0x10000) << 16 | kind << 8 | random.randrange(256)
        pk[a + 0x70] = random.choice([0, 0, 0, 1, 3, 2]) << 24 | random.randrange(1 << 24)
        for o in (0x2C, 0x30, 0x34): pk[a + o] = random.randrange(0x10000)
        for o in (0x10, 0x14): pk[a + o] = random.randrange(1 << 32)
    for k in (1, 2, 0xC, 0x18):
        o = 0x800CC6F0 + 0x32C * k
        pk[o + 0x1D4] = random.choice([0, 0x8044C000])
        pk[o + 0x90] = random.randrange(-300, 300) << 16 & 0xFFFFFFFF | random.randrange(0x10000)
        for f in (0x14, 0x18, 0x1C): pk[o + f] = F(random.uniform(-3000, 3000))
    for f in (0x30, 0x34, 0x38): pk[0x8044C000 + f] = F(random.uniform(-3000, 3000))
    for k in range(32): pk[0x800DC338 + 4 * k] = F(random.uniform(-2, 2))
    r = ','.join(random.choice(['0', '1', '1']) for _ in range(4))
    poke = ','.join('%08X=%s' % (k, v if isinstance(v, str) else '%08X' % v) for k, v in sorted(pk.items()))
    print('s3798_%d !  ! %s ! 15085E1C=%s !  !  !  ! ' % (i, poke, r.replace(',', ';')))
