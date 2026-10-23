#!/bin/bash
# P110: Chrome run without input (events on): LogoScreen scene on level 0x21, shots 20..50 s.  logo.sh DIR
cd /Users/sorikairo/conker-wt/web || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
D=$1; mkdir -p "$D"; S="1000:noop"
S=""; for t in 20000 30000 40000 46000 52000 60000 70000; do S="$S${S:+; }$t:shot:$D/logo_${t}ms.png"; done
PROBE_LOG=$D/chrome.log PROBE_ANGLE=metal PROBE_NOAUDIO=1 PROBE_SAMPLES=0 PROBE_STEPS="$S" \
  port/web/audprobe.sh "app=game&heapwatch=1&p78null=1&p103boot=1&p88scene=8&p113noguard=${NOG:-0}" 76
