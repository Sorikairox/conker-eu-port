#!/usr/bin/env python3
"""P174: list D_800877D0 level events (0x14-byte records) for a level: name, flags, level, prereqs."""
import sys, struct
from elfrd import Elf
e = Elf(sys.argv[1]); lv = int(sys.argv[2], 16) if len(sys.argv) > 2 else None
T = e.byname.get('D_800877D0', 0x800877D0)
def cstr(va):
    b = e.rd(va, 64) or b''
    return b.split(b'\0')[0].decode('latin1')
for i in range(0x400):
    r = e.rd(T + 0x14 * i, 0x14)
    if not r: break
    nm, fl, l, u, pre, x = struct.unpack('>IIHHII', r)
    if nm == 0 and fl == 0 and i > 0x300: break
    if lv is not None and l != lv: continue
    pl = []
    if pre:
        for k in range(16):
            v = struct.unpack('>H', e.rd(pre + 2 * k, 2))[0]
            pl.append('%X' % v)
            if v == 0xFFFF: break
    print('%3X %-24s fl %08X lv %X u %X pre [%s] x %08X' % (i, cstr(nm) if nm else '-', fl, l, u, ' '.join(pl), x))
