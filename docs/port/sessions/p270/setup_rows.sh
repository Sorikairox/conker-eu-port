#!/bin/bash
# P270: memcpy fix in func_151CE3D0, mutant files and registry rows for the stride fixes
cd ~/conker-wt/port || exit 1
python3 - <<'EOF'
p='conker/src_eu/game_eu_1FB080.c'; s=open(p).read()
a='memcpy(temp_f12_2, sp.uBC, (s16 *) ((u8 *) sp.uBC - 0x20));  /* P270: byte offset (was s16 stride) */'
assert s.count(a)==1
s=s.replace(a,'memcpy(sp.uBC, (u8 *) sp.uBC - 0x20, 0x20);  /* P270: was memcpy(temp_f12_2, sp.uBC, sp.uBC - 0x20) (asm: a0 = sp.uBC, a1 = a0 - 0x20, a2 = 0x20) */')
open(p,'w').write(s)
EOF
D=docs/port/sessions/p270
w() { printf '%s\n' "$@"; }
w 's|(s16 \*) ((u8 \*) \([a-z_.A-Z0-9]*\) + 0x10)|\1 + 0x10|g' > $D/mstride_all.txt
w 's|(s16 \*) ((u8 \*) sp.uD8 - 0x60)|sp.uD8 - 0x60|' 's|sp.uD8 = (s16 \*) ((u8 \*) sp.uD8 + 0x10);|sp.uD8 += 0x10;|' > $D/m4810.txt
w 's|(s16 \*) ((u8 \*) sp.uAC - 0x40)|sp.uAC - 0x40|' 's|sp.uAC = (s16 \*) ((u8 \*) sp.uAC + 0x10);|sp.uAC += 0x10;|' > $D/m2f24.txt
w 's|(s16 \*) ((u8 \*) sp.uBC - 0x40)|sp.uBC - 0x40|' 's|memcpy(sp.uBC, (u8 \*) sp.uBC - 0x20, 0x20)|memcpy(sp.uBC, (u8 *) sp.uBC - 0x20, 0x10)|' 's|memcpy(sp.uBC, (u8 \*) sp.uBC - 0x20, 0x20)|memcpy(sp.uBC, sp.uBC - 0x20, 0x20)|' > $D/me3d0.txt
w 's|var_f14 = temp_f16_2 \* temp_f2_3;|var_f14 = (s32)temp_f16_2 * (s32)temp_f2_3;|' > $D/mcadc.txt
R=tools/port/verify_registry.tsv
row() { printf '%s\t%s\t\tDIFFTEST_ROMDATA=1 NR=200\t%s\tP270\n' "$1" "$2" "$3" >> $R; }
row func_150D4810 game_eu_101080 $D/mstride_all.txt,$D/m4810.txt
row func_151C3080 game_eu_1EFE10 $D/mstride_all.txt
row func_1519CADC game_eu_1C3530 $D/mstride_all.txt,$D/mcadc.txt
row func_151CE3D0 game_eu_1FB080 $D/mstride_all.txt,$D/me3d0.txt
row func_150E6920 game_eu_113D60 $D/mstride_all.txt
row func_15103438 game_eu_1306B0 $D/mstride_all.txt
row func_151B2F24 game_eu_1DFE20 $D/mstride_all.txt,$D/m2f24.txt
tail -8 $R | cut -f1,5
