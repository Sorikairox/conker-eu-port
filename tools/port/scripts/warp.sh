#!/bin/bash
# P327: one-command gameplay test. Boots straight into level LEVEL (hex) with ?warp (no intro / title / opening),
# muted, det=2, fresh save, one headless Chrome at a time; prints a compact summary.
#   tools/port/scripts/warp.sh NAME SECS LEVEL [EXTRA_QUERY]      e.g. warp.sh t1 40 29 '&opt=longbreath:1'
#   env: PADF  pad script, absolute VI retraces (frame:buttons hex:stick x:stick y,...), e.g. '200:0:0:80,400:0:0:0'
#        SCENE warpscene (start / entry index passed to the level load, default 0)
#        SHOTS screenshot times in ms (default: SECS-3 s)    POS=F  dump object positions every 250 retraces from F
#        STEPS extra audprobe steps (P347), e.g. '9000:keydown:KeyL; 10000:keyup:KeyL; 12500:click; 13000:eval:EXPR'
#        PROBE_WEB=DIR serve another build directory (audprobe.sh, P347)
# Logs: port_work/p327/NAME/chrome.log (+ s_<ms>ms.png). Gameplay on level 0x29 starts ~retrace 100 (about 7 s
# wall time), against ~5800 retraces (~2 min at det=2, 4+ min with the new-game route) through the title + opening.
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1   # P353: the worktree this script lives in
[ -n "${PROBE_NOWAIT:-}" ] || while [ "$(ps -axo command | grep -v grep | grep -c 'headless=new')" -gt 0 ]; do sleep 10; done
D=port_work/p327/$1; rm -rf "$D"; mkdir -p "$D"
T=${2:-40}; SHOTS=${SHOTS:-$(( (T - 3) * 1000 ))}
S="${STEPS:-}"; for t in $SHOTS; do S="$S${S:+; }$t:shot:$D/s_${t}ms.png"; done
Q="app=game&det=2&p103boot=1&warp=$3${SCENE:+&warpscene=$SCENE}${PADF:+&padf=$PADF}${POS:+&p205obj=$POS}${4:-}"
s=$(date +%s)
PROBE_LOG=$D/chrome.log PROBE_ANGLE=metal PROBE_NOAUDIO=1 PROBE_SAMPLES=0 PROBE_STEPS="$S" \
  port/web/audprobe.sh "$Q" "$T" > "$D.out" 2>&1
L=$D/chrome.log
echo "== $1 (warp=$3, ${T}s run, $(( $(date +%s) - s ))s wall): $(grep -m1 '\[warp\]' $L)"
echo "modes: $(grep -oE 'frame [0-9]+: mode [0-9]+ \(prev [0-9]+\) level [0-9A-F]+' $L | awk '{print $2 "m" $4 "L" $8}' | tr '\n' ' ' | cut -c1-400)"
[ -n "$POS" ] && grep -E '\[p205obj\] frame|\[p205obj\]   rec  ?[0-9]+ ' $L | awk '/frame/ {f=$3; p=$5; next} {r=$3+0; if (r==p) print "  player pos @" f ": " $11, $12, $13}'
echo "traps/aborts: $(grep -iE 'Aborted|RuntimeError|trap' $L | grep -vc 'no trap')  last frame: $(grep -oE 'frame [0-9]+' $L | tail -1)"
