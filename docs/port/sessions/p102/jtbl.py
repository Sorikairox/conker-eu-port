#!/usr/bin/env python3
"""P102: read a jump table from build/conker.eu.elf. usage: jtbl.py ADDR N [base] -> 'case target' lines (case = base + i)."""
import struct, sys
def rd(elf, addr, n):
    d = open(elf, 'rb').read()
    shoff, = struct.unpack('>I', d[0x20:0x24]); shentsize, shnum = struct.unpack('>HH', d[0x2E:0x32])
    for i in range(shnum):
        nm, ty, fl, a, off, sz = struct.unpack('>6I', d[shoff + i * shentsize: shoff + i * shentsize + 24])
        if ty == 1 and a <= addr < a + sz:
            o = off + addr - a; return struct.unpack('>%dI' % n, d[o:o + 4 * n])
    raise SystemExit('not found')
a, n = int(sys.argv[1], 16), int(sys.argv[2]); base = int(sys.argv[3], 16) if len(sys.argv) > 3 else 0
for i, w in enumerate(rd('/Users/sorikairo/conker-wt/portb/conker/build/conker.eu.elf', a, n)): print('%X %08X' % (base + i, w))
