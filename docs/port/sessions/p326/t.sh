#!/bin/bash
# P326 (copy of p325/t.sh): one muted det=2 browser run through p320/run.sh, then a compact summary.
# t.sh NAME SECS PADF [EXTRA_QUERY e.g. &opt=skipcut:0]   (logs: port_work/p326/NAME/chrome.log)
cd ~/conker-wt/web || exit 1
D=port_work/p326/$1; rm -rf "$D"
PADF=$3 SHOTS="${SHOTS:-$(( ($2 - 5) * 1000 ))}" docs/port/sessions/p320/run.sh "$D" "$2" "$4" > "$D.out" 2>&1
L=$D/chrome.log
echo "== $1: $(grep -m1 '\[options\]' $L)"
echo "first scene end (cutscene 0) after 5600: $(grep '\[p88\] scene frame' $L | awk '{f=$4+0; if (f>5600 && /cutscene 0/) {print f; exit}}')"
echo "modes: $(grep -oE 'frame [0-9]+: mode [0-9]+ \(prev [0-9]+\) level [0-9A-F]+' $L | awk '{print $2 "m" $4 "L" $8}' | tr '\n' ' ' | cut -c1-500)"
echo "traps/aborts: $(grep -iE 'Aborted|RuntimeError|trap' $L | grep -vc 'no trap')  last frame: $(grep -oE 'frame [0-9]+' $L | tail -1)"
