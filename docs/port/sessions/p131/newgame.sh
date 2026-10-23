#!/bin/bash
# P131: Chrome run, events on: LogoScreen -> title menu; START (Enter) at 58 s and 76 s -> new game (mode 0, level 0x18);
# runs SECS (default 150) s with shots every few seconds.  newgame.sh DIR [EXTRA_QUERY] [SECS]
# P149: STARTs are now FRAME-based (?padf): retraces F1=3386 / F2=4458 (env), held 15 retraces (= the 58 / 76 s presses
# at P131's 60 Hz pacing; at 50 Hz wall time they would be 69.5 / 91 s). WALLCLOCK=1 = the old Enter presses.
cd /Users/sorikairo/conker-wt/web || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
D=$1; T=${3:-150}; mkdir -p "$D"
F1=${F1:-3386}; F2=${F2:-4458}; Q="&padf=$F1:1000:0:0,$((F1 + 15)):0:0:0,$F2:1000:0:0,$((F2 + 15)):0:0:0"
S="58000:shot:$D/ng_58000ms.png"
[ -n "${WALLCLOCK:-}" ] && { S="58000:keydown:Enter; 58300:keyup:Enter; 76000:keydown:Enter; 76300:keyup:Enter"; Q=""; }
for t in 52000 64000 77000 78000 80000 84000 90000 $(seq 100000 10000 $(( (T-4)*1000 ))); do S="$S; $t:shot:$D/ng_${t}ms.png"; done
PROBE_LOG=$D/chrome.log PROBE_ANGLE=metal PROBE_NOAUDIO=1 PROBE_SAMPLES=0 PROBE_STEPS="$S" \
  port/web/audprobe.sh "app=game&heapwatch=1&p78null=1&p103boot=1&p88scene=8&p123fade=1$Q${2:-}" $T
