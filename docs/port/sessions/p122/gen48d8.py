#!/usr/bin/env python3
"""P122: difftest setups for func_151848D8 (shadow_light_projection). EU addresses. Fields:
name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW  (knobs.sh). usage: gen48d8.py N SEED > setups.txt"""
import random, struct, sys

def f(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
def w(x): return '%08X' % (x & 0xFFFFFFFF)

N, seed = int(sys.argv[1]), int(sys.argv[2])
rng = random.Random(seed)
REC, HEAD, LBUF = 0x800CC6F0, 0x800DD1A8, 0x80400000
for n in range(N):
    o = rng.choice([0, 1, 3])
    slot = rng.choice([0, 1, 2, 7])
    base = REC + o * 0x32C
    pos = [rng.choice([0.0, 120.5, -300.0, 1000.0]) for _ in range(3)]
    sx, sy, sz = [rng.choice([10.0, 25.0, 0.5]) for _ in range(3)]
    prev = rng.choice([0.0, 0.0, 0.0, 150.0, 400.0])
    pokes = {base + 0x14: f(pos[0]), base + 0x18: f(pos[1]), base + 0x1C: f(pos[2]),
             base + 0xCC: w((rng.choice([0, -5, -10, -11, -30, -200]) << 16) | 0x1234),
             base + 0x1DC: w(rng.choice([0, 0x40, 0x80, 0xFF, 0x86, 0x86]) << 16)}
    nolights = rng.random() < 0.2
    pokes[0x800DE464] = w(1 if nolights else 0)
    nl = rng.choice([0, 1, 2, 3])
    rets = []
    pokes[HEAD] = w(LBUF if nl else 0)
    for i in range(nl):
        e = LBUF + 0x40 * i
        off = 1 if rng.random() < 0.2 else 0
        hid = 1 if rng.random() < 0.2 else 0
        x, y, z = [rng.choice([0, 50, -400, 1500, 3000]) for _ in range(3)]
        pokes[e] = w(e + 0x40 if i + 1 < nl else 0)
        pokes[e + 4] = w(off << 24); pokes[e + 8] = w(hid << 16)
        pokes[e + 12] = w(x & 0xFFFF); pokes[e + 16] = w(((y & 0xFFFF) << 16) | (z & 0xFFFF))
        if not off and not hid and not nolights: rets.append(rng.choice([100, 300, 400, 4999, 5000, 7000]))
    rets.append(rng.choice([150, 250, 800]))   # the min-height re-measure
    defy = rng.choice([0.0, -5.0, 600.0, 300.0])
    pokes[0x800DE440] = f(rng.choice([100.0, -50.0])); pokes[0x800DE444] = f(defy); pokes[0x800DE448] = f(-200.0)
    pokes[0x800DE46C] = f(rng.choice([1.0, 1.0, 0.5, 2.0]))
    pokes[0x800DC424] = w(rng.choice([0, 0, 1]))
    pokes[0x800DE468] = w(rng.choice([0, 1, 2, 3]))
    for k in range(3): pokes[0x800DE3E0 + slot * 12 + 4 * k] = f(rng.choice([0.0, 200.0, -100.0, 900.0]))
    pokes[0x800DE470] = w(rng.choice([0, 1]) << 24)
    pokes[0x800DE458] = f(rng.choice([400.0, 1000.0]))
    pokes[0x800DF510] = w(rng.choice([0, 1]) << 16)
    pokes[0x800BEDE0] = w(rng.choice([0, 1]) << 24)
    length = rng.choice([100.0, 150.0, 500.0, 3000.0, 6000.0, 4500.0, 4500.0])
    # corners: x / y / z outputs of func_150A7E40 per call
    zs = [rng.choice([-50.0, -200.0, -0.5, 0.0, -3.0, 5.0]) for _ in range(8)]
    if rng.random() < 0.7: zs = [rng.choice([-50.0, -200.0, -3.0, -1.5]) for _ in range(8)]
    if rng.random() < 0.3: zs = [rng.choice([-1.5, -1.2, -0.5]) for _ in range(8)]
    if rng.random() < 0.3: zs[rng.randrange(8)] = 0.0
    xs = [rng.choice([1.0, -2.0, 0.5, -0.25, 0.001, 10.0]) for _ in range(8)]
    ys = [rng.choice([1.0, -2.0, 0.5, -0.25, 0.001, 10.0]) for _ in range(8)]
    if rng.random() < 0.15: xs = [0.0001] * 8
    elif rng.random() < 0.15: ys = [0.0001] * 8
    if rng.random() < 0.3: ys = [rng.choice([1.5, -1.8, 0.5]) for _ in range(8)]
    outw = '150A7E40=4:%s/5:%s/6:%s' % (';'.join(map(f, xs)), ';'.join(map(f, ys)), ';'.join(map(f, zs)))
    big = rng.random() < 0.35
    if big: outw += ',150A7F28=2:%s;3F800000' % rng.choice(['47800000', 'C7800000', '46FFFE00', '46F00000', '46F00000'])
    persp = [rng.choice([1.0, -2.0, 0.5, 100.0, -300.0, 0.0]) for _ in range(16)]
    outa = '150481F0=0:%s' % ';'.join(map(f, persp))
    # P122b: func_15048F90 (dir = light - pos) is a stub: give dir explicitly (else stack garbage / zeros)
    dvec = [rng.choice([30.0, -80.0, 5.0, 150.0, -2.0]), rng.choice([3.0, 50.0, -10.0, 400.0, 15.0, 10.5, 10.5]), rng.choice([60.0, -25.0, 1.0])]
    outa += ',15049280=2:%s' % ';'.join(map(f, dvec))
    retf = '150ADE10=%s,15048790=%s;%s' % (f(length), f(rng.choice([0.5, 0.3, 1.2])), f(rng.choice([0.5, 0.3, 1.2])))
    arg = '0=%X,1=%X,2=%s,3=%s,4=%s,5=%s' % (o, slot, f(sx), f(sy), f(sz), f(prev))
    print('s%d ! %s ! %s ! 150ADE80=%s ! %s ! %s ! %s ! ' % (n, arg, ','.join('%X=%s' % kv for kv in sorted(pokes.items())),
          ';'.join('%X' % r for r in rets), retf, outa, outw))
