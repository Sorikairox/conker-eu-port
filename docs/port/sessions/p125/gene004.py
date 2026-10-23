import random, struct
def f(x): return struct.unpack('>I', struct.pack('>f', x))[0]
random.seed(7)
L = []
for i in range(40):
    st = i % 2
    p = {0x80400110: 0x80410000, 0x80400120: (st << 24) | (random.choice([0, 0x40, 0xFF]) << 8),
         0x80400124: (random.choice([0, 1, 3]) << 24), 0x800BEDE0: random.choice([0, 1]) << 24,
         0x800BEE04: random.choice([1, 2, 30, 60])}
    ret = []; outa = []; retf = []
    ret.append('1510E908=%X' % (0 if i % 7 == 6 else 1))
    outa.append('1510E908=2:%08X/3:%08X' % (f(random.uniform(-0.5, 0.5)), f(random.uniform(-0.5, 0.5))))
    sn = random.uniform(-1, 1); cs = random.choice([-1, 1]) * (1 - sn * sn) ** 0.5
    retf.append('15048D30=%08X' % f(sn)); retf.append('15048CA0=%08X' % f(cs))
    y = random.choice([0.0, 50.0, 300.0, 900.0, -2000.0, -200.0]); fl = random.choice([0.0, -100.0, 20.0, -200.0])
    if st == 0:
        p[0x80410004] = random.choice([0x25, 0x10]) << 24
        p[0x80410014] = f(random.uniform(-500, 500)); p[0x80410018] = f(y); p[0x8041001C] = f(random.uniform(-500, 500))
        p[0x80410180] = f(fl); p[0x80410188] = 0x80420000
        p[0x80410160] = random.choice([0, 1, 20, 0xFFFF]) << 16; p[0x8041014C] = f(random.choice([0.5, 1.0, 3.0]))
        p[0x80410078] = random.choice([0, 0xE000, 0x1234, 0x8000])
    else:
        p[0x80410010] = ((random.randrange(-500, 500) & 0xFFFF) << 16) | (int(y) & 0xFFFF)
        p[0x80410014] = (random.randrange(-500, 500) & 0xFFFF) << 16
        p[0x8041006C] = random.choice([0, 0, 0, 1]) << 8
        p[0x80410094] = 0x80430000; p[0x80410070] = random.randrange(256) << 16
        p[0x8041004C] = random.choice([0, 1, 5]) << 16; p[0x8041002C] = f(random.choice([1.0, 2.5]))
        ret.append('150A44A4=%X' % random.choice([0, 1]))
        outa.append('150A44A4=4:%08X' % f(fl))
    L.append('e%d ! 0=80400000 ! %s ! %s ! %s ! %s ! ' % (i, ','.join('%08X=%08X' % kv for kv in p.items()), ','.join(ret), ';'.join([]) or ','.join(retf), ','.join(outa)))
open('e004.txt', 'w').write('\n'.join(L) + '\n')
