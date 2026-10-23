#!/usr/bin/env python3
"""P154: new game + an attempt at the first room's puzzle: Conker starts facing the pillar with the gargoyle and the
   hanging tongue (light pull); walk up to it, jump (A, held = tail hover) and pull down. padtongue.py [START=18540]; env NOSTART=1: no pause, idle, then B presses"""
import os, sys
S = int(sys.argv[1]) if len(sys.argv) > 1 else 18540
F1, F2 = int(os.environ.get('F1', 3386)), int(os.environ.get('F2', 4458))
e = [(F1, '1000', 0, 0), (F1 + 15, '0', 0, 0), (F2, '1000', 0, 0), (F2 + 15, '0', 0, 0)]
steps = [(0, '0', 0, 80), (25, '8000', 0, 80), (55, '8000', 0, 0), (85, '0', 0, 0), (160, '0', 0, -80), (220, '0', 0, 0),
         (260, '8000', 0, 80), (300, '0', 0, 0), (360, '4000', 0, 0), (372, '0', 0, 0), (460, '0', 0, 80), (500, '8000', 0, 80),
         (560, '0', 0, 0), (640, '0', 0, -80), (700, '0', 0, 0)]
if not os.environ.get('NOSTART'): steps += [(760, '1000', 0, 0), (775, '0', 0, 0)]  # START = pause menu
else: steps += [(2000 + 200 * k + d, b, 0, 0) for k in range(6) for d, b in ((0, '4000'), (12, '0'))]  # NOSTART=1: idle, then B x6
e += [(S + d, b, x, y) for d, b, x, y in steps]
print(','.join(f'{f}:{b}:{x}:{y}' for f, b, x, y in e))
