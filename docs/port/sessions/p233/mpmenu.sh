#!/bin/bash
# P217: title-menu exploration in Chrome. mpmenu.sh DIR SECS  env PADF (frame script), SHOTS (ms list) default every 2 s from 60 s
cd /Users/sorikairo/conker-wt/web || exit 1
D=$1; T=${2:-120}
: ${SHOTS:="$(seq 60000 2000 $(( (T-4)*1000 )) | tr '\n' ' ')"}
SHOTS="$SHOTS" PADF="$PADF" docs/port/sessions/p233/shots.sh "$D" "${3:-}" "$T"
