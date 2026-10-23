#!/bin/bash
# P76: func_15037224 mutants on s7224.txt (mutfast.sh)
D=/Users/sorikairo/conker-wt/port/docs/port/sessions/p76
$D/mutfast.sh func_15037224 port_work/p76/7224.c $D/s7224.txt \
 's/            joint = 0xC;/            joint = 0xD;/' \
 's/                limits = 10;/                limits = 11;/' \
 's/            yOfs = -165.0f;/            yOfs = -160.0f;/' \
 's/(self + 0x84) == 7 ||/(self + 0x84) == 6 ||/' \
 's/                prefer = 0x7E;/                prefer = 0x7F;/' \
 's/                always = TRUE;//' \
 's/                mode = 1;/                mode = 2;/' \
 's/(self + 0x2E8) == 1/(self + 0x2E8) == 2/' \
 's/if (D_800BE616 != 0)/if (D_800BE616 == 2)/' \
 's/? 2 : 3;/? 3 : 3;/' \
 's/                later = FALSE;/                later = TRUE;/' \
 's/            postMul = TRUE;//' \
 's/            lookArg = 7;/            lookArg = 6;/' \
 's/(D_800C441A == 1) ? 3 : 5/(D_800C441A == 1) ? 3 : 4/' \
 's/D_80098418\[lookArg - 1\])\[4\]/D_80098418[lookArg - 1])[3]/' \
 's/D_800C4408\[1\] += yOfs;/D_800C4408[2] += yOfs;/' \
 's/} else if (D_800C441A == 0 || always) {/} else if (D_800C441A == 0) {/' \
 's/    D_800C441A++;//' \
 's/        case 0x44:/        case 0x44: case 0x45:/' \
 's/(s32) \&best, wrap, needVisible/(s32) \&best, 0, needVisible/'
