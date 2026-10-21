#include <ultra64.h>
#include "functions.h"
#include "variables.h"


u8 *func_15164CF0(u8 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    u8 *p;
    struct127 *obj;
    struct108 *e;

    e = &D_800DBFF0[arg0[6]];
    obj = e->unk3D0;
    if (obj != NULL && obj->unk31C != NULL && obj->unk31C->unk198 != 0) {
        return NULL;
    }
    p = func_15167A68(0x39, arg3, arg1 + 0x68, 1, arg2, 1);
    if (p == NULL) {
        return NULL;
    }
    memcpy(p + 0x10, arg0, 0x38);
    p[0x60] = 1;
    p[0x61] = 1;
    p[0x62] = 1;
    p[0x63] = 1;
    p[0x64] = 1;
    p[0x65] = 1;
    *(f32 *)(p + 0x48) = 0.0f;
    *(f32 *)(p + 0x4C) = 0.0f;
    *(f32 *)(p + 0x50) = 0.0f;
    *(f32 *)(p + 0x54) = 0.0f;
    *(f32 *)(p + 0x58) = 0.0f;
    *(f32 *)(p + 0x5C) = 0.0f;
    return p;
}

void func_15164DF8(u8 *arg0) {
    arg0[0x10] |= 2;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_192500/func_15164E0C.s")

void func_15165454(void) {
    bzero(D_800DD210, 0x60);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_192500/func_1516547C.s")

#ifdef NON_MATCHING
u8 *func_15165B98(u8 *arg0, s32 arg1, s8 arg2, s32 arg3, u8 arg4, s32 arg5) {
    struct {
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        s32 u98;
        u8 pad9C[0x8];
        s32 uA4;
        u8 padA8[0x8];
        s32 uB0;
        u8 padB4[0x8];
        s32 uBC;
        u8 padC0[0x8];
        f32 uC8;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        u8 uD8;
        s8 uD9;
        s8 uDA;
        u8 padDB[0x1];
        s16 uDC;
        s8 uDE;
        u8 padDF[0x1];
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        f32 uF4;
        f32 uF8;
        f32 uFC;
        f32 u100;
        f32 u104;
        f32 u108;
        f32 u10C;
    } sp;
    f32 temp_f0;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f2;
    u8 *temp_v0;

    temp_f14 = (*(f32 *)((u8 *)arg0 + 0x30));
    if ((temp_f14 == 0.0f) || (temp_f16 = (*(f32 *)((u8 *)arg0 + 0x38)), (temp_f16 == 0.0f))) {
        return NULL;
    }
    temp_f0 = 1.0f / temp_f14;
    sp.uD8 = 4;
    sp.uD9 = 0;
    sp.uDC = 0x12C;
    sp.uDE = arg1 & 0xFF;
    sp.uDA = arg2;
    sp.uE0 = 0.0f;
    sp.uE4 = 0.0f;
    sp.uE8 = 0.0f;
    sp.uEC = 0.0f;
    sp.uF0 = 0.0f;
    sp.uF4 = 0.0f;
    sp.uF8 = 0.0f;
    sp.uFC = 0.0f;
    sp.u100 = 0.0f;
    sp.u104 = 0.0f;
    sp.u108 = 0.0f;
    sp.u10C = 0.0f;
    temp_f2 = 1.0f / temp_f16;
    sp.u38 = (*(f32 *)((u8 *)arg0 + 0)) * temp_f0;
    sp.u3C = (*(f32 *)((u8 *)arg0 + 4)) * temp_f0;
    sp.u40 = (*(f32 *)((u8 *)arg0 + 8)) * temp_f0;
    sp.u44 = (*(f32 *)((u8 *)arg0 + 0xC)) * temp_f0;
    sp.u48 = (*(f32 *)((u8 *)arg0 + 0x10)) * temp_f0;
    sp.u4C = (*(f32 *)((u8 *)arg0 + 0x14)) * temp_f0;
    sp.u50 = (*(f32 *)((u8 *)arg0 + 0x18)) * temp_f0;
    sp.u54 = (*(f32 *)((u8 *)arg0 + 0x1C)) * temp_f0;
    sp.u58 = (*(f32 *)((u8 *)arg0 + 0x20)) * temp_f0;
    sp.u5C = (*(f32 *)((u8 *)arg0 + 0x24)) * temp_f0;
    sp.u60 = (*(f32 *)((u8 *)arg0 + 0x28)) * temp_f0;
    sp.u64 = (*(f32 *)((u8 *)arg0 + 0x2C)) * temp_f0;
    sp.u74 = (*(f32 *)((u8 *)arg0 + 0)) * temp_f2;
    sp.u78 = (*(f32 *)((u8 *)arg0 + 4)) * temp_f2;
    sp.u7C = (*(f32 *)((u8 *)arg0 + 8)) * temp_f2;
    sp.u68 = (*(f32 *)((u8 *)arg0 + 0xC)) * temp_f2;
    sp.u6C = (*(f32 *)((u8 *)arg0 + 0x10)) * temp_f2;
    sp.u70 = (*(f32 *)((u8 *)arg0 + 0x14)) * temp_f2;
    sp.u8C = (*(f32 *)((u8 *)arg0 + 0x18)) * temp_f2;
    sp.u90 = (*(f32 *)((u8 *)arg0 + 0x1C)) * temp_f2;
    sp.u94 = (*(f32 *)((u8 *)arg0 + 0x20)) * temp_f2;
    sp.u80 = (*(f32 *)((u8 *)arg0 + 0x24)) * temp_f2;
    sp.u84 = (*(f32 *)((u8 *)arg0 + 0x28)) * temp_f2;
    sp.u88 = (*(f32 *)((u8 *)arg0 + 0x2C)) * temp_f2;
    (*(f32 *)((u8 *)(&sp.u98) + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0));
    (*(f32 *)((u8 *)(&sp.u98) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 4));
    (*(f32 *)((u8 *)(&sp.u98) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 8));
    (*(f32 *)((u8 *)(&sp.uA4) + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0xC));
    (*(f32 *)((u8 *)(&sp.uA4) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 0x10));
    (*(f32 *)((u8 *)(&sp.uA4) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 0x14));
    (*(f32 *)((u8 *)(&sp.uB0) + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0x18));
    (*(f32 *)((u8 *)(&sp.uB0) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 0x1C));
    (*(f32 *)((u8 *)(&sp.uB0) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 0x20));
    (*(f32 *)((u8 *)(&sp.uBC) + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0x24));
    (*(f32 *)((u8 *)(&sp.uBC) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 0x28));
    (*(f32 *)((u8 *)(&sp.uBC) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 0x2C));
    sp.uC8 = (*(f32 *)((u8 *)arg0 + 0x30));
    sp.uCC = (*(f32 *)((u8 *)arg0 + 0x34));
    sp.uD4 = 0.0f;
    sp.uD0 = (*(f32 *)((u8 *)arg0 + 0x38));
    temp_v0 = func_15164CF0(&sp.uD8, arg3 + 0xA0, arg4, arg5);
    if (temp_v0 != NULL) {
        memcpy(temp_v0 + 0x68, &sp.u38, 0xA0);
    }
    return temp_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_192500/func_15165B98.s")
#endif
#ifdef NON_MATCHING
s32 func_15165E4C(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;
    s32 var_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    var_v1 = 1;
    temp_v0 = arg0 + 0x68;
    (*(f32 *)((u8 *)arg0 + 0x104)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x104)) + D_800BE9A4);
    if ((*(f32 *)((u8 *)arg0 + 0x104)) < (*(f32 *)((u8 *)arg0 + 0xF8))) {
        temp_v0_2 = arg0 + 0x68;
        (*(f32 *)((u8 *)arg0 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x1C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 4)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x20)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 8)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x24)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0xC)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x10)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x14)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x18)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x1C)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x20)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x24)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x28)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
        (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0x2C)) * (*(f32 *)((u8 *)temp_v0_2 + 0x9C)));
    } else {
        temp_f2 = (*(f32 *)((u8 *)temp_v0 + 0x9C));
        temp_f12 = (*(f32 *)((u8 *)temp_v0 + 0x90)) + (*(f32 *)((u8 *)temp_v0 + 0x94));
        if (temp_f2 < temp_f12) {
            (*(f32 *)((u8 *)arg0 + 0x18)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x60));
            (*(f32 *)((u8 *)arg0 + 0x1C)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x64));
            (*(f32 *)((u8 *)arg0 + 0x20)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x68));
            (*(f32 *)((u8 *)arg0 + 0x24)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x6C));
            (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x70));
            (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x74));
            (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x78));
            (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x7C));
            (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x80));
            (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x84));
            (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x88));
            (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x8C));
        } else if (temp_f2 < (temp_f12 + (*(f32 *)((u8 *)temp_v0 + 0x98)))) {
            temp_f0 = temp_f2 - temp_f12;
            (*(f32 *)((u8 *)arg0 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x60)) - ((*(f32 *)((u8 *)temp_v0 + 0x3C)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x1C)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x64)) - ((*(f32 *)((u8 *)temp_v0 + 0x40)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x20)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x68)) - ((*(f32 *)((u8 *)temp_v0 + 0x44)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x24)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x6C)) - ((*(f32 *)((u8 *)temp_v0 + 0x30)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x70)) - ((*(f32 *)((u8 *)temp_v0 + 0x34)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x74)) - ((*(f32 *)((u8 *)temp_v0 + 0x38)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x78)) - ((*(f32 *)((u8 *)temp_v0 + 0x54)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x7C)) - ((*(f32 *)((u8 *)temp_v0 + 0x58)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x80)) - ((*(f32 *)((u8 *)temp_v0 + 0x5C)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x84)) - ((*(f32 *)((u8 *)temp_v0 + 0x48)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x88)) - ((*(f32 *)((u8 *)temp_v0 + 0x4C)) * temp_f0));
            (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x8C)) - ((*(f32 *)((u8 *)temp_v0 + 0x50)) * temp_f0));
        } else {
            var_v1 = 0;
        }
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_192500/func_15165E4C.s")
#endif
f32 func_15166120(void *arg0, void *arg1, s32 arg2, s32 arg3, f32 arg4);

