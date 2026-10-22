#!/bin/bash
# P76: func_150314B4 mutants on s14b4.txt (mutfast.sh)
D=/Users/sorikairo/conker-wt/port/docs/port/sessions/p76
$D/mutfast.sh func_150314B4 port_work/p76/14b4.c $D/s14b4.txt \
 's/if (att\[5\] == 0)/if (att[4] == 0)/' \
 's/alpha = (v \* alpha) >> 8;/alpha = (v * alpha) >> 7;/' \
 's/if (v != 0xFF)/if (v != 0xFE)/' \
 's/if (alpha < 0xFF)/if (alpha <= 0xFF)/' \
 's/col\[3\] = 0xFF;/col[3] = 0xFE;/' \
 's/ATT_DL(gfx, 0xD9FFFFFF, 0x20000);/ATT_DL(gfx, 0xD9FFFFFF, 0x20001);/' \
 's/!= 8 \&\& !(att\[4\] \& 1)/!= 4 \&\& !(att[4] \& 1)/' \
 's/} else if (D_800DCD7C != 0) {/} else if (D_800DCD7C == 0) {/' \
 's/? 10 : 2;/? 10 : 3;/' \
 's/obj\[5\] != 5 \&\&/obj[5] != 4 \&\&/' \
 's/(obj\[0x66\] \& 0xC) != 0 \&\& !created/!created/' \
 's/\*(f32 \*) (obj + 0x18), \*(f32 \*) (obj + 0x1C)/*(f32 *) (obj + 0x1C), *(f32 *) (obj + 0x18)/' \
 's/(D_800DD714\[1\] << 16)/(D_800DD714[2] << 16)/' \
 's/((primG \& 0xFF) << 16)/((primB \& 0xFF) << 16)/' \
 's/((envB \& 0xFF) << 8) | (alpha \& 0xFF)/((envB \& 0xFF) << 8) | (fogA \& 0xFF)/' \
 's/att + 0x28 + D_800BE9C0 \* 4/att + 0x2C + D_800BE9C0 * 4/' \
 's/ATT_DL(gfx, 0xDB06001C, v);/ATT_DL(gfx, 0xDB060018, v);/' \
 's/if (!(att\[0x13\] \& (1 << i)))/if (!(att[0x13] \& (2 << i)))/' \
 's/att, envR, envG, envB)/att, envR, envB, envG)/' \
 's/> D_800BEFC4) {/>= D_800BEFC4) {/' \
 's/return (s32) start;/return (s32) gfx;/' \
 's/D_800BE9C0 \* 8);/D_800BE9C0 * 4);/' \
 's/ATT_DL(gfx, 0xDB06000C, mtx);/ATT_DL(gfx, 0xDB06000C, mtx + 1);/'
