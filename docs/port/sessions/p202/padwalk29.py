#!/usr/bin/env python3
"""P185: new game (STARTs at F1 / F2), then from S (first gameplay frame on level 0x29, ~23940 in node) a walk:
   forward, turn right + forward, jump (A), attack (B), turn left + forward, back; repeated twice.  padwalk29.py [S] [CYCLES]"""
import sys
S = int(sys.argv[1]) if len(sys.argv) > 1 else 24100
F1, F2 = 3386, 4458
e = [(F1, '1000', 0, 0), (F1 + 15, '0', 0, 0), (F2, '1000', 0, 0), (F2 + 15, '0', 0, 0)]
st = [(0, '0', 0, 80), (250, '0', 60, 60), (400, '0', 0, 80), (550, '8000', 0, 80), (565, '0', 0, 80), (650, '0', 0, 0),
      (700, '4000', 0, 0), (712, '0', 0, 0), (760, '0', -60, 60), (1000, '0', 0, -80), (1200, '0', 0, 0)]
K = int(sys.argv[2]) if len(sys.argv) > 2 else 2  # P199: number of walk cycles
for k in range(K):
    e += [(S + 1300 * k + d, b, x, y) for d, b, x, y in st]
print(','.join(f'{f}:{b}:{x}:{y}' for f, b, x, y in e))
