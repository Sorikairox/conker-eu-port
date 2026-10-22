#!/bin/bash
# POKE is per aligned word: W ADDR HEX splits a byte string into words.
# usage: a834knobs.sh draft.c [setups] -- func_15021834 (actor to spawn marker) with real marker tables (EU addresses):
# arg0 = record 1 (0x800CCA1C), arg1 = 0, arg2 = -1; D_800C35EA[0] = 1, 2 markers, both kind 2 and func_15083E90 -> arg0.
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env portb)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
M0="42C80000412000004248000040400000429A000040000000BF0000004040000000000000000000000000000000000000000000004396000040A000000000000000000000"
M1="C2C8000041F00000C1200000BF800000C3C80000C0000000${R18:-3F800000}${R1C:-3F800000}0000000000000000000000000000000000000000C0A0000040A000000000000000000000"
W() { python3 -c "import sys; a=int(sys.argv[1],16); h=sys.argv[2]; print(','.join('%X=%s'%(a+i//2,h[i:i+8]) for i in range(0,len(h),8)))" $1 $2; }
B="800C3A08=00000100,800C3A58=00000200,800C39E8=80460000,80460000=00010001,800C3A10=80470000,$(W 80470000 00020500000000000002050000000000),800C3D78=80480000,$(W 80480000 ${M0}${M1}),800CCA1C=00000001,800CCD38=80490000,800CCB34=42C80000,800CCA34=4479C000"
for s in ${2:-a b c d}; do
 case $s in
  a) K="800C40A8=00000000";;                       # moving: xz_velocity = 2 * distance, in water
  b) K="800C40A8=01000000,800CCB34=C2C80000";;     # D_800C3C88 != 0 (velocity 0), water below the actor
  c) K="800C40A8=00000000,800CCD38=00000000";;     # no +0x31C record
  d) K="800C40A8=00000000,800CCA1C=00000002";;     # not a player (no water test)
 esac
 echo "$s: $(DIFFTEST_TMP=build/difftest_a834 DIFFTEST_EXACT='*' DIFFTEST_BUDGET=${BU:-60} DIFFTEST_ARG="0=800CCA1C,1=0,2=FFFFFFFF" DIFFTEST_RET="150842F8=800CCA1C" DIFFTEST_POKE="$B,$K" tools/port/difftest.sh func_15021834 $1 --trials ${TR:-16} --seed ${SEED:-1} -v 2>&1 | grep -E "EQUIV|DIFFER|UNSURE|ERROR|calls" | grep -E "^(EQUIV|DIFFER|UNSURE|ERROR)" | cut -c1-250)"
done
