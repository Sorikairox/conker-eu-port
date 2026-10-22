#!/bin/bash
# usage: eed0knobs.sh draft.c [setups] -- func_1510EED0 (floor lookup) with a filled candidate table (EU addresses):
# out buffers at 0x80500000.., record 1 (0x800CCA1C), D_800D3720[0..3] = heights 45 / 55 / 120 / -20000, triangles in
# D_800DC26C = 0x80520000, flags D_800DBE5C = 0x80540000 (tri 1 = 8), objects D_800DBEF4 = 0x80550000, step 25.
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env portb)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
T="800D3720=00002D00,800D3724=80520000,800D3728=00000000,800D372C=00000001,800D3730=00003700,800D3734=8052000C,800D3738=00000000,800D373C=00000000,800D3740=00007800,800D3744=80520018,800D3748=00000000,800D374C=00000002,800D3750=FFB1E000,800D3754=80520024,800D3758=00000000,800D375C=00000001"
G="800DC26C=80520000,800DC28C=80540000,80540004=00000008,800DC294=41C80000,800DC324=80550000,80550044=00000000,800DC3C4=80560000,800CCB14=00000000"
for s in ${2:-a b c d e f g h i j}; do
 Y=42480000; A=42700000; F=0; AR=01000000; EB="1"; C3=3; X=""
 case $s in
  a) ;;                                    # area 0, all floors, came from above (y 50 < from 60)
  b) EB="0;1;0;1;1;0;1;0";;                # mixed floors / ceilings
  c) AR=01010101; EB="1;0";;               # all areas (2: objects, 3: records)
  d) F=1; EB="0;0;1;0;1";;                 # no fallback floor
  e) Y=42A00000; EB="1;1;0;1";;            # y 80 > from 60
  f) Y=42820000; A=42800000; EB="0;1;1;1";; # y 65, from 64 (h < y + step but above from)
  g) AR=00000101; X=",800CCB14=00000200";; # areas 2 / 3, record has +0xF8 & 0x200 (skip area 3)
  h) AR=01010101; EB="0";;                 # nothing is a floor (fallback / ceiling only)
  i) AR=00000001;;                          # area 3 only (records): +0x274 standing-on record, +0x19E
  j) X=",800D3730=00004600";;              # entry 1 at 70: in [from, from + step)
 esac
 echo "$s: $(DIFFTEST_TMP=build/difftest_eed0 DIFFTEST_EXACT='*' DIFFTEST_BUDGET=${BU:-60} \
  DIFFTEST_ARG="0=80500000,1=80500010,2=80500030,3=80500050,4=80500054,5=80500058,6=8050005C,7=42C80000,8=$Y,9=C1F00000,10=$A,11=3,12=800CCA1C,13=C2C80000,14=43480000,15=$F" \
  DIFFTEST_RET="150A3F50=$C3,1510EBF0=$EB,150A5480=2,150A48C0=2;4,150A6A48=80510000" \
  DIFFTEST_POKE="$T,$G,800894C0=$AR$X" tools/port/difftest.sh func_1510EED0 $1 --trials ${TR:-16} --seed ${SEED:-1} 2>&1 | grep -E "^(EQUIV|DIFFER|UNSURE|ERROR|CERR)" | cut -c1-200)"
done
