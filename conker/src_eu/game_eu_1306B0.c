#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 func_1510FE4C(s32);

struct210 *func_15102EA0(f32 arg0, u8 arg1, s32 arg2, u8 *arg3, s16 arg4, u8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9) {
    struct {
        s32 u64;
        s16 u68;
        s8 u6A;
        s8 u6B;
        s32 u6C;
        s32 u70;
        u8 u74;
        s8 u75;
        s8 u76;
        s8 u77;
        s8 u78;
        s8 u79;
        s8 u7A;
        s8 u7B;
        s32 u7C;
        u8 pad80[0x6];
        s16 u86;
        s16 u88;
    } sp;
    s32 sp60;
    s32 sp5C;
    s32 sp50;
    s32 sp4C;
    s32 temp_v0;
    s32 var_v1;
    s32 var_v1_2;

    sp.u86 = 0xA;
    sp.u88 = 0x19;
    temp_v0 = func_1510FE4C(arg7);
    sp.u6A = 0x5C;
    if (D_800BE9F0 != 0x26) {
        if (D_800BE9F0 == 0x36) {
            if (temp_v0 == 9) {
                return NULL;
            }
            sp.u6A = 0x85;
            arg0 *= 0.6f;
            goto block_7;
        }
        goto block_7;
    }
    if (temp_v0 == 2) {
        return NULL;
    }
block_7:
    sp.u6B = 0;
    if (arg4 == -1) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    sp.u64 = var_v1 | 0x9700 | 0x20000;
    if (arg4 == -1) {
        sp.u68 = 0x12C;
    } else {
        sp.u68 = arg4;
    }
    sp.u6C = 0;
    sp.u70 = 0;
    if (D_800BE9F0 == 0x36) {
        sp.u74 = (u8) ((s32) arg1 >> 1);
    } else {
        sp.u74 = arg1;
    }
    sp.u75 = 0xFF;
    sp.u78 = 0;
    sp.u77 = 0;
    sp.u76 = 0;
    sp.u79 = 0xFF;
    if (arg6 != 0) {
        var_v1_2 = 2;
    } else {
        var_v1_2 = 1;
    }
    sp.u7C = var_v1_2 + 0x3B0000;
    sp.u7A = 0;
    sp.u7B = 7;
    if (arg5 != 0) {
        sp60 = 3;
        sp5C = 0xFF;
    } else {
        sp60 = 0;
        sp5C = 0;
    }
    sp4C = func_150ADA20();
    sp50 = func_150ADA20();
    return func_1513C650((s32) &sp.u64, 0U, 0U, arg2, (*(f32 *)((u8 *)arg3 + 0)), (*(f32 *)((u8 *)arg3 + 4)), (*(f32 *)((u8 *)arg3 + 8)), arg0, arg0, (u8) (sp4C & 0xFF), (u8) (((func_150ADA20() & 1) * 2) + (sp50 & 1)), sp60, sp5C, 0, (u8) (s32) arg8, arg9);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1306B0/func_15102EA0.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1306B0/func_151030B8.s")

void func_151032D0(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x110, arg0 + 0x114, arg0);
}

#ifdef NON_MATCHING
u8 * func_15031C4C(u8 *arg0, s32 arg1, s32 arg2);
void func_15145EA4(f32 **arg0, f32 **arg1, Mtx *arg2, s32 arg3);
s32 func_1514654C(u8 *, s32, s32, u8 **, u8 **, s32);

