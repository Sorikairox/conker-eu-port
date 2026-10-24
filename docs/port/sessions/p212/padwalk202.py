#!/usr/bin/env python3
"""P202: padwalk29's first CYC1 cycles (P199 route: pond, swim out), then CYC2 exploration cycles with A taps:
   forward 360 retraces (A tap every 90), turn (stick x +-60, alternating every 2nd cycle), B tap.
   padwalk202.py [S=24100] [CYC1=6] [CYC2=10]"""
import sys
a = [int(x) for x in sys.argv[1:]] + [None] * 3
S, K1, K2 = a[0] or 24100, a[1] if a[1] is not None else 6, a[2] if a[2] is not None else 10
F1, F2 = 3386, 4458
e = [(F1, '1000', 0, 0), (F1 + 15, '0', 0, 0), (F2, '1000', 0, 0), (F2 + 15, '0', 0, 0)]
st = [(0, '0', 0, 80), (250, '0', 60, 60), (400, '0', 0, 80), (550, '8000', 0, 80), (565, '0', 0, 80), (650, '0', 0, 0),
      (700, '4000', 0, 0), (712, '0', 0, 0), (760, '0', -60, 60), (1000, '0', 0, -80), (1200, '0', 0, 0)]
for k in range(K1):
    e += [(S + 1300 * k + d, b, x, y) for d, b, x, y in st]
T = S + 1300 * K1
for k in range(K2):
    sx = 60 if (k // 2) % 2 == 0 else -60
    for j in range(4):
        e += [(T + 90 * j, '0', 0, 80), (T + 90 * j + 40, '8000', 0, 80), (T + 90 * j + 48, '0', 0, 80)]
    e += [(T + 360, '0', sx, 40), (T + 460, '0', 0, 0), (T + 480, '4000', 0, 0), (T + 490, '0', 0, 0), (T + 500, '8000', 0, 0), (T + 508, '0', 0, 0)]
    T += 540
print(','.join(f'{f}:{b}:{x}:{y}' for f, b, x, y in e))
