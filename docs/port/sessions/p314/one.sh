#!/bin/bash
# P314: run one setup of s5EC8.txt (registry knobs) against the current NM block, full verdict line. usage: one.sh NAME
F=func_15175EC8; SF=docs/port/sessions/p314/s5EC8.txt; SN=$1
R=${CONKER_ROOT:?}; cd "$R" || exit 2
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
kn=$(awk -F'\t' -v f="$F" '$1==f {print $4}' tools/port/verify_registry.tsv | tail -1)
envs=(); for k in $kn; do case $k in TR=*) ;; *) envs+=("$k");; esac; done
C=port_work/p314/one.c; NMBLOCK_WHOLE=1 python3 tools/port/nmblock.py $F $C > /dev/null
l=$(grep "^$SN " $SF); IFS='!' read -r n a p r rf ow ww wb <<< "$l"
sw=(); for kv in "DIFFTEST_ARG=$(echo $a)" "DIFFTEST_POKE=$(echo $p)" "DIFFTEST_RET=$(echo $r)" "DIFFTEST_RETF=$(echo $rf)" "DIFFTEST_OUTA=$(echo $ow)" "DIFFTEST_OUTW=$(echo $ww)" "DIFFTEST_OUTB=$(echo $wb)"; do [ -n "${kv#*=}" ] && sw+=("$kv"); done
env "${envs[@]}" "${sw[@]}" DIFFTEST_TMP=build/dt314one tools/port/difftest.sh $F $C --trials ${N:-2} --seed 1 "${@:2}" 2>&1 | grep -v "^\s*$" | tail -${TL:-6} | cut -c1-${CUT:-700}
