#!/usr/bin/env python3
"""P171: padroom.py (new game + first-room loop from S=18540) plus A / B taps (12 retraces) during the text boxes of the
   12157-17977 cutscene: A at 12300 + 400k, B at 12500 + 400k (k = 0..13).  padtalk.py [S]  env NOSTART as padroom."""
import os, subprocess, sys
here = os.path.dirname(os.path.abspath(__file__))
base = subprocess.check_output([sys.executable, os.path.join(here, 'padroom.py')] + sys.argv[1:], text=True).strip().split(',')
ev = [tuple(x.split(':')) for x in base]
for k in range(14):
    for f, b in ((12300 + 400 * k, '8000'), (12500 + 400 * k, '4000')):
        ev += [(str(f), b, '0', '0'), (str(f + 12), '0', '0', '0')]
ev.sort(key=lambda e: int(e[0]))
print(','.join(':'.join(e) for e in ev))
