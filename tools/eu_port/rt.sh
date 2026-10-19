#!/bin/bash
# usage: rt.sh <func> <draft.c>  -> repair_try + opcode-level shifts + first ** lines (compact)
eval "$(dirname $0)/wt.sh env ${WTNAME:-a}" 2>/dev/null
$(dirname $0)/repair_try.sh $1 $2 | head -${3:-3}
R=${CONKER_ROOT:-$HOME/conker}/tools/decomp-permuter/repair
python3 $(dirname $0)/opshift.py $R/$1.diff | head -${4:-12}
