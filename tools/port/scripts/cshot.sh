#!/bin/bash
# P349: canvas shot of one retrace. The game runs at det=2 (muted, one headless Chrome at a time), ?nethashstop pauses
# it right after retrace STOP, and the canvas's drawing buffer is saved as it is (its own resolution, no page around it).
# The same STOP and query give the same frame, so two builds can be compared pixel by pixel.
#   tools/port/scripts/cshot.sh OUT.png STOP SECS [EXTRA_QUERY]
#   env: CANVAS=WxH drawing buffer (default 1920x1440), PADF pad script (frame:buttons hex:x:y,...), WEB=DIR build dir
#        (default port/build/web), PROBE_STEPS extra audprobe steps
# e.g. cshot.sh port_work/p349/hud.png 400 40 '&warp=29&opt=healthhud:1,cashhud:1'
cd ~/conker-wt/web || exit 1
while [ "$(ps -axo command | grep -v grep | grep -c 'headless=new')" -gt 0 ]; do sleep 10; done
OUT=$1; STOP=$2; T=${3:-60}
case $OUT in /*) ;; *) OUT=$PWD/$OUT;; esac
mkdir -p "$(dirname "$OUT")"
Q="app=game&det=2&p103boot=1&nethashstop=$STOP&canvas=${CANVAS:-1920x1440}${PADF:+&padf=$PADF}${4:-}"
PROBE_LOG=${OUT%.png}.log PROBE_ANGLE=metal PROBE_NOAUDIO=1 PROBE_SAMPLES=0 PROBE_CSHOT=$OUT PROBE_WEB=${WEB:-} \
  port/web/audprobe.sh "$Q" "$T" > "${OUT%.png}.out" 2>&1
L=${OUT%.png}.log
echo "$(basename "$OUT"): $(grep -m1 -o 'stopped after retrace [0-9]*' "$L" || echo 'NOT STOPPED, last frame '"$(grep -oE 'frame [0-9]+' "$L" | tail -1)"); traps $(grep -iE 'Aborted|RuntimeError' "$L" | wc -l | tr -d ' ')"
