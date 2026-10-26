#!/bin/bash
# P66: real-time Chrome frame sequence of Conker jumping (Space = A, held 400 ms) from the idle stance, then landing.
#   port/web/p66shots.sh [OUTDIR] [JUMP_MS=28000] [EXTRA_QUERY]
cd "$(dirname "$0")/../.." || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
D=${1:-$PWD/port_work/p66}; J=${2:-28000}; mkdir -p "$D"
S="$((J-600)):shot:$D/jump_00_$((J-600))ms.png; $J:keydown:Space; $((J+400)):keyup:Space"
for k in 01 02 03 04 05 06 07 08 09 10 11 12 13 14; do t=$((J + 100 * 10#$k)); S="$S; $t:shot:$D/jump_${k}_${t}ms.png"; done
S="$S; $((J+2500)):shot:$D/jump_15_$((J+2500))ms.png"
PROBE_LOG=$D/chrome_jump.log PROBE_ANGLE=metal PROBE_NOAUDIO=1 PROBE_SAMPLES=0 PROBE_STEPS="$S" \
  port/web/audprobe.sh "app=game&heapwatch=1&p66jump=2&p63anim=1&p66hud=5${3:-}" $(( (J + 5000) / 1000 ))
