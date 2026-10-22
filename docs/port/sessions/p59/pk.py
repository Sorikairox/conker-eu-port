#!/usr/bin/env python3
"""P59 poke builder: pk.py 'BASE:off=size:val,...;BASE2:...' -> DIFFTEST_POKE words (big-endian merge).
BASE may be rN (record N of D_800CC2D0, EU 0x800CC6F0 + N*0x32C) or a hex address. size: b h w f (f = float)."""
import sys, struct
def build(spec):
    words = {}
    for part in filter(None, spec.split(';')):
        base, fields = part.split(':', 1)
        b = 0x800CC6F0 + int(base[1:]) * 0x32C if base.startswith('r') else int(base, 16)
        for f in filter(None, fields.split(',')):
            off, sv = f.split('='); sz, v = sv.split(':')
            a = b + int(off, 16)
            raw = struct.pack('>f', float(v)) if sz == 'f' else int(v, 16).to_bytes({'b': 1, 'h': 2, 'w': 4}[sz], 'big')
            for k, byte in enumerate(raw):
                w = (a + k) & ~3; sh = (3 - ((a + k) & 3)) * 8
                cur = words.get(w, 0); words[w] = (cur & ~(0xFF << sh)) | (byte << sh)
    return ','.join('%08X=%08X' % (w, v) for w, v in sorted(words.items()))
if __name__ == '__main__':
    print(build(sys.argv[1]))
