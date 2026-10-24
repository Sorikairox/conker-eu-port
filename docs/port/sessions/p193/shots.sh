#!/bin/bash
# P193: before/after screenshots, one Chrome boot at a time: new game to level 0x29 (shots 52/70/80 s logo/menu/throne
# room, 90..590 s every 50 s) and the noev level-0 walk (chrome.sh), each with ?p193oldtc=1 (= the pre-P193 texture
# cache, "before") and without ("after").   shots.sh OUTDIR
cd /Users/sorikairo/conker-wt/web || exit 1
O=$1; mkdir -p "$O"
for v in before after; do
  Q=""; [ $v = before ] && Q="&p193oldtc=1"
  P103= PADF=$(python3 docs/port/sessions/p193/padwalk29.py) SHOTFROM=90000 SHOTSTEP=50000 \
    docs/port/sessions/p193/newgame.sh "$O/ng_$v" "$Q" 596 > "$O/ng_$v.out" 2>&1
  docs/port/sessions/p189/chrome.sh "$O/noev_$v" "$Q" > "$O/noev_$v.out" 2>&1
done
echo ALLDONE
