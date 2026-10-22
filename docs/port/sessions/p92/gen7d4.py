#!/usr/bin/env python3
"""P92 setups for func_1501F7D4 (stubs: func_15020920 = jal 15020920, func_15020090 = jal 15020090 with OUTA a0 =
12 floats). usage: gen7d4.py [n] > 7d4.txt"""
import random, struct, sys
from gen import Mem, fb
E8, E70, C88 = 0x800C39E8, 0x800C3E70, 0x800C3C88
R = random.Random(9274)
for i in range(int(sys.argv[1]) if len(sys.argv) > 1 else 50):
    M = Mem(); slot = i % 2; actor = R.randint(0, 3); n = R.choice([1, 2, 3, 5, 8])
    e8 = M.alloc(8); M.w(E8 + 4 * slot, e8); M.h(e8 + 2 * actor, n)
    acts = M.alloc(0x40 * 4); M.w(E70 + 4 * slot, acts); a = acts + 0x40 * actor
    keys = M.alloc(4 * (n + 1)); M.w(a + 4, keys); v = 0.0; ks = []
    for j in range(n + 1):
        ks.append(v); M.f(keys + 4 * j, v); v += R.choice([0.0, round(R.uniform(1, 500), 2)])
    st = M.alloc(102 * 4); M.w(a + 0x38, st); v = 0.0; ss = []
    for j in range(102):
        ss.append(v); M.f(st + 4 * j, v); v += R.choice([0.0, round(R.uniform(0, 20), 2), round(R.uniform(0, 20), 2)])
    for j in range(12): M.f(a + 8 + 4 * j, round(R.uniform(-300, 300), 2))
    M.put(a + 0x3C, bytes([R.choice([0, 1, 2, 0xFF])]))
    rec = M.alloc(8 * 9); M.w(C88 + slot * 0x78 + 4 * actor, rec)
    for j in range(9): M.h(rec + 8 * j + 6, R.choice([0, 0, 1]))
    pool = ks + ss
    dist = R.choice([R.choice(pool), round(R.uniform(-10, max(pool) + 10), 2), round(R.uniform(0, max(ks)), 2), round(R.uniform(0, max(ss)), 2)])
    pts = ';'.join('%08X' % fb(round(R.uniform(-500, 500), 2)) for _ in range(12))
    print('s7d4_%d ! 0=%X,1=%08X,2=80450000,3=%X,4=80450040 ! %s !  !  ! 15020090=0:%s !  ! ' % (
        i, actor, fb(dist), slot, M.poke(R), pts))
