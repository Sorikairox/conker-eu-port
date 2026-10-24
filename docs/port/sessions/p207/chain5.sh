#!/bin/bash
# P207 chain 5: func_150867D4 mutants
cd /Users/sorikairo/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
D=docs/port/sessions/p207
echo "### 67D4"; NORAND=1 TR=4 $D/mut.sh func_150867D4 $D/150867D4_cand.c $D/150867D4_setups.txt $D/150867D4_muts.txt
echo CHAIN DONE
