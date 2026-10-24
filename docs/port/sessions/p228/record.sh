#!/bin/bash
# P228: record a human route on level 0x29 (the river crossing) and replay it.
#   record.sh url [PFRAME]            print the Chrome URL: the autopilot plays the new game up to scene 5 (B pad,
#                                     ~33900 retraces, ~11 min), hands the pad to the keyboard / gamepad at retrace
#                                     PFRAME (default 34200) and logs every pad change (?padrec=1).
#   record.sh replay FILE [SECS] [DIR] replay a recording headless (FILE = the text copied with copy(__padrec.join(',')))
#                                     with shots every 10 s from 680 s; default 1000 s, port_work/p228/replay.
# The recording keeps only entries after PFRAME (the prefix is replayed by the same autopilot, which is switched
# off for good at the F:P entry, see port/ultra/pc_pif.c). Retrace drift between runs is ~1 retrace (P223).
cd /Users/sorikairo/conker-wt/web || exit 1
H=docs/port/sessions/p228
PADF0=$(python3 $H/padwalk223.py bpad2 | sed -n 1p)
SCARE='1640:1300_1640:700_1400:560_900:480_400:560_200:900_200:1150_456:1400_920:1540'
GOTO="24000:70:8000:${SCARE}_t8000:50_894:970:10_t8000:30_t4000:6_t8000:20_t4000:3_894:1100"
case $1 in
url)
  PF=${2:-34200}
  echo "http://localhost:8064/index.html?app=game&padrec=1&p174ev=1&padf=$PADF0,$PF:P&p205goto=$GOTO"
  echo "(conker-web-serve serves port/build/web on 8064; load the ROM as usual or add &romurl=...)";;
replay)
  F=$2; T=${3:-1000}; D=${4:-port_work/p228/replay}; PF=${PFRAME:-34200}
  REC=$(tr -d ' \n"' < "$F" | tr ',' '\n' | awk -F: -v p=$PF '$1+0 > p' | paste -sd, -)
  export PADF="$PADF0,$PF:P${REC:+,$REC}"
  export SHOTS=$(seq -f %.0f 680000 10000 $(( (T-5)*1000 )) | tr '\n' ' ')
  echo "replay: $(tr ',' '\n' <<<"$REC" | wc -l | tr -d ' ') recorded entries after $PF -> $D"
  $H/shots.sh "$D" "&p205obj=1&p174ev=1&p205goto=$GOTO" "$T"
  python3 $H/sum.py "$D/chrome.log" | head -2;;
*) echo "record.sh url [PFRAME] | replay FILE [SECS] [DIR]   (env PFRAME for replay if not 34200)"; exit 2;;
esac
