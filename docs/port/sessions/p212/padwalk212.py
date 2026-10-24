#!/usr/bin/env python3
"""P212 (from P205): padwalk202 extended with targeted level-0x29 routes for the pad autopilot (port/gfx/p205_obj.c, TEST
   ?p205goto / PORT_P205GOTO). New game START presses as padwalk202 (no walk cycles), then from retrace 24000 the
   autopilot walks the waypoints (x:z, radius 70; tBTN:N = tap BTN N times every 60 retraces).
   padwalk205.py ROUTE  -> line 1: padf string, line 2: p205goto string
   Routes:
     scarecrow  around the fence (x ~1590) by the south (z ~490), west side (x ~200), into the field to (920, 1540):
                the Birdy (scarecrow) dialogue starts there (box 26812, 16 lines; second box 28840, 4 lines), A taps.
     bpad       scarecrow + 50 A taps (dialogue to the end) + the disc in front of the scarecrow (895, 1295, radius 15) + 3 B taps
                + 20 A taps.
     north      (P212) scarecrow + 50 A taps, then north: 900:1000 steps on the B pad (zone 0x24, 894 / 970, radius 37)
                -> second Birdy scene 29921..31469 ("OKAY, I'LL PRESS B"); then 900:600 and on to the river fence (stuck at
                z ~548; door on the hill across the river).
     bpad2      (P212) scarecrow + 50 A taps, B pad (894:970:10), 30 A taps (scene), 6 B taps, 40 A taps.
   Node:   PORT_PADF="$(sed -n 1p)" PORT_P205GOTO="$(sed -n 2p)" nb.sh NAME 760
   Chrome: shots.sh DIR "&p205goto=..." 780 with PADF = line 1."""
import subprocess, sys, os
here = os.path.dirname(os.path.abspath(__file__))
route = sys.argv[1] if len(sys.argv) > 1 else 'scarecrow'
padf = subprocess.check_output([sys.executable, os.path.join(here, 'padwalk202.py'), '24100', '0', '0'], text=True).strip()
scare = '1640:1300_1640:700_1400:560_900:480_400:560_200:900_200:1150_456:1400_920:1540'
routes = {
    'scarecrow': '24000:70:8000:' + scare,
    'bpad': '24000:70:8000:' + scare + '_t8000:50_895:1295:15_t4000:3_t8000:20',
    'north': '24000:70:8000:' + scare + '_t8000:50_900:1000_900:600_900:200_900:-200_900:-600_900:-1000_900:-1400',
    'bpad2': '24000:70:8000:' + scare + '_t8000:50_894:970:10_t8000:30_t4000:6_t8000:40',
}
print(padf)
print(routes[route])
