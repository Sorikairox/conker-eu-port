#!/usr/bin/env python3
"""P70: read bytes at a virtual address from conker/build/conker.eu.elf (ELF32 BE program headers).
usage: rd.py ADDR COUNT [h|w|b]   (prints hex values)"""
import struct, sys, os
E = os.path.join(os.path.dirname(__file__), '../../../../conker/build/conker.eu.elf')
d = open(E, 'rb').read()
phoff, = struct.unpack_from('>I', d, 0x1C); phnum, = struct.unpack_from('>H', d, 0x2C)
def rd(a, n):
    for i in range(phnum):
        t, off, va, pa, fs, ms = struct.unpack_from('>6I', d, phoff + 32 * i)
        if t == 1 and va <= a < va + fs:
            return d[off + a - va: off + a - va + n]
    raise SystemExit('not found %08X' % a)
a = int(sys.argv[1], 16); n = int(sys.argv[2]); k = sys.argv[3] if len(sys.argv) > 3 else 'w'
sz = {'b': 1, 'h': 2, 'w': 4}[k]; fmt = {'b': 'B', 'h': 'H', 'w': 'I'}[k]
b = rd(a, n * sz)
print(' '.join('%0*X' % (2 * sz, v) for v in struct.unpack('>%d%s' % (n, fmt), b)))
