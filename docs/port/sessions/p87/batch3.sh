#!/bin/bash
# P87 batch 3: F6C reruns (load-INVALID + survivors, extra setups f6c2), C4C, A4C, P83 survivor setups.
cd "$(dirname "$0")/../../../.."
P=docs/port/sessions/p87; W=port_work/p87
TR=4 KTMP=build/difftest_p87k_f6c docs/port/sessions/p73/knobs.sh func_15020F6C $P/func_15020F6C.c $P/f6c2.txt > $W/f6c2_knobs.log 2>&1
TR=4 KTMP=build/difftest_p87k_f6c docs/port/sessions/p73/knobs.sh func_15020F6C $P/func_15020F6C.c $P/f6c.txt f6c_58 f6c_59 >> $W/f6c2_knobs.log 2>&1
echo "f6c extra setups: $(grep -c EQUIV $W/f6c2_knobs.log) EQUIV of $(wc -l < $W/f6c2_knobs.log)"
NORAND=1 TR=4 docs/port/sessions/p82/mut.sh func_15020F6C $P/func_15020F6C.c $P/f6call.txt $P/surv_f6c.txt > $W/f6c_surv.log 2>&1
echo "f6c reruns: $(grep -c KILLED $W/f6c_surv.log) killed of $(wc -l < $W/f6c_surv.log)"
TR=4 KTMP=build/difftest_p87k_ce34 docs/port/sessions/p73/knobs.sh func_1501CE34 docs/port/sessions/p83/func_1501CE34.c $P/ce34z.txt > $W/ce34z_knobs.log 2>&1
TR=4 docs/port/sessions/p82/mut.sh func_1501CE34 docs/port/sessions/p83/func_1501CE34.c $P/ce34z.txt $P/ce34z_mut.txt > $W/ce34z_mut.log 2>&1
TR=4 KTMP=build/difftest_p87k_317c docs/port/sessions/p73/knobs.sh func_1512317C docs/port/sessions/p83/func_1512317C.c $P/317c9.txt > $W/317c9_knobs.log 2>&1
TR=4 docs/port/sessions/p82/mut.sh func_1512317C docs/port/sessions/p83/func_1512317C.c $P/317c9.txt $P/317c9_mut.txt > $W/317c9_mut.log 2>&1
echo "P83 survivors: ce34 setups $(grep -c EQUIV $W/ce34z_knobs.log)/$(wc -l < $W/ce34z_knobs.log), $(cat $W/ce34z_mut.log | tr '\n' ' '); 317c setups $(grep -c EQUIV $W/317c9_knobs.log)/$(wc -l < $W/317c9_knobs.log), $(cat $W/317c9_mut.log | tr '\n' ' ')"
docs/port/sessions/p87/run_all.sh func_15022C4C:c4c
NORAND=1 docs/port/sessions/p87/run_all.sh func_15095A4C:a4c
echo "batch3 done"
