#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 func_151C4B0C(s32 arg0, u8 *arg1, f32 arg2);
void func_151C4AC0(u8 *arg0, u8 *arg1, f32 arg2);
s32 func_151C4990(u8 *arg0, u8 *arg1, f32 arg2);
void func_151C491C(s32 arg0, u8 *arg1, s32 arg2);
#endif
// hoisted forward declaration(s) for func_151C4B0C
extern void (*D_8008FF70[])(s32);


#ifdef NON_MATCHING
s32 func_1000B060(f32, f32, u32);
void func_1000E7A0(u32, s32);
s32 func_1510FE4C(s32);

void func_151C2600(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, f32 arg4) {
    struct {
        s32 u48;
        s32 u4C;
    } sp;
    s32 sp40;
    f32 sp34;
    f32 temp_f0;
    s16 temp_v0;
    s16 temp_v0_2;
    u8 *temp_v1;

    if (arg0 != NULL) {
        if ((D_800BE616 != 0) || (temp_v1 = (*(u8 **)((u8 *)arg0 + 0x318)), (temp_v1 == NULL))) {
            temp_v0 = (*(s16 *)((u8 *)D_800B0DF0 + 0x2C));
            if ((temp_v0 == 0x24) || (temp_v0 == 0x13) || (temp_v0 == 0x4D) || (temp_v0 == 0x85) || (temp_v0 == 0x93)) {
                func_100114D0((s32) (*(f32 *)((u8 *)arg1 + 0)), (s32) (*(f32 *)((u8 *)arg1 + 4)), (s32) (*(f32 *)((u8 *)arg1 + 8)), 0x7FFF, 0x3E8, 0x64, &sp.u4C, &sp.u48, NULL);
                if ((u32) sp.u48 >= 0x1001U) {
                    sp.u48 = (s32) ((u32) sp.u48 >> 7);
                    func_1000E7A0(8, (func_1510FE4C(arg3) + 1) | (sp.u48 << 8) | (sp.u4C << 0x10));
                }
            }
        } else {
            temp_v0_2 = (*(s16 *)((u8 *)D_800B0DF0 + 0x2C));
            if ((temp_v0_2 == 0x24) || (temp_v0_2 == 0x13)) {
                temp_f0 = 255.0f - (arg4 * 0.1f);
                if (temp_f0 > 16.0f) {
                    sp34 = temp_f0;
                    sp40 = func_1000B060((*(f32 *)((u8 *)arg2 + 0)), (*(f32 *)((u8 *)arg2 + 8)), (u32) ((*(f32 *)((u8 *)temp_v1 + 0x3A0)) * 40.743664f));
                    func_1000E7A0(8, (func_1510FE4C(arg3) + 1) | ((s32) temp_f0 << 8) | (sp40 << 0x10));
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C2600.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C284C.s")

#ifdef NON_MATCHING
s32 func_1000A420(s32, s32, s32, f32, s32, s32, s32, s32, s32, s32 *, s32 *, s32);
extern s32 D_8008FF88;

s8 func_151C2CE4(u8 *arg0) {
    struct {
        s32 uA4;
        s32 uA8;
        u8 padAC[0x1C];
        s32 uC8;
        struct108 * uCC;
        u8 padD0[0x7];
        s8 uD7;
    } sp;
    f32 sp70;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f6;
    f32 temp_f8;
    s32 temp_f6_2;
    s32 temp_f6_3;
    s32 temp_f6_4;
    s32 temp_v0;
    s8 var_v1;
    struct108 *var_a0;
    struct108 *var_t0;
    u16 temp_a0;
    u16 temp_a2;
    u8 *temp_s0;
    u8 *temp_a3;

    temp_s0 = arg0 + 0x110;
    sp.uD7 = 1;
    func_151C491C(arg0, temp_s0, D_800BE9E4);
    if (func_151C4990(arg0, temp_s0, D_800BE9A4) == 0) {
        sp.uD7 = 0;
    }
    func_151C4AC0(arg0, temp_s0, D_800BE9A4);
    if (func_151C4B0C((s32) arg0, temp_s0, D_800BE9A4) == 0) {
        sp.uD7 = 0;
    }
    if (((*(u8 *)((u8 *)(&arg0[0x110]) + 0xA0)) != 0) && (sp.uD7 == 1)) {
        sp.uC8 = 0;
        temp_a0 = (*(u16 *)((u8 *)(&arg0[0x110]) + 0x9E));
        if (temp_a0 == 0) {
            sp.uCC = NULL;
            temp_v0 = func_150ADA20();
            var_t0 = sp.uCC;
            var_v1 = 0;
            if (D_80082FA0 >= 0) {
                temp_a3 = ((temp_v0 & 7) * 4) + &D_8008FF88;
                temp_a2 = (*(u16 *)((u8 *)temp_a3 + 2));
                var_a0 = D_800DBFF0;
                temp_f18 = (*(f32 *)((u8 *)(&arg0[0x110]) + 0x98));
                sp70 = (f32) temp_a2 * temp_f18;
loop_9:
                temp_f8 = var_a0->unk2FC;
                temp_f6 = var_a0->unk300;
                temp_f12 = var_a0->unk2F8 - (*(f32 *)((u8 *)arg0 + 0x34));
                var_t0 = var_a0;
                var_a0 += 0x9A0;
                temp_f14 = temp_f8 - (*(f32 *)((u8 *)arg0 + 0x38));
                temp_f16 = temp_f6 - (*(f32 *)((u8 *)arg0 + 0x3C));
                temp_f2 = ((*(f32 *)((u8 *)(&arg0[0x110]) + 0x60)) * temp_f12) + (temp_f14 * (*(f32 *)((u8 *)(&arg0[0x110]) + 0x64))) + (temp_f16 * (*(f32 *)((u8 *)(&arg0[0x110]) + 0x68)));
                if ((temp_f2 < sp70) && (((f32) (temp_a2 - 0xA) * temp_f18) < temp_f2) && (temp_f0 = sqrtf((temp_f12 * temp_f12) + (temp_f14 * temp_f14) + (temp_f16 * temp_f16)), (temp_f0 != 0.0f)) && (temp_f0 < ((*(f32 *)((u8 *)(&arg0[0x110]) + 0x8C)) * temp_f18)) && ((temp_f2 / temp_f0) > 0.9f)) {
                    sp.uC8 = (s32) (*(u16 *)((u8 *)temp_a3 + 0));
                    (*(s8 *)((u8 *)(&arg0[0x110]) + 0xA1)) = var_v1;
                } else {
                    var_v1 += 1;
                    var_t0 = NULL;
                    if (D_80082FA0 < var_v1) {

                    } else {
                        goto loop_9;
                    }
                }
            }
        } else {
            sp.uCC = NULL;
            var_t0 = NULL;
            if (func_1000F3D0(temp_a0) != 0) {
                var_t0 = &D_800DBFF0[(*(u8 *)((u8 *)(&arg0[0x110]) + 0xA1))];
            } else {
                (*(s8 *)((u8 *)(&arg0[0x110]) + 0xA0)) = 0;
            }
        }
        if (var_t0 != NULL) {
            sp.uA8 = 0x40;
            temp_f6_2 = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - var_t0->unk2F8);
            temp_f6_3 = (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) - var_t0->unk2FC);
            temp_f6_4 = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - var_t0->unk300);
            func_1000A420(temp_f6_2, temp_f6_3, temp_f6_4, var_t0->unk380, temp_f6_2, temp_f6_3, temp_f6_4, 0x2710, 0x270F, &sp.uA8, &sp.uA4, 0);
            if (sp.uC8 != 0) {
                (*(u16 *)((u8 *)(&arg0[0x110]) + 0x9E)) = func_10010F30(sp.uC8, 0x6590U, sp.uA8 & 0x7F, 0, (u8) (sp.uA8 & 0x80));
            } else {
                func_1000F85C((*(u16 *)((u8 *)(&arg0[0x110]) + 0x9E)), 4, sp.uA8 & 0x7F);
                func_1000F85C((*(u16 *)((u8 *)(&arg0[0x110]) + 0x9E)), 0x100, sp.uA8 & 0x80);
            }
        }
    }
    return sp.uD7;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C2CE4.s")
#endif
#ifdef NON_MATCHING
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
s32 memcpy(s32, s32, s32);

s16 *func_151C3080(u8 *arg0, s16 arg1) {
    struct {
        u8 u53;
        u8 pad54[0x4];
        s16 * u58;
        s16 * u5C;
        u8 pad60[0x4];
        f32 u64;
        u8 pad68[0xC];
        f32 u74;
        f32 u78;
        f32 u7C;
        u8 pad80[0x18];
        f32 u98;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
    } sp;
    u8 *sp48;
    s32 sp44;
    f32 sp38;
    f32 sp34;
    f32 sp28;
    f32 *temp_v0;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f18;
    f32 temp_f18_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f8;
    f32 temp_f8_2;
    f32 var_f12;
    f32 var_f14;
    f32 var_f16;
    s16 *temp_t2;
    s16 *temp_t2_2;
    s16 *temp_t6;
    s32 temp_a1;
    u8 *temp_v1;
    u8 *temp_v1_2;

    func_151D6310(arg0 + 0x100, arg1, 0x40, &sp.u5C, &sp.u53);
    sp.u58 = sp.u5C;
    if (sp.u5C != NULL) {
        if (sp.u53 != 0) {
            temp_v1 = arg0 + (arg1 * 4);
            temp_a1 = arg0 + 0xC0;
            sp44 = temp_a1;
            sp48 = temp_v1;
            memcpy((*(s32 *)((u8 *)temp_v1 + 0x100)), temp_a1, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v1 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_v0 = func_15144B34((s32) arg1);
        temp_v1_2 = arg0 + 0x110;
        (*(f32 *)((u8 *)(&sp.uA4) + 0)) = (*(f32 *)((u8 *)arg0 + 0x34));
        (*(f32 *)((u8 *)(&sp.uA4) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 0x38));
        (*(f32 *)((u8 *)(&sp.uA4) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C));
        temp_f16 = (*(f32 *)((u8 *)arg0 + 0x34)) - (*(f32 *)((u8 *)temp_v1_2 + 0x10));
        temp_f18 = (*(f32 *)((u8 *)arg0 + 0x38)) - (*(f32 *)((u8 *)temp_v1_2 + 0x14));
        temp_f4 = (*(f32 *)((u8 *)arg0 + 0x3C)) - (*(f32 *)((u8 *)temp_v1_2 + 0x18));
        temp_f2 = temp_f16 - sp.uA4;
        sp.uA0 = temp_f4;
        temp_f12 = temp_f18 - sp.uA8;
        temp_f10 = ((temp_f2 * 0.5f) + sp.uA4) - (*(f32 *)((u8 *)temp_v0 + 0));
        sp.u74 = temp_f10;
        temp_f8 = ((temp_f12 * 0.5f) + sp.uA8) - (*(f32 *)((u8 *)temp_v0 + 4));
        sp.u78 = temp_f8;
        temp_f14 = temp_f4 - sp.uAC;
        sp28 = temp_f10;
        sp.u9C = temp_f18;
        temp_f4_2 = ((temp_f14 * 0.5f) + sp.uAC) - (*(f32 *)((u8 *)temp_v0 + 8));
        sp.u98 = temp_f16;
        sp.u7C = temp_f4_2;
        temp_f18_2 = (temp_f12 * temp_f4_2) - (temp_f8 * temp_f14);
        temp_f16_2 = (temp_f14 * sp28) - (temp_f4_2 * temp_f2);
        sp38 = temp_f16_2;
        temp_f8_2 = (temp_f2 * temp_f8) - (sp28 * temp_f12);
        sp34 = temp_f8_2;
        temp_f0 = (temp_f18_2 * temp_f18_2) + (temp_f16_2 * temp_f16_2) + (temp_f8_2 * temp_f8_2);
        sp.u64 = temp_f0;
        if (temp_f0 == 0.0f) {
            var_f16 = 0.0f;
            var_f12 = 0.0f;
            var_f14 = 0.0f;
        } else {
            temp_f2_2 = (*(f32 *)((u8 *)arg0 + 0x2C)) / sqrtf(temp_f0);
            var_f12 = temp_f18_2 * temp_f2_2;
            var_f14 = sp38 * temp_f2_2;
            var_f16 = sp34 * temp_f2_2;
        }
        (*(s16 *)((u8 *)sp.u5C + 0)) = (s16) (s32) (sp.uA4 - var_f12);
        (*(s16 *)((u8 *)sp.u5C + 2)) = (s16) (s32) (sp.uA8 - var_f14);
        (*(s16 *)((u8 *)sp.u5C + 4)) = (s16) (s32) (sp.uAC - var_f16);
        (*(u8 *)((u8 *)sp.u5C + 0xF)) = (u8) (*(u8 *)((u8 *)arg0 + 0x5C));
        (*(s16 *)((u8 *)sp.u5C + 6)) = 0;
        temp_t2 = sp.u5C + 0x10;
        sp.u5C = temp_t2;
        *temp_t2 = (s16) (s32) (sp.u98 - var_f12);
        (*(s16 *)((u8 *)sp.u5C + 2)) = (s16) (s32) (sp.u9C - var_f14);
        (*(s16 *)((u8 *)sp.u5C + 4)) = (s16) (s32) (sp.uA0 - var_f16);
        (*(u8 *)((u8 *)sp.u5C + 0xF)) = 0U;
        (*(s16 *)((u8 *)sp.u5C + 6)) = 0;
        temp_t2_2 = sp.u5C + 0x10;
        sp.u5C = temp_t2_2;
        (*(s8 *)((u8 *)temp_t2_2 + 0xF)) = 0;
        (*(s16 *)((u8 *)temp_t2_2 + 6)) = 0;
        (*(s16 *)((u8 *)temp_t2_2 + 0)) = (s16) (s32) (sp.u98 + var_f12);
        (*(s16 *)((u8 *)temp_t2_2 + 2)) = (s16) (s32) (sp.u9C + var_f14);
        (*(s16 *)((u8 *)temp_t2_2 + 4)) = (s16) (s32) (sp.uA0 + var_f16);
        temp_t6 = temp_t2_2 + 0x10;
        sp.u5C = temp_t6;
        *temp_t6 = (s16) (s32) (sp.uA4 + var_f12);
        (*(s16 *)((u8 *)sp.u5C + 2)) = (s16) (s32) (sp.uA8 + var_f14);
        (*(s16 *)((u8 *)sp.u5C + 4)) = (s16) (s32) (sp.uAC + var_f16);
        (*(u8 *)((u8 *)sp.u5C + 0xF)) = (u8) (*(u8 *)((u8 *)arg0 + 0x5C));
        (*(s16 *)((u8 *)sp.u5C + 6)) = 0;
        return sp.u58;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C3080.s")
#endif
s32 func_151C33FC(u8 *arg0, u8 *arg1) {
    if (arg0 == arg1) {
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

s32 func_151C3444(u8 *arg0, u8 *arg1) {
    if (arg0 == arg1) {
        return 0;
    }
    if (*(s32 *)arg0 == 0) {
        return 0;
    }
    if (arg0[4] == 0xFF) {
        return 0;
    }
    if (arg0[0x127] == 0xFF) {
        return 0;
    }
    return 1;
}

void func_151C34A0(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_151D535C(arg0, arg1, arg3, arg4, arg5, *(s32 *)(arg2 + 0x1B4), arg2 + 0x170, arg2[0xC], arg2[1]);
}

#ifdef NON_MATCHING
s32 func_15102EA0(f32, s32, u8 *, u8 *, s32, s32, s32, s32, s32, s32);
s32 func_151530A8(s32 *, u8, u8);
extern u8 D_800DCE50;
extern f32 D_800DCE54;

void func_151C34F8(u8 *arg0) {
    struct {
        s32 u54;
        s32 u58;
        s32 u5C;
        u8 pad60[0x8];
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        s16 u80;
        s16 u82;
        s16 u84;
        s16 u86;
        s32 u88;
        s32 u8C;
        s16 u90;
        s16 u92;
        s16 u94;
        s8 u96;
        s8 u97;
        s8 u98;
        s8 u99;
        s8 u9A;
        s8 u9B;
        s8 u9C;
        s8 u9D;
        s8 u9E;
        s8 u9F;
        s8 uA0;
        s8 uA1;
        s8 uA2;
        s8 uA3;
        s8 uA4;
        s8 uA5;
        s8 uA6;
        s8 uA7;
        s8 uA8;
        s8 uA9;
        s8 uAA;
        s8 uAB;
        s8 uAC;
        u8 padAD[0x3];
        s32 uB0;
        s32 uB4;
        s16 uB8;
        s16 uBA;
        s16 uBC;
        s8 uBE;
        u8 padBF[0x1];
        f32 uC0;
        s8 uC4;
        s8 uC5;
        s8 uC6;
        s8 uC7;
        s32 uC8;
        s32 uCC;
        s32 uD0;
        s8 uD4;
        s8 uD5;
        s16 uD6;
        s8 uD8;
    } sp;
    f32 sp4C;
    u8 *sp48;
    u8 *sp44;
    u8 *temp_a3;
    u8 *temp_v1;

    sp4C = func_150ADA68();
    temp_v1 = arg0 + 0x110;
    temp_a3 = temp_v1 + 0x30;
    sp44 = temp_a3;
    sp48 = temp_v1;
    func_15102EA0((sp4C * 30.0f) + 8.0f, 0xFF, temp_v1 + 0x6C, temp_a3, (func_150ADA20() % 46U) + 0x19, 1, 1, (*(s32 *)((u8 *)temp_v1 + 0x88)), (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
    if (func_150ADA68() < (0.25300002f * D_800DCE54)) {
        sp.uD4 = 3;
        sp.uD5 = -1;
        sp48 = temp_v1;
        sp.uD6 = (func_150ADA20() % 7U) + 4;
        sp.uD8 = 0;
        sp.uC8 = (s32) (*(f32 *)((u8 *)temp_v1 + 0x30));
        sp.uCC = (s32) (*(f32 *)((u8 *)temp_v1 + 0x34));
        sp.uD0 = (s32) (*(f32 *)((u8 *)temp_v1 + 0x38));
        func_151602C0((Header *) &sp.uD4, (Header2 *) &sp.uC8, (func_150ADA20() % 9U) + 0xC, 0xFF, 0xFF, 0xFF, 0xFFU, 0U, 0, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
        sp.u54 = 5 >> D_800DCE50;
        sp.u58 = 4 >> D_800DCE50;
        (*(s32 *)((u8 *)(&sp.u5C) + 0)) = (s32) (*(s32 *)((u8 *)sp44 + 0));
        (*(s32 *)((u8 *)(&sp.u5C) + 4)) = (s32) (*(s32 *)((u8 *)sp44 + 4));
        (*(s32 *)((u8 *)(&sp.u5C) + 8)) = (s32) (*(s32 *)((u8 *)sp44 + 8));
        sp.u86 = 0x50;
        sp.u88 = 3;
        sp.u84 = -0x3D;
        sp.u8C = 1;
        sp.u90 = 0xC;
        sp.u92 = 0xA;
        sp.u94 = 1;
        sp.u96 = 4;
        sp.u97 = 2;
        sp.u82 = 0xFF;
        sp.u9A = 0xFF;
        sp.u9B = 0xFF;
        sp.u99 = 0xFF;
        sp.u9C = 0xFF;
        sp.uA1 = 0xFF;
        sp.uA2 = 0xFF;
        sp.uA3 = 0xFF;
        sp.uA4 = 0xFF;
        sp.uA9 = 0xFF;
        sp.u70 = 0.0f;
        sp.u74 = 0.0f;
        sp.u80 = 0;
        sp.u98 = 3;
        sp.u9D = 0;
        sp.u9E = 0;
        sp.u9F = 0;
        sp.uA0 = 0;
        sp.uA5 = 0;
        sp.uA6 = 0;
        sp.uA7 = 0;
        sp.uA8 = 0;
        sp.uAA = 0;
        sp.uAB = 3;
        sp.uAC = 0x24;
        sp.uB0 = 0x200005;
        sp.uB4 = 0x60600;
        sp.uB8 = 0xA;
        sp.uBA = 0x19;
        sp.uBC = 1;
        sp.uBE = 0;
        sp.uC4 = -1;
        sp.uC5 = 0;
        sp.uC6 = -1;
        sp.uC7 = -1;
        sp.u68 = 8.25f;
        sp.u6C = 5.8599997f;
        sp.u78 = 7.0f;
        sp.u7C = 16.0f;
        sp.uC0 = 1.0f;
        func_151530A8(&sp.u54, (*(u8 *)((u8 *)arg0 + 0xC)), (*(u8 *)((u8 *)arg0 + 1)));
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C34F8.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C384C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C3C88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C40BC.s")

#ifdef NON_MATCHING
void func_151C491C(s32 arg0, u8 *arg1, s32 arg2) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f16;
    s32 var_a2;

    var_a2 = arg2;
    if (var_a2 > 0) {
        do {
            temp_f0 = (*(f32 *)((u8 *)arg1 + 0x10));
            temp_f12 = (*(f32 *)((u8 *)arg1 + 0x14));
            temp_f16 = (*(f32 *)((u8 *)arg1 + 0x18));
            var_a2 -= 1;
            (*(f32 *)((u8 *)arg1 + 0x10)) = (f32) (temp_f0 + (((*(f32 *)((u8 *)arg1 + 0x1C)) - temp_f0) * 0.228659f));
            (*(f32 *)((u8 *)arg1 + 0x14)) = (f32) (temp_f12 + (((*(f32 *)((u8 *)arg1 + 0x20)) - temp_f12) * 0.228659f));
            (*(f32 *)((u8 *)arg1 + 0x18)) = (f32) (temp_f16 + (((*(f32 *)((u8 *)arg1 + 0x24)) - temp_f16) * 0.228659f));
        } while (var_a2 > 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C491C.s")
#endif
s32 func_15081A90(struct127 *, s32, s32, s32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);
typedef struct { s32 w0; s32 w4; u8 b8[0x18]; u8 b20[0x39]; u8 x59; u8 pad5A[0x1A]; } Res_151C4990;
s32 func_151C4990(u8 *arg0, u8 *arg1, f32 arg2)
{
  u8 ret;
  struct127 *t;
  Res_151C4990 r;
  f32 f;
  t = *((struct127 **) (arg1 + 0x90));
  ret = 1;
  if (arg1[0] & 4)
  {
    if ((*((f32 *) (arg1 + 0x8C))) < arg2)
    {
      f = (*((f32 *) (arg1 + 0x8C))) * (*((f32 *) (arg1 + 0x98)));
    }
    else
    {
      f = (*((f32 *) (arg1 + 0x98))) * arg2;
    }
    if (f != 0.0f)
    {
      func_15081A90(t, *((s32 *) (arg0 + 0x34)), *((s32 *) (arg0 + 0x38)), *((s32 *) (arg0 + 0x3C)), *((f32 *) (arg1 + 0x60)), *((f32 *) (arg1 + 0x64)), *((f32 *) (arg1 + 0x68)), (u8 *) (&r), f, 1, 0, !(arg1[0] & 8), *((s8 *) (arg1 + 0xA8)), 0, *((s32 *) (arg1 + 0xAC)));
      if (r.x59 >= 2)
      {
        func_151C34A0(r.w0, (s32) t, arg0, (s32) r.b8, (s32) r.b20, (s32) (&r));
        ret = 0;
        if (arg1) // fakematch: register order of ret/flags
        {
        }
      }
    }
  }
  return ret;
}

void func_151C4AC0(u8 *arg0, u8 *arg1, f32 arg2) {
    (*(f32 *)((u8 *)arg0 + 0x34)) += ((*(f32 *)((u8 *)arg1 + 4)) * arg2);
    (*(f32 *)((u8 *)arg0 + 0x38)) += ((*(f32 *)((u8 *)arg1 + 8)) * arg2);
    (*(f32 *)((u8 *)arg0 + 0x3C)) += ((*(f32 *)((u8 *)arg1 + 0xC)) * arg2);
}

s32 func_151C4B0C(s32 arg0, u8 *arg1, f32 arg2) {
    s32 temp_v1;
    s32 var_v1;
    s8 temp_v0;
    var_v1 = 1;
    (*(f32 *)((u8 *)arg1 + 0x8C)) = (f32) ((*(f32 *)((u8 *)arg1 + 0x8C)) - arg2);
    if ((*(f32 *)((u8 *)arg1 + 0x8C)) <= 0.0f) {
        if ((D_800E0940 != NULL) && ((*(u8 *)((u8 *)arg1 + 0)) & 1)) {
            temp_v1 = (*(s32 *)((u8 *)arg1 + 0x84));
            if (temp_v1 != 0) {
                ((void (*)(u8 *, s32)) D_800E0940)(arg1 + 0x30, (temp_v1 - (s32) D_800DBEF4) / 160);
            }
        }
        if ((*(u8 *)((u8 *)arg1 + 0)) & 2) {
            temp_v0 = (*(s8 *)((u8 *)arg1 + 0x9C));
            if (temp_v0 != -1) {
                D_8008FF70[temp_v0](arg0);
            }
        }
        var_v1 = 0;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C4BF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C4DD0.s")

void func_151C5060(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *p = arg0 + 0x110;
    if (arg2 == 0x2D) {
        if (arg1[0] == *(s32 *)(p + 0x90)) {
            *(s32 *)(p + 0x90) = arg1[1];
            p[0x94] = ((u8 *)arg1)[9];
            return;
        }
        if (arg1[1] == *(s32 *)(p + 0x90)) {
            *(s32 *)(p + 0x90) = arg1[0];
            p[0x94] = ((u8 *)arg1)[8];
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EFE10/func_151C50BC.s")
