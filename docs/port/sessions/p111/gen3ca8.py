#!/usr/bin/env python3
"""P111 setups for func_150B3CA8(obj, a1, a2, a3, y, a5). Stubs by jal word: func_150ADA20 150ADF00 (RET),
func_150ADA68 150ADF48 (RETF). ARGMEM on func_1513C73C 1513CCAC a0 (28 bytes) and func_15148310 a0 / a1 / a11."""
import random
from importlib.machinery import SourceFileLoader
import sys; sys.path.insert(0, __file__.rsplit('/', 2)[0] + '/p96')
from gen import Mem, fb
R = random.Random(3)
for i in range(30):
    M = Mem(); obj = M.alloc(0x100); rec = M.alloc(0x40); pts = M.alloc(20 * 8)
    M.w(obj + 0x94, pts); M.w(obj + 0x98, rec); k = R.randint(0, 7); M.put(obj + 0x2D, bytes([k]))
    M.put(obj + 0xC, bytes([R.getrandbits(8)])); M.put(obj + 1, bytes([R.getrandbits(8)])); M.put(obj + 0x25, bytes([R.getrandbits(8)]))
    for j in range(8 * 5): M.f(pts + 4 * j, round(R.uniform(-500, 500), 2))
    for o in (0, 4, 0xC, 0x10): M.f(rec + o, round(R.uniform(-50, 50), 2))
    M.put(rec + 0x19, bytes([R.getrandbits(8) for _ in range(3)])); M.put(rec + 0x20, bytes([1]))
    rets = '150ADF00=%s' % ';'.join('%X' % R.getrandbits(32) for _ in range(4))
    retf = '150ADF48=%X;%X' % (fb(R.random()), fb(R.random()))
    print('s3ca8_%d ! 0=%X,1=0,2=1,3=0,4=%X,5=%X ! %s ! %s ! %s !  !  ! ' % (i, obj, fb(round(R.uniform(-200, 200), 2)), R.randint(0, 5), M.poke(R), rets, retf))
