#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 func_1519F500(u8 *arg0, u8 arg1, u8 *arg2);
#endif


#ifdef NON_MATCHING
extern f32 D_800A90C0;
extern f32 D_800A90C4;
s32 func_1519F500(u8 *arg0, u8 arg1, u8 *arg2) {
    u8 *temp_v0;
    u8 temp_v0_2;
    struct127 *var_a3;
    f32 var_f18;
    f32 var_f16;
    f32 var_f0;
    f32 temp_f2_2;
    f32 temp_f2;
    f32 temp_f14;
    f32 temp_f12;
    u8 sp1F;
    f32 sp28;
    f32 sp2C;
    u8 *sp38;
    struct127 *sp3C;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0));
    sp38 = temp_v0 + 0x58;
    var_a3 = (*(struct127 **)((u8 *)temp_v0 + 0x18));
    if (var_a3->unk1D4 == NULL) {
        return 0;
    }
    var_f16 = var_a3->x_position;
    temp_f12 = var_f16 - (*(f32 *)((u8 *)arg0 + 0x20));
    temp_f14 = var_a3->z_position - (*(f32 *)((u8 *)arg0 + 0x24));
    if ((fabsf(temp_f12) > D_800A90C0) || (fabsf(temp_f14) > D_800A90C0)) {
        temp_f2 = 1.0f / sqrtf((temp_f12 * temp_f12) + (temp_f14 * temp_f14));
        var_f18 = temp_f14 * temp_f2;
        sp28 = temp_f12 * temp_f2;
    } else {
        sp3C = var_a3;
        temp_v0_2 = func_15143E08(var_a3);
        sp1F = temp_v0_2;
        sp2C = func_151423D8(temp_v0_2 & 0xFF);
        var_a3 = sp3C;
        var_f18 = sp2C;
        sp28 = func_151423D8((sp1F - 0x40) & 0xFF);
        var_f16 = var_a3->x_position;
    }
    if (arg1 == 6) {
        var_f0 = (*(f32 *)((u8 *)sp38 + 0x10));
    } else {
        var_f0 = -(*(f32 *)((u8 *)sp38 + 0x10));
    }
    (*(f32 *)((u8 *)arg2 + 0)) = (f32) (var_f16 + (var_f0 * var_f18));
    (*(f32 *)((u8 *)arg2 + 8)) = (f32) (var_a3->z_position - (var_f0 * sp28));
    temp_f2_2 = var_a3->unk118;
    if (temp_f2_2 < D_800A90C4) {
        (*(f32 *)((u8 *)arg2 + 4)) = (f32) var_a3->y_position;
        return 1;
    }
    (*(f32 *)((u8 *)arg2 + 4)) = temp_f2_2;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519F500.s")
#endif
void func_1519F678(u8 *arg0) {
    u8 **temp_v0 = *(u8 ***)(arg0 + 0x98);
    s32 *temp_a0;

    if (*temp_v0 != NULL) {
        temp_a0 = (s32 *)(*temp_v0 + 0x58);
        if (*(s32 *)(arg0 + 0x20) == 6) {
            temp_a0[0] = 0;
        }
        if (*(s32 *)(arg0 + 0x20) == 7) {
            temp_a0[2] = 0;
        }
    }
    func_15147E64(arg0);
}

void func_1519F6D8(u8 *arg0) {
    u8 **temp_v0 = *(u8 ***)(arg0 + 0x98);
    s32 *temp_a0;

    if (*temp_v0 != NULL) {
        temp_a0 = (s32 *)(*temp_v0 + 0x58);
        if (*(s32 *)(arg0 + 0x20) == 6) {
            temp_a0[0] = 0;
        }
        if (*(s32 *)(arg0 + 0x20) == 7) {
            temp_a0[2] = 0;
        }
    }
    func_15147E98(arg0);
}

#ifdef NON_MATCHING
u8 func_151D8E20(void);
s32 memcpy(s32, u8 **, s32);
extern s32 D_800AB7F4;

