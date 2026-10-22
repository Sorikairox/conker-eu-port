#!/bin/bash
# usage: af10_knobs.sh [draft.c] -- func_1504AF10 (EU addresses; record = D_800CC2D0[2])
cd /Users/sorikairo/conker-wt/portb
eval "$(tools/eu_port/wt.sh env portb)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
D=${1:-port_work/p45/tAF10.c}
R=800CCD48
B="800DC324=80490000,800CCD5C=43480000,800CCD60=42C80000,800CCD64=C3160000,804903EF=000000FF"
for a in "0;0" "1;0" "0;1" "1;1"; do
for g in "800CCDD8=00000000" "800CCDD8=00073005" "800CCDD8=00078005" "800CCDD8=0007B005" "800CCDD8=00072005" "800CCDD8=FFF90006"; do
 for r in 0 3; do
 echo "$a $g r$r: $(DIFFTEST_EXACT='*' DIFFTEST_POKE="$B,$g" DIFFTEST_ARG="0=$R,1=${a%;*},2=${a#*;}" DIFFTEST_RET="1504AEF4=$r" DIFFTEST_OUTW="1504AEF4=1:6" tools/port/difftest.sh func_1504AF10 $D --trials 4 2>&1 | tail -1 | cut -c1-110)"
 done
done; done
