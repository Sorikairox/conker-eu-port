# P129: setups for func_1509093C (knobs fields name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB).
# Air meter state at 0x800D2968 (= D_800D28E8 + 0x80), object 0 at 0x800CC6F0 (+0xAD in_water, +0xB2 unkB2),
# frames 0x800BEE04, D_800BE9C0 (frame buffer index) 0x800BEDE0.
import random, struct
r = random.Random(93); out = []
f2h = lambda f: '%08X' % struct.unpack('>I', struct.pack('>f', f))[0]
useds = [0x5A, 0x5B, 479, 480, 959, 960, 1199, 1200, 1201, 1439, 1440, 1441, 1442, 720, 900, 0xFFFF, 0x8000, 300]
for n in range(40):
    used = useds[n % len(useds)]; water = 0 if n % 17 == 5 else 1
    frames = r.choice([1, 1, 2, 3, 0, 5])
    load = (n % 4 == 0)
    count = r.choice([0, 1, 0x10, 0xCF, 0xD0, 0xDB, 0xDC, 0xE4, 0xFF])
    active = r.choice([0, 0xFF, 0xFF, 1])
    timer = r.choice([0, 0, 1, frames, frames + 1, 0x40, 0xFFFF])
    pk = ['800CC79C=00%02X0000' % water, '800CC7A0=0000%04X' % used, '800BEE04=%08X' % frames,
          '800BEDE0=%02X000000' % r.choice([0, 1]),
          '800D2968=%08X' % (0 if load else 0x80431234), '800D296C=80440000', '800D2970=80450000',
          '800D2974=80460000', '800D2978=80470000',
          '800D297C=' + f2h(r.choice([0.0, 0.3, 0.5, 0.99, 1.2, -0.1])),
          '800D2980=' + f2h(r.choice([0.01, -0.02, 0.2, -0.3])),
          '800D2984=' + f2h(r.uniform(0, 1)),
          '800D2988=' + f2h(r.choice([0.0, -10.0, -21.9, -22.0, -30.0])),
          '800D298C=' + f2h(r.choice([0.5, -1.0, 2.0])),
          '800D2990=' + f2h(r.choice([0.0, 0.05, 1.9, 2.1, -1.95, -2.5, -0.01])),
          '800D2994=' + f2h(r.choice([0.0, 0.1, -0.1, 0.01, -0.005, 0.3])),
          '800D29A0=%04X%02X%02X' % (timer, active, count)]
    ret = '10003E90=80480000;80490000,150ADF00=%08X' % r.randrange(1 << 32)
    d = 0x80440000
    outw = '15030100=1:%08X/3:%08X' % (d + 16 * count, d) if load else ''
    outb = '15030100=2:%02X' % (r.randrange(256)) if load else ''
    out.append('s%d ! ! %s ! %s ! ! ! %s ! %s' % (n, ','.join(pk), ret, outw, outb))
print('\n'.join(out))
