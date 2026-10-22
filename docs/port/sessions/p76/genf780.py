#!/usr/bin/env python3
"""P76: knob setups for func_1502F780 (p76/knobs.sh). EU: D_800C6070 0x800C6490, D_800D19A0 0x800D1DC0,
D_800C6318 0x800C6318 (u16), D_800C5C08 0x800C6028. func_150A7E40 (jal 150A7E40) out x / y / z = stack args 4..6
(OUTW per call: old corners 0..2, then new corners 0..2). Args: 0 obj, 1 x*, 2 y*, 3 z*, 4 tri."""
import random, struct, sys
r = random.Random(0xF780)
def fw(x): return struct.unpack('>I', struct.pack('>f', x))[0]
N = int(sys.argv[1]) if len(sys.argv) > 1 else 60
for t in range(N):
    kind = r.choice([0, 3, 0x41, 0xBA]); tri = r.randint(0, 3)
    obj = 0x804A0000; px, py, pz = 0x804E0000, 0x804E0010, 0x804E0020
    p = ['%08X=%08X' % (obj + 4, kind << 24)]
    case = t % 6
    tris = 0 if case == 0 and t % 12 == 0 else 0x804B0000
    p.append('%08X=%08X' % (0x800C6490 + 4 * kind, tris))
    p.append('%08X=%08X' % (0x800D1DC0 + 4 * kind, 0x804C0000))
    offs = [r.randrange(0, 8) * 16 for _ in range(12)]
    for k in range(12):
        p.append('%08X=%08X' % (tris + 4 * k, offs[k]))
    for k in range(8):
        b = 0x804C0000 + 16 * k
        p += ['%08X=%04X%04X' % (b, r.randint(-500, 500) & 0xFFFF, r.randint(-500, 500) & 0xFFFF), '%08X=%04X0000' % (b + 4, r.randint(-500, 500) & 0xFFFF)]
    nr = r.choice([0, 1, 2, 3, 4]) if case == 1 else r.choice([3, 4, 4, 4])
    cw = 0x800C6318 + 2 * kind
    p.append('%08X=%08X' % (cw & ~3, (nr << 16) if (cw & 2) == 0 else nr))
    p.append('%08X=%08X' % (0x800C6028 + 4 * kind, 0x804D0000))
    # ranges cover vertices 0..7 in pieces; some may miss
    cuts = sorted(r.sample(range(1, 8), 3))
    rs = [(0, cuts[0]), (cuts[0], cuts[1]), (cuts[1], cuts[2]), (cuts[2], 8)]
    r.shuffle(rs)
    for k, (a, b) in enumerate(rs):
        cnt = b - a if not (case == 2 and k == 0) else 0
        q = 0x804D0000 + 12 * k
        p += ['%08X=%08X' % (q, 0x804C0000 + 16 * a), '%08X=%08X' % (q + 4, cnt), '%08X=%08X' % (q + 8, r.randint(0, 3))]
    p += ['%08X=%08X' % (obj + 0x1D4, 0 if case == 3 and (t // 6) % 2 else 0x804F0000), '%08X=%08X' % (obj + 0x1D8, 0 if case == 3 and not (t // 6) % 2 else 0x804F1000)]
    # corners
    A = [r.uniform(-100, 100) for _ in range(3)]
    e1 = [r.uniform(-20, 20), r.uniform(-5, 5), r.choice([0.0, r.uniform(-20, 20)])]
    e2 = [r.choice([0.0, r.uniform(-20, 20)]), r.uniform(-5, 5), r.uniform(-20, 20) if case != 4 else 0.0]
    if case == 5 and t % 4 == 1: e1[0] = e2[0] = 0.0  # den == 0
    old = [A, [A[i] + e1[i] for i in range(3)], [A[i] + e2[i] for i in range(3)]]
    mv = [r.uniform(-3, 3) for _ in range(3)]
    new = [[c[i] + mv[i] + r.uniform(-1, 1) for i in range(3)] for c in old]
    cs = old + new
    u, v = r.choice([r.uniform(0, 1)] * 4 + [-0.1, 1.1, 0.0, 1.0]), r.choice([r.uniform(0, 1)] * 4 + [-0.1, 1.1])
    P = [A[i] + u * e1[i] + v * e2[i] for i in range(3)]
    p += ['%08X=%08X' % (px, fw(P[0])), '%08X=%08X' % (py, fw(P[1] + r.uniform(-2, 2))), '%08X=%08X' % (pz, fw(P[2]))]
    ow = '150A7E40=' + '/'.join('%d:%s' % (4 + i, ';'.join('%08X' % fw(c[i]) for c in cs)) for i in range(3))
    print('k%02d_c%d_k%X_n%d ! 0=%X,1=%X,2=%X,3=%X,4=%X ! %s ! ! ! ! %s ! ' % (t, case, kind, nr, obj, px, py, pz, tri, ','.join(p), ow))
