#!/bin/bash
# P180: mutants of the func_1500BEC0 unit (TR=4; ROMDATA except func_1517BE0C, whose key word is poked)
cd "$(dirname "$0")/../../../.." ; D=docs/port/sessions/p180
for k in ${KEYS:-AD84 AF08 B1F4 B8F4 BAB8 BC7C B714 B3B0 BEC0 BE0C}; do
  f=func_1500$k; rd=1; [ $k = BE0C ] && { f=func_1517BE0C; rd=0; }; l=$(echo $k | tr A-Z a-z)
  echo "== $k"; DIFFTEST_ROMDATA=$rd TR=4 $D/mut.sh $f $D/${k}_cand.c $D/${l}_setups.txt $D/${l}_muts.txt
done
