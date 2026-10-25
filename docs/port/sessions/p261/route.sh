#!/bin/bash
# P261 (from P252): one level-0x29 route run (Chrome, one at a time).  route.sh NAME SECS GOTO_FILE [EXTRA_QUERY]
#   env DET (default 2: deterministic clock / AI / no wall budget, wall-paced VI; DET=0 = old wall-clock run), SHOTS
# Logs: port_work/p261/NAME/chrome.log; prints a compact summary (events, waypoints, stubs, hits, last positions).
cd /Users/sorikairo/conker-wt/web || exit 1
H=docs/port/sessions/p261; D=port_work/p261/$1
DET=${DET-2}; Q="&p248mesh=4700&p174ev=1&p223hit=60&p205goto=$(cat "$3")${DET:+&det=$DET}${4:-}"
[ "$DET" = 0 ] && Q="&p248mesh=4700&p174ev=1&p223hit=60&p205goto=$(cat "$3")${4:-}"
$H/r29load.sh "$D" "$2" "$Q" > port_work/p261/$1.out 2>&1
L=$D/chrome.log
echo "== $1 (det=${DET:-none})"; python3 $H/sum.py $L 2>/dev/null | head -12
grep -E '\[p174ev\] frame [0-9]+ ev [0-9]+ act6 id (50[0-9A-F][0-9A-F]|100[0-9A-F]) ' $L | awk '!s[$7 $8 $9]++' | head -14
grep -E 'waypoint [0-9]+ .*reached' $L | tail -4
grep -E '\[p205go\] retrace [0-9]+: wp' $L | tail -2
grep -E '\[p223hit\] call' $L | head -4
grep -E '^\[stub +[0-9]+\]' $L | head -20
