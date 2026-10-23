#!/usr/bin/env python3
# jals.py ASM : decoded jal target per jal (key for RET/OUTA/OUTW)
import sys, re
for l in open(sys.argv[1]):
    m = re.search(r'/\* \w+ (\w{8}) (\w{8}) \*/\s+jal\s+(\w+)', l)
    if m:
        w = int(m.group(2), 16); pc = int(m.group(1), 16)
        print(m.group(3), '%08X' % ((pc & 0xF0000000) | ((w & 0x3FFFFFF) << 2)))
