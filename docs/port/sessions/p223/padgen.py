#!/usr/bin/env python3
"""P154: ?padf / PORT_PADF string for a long new game: the two menu STARTs (F1 / F2, default 3386 / 4458), then from FROM
   to TO a cycle of PERIOD retraces: A held HOLD at +0, B held HOLD at +PERIOD/3, stick up (Y=STICK) held PERIOD/4 at
   +PERIOD/2 (advances dialogue / skips; in gameplay it makes Conker jump / attack / walk = visible control).
   padgen.py [FROM=10800] [TO=30000] [PERIOD=300] [HOLD=8] [STICK=80]   env F1 F2, NOA=1 (no A), NOB=1, NOSTICK=1"""
import os, sys
a = [int(x) for x in sys.argv[1:]] + [None] * 5
FROM, TO, PER, HOLD, ST = a[0] or 10800, a[1] or 30000, a[2] or 300, a[3] or 8, a[4] or 80
F1, F2 = int(os.environ.get('F1', 3386)), int(os.environ.get('F2', 4458))
e = [(F1, '1000', 0, 0), (F1 + 15, '0', 0, 0), (F2, '1000', 0, 0), (F2 + 15, '0', 0, 0)]
for t in range(FROM, TO, PER):
    if not os.environ.get('NOA'): e += [(t, '8000', 0, 0), (t + HOLD, '0', 0, 0)]
    if not os.environ.get('NOB'): e += [(t + PER // 3, '4000', 0, 0), (t + PER // 3 + HOLD, '0', 0, 0)]
    if not os.environ.get('NOSTICK'): e += [(t + PER // 2, '0', 0, ST), (t + PER // 2 + PER // 4, '0', 0, 0)]
print(','.join(f'{f}:{b}:{x}:{y}' for f, b, x, y in sorted(e)))
