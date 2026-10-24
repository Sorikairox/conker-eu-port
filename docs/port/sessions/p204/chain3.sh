#!/bin/bash
# P204 chain 3: survivor re-runs with the added setups (setups first: must stay EQUIV)
cd /Users/sorikairo/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
D=docs/port/sessions/p204
echo "### 03DC inveps"; DIFFTEST_ARGMEM=15143394=9:1 TR=4 $D/knobs.sh func_151A03DC $D/151A03DC_cand.c $D/151A03DC_setups.txt inveps | cut -c1-120
DIFFTEST_ARGMEM=15143394=9:1 TR=4 NORAND=1 $D/mut.sh func_151A03DC $D/151A03DC_cand.c $D/151A03DC_setups.txt $D/151A03DC_surv2.txt
echo "### 96A0 cam_edge2"; DIFFTEST_ARGMEM=150A7C70=0:64,150A7E40=0:64 TR=4 $D/knobs.sh func_151096A0 $D/151096A0_cand.c $D/151096A0_setups.txt cam_edge2 | cut -c1-120
DIFFTEST_ARGMEM=150A7C70=0:64,150A7E40=0:64 TR=4 NORAND=1 $D/mut.sh func_151096A0 $D/151096A0_cand.c $D/151096A0_setups.txt $D/151096A0_surv.txt
echo "### BF60 new setups"; TR=4 $D/knobs.sh func_1000BF60 $D/1000BF60_cand.c $D/1000BF60_setups.txt m1_bit2 neg_last pan_hi first_m1 | cut -c1-120
TR=4 NORAND=1 $D/mut.sh func_1000BF60 $D/1000BF60_cand.c $D/1000BF60_setups.txt $D/1000BF60_surv.txt
echo CHAIN DONE
