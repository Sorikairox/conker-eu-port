#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 memcpy(s32, s32, s32);
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
#endif


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E390/func_15100B80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E390/func_15101610.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E390/func_151016C8.s")

void func_15101768(struct210 *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0x124) + 0x110;
    *(s32 *)(p + 0x28) = 0;
    func_1513CA6C(arg0);
}

void func_15101790(struct210 *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0x124) + 0x110;
    *(s32 *)(p + 0x28) = 0;
    func_1513CAA0(arg0);
}

void func_151017B8(struct210 *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0x18) + 0x110;
    *(s32 *)(p + 0x2C) = 0;
    func_151617C4(arg0);
}

void func_151017E0(struct210 *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0x18) + 0x110;
    *(s32 *)(p + 0x2C) = 0;
    func_151617E4(arg0);
}

void func_15101808(struct210 *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0xD0) + 0x110;
    *(s32 *)(p + 0x24) = 0;
    func_15131CAC(arg0);
}

void func_15101830(struct210 *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0xD0) + 0x110;
    *(s32 *)(p + 0x24) = 0;
    func_15131CCC(arg0);
}

void func_15101858(struct210 *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0x170) + 0x110;
    *(s32 *)(p + 0x30) = 0;
    func_151411A4(arg0);
}

void func_15101880(struct210 *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0x170) + 0x110;
    *(s32 *)(p + 0x30) = 0;
    func_151411C4(arg0);
}

void func_151018A8(struct210 *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0xA8) + 0x110;
    *(s32 *)(p + 0x34) = 0;
    func_15131CAC(arg0);
}

