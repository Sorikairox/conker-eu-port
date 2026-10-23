#!/bin/bash
# P161: Chrome new game -> first room (padtongue.py: walk, jump, START = pause at retrace ~19300), shots while paused.
#   pause.sh DIR [EXTRA_QUERY] [SECS=420]
cd /Users/sorikairo/conker-wt/web || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
D=$1; T=${3:-420}; mkdir -p "$D"; P=$(python3 docs/port/sessions/p161/padtongue.py)
S=""; for t in 300000 372000 $(seq 384000 3000 $(( (T-4)*1000 ))); do S="$S${S:+; }$t:shot:$D/pz_${t}ms.png"; done
PROBE_LOG=$D/chrome.log PROBE_ANGLE=metal PROBE_NOAUDIO=1 PROBE_SAMPLES=0 PROBE_STEPS="$S" \
  port/web/audprobe.sh "app=game&heapwatch=1&p78null=1&p88scene=8&padf=$P${2:-}" $T
