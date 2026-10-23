#!/usr/bin/env python3
"""P102 setups for func_1507BB28(unused, kind): D_800D154C (EU 800D196C) -> obj (+4 type id), D_800D1588 (EU 800D19A8)
[id] -> type, type - 0x10 -> list of {script, kind} (8 bytes, NULL script ends). Default list D_80086E28 (ROM data:
kinds 1 and 0xFA, else the asm spins). usage: genbb28.py [n] > bb28.txt"""
import random, sys
sys.path.insert(0, '/Users/sorikairo/conker-wt/portb/docs/port/sessions/p96')
from gen import Mem
R = random.Random(28)
for i in range(int(sys.argv[1]) if len(sys.argv) > 1 else 24):
    M = Mem(); obj = M.alloc(0x10); M.w(0x800D196C, obj); tid = R.randint(0, 186); M.put(obj + 4, bytes([tid]))
    c = R.random(); kinds = R.sample(range(2, 40), R.randint(0, 5))
    if c < 0.1: M.w(0x800D19A8 + 4 * tid, 0)
    else:
        t = M.alloc(0x40) + 0x10; M.w(0x800D19A8 + 4 * tid, t)
        if c < 0.2: M.w(t - 0x10, 0)
        else:
            lst = M.alloc(8 * (len(kinds) + 1)); M.w(t - 0x10, lst)
            for k, kd in enumerate(kinds): M.w(lst + 8 * k, M.alloc(4)); M.put(lst + 8 * k + 4, bytes([kd]))
            M.w(lst + 8 * len(kinds), 0); M.put(lst + 8 * len(kinds) + 4, bytes([R.choice([0, 0xFA, 7])]))
    kind = R.choice(kinds + [1, 0xFA, 0x101] if kinds else [1, 0xFA])
    print('bb28_%d ! 0=%X,1=%X ! %s !  !  !  !  ! ' % (i, R.getrandbits(32), kind, M.poke(R)))
