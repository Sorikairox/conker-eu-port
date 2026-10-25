#!/bin/bash
# P271: det=2 new game, no taps after the Start presses; shots in SHOTS (ms).  run.sh DIR SECS [EXTRA_QUERY]
cd /Users/sorikairo/conker-wt/web || exit 1
export PADF='3386:1000:0:0,3401:0:0:0,4458:1000:0:0,4473:0:0:0'
export SHOTS="${SHOTS:-100000 110000 120000 130000 140000 150000 160000 170000 180000 190000}" P103="${P103-}"
/Users/sorikairo/conker-wt/web/docs/port/sessions/p240/shots.sh "$1" "&det=2&p174ev=1${3:-}" "${2:-200}"
