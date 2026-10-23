# P115: setups for func_15128D50 (camera_lean_from_heading). usage: gen8d50.py N > 8d50.txt
# D_800D2DB4 is EU 800D31D4 (first run poked the US address: fixed, setups regenerated).
import sys, random, struct
random.seed(115)
F = lambda f: '%08X' % struct.unpack('>I', struct.pack('>f', f))[0]
C = 0x80430000
for i in range(int(sys.argv[1])):
    pk = {}
    pk[0x800D31D4] = 0 if random.random() < 0.85 else 1
    mode = random.choice([0, 0, 3, 3, 1])
    pk[C + 0x73C] = (mode << 16) | random.randrange(0x10000)
    pk[C + 0x3D4] = 0x80438000; pk[0x80438120] = (0 if random.random() < 0.85 else 1) << 24
    pk[C + 0x3D0] = 0x80439000; pk[0x8043903C] = F(random.choice([0.0, 30.0, random.uniform(0, 60), random.uniform(-10, 40)]))
    pk[C + 0x134] = random.randrange(6)
    pk[C + 0x2C] = random.choice([0, 0x40, 0x100, 0x140, random.randrange(1 << 32)])
    pk[C + 0x23C] = (1 if random.random() < 0.25 else 0) << 24 | random.randrange(1 << 24)
    pk[C + 0x390] = F(random.choice([random.uniform(-400, 400), random.uniform(-200, 200), 90.0, -90.0, 180.0, -180.0, 0.0, 540.5, 270.0]))
    pk[C + 0x6C8] = random.choice([0, 1, 2])
    pk[C + 0x6FC] = random.choice([0xA, 0xE, 2, 7])
    for o in (0x3A8, 0x5E8, 0x65C, 0x660):
        pk[C + o] = F(random.uniform(-20, 20))
    pk[C + 0x7B4] = F(random.choice([1.0, 0.5, 2.0]))
    a1 = random.choice(['0', '80440000']); a2 = random.choice(['0', '80440010'])
    poke = ','.join('%08X=%s' % (k, v if isinstance(v, str) else '%08X' % v) for k, v in sorted(pk.items()))
    print('s8d50_%d ! 0=%X,1=%s,2=%s ! %s !  !  !  !  ! ' % (i, C, a1, a2, poke))
