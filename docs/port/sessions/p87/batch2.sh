#!/bin/bash
# P87 batch 2: ECA4 load-INVALID reruns, then setups + mutants of func_1501D044 / DB18 / E888 / 15020430.
cd "$(dirname "$0")/../../../.."
export DIFFTEST_ARGMEM="15049AD0=0:16,151695B0=0:1"
TR=4 docs/port/sessions/p82/mut.sh func_1501ECA4 docs/port/sessions/p87/func_1501ECA4.c docs/port/sessions/p87/eca4.txt docs/port/sessions/p87/surv_eca4.txt > port_work/p87/eca4_surv.log 2>&1
echo "eca4 reruns: $(grep -c KILLED port_work/p87/eca4_surv.log) killed of $(wc -l < port_work/p87/eca4_surv.log)"
docs/port/sessions/p87/run_all.sh func_1501D044:d044 func_1501DB18:db18 func_1501E888:e888 func_15020430:s20430
