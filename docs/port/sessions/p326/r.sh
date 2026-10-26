#!/bin/bash
# P326: one muted det=2 level-0x29 run from the P240 save (r29load.sh, level 0x29 at ~4562) with the ?p326 probe.
#   r.sh NAME SECS [EXTRA_QUERY e.g. &opt=longbreath:1&p205goto=...&p326sink=1]   env PADX (pad events after 4600)
# Waits for any other headless Chrome first (one Chrome run at a time). Prints the [p326] lines.
cd ~/conker-wt/web || exit 1
while [ "$(ps -axo command | grep -v grep | grep -c 'headless=new')" -gt 0 ]; do sleep 20; done
D=port_work/p326/$1; rm -rf "$D"
SHOTS="${SHOTS:-$(( ($2 - 5) * 1000 ))}" docs/port/sessions/p261/r29load.sh "$D" "$2" "&det=2&p326=1${3:-}" > "$D.out" 2>&1
L=$D/chrome.log
echo "== $1: $(grep -m1 '\[options\]' $L)"
grep '\[p326\]' $L | head -${MAXL:-60}
echo "traps/aborts: $(grep -iE 'Aborted|RuntimeError|trap' $L | grep -vc 'no trap')  last frame: $(grep -oE 'frame [0-9]+' $L | tail -1)"
