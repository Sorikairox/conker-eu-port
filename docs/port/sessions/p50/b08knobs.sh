#!/bin/bash
# usage: b08knobs.sh draft.c [setups] -- func_15056B08 with a realistic record (EU addresses):
# record 0x80420000 (a0), not stunned, D_800C3638 = 0 (no func_15022A8C), D_800D2528 -> 0x80460000 (all non-zero),
# D_800D2104 -> 0x80470000 (256 pointers to 0x80480000). Setups = unk223 kind (byte 0x223, 0x220..0x222 = 0) + extras.
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env portb)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
B="80420104=0,800C3A58=0,800D2528=80460000,80460000=01010101*64,800D2524=80470000,80470000=80480000*256"
for s in ${2:-0 1 2 3 4 5 6 7 8 9 A B C D E F 10 11 6a 1b 1c 1d 0e 5f 9e 9f}; do
 case $s in
  6a) K="80420220=00000006,8042022C=00010000";;          # kind 6 with unk22C & 1 (aim at the leader)
  1b) K="80420220=00000001,8042022C=00800000";;          # kind 1, +0x22C & 0x80 (height check)
  1c) K="80420220=00000004,80420240=00020000";;          # kind 4, unk241 != 0 (25-record scan)
  1d) K="80420220=00000001,8042025C=00000001";;          # kind 1, +0x25C & 1
  0e) K="80420220=00000000,8042025C=00000001";;          # kind 0, +0x25C & 1 (func_1505693C)
  9e) K="80420220=00000009,80420004=9E000000,8042022C=0,80420230=00000001,80420234=0,8042025C=0,8042003C=47000000,804201A4=0,804201A8=0,800CC704=0,800CC70C=0,8042023C=00FF0000,80420228=0,800C4298=01000000,80420240=0";;  # kind 9, id 0x9E: func_15047680 / func_15049440 view test
  9f) K="80420220=00000009,80420004=12000000,8042022C=0,80420230=00000001,80420234=0,8042025C=0,8042003C=47000000,804201A4=0,804201A8=0,800CC704=0,800CC70C=0,8042023C=00FF0000,80420228=0,800C4298=01000000,80420240=0";;  # same, other id: facing test with unk2CA
  5f) K="80420220=00000005,8042022C=00010000";;          # kind 5 with +0x22C & 1
  *) K="80420220=000000$(printf %02X $((16#$s)))";;
 esac
 echo "$s: $(DIFFTEST_TMP=build/difftest_b08 DIFFTEST_EXACT='*' DIFFTEST_BUDGET=${BU:-60} DIFFTEST_ARG="0=80420000" DIFFTEST_POKE="$B,$K" tools/port/difftest.sh func_15056B08 $1 --trials ${TR:-32} --seed ${SEED:-1} 2>&1 | tail -1 | cut -c1-200)"
done
