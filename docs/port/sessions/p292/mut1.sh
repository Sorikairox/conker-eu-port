#!/bin/bash
# P292: run one mutant line (sed expr) of FUNC against one setup line of SETUPFILE with the registry knobs.
# usage: mut1.sh FUNC SETUPFILE SETUPNAME 'sed-expr'   (after wt.sh env)
F=$1; SF=$2; SN=$3; E=$4
R=${CONKER_ROOT:-$HOME/conker}; cd "$R" || exit 2
kn=$(awk -F'\t' -v f="$F" '$1==f {print $4}' tools/port/verify_registry.tsv | tail -1)
envs=(); for k in $kn; do case $k in TR=*) ;; *) envs+=("$k");; esac; done
C=port_work/m1_$F.c; M=port_work/m1_${F}_mut.c
NMBLOCK_WHOLE=1 python3 tools/port/nmblock.py $F $C > /dev/null
sed "$E" $C > $M; cmp -s $C $M && { echo "NOAPPLY $E"; exit 1; }
l=$(grep "^$SN " $SF); IFS='!' read -r n a p r rf ow ww wb <<< "$l"
sw=(); for kv in "DIFFTEST_ARG=$(echo $a)" "DIFFTEST_POKE=$(echo $p)" "DIFFTEST_RET=$(echo $r)" "DIFFTEST_RETF=$(echo $rf)" "DIFFTEST_OUTA=$(echo $ow)" "DIFFTEST_OUTW=$(echo $ww)" "DIFFTEST_OUTB=$(echo $wb)"; do [ -n "${kv#*=}" ] && sw+=("$kv"); done
env "${envs[@]}" "${sw[@]}" DIFFTEST_EXACT='*' DIFFTEST_TMP=build/dt292m tools/port/difftest.sh $F $M --trials 4 --seed 1 2>&1 | grep -E "^(EQUIV|DIFFER|UNSURE|ERROR)" | head -1 | cut -c1-200
