#!/bin/bash
# P245: mp.sh for any env file: mpx.sh ENV DIR SECS [EXTRA_QUERY]; env SHOTS (ms list) overrides; default shots every 10 s from 100 s.
cd /Users/sorikairo/conker-wt/web || exit 1
H=docs/port/sessions/p245
E=$1; D=$2; T=${3:-200}
S_OVR="$SHOTS"; source $E
SHOTS=${S_OVR:-$(seq -s ' ' 100000 10000 $(( (T-3)*1000 )))}
export PADF SHOTS
echo "mpx.sh: $E -> $D ($T s, $(echo $PADF | tr ',' '\n' | wc -l | tr -d ' ') pad events, $(echo $SHOTS | wc -w | tr -d ' ') shots)"
$H/shots.sh "$D" "${4:-}" "$T"
L=$D/chrome.log
python3 $H/sum.py $L | head -3
grep -E "^\[p103\] frame [0-9]+: mode" $L | awk "{print \$3, \$4, \$5, \$8, \$9}" | uniq -f2 | head -12
grep '^\[stub' $L | sed -E 's/^\[stub +[0-9]+\] (func_[0-9A-Fa-f]+ \([^)]*\)).*frame=([0-9]+).*/\2 \1/' | head -20
