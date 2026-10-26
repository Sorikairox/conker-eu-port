#!/bin/bash
# P69: real-time Chrome run with the P69 checks: stand, B (KeyF), short walk (W), jump (Space), idle; screenshots.
#   port/web/p69shots.sh [OUTDIR] [START_MS=28000] [EXTRA_QUERY]
cd "$(dirname "$0")/../.." || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
D=${1:-$PWD/port_work/p69}; W=${2:-28000}; mkdir -p "$D"
S="$((W-500)):shot:$D/stand_$((W-500))ms.png; $W:keydown:KeyF; $((W+200)):keyup:KeyF"
for k in 1 2 3 4 5 6; do t=$((W + 200 * k)); S="$S; $t:shot:$D/b_${t}ms.png"; done
S="$S; $((W+2000)):keydown:KeyW"
for k in 1 2 3 4; do t=$((W + 2000 + 200 * k)); S="$S; $t:shot:$D/walk_${t}ms.png"; done
S="$S; $((W+2900)):keyup:KeyW; $((W+3300)):keydown:Space; $((W+3700)):keyup:Space"
for k in 1 2 3 4 5; do t=$((W + 3300 + 150 * k)); S="$S; $t:shot:$D/jump_${t}ms.png"; done
S="$S; $((W+6000)):shot:$D/idle_$((W+6000))ms.png"
PROBE_LOG=$D/chrome.log PROBE_ANGLE=metal PROBE_NOAUDIO=1 PROBE_SAMPLES=0 PROBE_STEPS="$S" \
  port/web/audprobe.sh "app=game&heapwatch=1&p63anim=1&p69look=6&p69attach=6&p69att=20&p69tri=10${3:-}" $(( (W + 9000) / 1000 ))
