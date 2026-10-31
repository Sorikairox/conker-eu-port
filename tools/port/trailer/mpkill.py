#!/usr/bin/env python3
"""P370 v6: pads for the trailer's 4-player kill. Base = the net4 session's menu route (port_work/trailer/mpkill/
base.env: every entry before retrace 6000 of net4/pads.env, i.e. title -> MULTI -> Bunker Deathmatch, 4 joined, match
from ~5947). Two uses:
  mpkill.py OUT.env 'P0=F:B:X:Y,...' ...       base + extra gameplay entries per pad (?padf syntax)
  mpkill.py OUT.env --bot DUMP.json [FROM [SHIFT]]   base + the inputs mpctl.js recorded from retrace FROM (default
                                                5990) on (the value in effect at FROM is written at FROM), every entry
                                                SHIFT retraces later: -2 = capture.mjs's padShift 2 for this env undone
                                                (the bot recorded real retraces; the mpkill shot adds 2 to every entry)"""
import sys, json
base = dict(l.split('=', 1) for l in open('port_work/trailer/mpkill/base.env').read().split('\n') if l)
add = {}
if len(sys.argv) > 2 and sys.argv[2] == '--bot':
    d = json.load(open(sys.argv[3])); frm = int(sys.argv[4]) if len(sys.argv) > 4 else 5990; sh = int(sys.argv[5]) if len(sys.argv) > 5 else 0
    for ch in range(4):
        ev = [e for e in d['padf'][ch].split(',') if e]
        before = [e for e in ev if int(e.split(':')[0]) <= frm]
        after = [f"{int(e.split(':')[0]) + sh}:{e.split(':', 1)[1]}" for e in ev if int(e.split(':')[0]) > frm]
        first = [f"{frm + sh}:{before[-1].split(':', 1)[1]}"] if before else []
        add[f'PADF{ch}'] = ','.join(first + after)
else:
    add = {f'PADF{a[1]}': a[3:] for a in sys.argv[2:]}
with open(sys.argv[1], 'w') as o:
    for k in ['PADF0', 'PADF1', 'PADF2', 'PADF3']:
        o.write(f"{k}={base[k]}{',' + add[k] if add.get(k) else ''}\n")
