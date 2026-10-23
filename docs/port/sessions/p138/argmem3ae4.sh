#!/bin/bash
# P138: func_151E3AE4's P120 setups (optionally only the names in a file) with DIFFTEST_ARGMEM on func_15049AD0.
# usage: argmem3ae4.sh OUTLOG [names.txt] [setups.txt]   env TR (default 4), AM (default 15049AD0=0:52)
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
f=func_151E3AE4; c=port_work/p138/cand_$f.c
bash docs/port/sessions/p132/cand.sh $f conker/src_eu/game_eu_20B730.c $c || exit 1
names=""; [ -n "$2" ] && names=$(cat $2)
DIFFTEST_ARGMEM=${AM:-15049AD0=0:52} TR=${TR:-4} KTAG=_p138 bash docs/port/sessions/p132/knobs.sh $f $c ${3:-docs/port/sessions/p120/3ae4_setups.txt} $names > $1 2>&1
echo "EQUIV $(grep -c ': EQUIV' $1) DIFFER $(grep -c ': DIFFER' $1) other $(grep -vc ': EQUIV\|: DIFFER' $1)"
