#!/bin/bash
# usage: 4950knobs.sh draft.c [setups] -- func_15044950 (wall cylinder) on record 1 (0x800CCA1C), EU addresses:
# word +0 kind, +4 bytes 4 / 5, +0xAD in-water, +0x28 float; D_8008FD8C (EU 0x8009012C) players.
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env portb)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
for s in ${2:-a b c d e f g h}; do
 k=1; b45=10000000; ad=00000000; f28=00000000; n=02000000
 case $s in
  a) k=2D;; b) b45=10050000;; c) ad=00010000;; d) b45=53000000;; e) b45=28000000;;
  f) f28=3F800000;; g) b45=25000000;; h) f28=3F800000; n=01000000;;
 esac
 K="800CCA1C=000000$k,800CCA20=$b45,800CCAC8=$ad,800CCA44=$f28,8009012C=$n"
 echo "$s: $(DIFFTEST_TMP=build/difftest_4950 DIFFTEST_EXACT='*' DIFFTEST_ARG="0=800CCA1C" DIFFTEST_POKE="$K" tools/port/difftest.sh func_15044950 $1 --trials ${TR:-16} --seed ${SEED:-1} 2>&1 | grep -E "^(EQUIV|DIFFER|UNSURE|ERROR)" | cut -c1-200)"
done
