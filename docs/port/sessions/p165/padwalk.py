#!/usr/bin/env python3
"""P154: new game (menu STARTs F1 / F2) + no input through the cutscenes (they are timed: the Gregg cutscene ends at
   retrace 18485 with no presses) + a walk test in the first controllable room from START (default 18600):
   right, down, left, up (STEP retraces each, gap 100), A (jump), B, down-right, right, Z+up.  padwalk.py [START] [STEP]"""
import os, sys
S = int(sys.argv[1]) if len(sys.argv) > 1 else 18600
STEP = int(sys.argv[2]) if len(sys.argv) > 2 else 200
F1, F2 = int(os.environ.get('F1', 3386)), int(os.environ.get('F2', 4458))
e = [(F1, '1000', 0, 0), (F1 + 15, '0', 0, 0), (F2, '1000', 0, 0), (F2 + 15, '0', 0, 0)]
t = S
for b, x, y in [('0', 80, 0), ('0', 0, -80), ('0', -80, 0), ('0', 0, 80), ('8000', 0, 0), ('4000', 0, 0),
                ('0', 56, -56), ('0', 80, 0), ('2000', 0, 80)]:
    d = STEP if b in ('0', '2000') else 12
    e += [(t, b, x, y), (t + d, '0', 0, 0)]
    t += d + 100
print(','.join(f'{f}:{b}:{x}:{y}' for f, b, x, y in e))
print(f'walk {S}..{t}', file=sys.stderr)
