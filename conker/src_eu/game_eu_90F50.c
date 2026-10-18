#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s16 func_15063740(u8 *arg0) {
    struct127 *temp_v0;

    temp_v0 = &D_800CC2D0[(*(u8 *)((u8 *)arg0 + 0x222))];
    return func_1505A630(temp_v0->x_position - (*(f32 *)((u8 *)arg0 + 0x14)), (*(f32 *)((u8 *)arg0 + 0x1C)) - temp_v0->z_position, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_150637B4.s")

s32 func_150836CC(struct127 *, s32);
void func_15063894(struct127 *arg0) {
    struct127 *temp_v0;
    temp_v0 = &D_800CC2D0[arg0 - D_800CC2D0];
    temp_v0->unk31C->unk78 = 0;
    temp_v0->unk31C->unk11A = 0;
    func_150836CC(arg0, 0x1D);
    func_150836CC(arg0, 0x1E);
    *((u8 *)arg0 + 0x8A) = 0;
    *((u8 *)arg0 + 0x89) = 0;
    *((u8 *)arg0 + 0x83) = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15063920.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_150639D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15063A54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15063AA0.s")

extern s16 D_800CC6D2;

s16 func_15063D6C(u8 *arg0) {
    D_800CC6D2 = ((*(u16 *)((u8 *)arg0 + 0x7A)) - (*(s16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x12))) - func_15063740(arg0);
    if (D_800CC6D2 >= 0x3E81) {
        D_800CC6D2 = 0x3E80;
    }
    if (D_800CC6D2 < -0x3E80) {
        D_800CC6D2 = -0x3E80;
    }
    return D_800CC6D2;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15063DE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15063F14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_1506401C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15064240.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_1506435C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15064594.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15064668.s")

void func_15064D5C(s32 arg0, s32 arg1) {
    f32 temp_f0;
    struct197 *temp_v0;
    struct197 *temp_v1;

    temp_v0 = D_800CC2D0[arg1].unk2D0;
    temp_v1 = D_800CC2D0[arg0].unk2D0;
    if ((temp_v0 != NULL) && (temp_v1 != NULL)) {
        temp_f0 = temp_v0->unk18;
        temp_v0->unk8 = temp_v1->unk8;
        if (temp_f0 <= temp_v0->unk8) {
            temp_v0->unk8 = temp_f0 - 1.0f;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15064DD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15064F50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_90F50/func_15065E18.s")
