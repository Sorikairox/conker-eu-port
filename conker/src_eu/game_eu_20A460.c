#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20A460/func_151DCC50.s")

void func_151DCC50(u8 *arg0, u8 arg1, s32 arg2);

void func_151DCE6C(u8 *arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5) {
    typedef struct {
        s32 w[3];
    } Blk12;
    struct {
        Blk12 unk0;
        f32 unkC;
        u8 unk10;
    } tmp;
    struct260 *temp_v0;

    if (arg2 != 0) {
        func_151DCC50(arg0, arg4, arg5);
    }
    tmp.unk0 = *(Blk12 *)arg0;
    tmp.unkC = 0.0f;
    tmp.unk10 = arg3;
    temp_v0 = func_15149130(arg1, -1, 0x5B, -1, 1, 0, 0x14, arg4, arg5);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x14);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20A460/func_151DCF2C.s")
