#!/usr/bin/env python3
# P252: resolve every conflict block by taking the incoming side (theirs). Usage: take_theirs.py FILE
import sys
p = sys.argv[1]; out = []; st = 0
for l in open(p):
    if l.startswith('<<<<<<< '): st = 1; continue
    if st == 1 and l.startswith('======='): st = 2; continue
    if st == 2 and l.startswith('>>>>>>> '): st = 0; continue
    if st != 1: out.append(l)
open(p, 'w').writelines(out)
