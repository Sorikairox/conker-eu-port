#!/bin/bash
# usage: 16a4_knobs.sh [draft.c] [setups] -- func_150A16A4 (EU addresses), func_150A2280 = 0 / 1;0
cd /Users/sorikairo/conker-wt/portb
eval "$(tools/eu_port/wt.sh env portb)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
D=${1:-port_work/p45/t16A4.c}
for s in ${2:-a b c d e f g h}; do for r in "0" "1;0;0"; do
 echo "$s r$r: $(DIFFTEST_EXACT='*' DIFFTEST_POKE="$(python3 port_work/p45/k16a4.py $s)" DIFFTEST_ARG="0=800CC6F0" DIFFTEST_RET="150A2280=$r,1000E75C=1;0;1" tools/port/difftest.sh func_150A16A4 $D --trials ${TR:-4} 2>&1 | tail -1 | cut -c1-200)"
done; done
