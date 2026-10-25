#!/bin/bash
# P202: Chrome new-game run with an explicit shot list (ms, space-separated in SHOTS).  shots.sh DIR EXTRA_QUERY SECS   env PADF, SHOTS, P103
cd /Users/sorikairo/conker-wt/web || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
D=$1; T=${3:-150}; mkdir -p "$D"
S=""; for t in $SHOTS; do S="$S${S:+; }$t:shot:$D/s_${t}ms.png"; done
PROBE_LOG=$D/chrome.log PROBE_ANGLE=metal PROBE_NOAUDIO=1 PROBE_SAMPLES=0 PROBE_STEPS="$S" \
  port/web/audprobe.sh "app=game&heapwatch=1&p78null=1&${P103-p103boot=1&}p88scene=8&p123fade=1&padf=$PADF${2:-}" $T
