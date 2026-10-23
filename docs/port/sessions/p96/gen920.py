#!/usr/bin/env python3
"""P96 setups for func_15020920 (actor, seg, slot). Stub func_15020090 = jal 15020090 with OUTA a0 = 12 floats
(the control points). EU addresses (= US names here): D_800C39E8, D_800C3E70, D_eu_800C3C88. usage: gen920.py [n]"""
import random, struct, sys
from gen import Mem, fb
E8, E70, C88 = 0x800C39E8, 0x800C3E70, 0x800C3C88
R = random.Random(9620)
for i in range(int(sys.argv[1]) if len(sys.argv) > 1 else 40):
    M = Mem(); slot = i % 2; actor = R.randint(0, 3); n = R.choice([1, 2, 3, 5, 8])
    seg = R.choice([0, 1, n - 2, n - 1, n, R.randint(0, max(n - 2, 0))])
    e8 = M.alloc(8); M.w(E8 + 4 * slot, e8); M.h(e8 + 2 * actor, n)
    acts = M.alloc(0x40 * 4); M.w(E70 + 4 * slot, acts); a = acts + 0x40 * actor
    keys = M.alloc(4 * (n + 2)); M.w(a + 4, keys); v = round(R.uniform(0, 50), 2)
    for j in range(n + 2):
        M.f(keys + 4 * j, v); v += R.choice([0.0, round(R.uniform(1, 500), 2)])
    st = M.alloc(104 * 4); M.w(a + 0x38, st)
    for j in range(104): M.f(st + 4 * j, -1.0)
    for j in range(12): M.f(a + 8 + 4 * j, 7.0)
    M.put(a + 0x3C, bytes([0xEE]))
    rec = M.alloc(8 * 10); M.w(C88 + slot * 0x78 + 4 * actor, rec)
    for j in range(10): M.h(rec + 8 * j + 6, R.choice([0, 0, 1, 2]) if i >= 4 else (i & 1))
    mode = R.random()
    if mode < 0.15: P = [round(R.uniform(-5, 5), 2)] * 3 * 4          # degenerate: all points equal
    elif mode < 0.3: P = [0.0] * 12
    else: P = [round(R.uniform(-500, 500), 2) for _ in range(12)]
    pts = ';'.join('%08X' % fb(x) for x in P)
    print('s920_%d ! 0=%X,1=%X,2=%X ! %s !  !  ! 15020090=0:%s !  ! ' % (i, actor, seg & 0xFFFFFFFF, slot, M.poke(R), pts))
