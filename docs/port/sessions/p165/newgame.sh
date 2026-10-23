#!/bin/bash
# P165: env PADF overrides the whole pad script (padgen.py). P149: Chrome new-game run with FRAME-based input (?padf): START at retrace F1 (default 3386) and F2 (default 4458), held
# 15 retraces each (= P144's 58 / 76 s presses at 60 Hz, P147's E1 69500 / E2 91000 ms at 50 Hz). Events on:
# LogoScreen -> title intro -> GAME1 / NEW GAME menu -> new game (mode 0, level 0x18). Shots are still wall time.
#   newgame.sh DIR [EXTRA_QUERY] [SECS]   env F1 / F2 = retraces of the two STARTs
cd /Users/sorikairo/conker-wt/web || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
D=$1; T=${3:-150}; mkdir -p "$D"; F1=${F1:-3386}; F2=${F2:-4458}
P="${PADF:-$F1:1000:0:0,$((F1 + 15)):0:0:0,$F2:1000:0:0,$((F2 + 15)):0:0:0}"
S=""; for t in 52000 70000 80000 $(seq ${SHOTFROM:-88000} ${SHOTSTEP:-3000} $(( (T-4)*1000 ))); do S="$S${S:+; }$t:shot:$D/ng_${t}ms.png"; done
PROBE_LOG=$D/chrome.log PROBE_ANGLE=metal PROBE_NOAUDIO=1 PROBE_SAMPLES=0 PROBE_STEPS="$S" \
  port/web/audprobe.sh "app=game&heapwatch=1&p78null=1&p103boot=1&p88scene=8&p123fade=1&padf=$P${2:-}" $T
