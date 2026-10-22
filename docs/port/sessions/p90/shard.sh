#!/bin/bash
# P90: run one shard (K of 2) of the s268bc.txt knob setups (own temp dir) with DIFFTEST_ARGMEM from argmem.txt;
# usage: shard.sh DRAFT OUT.log K [TR] ; env SKIP = log files whose setup names are skipped (already run), ONLY = names.
# Start the two shards as two separate background jobs (run_in_background), never with '&'.
cd /Users/sorikairo/conker-wt/port
S=docs/port/sessions/p90/s268bc.txt; D=$1; O=$2; K=$3; export TR=${4:-4}
export DIFFTEST_ARGMEM=$(cat docs/port/sessions/p90/argmem.txt)
all=${ONLY:-$(grep -vE '^\s*(#|$)' $S | awk '{print $1}')}
done=$( [ -n "$SKIP" ] && cat $SKIP | cut -d/ -f1 )
names=$(for n in $all; do echo "$done" | grep -qx "$n" || echo $n; done | awk -v k=$K '(NR+k)%2==0' | tr '\n' ' ')
KTAG=$K docs/port/sessions/p90/knobs.sh func_150268BC $D $S $names > $O 2>&1
echo "shard $K done: $(grep -c EQUIV $O) EQUIV, $(grep -vc EQUIV $O) other"
