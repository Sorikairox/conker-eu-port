#include <ultra64.h>
#include "functions.h"
#include "variables.h"


u8 *func_15172210(s16 arg0, u16 arg1, u8 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, s32 arg7) {
    s32 var_a0;
    u8 *t;
    if (arg5 == 0) {
        var_a0 = 0xF;
    } else {
        var_a0 = 0x43;
    }
    t = func_15167A68(var_a0, arg7, 0x60, 1, (u8) (s32) arg6, 1U);
    if (t == NULL) {
        return NULL;
    }
    *(s16 *)(t + 0x50) = arg0;
    *(s16 *)(t + 0x52) = 0;
    *(s16 *)(t + 0x54) = arg4;
    *(u16 *)(t + 0x56) = arg1;
    *(u8 *)(t + 0x58) = arg2;
    *(s8 *)(t + 0x59) = arg3;
    *(s16 *)(t + 0x16) = 0;
    *(s16 *)(t + 0x26) = 0;
    *(s16 *)(t + 0x36) = 0;
    *(s16 *)(t + 0x46) = 0;
    return t;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19FA20/func_151722BC.s")

s32 func_15172B6C(s32, s32, f32, f32, f32, f32, s32, s32);
extern s32 D_8008CDEC;

void func_15172474(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s16 arg4, u16 arg5, u8 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 argB, s32 argC) {
    u8 *temp_v0;
    u8 *sp2C;

    temp_v0 = func_15172210(arg4, arg5, arg6, arg8, arg9, argA, (s32) argB, argC);
    if (temp_v0 != NULL) {
        sp2C = temp_v0;
        if (func_15172B6C((s32)((u8 *)temp_v0 + 0x10), arg3, arg0, arg1, arg2, 0.0f, arg7, *(u16 *)((u8 *)((s32 *)&D_8008CDEC)[*((u8 *)temp_v0 + 0x58)] + 6)) == 0) {
            func_1516972C((struct102 *)sp2C);
        }
    }
}

void func_15172530(struct102 *arg0) {
    s16 temp_v0;
    s32 temp_v0_2;

    temp_v0 = (*(s16 *)((u8 *)arg0 + 0x50));
    if (temp_v0 < -1) {
        (*(s16 *)((u8 *)arg0 + 0x50)) = (s16) (temp_v0 + 1);
        if ((*(s16 *)((u8 *)arg0 + 0x50)) == -1) {
            func_1516972C(arg0);
        }
    } else {
        if (temp_v0 == 0) {
            (*(s16 *)((u8 *)arg0 + 0x50)) = -3;
            return;
        }
        if (temp_v0 != -1) {
            if (!((*(u8 *)((u8 *)arg0 + 0x59)) & 4)) {
                if (D_800BE9E4 < temp_v0) {
                    (*(s16 *)((u8 *)arg0 + 0x50)) = (s16) (temp_v0 - D_800BE9E4);
                } else {
                    (*(s16 *)((u8 *)arg0 + 0x50)) = 0;
                }
            }
            (*(s16 *)((u8 *)arg0 + 0x52)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x54)) + (*(s16 *)((u8 *)arg0 + 0x52)));
            temp_v0_2 = (*(u8 *)((u8 *)((&D_8008CDEC)[(*(u8 *)((u8 *)arg0 + 0x58))]) + 4));
            if (((s16) (*(s16 *)((u8 *)arg0 + 0x52)) / 256) >= temp_v0_2) {
                if ((*(u8 *)((u8 *)arg0 + 0x59)) & 4) {
                    (*(s16 *)((u8 *)arg0 + 0x50)) = -3;
                    return;
                }
                (*(s16 *)((u8 *)arg0 + 0x52)) = (s16) ((temp_v0_2 << 8) - 0x100);
            }
        }
    }
}

#ifdef NON_MATCHING
extern s32 D_800D30BC;
extern u32 D_800DD5E4;
extern s32 D_800DD5E8;
extern s16 D_800DD5EC;

