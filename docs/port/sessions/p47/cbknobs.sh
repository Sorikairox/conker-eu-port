#!/bin/bash
# usage: cbknobs.sh draft.c [setups] -- func_1504CB98 with realistic pointers (EU addresses):
# record 0x80420000 (a0), its unk31C 0x80430000, camera (+0x318) 0x80440000, D_800CC6A4 -> pad 0x80450000.
cd "$(dirname "$0")/../.." && eval "$(tools/eu_port/wt.sh env portb)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
B="8042031C=80430000,80420318=80440000,800CC6A4=80450000"
for s in ${2:-a b c d e f g h i j k l}; do
 case $s in
  a) K="80430084=0";;                       # unk31C+0x84 == 0: no remote pad copy
  b) K="80430084=01000000,80420104=0";;     # +0x84 != 0, not stunned: func_15056B08 path
  c) K="80420318=0";;                       # no camera
  d) K="80430084=0,8043004C=00000000";;     # unk31C+0x4E kind 0
  e) K="80430084=0,8043004C=00000200";;     # kind 2
  f) K="80430084=0,80430094=00000000,80430020=0";;  # no zone teleport (+0x95), no +0x23 timer
  g) K="80430084=0,80430094=00010000,80420104=0,8044002C=0";;   # zone teleport (+0x95 = 1), not stunned, camera ok
  h) K="80430084=0,80430020=00000005";;    # +0x23 timer > 0 (pad reset)
  i) K="80430084=0,8042013C=70000000";;    # +0x13C >= 0x64
  j) K="80430084=0,804200AC=00010000";;    # in water (+0xAD)
  k) K="80430084=0,8043004C=00000100";;    # unk31C+0x4E kind 1
  l) K="80430084=0,80430108=0,80420110=0";;  # +0x110 == 0
 esac
 echo "$s: $(DIFFTEST_TMP=build/difftest_cb DIFFTEST_EXACT='*' DIFFTEST_BUDGET=${BU:-60} DIFFTEST_ARG="0=80420000" DIFFTEST_POKE="$B,$K" tools/port/difftest.sh func_1504CB98 $1 --trials ${TR:-32} --seed ${SEED:-1} 2>&1 | tail -1 | cut -c1-220)"
done
