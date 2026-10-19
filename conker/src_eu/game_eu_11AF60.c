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

void func_150EDAF8(u8 *arg0) {
    struct127 *temp_v1;
    u8 var_v0;
    u8 *temp_v0;
    struct108 *cam;
    temp_v0 = *(u8 **)(arg0 + 0x31C);
    if ((temp_v0 != NULL) && (temp_v0[0x84] == 0)) {
        if (D_800BE616 != 0) {
            var_v0 = arg0[0x127];
        } else {
            var_v0 = arg0[0x124];
        }
        if (((u16 **)D_800BE728[0])[var_v0][0] & 0x10) {
            temp_v1 = &D_800CC2D0[var_v0];
            if (*((u8 *)temp_v1->unk31C + 0x197) != 0) {
                cam = temp_v1->camera;
                if (cam != NULL) {
                    arg0[0x2FC] |= 1 << *((u8 *)cam + 0x23D);
                }
            }
        }
    }
}

s32 func_15062FC0(u8 *, s32, s32, s32, s32, s32, s32, s32);
void func_150EDBB8(u8 *arg0, s32 arg1, s32 arg2) {
    s32 t;
    s32 var_s0;
    arg1 = (arg1 < -0x2D) ? -0x2D : ((arg1 > 0x2D) ? 0x2D : arg1);
    arg2 = (arg2 < -0x2D) ? -0x2D : ((arg2 > 0x2D) ? 0x2D : arg2);
    if (arg0[4] == 0x28) {
        var_s0 = 0x7C;
    } else {
        t = arg1;
        arg1 = arg2;
        var_s0 = 0x1C;
        arg2 = t;
    }
    func_15062FC0(arg0, 0, 0, 0x800, 0x800, var_s0, -arg2 * 7, 0);
    func_15062FC0(arg0, 1, var_s0, 0x800, 0x800, var_s0, -arg1 * 7, 0);
}

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
