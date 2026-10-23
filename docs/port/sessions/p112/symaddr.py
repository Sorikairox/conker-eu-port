#!/usr/bin/env python3
"""P112: EU addresses of the data symbols an asm file uses (from the %hi / %lo instruction words). usage: symaddr.py FILE.s"""
import re, sys
hi, lo = {}, {}
for l in open(sys.argv[1]):
    m = re.search(r'/\* \w+ \w+ ([0-9A-F]{8}) \*/.*%(hi|lo)\(([A-Za-z_0-9]+)\)', l)
    if not m: continue
    w = int(m.group(1), 16) & 0xFFFF
    (hi if m.group(2) == 'hi' else lo).setdefault(m.group(3), w)
for s in sorted(set(hi) & set(lo)):
    print('%s %08X' % (s, ((hi[s] << 16) + (lo[s] - ((lo[s] & 0x8000) << 1))) & 0xFFFFFFFF))
