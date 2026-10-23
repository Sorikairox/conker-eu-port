#!/bin/bash
# P147 (from p144; copy of p137): Chrome walk 29-37 s (death + respawn scene), second walk 46-54 s (0x2C warp); shots 44..62 s.
cd /Users/sorikairo/conker-wt/web || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
D=$1; mkdir -p "$D"
S="29000:keydown:KeyW; 37000:keyup:KeyW; 46000:keydown:KeyW; 54000:keyup:KeyW"
for t in $(seq 44000 1000 62000); do S="$S; $t:shot:$D/walk_${t}ms.png"; done
PROBE_LOG=$D/chrome.log PROBE_ANGLE=metal PROBE_NOAUDIO=1 PROBE_SAMPLES=0 PROBE_STEPS="$S" \
  port/web/audprobe.sh "app=game&heapwatch=1&p61check=20&p69free=1&p78null=1&p88scene=8&p81look=60${2:-}" 66
