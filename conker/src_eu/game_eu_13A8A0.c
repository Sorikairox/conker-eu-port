#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13A8A0/func_1510D090.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13A8A0/func_1510D338.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13A8A0/func_1510D3E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13A8A0/func_1510D66C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13A8A0/func_1510D8F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13A8A0/func_1510D984.s")

void func_1510DB88(s32 arg0, s32 arg1) {
    s8 *p = &D_800BC860[arg0];
    s8 v = *p;
    if (v != 0) {
        *p = (v & 0x40) | arg1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13A8A0/func_1510DBB0.s")

void func_1510DC14(s32 arg0) {
    u8 *temp_v0 = &D_800DA388[arg0];
    if (D_800BC860[arg0] != 0) {
        if (*temp_v0 != 0) {
            *temp_v0 = *temp_v0 - 1;
            if (*temp_v0 == 0) {
                if (arg0 < D_800DA378) {
                    D_800DA378 = arg0;
                }
                if (D_800DA37C < arg0) {
                    D_800DA37C = arg0;
                }
                func_1510DB88(arg0, 3);
            }
        }
    }
}

void func_1510DCA0(s32 arg0) {
    u8 *temp_v0 = &D_800DA388[arg0];
    if (D_800BC860[arg0] != 0) {
        if (*temp_v0 != 0) {
            *temp_v0 = *temp_v0 - 1;
            if (*temp_v0 == 0) {
                if (arg0 < D_800DA378) {
                    D_800DA378 = arg0;
                }
                if (D_800DA37C < arg0) {
                    D_800DA37C = arg0;
                }
                func_1510DB88(arg0, 2);
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13A8A0/func_1510DD2C.s")

extern s8 D_800DA2F0;

void func_1510DDE4(void) {
    D_800DA2F0 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13A8A0/func_1510DDF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13A8A0/func_1510DE40.s")