void func_151660F0(u8 *arg0) {
    func_15166120(arg0, arg0 + 0x108, *(s32 *)(arg0 + 0x114), *(s32 *)(arg0 + 0x118), *(f32 *)(arg0 + 0x11C));
}

#ifdef NON_MATCHING
f32 func_15143E64(void *);

f32 func_15166120(void * arg0_p, void * arg1_p, s32 arg2, s32 arg3, f32 arg4) {
    u8 * arg0 = (u8 *) arg0_p;
    u8 * arg1 = (u8 *) arg1_p;
    struct {
        f32 u20;
        f32 u24;
        f32 u28;
    } sp;
    f32 *temp_v0;
    f32 temp_f0;
    f32 var_f2;

    temp_v0 = func_15144B34((s32) (*(u8 *)((u8 *)arg0 + 0x16)));
    sp.u20 = (*(f32 *)((u8 *)arg1 + 0)) - (*(f32 *)((u8 *)temp_v0 + 0));
    sp.u24 = (*(f32 *)((u8 *)arg1 + 4)) - (*(f32 *)((u8 *)temp_v0 + 4));
    sp.u28 = (*(f32 *)((u8 *)arg1 + 8)) - (*(f32 *)((u8 *)temp_v0 + 8));
    temp_f0 = func_15143E64(&sp.u20);
    if (temp_f0 < (*(f32 *)&(arg2))) {
        var_f2 = 1.0f;
    } else if (((*(f32 *)&(arg2)) + (*(f32 *)&(arg3))) < temp_f0) {
        var_f2 = 0.0f;
    } else {
        var_f2 = 1.0f - ((temp_f0 - (*(f32 *)&(arg2))) * arg4);
    }
    return var_f2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_192500/func_15166120.s")
#endif