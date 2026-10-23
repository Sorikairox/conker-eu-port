#!/usr/bin/env python3
"""P114: load a ROM asset by path (as func_1502B6BC(&q, 0, &n, depth, k0, k1, ...) does) and split its chunk table.
usage: scasset.py ROM K0 K1 ... (hex)  -> chunk list + hex head"""
import sys, struct, zlib
BASE = 0xAB2240
def load(rom, path):
    p = BASE; info = 0
    for k in path:
        off, info = struct.unpack_from('>iI', rom, p + 8 * k)
        if info & 0x0FFFFFFF == 0 or off == -1: return None
        p = p + off
    size = ((info & 0x0FFFFFFF) + 1) & ~1
    raw = rom[p:p + size]
    if (info & 0x70000000) == 0x10000000:
        n = struct.unpack_from('>I', raw)[0] & 0x7FFFFFFF
        raw = zlib.decompressobj(-15).decompress(raw[4:], n)
    return raw
def chunks(b):
    """func_1502B4A8(base, 0): {off, info} pairs until info bit 31; returns [(off, size)] (off None = empty)"""
    out = []; i = 0
    while True:
        off, info = struct.unpack_from('>iI', b, 8 * i); i += 1
        out.append((None if off == -1 or info & 0x0FFFFFFF == 0 else off, info & 0x0FFFFFFF))
        if info & 0x80000000: break
    return out
if __name__ == '__main__':
    rom = open(sys.argv[1], 'rb').read()
    b = load(rom, [int(x, 16) for x in sys.argv[2:]])
    if b is None: print('none'); sys.exit()
    print('%d bytes' % len(b))
    for k, (o, s) in enumerate(chunks(b)):
        print('chunk %d: off %s size %X' % (k, '%X' % o if o is not None else '-', s))
        if o is not None: print('   ', b[o:o + 64].hex())
