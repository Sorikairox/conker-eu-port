#!/bin/bash
# P223: one command to boot straight into a multiplayer mode in Chrome, from the P217 frame scripts (title -> MULTI
# barrel cellar -> mode pages). Race A = level 0x33 (mode 0 at ~7447 retraces), Total War = level 0x2D (~6607).
#   mp.sh race|war [DIR] [SECS] [EXTRA_QUERY]
#   default DIR port_work/p245/mp_<mode>, SECS 200 (race) / 180 (war); shots from the env file unless SHOTS is set.
#   env STICK=0 drops the stick / button presses after the mode starts (frame script cut at the mode-start retrace).
# Never run two Chrome runs at once: the second one hides the first tab and the port pauses it ("[page] tab hidden:
# paused"; P223 lost a river run that way).
# The env files are copies of p217/chR2.env (race.env: stick up + A taps from 8100) and p217/chW1.env (war.env).
cd /Users/sorikairo/conker-wt/web || exit 1
H=docs/port/sessions/p245
M=${1:-race}; case $M in race) E=$H/race.env; T0=200; CUT=7600;; war) E=$H/war.env; T0=180; CUT=6700;; *) echo "mode race|war"; exit 2;; esac
D=${2:-port_work/p245/mp_$M}; T=${3:-$T0}
S_OVR="$SHOTS"
source $E
[ -n "$S_OVR" ] && SHOTS="$S_OVR"
if [ "${STICK:-1}" = 0 ]; then
  PADF=$(echo "$PADF" | tr ',' '\n' | awk -F: -v c=$CUT '$1 < c' | paste -sd, -)
fi
# drop shots past the run end
SHOTS=$(for s in $SHOTS; do [ $s -lt $(( (T-3)*1000 )) ] && echo $s; done | tr '\n' ' ')
export PADF SHOTS
echo "mp.sh: $M -> $D ($T s, $(echo $PADF | tr ',' '\n' | wc -l | tr -d ' ') pad events, $(echo $SHOTS | wc -w | tr -d ' ') shots)"
$H/shots.sh "$D" "${4:-}" "$T"
L=$D/chrome.log
python3 $H/sum.py $L | head -3
grep -E "^\[p103\] frame [0-9]+: mode" $L | awk "{print \$3, \$4, \$5, \$8, \$9}" | uniq -f2 | head -12
grep -c '\[stub' $L | sed 's/^/stub lines: /'
