#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F8DF0/func_150CB5E0.s")

s32 func_150CB6E0(s32 arg0, s32 arg1) {
    return 11;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F8DF0/func_150CB6F4.s")

s32 func_150CBCDC(u8 *arg0) {
    s16 temp_v0 = *(s16 *)(arg0 + 0x1C);
    if (temp_v0 < 32) {
        if ((temp_v0 * 8) < arg0[0x28]) {
            arg0[0x28] = temp_v0 * 8;
        }
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F8DF0/func_150CBD10.s")

s32 func_150CBF40(u8 *arg0) {
    f32 temp_f0;
    s16 temp_v0;
    s32 temp_v1;

    (*(s16 *)((u8 *)arg0 + 0x128)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x128)) - D_800BE9E4);
    if ((*(s16 *)((u8 *)arg0 + 0x128)) > 0) {
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x12C)) * D_800BE9A4;
        (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x2C)) + temp_f0);
        (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x30)) + temp_f0);
    }
    if ((*(s32 *)((u8 *)arg0 + 0x58)) & 1) {
        temp_v0 = (*(s16 *)((u8 *)arg0 + 0x1C));
        if (temp_v0 < 0x20) {
            temp_v1 = temp_v0 * 8;
            if (temp_v1 < (s32) (*(u8 *)((u8 *)arg0 + 0x5C))) {
                (*(u8 *)((u8 *)arg0 + 0x5C)) = (u8) temp_v1;
            }
        }
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F8DF0/func_150CBFCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F8DF0/func_150CC1F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F8DF0/func_150CC398.s")

void func_150CC46C(u8 *arg0) {
    *(s32 *)(arg0 + 0x58) |= 1;
    *(s16 *)(arg0 + 0x1C) = 0x20;
}