// attached_points_update: refreshes the two attachment points of arg0 (arg0 + 0x34 / + 0x40) from its owner
// (arg0 + 0x110): 0 when the owner changed or is gone, 1 when it has no model / is hidden or after the update. With
// a joint id (+0x11C != -1) the points come from that joint (func_1514654C), else from the owner's matrix list
// (func_15145EA4); sets bit 0 of +0x124 on success. P124: the point lists are 2-element arrays (m2c had 4 locals).
s32 func_15103310(u8 *arg0) {
    u8 *dst[2];
    u8 *src[2];
    s16 joint;
    s32 node;
    u8 *att;
    u8 *owner;

    owner = *(u8 **)(arg0 + 0x110);
    arg0[0x124] &= 0xFE;
    if (arg0[0x114] != owner[0x3B] || *(s32 *)(owner + 0) == 0) {
        return 0;
    }
    if (*(s32 *)(owner + 0x1D4) == 0 || (owner[0x74] & 0xF) == 0xF) {
        return 1;
    }
    att = arg0 + 0x110;
    dst[0] = arg0 + 0x34;
    dst[1] = arg0 + 0x40;
    src[0] = att + 0x18;
    src[1] = att + 0x24;
    joint = *(s16 *)(att + 0xC);
    if (joint != -1) {
        node = (s32) func_15031C4C(owner, joint, 0);
        if (node == 0) {
            return 0;
        }
        if (func_1514654C(owner, node, *(s32 *)(att + 0x10), dst, src, 2) == 0) {
            return 0;
        }
    } else {
        func_15145EA4((f32 **) dst, (f32 **) src, (Mtx *) (*(s32 *)(owner + 0x1D4) + *(s32 *)(att + 8)), 2);
    }
    att[0x14] |= 1;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1306B0/func_15103310.s")
#endif
#ifdef NON_MATCHING
s32 memcpy(s32, u8 *, s32);

s16 *func_15103438(u8 *arg0, s16 arg1) {
    struct {
        u8 u43;
        f32 u44;
        s32 u48;
        s16 * u4C;
        s16 * u50;
        u8 pad54[0x18];
        f32 u6C;
        f32 u70;
        f32 u74;
        u8 pad78[0x4];
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
    } sp;
    u8 *sp38;
    u8 *sp34;
    f32 sp30;
    f32 sp2C;
    f32 *temp_s1;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f18;
    f32 temp_f18_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f6;
    f32 temp_f6_2;
    f32 var_f12;
    f32 var_f14;
    f32 var_f16;
    s16 *temp_t4;
    s16 *temp_t6;
    s16 *temp_t7;
    u8 *temp_a1;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_s1 = func_15144B34((s32) arg1);
    if (!((*(u8 *)((u8 *)arg0 + 0x124)) & 1)) {
        return NULL;
    }
    func_151D6310(arg0 + 0x100, arg1, 0x40, &sp.u50, &sp.u43);
    sp.u4C = sp.u50;
    if (sp.u50 != NULL) {
        if (sp.u43 != 0) {
            temp_v1 = arg0 + (arg1 * 4);
            temp_a1 = arg0 + 0xC0;
            sp34 = temp_a1;
            sp38 = temp_v1;
            memcpy((*(s32 *)((u8 *)temp_v1 + 0x100)), temp_a1, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v1 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_v0 = arg0 + 0x110;
        temp_f2 = (*(f32 *)((u8 *)temp_v0 + 0x18));
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x30));
        temp_f12 = (*(f32 *)((u8 *)temp_v0 + 0x1C));
        temp_f14 = (*(f32 *)((u8 *)temp_v0 + 0x20));
        temp_f16 = temp_f2 + (((*(f32 *)((u8 *)temp_v0 + 0x24)) - temp_f2) * temp_f0);
        temp_f18 = temp_f12 + (((*(f32 *)((u8 *)temp_v0 + 0x28)) - temp_f12) * temp_f0);
        sp.u7C = temp_f16 - temp_f2;
        temp_f6 = temp_f14 + (((*(f32 *)((u8 *)temp_v0 + 0x2C)) - temp_f14) * temp_f0);
        sp.u90 = temp_f6;
        sp.u80 = temp_f18 - (*(f32 *)((u8 *)temp_v0 + 0x1C));
        sp.u8C = temp_f18;
        sp.u88 = temp_f16;
        sp38 = temp_v0;
        sp.u84 = temp_f6 - (*(f32 *)((u8 *)temp_v0 + 0x20));
        func_15145548(temp_f12, temp_f14, temp_v0 + 0x18, &sp.u7C, temp_s1, &sp.u6C, &sp.u48);
        temp_f0_2 = sp.u6C - (*(f32 *)((u8 *)temp_s1 + 0));
        temp_f2_2 = sp.u70 - (*(f32 *)((u8 *)temp_s1 + 4));
        temp_f12_2 = sp.u74 - (*(f32 *)((u8 *)temp_s1 + 8));
        temp_f18_2 = (sp.u80 * temp_f12_2) - (temp_f2_2 * sp.u84);
        temp_f16_2 = (sp.u84 * temp_f0_2) - (temp_f12_2 * sp.u7C);
        sp30 = temp_f16_2;
        temp_f6_2 = (sp.u7C * temp_f2_2) - (temp_f0_2 * sp.u80);
        sp2C = temp_f6_2;
        temp_f14_2 = (temp_f18_2 * temp_f18_2) + (temp_f16_2 * temp_f16_2) + (temp_f6_2 * temp_f6_2);
        sp.u44 = temp_f14_2;
        if (temp_f14_2 == 0.0f) {
            var_f16 = 0.0f;
            var_f12 = 0.0f;
            var_f14 = 0.0f;
        } else {
            temp_f2_3 = (*(f32 *)((u8 *)arg0 + 0x2C)) / sqrtf(sp.u44);
            var_f12 = temp_f18_2 * temp_f2_3;
            var_f14 = sp30 * temp_f2_3;
            var_f16 = sp2C * temp_f2_3;
        }
        (*(s16 *)((u8 *)sp.u50 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)sp38 + 0x18)) + var_f12);
        (*(s16 *)((u8 *)sp.u50 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)sp38 + 0x1C)) + var_f14);
        (*(s16 *)((u8 *)sp.u50 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)sp38 + 0x20)) + var_f16);
        (*(s16 *)((u8 *)sp.u50 + 6)) = 0;
        temp_t4 = sp.u50 + 0x10;
        sp.u50 = temp_t4;
        *temp_t4 = (s16) (s32) (sp.u88 + var_f12);
        (*(s16 *)((u8 *)sp.u50 + 2)) = (s16) (s32) (sp.u8C + var_f14);
        (*(s16 *)((u8 *)sp.u50 + 4)) = (s16) (s32) (sp.u90 + var_f16);
        (*(s16 *)((u8 *)sp.u50 + 6)) = 0;
        temp_t6 = sp.u50 + 0x10;
        sp.u50 = temp_t6;
        *temp_t6 = (s16) (s32) (sp.u88 - var_f12);
        (*(s16 *)((u8 *)sp.u50 + 2)) = (s16) (s32) (sp.u8C - var_f14);
        (*(s16 *)((u8 *)sp.u50 + 4)) = (s16) (s32) (sp.u90 - var_f16);
        (*(s16 *)((u8 *)sp.u50 + 6)) = 0;
        temp_t7 = sp.u50 + 0x10;
        sp.u50 = temp_t7;
        *temp_t7 = (s16) (s32) ((*(f32 *)((u8 *)sp38 + 0x18)) - var_f12);
        (*(s16 *)((u8 *)sp.u50 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)sp38 + 0x1C)) - var_f14);
        (*(s16 *)((u8 *)sp.u50 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)sp38 + 0x20)) - var_f16);
        (*(s16 *)((u8 *)sp.u50 + 6)) = 0;
        return sp.u4C;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1306B0/func_15103438.s")
