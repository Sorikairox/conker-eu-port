#!/bin/bash
# P80: knobs + mutants of func_1507488C / func_1506EF5C / func_1506C32C (after the P80 splice fix)
D=/Users/sorikairo/conker-wt/port/docs/port/sessions/p80; P=/Users/sorikairo/conker-wt/port/port_work/p80
{ for f in func_1507488C:488c:s981e0 func_1506EF5C:ef5c:s981e0 func_1506C32C:c32c:sc32c; do
  IFS=: read F c s <<< "$f"; KTAG=_x TR=8 $D/knobs.sh $F port_work/p80/$c.c $D/$s.txt | awk -v F=$F '{print F, $0}'; done; } > $D/knobs_981e0.log 2>&1
$D/mut_981e0.sh > $D/mut_981e0.log 2>&1
MTAG=_z $D/mutfast.sh func_1506C32C port_work/p80/c32c.c $D/sc32c.txt 's/D_800D1C9C--;/D_800D1C9C -= 2;/' 's/n = 4;/n = 3;/' 's/(D_800D1580 >> 11) \& 0x7FF/(D_800D1580 >> 12) \& 0x7FF/' \
  's/0xFFFEF800/0xFFFFF800/' 's/D_800D1580 = v\[n\] | keep;/D_800D1580 = v[n];/' 's/if (v\[n\] != 0) {/if (v[n] == 0) {/' 's/func_1000F568(v\[0\], n) - v\[0\]/func_1000F568(v[0], n + 1) - v[0]/' \
  's/v\[0\] = D_800D1C9C \& 0x7FF;/v[0] = D_800D1C9C \& 0x3FF;/' 's/} else if (v\[1\] != 0) {/} else if (v[1] != 1) {/' >> $D/mut_981e0.log 2>&1
echo DONE; awk '{print $3}' $D/knobs_981e0.log | sort | uniq -c; grep -c KILLED $D/mut_981e0.log; grep -v KILLED $D/mut_981e0.log
