#!/bin/bash
# P200 chain: survivor re-runs and fixed-setup runs, one at a time
cd /Users/sorikairo/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
D=docs/port/sessions/p200
echo "### 6508 survivors (v2 setups)"; TR=4 NORAND=1 $D/mut.sh func_15086508 $D/15086508_cand.c $D/15086508_setups.txt $D/15086508_surv.txt
echo "### 6508 setups v2"; NOMUT=1 TR=4 $D/full.sh 15086508 | grep -v "^== random"
echo "### 8E84 setups (EU D_800BE616)"; NOMUT=1 TR=4 $D/full.sh 15088E84
echo "### 882C full (EU objects)"; TR=4 $D/full.sh 1508882C
echo "### F01C full"; TR=4 $D/full.sh 1517F01C
echo "### CFB90 full + ARGMEM"; DIFFTEST_ARGMEM=151559FC=0:17,151559FC=0+12:48,151559FC=0+44:1,151559FC=0+48:16,10023360=1:1,10023360=1+4:12 TR=4 $D/full.sh 150CFB90
echo CHAIN DONE