s32 func_1519F738(u8 *arg0, u8 arg1) {
    struct {
        u8 * u48;
        s8 u4C;
        u8 pad4D[0x3];
        f32 u50;
        f32 u54;
        s32 u58;
        u8 pad5C[0x8];
        f32 u64;
        f32 u68;
        f32 u6C;
        s16 u70;
        u8 u72;
        u8 u73;
        u8 u74;
        u8 pad75[0x1];
        s16 u76;
        s16 u78;
        s16 u7A;
        s16 u7C;
        u8 pad7E[0x2];
        f32 u80;
        f32 u84;
        s8 u88;
        s8 u89;
        s8 u8A;
        s8 u8B;
        s8 u8C;
        s8 u8D;
        s16 u8E;
        s16 u90;
        s16 u92;
        f32 u94;
        s32 u98;
        u8 pad9C[0x8];
        s16 uA4;
        u16 uA6;
        s32 uA8;
        u8 padAC[0x1];
        s8 uAD;
        u8 padAE[0x6];
        u8 * uB4;
    } sp;
    u8 *sp44;
    u8 sp43;
    u8 temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v1;
    u8 *var_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x18));
    sp.uB4 = temp_v1;
    temp_v0 = func_151D8E20();
    sp.uA6 = 0x42;
    sp.uA4 = 0x12C;
    sp.uAD = 0xA;
    sp.u76 = 0xC8;
    sp.u88 = 3;
    sp.u48 = arg0;
    sp43 = temp_v0;
    sp.u4C = 6;
    sp.u89 = 0x55;
    sp.u8A = 3;
    sp.u8B = 0x55;
    sp.u8C = 0x88;
    sp.u8D = 0xC4;
    sp.u70 = 0;
    sp.u8E = 0;
    sp.u78 = 0xFF;
    sp.u7A = 0x28;
    sp.u7C = 0x19;
    sp.u90 = 6;
    sp.u92 = 0x325;
    sp.u50 = 0.015000001f;
    sp.u80 = 5.8f;
    sp.u84 = 1.0f;
    sp.u54 = 0.0f;
    sp.u64 = 0.0f;
    sp.uA8 = (s32) arg1;
    sp.u94 = 1.5f;
    sp.u68 = (*(f32 *)((u8 *)temp_v1 + 0x14));
    sp.u6C = (*(f32 *)((u8 *)temp_v1 + 0x1C));
    if (func_1519F500(&sp.u48, arg1 & 0xFF, &sp.u98) != 0) {
        (*(s32 *)((u8 *)(&sp.u58) + 0)) = (s32) (*(s32 *)((u8 *)(&sp.u98) + 0));
        (*(s32 *)((u8 *)(&sp.u58) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u98) + 4));
        (*(s32 *)((u8 *)(&sp.u58) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u98) + 8));
        sp.uA6 |= 4;
    }
    temp_v0_2 = (sp43 * 3) + &D_800AB7F4;
    sp.u72 = (*(u8 *)((u8 *)temp_v0_2 + 0));
    sp.u73 = (*(u8 *)((u8 *)temp_v0_2 + 1));
    sp.u74 = (*(u8 *)((u8 *)temp_v0_2 + 2));
    temp_v0_3 = func_15147FF0(&sp.u98, 0x50, 0x24, 5, 5, 5, 0, 0, (s32) (arg0 + 0x34), 0xFFU, 1);
    var_v1 = temp_v0_3;
    if (temp_v0_3 != NULL) {
        sp44 = temp_v0_3;
        memcpy((*(s32 *)((u8 *)temp_v0_3 + 0x98)), &sp.u48, 0x50);
        var_v1 = sp44;
    }
    return (s32) var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519F738.s")
#endif
s32 func_1519F738(u8 *, u8);
void func_1519F928(u8 *arg0) {
    s32 *p = (s32 *)(arg0 + 0x58);
    p[0] = func_1519F738(arg0, 6);
    p[1] = 0;
    p[2] = func_1519F738(arg0, 7);
    p[3] = 0;
}

void func_151A0E98(u8 *);
void func_1519F9FC(u8 *);

void func_1519F970(u8 *arg0) {
    u8 *v = arg0 + 0x58;

    if (*(s32 *)(arg0 + 0x58) != 0) {
        func_1519F9FC(*(u8 **)(arg0 + 0x58));
    }
    if (*(u8 **)(v + 8) != NULL) {
        func_1519F9FC(*(u8 **)(v + 8));
    }
    if (*(u8 **)(v + 4) != NULL) {
        func_151A0E98(*(u8 **)(v + 4));
        func_1516972C(*(struct102 **)(v + 4));
    }
    if (*(u8 **)(v + 0xC) != NULL) {
        func_151A0E98(*(u8 **)(v + 0xC));
        func_1516972C(*(struct102 **)(v + 0xC));
    }
}

