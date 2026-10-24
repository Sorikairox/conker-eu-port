#!/usr/bin/env python3
# P207: EU addresses of the %hi/%lo symbols in an asm function (from the encoded immediates). usage: symaddr.py file.s
import re, sys
hi, out = {}, {}
for l in open(sys.argv[1]):
    m = re.search(r'/\*\s*[0-9A-F]+\s+[0-9A-F]+\s+([0-9A-F]{8})\s*\*/.*%(hi|lo)\(([^)]+)\)', l)
    if not m: continue
    w = int(m.group(1), 16); imm = w & 0xFFFF; s = m.group(3)
    if m.group(2) == 'hi': hi[s] = imm
    elif s in hi:
        out[s] = ((hi[s] << 16) + (imm - 0x10000 if imm & 0x8000 else imm)) & 0xFFFFFFFF
for s, a in sorted(out.items()): print('%s %08X' % (s, a))
