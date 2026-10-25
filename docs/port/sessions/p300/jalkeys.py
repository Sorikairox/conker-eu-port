#!/usr/bin/env python3
# P300: list the EU jal keys (decoded from the jal word) of a nonmatchings .s file: count, key, symbol name.
import sys, re, collections
c = collections.Counter()
for l in open(sys.argv[1]):
    m = re.search(r'/\* \w+ (\w+) (\w+) \*/\s+jal\s+(\S+)', l)
    if m:
        w = int(m.group(2), 16); pc = int(m.group(1), 16)
        c[('%X' % ((pc & 0xF0000000) | ((w & 0x3FFFFFF) << 2)), m.group(3))] += 1
for (k, n), v in sorted(c.items()): print(v, k, n)
