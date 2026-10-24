#!/usr/bin/env python3
"""P223 (from padwalk217 / 212 / 205): level-0x29 autopilot routes (?p205goto). Line 1: padf, line 2: p205goto.
   New routes:
     river   bpad2 (B pad, item, scene 4) then back south-west through zone 0x36 (Conker was 'in' 0x36 at (482, 535) ..
             (142, 1205) in P217 chB: ev 1074 waits on q 0x4036), A taps there, then east along the fence and north
             over the river fence line (900:200 .. 900:-600).
     river3  (P223) bpad, then after scene 4 B taps on the pad again (event 2 = ev 1074 needs held item q 0x2000 cmd 0xAA
             == 4 AND player off zone 8 (q 0x4008 = 1)), step off south (894:1100), A taps, then the river route.
     river4  (P223) bpad + B again (item 4 -> event 2 scene 5), then north from (900, 560) over the river fence with jump
             waypoints (jX:Z: A every 40 retraces) towards zone 0x0F (622, -2674) = the Jumping event 4, B taps there.
     pad9    (P223) bpad + B again (event 2 / scene 5), then back out of the field the way the scarecrow route came in to
             zone 9 (1746, -73, 1309, size 92; event 1 = ev 1090 wants q 0x4009 + held item 0x28), B / A taps there, then
             east (2100:1300, 2450:1100 = zone 0x42) and B taps.
     hitriver (P223) hit2 (12 B taps at Birdy, ?p223hit log), then the B pad + B again (scene 5), then west out of the
             field (200:900) and along the river with jump waypoints (-600:1000).
     river2  as river but straight north from the pad after scene 4 (no detour).
   Older: scarecrow, bpad, north, hit, hit2, bpad2 (see padwalk217.py)."""
import subprocess, sys, os
here = os.path.dirname(os.path.abspath(__file__))
route = sys.argv[1] if len(sys.argv) > 1 else 'river'
padf = subprocess.check_output([sys.executable, os.path.join(here, 'padwalk202.py'), '24100', '0', '0'], text=True).strip()
scare = '1640:1300_1640:700_1400:560_900:480_400:560_200:900_200:1150_456:1400_920:1540'
bpad = '24000:70:8000:' + scare + '_t8000:50_894:970:10_t8000:30_t4000:6_t8000:20'
routes = {
    'scarecrow': '24000:70:8000:' + scare,
    'bpad2': bpad + '_t8000:20',
    'river': bpad + '_900:700_700:500_480:540_250:700_150:1000_t8000:20_480:540_700:480_900:450_900:200_900:-200_900:-600',
    'river3': bpad + '_t4000:3_894:1100_t8000:40_900:700_700:500_480:540_250:700_150:1000_t8000:20_900:450_900:200_900:-200_900:-600',
    'river4': bpad + '_t4000:3_894:1100_t8000:12_900:700_900:560_j900:300_j900:0_j850:-400_j700:-900_j622:-1500_j622:-2000_622:-2674_t4000:10',
    'pad9': bpad + '_t4000:3_456:1400_200:1150_200:900_400:560_900:480_1400:560_1640:700_1746:1309:10_t4000:6_t8000:20_2100:1300_2450:1100_t4000:5',
    'hitriver': '24000:70:8000:' + scare + '_t8000:50_895:1295:15_t4000:12_894:970:10_t8000:30_t4000:6_t8000:20_t4000:3_200:1150_200:900_j170:700_j100:600_j-100:650_j-300:800_j-600:1000',
    'river2': bpad + '_900:600_900:200_900:-200_900:-600_900:-1000',
    'hit2': '24000:70:8000:' + scare + '_t8000:50_895:1295:15_t4000:12_t8000:10',
}
print(padf)
print(routes[route])
