#!/bin/bash
# P180: knobs.sh over the unit's setups with DIFFTEST_ROMDATA=1; prints a summary per function. usage: run_setups.sh KEY...
cd "$(dirname "$0")/../../../.." ; D=docs/port/sessions/p180
for k in "$@"; do
  f=func_1500$k; [ $k = BE0C ] && f=func_1517BE0C; s=$D/$(echo $k | tr A-Z a-z)_setups.txt
  o=$(DIFFTEST_ROMDATA=1 TR=${TR:-4} SEEDS="${SEEDS:-1 2}" $D/knobs.sh $f $D/${k}_cand.c $s)
  echo "$k: $(echo "$o" | grep -c ': EQUIV') EQUIV / $(echo "$o" | wc -l) runs"; echo "$o" | grep -v ': EQUIV' | cut -c1-250 | head -${SHOW:-6}
done