void func_151018D0(struct210 *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0xA8) + 0x110;
    *(s32 *)(p + 0x34) = 0;
    func_15131CCC(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E390/func_151018F8.s")

#ifdef NON_MATCHING
u8 *func_15101F44(u8 *arg0, s16 arg1) {
    struct {
        u8 u67;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        u8 pad84[0x8];
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        u8 pad9C[0xC];
        f32 uA8;
        f32 uAC;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 * uC0;
        u8 * uC4;
        u8 * uC8;
    } sp;
    u8 *sp48;
    u8 *sp44;
    u8 *sp40;
    f32 sp3C;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 *temp_v0_2;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f4;
    f32 temp_f6;
    f32 temp_f6_2;
    f32 temp_f8;
    f32 var_f14;
    f32 var_f6;
    s16 temp_a1;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_a1_2;
    u8 *temp_t0;
    u8 *temp_t2;
    u8 *temp_t5;
    u8 *temp_t6;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_a1 = arg1;
    temp_t0 = arg0 + 0x110;
    if ((temp_a1 == (*(u8 *)((u8 *)arg0 + 0x132))) && ((temp_v0 = (*(u8 **)((u8 *)arg0 + 0x110)), (temp_v0 == NULL)) || ((*(u8 *)((u8 *)((*(u8 **)((u8 *)temp_v0 + 0x31C))) + 0x197)) != 0))) {
        goto block_23;
    }
    if ((*(u8 *)((u8 *)temp_t0 + 0x23)) & 1) {
        arg1 = temp_a1;
        sp48 = temp_t0;
        func_151D6310(arg0 + 0x100, temp_a1, 0x40, &sp.uC8, &sp.u67);
        sp.uC4 = sp.uC8;
        if (sp.uC8 != NULL) {
            if (sp.u67 != 0) {
                temp_v1 = arg0 + (arg1 * 4);
                temp_a1_2 = arg0 + 0xC0;
                sp40 = temp_a1_2;
                sp44 = temp_v1;
                memcpy((*(s32 *)((u8 *)temp_v1 + 0x100)), temp_a1_2, 0x40);
                memcpy((*(s32 *)((u8 *)temp_v1 + 0x100)) + 0x40, temp_a1_2, 0x40);
            }
            temp_v0_2 = func_15144B34((s32) arg1);
            (*(f32 *)((u8 *)(&sp.u78) + 0)) = (*(f32 *)((u8 *)arg0 + 0x34));
            (*(s32 *)((u8 *)(&sp.u78) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 0x38));
            (*(s32 *)((u8 *)(&sp.u78) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0x3C));
            temp_f2 = (*(f32 *)((u8 *)sp48 + 0x44));
            if (temp_f2 > 3508.0f) {
                temp_f0 = 3508.0f / temp_f2;
                temp_f8 = ((*(f32 *)((u8 *)arg0 + 0x40)) - sp.u78) * temp_f0;
                sp.uB4 = temp_f8;
                sp28 = sp.u78;
                temp_f10 = ((*(f32 *)((u8 *)arg0 + 0x44)) - sp.u7C) * temp_f0;
                sp.uB8 = temp_f10;
                sp2C = temp_f8;
                sp30 = sp.u7C;
                temp_f6 = sp2C;
                sp2C = temp_f10;
                sp.u68 = 3508.0f;
                temp_f4 = ((*(f32 *)((u8 *)arg0 + 0x48)) - sp.u80) * temp_f0;
                sp.u6C = sp28 + temp_f6;
                sp.uBC = temp_f4;
                sp.u70 = sp30 + sp2C;
                sp.u74 = sp.u80 + temp_f4;
            } else {
                (*(f32 *)((u8 *)(&sp.u6C) + 0)) = (*(f32 *)((u8 *)arg0 + 0x40));
                (*(f32 *)((u8 *)(&sp.u6C) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 0x44));
                (*(f32 *)((u8 *)(&sp.u6C) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 0x48));
                sp.uB4 = sp.u6C - sp.u78;
                sp.uB8 = sp.u70 - sp.u7C;
                sp.uBC = sp.u74 - sp.u80;
                sp.u68 = (*(f32 *)((u8 *)sp48 + 0x44));
            }
            sp.uC0 = temp_v0_2;
            func_15145548(3508.0f, &sp.u78, &sp.uB4, temp_v0_2, &sp.uA8, 0);
            temp_f0_2 = sp.uA8 - (*(f32 *)((u8 *)sp.uC0 + 0));
            temp_f2_2 = sp.uAC - (*(f32 *)((u8 *)sp.uC0 + 4));
            temp_f12 = sp.uB0 - (*(f32 *)((u8 *)sp.uC0 + 8));
            temp_f16 = (sp.uB8 * temp_f12) - (temp_f2_2 * sp.uBC);
            temp_f18 = (sp.uBC * temp_f0_2) - (temp_f12 * sp.uB4);
            temp_f6_2 = (sp.uB4 * temp_f2_2) - (temp_f0_2 * sp.uB8);
            sp3C = temp_f6_2;
            temp_f14 = (temp_f16 * temp_f16) + (temp_f18 * temp_f18) + (temp_f6_2 * temp_f6_2);
            sp.u8C = temp_f14;
            if (temp_f14 == 0.0f) {
                var_f6 = 0.0f;
                var_f14 = 0.0f;
                sp.u94 = 0.0f;
            } else {
                temp_f2_3 = (*(f32 *)((u8 *)sp48 + 0x38)) / sqrtf(sp.u8C);
                var_f14 = temp_f16 * temp_f2_3;
                var_f6 = sp3C * temp_f2_3;
                sp.u94 = temp_f18 * temp_f2_3;
            }
            sp.u98 = var_f6;
            sp.u90 = var_f14;
            temp_f2_4 = (*(f32 *)((u8 *)sp48 + 0x58));
            var_a0 = (s32) temp_f2_4;
            var_v1 = (s32) (temp_f2_4 + (sp.u68 * ((*(f32 *)((u8 *)sp48 + 0x48)) + ((*(f32 *)((u8 *)sp48 + 0x4C)) * sinf((*(f32 *)((u8 *)sp48 + 0x50)))))));
            if ((var_v1 >= 0x8000) || (var_a0 < -0x8000)) {
                var_v0 = var_a0;
                if (var_a0 >= 0x2001) {
                    do {
                        var_v0 -= 0x2000;
                    } while (var_v0 >= 0x2001);
                }
                if (var_v0 < 0) {
                    do {
                        var_v0 += 0x2000;
                    } while (var_v0 < 0);
                }
                temp_v1_2 = var_v0 + (var_v1 - var_a0);
                var_a0 = var_v0 - 0x8000;
                var_v1 = temp_v1_2 - 0x8000;
            }
            (*(s16 *)((u8 *)sp.uC8 + 0)) = (s16) (s32) (sp.u6C + var_f14);
            (*(s16 *)((u8 *)sp.uC8 + 2)) = (s16) (s32) (sp.u70 + sp.u94);
            (*(s16 *)((u8 *)sp.uC8 + 4)) = (s16) (s32) (sp.u74 + sp.u98);
            (*(s16 *)((u8 *)sp.uC8 + 0xA)) = 0;
            (*(s16 *)((u8 *)sp.uC8 + 8)) = (s16) var_v1;
            (*(s16 *)((u8 *)sp.uC8 + 6)) = 0;
            temp_t2 = sp.uC8 + 0x10;
            sp.uC8 = temp_t2;
            (*(s16 *)((u8 *)temp_t2 + 0)) = (s16) (s32) (sp.u6C - var_f14);
            (*(s16 *)((u8 *)sp.uC8 + 2)) = (s16) (s32) (sp.u70 - sp.u94);
            (*(s16 *)((u8 *)sp.uC8 + 4)) = (s16) (s32) (sp.u74 - sp.u98);
            (*(s16 *)((u8 *)sp.uC8 + 0xA)) = 0x7C0;
            (*(s16 *)((u8 *)sp.uC8 + 8)) = (s16) var_v1;
            (*(s16 *)((u8 *)temp_t2 + 6)) = 0;
            temp_t6 = sp.uC8 + 0x10;
            sp.uC8 = temp_t6;
            (*(s16 *)((u8 *)temp_t6 + 0)) = (s16) (s32) (sp.u78 - var_f14);
            (*(s16 *)((u8 *)sp.uC8 + 2)) = (s16) (s32) (sp.u7C - sp.u94);
            (*(s16 *)((u8 *)sp.uC8 + 4)) = (s16) (s32) (sp.u80 - sp.u98);
            (*(s16 *)((u8 *)sp.uC8 + 0xA)) = 0x7C0;
            (*(s16 *)((u8 *)sp.uC8 + 8)) = (s16) var_a0;
            (*(s16 *)((u8 *)temp_t6 + 6)) = 0;
            temp_t5 = sp.uC8 + 0x10;
            sp.uC8 = temp_t5;
            (*(s16 *)((u8 *)temp_t5 + 0)) = (s16) (s32) (sp.u78 + var_f14);
            (*(s16 *)((u8 *)sp.uC8 + 2)) = (s16) (s32) (sp.u7C + sp.u94);
            (*(s16 *)((u8 *)sp.uC8 + 4)) = (s16) (s32) (sp.u80 + sp.u98);
            (*(s16 *)((u8 *)sp.uC8 + 0xA)) = 0;
            (*(s16 *)((u8 *)sp.uC8 + 8)) = (s16) var_a0;
            (*(s16 *)((u8 *)temp_t5 + 6)) = 0;
            return sp.uC4;
        }
        goto block_23;
    }
block_23:
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E390/func_15101F44.s")
#endif
#ifdef NON_MATCHING
s32 func_15144E80(u8 *, f32 *, f32 *, s32);
s32 func_15145128(f32 *, f32 *, s32, s32);
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
s32 memcpy(s32, s32, s32);

u8 *func_151024D0(u8 *arg0, s16 arg1) {
    struct {
        u8 u33;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        u8 * u4C;
        u8 * u50;
    } sp;
    u8 *sp2C;
    s32 sp28;
    f32 temp_f4;
    f32 temp_f8;
    s32 temp_a1;
    u8 *temp_v1;

    func_151D6310(arg0 + 0x100, arg1, 0x40, &sp.u50, &sp.u33);
    sp.u4C = sp.u50;
    if (sp.u50 != NULL) {
        if (sp.u33 != 0) {
            temp_v1 = arg0 + (arg1 * 4);
            temp_a1 = arg0 + 0xC0;
            sp28 = temp_a1;
            sp2C = temp_v1;
            memcpy((*(s32 *)((u8 *)temp_v1 + 0x100)), temp_a1, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v1 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        if (!((*(u8 *)((u8 *)arg0 + 0x110)) & 1)) {
            return NULL;
        }
        if (func_15144E80(arg0 + 0x112, &sp.u40, &sp.u34, 0) == 0) {
            return NULL;
        }
        func_15145128(&sp.u40, &sp.u40, 0, 0);
        func_15145128(&sp.u34, &sp.u34, 0, 0);
        temp_f8 = sp.u40 * (*(f32 *)((u8 *)arg0 + 0x2C));
        sp.u40 = temp_f8;
        sp.u44 *= (*(f32 *)((u8 *)arg0 + 0x2C));
        sp.u48 *= (*(f32 *)((u8 *)arg0 + 0x2C));
        temp_f4 = sp.u34 * (*(f32 *)((u8 *)arg0 + 0x30));
        sp.u34 = temp_f4;
        sp.u38 *= (*(f32 *)((u8 *)arg0 + 0x30));
        sp.u3C *= (*(f32 *)((u8 *)arg0 + 0x30));
        (*(s16 *)((u8 *)sp.u50 + 0)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f8) + temp_f4);
        (*(s16 *)((u8 *)sp.u50 + 2)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x38)) - sp.u44) + sp.u38);
        (*(s16 *)((u8 *)sp.u50 + 4)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x3C)) - sp.u48) + sp.u3C);
        (*(s16 *)((u8 *)sp.u50 + 6)) = 0;
        (*(s16 *)((u8 *)sp.u50 + 0x10)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f8 + temp_f4);
        (*(s16 *)((u8 *)sp.u50 + 0x12)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + sp.u44 + sp.u38);
        (*(s16 *)((u8 *)sp.u50 + 0x14)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + sp.u48 + sp.u3C);
        (*(s16 *)((u8 *)sp.u50 + 0x16)) = 0;
        (*(s16 *)((u8 *)sp.u50 + 0x20)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f8) - temp_f4);
        (*(s16 *)((u8 *)sp.u50 + 0x22)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x38)) + sp.u44) - sp.u38);
        (*(s16 *)((u8 *)sp.u50 + 0x24)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x3C)) + sp.u48) - sp.u3C);
        (*(s16 *)((u8 *)sp.u50 + 0x26)) = 0;
        (*(s16 *)((u8 *)sp.u50 + 0x30)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f8) - temp_f4);
        (*(s16 *)((u8 *)sp.u50 + 0x32)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x38)) - sp.u44) - sp.u38);
        (*(s16 *)((u8 *)sp.u50 + 0x34)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x3C)) - sp.u48) - sp.u3C);
        (*(s16 *)((u8 *)sp.u50 + 0x36)) = 0;
        return sp.u4C;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E390/func_151024D0.s")
