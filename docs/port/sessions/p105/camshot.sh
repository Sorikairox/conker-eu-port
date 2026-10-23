#!/bin/bash
# P105: Chrome shots at 31/33/35 s (pre-death fall camera) with the build in port/build/web.  camshot.sh DIR
cd /Users/sorikairo/conker-wt/web || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
D=$1; mkdir -p "$D"
S="29000:keydown:KeyW; 37000:keyup:KeyW"
for t in 31000 33000 35000; do S="$S; $t:shot:$D/cam_${t}ms.png"; done
PROBE_LOG=$D/chrome.log PROBE_ANGLE=metal PROBE_NOAUDIO=1 PROBE_SAMPLES=0 PROBE_STEPS="$S" \
  port/web/audprobe.sh "app=game&heapwatch=1&p78null=1" 38
