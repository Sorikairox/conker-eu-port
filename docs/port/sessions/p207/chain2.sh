#!/bin/bash
# P207 chain 2: func_150538CC random + setups (no mutants)
cd /Users/sorikairo/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
D=docs/port/sessions/p207
echo "### 38CC setups"; DIFFTEST_ROMDATA=1 TR=4 $D/knobs.sh func_150538CC $D/150538CC_cand.c $D/150538CC_setups.txt
echo CHAIN DONE
