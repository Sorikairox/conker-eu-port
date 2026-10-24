#!/bin/bash
# P207 chain 4b: func_150B1200 setups v2 + mutants (survivors / sed errors / the rest)
cd /Users/sorikairo/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
D=docs/port/sessions/p207
export DIFFTEST_ROMDATA=1 DIFFTEST_ARGMEM=151D95C4=0:12,151D95C4=1:12,150B0F40=2:8,150B0F40=3:8
echo "### 1200 setups v2"; TR=4 $D/knobs.sh func_150B1200 $D/150B1200_cand.c $D/150B1200_setups.txt | grep -v ': EQUIV'
echo "### 1200 muts2"; TR=4 $D/mut.sh func_150B1200 $D/150B1200_cand.c $D/150B1200_setups.txt $D/150B1200_muts2.txt
echo CHAIN DONE
