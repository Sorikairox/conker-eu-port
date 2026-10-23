#!/usr/bin/env python3
# P172: draft for difftest = header lines + the NM body of FUNC cut from a source file (from the line after
# '#ifdef NON_MATCHING' that precedes it ... up to its closing '}' at column 0). usage: mkdraft.py src.c FUNC hdr.c out.c
import sys, re
src, fn, hdr, out = sys.argv[1:5]
L = open(src).read().split('\n')
i = next(k for k, l in enumerate(L) if re.match(r'^[A-Za-z].*\b%s\(.*\{\s*$' % fn, l))
s = i
while s > 0 and L[s - 1].startswith('//'): s -= 1
e = i
while L[e] != '}': e += 1
open(out, 'w').write(open(hdr).read() + '\n'.join(L[s:e + 1]) + '\n')
