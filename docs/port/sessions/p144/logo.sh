#!/bin/bash
# P144 (from p131 logo.sh): Chrome run without input: LogoScreen scene, shots every 1.5 s from 27 to 51 s (scope lens
# func_1518010C runs at frames ~1953..2100, the image draw from 1985).  logo.sh DIR [EXTRA_QUERY]
cd /Users/sorikairo/conker-wt/web || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
D=$1; mkdir -p "$D"
S=""; for t in $(seq ${T0:-27000} ${TS:-1500} ${T1:-51000}); do S="$S${S:+; }$t:shot:$D/logo_${t}ms.png"; done
PROBE_LOG=$D/chrome.log PROBE_ANGLE=metal PROBE_NOAUDIO=1 PROBE_SAMPLES=0 PROBE_STEPS="$S" \
  port/web/audprobe.sh "app=game&heapwatch=1&p78null=1&p103boot=1&p88scene=8&p144hits=1${2:-}" ${SECS:-55}
