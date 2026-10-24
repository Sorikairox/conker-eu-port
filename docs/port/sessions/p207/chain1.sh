#!/bin/bash
# P207 chain 1: func_1509E3D4 setups + mutants
cd /Users/sorikairo/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
D=docs/port/sessions/p207
echo "### 3D4"; DIFFTEST_ROMDATA=1 TR=4 $D/full.sh 1509E3D4
echo CHAIN DONE
