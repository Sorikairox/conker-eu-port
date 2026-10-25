#!/bin/bash
# P305: run FUNC's current NM block against one setup line (registry knobs) and print the verdict + detail lines.
# usage: run1.sh FUNC SETUPFILE SETUPNAME [extra K=V ...]   (after wt.sh env)
F=$1; SF=$2; SN=$3; shift 3
R=${CONKER_ROOT:-$HOME/conker}; cd "$R" || exit 2
kn=$(awk -F'\t' -v f="$F" '$1==f {print $4}' tools/port/verify_registry.tsv | tail -1)
envs=(); for k in $kn; do case $k in TR=*) ;; *) envs+=("$k");; esac; done
C=port_work/p305/r1_$F.c
NMBLOCK_WHOLE=1 python3 tools/port/nmblock.py $F $C > /dev/null
l=$(grep "^$SN " $SF); IFS='!' read -r n a p r rf ow ww wb <<< "$l"
sw=(); for kv in "DIFFTEST_ARG=$(echo $a)" "DIFFTEST_POKE=$(echo $p)" "DIFFTEST_RET=$(echo $r)" "DIFFTEST_RETF=$(echo $rf)" "DIFFTEST_OUTA=$(echo $ow)" "DIFFTEST_OUTW=$(echo $ww)" "DIFFTEST_OUTB=$(echo $wb)"; do [ -n "${kv#*=}" ] && sw+=("$kv"); done
env "${envs[@]}" "${sw[@]}" "$@" DIFFTEST_EXACT='*' DIFFTEST_TMP=build/dt305r tools/port/difftest.sh $F $C --trials ${TRN:-4} --seed 1 $DTV 2>&1 | grep -v "^\s*$" | tail -${NL:-12} | cut -c1-400
