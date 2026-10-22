#!/bin/bash
# usage: a9acknobs.sh draft.c [setups] -- func_1505A9AC (landing) on record 1 (EU 0x800CCA1C), +0x31C -> 0x800CD400 (inside record 3; 0x806xxxxx pokes are not applied).
# Words (EU): R+0x18 y, +0x20 y speed, +0x64 (byte 0x65), +0xAC (0xAD in water), +0x104 (stunned), +0x118, +0x184,
# +0x1C8 (0x1CA health), +0x1CC fall-start y, R+4 (id), +0x28, +0x84 (u16), +0xA8 (0xA9), +0x100 (byte); P+0x4C (byte 0x4F), P+0x78, P+0x120; D_800BE9F0 = 0x800BEE10.
# arg1 (floor y) is random in [-200, 200]: y = -500 lands, y = 500 is in the air.
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env portb)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
R=800CCA1C
for s in ${2:-a b c d e f g h i j k l m n o p q r}; do
 p4f=0; y=C3FA0000; yv=00000000; b65=00000000; wat=00000000; st=00000000; u118=00000000; u184=00000000
 hp=00000300; fy=00000000; id=01000000; p78=00000000; p120=00000000; lev=00000000; a8=00000000; u84=00000000
 u28=00000000; u100=00000000
 case $s in
  a) p4f=1; y=42C80000; u118=42C80000;;
  b) p4f=1; y=42C80000; u118=43480000; yv=C1F00000;;
  c) b65=00010000;;
  d) ;;
  e) u184=00001000; lev=00000014;;
  f) u184=00001000;;
  g) fy=44BB8000;;
  h) fy=43FA0000;;
  i) wat=00010000;;
  j) fy=44BB8000; u184=00002000;;
  k) y=43FA0000;;
  l) fy=44BB8000; id=75000000; hp=00000000;;
  m) fy=43FA0000; p78=21000000; st=01000000;;
  n) a8=00020000;;
  o) u84=003B0000; u184=0000000A;;
  p) u84=003C0000; u184=00000002; u28=40000000;;
  q) u28=40000000; u100=10000000; p78=25000000;;
  r) u28=40000000; u100=04000000; p78=21000000;;
 esac
 a() { printf '%X' $((0x$R + $1)); }
 K="$(a 0x18)=$y,$(a 0x20)=$yv,$(a 0x64)=$b65,$(a 0xAC)=$wat,$(a 0x104)=$st,$(a 0x118)=$u118,$(a 0x184)=$u184"
 K="$K,$(a 0x1C8)=$hp,$(a 0x1CC)=$fy,$(a 4)=$id,$(a 0x31C)=800CD400,800CD44C=$p4f,800CD478=$p78,800CD520=$p120,800BEE10=$lev,$(a 0xA8)=$a8,$(a 0x84)=$u84,$(a 0x28)=$u28,$(a 0x100)=$u100"
 echo "$s: $(DIFFTEST_TMP=build/difftest_a9ac DIFFTEST_EXACT='*' DIFFTEST_ARG="0=$R" DIFFTEST_POKE="$K" tools/port/difftest.sh func_1505A9AC $1 --trials ${TR:-16} --seed ${SEED:-1} 2>&1 | grep -E "^(EQUIV|DIFFER|UNSURE|ERROR)" | cut -c1-220)"
done
