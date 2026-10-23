#!/bin/bash
# P161 copy of p158/chrome.sh. P149: Chrome noev walk with FRAME-based input (?padf): stick up retraces 1380-1780 (death + respawn scene) and
# 2230-2630 (0x2C warp, then level 0) = P144's 29-37 s / 46-54 s KeyW presses mapped to 50 Hz retraces
# (Chrome: retrace ~ 50 * t - 70 after boot). Shots wall time 44..62 s.  chrome.sh DIR [EXTRA_QUERY]  env PADF overrides
cd /Users/sorikairo/conker-wt/web || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
D=$1; mkdir -p "$D"; P=${PADF:-1380:0:0:80,1780:0:0:0,2230:0:0:80,2630:0:0:0}
S=""; for t in $(seq 44000 1000 62000); do S="$S${S:+; }$t:shot:$D/walk_${t}ms.png"; done
PROBE_LOG=$D/chrome.log PROBE_ANGLE=metal PROBE_NOAUDIO=1 PROBE_SAMPLES=0 PROBE_STEPS="$S" \
  port/web/audprobe.sh "app=game&heapwatch=1&p61check=20&p69free=1&p78null=1&p88scene=8&p81look=60&padf=$P${2:-}" 66
