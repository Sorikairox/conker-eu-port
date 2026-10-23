#!/bin/bash
# P134: re-run saved setup files against the current NM block. usage: rerun_setups.sh FUNC setups.txt [TR]
# prints a count line (EQUIV / DIFFER / other) and the non-EQUIV lines
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env port)"
f=$1; s=$2; mkdir -p port_work/p134/cand port_work/p134/rerun
src=$(grep -l "GLOBAL_ASM(\"asm/nonmatchings/[^/]*/$f.s\")" conker/src_eu/*.c | head -1)
c=port_work/p134/cand/$f.c; bash docs/port/sessions/p132/cand.sh $f $src $c
log=port_work/p134/rerun/${f}_$(basename $s .txt).log
TR=${3:-4} KTAG=_p134_$(basename $s .txt) bash docs/port/sessions/p132/knobs.sh $f $c $s > $log 2>&1
echo "$f $(basename $s): EQUIV $(grep -c ': EQUIV' $log) DIFFER $(grep -c ': DIFFER' $log) other $(grep -vc ': EQUIV\|: DIFFER' $log)"
grep -v ': EQUIV' $log | head -5 | cut -c1-250
