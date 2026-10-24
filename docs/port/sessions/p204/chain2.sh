#!/bin/bash
# P204 chain 2: func_151A03DC survivors (new setups, ARGMEM on the flag byte), func_151096A0 and func_1000BF60 mutants
cd /Users/sorikairo/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
D=docs/port/sessions/p204
echo "### 03DC survivors"; DIFFTEST_ARGMEM=15143394=9:1 TR=4 NORAND=1 $D/mut.sh func_151A03DC $D/151A03DC_cand.c $D/151A03DC_setups.txt $D/151A03DC_surv.txt
echo "### 96A0"; DIFFTEST_ARGMEM=150A7C70=0:64,150A7E40=0:64 TR=4 $D/mut.sh func_151096A0 $D/151096A0_cand.c $D/151096A0_setups.txt $D/151096A0_muts.txt
echo "### BF60"; TR=4 $D/mut.sh func_1000BF60 $D/1000BF60_cand.c $D/1000BF60_setups.txt $D/1000BF60_muts.txt
echo CHAIN DONE
