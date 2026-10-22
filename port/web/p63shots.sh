#!/bin/bash
# P63: real-time Chrome frame sequence of Conker standing, walking (W held), stopping and idling.
#   port/web/p63shots.sh [OUTDIR] [WALK_START_MS] [EXTRA_QUERY]
cd "$(dirname "$0")/../.." || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
D=${1:-$PWD/docs/port/sessions/p63}; W=${2:-28000}; mkdir -p "$D"
S="$((W-1000)):shot:$D/stand_$((W-1000))ms.png; $((W-400)):shot:$D/stand_$((W-400))ms.png; $W:keydown:KeyW"
for k in 1 2 3 4 5 6 7 8 9 10; do t=$((W + 150 * k)); S="$S; $t:shot:$D/walk_${t}ms.png"; done
S="$S; $((W+1600)):keyup:KeyW; $((W+2000)):shot:$D/stop_$((W+2000))ms.png; $((W+2600)):shot:$D/idle_$((W+2600))ms.png; $((W+3600)):shot:$D/idle_$((W+3600))ms.png"
PROBE_LOG=$D/chrome_walk.log PROBE_ANGLE=metal PROBE_NOAUDIO=1 PROBE_SAMPLES=0 PROBE_STEPS="$S" \
  port/web/audprobe.sh "app=game&heapwatch=1&p63anim=2&p49walk=1&p49every=64${3:-}" $(( (W + 6000) / 1000 ))
