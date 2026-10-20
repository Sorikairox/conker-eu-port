#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted forward declaration(s) for func_150EBA04
s32 func_150EBA04(u8 *arg0, f32 *arg1, s32 arg2);



void func_150EB430(void *arg0, void *arg1, s32 arg2) {
    f32 sp1C[3];

    sp1C[0] = ((f32 *)arg1)[0] + ((f32 *)arg0)[0];
    sp1C[1] = ((f32 *)arg1)[1] + ((f32 *)arg0)[1];
    sp1C[2] = ((f32 *)arg1)[2] + ((f32 *)arg0)[2];
    func_150EBA04(arg0, sp1C, arg2);
}

s32 func_150A2D44(s32, s32);
s32 func_150EC200(u8 *, s32, s32);
extern s32 D_80088E40[];
extern s32 D_80088E50[];
extern s32 D_80088E70;

s32 func_150EBA04(u8 *arg0, f32 *arg1, s32 arg2) {
    s32 pad[2]; // fakematch: unused 8 bytes, the ref frame is 0x50
    struct127 *sp44;
    s32 *var_s0;
    s32 temp_lo;
    s32 temp_s2;
    s32 var_s1;

    sp44 = func_15083E90(9U);
    if (sp44 != NULL) {
        for (var_s1 = 0; var_s1 < 4; var_s1++) {
            temp_s2 = D_80088E40[var_s1];
            temp_lo = temp_s2 * 0x34;
            if (func_150A3990(temp_lo + D_800D34B8, arg0, arg1, arg2) != 0) {
                func_150A2D44(temp_s2, 1);
                sp44->unk2E8 = var_s1 + 1;
                func_150EC200(temp_lo + D_800D34B8, 0xFF, 1);
                return 1;
            }
        }
        for (var_s1 = 0; var_s1 < 8; var_s1++) {
            if (func_150A3990((D_80088E50[var_s1] * 0x34) + D_800D34B8, arg0, arg1, arg2) != 0) {
                return 1;
            }
        }
        return 0;
    }
    if (func_150A3990(D_800D34B8 + 0xF70, arg0, arg1, arg2) != 0) {
        (*(s32 *)((u8 *)D_800D34B8 + 0xF88)) = 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1191C0/func_150EBB94.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1191C0/func_150EBE44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1191C0/func_150EC200.s")
