#include <ultra64.h>
#include "functions.h"
#include "variables.h"


f32 func_15144BC8(f32);
f32 func_150ED750(f32 arg0, f32 arg1) {
    f32 temp_f0;
    f32 var_f2;
    arg0 = func_15144BC8(arg0);
    temp_f0 = func_15144BC8(func_15144BC8(arg1) - arg0);
    var_f2 = temp_f0;
    if (temp_f0 > 180.0f) {
        var_f2 = -360.0f + temp_f0;
    }
    return var_f2;
}

f32 func_150ED750(f32, f32);

void func_150ED7B4(u8 *arg0, u8 *arg1) {
    func_150ED750((f32) (func_1505A630((*(f32 *)((u8 *)arg1 + 0x14)) - (*(f32 *)((u8 *)arg0 + 0x14)), (*(f32 *)((u8 *)arg0 + 0x1C)) - (*(f32 *)((u8 *)arg1 + 0x1C)), 0) + 0x4000) * 0.005493164f, (*(f32 *)((u8 *)arg0 + 0x40)));
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11AF60/func_150ED818.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11AF60/func_150EDAF8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11AF60/func_150EDBB8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11AF60/func_150EDCC8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11AF60/func_150EF204.s")

void func_15104B60(u8 *, s32, f32);
s32 func_15052590(u8 *);
void func_150EF328(u8 *arg0) {
    if (arg0[5] != 3) {
        func_15104B60(arg0, 0xF, 250.0f);
        arg0[5] = 3;
        *(s16 *)(arg0 + 0xE4) = 0;
        arg0[0x125] = 0xFF;
    }
    func_15052590(arg0);
}
