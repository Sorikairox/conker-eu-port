# P108 setups for the trail particle functions. usage: gentrail.py {8e34|9114|9350|85ac} N
# obj 80430000, rec 80430200, pts 80430400 (0x14 each), camera 80430600, vertex buffer 80438000.
import random, struct, sys
mode, N = sys.argv[1], int(sys.argv[2])
random.seed(hash(mode) & 0xFFFF if False else {'8e34': 1, '9114': 2, '9350': 3, '85ac': 4}[mode])
O, R, P, C, V = 0x80430000, 0x80430200, 0x80430400, 0x80430600, 0x80438000
fb = lambda f: struct.unpack('>I', struct.pack('>f', f))[0]
for n in range(N):
    cap = random.choice((3, 4, 5, 8))
    cnt = random.choice(list(range(0, cap)) + [cap - 1, cap - 1])
    if mode == '9350' and random.random() < 0.3: cnt = random.choice((0, 1, 2, 3))
    tail = random.randrange(cap)
    head = (tail + cnt) % cap
    if random.random() < 0.1: head = random.randrange(cap)  # inconsistent ring
    pk = {}
    pk[O + 0x10] = fb(random.uniform(-900, 900)); pk[O + 0x14] = fb(random.uniform(-900, 900)); pk[O + 0x18] = fb(random.uniform(-900, 900))
    pk[O + 0x1C] = 0x00100035
    pk[O + 0x24] = (0xFF << 24) | (cap << 16)
    pk[O + 0x2C] = (cnt << 24) | (tail << 16) | (head << 8) | 1
    pk[O + 0x60] = fb(random.uniform(-500, 500)); pk[O + 0x64] = fb(1.5)
    pk[O + 0x7C] = random.choice((0, 3, 1)) << 16
    pk[O + 0x94] = P; pk[O + 0x98] = R
    flags = random.choice((0, 0x20, 0x01, 0x10, 0x17, 0x21, 0x48, 0x80, 0xA3, 0x07, 0x37, 0x04, 0x14))
    pk[R + 0x00] = fb(random.choice((0.0, 4.0, 12.5)))
    for k in (4, 8, 0xC, 0x10): pk[R + k] = fb(random.uniform(-20, 20))
    pk[R + 0x18] = (flags << 24) | (random.randrange(4) << 16) | (random.randrange(256) << 8) | random.randrange(256)
    pk[R + 0x20] = (1 << 24) | (random.choice((0, 2, 7)) << 8) | random.choice((0, 1, 4))  # +0x23 hit handler
    pk[R + 0x24] = random.choice((0, 1, 4)) << 24
    for k in range(0x28, 0x44, 4): pk[R + k] = random.getrandbits(32) & 0x0FFF0FFF
    pk[R + 0x34] = random.randrange(4)
    pk[R + 0x38] = random.randrange(256) << 16  # +0x3B combine
    pk[R + 0x44] = (random.randrange(-3, 4) & 0xFF) << 24 | (random.randrange(-3, 4) & 0xFF) << 16
    for i in range(cap):
        for k in range(4): pk[P + i * 0x14 + 4 * k] = fb(random.uniform(-800, 800) if k < 3 else random.uniform(-10, 10))
        pk[P + i * 0x14 + 0x10] = random.getrandbits(16) << 16
    if random.random() < 0.2:  # repeated point: zero normal
        for k in range(3): pk[P + ((head - 2) % cap) * 0x14 + 4 * k] = pk[P + ((head - 1) % cap) * 0x14 + 4 * k]
    pk[0x800BEDC4] = fb(random.choice((1.0, 0.5, 2.0)))  # D_800BE9A4 frame time (EU address)
    ret, outw = [], []
    if mode == '9114':
        ret.append('15046F70=%X' % random.choice((0, 1)))
        for i in range(cap):  # some trails moving down at the oldest point
            if random.random() < 0.5: pk[P + i * 0x14 + 0xC] = fb(-abs(random.uniform(1, 30)))
        if n % 5 == 4:  # the oldest point keeps its height: y == old y
            pk[R + 0x10] = 0; pk[P + tail * 0x14 + 0xC] = 0
    if mode == '85ac':
        for k in range(3): pk[C + 4 * k] = fb(random.uniform(-900, 900))
        pk[0x800BEDE0] = random.choice((0, 1)) << 24  # D_800BE9C0 (EU)
        pk[0x800DD5E0] = 0x1234
        ret += ['151450A4=%X' % C, '151435DC=%X' % random.choice((0x1234, 0x5678)), '150954E4=80440000', '151430EC=80440010',
                '15143180=80440020', '15143260=80440030', '1513FA54=80440040', '1514352C=80441000']
        outw.append('151D6310=3:%X' % random.choice((V, V, V, 0)))
        if n % 4 == 3:  # tiny segments: |normal| below 1
            x0, y0, z0 = (random.uniform(-50, 50) for _ in range(3))
            for i in range(cap):
                for k, b in enumerate((x0, y0, z0)): pk[P + i * 0x14 + 4 * k] = fb(b + random.uniform(-0.01, 0.01))
            for k in range(3): pk[C + 4 * k] = fb(random.uniform(-2, 2))
    outb = ''
    if mode == '85ac':  # the colour out-params of func_151441A4 / func_151442FC (s16 each)
        outb = ','.join('%s=%s' % (a, '/'.join('%d:%02X;%02X' % (i, random.randrange(256), random.randrange(256)) for i in range(4)))
                        for a in ('15144714', '1514486C'))
    print('t%s_%d ! 0=%08X,1=80441000,2=%X ! %s ! %s !  !  ! %s ! %s' % (mode, n, O, random.choice((0, 3)),
          ','.join('%08X=%08X' % kv for kv in sorted(pk.items())), ','.join(ret), ','.join(outw), outb))
