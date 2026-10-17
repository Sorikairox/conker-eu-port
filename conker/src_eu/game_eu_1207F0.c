#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F2FE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F320C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F3294.s")

void func_150F3714(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

void func_150F3754(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x110, arg0 + 0x114, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F3794.s")

void func_15140410();

void func_150F38FC(u8 *arg0, s16 arg1) {
    func_15140410(arg0, arg0 + 0x12C, arg0 + 0x138, arg1);
}

typedef struct {
    u8 pad0[0x4F];
    u8 unk4F_7 : 7;
    u8 unk4F_0 : 1;
} struct_eu_150F3930;

void func_150F3930(struct_eu_150F3930 *arg0) {
    if (*(f32 *)((u8 *)D_800DBFF0 + 0x300) < -2000.0f) {
        arg0->unk4F_0 = 0;
        return;
    }
    arg0->unk4F_0 = 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F3978.s")

extern f32 D_800A1D50;
extern f32 D_800A1D54;

f32 func_150F3A20(s32 arg0, f32 arg1) {
    f32 var_f2;

    if (arg1 < -5.0f) {
        var_f2 = (arg1 * D_800A1D50) + D_800A1D54;
    } else {
        var_f2 = 0.75f;
    }
    return var_f2;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F3A74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F4970.s")
