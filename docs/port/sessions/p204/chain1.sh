#!/bin/bash
# P204 chain: mutants of func_151D7814 (ROMDATA) and func_150F5FD4, one at a time
cd /Users/sorikairo/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
D=docs/port/sessions/p204
echo "### 7814"; DIFFTEST_ROMDATA=1 TR=4 $D/mut.sh func_151D7814 $D/151D7814_cand.c $D/151D7814_setups.txt $D/151D7814_muts.txt
echo "### 5FD4"; TR=4 $D/mut.sh func_150F5FD4 $D/150F5FD4_cand.c $D/150F5FD4_setups.txt $D/150F5FD4_muts.txt
echo CHAIN DONE
