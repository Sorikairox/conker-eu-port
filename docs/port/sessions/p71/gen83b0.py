#!/usr/bin/env python3
"""P71: setups for func_150383B0 (look target search), p71/knobs.sh. 25 objects at EU 0x800CC6F0 (0x32C each);
D_800C35EA / D_800C35EB = EU 0x800C3A0A / B; func_15037988 (EU 0x15037988) answers by a RET sequence."""
import random, struct
r = random.Random(0x83B0)
fb = lambda f: '%08X' % struct.unpack('>I', struct.pack('>f', f))[0]
KINDS = [5, 0xAD, 0x2D, 0x2C, 0x10, 0x10, 0x22, 0x40, 0xFF, 7]
for i in range(60):
    sid = r.randint(0, 24); B = lambda k: 0x800CC6F0 + 0x32C * k
    cut = i % 15 == 14
    p = ['800C3A08=0000%02X%02X' % ((1 if cut and i & 16 else 0), (1 if cut and not i & 16 else 0))]
    skind = r.choice(KINDS[:8]); prefer = r.choice(KINDS + [0x33])
    for k in range(25):
        kind = skind if k == sid else r.choice(KINDS)
        act = 0 if r.random() < 0.15 else r.randint(1, 5)
        p.append('%08X=%08X' % (B(k), act))
        p.append('%08X=%08X' % (B(k) + 4, kind << 24 | r.getrandbits(24)))
        link = r.choice([0, 0, 0, sid + 1, r.randint(1, 25)])
        p.append('%08X=%04X%02X%02X' % (B(k) + 0x64, r.getrandbits(16), link, r.getrandbits(8)))
        p.append('%08X=%06X%02X' % (B(k) + 0x124, r.getrandbits(24), r.choice([0xFF, 0, 3])))
        p += ['%08X=%s' % (B(k) + o, fb(r.uniform(-300, 300))) for o in (0x14, 0x18, 0x1C)]
        p.append('%08X=%08X' % (B(k) + 0x1A4, r.getrandbits(32)))
        p.append('%08X=%08X' % (B(k) + 0x1A8, r.getrandbits(32)))
        p.append('%08X=%08X' % (B(k) + 0x138, r.getrandbits(32)))
    p.append('%08X=%02X%06X' % (B(sid) + 0x23C, r.getrandbits(8), r.randint(0, 255) << 16 | r.getrandbits(16)))
    p.append('%08X=0000%02X%02X' % (B(sid) + 0x220, r.randint(0, 24), r.choice([1, 0xC, 0, 2])))
    p.append('%08X=%04X%04X' % (B(sid) + 0x2F8, r.choice([0, 4, 5, 3]) | r.getrandbits(13) << 3, r.getrandbits(16)))
    p.append('804B0000=%s' % fb(r.choice([1e12, 50000.0, 3000.0, 0.0])))
    ret = ';'.join(r.choice('001') for _ in range(12))
    a = '0=804C0000,1=%X,2=%X,3=%X,4=%s,5=%X,6=804B0000,7=%X,8=%X,9=%X,10=%X' % (r.randint(0, 9), r.randint(0, 9), sid,
        fb(r.uniform(1, 90)), prefer, r.randint(0, 1), r.randint(0, 1), 1 if i % 4 == 3 else 0, r.randint(0, 3))
    print('k%02d_s%d ! %s ! %s ! 15037988=%s ! ! ! ! ' % (i, sid, a, ','.join(p), ret))