#ifdef NON_MATCHING
void func_1519F9FC(u8 *arg0) {
    s32 temp_v1;
    u8 *temp_a1;
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_v1 = (*(s32 *)((u8 *)temp_v0 + 0));
    if (temp_v1 != 0) {
        temp_a1 = temp_v1 + 0x58;
        if ((*(s32 *)((u8 *)arg0 + 0x20)) == 6) {
            (*(s32 *)((u8 *)temp_a1 + 0)) = 0;
        }
        if ((*(s32 *)((u8 *)arg0 + 0x20)) == 7) {
            (*(s32 *)((u8 *)temp_a1 + 8)) = 0;
        }
        (*(s32 *)((u8 *)temp_v0 + 0)) = 0;
    }
    (*(s8 *)((u8 *)arg0 + 0x30)) = 0;
    (*(u16 *)((u8 *)arg0 + 0x1E)) = (u16) ((*(u16 *)((u8 *)arg0 + 0x1E)) & 0xFFFD);
    (*(u8 *)((u8 *)temp_v0 + 4)) = (u8) ((*(u8 *)((u8 *)temp_v0 + 4)) | 1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519F9FC.s")
#endif
#ifdef NON_MATCHING
extern f32 D_800A90D0;
s32 func_15045AF0(f32 *, s32, f32, u8 *);

s32 func_1519FA60(u8 *arg0) {
    struct {
        f32 u58;
        f32 u5C;
        f32 u60;
    } sp;
    f32 temp_f0;
    s16 temp_v0;
    s32 temp_fp;
    s32 var_s3;
    s8 var_s2;
    u8 *temp_s1;
    u8 *temp_s6;
    u8 *temp_v0_2;

    temp_s6 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_fp = (*(s32 *)((u8 *)arg0 + 0x94));
    if (((*(s8 *)((u8 *)arg0 + 0x2C)) < 2) && ((*(u8 *)((u8 *)temp_s6 + 4)) & 1)) {
        return 0;
    }
    var_s2 = (*(s8 *)((u8 *)arg0 + 0x2E));
    if (var_s2 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
        do {
            var_s2 -= 1;
            var_s3 = 0;
            if (var_s2 < 0) {
                var_s2 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_s1 = (var_s2 * 0x24) + temp_fp;
            (*(s16 *)((u8 *)temp_s1 + 0x18)) = (s16) ((*(s16 *)((u8 *)temp_s1 + 0x18)) - D_800BE9E4);
            if ((*(s16 *)((u8 *)temp_s1 + 0x18)) < 0) {
                var_s3 = 1;
            }
            temp_v0 = (*(s16 *)((u8 *)temp_s1 + 0x12));
            (*(s16 *)((u8 *)temp_s1 + 0x14)) = 0xFF;
            if (temp_v0 > 0) {
                (*(s16 *)((u8 *)temp_s1 + 0x12)) = (s16) (temp_v0 - D_800BE9E4);
            } else {
                (*(s16 *)((u8 *)temp_s1 + 0x10)) = (s16) ((*(s16 *)((u8 *)temp_s1 + 0x10)) - ((*(s16 *)((u8 *)temp_s6 + 0x34)) * D_800BE9E4));
            }
            (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) + ((*(f32 *)((u8 *)temp_s6 + 0x3C)) * D_800BE9A4));
            (*(f32 *)((u8 *)temp_s1 + 0)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0)) + ((*(f32 *)((u8 *)temp_s1 + 0x1C)) * D_800BE9A4));
            (*(f32 *)((u8 *)temp_s1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 4)) + ((*(f32 *)((u8 *)temp_s1 + 0x20)) * D_800BE9A4));
            sp.u58 = (*(f32 *)((u8 *)temp_s1 + 0));
            temp_f0 = fabsf(sp.u58);
            sp.u5C = (*(f32 *)((u8 *)temp_s1 + 8)) + 30.0f;
            sp.u60 = (*(f32 *)((u8 *)temp_s1 + 4));
            if ((temp_f0 > D_800A90D0) || (fabsf(sp.u60) > D_800A90D0)) {
                goto block_17;
            }
            if (func_15045AF0(&sp.u58, 0, (*(f32 *)((u8 *)temp_s1 + 8)) - 30.0f, arg0 + 0x60) != 0) {
                (*(f32 *)((u8 *)temp_s1 + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 0x60));
            } else {
block_17:
                var_s3 = 1;
            }
            if ((*(s16 *)((u8 *)temp_s1 + 0x10)) < 0) {
                var_s3 = 1;
            }
            if (var_s3 != 0) {
                if (var_s2 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    do {
                        (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2D)) + 1);
                        if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                            (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                        }
                        (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
                    } while (var_s2 != (*(s8 *)((u8 *)arg0 + 0x2D)));
                }
                (*(s16 *)((u8 *)((temp_fp + ((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x24))) + 0x10)) = 0;
            }
        } while (var_s2 != (*(s8 *)((u8 *)arg0 + 0x2D)));
    }
    (*(s16 *)((u8 *)temp_s6 + 0x46)) = (s16) ((*(s16 *)((u8 *)temp_s6 + 0x46)) + ((*(s16 *)((u8 *)temp_s6 + 0x48)) * D_800BE9E4));
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) > 0) {
        temp_v0_2 = temp_fp + ((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x24);
        (*(f32 *)((u8 *)arg0 + 0x54)) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0));
        (*(f32 *)((u8 *)arg0 + 0x58)) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 8));
        (*(f32 *)((u8 *)arg0 + 0x5C)) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 4));
    } else {
        (*(f32 *)((u8 *)arg0 + 0x54)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x58)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x5C)) = 0.0f;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519FA60.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519FD60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_151A03DC.s")

