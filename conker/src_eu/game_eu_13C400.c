#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_1510F800(s32 arg0);
extern u8 *D_800DC278;
s32 func_151103B0(u8 *arg0);
#endif


#ifdef NON_MATCHING
void func_150ADD90(u8 *, u8 *, u8 *);
extern s32 D_800D3720;

s32 func_1510EBF0(s32 arg0) {
    struct {
        s32 u20;
        s32 u24;
        u8 pad28[0x4];
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
    } sp;
    s32 temp_t1;
    s32 var_v0;
    u8 *temp_a3;
    u8 *temp_t0;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v1;

    temp_v0 = ((s32 *)((u8 *)&D_800D3720 + (arg0 * 0x10)));
    temp_t0 = (*(u8 **)((u8 *)temp_v0 + 4));
    temp_t1 = (*(s32 *)((u8 *)temp_v0 + 8));
    var_v0 = 0;
    if (temp_t0 != NULL) {
        temp_v0_2 = (*(s32 *)((u8 *)temp_t0 + 0)) + temp_t1;
        temp_v1 = (*(s32 *)((u8 *)temp_t0 + 4)) + temp_t1;
        temp_a3 = (*(s32 *)((u8 *)temp_t0 + 8)) + temp_t1;
        sp.u38 = (f32) ((*(s16 *)((u8 *)temp_v1 + 0)) - (*(s16 *)((u8 *)temp_v0_2 + 0)));
        sp.u3C = (f32) ((*(s16 *)((u8 *)temp_v1 + 2)) - (*(s16 *)((u8 *)temp_v0_2 + 2)));
        sp.u40 = (f32) ((*(s16 *)((u8 *)temp_v1 + 4)) - (*(s16 *)((u8 *)temp_v0_2 + 4)));
        sp.u2C = (f32) ((*(s16 *)((u8 *)temp_a3 + 0)) - (*(s16 *)((u8 *)temp_v0_2 + 0)));
        sp.u30 = (f32) ((*(s16 *)((u8 *)temp_a3 + 2)) - (*(s16 *)((u8 *)temp_v0_2 + 2)));
        sp.u34 = (f32) ((*(s16 *)((u8 *)temp_a3 + 4)) - (*(s16 *)((u8 *)temp_v0_2 + 4)));
        func_150ADD90(&sp.u38, &sp.u2C, &sp.u20);
        if (sp.u24 < 0.0f) {
            return 0;
        }
        var_v0 = 1;
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return var_v0;
    }
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/func_1510EBF0.s")
#endif
s32 func_1510EED0(s32, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, u16, s32, f32, f32, s32);
void func_1510ED24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB, f32 argC, f32 argD) {
    func_1510EED0(arg0, arg1, 0, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA, argB, argC, argD, 0);
}

s32 func_1510EED0(s32, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, u16, s32, f32, f32, s32);
void func_1510EDAC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB) {
    func_1510EED0(arg0, arg1, 0, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA, argB, -10000.0f, 20000.0f, 0);
}

