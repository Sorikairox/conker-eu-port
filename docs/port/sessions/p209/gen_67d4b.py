#!/usr/bin/env python3
# P209: extra func_150867D4 setups for the P207 survivors (penalty size, s16 first hop, open-slot ties, zone RET 0x100).
import sys, os
sys.path.insert(0, os.path.dirname(__file__))
import gen_67d4 as g
S = g.setup; F = 0xFF
# avoid penalty 50 vs 5000: via avoided A (first hop) is 200 + extra, via B 482
GA = [((0, 0, 0), (1, 2)), ((100, 0, 0), (0, 3)), ((0, 200, 0), (0, 3)), ((200, 0, 0), (1, 2))]
# same, avoided node 2 hops away (inner relaxation)
GA2 = [((0, 0, 0), (1,)), ((0, 0, 100), (0, 2, 3)), ((100, 0, 100), (1, 4)), ((0, 200, 100), (1, 4)), ((200, 0, 100), (2, 3))]
# first hop > 32767: (s16) makes it negative
GS = [((-30000, 0, 0), (1, 2)), ((30000, 0, 0), (0, 3)), ((-30000, 100, 0), (0, 3)), ((29000, 100, 0), (1, 2))]
# start pushed back into the open list (link == start skip): tie X / B at 200, T 141 from both
GL = [((0, 0, 0), (1, 2)), ((100, 0, 0), (0, 3)), ((0, 200, 0), (0, 4)), ((200, 0, 0), (1, 4)), ((100, 100, 0), (2, 3))]
# 0xFF link in the middle of start's links (0xFE mutant), tie Y / B at 300
GF = [((0, 0, 0), (1, F, 2)), ((100, 0, 0), (0, 3, 4)), ((0, 300, 0), (0, 5)), ((100, -100, 0), (1,)), ((300, 0, 0), (1, 5)),
      ((300, 300, 0), (2, 4))]
# two free slots when X / Y are added (first-free slot), tie X / Y, T equidistant
GW = [((0, 0, 0), (1, 2, 3)), ((-100, 0, 0), (0,)), ((100, 0, 0), (0, 4, 5)), ((0, 0, 900), (0,)), ((200, 100, 0), (2, 6)),
      ((200, -100, 0), (2, 6)), ((300, 0, 0), (4, 5))]
rows = [
 S('pen1', 0, [3], avoid=[1], g=GA), S('pen1n', 0, [3], g=GA), S('pen2', 0, [4], avoid=[2], g=GA2), S('pen2n', 0, [4], g=GA2),
 S('s16hop', 0, [3], g=GS), S('s16hop_b', 3, [0], g=GS),
 S('lstart', 0, [4], g=GL), S('lstart_z', 0, [4], zone='0;1;0;1', g=GL),
 S('ffmid', 0, [5], g=GF), S('ffmid2', 0, [5, 3], g=GF),
 S('wfree', 0, [6], g=GW), S('wfree_z', 0, [6], zone='1;0;1;0', g=GW),
 S('z100', 0, [7], zone='100;1;0;100;0;0'), S('z100b', 0, [7], zone='0;100;100;0;1;0'),
]
print('\n'.join(rows))
