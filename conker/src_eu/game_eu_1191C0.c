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

#ifdef NON_MATCHING
void func_150E892C(void *, s16, u8, s32);
s32 func_15154728(f32 *, f32, f32, f32, f32, s32, s32);
s32 func_1516547C(s32, s32, s32, s32, s32);
void func_151D45A4(u8 *, u8, s32);
s32 func_151D5AC4(f32 *, s32, s32);

s32 func_150EC200(u8 *arg0, s32 arg1, s32 arg2) {
    struct {
        s8 u7C;
        u8 pad7D[0x1];
        s16 u7E;
        s8 u80;
        s8 u81;
        s8 u82;
        u8 pad83[0x9];
        f32 u8C;
        f32 u90;
        f32 u94;
    } sp;
    f32 temp_f20;
    f32 temp_f30;
    f32 var_f18;
    s32 temp_at;
    s32 temp_s1;
    s32 temp_t8;
    s32 temp_t9;
    s32 temp_v0;
    s32 var_s0;

    temp_s1 = arg1 & 0xFF;
    sp.u8C = (f32) (*(s16 *)((u8 *)arg0 + 0));
    sp.u90 = (f32) (*(s16 *)((u8 *)arg0 + 2));
    sp.u94 = (f32) (*(s16 *)((u8 *)arg0 + 4));
    temp_f30 = (f32) (*(s16 *)((u8 *)arg0 + 8)) * 0.5f;
    func_150E892C(&sp.u8C, (s16) ((func_150ADA20() % 101U) + 0x12C), temp_s1 & 0xFF, arg2);
    sp.u7C = 1;
    sp.u7E = (func_150ADA20() % 21U) + 0xF;
    sp.u80 = 0;
    sp.u82 = -1;
    sp.u81 = 1;
    func_151D8E18((structEU_151D8E18 *) &sp.u7C, 0, temp_s1 & 0xFF, arg2);
    func_1516547C(0, 0, 0, temp_s1 & 0xFF, arg2);
    var_s0 = 0;
    do {
        func_151D45A4(&sp.u8C, temp_s1 & 0xFF, arg2);
        func_151D5AC4(&sp.u8C, temp_s1 & 0xFF, arg2);
        temp_f20 = func_150ADA68();
        temp_t8 = (func_150ADA20() % 56U) + 0xC8;
        var_f18 = (f32) temp_t8;
        if (temp_t8 < 0) {
            var_f18 += 4294967296.0f;
        }
        temp_v0 = func_15154728(&sp.u8C, (temp_f20 * 4.0f) + 12.0f, 1.6409999f, var_f18, 0.0f, temp_s1, arg2);
        temp_t9 = (var_s0 + 1) & 0xFF;
        temp_at = temp_t9 < 2;
        var_s0 = temp_t9;
        sp.u90 += temp_f30;
    } while (temp_at != 0);
    return temp_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1191C0/func_150EC200.s")
#endif