s32 func_1510EED0(s32, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, u16, s32, f32, f32, s32);
void func_1510EE3C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB, s32 argC, s32 argD, s32 argE) {
    func_1510EED0(arg0, arg1, 0, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA, argB, -10000.0f, 20000.0f, argE);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/func_1510EED0.s")

#ifdef NON_MATCHING
s32 func_150A48C0(s32, s32, s32, s32 *);
s32 func_150A49D0(s32, s32 *, s32);
s32 func_150A69A8(s16, s16, s32 *, s32);
extern s32 D_800D3720;
extern s32 D_800D3C50;

f32 func_1510FBC8(f32 arg0, f32 arg1, f32 arg2) {
    struct {
        s32 u28;
    } sp;
    s32 sp20;
    s32 sp1C;
    f32 var_f2;
    s32 temp_f10;
    s32 temp_f6;

    func_1510F800(2);
    temp_f6 = (s32) arg0;
    temp_f10 = (s32) arg2;
    sp20 = temp_f6;
    sp1C = temp_f10;
    func_150A69A8((s16) temp_f6, (s16) temp_f10, &sp.u28, (s32) arg1);
    func_150A49D0(sp.u28, &D_800D3C50, 0);
    if (func_150A48C0(sp20, sp1C, sp.u28, &D_800D3C50) != 0) {
        var_f2 = (f32) D_800D3720 * 0.00390625f;
    } else {
        var_f2 = -10000.0f;
    }
    return var_f2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/func_1510FBC8.s")
#endif
#ifdef NON_MATCHING
s32 func_1510FCA0(s32 arg0, s32 arg1, s32 arg2, u8 **arg3) {
    s16 temp_a1_3;
    s16 var_a2_2;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 var_a2;
    s32 var_a3;
    s32 var_v1;
    u8 **var_s2;
    u8 *var_v0;

    var_s2 = arg3;
    var_v0 = D_800DC278;
    var_v1 = 0;
    if (var_v0 != NULL) {
        do {
            temp_a1 = (*(s16 *)((u8 *)var_v0 + 8)) - arg0;
            var_a2 = temp_a1;
            if (temp_a1 < 0) {
                var_a2 = -temp_a1;
            }
            temp_a1_2 = arg2 + (*(u16 *)((u8 *)var_v0 + 6));
            if (var_a2 < temp_a1_2) {
                temp_a2 = (*(s16 *)((u8 *)var_v0 + 0xA)) - arg1;
                var_a3 = temp_a2;
                if (temp_a2 < 0) {
                    var_a3 = -temp_a2;
                }
                if (var_a3 < temp_a1_2) {
                    temp_a1_3 = (*(s16 *)((u8 *)var_v0 + 0xC));
                    if (temp_a1_3 != 0) {
                        var_a2_2 = temp_a1_3;
                    } else {
                        *var_s2 = var_v0;
                        var_s2 = (u8 * *)((u8 *)var_s2 + (4));
                        var_v1 += 1;
                        goto block_10;
                    }
                } else {
                    goto block_10;
                }
            } else {
block_10:
                var_a2_2 = (*(s16 *)((u8 *)var_v0 + 4));
            }
            if (var_a2_2 != 0) {
                var_v0 = &var_v0[var_a2_2];
            } else {
                var_v0 = NULL;
            }
        } while (var_v0 != NULL);
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/func_1510FCA0.s")
#endif
void func_1510F800(s32 arg0) {
    func_150A4ED4(arg0);
}

s32 func_1510E908(s32, s32, f32 *, f32 *);
void func_1510FDA0(s32 arg0, s32 arg1, f32 *arg2, f32 *arg3, s32 arg4, f32 *arg5, f32 *arg6)
{
  f32 sp24;
  f32 sp20;
  f32 temp_f2;
  func_1510E908(arg0, arg1, &sp24, &sp20);
  temp_f2 = sqrtf((sp24 * sp24) + (sp20 * sp20));
  *arg5 = sp24;
  *arg6 = sp20;
  temp_f2 = temp_f2 * 0.02f;
  if (temp_f2 == 0.0f) {
    *arg2 = 1.0f;
    *arg3 = 0.0f;
    return;
  }
  *arg2 = sp24 / temp_f2;
  *arg3 = sp20 / temp_f2;
}

s32 func_1510FE4C(s32 arg0) {
    return arg0 & 0x1F;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/func_1510FE58.s")

#ifdef NON_MATCHING
s32 func_150A6C40(s32);
void func_150F3978(s32);
extern s32 D_800DC1F0;
extern s32 D_800DC1F4;
extern s32 D_800DC1F8;
extern f32 D_800DC1FC;
extern f32 D_800DC200;
extern s32 D_800DC260;

void func_151101B4(s32 arg0) {
    s16 *temp_v1;
    s32 temp_f10;
    s32 temp_f6;
    s32 temp_v0_2;
    s32 temp_v0_3;
    struct108 *temp_v0;

    D_800DC1F0 = arg0;
    temp_v0 = &D_800DBFF0[arg0];
    temp_f6 = (s32) temp_v0->unk2F8;
    temp_f10 = (s32) temp_v0->unk300;
    D_800DC1FC = (f32) temp_f6;
    D_800DC200 = (f32) temp_f10;
    temp_v0_2 = func_1510FD20(temp_f6, temp_f10);
    D_800DC1F8 = temp_v0_2;
    temp_v0_3 = func_151103B0((u8 *) temp_v0_2);
    D_800DC1F4 = temp_v0_3;
    temp_v1 = ((s32 *)((u8 *)&D_800DC260 + (arg0 * 2)));
    if (temp_v0_3 != *temp_v1) {
        *temp_v1 = (s16) temp_v0_3;
        func_150A6C40(arg0);
    }
    if (D_800BE9F0 == 0x3C) {
        func_150F3978(arg0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/func_151101B4.s")
#endif
#ifdef NON_MATCHING
s32 func_1510FD20(s32 arg0, s32 arg1) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s32 temp_a1;
    s32 temp_a1_3;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_t0;
    s32 var_t0_2;
    u16 temp_a1_2;
    u16 temp_a1_4;
    u8 *var_v1;

    var_v1 = D_800DC278;
    if (var_v1 != NULL) {
loop_1:
        temp_v0 = (*(s16 *)((u8 *)var_v1 + 0xC));
        if (temp_v0 != 0) {
            temp_a1 = arg0 - (*(s16 *)((u8 *)var_v1 + 8));
            var_a2 = temp_a1;
            if (temp_a1 < 0) {
                var_a2 = -temp_a1;
            }
            temp_a1_2 = (*(u16 *)((u8 *)var_v1 + 6));
            if ((s32) temp_a1_2 >= var_a2) {
                temp_a2 = arg1 - (*(s16 *)((u8 *)var_v1 + 0xA));
                var_t0 = temp_a2;
                if (temp_a2 < 0) {
                    var_t0 = -temp_a2;
                }
                if ((s32) temp_a1_2 >= var_t0) {
                    var_v1 = &var_v1[temp_v0];
                } else {
                    goto block_9;
                }
            } else {
block_9:
                temp_v0_2 = (*(s16 *)((u8 *)var_v1 + 4));
                if (temp_v0_2 != 0) {
                    var_v1 = &var_v1[temp_v0_2];
                } else {
                    goto block_21;
                }
            }
            goto block_22;
        }
        temp_a1_3 = arg0 - (*(s16 *)((u8 *)var_v1 + 8));
        var_a2_2 = temp_a1_3;
        if (temp_a1_3 < 0) {
            var_a2_2 = -temp_a1_3;
        }
        temp_a1_4 = (*(u16 *)((u8 *)var_v1 + 6));
        if ((s32) temp_a1_4 >= var_a2_2) {
            temp_a2_2 = arg1 - (*(s16 *)((u8 *)var_v1 + 0xA));
            var_t0_2 = temp_a2_2;
            if (temp_a2_2 < 0) {
                var_t0_2 = -temp_a2_2;
            }
            if ((s32) temp_a1_4 >= var_t0_2) {
                return (s32) var_v1;
            }
            goto block_19;
        }
block_19:
        temp_v0_3 = (*(s16 *)((u8 *)var_v1 + 4));
        if (temp_v0_3 != 0) {
            var_v1 = &var_v1[temp_v0_3];
        } else {
block_21:
            var_v1 = NULL;
        }
block_22:
        if (var_v1 == NULL) {
    s32 pad;
            /* Duplicate return node #23. Try simplifying control flow for better match */
            return 0;
        }
        goto loop_1;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13C400/func_1510FD20.s")
#endif
extern u8 *D_800DC278;
s32 func_151103B0(u8 *arg0) {
    s32 count = 0;
    u8 *p = D_800DC278;

    while (p != NULL) {
        if (p == arg0) {
            return count;
        }
        if (*(s16 *)(p + 0xC) != 0) {
            p += *(s16 *)(p + 0xC);
        } else if (*(s16 *)(p + 4) != 0) {
            p += *(s16 *)(p + 4);
            count++;
        } else {
            p = NULL;
        }
    }
    return 0;
}
