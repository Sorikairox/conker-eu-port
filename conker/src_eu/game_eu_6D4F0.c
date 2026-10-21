#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
extern s16 D_80084814;

void func_1503FCE0(s16 arg0, s16 *arg1, s16 *arg2) {
    s16 temp_v1;
    s16 temp_v1_3;
    s16 temp_v1_4;
    s16 var_v0;
    s16 var_v0_2;
    s8 temp_a0;
    s8 temp_v1_2;
    u8 *temp_v0;

    temp_v1 = D_80084814 - 1;
    temp_v0 = *(s32 *)(*D_800BE728 + (arg0 * 4));
    if (temp_v1 != 0) {
        D_80084814 = temp_v1;
        *arg1 = 0;
        *arg2 = 0;
        return;
    }
    temp_a0 = (*(s8 *)((u8 *)temp_v0 + 2));
    D_80084814 = 5;
    if ((temp_a0 < -0x14) || (temp_a0 >= 0x15)) {
        *arg1 = (s16) temp_a0;
    } else {
        *arg1 = 0;
    }
    temp_v1_2 = (*(s8 *)((u8 *)temp_v0 + 3));
    if ((temp_v1_2 < -0x14) || (temp_v1_2 >= 0x15)) {
        *arg2 = (s16) temp_v1_2;
    } else {
        *arg2 = 0;
    }
    (*(s8 *)((u8 *)temp_v0 + 2)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 3)) = 0;
    temp_v1_3 = *arg1;
    if (temp_v1_3 < -1) {
        *arg1 = -1;
    } else {
        var_v0 = temp_v1_3;
        if (temp_v1_3 >= 2) {
            var_v0 = 1;
        }
        *arg1 = var_v0;
    }
    temp_v1_4 = *arg2;
    if (temp_v1_4 < -1) {
        *arg2 = -1;
        return;
    }
    var_v0_2 = temp_v1_4;
    if (temp_v1_4 >= 2) {
        var_v0_2 = 1;
    }
    *arg2 = var_v0_2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6D4F0/func_1503FCE0.s")
#endif
void func_1503FB08(void) {
    D_80084818 = 0;
    D_800C6C70 = 0.0f;
    D_8008481C = 0;
    D_80084820 = 30;
    D_80084824 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6D4F0/func_1503FE30.s")
