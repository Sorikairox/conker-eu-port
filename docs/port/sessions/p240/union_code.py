#!/usr/bin/env python3
# P240: resolve conflict blocks by keeping both sides (ours then theirs). Usage: union_code.py FILE
import sys, re
p = sys.argv[1]; out = []; st = 0; a = []; b = []
for l in open(p):
    if l.startswith('<<<<<<< '): st = 1; a = []; b = []; continue
    if st == 1 and l.startswith('======='): st = 2; continue
    if st == 2 and l.startswith('>>>>>>> '): out += a + b; st = 0; continue
    (a if st == 1 else b if st == 2 else out).append(l)
open(p, 'w').writelines(out)
