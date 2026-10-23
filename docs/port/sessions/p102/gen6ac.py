#!/usr/bin/env python3
"""P102 setups for func_151406AC(ret, idx, group, skip): a doubly linked list (+4 prev, +8 next, key = +0x18 << 8 +
(+0x20 >> 16), non-negative keys: the asm's head stand-in has an uninitialised prev) at D_800DD280[group][idx]
(EU 800DD280, 0x1A0 per group). usage: gen6ac.py [n] > 6ac.txt"""
import random, sys
sys.path.insert(0, '/Users/sorikairo/conker-wt/portb/docs/port/sessions/p96')
from gen import Mem
R = random.Random(6)
for i in range(int(sys.argv[1]) if len(sys.argv) > 1 else 30):
    M = Mem(); g = R.randint(0, 1); idx = R.randint(0, 103); n = R.choice([1, 2, 2, 3, 4, 5, 6, 8]) if i > 1 else i + 1
    nodes = [M.alloc(0x30) for _ in range(n)]
    for k, a in enumerate(nodes):
        M.w(a + 4, nodes[k - 1] if k else 0); M.w(a + 8, nodes[k + 1] if k + 1 < n else 0)
        M.put(a + 0x18, bytes([R.choice([0, 1, 2, R.randint(0, 255)])]))
        M.w(a + 0x20, R.choice([R.randint(0, 0x7FFFFFFF), R.randint(0, 3) << 16, 0x10000]))
    M.w(0x800DD280 + g * 0x1A0 + idx * 4, nodes[0])
    print('6ac_%d ! 0=%X,1=%X,2=%X,3=%X ! %s !  !  !  !  ! ' % (i, R.getrandbits(32), idx, g, 0 if R.random() < 0.9 else 1, M.poke(R)))
