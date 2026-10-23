#!/bin/bash
# P147: Chrome run, no input (LogoScreen -> title), ?p147pace=1 (pacing / audio log every 250 retraces), SECS (default 130) s.
#   pace.sh DIR [EXTRA_QUERY]
cd /Users/sorikairo/conker-wt/web || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
D=$1; mkdir -p "$D"
PROBE_LOG=$D/chrome.log PROBE_ANGLE=metal PROBE_SAMPLES=0 PROBE_GREP='\[p147\]|\[aud\]' PROBE_TAIL=40 PROBE_STEPS="${STEPS:-}" \
  port/web/audprobe.sh "app=game&p147pace=1${2:-}" ${SECS:-130}
