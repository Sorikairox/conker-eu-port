#!/bin/bash
# P207 chain 3: mutants of func_150538CC (ROMDATA) and func_151B8EB8 (ARGMEM on the request)
cd /Users/sorikairo/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
D=docs/port/sessions/p207
echo "### 8EB8"; DIFFTEST_ARGMEM=151307F0=0:103 TR=4 $D/mut.sh func_151B8EB8 $D/151B8EB8_cand.c $D/151B8EB8_setups.txt $D/151B8EB8_muts.txt
echo "### 38CC"; DIFFTEST_ROMDATA=1 TR=4 $D/mut.sh func_150538CC $D/150538CC_cand.c $D/150538CC_setups.txt $D/150538CC_muts.txt
echo CHAIN DONE
