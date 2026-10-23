#!/usr/bin/env python3
# P100: ins.py SRC FUNC DRAFT: replace the bare `#pragma GLOBAL_ASM(".../FUNC.s")` line of SRC (conker/src_eu) with
# DRAFT (which carries its own #ifdef NON_MATCHING / #else GLOBAL_ASM / #endif). Refuses if the line is already
# inside an #else branch or occurs more than once.
import sys, re
src, func, draft = sys.argv[1:4]
L = open(src).read().split('\n')
idx = [i for i, l in enumerate(L) if re.match(r'#pragma GLOBAL_ASM\(".*/%s\.s"\)\s*$' % func, l)]
assert len(idx) == 1, idx
i = idx[0]
assert not (i > 0 and L[i - 1].strip() == '#else'), 'already converted'
d = open(draft).read().rstrip('\n').split('\n')
assert d[0].startswith('#ifdef NON_MATCHING') and d[-1] == '#endif' and L[i] in d, 'draft shape'
L[i:i + 1] = d
open(src, 'w').write('\n'.join(L))
print('inserted', func, 'at line', i + 1)
