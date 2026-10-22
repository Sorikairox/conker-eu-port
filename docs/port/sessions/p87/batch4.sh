#!/bin/bash
# P87 batch 4: DB18 equal-return setups, ECA4 pos == end setups (eca4_*eq), func_15022A8C.
cd "$(dirname "$0")/../../../.."
P=docs/port/sessions/p87; W=port_work/p87
export DIFFTEST_ARGMEM="15049AD0=0:16"
TR=4 KTMP=build/difftest_p87k_db18 docs/port/sessions/p73/knobs.sh func_1501DB18 $P/func_1501DB18.c $P/db18eq.txt > $W/db18eq_knobs.log 2>&1
TR=4 docs/port/sessions/p82/mut.sh func_1501DB18 $P/func_1501DB18.c $P/db18eq.txt $P/surv_db18.txt > $W/db18_surv.log 2>&1
echo "db18 eq: setups $(grep -c EQUIV $W/db18eq_knobs.log)/$(wc -l < $W/db18eq_knobs.log), reruns $(grep -c KILLED $W/db18_surv.log) killed of $(wc -l < $W/db18_surv.log)"
grep eq $P/eca4.txt > $P/eca4eq.txt
TR=4 KTMP=build/difftest_p87k_eca4 docs/port/sessions/p73/knobs.sh func_1501ECA4 $P/func_1501ECA4.c $P/eca4eq.txt > $W/eca4eq_knobs.log 2>&1
TR=4 docs/port/sessions/p82/mut.sh func_1501ECA4 $P/func_1501ECA4.c $P/eca4eq.txt $P/surv_eca4b.txt > $W/eca4_surv2.log 2>&1
echo "eca4 eq: setups $(grep -c EQUIV $W/eca4eq_knobs.log)/$(wc -l < $W/eca4eq_knobs.log), $(cat $W/eca4_surv2.log | cut -c1-60)"
unset DIFFTEST_ARGMEM
docs/port/sessions/p87/run_all.sh func_15022A8C:a8c
echo "batch4 done"
