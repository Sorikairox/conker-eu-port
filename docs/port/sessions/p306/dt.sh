#!/bin/bash
# P306: difftest the current NM block of FUNC. usage: dt.sh FUNC TRIALS [extra difftest args]; knobs from env.
F=$1; N=${2:-100}; shift 2
R=${CONKER_ROOT:?}; cd "$R" || exit 2
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
C=port_work/p306_$F.c
NMBLOCK_WHOLE=1 python3 tools/port/nmblock.py $F $C > /dev/null || { echo "nmblock failed"; exit 2; }
DIFFTEST_SLOTS=1 DIFFTEST_TMP=build/dt306_$F tools/port/difftest.sh $F $C --trials $N --seed ${SEED:-1} "$@" 2>&1 | grep -v "^\s*$" | tail -${TL:-25} | cut -c1-${CUT:-300}
