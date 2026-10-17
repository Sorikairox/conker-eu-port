#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_151DDF20(void) {
    s32 i;
    for (i = 0; i < 0x1C; i++) {
        D_800E1010[i] = D_800901F4[i];
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DDF6C.s")

s32 func_151DE074(s32 arg0) {
    return ~arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DE080.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DE100.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DEBB4.s")

void func_151DED3C(void);

void func_151DECB4(void) {
    D_800E0EC0 = 0;
    D_800E0FC7 = 0;
    D_800E0FC8 = 0;
    D_800E0EBC = 0;
    D_800901C8 = 2;
    func_151DED3C();
}

void func_151DECFC(void) {
    D_80090114 = 4;
    D_800E0FC6 = 0;
    if (D_800901D0 == 0) {
        func_1500764C();
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DED3C.s")

void func_151DEDC8(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DEDD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DF6A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DFD0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E06D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E0BBC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E1174.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E1308.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E19AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E1EDC.s")

void func_151E5AB8(void);
void func_151E4B40(void);

void func_151E2A1C(void) {
    D_80090120 = 3;
    func_151E5AB8();
    func_151E4B40();
    D_80090120 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2A54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2B9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2C88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2FCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E3864.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E3A1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E3AE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E49C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E4A78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E4B40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E533C.s")

void func_151E5528(void) {
    D_800E0B94 = 10;
}

void func_151E553C(void) {
    if (D_800E0FCA & 0x8020) {
        D_800E0B94 = 4;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E5564.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E55C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E564C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E5798.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E582C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E5928.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E5AB8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E5B94.s")

void func_151E5D28(void) {
    D_800843F0[0] = 0;
    D_800843F0[1] = 1;
    D_800843F0[2] = 2;
    D_800843F0[3] = 3;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E5D54.s")

void func_151E5DD8(void) {
    if (D_800E0EBC != 0) {
        D_800E0EBC = 0;
    }
}

s8 func_151E5DF8(void) {
    return D_80090168;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E5E08.s")

s32 func_151E6710(s32 arg0) {
    s8 var_v1;
    if ((D_800BE616 != 0) || (D_800E0B94 != 0)) {
        var_v1 = D_800E1030[arg0];
        if (var_v1 < 0) {
            var_v1 = 0;
        }
        return var_v1;
    }
    return arg0;
}

s8 func_151E6758(void) {
    if (D_800E101B != 0) {
        if (D_8008FD8C >= 5) {
            return D_80090130;
        }
        return D_8008FD8C;
    }
    return D_80090130;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E67A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E7110.s")

void func_151E73A8(void) {
    D_800E1003 = 0;
    D_800E1004 = 0;
    D_80090178 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E73C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E856C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E8648.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E86A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E870C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E8998.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E89C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E8A64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E8B94.s")