#endif
#ifdef NON_MATCHING
s32 func_151308E4(s32 *, s32, s32, u8, s32);
extern s32 D_80088F70;

void func_151037D4(s16 arg0, u8 arg1, f32 arg2, u8 *arg3, u8 arg4, u8 arg5, s32 arg6) {
    struct {
        s32 u2C;
        s32 u30;
        s16 u34;
        s16 u36;
        s32 u38;
        s32 u3C;
        s8 u40;
        s8 u41;
        s8 u42;
        s8 u43;
        s8 u44;
        s8 u45;
        s8 u46;
        u8 u47;
        s8 u48;
        s8 u49;
        s16 u4A;
        s16 u4C;
        s16 u4E;
        f32 u50;
        f32 u54;
        f32 u58;
        s32 u5C;
        u8 pad60[0x8];
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        s32 u84;
        u8 pad88[0x4];
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        s8 u90;
        s8 u91;
        u8 u92;
    } sp;
    s32 sp24;
    s32 temp_t8;
    s32 var_v0;
    s32 var_v1;

    temp_t8 = *(((s32 *)((u8 *)&D_80088F70 + ((func_150ADA20() & 3) * 4))));
    sp.u30 = 0x20000;
    sp.u40 = 0xFF;
    sp.u34 = 0x2203;
    sp.u2C = 0x200005;
    sp.u49 = (s8) temp_t8;
    sp.u36 = arg0 + 1;
    sp.u38 = 0;
    sp.u3C = 0;
    sp.u41 = 0xFF;
    sp.u42 = 0xFF;
    sp.u43 = 0xFF;
    sp.u44 = 0xFF;
    sp.u45 = 0xFF;
    sp.u46 = 0xFF;
    sp.u48 = 0xFF;
    sp.u58 = arg2;
    sp.u54 = arg2;
    sp.u47 = arg1;
    (*(s32 *)((u8 *)(&sp.u5C) + 0)) = (s32) (*(s32 *)((u8 *)arg3 + 0));
    (*(s32 *)((u8 *)(&sp.u5C) + 4)) = (s32) (*(s32 *)((u8 *)arg3 + 4));
    (*(s32 *)((u8 *)(&sp.u5C) + 8)) = (s32) (*(s32 *)((u8 *)arg3 + 8));
    sp.u4A = 3;
    sp.u4C = 0x55;
    sp.u4E = 1;
    sp.u68 = 0.0f;
    sp.u6C = 0.0f;
    sp.u70 = 0.0f;
    sp.u74 = 0.0f;
    sp.u78 = 0.0f;
    sp.u7C = 0.0f;
    sp.u80 = 0.0f;
    sp.u50 = 1.0f;
    var_v1 = 0;
    if (func_150ADA20() & 1) {
        var_v1 = 0x40;
    }
    sp24 = var_v1;
    if (func_150ADA20() & 1) {
        var_v0 = 0x80;
    } else {
        var_v0 = 0;
    }
    sp.u84 = var_v0 | 1 | var_v1 | 0xC200 | 0x40000 | 0x800000;
    sp.u8C = 6;
    sp.u8D = 8;
    sp.u8E = -1;
    sp.u8F = -1;
    sp.u90 = -1;
    sp.u91 = 0;
    sp.u92 = arg4;
    func_151308E4(&sp.u2C, 1, 0, arg5, arg6);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1306B0/func_151037D4.s")
#endif