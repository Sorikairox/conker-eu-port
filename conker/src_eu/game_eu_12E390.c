#include <ultra64.h>
#include "functions.h"
#include "variables.h"


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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E390/func_15101F44.s")

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
