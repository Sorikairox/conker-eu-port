#!/usr/bin/env python3
"""ex.py SRC FUNC > draft.c: the #ifdef NON_MATCHING ... #else block of SRC that defines FUNC (without the #if lines)"""
import sys, re
src, fn = sys.argv[1], sys.argv[2]
L = open(src).read().split('\n')
d = [i for i, l in enumerate(L) if re.match(r'^[A-Za-z_].*\b%s\s*\(' % fn, l) and not l.rstrip().endswith(';')][0]
a = max(i for i in range(d) if L[i].startswith('#ifdef NON_MATCHING'))
b = min(i for i in range(d, len(L)) if L[i].startswith(('#else', '#endif')))
print('\n'.join(L[a + 1:b]))
