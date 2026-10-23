#!/bin/bash
# P114: all func_15024910 setups (ROM .data for the colour / kind tables), compact log. usage: runvm.sh CAND LOG
cd /Users/sorikairo/conker-wt/port
DIFFTEST_ROMDATA=1 DIFFTEST_ARGMEM=$(cat docs/port/sessions/p114/argmem.txt) TR=${TR:-4} docs/port/sessions/p114/knobs.sh func_15024910 $1 docs/port/sessions/p114/s24910.txt > $2 2>&1
echo DONE >> $2
