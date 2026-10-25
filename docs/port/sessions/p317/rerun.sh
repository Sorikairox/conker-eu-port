#!/bin/bash
# P317: (1) the two DIFFTEST_MEMCPY selftest cases, (2) re-run (MUT=1, DIFFTEST_MEMCPY=1) the registry rows whose function
# memcpy's and whose recorded mutant count was incomplete, (3) the final checks (check.sh -> check3.out).
cd ~/conker-wt/portb && eval "$(tools/eu_port/wt.sh env portb)" && export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
D=docs/port/sessions/p317; C=$PWD/tools/port/difftest/cases/func_1501175C.c
S="DIFFTEST_ROMDATA=1 DIFFTEST_STKFILL=A5A5A5A5 DIFFTEST_ARG=0=80460000,1=00000012,2=00000001 DIFFTEST_POKE=8046003B=07000000,8046014C=41200000,80460150=42C80000 DIFFTEST_RET=151496A0=80470000,1513D860=80480000,150ADF00=00000003,15160830=80490000 DIFFTEST_ARGMEM=10023360=1:16@0"
sed 's/0.396174014f/0.396175f/' $C > port_work/p317/m175C.c
for m in 0 1; do for c in $C $PWD/port_work/p317/m175C.c; do echo "MEMCPY=$m $(basename $c): $(env $S DIFFTEST_MEMCPY=$m tools/port/difftest.sh func_1501175C $c --trials 8 2>&1 | grep -E '^(EQUIV|DIFFER|UNSURE|ERROR)' | cut -c1-120)"; done; done
DIFFTEST_MEMCPY=1 JOBS=2 tools/port/reverify_all.sh $(cat $D/memcpy_rerun.list)
echo CHECKS; $D/check.sh > $D/check3.out 2>&1; cat $D/check3.out; echo ALLDONE
