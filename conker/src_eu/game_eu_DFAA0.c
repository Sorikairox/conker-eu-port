#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DFAA0/func_150B2290.s")

s32 func_1509BE40(s32, s32, s32, s32);

void func_150B2300(u8 *arg0) {
    u8 *temp_v0;

    if (func_1509BE40(1, 0x4054, 6, 0x9000) != 0) {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x10000);
    } else {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & 0xFFFEFFFF);
    }
    if ((func_1509BE40(1, 0x405C, 6, 0x9000) == 0) && (func_1509BE40(1, 0x405B, 6, 0x2000) != 0) && ((*(s32 *)((u8 *)arg0 + 0x2C)) != 0x40)) {
        temp_v0 = (*(u8 **)((u8 *)arg0 + 0x3D0));
        (*(f32 *)((u8 *)temp_v0 + 0x17C)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x180)) + 10.0f);
    }
}

void func_150B23C0(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    typedef struct { s32 w[3]; } Blk12;
    struct {
        Blk12 unk0;
        f32 unkC;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = *(Blk12 *)arg1;
    tmp.unkC = 0.0f;
    temp_v0 = func_15149130((func_150ADA20() % 133U) + 69, -1, 0x49, -1, 1, 0, 0x10, arg0[0xC], arg0[0x1]);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DFAA0/func_150B2470.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DFAA0/func_150B2820.s")
