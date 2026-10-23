#!/bin/bash
# P126: Chrome run, events on, no fade wrap: LogoScreen -> title menu (level 0x1D); START (Enter) at 58 s and 76 s.  menu.sh DIR [EXTRA_QUERY]
cd /Users/sorikairo/conker-wt/web || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
D=$1; mkdir -p "$D"
S="58000:keydown:Enter; 58300:keyup:Enter; 76000:keydown:Enter; 76300:keyup:Enter"
for t in 30000 44000 52000 57000 60000 64000 70000 75000 78000 84000 90000; do S="$S; $t:shot:$D/menu_${t}ms.png"; done
PROBE_LOG=$D/chrome.log PROBE_ANGLE=metal PROBE_NOAUDIO=1 PROBE_SAMPLES=0 PROBE_STEPS="$S" \
  port/web/audprobe.sh "app=game&heapwatch=1&p78null=1&p103boot=1&p88scene=8&p123fade=1${2:-}" 94
