#!/usr/bin/env python3
# P184: wrap FILE's GLOBAL_ASM line of FUNC in #ifdef NON_MATCHING with the candidate. usage: insert.py FILE FUNC cand.c
import sys, re
p, fn, c = sys.argv[1:4]
t = open(p).read()
m = re.search(r'#pragma GLOBAL_ASM\("asm/nonmatchings/[^"]+/%s\.s"\)\n' % fn, t)
assert m and t.count(m.group(0)) == 1, 'not found once'
cand = open(c).read()
open(p, 'w').write(t.replace(m.group(0), '#ifdef NON_MATCHING\n' + cand + '#else\n' + m.group(0) + '#endif\n'))
print('inserted', fn, 'in', p)
