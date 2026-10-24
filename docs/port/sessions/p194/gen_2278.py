# P194: setups for func_15082278 (obj 0x80410000 or player 1 0x800CCA1C, hit 0x80420000, target 0x80430000,
# target controller 0x80438000, shooter controller 0x80418000). EU: D_800BE9F0 0x800BEE10, D_800BE616 0x800BEA36.
import sys, struct, random
random.seed(194)
def fb(x): return struct.unpack('>I', struct.pack('>f', x))[0]
def h(v): return '%08X' % (v & 0xFFFFFFFF)
R = []
def row(name, kind, typ, level, ttype, t1ca, inv, t2ec, tctrl, sub, dist, u5a, f18, b616, yaw, obj, octrl, ra):
    p = {}
    def b(a, v):  # byte poke merged into the word
        w = a & ~3; sh = (3 - (a & 3)) * 8
        p[w] = (p.get(w, 0) & ~(0xFF << sh)) | ((v & 0xFF) << sh)
    def hw(a, v):
        w = a & ~3; sh = (2 - (a & 2)) * 8
        p[w] = (p.get(w, 0) & ~(0xFFFF << sh)) | ((v & 0xFFFF) << sh)
    p[obj + 0x31C] = octrl; b(obj + 0x124, 2)
    if octrl: hw(octrl + 0x1AA, 7)
    H = 0x80420000
    p[H] = 0x80430000; p[H + 4] = fb(dist)
    for i, v in enumerate((100.5, -20.25, 300.0)): p[H + 8 + 4 * i] = fb(v)
    p[H + 0x18] = fb(f18)
    for i, v in enumerate((1.0, 2.0, 3.0)): p[H + 0x20 + 4 * i] = fb(v)
    for i, v in enumerate((0.6, -0.8, 0.25)): p[H + 0x38 + 4 * i] = fb(v)
    for i, v in enumerate((0.0, 1.0, 0.0)): p[H + 0x44 + 4 * i] = fb(v)
    hw(H + 0x56, 0x1234); b(H + 0x58, sub); b(H + 0x59, typ); b(H + 0x5A, u5a)
    T = 0x80430000
    b(T + 4, ttype); b(T + 0x104, inv & 1); b(T + 0x125, inv >> 1); b(T + 0x1CA, t1ca)
    p[T + 0x2EC] = t2ec; p[T + 0x31C] = tctrl; p[T + 0x14C] = fb(7.5); p[T + 0x150] = fb(-8.25)
    if tctrl: b(tctrl + 0x1AD, ra)
    p[0x800BEE10] = level; b(0x800BEA36, b616)
    pk = ','.join('%08X=%s' % (a, h(v)) for a, v in sorted(p.items()))
    R.append('%s ! 0=%08X,1=80420000,2=%X ! %s ! 150ADF00=5 ! ! ! 15145EE4=1:%08X/2:%08X !' % (name, obj, kind, pk, fb(yaw), fb(-12.5)))
kinds = [0, 2, 3, 5, 6, 7, 9, 10, 11, 12, 13, 14, 18]
n = 0
for kind in kinds:
    for typ in (0, 1, 4):
        for level in ((0, 0xE) if typ == 1 else (0,)):
            row('w_k%d_t%d_l%X' % (kind, typ, level), kind, typ, level, 0x10, 1, 0, 0, 0, 3, 500, 0, 0, 0, 45, 0x80410000, 0x80418000 if kind & 1 else 0, 0)
for i in range(260):
    kind = random.choice(kinds); typ = random.choice((2, 3, 3, 3))
    ttype = random.choice((0x94, 0x9F, 0xA0, 0x80, 0x10)); t1ca = random.choice((0, 1, 3))
    inv = random.choice((0, 0, 1, 2, 3)); t2ec = random.choice((0, 5)); tctrl = random.choice((0, 0x80438000))
    sub = random.choice((10, 10, 3)); dist = random.choice((500.0, 2000.0)); u5a = random.choice((0, 0, 1))
    f18 = random.choice((-30.0, -25.0, -10.0)); b616 = random.choice((0, 0, 1)); yaw = random.choice((45.0, 300.0, -100.0, 89.5, 90.0, 400000000.0))
    obj = random.choice((0x80410000, 0x800CCA1C)); octrl = random.choice((0, 0x80418000)); ra = random.choice((0, 1))
    level = random.choice((0, 0x2B))
    row('o%d_k%d_t%d' % (i, kind, typ), kind, typ, level, ttype, t1ca, inv, t2ec, tctrl, sub, dist, u5a, f18, b616, yaw, obj, octrl, ra)
open(sys.argv[1], 'w').write('\n'.join(R) + '\n'); print(len(R))
