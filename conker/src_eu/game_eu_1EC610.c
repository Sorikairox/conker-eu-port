#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 func_151BF444(u8 *arg0);
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EC610/func_151BEE00.s")

s32 func_151BF0D0(u8 *arg0) {
    func_150A8050(((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0], 0.0f, *(f32 *)(arg0 + 0x120), 0.0f);
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][3][0] = *(f32 *)(arg0 + 0x54);
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][3][1] = *(f32 *)(arg0 + 0x58);
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][3][2] = *(f32 *)(arg0 + 0x5C);
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][0][0] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][0][1] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][0][2] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][1][0] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][1][1] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][1][2] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][2][0] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][2][1] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][2][2] *= 0.92300004f;
    return 1;
}

s32 func_151BF244(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4) {
    *arg4 = 1;
    return arg0;
}

#ifdef NON_MATCHING
f32 func_15143E64(f32 *);
void func_1515C710(u8 *, f32 *, f32 *, f32 *);
s32 func_151BF490(f32, s32, s32, u8, s32, s32, s32, s32, s32);
s32 func_151BF678(u8 *);
s32 func_151BF8F0(u8, u8);
extern s32 D_800D1968;

s32 func_151BF268(u8 *arg0) {
    struct {
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        s32 u98;
        f32 u9C;
    } sp;
    s32 var_s5;
    s32 var_v1;
    struct127 *var_s3;
    u8 temp_v0;
    u8 *temp_s1;

    var_s5 = 1;
    var_s3 = D_800CC2D0;
    do {
        if (func_151BF444((u8 *) var_s3) != 0) {
            temp_s1 = arg0 + 0x120;
            func_1515C710((u8 *) var_s3, &sp.u8C, &sp.u9C, &sp.u98);
            sp.u80 = sp.u8C - (*(f32 *)((u8 *)temp_s1 + 4));
            sp.u84 = sp.u90 - (*(f32 *)((u8 *)temp_s1 + 8));
            sp.u88 = sp.u94 - (*(f32 *)((u8 *)temp_s1 + 0xC));
            if ((func_15143E64(&sp.u80) - sp.u9C) < 43.0f) {
                var_s5 = 0;
                func_15085710((s16) var_s3->unk127, 3, (s32) (*(u8 *)((u8 *)temp_s1 + 0x10)));
                func_10010F30(0x511, 0x7D00U, 0x40U, 0, 0U);
                func_151BF8F0((*(u8 *)((u8 *)arg0 + 0xC)), (*(u8 *)((u8 *)arg0 + 1)));
                func_151BF678(temp_s1 + 4);
                temp_v0 = (*(u8 *)((u8 *)arg0 + 0x48));
                var_v1 = 0;
                switch (temp_v0) {                  /* irregular */
                case 0:
                    break;
                default:
                    var_v1 = 0;
                    if (temp_v0 != 3) {

                    }
                    break;
                case 1:
                    var_v1 = 1;
                    break;
                case 2:
                    var_v1 = 2;
                    break;
                }
                func_151BF490((*(f32 *)((u8 *)temp_s1 + 0)), arg0 + 0x54, (*(s32 *)((u8 *)arg0 + 0xFC)), (*(u8 *)((u8 *)arg0 + 0x11B)), var_v1, (*(u8 *)((u8 *)arg0 + 0x10)) & 0x10, (*(s32 *)((u8 *)arg0 + 0x60)), (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            }
        }
        var_s3 = (struct127 *)((u8 *)var_s3 + (0x32C));
    } while ((s32)var_s3 != (s32)&D_800D1968);
    return var_s5;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EC610/func_151BF268.s")
#endif
s32 func_151BF444(u8 *arg0) {
    if (arg0[0x127] == 0xFF) {
        return 0;
    }
    if (*(s32 *)arg0 == 0) {
        return 0;
    }
    if (arg0[4] == 0xFF) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EC610/func_151BF490.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EC610/func_151BF678.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EC610/func_151BF8F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EC610/func_151BFDCC.s")

void func_151C00DC(u8 *arg0) {
    u8 *new_var; // fakematch: pointer temp keeps arg0 out of s-regs (permuter artifact)
    struct102 *temp_a0;
    u8 *v;
    s32 i;
    new_var = arg0 + 0x28;
    if (*(s32 *)new_var != 0) {
        func_1516972C((struct102 *)*(s32 *)new_var);
    }
    v = arg0 + 0x28;
    i = 0;
    do {
        temp_a0 = *(struct102 **)((v + 4) + (i * 4));
        if (temp_a0 != 0) {
            func_1516972C(temp_a0);
        }
        i = (i + 1) & 0xFF;
    } while (i < 2);
}

void func_151C0154(struct260 * arg0) {
    func_151C00DC(arg0);
    func_1514933C(arg0);
}

void func_151C0180(struct260 * arg0) {
    func_151C00DC(arg0);
    func_15149368(arg0);
}

void func_151C01AC(struct102 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x57) {
        func_1516972C(arg0);
    }
}
