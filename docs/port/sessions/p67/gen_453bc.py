#!/usr/bin/env python3
"""P67 setups for func_150453BC -> 453bc.txt. pos = 0x80420000, out = 0x80430000, floor list D_800D3720 (2 entries,
heights 24.8 fixed), vertex pointer lists at 0x80440000 / 0x80440010 -> 0x80450000.., surface table D_800DBE5C
(EU 0x800DC28C) = 0x80460000, D_800DC26C = 0x80440000. func_150A3F50 returns the entry count."""
import sys, struct
sys.path.insert(0, '../p59'); from pk import build
def fb(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
def setup(name, y=30, maxY=5, h0=10, h1=20, idx0=1, idx1=0, surf='80460000', n=2):
    spec = '80420000:0=f:1,4=f:%s,8=f:3;80430000:0=f:0,1C=b:0' % y
    spec += ';800D3720:0=w:%X,4=w:80440000,8=w:%X,10=w:%X,14=w:80440010,18=w:%X' % (int(h0 * 256) & 0xFFFFFFFF, idx0, int(h1 * 256) & 0xFFFFFFFF, idx1)
    spec += ';80440000:0=w:80450000,4=w:80450100,8=w:80450200,10=w:80450300,14=w:80450400,18=w:80450500'
    for b in range(6):
        spec += ';%X:0=w:%X,4=w:%X,8=w:%X,10=w:%X,14=w:%X,18=w:%X' % (0x80450000 + b * 0x100, *[(b << 12) | k for k in range(6)])
    spec += ';800DC28C:0=w:%s;800DC26C:0=w:80440000;80460000:0=w:111,4=w:222,8=w:333' % surf
    return '%s ! 0=80420000,1=%s,2=80430000 ! %s ! 150A3F50=%X ! ! ! !' % (name, fb(maxY), build(spec), n)
S = [('base', {}), ('eqY', dict(y=15, maxY=15)), ('eqD', dict(y=20)), ('tie', dict(h0=10, h1=10)), ('maxeq', dict(maxY=20)),
     ('maxhi', dict(maxY=25)), ('lowY', dict(y=4)), ('none', dict(y=8)), ('n0', dict(n=0)), ('n1', dict(n=1)), ('nosurf', dict(surf='0')),
     ('idx', dict(idx0=2, idx1=3)), ('neg', dict(h0=-5, h1=-2, y=0, maxY=-3))]
open(sys.argv[1] if len(sys.argv) > 1 else '453bc.txt', 'w').write('\n'.join(setup(k, **v) for k, v in S) + '\n')
