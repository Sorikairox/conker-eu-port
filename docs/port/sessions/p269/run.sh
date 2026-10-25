#!/bin/bash
# P268: intro run with button taps during cutscenes.  run.sh DIR SECS BTNS(hex list cycled) PERIOD [EXTRA_QUERY]
cd /Users/sorikairo/conker-wt/web || exit 1
D=$1; T=$2; B=${3:-8000}; P=${4:-150}
PADF='3386:1000:0:0,3401:0:0:0,4458:1000:0:0,4473:0:0:0'
i=0; IFS=, read -ra BL <<< "$B"
for ((f=4700; f<20000; f+=P)); do b=${BL[$((i % ${#BL[@]}))]}; i=$((i+1)); PADF="$PADF,$f:$b:0:0,$((f+6)):0:0:0"; done
export PADF SHOTS="${SHOTS:-}" P103="${P103-}"
/Users/sorikairo/conker-wt/web/docs/port/sessions/p240/shots.sh "$D" "&p174ev=1&p205obj=1${5:-}" "$T"