u8 *func_15172634(u8 *arg0, u8 *arg1, s32 arg2) {
    struct {
        s32 u8C;
        s32 u90;
        u32 u94;
        s32 u98;
        u8 pad9C[0x18];
        s32 uB4;
        s32 uB8;
    } sp;
    s32 sp88;
    s32 sp84;
    s32 sp80;
    s16 temp_a2;
    s16 temp_t5;
    s16 temp_t6;
    s16 temp_t8;
    s16 temp_v1_2;
    s16 var_a0_2;
    s32 temp_t4;
    s32 var_a0;
    s32 var_t0_2;
    s32 var_t2;
    s32 var_v1;
    s32 var_v1_2;
    u16 temp_v0_4;
    u32 temp_v0;
    u32 var_t0;
    u8 temp_v1;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_s0_3;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *var_s0;
    u8 *var_s0_2;

    var_s0 = arg0;
    sp.u8C = 1;
    if ((*(s16 *)((u8 *)arg1 + 0x50)) >= 2) {
        temp_t4 = (&D_8008CDEC)[(*(u8 *)((u8 *)arg1 + 0x58))];
        sp88 = temp_t4;
        temp_v0 = *(s32 *)temp_t4;
        temp_a2 = (*(s16 *)((u8 *)arg1 + 0x52));
        var_t0 = temp_v0;
        var_v1 = temp_a2 >> 8;
        if (temp_v0 >= 0x10000000U) {
            var_t0 = *(s32 *)(temp_v0 + (var_v1 * 4));
            var_v1 = 0;
        }
        if ((var_t0 != D_800DD5E4) || (var_v1 != D_800DD5E8)) {
            sp.u90 = var_v1;
            sp.u94 = var_t0;
            temp_v0_2 = func_15095380(var_s0, sp88, temp_a2, &sp.u98, 0, 0, 0, 2, 3);
            D_800DD5E4 = sp.u94;
            var_s0 = temp_v0_2;
            D_800DD5E8 = sp.u90;
        }
        var_t0_2 = D_800DD5EC & 0xF;
        if (!((*(u8 *)((u8 *)arg1 + 0x59)) & 1)) {
            var_v1_2 = 1;
        } else {
            var_v1_2 = 2;
        }
        if ((*(u8 *)((u8 *)sp88 + 0xA)) == 5) {
            var_v1_2 += 2;
        }
        if (var_t0_2 != var_v1_2) {
            var_t0_2 = var_v1_2;
            if (sp.u8C != 0) {
                (*(s32 *)((u8 *)var_s0 + 0)) = 0xE7000000;
                (*(s32 *)((u8 *)var_s0 + 4)) = 0;
                var_s0 += 8;
            }
            sp.u8C = 0;
            switch (var_v1_2) {                     /* switch 1; irregular */
            case 1:                                 /* switch 1 */
                sp84 = 0;
                sp80 = 0x504DD8;
                break;
            case 2:                                 /* switch 1 */
                sp84 = 0;
                sp80 = 0x504B50;
                break;
            case 3:                                 /* switch 1 */
                sp84 = 0x100000;
                sp80 = 0x0C184DD8;
                break;
            case 4:                                 /* switch 1 */
                sp84 = 0x100000;
                sp80 = 0x0C184B50;
                break;
            }
            (*(s32 *)((u8 *)var_s0 + 0)) = 0xE2001E01;
            (*(s32 *)((u8 *)var_s0 + 4)) = 0;
            temp_s0 = var_s0 + 8;
            (*(s32 *)((u8 *)temp_s0 + 0)) = 0xD9EEFFFF;
            (*(s32 *)((u8 *)temp_s0 + 4)) = 0;
            var_s0 = temp_s0 + 8;
        }
        sp.uB8 = var_t0_2;
        sp.uB4 = D_800DD5EC & 0xF0;
        temp_v0_3 = func_15142FBC(var_s0, sp84 | 0x80000 | D_800D30BC | 0x2CB0, sp80, &sp.u8C);
        var_t2 = sp.uB4;
        var_s0_2 = temp_v0_3;
        var_a0 = 0x40;
        if (!((*(u8 *)((u8 *)arg1 + 0x59)) & 8)) {
            temp_v1 = (*(u8 *)((u8 *)sp88 + 0xA));
            if (temp_v1 == 0) {
                if ((*(u16 *)((u8 *)arg1 + 0x56)) != 0) {
                    var_a0 = 0x10;
                } else {
                    var_a0 = 0x20;
                }
            } else if (temp_v1 == 5) {
                if ((*(u16 *)((u8 *)arg1 + 0x56)) != 0) {
                    var_a0 = 0x60;
                } else {
                    var_a0 = 0x50;
                }
            } else {
                var_a0 = 0x30;
            }
        }
        if (var_t2 != var_a0) {
            var_t2 = var_a0;
            if (sp.u8C != 0) {
                (*(s32 *)((u8 *)temp_v0_3 + 0)) = 0xE7000000;
                var_s0_2 = temp_v0_3 + 8;
                (*(s32 *)((u8 *)temp_v0_3 + 4)) = 0;
            }
            switch (var_a0) {
            case 0x10:
                (*(s32 *)((u8 *)var_s0_2 + 0)) = 0xFC30B261;
                (*(s32 *)((u8 *)var_s0_2 + 4)) = 0xFF67FFFF;
                var_s0_2 += 8;
                break;
            case 0x20:
                (*(s32 *)((u8 *)var_s0_2 + 0)) = 0xFCFFB3FF;
                (*(s32 *)((u8 *)var_s0_2 + 4)) = 0xFF64FE7F;
                var_s0_2 += 8;
                break;
            case 0x30:
                (*(s32 *)((u8 *)var_s0_2 + 0)) = 0xFCFF97FF;
                (*(s32 *)((u8 *)var_s0_2 + 4)) = 0xFF2DFEFF;
                var_s0_2 += 8;
                break;
            case 0x40:
                (*(s32 *)((u8 *)var_s0_2 + 0)) = 0xFCFFFFFF;
                (*(s32 *)((u8 *)var_s0_2 + 4)) = 0xFFFCF279;
                var_s0_2 += 8;
                break;
            case 0x50:
                (*(s32 *)((u8 *)var_s0_2 + 0)) = 0xFCFFB5FF;
                (*(s32 *)((u8 *)var_s0_2 + 4)) = 0xFFFCFE38;
                var_s0_2 += 8;
                break;
            case 0x60:
                (*(s32 *)((u8 *)var_s0_2 + 4)) = -0x1C8;
                (*(s32 *)((u8 *)var_s0_2 + 0)) = 0xFC30B5FF;
                var_s0_2 += 8;
                break;
            }
        }
        D_800DD5EC = sp.uB8 | var_t2;
        temp_v0_4 = (*(u16 *)((u8 *)arg1 + 0x56));
        temp_v1_2 = (*(s16 *)((u8 *)arg1 + 0x50));
        temp_t5 = ((s32) temp_v0_4 >> 8) & 0xF8;
        temp_t6 = ((s32) temp_v0_4 >> 3) & 0xF8;
        temp_t8 = (temp_v0_4 * 4) & 0xF8;
        if (temp_v1_2 >= 0x1A) {
            var_a0_2 = 0xFF;
        } else {
            var_a0_2 = temp_v1_2 * 0xA;
        }
        if ((temp_t5 != D_800DD5F0) || (temp_t6 != D_800DD5F2) || (temp_t8 != D_800DD5F4) || (var_a0_2 != D_800DD5F6)) {
            D_800DD5F0 = temp_t5;
            D_800DD5F2 = temp_t6;
            D_800DD5F4 = temp_t8;
            D_800DD5F6 = var_a0_2;
            if (sp.u8C != 0) {
                (*(s32 *)((u8 *)var_s0_2 + 0)) = 0xE7000000;
                (*(s32 *)((u8 *)var_s0_2 + 4)) = 0;
                var_s0_2 += 8;
            }
            (*(s32 *)((u8 *)var_s0_2 + 0)) = 0xFA000100;
            (*(s32 *)((u8 *)var_s0_2 + 4)) = (s32) ((temp_t5 << 0x18) | ((temp_t6 & 0xFF) << 0x10) | ((temp_t8 & 0xFF) << 8) | (var_a0_2 & 0xFF));
            var_s0_2 += 8;
        }
        (*(u8 **)((u8 *)var_s0_2 + 4)) = (u8 *) (arg1 + 0x10);
        (*(s32 *)((u8 *)var_s0_2 + 0)) = 0x01004008;
        temp_s0_2 = var_s0_2 + 8;
        (*(s32 *)((u8 *)temp_s0_2 + 0)) = 0x05000204;
        (*(s32 *)((u8 *)temp_s0_2 + 4)) = 0;
        temp_s0_3 = temp_s0_2 + 8;
        (*(s32 *)((u8 *)temp_s0_3 + 0)) = 0x05000406;
        (*(s32 *)((u8 *)temp_s0_3 + 4)) = 0;
        var_s0 = temp_s0_3 + 8;
    }
    return var_s0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19FA20/func_15172634.s")
#endif
#ifdef NON_MATCHING
extern f32 D_800A7524;
extern f32 D_800A7530;
s32 func_1510E908(s32, s32, f32 *, f32 *);
extern s32 D_800A73B0;
extern s32 D_800A73C0;
extern s32 D_800A73D0;

s32 func_15172B6C(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7) {
    struct {
        f32 u64;
        f32 u68;
        u8 pad6C[0x8];
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
    } sp;
    f32 sp58;
    s32 sp48;
    f32 sp40;
    s32 *var_a1;
    s32 *var_v0_2;
    f32 *var_v0;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f4;
    f32 temp_f6;
    f32 temp_f6_2;
    f32 temp_f8;
    f32 var_f12;
    f32 var_f12_2;
    f32 var_f14;
    f32 var_f18;
    f32 var_f2;
    s16 temp_f10;
    s32 temp_t6;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;

    temp_t6 = arg6 / 16;
    var_v1 = temp_t6;
    if (temp_t6 == 0) {
        var_v1 = 1;
    }
    sp48 = var_v1;
    if (func_1510E908(arg1, 0, &sp.u64, &sp.u68) == 0) {
        return 0;
    }
    temp_f18 = (f32) -sp48;
    sp.u74 = 0.0f;
    temp_f12 = -temp_f18 - temp_f18;
    temp_f4 = (temp_f18 * sp.u68) + (sp.u64 * 0.0f);
    sp.u78 = temp_f4;
    var_f2 = (2.0f * temp_f12) + (2.0f * sp.u68 * (-temp_f4 - temp_f4));
    if (var_f2 == 0.0f) {
        var_f2 = D_800A7524;
    }
    sp.u80 = temp_f18;
    temp_f14 = sp.u64 * sp.u80;
    sp.u84 = (temp_f12 * (2.0f * temp_f14)) / var_f2;
    if (sp.u68 == 0.0f) {
        var_f18 = 0.0f;
    } else {
        var_f18 = (sp.u84 - temp_f14) / sp.u68;
    }
    sp.u7C = temp_f18;
    var_f12 = (temp_f18 * temp_f18) + (0.0f + (sp.u78 * sp.u78));
    if (var_f12 > 1e8f) {
        var_f12 = 1e8f;
    }
    temp_f2 = (f32) (sp48 * sp48);
    if (var_f12 < temp_f2) {
        var_f12 = temp_f2;
    }
    temp_f0 = sqrtf(var_f12);
    sp.u88 = var_f18;
    var_f14 = (var_f18 * var_f18) + ((sp.u80 * sp.u80) + (sp.u84 * sp.u84));
    if (var_f14 > 1e8f) {
        var_f14 = 1e8f;
    }
    if (var_f14 < temp_f2) {
        var_f14 = temp_f2;
    }
    temp_f0_2 = sqrtf(var_f14);
    var_v0 = &sp.u74;
    var_a0 = 0;
    var_v1_2 = arg0;
    temp_f2_2 = (f32) arg6;
    do {
        temp_f8 = (*(f32 *)((u8 *)var_v0 + 0xC));
        var_a0 += 2;
        temp_f6 = (*(f32 *)((u8 *)var_v0 + 0)) * temp_f2_2;
        var_v0 = (f32 *)((u8 *)var_v0 + (4));
        var_v1_2 += 2;
        (*(f32 *)((u8 *)var_v0 + -4)) = (f32) (temp_f6 / temp_f0);
        (*(f32 *)((u8 *)var_v0 + 8)) = (f32) ((temp_f8 * temp_f2_2) / temp_f0_2);
        (*(s16 *)((u8 *)var_v1_2 + -2)) = (s16) (s32) (*(f32 *)((u8 *)var_v0 + -4));
        (*(s16 *)((u8 *)var_v1_2 + 0xE)) = (s16) (s32) (*(f32 *)((u8 *)var_v0 + 8));
        (*(s16 *)((u8 *)var_v1_2 + 0x1E)) = (s16) (s32) -(*(f32 *)((u8 *)var_v0 + -4));
        (*(s16 *)((u8 *)var_v1_2 + 0x2E)) = (s16) (s32) -(*(f32 *)((u8 *)var_v0 + 8));
    } while (var_a0 < 6);
    temp_f12_2 = (arg5 - 225.0f) * D_800A7530;
    sp40 = temp_f12_2;
    sp58 = cosf(temp_f12_2);
    temp_f0_3 = sinf(temp_f12_2);
    var_a0_2 = 0;
    if ((u8) arg7 == 0x10) {
        var_f12_2 = 256.0f;
        var_a1 = &D_800A73D0;
    } else if ((u8) arg7 == 0x20) {
        var_f12_2 = 512.0f;
        var_a1 = &D_800A73C0;
    } else {
        var_f12_2 = 1024.0f;
        var_a1 = &D_800A73B0;
    }
    var_v1_3 = arg0;
    var_v0_2 = var_a1;
    do {
        var_a0_2 += 0x10;
        var_v1_3 += 0x10;
        temp_f6_2 = (f32) (*(s16 *)((u8 *)var_v0_2 + 0));
        temp_f10 = (*(s16 *)((u8 *)var_v0_2 + 2));
        var_v0_2 = (s32 *)((u8 *)var_v0_2 + (4));
        (*(s16 *)((u8 *)var_v1_3 + -8)) = (s16) (s32) ((((temp_f6_2 - var_f12_2) * sp58) - (((f32) temp_f10 - var_f12_2) * temp_f0_3)) + var_f12_2 + 8192.0f);
        (*(s16 *)((u8 *)var_v1_3 + -6)) = (s16) (s32) ((((f32) (*(s16 *)((u8 *)var_v0_2 + -2)) - var_f12_2) * sp58) + (((f32) (*(s16 *)((u8 *)var_v0_2 + -4)) - var_f12_2) * temp_f0_3) + var_f12_2 + 8192.0f);
    } while (var_a0_2 < 0x40);
    (*(s16 *)((u8 *)arg0 + 0)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0)) + arg2);
    (*(s16 *)((u8 *)arg0 + 2)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 2)) + arg3);
    (*(s16 *)((u8 *)arg0 + 4)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 4)) + arg4);
    (*(s16 *)((u8 *)arg0 + 0x10)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x10)) + arg2);
    (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x12)) + arg3);
    (*(s16 *)((u8 *)arg0 + 0x14)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x14)) + arg4);
    (*(s16 *)((u8 *)arg0 + 0x20)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x20)) + arg2);
    (*(s16 *)((u8 *)arg0 + 0x22)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x22)) + arg3);
    (*(s16 *)((u8 *)arg0 + 0x24)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x24)) + arg4);
    (*(s16 *)((u8 *)arg0 + 0x30)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x30)) + arg2);
    (*(s16 *)((u8 *)arg0 + 0x32)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x32)) + arg3);
    (*(s16 *)((u8 *)arg0 + 0x34)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x34)) + arg4);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19FA20/func_15172B6C.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19FA20/func_15173090.s")
