#!/usr/bin/env python3
"""P165: new game, then a first-room test after control (~18485):
   S+0..500 idle (audio idle window), S+500..1000 run forward (stick 80), S+1000..1300 slow walk (stick 25),
   then an exploration loop: walk in 8 directions (120 retraces each) and press B after each leg (B also pressed
   standing still twice), finally START (pause) at S+3800.  padroom.py [S=18540]  env NOSTART=1: no pause.
   Output: the ?padf list (frame:buttons_hex:x:y)."""
import os, sys
S = int(sys.argv[1]) if len(sys.argv) > 1 else 18540
F1, F2 = int(os.environ.get('F1', 3386)), int(os.environ.get('F2', 4458))
e = [(F1, '1000', 0, 0), (F1 + 15, '0', 0, 0), (F2, '1000', 0, 0), (F2 + 15, '0', 0, 0)]
st = [(500, '0', 0, 80), (1000, '0', 0, 25), (1300, '0', 0, 0),
      (1320, '4000', 0, 0), (1332, '0', 0, 0), (1400, '4000', 0, 0), (1412, '0', 0, 0)]
dirs = [(0, 80), (80, 0), (0, -80), (-80, 0), (60, 60), (-60, 60), (60, -60), (-60, -60),
        (0, 80), (0, 80), (80, 0), (0, 80)]
t = 1450
for x, y in dirs:
    st += [(t, '0', x, y), (t + 120, '0', 0, 0), (t + 130, '4000', 0, 0), (t + 142, '0', 0, 0)]
    t += 200
if not os.environ.get('NOSTART'): st += [(3800, '1000', 0, 0), (3815, '0', 0, 0)]
e += [(S + d, b, x, y) for d, b, x, y in st]
print(','.join(f'{f}:{b}:{x}:{y}' for f, b, x, y in e))