#endif
#ifdef NON_MATCHING
s32 func_1510282C(u8 *arg0) {
    u8 *sp28;
    u8 *sp24;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    u32 temp_t7;
    u8 *temp_s0;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_4;
    u8 *temp_v0_5;

    (*(f32 *)((u8 *)arg0 + 0x160)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x160)) + ((*(f32 *)((u8 *)arg0 + 0x164)) * D_800BE9A4));
    temp_s0 = arg0 + 0x110;
    (*(f32 *)((u8 *)temp_s0 + 0x50)) = func_15144B68((*(f32 *)((u8 *)arg0 + 0x160)));
    (*(f32 *)((u8 *)temp_s0 + 0x58)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x58)) + ((*(f32 *)((u8 *)temp_s0 + 0x5C)) * D_800BE9A4));
    if ((*(f32 *)((u8 *)temp_s0 + 0x58)) > 32767.0f) {
        do {
            (*(f32 *)((u8 *)temp_s0 + 0x58)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x58)) - 65536.0f);
        } while ((*(f32 *)((u8 *)temp_s0 + 0x58)) > 32767.0f);
    }
    if ((*(f32 *)((u8 *)temp_s0 + 0x58)) < -32768.0f) {
        do {
            (*(f32 *)((u8 *)temp_s0 + 0x58)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x58)) + 65536.0f);
        } while ((*(f32 *)((u8 *)temp_s0 + 0x58)) < -32768.0f);
    }
    (*(f32 *)((u8 *)temp_s0 + 0x68)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x68)) - D_800BE9A4);
    if ((*(f32 *)((u8 *)temp_s0 + 0x68)) < 0.0f) {
        (*(f32 *)((u8 *)temp_s0 + 0x68)) = (f32) (func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 0x6C)));
        temp_f2 = (*(f32 *)((u8 *)temp_s0 + 0x64));
        (*(f32 *)((u8 *)temp_s0 + 0x60)) = (f32) ((func_150ADA68() * (2.0f * temp_f2)) - temp_f2);
    }
    temp_f2_2 = (*(f32 *)((u8 *)temp_s0 + 0x5C));
    temp_f0 = (*(f32 *)((u8 *)temp_s0 + 0x38));
    temp_v0 = (*(u8 **)((u8 *)temp_s0 + 0x28));
    (*(f32 *)((u8 *)temp_s0 + 0x5C)) = (f32) (temp_f2_2 + (((*(f32 *)((u8 *)temp_s0 + 0x60)) - temp_f2_2) * (*(f32 *)((u8 *)temp_s0 + 0x70))));
    (*(f32 *)((u8 *)temp_s0 + 0x38)) = (f32) (temp_f0 + (((*(f32 *)((u8 *)temp_s0 + 0x3C)) - temp_f0) * (*(f32 *)((u8 *)temp_s0 + 0x40))));
    if (temp_v0 != NULL) {
        sp28 = temp_v0;
        temp_f2_3 = ((func_150ADA68() * 0.2f) + 0.4f) * (*(f32 *)((u8 *)temp_s0 + 0x38));
        (*(f32 *)((u8 *)sp28 + 0x30)) = temp_f2_3;
        (*(f32 *)((u8 *)sp28 + 0x2C)) = temp_f2_3;
    }
    (*(f32 *)((u8 *)temp_s0 + 0x84)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x84)) - D_800BE9A4);
    if ((*(f32 *)((u8 *)temp_s0 + 0x84)) < 0.0f) {
        (*(f32 *)((u8 *)temp_s0 + 0x84)) = (f32) (func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 0x88)));
        (*(f32 *)((u8 *)temp_s0 + 0x78)) = (f32) ((func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 0x80))) + (*(f32 *)((u8 *)temp_s0 + 0x7C)));
    }
    temp_f0_2 = (*(f32 *)((u8 *)temp_s0 + 0x74));
    (*(f32 *)((u8 *)temp_s0 + 0x74)) = (f32) (temp_f0_2 + (((*(f32 *)((u8 *)temp_s0 + 0x78)) - temp_f0_2) * (*(f32 *)((u8 *)temp_s0 + 0x8C))));
    temp_t7 = (u32) (*(f32 *)((u8 *)temp_s0 + 0x74));
    (*(u8 *)((u8 *)arg0 + 0x5C)) = (u8) temp_t7;
    temp_v0_2 = (*(u8 **)((u8 *)temp_s0 + 0x28));
    if (temp_v0_2 != NULL) {
        (*(s8 *)((u8 *)temp_v0_2 + 0x5C)) = (s8) temp_t7;
    }
    temp_v0_3 = (*(u8 **)((u8 *)temp_s0 + 0x24));
    if (temp_v0_3 != NULL) {
        (*(u8 *)((u8 *)temp_v0_3 + 0x2B)) = (u8) (*(u8 *)((u8 *)arg0 + 0x5C));
    }
    temp_v0_4 = (*(u8 **)((u8 *)temp_s0 + 0x2C));
    if (temp_v0_4 != NULL) {
        sp24 = temp_v0_4;
        (*(s8 *)((u8 *)((*(u8 **)((u8 *)sp24 + 0x14))) + 0x2F)) = (s8) ((func_150ADA20() & 3) + 2);
    }
    temp_v0_5 = (*(u8 **)((u8 *)temp_s0 + 0x34));
    if (temp_v0_5 != NULL) {
        temp_f2_4 = (func_150ADA68() * 10.0f) + 120.0f;
        (*(f32 *)((u8 *)temp_v0_5 + 0x3C)) = temp_f2_4;
        (*(f32 *)((u8 *)temp_v0_5 + 0x38)) = temp_f2_4;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E390/func_1510282C.s")
#endif
#ifdef NON_MATCHING
s32 func_15102B74(u8 *arg0, s32 arg1) {
    f32 sp24;
    f32 temp_f10;
    u8 *temp_s0;

    sp24 = sinf((*(f32 *)((u8 *)arg0 + 0xC0)));
    temp_s0 = arg0 + 0xA8;
    temp_f10 = (*(f32 *)((u8 *)temp_s0 + 0xC)) + ((*(f32 *)((u8 *)temp_s0 + 0x14)) * sinf((*(f32 *)((u8 *)arg0 + 0xC4))));
    (*(f32 *)((u8 *)temp_s0 + 0)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 8)) + ((*(f32 *)((u8 *)temp_s0 + 0x10)) * sp24));
    (*(f32 *)((u8 *)temp_s0 + 4)) = temp_f10;
    (*(f32 *)((u8 *)temp_s0 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x18)) + ((*(f32 *)((u8 *)temp_s0 + 0x20)) * D_800BE9A4));
    (*(f32 *)((u8 *)temp_s0 + 0x1C)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x1C)) + ((*(f32 *)((u8 *)temp_s0 + 0x24)) * D_800BE9A4));
    (*(f32 *)((u8 *)temp_s0 + 0x18)) = func_15144B68((*(f32 *)((u8 *)temp_s0 + 0x18)));
    (*(f32 *)((u8 *)temp_s0 + 0x1C)) = func_15144B68((*(f32 *)((u8 *)temp_s0 + 0x1C)));
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E390/func_15102B74.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E390/func_15102C3C.s")

