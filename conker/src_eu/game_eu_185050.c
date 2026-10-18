#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185050/func_15157840.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185050/func_15157990.s")

s32 func_15157DD0(s32 arg0) {
    guMtxIdentF(&((f32 (*)[16])(arg0 + 0x7C))[D_800BE9C0]);
    return 1;
}

s32 func_15157580(s32, s32, f32, s32, s32, s32, s32, s32);
s32 func_15157E08(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8) {
    u8 *v = func_15157580(arg0, arg2, arg3, arg4, arg5, arg6 + 0x38, arg7, arg8);
    if (v == NULL) {
        return 0;
    }
    memcpy(v + 0x120, arg1, 0x38);
    return v;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185050/func_15157E88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185050/func_15158018.s")

void func_151582F8(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x4C, arg0 + 0x50, arg0);
}

s32 func_15158338(s32 arg0) {
    func_1515835C(arg0, arg0 + 0x120);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185050/func_1515835C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185050/func_151584F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185050/func_15158558.s")

void func_151585E8(s32 arg0, u8 arg1) {
    func_15169260(D_800A6440, 3, arg0, arg1);
}
