#!/usr/bin/env python3
"""P357: one-paragraph report of an end-to-end replay (tools/port/scripts/e2e_replay.sh) from its result.json
(window.__e2e.status() of port/web/main.js at the end of the replay).
   e2e_report.py OUTDIR RECORDING_NAME      exit 0 = identical, 1 = a difference or an error"""
import json
import os
import sys

d, name = sys.argv[1], sys.argv[2]
try:
    r = json.load(open(os.path.join(d, 'result.json')))
except (OSError, ValueError):
    tail = open(os.path.join(d, 'driver.out')).read()[-400:] if os.path.exists(os.path.join(d, 'driver.out')) else ''
    print(f'ERROR {name}: no result ({tail.strip()})')
    sys.exit(1)
total = r.get('total') or 0
gt = lambda f: f'{int(f / 50 // 60)}:{int(f / 50 % 60):02d}'   # PAL: 50 retraces per second of game time
pct = lambda f: f'{100.0 * f / total:.1f} %' if total else '?'
reached = r.get('endFrame') or r.get('frame') or 0
wall = r.get('wall_s') or 0
speed = f'{reached / wall:.0f} retraces/s, {reached / 50 / wall:.1f}x real time' if wall else ''
builds = 'same build: H / S compared too' if r.get('sameBuild') else f"recorded with build {r.get('recBuild')}, this is {r.get('build')}: G / level / mode compared"
if r.get('state') == 'done' and not r.get('first'):
    print(f"PASS {name}: {total} retraces ({gt(total)} of game time) IDENTICAL, {r.get('matchedChecks')}/{r.get('checks')} checkpoints and "
          f"{r.get('matchedG')} digests matched; {wall:.0f} s ({speed}); {builds}")
    sys.exit(0)
if r.get('state') in ('error', 'timeout') or not r.get('first'):
    print(f"ERROR {name}: state {r.get('state')} {r.get('error') or ''} at retrace {reached} of {total} ({pct(reached)}); log {d}/chrome.log")
    sys.exit(1)
f = r['first']
pics = ' '.join(p for p in ('actual.png', 'expected.png') if os.path.exists(os.path.join(d, p)))
print(f"FAIL {name}: first difference at retrace {f['f']} ({gt(f['f'])} of game time, {pct(f['f'])} of the recording), level "
      f"{f.get('level', 0):X} mode {f.get('mode')}: {f['what']}")
print(f"     last matching fingerprint at retrace {f.get('lastGood')}; {r.get('matchedChecks')}/{r.get('checks')} checkpoints matched before; "
      f"reached retrace {reached} ({pct(reached)}, level {r.get('level', 0):X} mode {r.get('mode')})"
      + (f", {r.get('mismatches')} differing fingerprints in all" if r.get('mismatches', 0) > 1 else ''))
pix = open(os.path.join(d, 'pixdiff.txt')).read().strip().split(': ', 1)[-1] if os.path.exists(os.path.join(d, 'pixdiff.txt')) else ''
print(f"     {builds}; pictures in {d}: {pics or 'none'}{' (' + pix + ')' if pix else ''} (ROM-derived: port_work only)")
sys.exit(1)
