#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_1516ACE0(u8 *arg0) {
    s32 n = 1;

    while (*arg0 != 0) {
        if (*arg0 == 0xBD) {
            *arg0 = 0;
            n++;
        }
        arg0++;
    }
    return n;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1984F0/func_1516AD20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1984F0/func_1516AFE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1984F0/func_1516BC2C.s")

typedef struct { u8 *str; s32 pad; } StrEnt_1516CDE8;
extern StrEnt_1516CDE8 *D_800DD684;
extern StrEnt_1516CDE8 *D_800DD688;
u8 *func_1516CDE8(s32 *arg0, s32 arg1, s16 arg2) {
    s32 i;
    u8 *p;

    switch (arg2) {
    case 0:
        p = D_800DD684[arg0[1]].str;
        break;
    case 1:
        p = D_800DD688[arg0[1]].str;
        break;
    case 2:
        p = (u8 *)arg0[1];
        break;
    }
    for (i = 0; i < arg1; i++) {
        while (*p != 0) {
            p++;
        }
        while (*p == 0) {
            p++;
        }
    }
    return p;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1984F0/func_1516CEA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1984F0/func_1516D1C8.s")

#ifdef NON_MATCHING
extern u16 D_80090912;
extern u16 D_80090932;

void func_1516D63C(u8 *arg0, f32 *arg1, f32 *arg2, s32 arg3) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f8;
    f32 var_f4;
    f32 var_f8;

    var_f8 = (f32) D_80090912;
    if ((s32) D_80090912 < 0) {
        var_f8 += 4294967296.0f;
    }
    var_f4 = (f32) D_80090932;
    if ((s32) D_80090932 < 0) {
        var_f4 += 4294967296.0f;
    }
    sp1C = ((*(f32 *)((u8 *)arg0 + 0x38)) / var_f8) * var_f4 * 0.25f * (*(f32 *)((u8 *)arg0 + 0x28));
    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x38)) * 0.5f;
    temp_f18 = (*(f32 *)((u8 *)arg0 + 0x3C));
    temp_f14 = *arg2;
    temp_f8 = cosf((*(f32 *)((u8 *)arg0 + 0x58)) + 3.1415927f) * temp_f2;
    sp28 = temp_f14;
    sp2C = temp_f14 - temp_f18;
    temp_f12 = ((temp_f8 * 1.15f * (*(f32 *)((u8 *)arg0 + 0x28))) + *arg1) - sp1C;
    sp24 = temp_f12 - temp_f2;
    sp20 = temp_f2 + temp_f12;
    if (arg0 != NULL) {
        temp_f0 = (*(f32 *)((u8 *)D_800BE628 + 0x24));
        if (sp2C < temp_f0) {
            *arg2 = temp_f0 + temp_f18;
        } else {
            temp_f0_2 = (*(f32 *)((u8 *)D_800BE628 + 0x28));
            if (temp_f0_2 < sp28) {
                *arg2 = temp_f0_2;
            }
        }
        temp_f0_3 = (*(f32 *)((u8 *)D_800BE628 + 0x2C));
        if (sp24 < temp_f0_3) {
            *arg1 -= sp24 - temp_f0_3;
        } else {
            temp_f0_4 = (*(f32 *)((u8 *)D_800BE628 + 0x30));
            if (temp_f0_4 < sp20) {
                *arg1 += temp_f0_4 - sp20;
            }
        }
        *arg1 = (f32) (s32) *arg1;
        *arg2 = (f32) (s32) *arg2;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1984F0/func_1516D63C.s")
#endif
void func_1516D850(u8 *arg0) {
    if ((arg0 != NULL) && (arg0[0] == 0x51)) {
        (*(u8 **)(arg0 + 0x10))[8] = 0;
        func_1516972C((struct102 *)arg0);
        arg0[0x15] = 0;
    }
}

void func_1516D898(u8 *arg0) {
    if ((arg0 != NULL) && (arg0[0] == 0x51)) {
        **(s32 **)(arg0 + 0x10) |= 0x100;
        **(s32 **)(arg0 + 0x10) &= ~0x400;
        arg0[0x20] = (*(u8 **)(arg0 + 0x10))[8];
    }
}

u8 *func_1516D8E8(u8 *arg0) {
    if ((arg0 != NULL) && (arg0[0] == 0x51)) {
        **(s32 **)(arg0 + 0x10) |= 0x100;
        **(s32 **)(arg0 + 0x10) &= ~0x400;
        return arg0;
    }
    return NULL;
}

u8 *func_1516D934(u8 *arg0) {
    if ((arg0 != NULL) && (arg0[0] == 0x51)) {
        **(s32 **)(arg0 + 0x10) |= 0x500;
        return arg0;
    }
    return NULL;
}
