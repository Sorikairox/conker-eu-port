#!/bin/bash
# P144: Chrome run, events on: LogoScreen -> title menu; START (Enter) at 58 s and 76 s -> new game (mode 0, level 0x18);
# P147: E1 / E2 = ms of the two STARTs (default 58000 / 76000; at 50 Hz use 69500 / 91000: the same frames 3369 / 4449 as P144). Runs SECS (default 150) s with shots every few seconds.  newgame.sh DIR [EXTRA_QUERY] [SECS]
cd /Users/sorikairo/conker-wt/web || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
D=$1; T=${3:-150}; mkdir -p "$D"
S="${E1:-58000}:keydown:Enter; $(( ${E1:-58000} + 300 )):keyup:Enter; ${E2:-76000}:keydown:Enter; $(( ${E2:-76000} + 300 )):keyup:Enter"
for t in 52000 64000 80000 $(seq 88000 3000 $(( (T-4)*1000 ))); do S="$S; $t:shot:$D/ng_${t}ms.png"; done
PROBE_LOG=$D/chrome.log PROBE_ANGLE=metal PROBE_NOAUDIO=1 PROBE_SAMPLES=0 PROBE_STEPS="$S" \
  port/web/audprobe.sh "app=game&heapwatch=1&p78null=1&p103boot=1&p88scene=8&p123fade=1${2:-}" $T
