#!/bin/bash
# P72: real-time Chrome walk through the checkpoint respawn (the P69 hang) to the level 0x2C warp; screenshots + log.
#   port/web/p72shots.sh [OUTDIR] [WALK_MS=29000] [HOLD_MS=8000] [EXTRA_QUERY]
#   env DENSE="FROM_MS TO_MS": extra shots every 200 ms in that window (the warp lasts ~80 frames)
#   P149: the stick-up hold is now FRAME-based (?padf, VI retraces at 50 Hz): WALK_MS / HOLD_MS map to retraces
#   F = WALK_MS * 50 / 1000 - 70 (Chrome boot offset) .. F + HOLD_MS * 50 / 1000 (29000 / 8000 -> 1380 .. 1780);
#   env WALKF="FROM TO" sets the retraces directly; WALLCLOCK=1 = old KeyW presses at wall time
cd "$(dirname "$0")/../.." || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
D=${1:-$PWD/port_work/p72}; W=${2:-29000}; H=${3:-8000}; X=${4:-}; mkdir -p "$D"
if [ -n "${WALLCLOCK:-}" ]; then S="$W:keydown:KeyW; $((W + H)):keyup:KeyW"; Q=""
else set -- ${WALKF:-$((W * 50 / 1000 - 70)) $((W * 50 / 1000 - 70 + H * 50 / 1000))}; S=""; Q="&padf=$1:0:0:80,$2:0:0:0"; fi
for k in $(seq 1 16); do t=$((W + 1000 * k)); S="$S${S:+; }$t:shot:$D/walk_${t}ms.png"; done
if [ -n "${DENSE:-}" ]; then set -- $DENSE; for ((t = $1; t <= $2; t += 200)); do S="$S; $t:shot:$D/dense_${t}ms.png"; done; fi
PROBE_LOG=$D/chrome.log PROBE_ANGLE=metal PROBE_NOAUDIO=1 PROBE_SAMPLES=0 PROBE_STEPS="$S" \
  port/web/audprobe.sh "app=game&heapwatch=1&p61check=20&p69free=1$Q$X" $(( (W + 19000) / 1000 ))
