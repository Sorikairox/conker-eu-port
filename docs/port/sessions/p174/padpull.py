#!/usr/bin/env python3
"""P171: new game, then at control (S = 18540) the P154 padtongue walk to the pillar (jump = tail pick-up), then 8 tries
   at the gargoyle's tongue: short walk forward, A held (jump + tail hover) with B taps in the air and after landing,
   stick down (pull) while A is held; then B x4 standing.  padpull.py [S]"""
import sys
S = int(sys.argv[1]) if len(sys.argv) > 1 else 18540
F1, F2 = 3386, 4458
e = [(F1, '1000', 0, 0), (F1 + 15, '0', 0, 0), (F2, '1000', 0, 0), (F2 + 15, '0', 0, 0)]
st = [(0, '0', 0, 80), (25, '8000', 0, 80), (55, '8000', 0, 0), (85, '0', 0, 0), (160, '0', 0, -80), (220, '0', 0, 0),
      (260, '8000', 0, 80), (300, '0', 0, 0), (360, '4000', 0, 0), (372, '0', 0, 0)]
t = 450
for k in range(8):
    y = 40 if k % 2 == 0 else 20
    st += [(t, '0', 0, y), (t + 15, '8000', 0, y), (t + 30, 'C000', 0, 0), (t + 40, '8000', 0, 0), (t + 55, '8000', 0, -80),
           (t + 90, '0', 0, 0), (t + 100, '4000', 0, 0), (t + 112, '0', 0, 0), (t + 140, '0', 0, -30), (t + 160, '0', 0, 0)]
    t += 200
st += [(t + 200 * k + d, b, 0, 0) for k in range(4) for d, b in ((0, '4000'), (12, '0'))]
e += [(S + d, b, x, y) for d, b, x, y in st]
print(','.join(f'{f}:{b}:{x}:{y}' for f, b, x, y in e))
