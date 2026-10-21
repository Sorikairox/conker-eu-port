#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 func_15132BBC(f32 *, s32, s32, s32, s32, s32, s32);
s32 func_15145128(f32 *, f32 *, f32 *, s32 *);
s32 memcpy(s32, f32 *, s32);

void func_150F4AF0(u8 *arg0, u8 *arg1, u8 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9) {
    struct {
        f32 u3C;
        s32 u40;
        u8 pad44[0x8];
        f32 u4C;
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        s8 u60;
        u8 pad61[0x3];
        s32 u64;
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
        f32 u98;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        s32 uAC;
        u8 padB0[0x8];
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        f32 uD0;
        s32 uD4;
        s16 uD8;
        s16 uDA;
        s8 uDC;
        u8 padDD[0x3];
        s32 uE0;
        s8 uE4;
        s8 uE5;
        s8 uE6;
        s8 uE7;
        s8 uE8;
        s8 uE9;
        s8 uEA;
        s8 uEB;
        s8 uEC;
        s8 uED;
        s8 uEE;
        u8 padEF[0x1];
        s32 uF0;
        s8 uF4;
        u8 padF5[0x1];
        s16 uF6;
        s16 uF8;
        u8 padFA[0x2];
        s32 uFC;
    } sp;
    f32 sp34;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f8;
    s32 temp_v0;
    s32 var_v0;
    s32 var_v1;

    sp.u6C = (*(f32 *)((u8 *)arg1 + 0)) - (*(f32 *)((u8 *)arg0 + 0));
    sp.u70 = (*(f32 *)((u8 *)arg1 + 4)) - (*(f32 *)((u8 *)arg0 + 4));
    sp.u74 = (*(f32 *)((u8 *)arg1 + 8)) - (*(f32 *)((u8 *)arg0 + 8));
    if (func_15145128(&sp.u6C, &sp.u78, &sp.u68, &sp.u64) != 0) {
        if (arg6 != 0) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        if (arg7 != 0) {
            var_v0 = 2;
        } else {
            var_v0 = 0;
        }
        sp.u60 = var_v0 | var_v1;
        sp.u3C = sp.u68 * arg4;
        (*(f32 *)((u8 *)(&sp.u40) + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0));
        (*(f32 *)((u8 *)(&sp.u40) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 4));
        (*(f32 *)((u8 *)(&sp.u40) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 8));
        sp.u4C = func_150ADA68() * 6.2831855f;
        sp.u50 = (func_150ADA68() * 0.2f) + 0.080000006f;
        if (func_150ADA20() & 1) {
            sp.u50 = -sp.u50;
        }
        sp.u5C = (func_150ADA68() * 21.0f) + 13.0f;
        temp_f12 = func_150ADA68() * 6.2831855f;
        sp34 = temp_f12;
        sp.u54 = cosf(temp_f12);
        sp.u58 = sinf(temp_f12);
        sp.u84 = 1.0f;
        sp.u88 = 1.0f;
        sp.u90 = arg5;
        sp.u8C = arg5;
        sp.u94 = func_150ADA68() * 360.0f;
        sp.u98 = func_150ADA68() * 360.0f;
        temp_f0 = func_150ADA68();
        sp.uA0 = 1.0f;
        sp.uA4 = 1.0f;
        sp.uA8 = 1.0f;
        sp.u9C = temp_f0 * 360.0f;
        (*(f32 *)((u8 *)(&sp.uAC) + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0));
        (*(f32 *)((u8 *)(&sp.uAC) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 4));
        (*(f32 *)((u8 *)(&sp.uAC) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 8));
        sp.uB8 = sp.u78 * arg3;
        sp.uBC = sp.u7C * arg3;
        sp.uC0 = sp.u80 * arg3;
        temp_f8 = func_150ADA68() * 21.903002f;
        sp.uC8 = 0.0f;
        sp.uC4 = temp_f8 + -10.951501f;
        temp_f10 = (func_150ADA68() * 21.903002f) + -10.951501f;
        sp.uE4 = 0xFF;
        sp.uE5 = 0x16;
        sp.uDA = (s16) arg2;
        sp.uD4 = 0x14900;
        sp.uD8 = 0x12C;
        sp.uDC = 8;
        sp.uCC = temp_f10;
        sp.uE0 = 0;
        sp.uE6 = 7;
        sp.uE7 = 0;
        sp.uE8 = 0;
        sp.uE9 = 0;
        sp.uEA = 0;
        sp.uEB = 0;
        sp.uEC = 2;
        sp.uED = -1;
        sp.uEE = 2;
        sp.uF0 = 0;
        sp.uF4 = 0;
        sp.uF6 = 1;
        sp.uF8 = 0xFF;
        sp.uD0 = 0.0f;
        sp.uFC = arg7;
        temp_v0 = func_15132BBC(&sp.u84, 3, 0xFF, 0, 0x28, (s32) arg8, arg9);
        if (temp_v0 != 0) {
            memcpy(temp_v0 + 0x170, &sp.u3C, 0x28);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_122300/func_150F4AF0.s")
#endif
#ifdef NON_MATCHING
void func_1514373C(f32, f32, f32 *, f32 *);

u8 *func_150F4E50(u8 *arg0) {
    struct {
        f32 u1C;
        f32 u20;
    } sp;
    u8 *sp18;
    u8 *temp_v0;

    temp_v0 = arg0 + 0x170;
    (*(f32 *)((u8 *)arg0 + 0x170)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x170)) - D_800BE9A4);
    if ((*(f32 *)((u8 *)arg0 + 0x170)) <= 0.0f) {
        return NULL;
    }
    sp18 = temp_v0;
    func_1514373C((*(f32 *)((u8 *)temp_v0 + 0x10)), (*(f32 *)((u8 *)temp_v0 + 0x20)), &sp.u1C, &sp.u20);
    (*(f32 *)((u8 *)sp18 + 0x10)) = (f32) ((*(f32 *)((u8 *)sp18 + 0x10)) + ((*(f32 *)((u8 *)sp18 + 0x14)) * D_800BE9A4));
    (*(f32 *)((u8 *)sp18 + 4)) = (f32) ((*(f32 *)((u8 *)sp18 + 4)) + ((*(f32 *)((u8 *)arg0 + 0x44)) * D_800BE9A4));
    (*(f32 *)((u8 *)sp18 + 8)) = (f32) ((*(f32 *)((u8 *)sp18 + 8)) + ((*(f32 *)((u8 *)arg0 + 0x48)) * D_800BE9A4));
    (*(f32 *)((u8 *)sp18 + 0xC)) = (f32) ((*(f32 *)((u8 *)sp18 + 0xC)) + ((*(f32 *)((u8 *)arg0 + 0x4C)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)sp18 + 4)) + (sp.u1C * (*(f32 *)((u8 *)sp18 + 0x18))));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)sp18 + 8)) + sp.u20);
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) ((*(f32 *)((u8 *)sp18 + 0xC)) - (sp.u1C * (*(f32 *)((u8 *)sp18 + 0x1C))));
    (*(f32 *)((u8 *)arg0 + 0x20)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x20)) + ((*(f32 *)((u8 *)arg0 + 0x50)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x24)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x24)) + ((*(f32 *)((u8 *)arg0 + 0x54)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x28)) + ((*(f32 *)((u8 *)arg0 + 0x58)) * D_800BE9A4));
    return sp18;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_122300/func_150F4E50.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_122300/func_150F4FB8.s")

void func_150F527C(u8 *arg0, s32 arg1, u8 arg2) {
    u8 *v = arg0 + 0x170;

    if (arg2 == 0x4E) {
        arg0[0x71] = 0;
        v[0x24] |= 5;
    } else if (arg2 == 0x4F) {
        func_1516972C(arg0);
    }
}

void func_150F4D5C(u8 *arg0, s8 arg1, u8 arg2, u8 arg3, s32 arg4) {
    struct {
        u8 *unk0;
        f32 unk4;
        s8 unk8;
        u8 unk9;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = 0.0f;
    tmp.unk8 = arg1;
    tmp.unk9 = arg2;
    temp_v0 = func_15149130(300, -1, 0x56, -1, 0, 0, 0xC, arg3, arg4);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_122300/func_150F536C.s")
