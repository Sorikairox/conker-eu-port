#!/bin/bash
# P207 chain 4: func_150B1200 setups + mutants (ROMDATA, ARGMEM on the spawner's pos / vel and the side / fwd vectors)
cd /Users/sorikairo/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
D=docs/port/sessions/p207
export DIFFTEST_ROMDATA=1 DIFFTEST_ARGMEM=151D95C4=0:12,151D95C4=1:12,150B0F40=2:8,150B0F40=3:8
echo "### 1200"; TR=4 $D/full.sh 150B1200
echo CHAIN DONE
