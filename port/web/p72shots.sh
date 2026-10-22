#!/bin/bash
# P72: real-time Chrome walk through the checkpoint respawn (the P69 hang) to the level 0x2C warp; screenshots + log.
#   port/web/p72shots.sh [OUTDIR] [WALK_MS=29000] [HOLD_MS=8000] [EXTRA_QUERY]
#   env DENSE="FROM_MS TO_MS": extra shots every 200 ms in that window (the warp lasts ~80 frames)
cd "$(dirname "$0")/../.." || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
D=${1:-$PWD/docs/port/sessions/p72}; W=${2:-29000}; H=${3:-8000}; mkdir -p "$D"
S="$W:keydown:KeyW; $((W + H)):keyup:KeyW"
for k in $(seq 1 16); do t=$((W + 1000 * k)); S="$S; $t:shot:$D/walk_${t}ms.png"; done
if [ -n "${DENSE:-}" ]; then set -- $DENSE; for ((t = $1; t <= $2; t += 200)); do S="$S; $t:shot:$D/dense_${t}ms.png"; done; fi
PROBE_LOG=$D/chrome.log PROBE_ANGLE=metal PROBE_NOAUDIO=1 PROBE_SAMPLES=0 PROBE_STEPS="$S" \
  port/web/audprobe.sh "app=game&heapwatch=1&p61check=20&p69free=1${4:-}" $(( (W + 19000) / 1000 ))
