#!/bin/bash
# P207 chain 6: 67D4 setups v2 + survivors; 38CC setups v2 + survivors / fixed mutants
cd /Users/sorikairo/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
D=docs/port/sessions/p207
echo "### 67D4 setups v2"; TR=4 $D/knobs.sh func_150867D4 $D/150867D4_cand.c $D/150867D4_setups.txt | grep -v ': EQUIV'
echo "### 67D4 muts2"; NORAND=1 TR=4 $D/mut.sh func_150867D4 $D/150867D4_cand.c $D/150867D4_setups.txt $D/150867D4_muts2.txt
echo "### 38CC setups v2"; DIFFTEST_ROMDATA=1 TR=4 $D/knobs.sh func_150538CC $D/150538CC_cand.c $D/150538CC_setups.txt | grep -v ': EQUIV'
echo "### 38CC muts2"; DIFFTEST_ROMDATA=1 TR=4 $D/mut.sh func_150538CC $D/150538CC_cand.c $D/150538CC_setups.txt $D/150538CC_muts2.txt
echo CHAIN DONE
