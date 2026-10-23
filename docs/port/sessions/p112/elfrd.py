#!/usr/bin/env python3
"""P112: minimal big-endian ELF32 reader: rd(vaddr, n) from PROGBITS sections, sym names by address."""
import struct, sys
class Elf:
    def __init__(s, path):
        d = s.d = open(path, 'rb').read()
        shoff, = struct.unpack_from('>I', d, 0x20); shnum, shstr = struct.unpack_from('>HH', d, 0x30)
        sh = [struct.unpack_from('>10I', d, shoff + 40 * i) for i in range(shnum)]
        s.secs = [x for x in sh if x[1] == 1 and x[3] and x[5]]
        s.syms = {}; s.byname = {}
        for x in sh:
            if x[1] == 2:
                strt = sh[x[6]]
                for k in range(x[5] // 16):
                    nm, val, sz, info, oth, shn = struct.unpack_from('>IIIBBH', d, x[4] + 16 * k)
                    n = d[strt[4] + nm: d.index(b'\0', strt[4] + nm)].decode()
                    if n: s.syms.setdefault(val, n); s.byname[n] = val
    def rd(s, va, n):
        for x in s.secs:
            if x[3] <= va < x[3] + x[5]: return s.d[x[4] + va - x[3]: x[4] + va - x[3] + n]
        return None
    def w(s, va): b = s.rd(va, 4); return struct.unpack('>I', b)[0] if b else None
    def name(s, va): return s.syms.get(va, '%08X' % va)