#ifdef NON_MATCHING
void func_151A0DBC(u8 *arg0) {
    u8 *sp28;
    u8 sp23;
    u8 *sp18;
    s32 temp_v0_2;
    s32 var_v1;
    u8 *temp_a0;
    u8 *temp_a1;
    u8 *temp_a2;
    u8 *temp_t0;
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x28));
    var_v1 = 0;
    temp_a2 = arg0 + 0x28;
    temp_a1 = (*(u8 **)((u8 *)temp_v0 + 0x18));
    temp_t0 = temp_v0 + 0x58;
    if ((*(s32 *)((u8 *)temp_a1 + 0)) == 0) {
        var_v1 = 1;
    }
    temp_a0 = (*(u8 **)((u8 *)temp_a2 + 0));
    if ((*(u8 *)((u8 *)temp_a0 + 0x1C)) != (*(u8 *)((u8 *)temp_a1 + 0x3B))) {
        var_v1 = 1;
    }
    if ((var_v1 == 0) && ((*(s32 *)((u8 *)temp_a1 + 0x1D4)) != 0)) {
        sp23 = 1;
        sp28 = temp_t0;
        sp18 = temp_a2;
        temp_v0_2 = func_1519F738(temp_a0, (*(u8 *)((u8 *)temp_a2 + 4)));
        var_v1 = 1;
        if ((*(u8 *)((u8 *)temp_a2 + 4)) == 6) {
            (*(s32 *)((u8 *)temp_t0 + 0)) = temp_v0_2;
        } else {
            (*(s32 *)((u8 *)temp_t0 + 8)) = temp_v0_2;
        }
    }
    if (var_v1 != 0) {
        func_151A0E98(arg0);
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        (*(u8 *)((u8 *)arg0 + 0xD)) = (u8) ((*(u8 *)((u8 *)arg0 + 0xD)) | 1);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_151A0DBC.s")
#endif
void func_151A0E98(u8 *arg0) {
    u8 *p = *(u8 **)(arg0 + 0x28) + 0x58;
    if (arg0[0x2C] == 6) {
        *(s32 *)(p + 4) = 0;
    } else {
        *(s32 *)(p + 0xC) = 0;
    }
}

void func_151A0EC0(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_t6;
    unsigned int new_var; // fakematch: field temp pins t7/v1 register choice
    unsigned int new_var2; // fakematch: same for the second branch
    u8 **temp_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_t6 = arg2;
    temp_v1 = *(u8 ***)(arg0 + 0x98);
    if (temp_t6 == 0xA) {
        temp_v0 = *temp_v1;
        if ((temp_v0 != NULL) && (((new_var = *(s32 *)(temp_v0 + 0x18)) == *(s32 *)(arg1 + 0)) || (*(u8 *)(temp_v0 + 0x1C) == *(u8 *)(arg1 + 4)))) {
            func_1519F9FC(arg0);
        }
    } else if (temp_t6 == 0) {
        temp_v0_2 = *temp_v1;
        if ((temp_v0_2 != NULL) && ((new_var2 = *(s32 *)(temp_v0_2 + 0x18)) == *(s32 *)(arg1 + 0))) {
            func_1519F9FC(arg0);
        }
    }
}

void func_151A0F5C(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = *(u8 **)(*(u8 **)(arg0 + 0x28) + 0x18);
    if (arg2 == 0) {
        if (((s32)v == *(s32 *)arg1) || (v[0x3B] == arg1[4])) {
            func_151A0E98(arg0);
            func_1516972C(arg0);
        }
    }
}
