#!/bin/bash
# P90: print the asm of func_150268BC between the previous jal/label and each jal to the named callees (instruction text only)
# usage: callsite.sh NAME [NAME...]   (env N = max lines back, default 40)
python3 - "$@" <<'PY'
import re, sys, os
L = open('/Users/sorikairo/conker-wt/port/conker/asm/nonmatchings/game_eu_51190/func_150268BC.s').read().split('\n')
names = sys.argv[1:]; N = int(os.environ.get('N', 40))
def ins(l):
    m = re.search(r'\*/\s+(.*)', l)
    return m.group(1).strip() if m else l.strip()
for i, l in enumerate(L):
    m = re.search(r'\bjal\s+(\w+)', l)
    if m and m.group(1) in names:
        j = i - 1
        while j > 0 and i - j < N and not re.search(r'\bjal\b', L[j]) and not L[j].startswith('.L'): j -= 1
        print('== %s @%d' % (m.group(1), i + 1))
        print(' ; '.join(ins(x) for x in L[j:i + 2] if x.strip()))
PY
