#!/bin/bash
# P252 (from P248, P245): boot with the P240 route EEPROM (save on level 0x29 after scene 5) and PLAY it: level 0x29 at ~4562 instead of
# the 11-minute new-game route.  r29load.sh DIR SECS [EXTRA_QUERY]   env PADX (pad events after 4600), SHOTS
cd /Users/sorikairo/conker-wt/web || exit 1
H=docs/port/sessions/p252
export PADF="3386:1000:0:0,3401:0:0:0,4458:1000:0:0,4473:0:0:0${PADX:+,$PADX}"
: ${SHOTS:=$(seq -s ' ' 100000 10000 $(( (${2:-200}-3)*1000 )))}
export SHOTS
$H/shots.sh "$1" "&eephex=$(cat port_work/p240/eep_last.hex)&p205obj=1${3:-}" "${2:-200}"