void func_151027E8(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151403A8(&tmp, 0x1A);
}

s32 func_15102D9C(u8 *arg0, s16 arg1) {
    u8 *p;
    u8 *q;
    p = *(u8 **)(arg0 + 0xD0);
    if (arg1 == p[0x132]) {
        p = p + 0x110;
        if (!arg0 && !arg0 && !arg0) {} // fakematch: permuter artifact, hoists the +0x110 above the compare
        q = *(u8 **)p;
        if (q == NULL || (*(u8 **)(q + 0x31C))[0x197] != 0) {
            return 0;
        }
    }
    if (!(arg0[0xD4] & 1)) {
        return 0;
    }
    return 1;
}

s32 func_15102E04(u8 *arg0, s32 arg1) {
    s32 ret = 1;
    if (!(arg0[0xAC] & 1)) {
        return 0;
    }
    return ret;
}

s32 func_15102E2C(u8 *arg0, s16 arg1) {
    u8 *p;
    u8 *q;
    p = *(u8 **)(arg0 + 0x170);
    if (arg1 == p[0x132]) {
        p = p + 0x110;
        if (!arg0 && !arg0 && !arg0) {} // fakematch: permuter artifact, hoists the +0x110 above the compare
        q = *(u8 **)p;
        if (q == NULL || (*(u8 **)(q + 0x31C))[0x197] != 0) {
            return 0;
        }
    }
    if (!(arg0[0x174] & 1)) {
        return 0;
    }
    return 1;
}
