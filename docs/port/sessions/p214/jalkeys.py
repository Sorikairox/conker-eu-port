#!/usr/bin/env python3
# P207: decoded jal targets of an asm function: name -> key. usage: jalkeys.py file.s
import re, sys
for l in open(sys.argv[1]):
    m = re.search(r'/\*\s*[0-9A-F]+\s+([0-9A-F]+)\s+(0[CD][0-9A-F]{6})\s*\*/\s+jal\s+(\S+)', l)
    if m:
        w = int(m.group(2), 16); t = ((w & 0x3FFFFFF) << 2) | (int(m.group(1), 16) & 0xF0000000)
        print('%s %08X%s' % (m.group(3), t, '' if m.group(3) == 'func_%08X' % t else '  <-- differs'))
