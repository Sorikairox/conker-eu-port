#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FDEC0/func_150D06B0.s")

u8 *func_150D0420(u8, s32, s16, s32, s32, s32, u8, s32);
s32 memcpy(s32, void *, s32);
void func_150D07C4(u8 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4) {    s32 sfpad;

    struct { f32 x; s16 y; } sp2C;
    u8 *temp_v0;
    sp2C.y = 0;
    sp2C.x = 0.0f;
    temp_v0 = func_150D0420(arg0, arg1, arg2, 8, 1, 0, arg3, arg4);
    if (temp_v0 != NULL) {
        memcpy((*(s32 *)((u8 *)temp_v0 + 0x48)), &sp2C, 8);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FDEC0/func_150D083C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FDEC0/func_150D09D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FDEC0/func_150D0A44.s")
