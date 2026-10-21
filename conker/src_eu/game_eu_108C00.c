#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_108C00/func_150DB3F0.s")

#ifdef NON_MATCHING
extern f32 D_800A0FB4;
extern f32 D_800A0FB8;
s32 func_150DB694(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f2;
    s16 temp_v1;
    u8 *var_v0;

    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x134));
    var_v0 = arg0 + 0x110;
    (*(f32 *)((u8 *)arg0 + 0x110)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x110)) * temp_f0);
    (*(f32 *)((u8 *)arg0 + 0x114)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x114)) * temp_f0);
    (*(f32 *)((u8 *)arg0 + 0x118)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x118)) * temp_f0);
    (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x34)) + ((*(f32 *)((u8 *)arg0 + 0x110)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((*(f32 *)((u8 *)arg0 + 0x114)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + ((*(f32 *)((u8 *)arg0 + 0x118)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x124)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x124)) + ((*(f32 *)((u8 *)arg0 + 0x12C)) * D_800BE9A4));
    if ((*(f32 *)((u8 *)arg0 + 0x124)) > D_800A0FB4) {
        var_v0 = arg0 + 0x110;
        (*(f32 *)((u8 *)var_v0 + 0x14)) = D_800A0FB4;
        (*(f32 *)((u8 *)var_v0 + 0x1C)) = (f32) -(*(f32 *)((u8 *)var_v0 + 0x1C));
    } else if ((*(f32 *)((u8 *)var_v0 + 0x14)) < D_800A0FB8) {
        (*(f32 *)((u8 *)var_v0 + 0x14)) = D_800A0FB8;
        (*(f32 *)((u8 *)var_v0 + 0x1C)) = (f32) -(*(f32 *)((u8 *)var_v0 + 0x1C));
    }
    temp_f0_2 = (*(f32 *)((u8 *)var_v0 + 0x20));
    (*(f32 *)((u8 *)var_v0 + 0x18)) = (f32) ((*(f32 *)((u8 *)var_v0 + 0x18)) + (temp_f0_2 * D_800BE9A4));
    temp_f2 = (*(f32 *)((u8 *)var_v0 + 0x18));
    if (temp_f2 > D_800A0FB4) {
        (*(f32 *)((u8 *)var_v0 + 0x18)) = D_800A0FB4;
        (*(f32 *)((u8 *)var_v0 + 0x20)) = (f32) -temp_f0_2;
    } else if (temp_f2 < D_800A0FB8) {
        (*(f32 *)((u8 *)var_v0 + 0x18)) = D_800A0FB8;
        (*(f32 *)((u8 *)var_v0 + 0x20)) = (f32) -temp_f0_2;
    }
    (*(f32 *)((u8 *)var_v0 + 0xC)) = (f32) ((*(f32 *)((u8 *)var_v0 + 0xC)) + ((*(f32 *)((u8 *)var_v0 + 0x10)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) ((*(f32 *)((u8 *)var_v0 + 0xC)) * (*(f32 *)((u8 *)var_v0 + 0x14)));
    (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) ((*(f32 *)((u8 *)var_v0 + 0xC)) * (*(f32 *)((u8 *)var_v0 + 0x18)));
    temp_v1 = (*(u8 *)((u8 *)arg0 + 0x5C)) - (*(u8 *)((u8 *)var_v0 + 0x28));
    if (temp_v1 < 0) {
    s32 pad;
        (*(u8 *)((u8 *)arg0 + 0x5C)) = 0U;
        return 0;
    }
    (*(u8 *)((u8 *)arg0 + 0x5C)) = (u8) temp_v1;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_108C00/func_150DB694.s")
#endif
#ifdef NON_MATCHING
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
s32 memcpy(s32, s32, s32);

u8 *func_150DB858(u8 *arg0, s16 arg1) {
    struct {
        u8 u37;
        u8 pad38[0x8];
        u8 * u40;
        u8 * u44;
    } sp;
    u8 *sp30;
    s32 sp2C;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;
    s32 temp_a1;
    u8 *temp_v0;

    func_151D6310(arg0 + 0x100, arg1, 0x40, &sp.u44, &sp.u37);
    sp.u40 = sp.u44;
    if (sp.u44 != NULL) {
        if (sp.u37 != 0) {
            temp_v0 = arg0 + (arg1 * 4);
            temp_a1 = arg0 + 0xC0;
            sp2C = temp_a1;
            sp30 = temp_v0;
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)), temp_a1, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x2C));
        temp_f2 = temp_f0 * (*(f32 *)((u8 *)arg0 + 0x40));
        temp_f12 = -temp_f0 * (*(f32 *)((u8 *)arg0 + 0x48));
        (*(s16 *)((u8 *)sp.u44 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f2);
        (*(s16 *)((u8 *)sp.u44 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + (*(f32 *)((u8 *)arg0 + 0x30)));
        (*(s16 *)((u8 *)sp.u44 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f12);
        (*(s16 *)((u8 *)sp.u44 + 6)) = 0;
        (*(s16 *)((u8 *)sp.u44 + 0x10)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f2);
        (*(s16 *)((u8 *)sp.u44 + 0x12)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) - (*(f32 *)((u8 *)arg0 + 0x30)));
        (*(s16 *)((u8 *)sp.u44 + 0x14)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f12);
        (*(s16 *)((u8 *)sp.u44 + 0x16)) = 0;
        (*(s16 *)((u8 *)sp.u44 + 0x20)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f2);
        (*(s16 *)((u8 *)sp.u44 + 0x22)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) - (*(f32 *)((u8 *)arg0 + 0x30)));
        (*(s16 *)((u8 *)sp.u44 + 0x24)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f12);
        (*(s16 *)((u8 *)sp.u44 + 0x26)) = 0;
        (*(s16 *)((u8 *)sp.u44 + 0x30)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f2);
        (*(s16 *)((u8 *)sp.u44 + 0x32)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + (*(f32 *)((u8 *)arg0 + 0x30)));
        (*(s16 *)((u8 *)sp.u44 + 0x34)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f12);
        (*(s16 *)((u8 *)sp.u44 + 0x36)) = 0;
        return sp.u40;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_108C00/func_150DB858.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_108C00/func_150DBA98.s")

s32 func_150DBBB0(u8 *arg0) {
    f32 **pp = (f32 **)(arg0 + 0x120); // fakematch: pointer to the field keeps the reload of 0x120 in the else-if (permuter)
    if (**pp > 255.0f) {
        arg0[0x5C] = 0xFF;
    } else if (**pp < 0.0f) {
        arg0[0x5C] = 0;
    } else {
        arg0[0x5C] = **pp;
    }
    return 1;
}

#ifdef NON_MATCHING
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
s32 memcpy(s32, s32, s32);

u8 *func_150DBC94(u8 *arg0, s16 arg1) {
    struct {
        u8 u37;
        u8 pad38[0xC];
        f32 u44;
        s32 u48;
        u8 pad4C[0x4];
        u8 * u50;
        u8 * u54;
    } sp;
    u8 *sp30;
    s32 sp2C;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    s32 temp_a1;
    s32 temp_f10;
    u8 *temp_v0;
    u8 *temp_v1;

    func_151D6310(arg0 + 0x100, arg1, 0x40, &sp.u54, &sp.u37);
    sp.u50 = sp.u54;
    if (sp.u54 != NULL) {
        if (sp.u37 != 0) {
            temp_v0 = arg0 + (arg1 * 4);
            temp_a1 = arg0 + 0xC0;
            sp2C = temp_a1;
            sp30 = temp_v0;
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)), temp_a1, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_f10 = (s32) (*(*(f32 **)((u8 *)arg0 + 0x114)) * 0.7111111f);
        sp.u48 = temp_f10;
        sp.u44 = func_151423D8(temp_f10 & 0xFF);
        temp_v1 = arg0 + 0x110;
        temp_f2 = *(*(f32 **)((u8 *)temp_v1 + 8));
        temp_f12 = temp_f2 * sp.u44;
        temp_f14 = -temp_f2 * func_151423D8((temp_f10 - 0x40) & 0xFF);
        (*(s16 *)((u8 *)sp.u54 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)((*(u8 **)((u8 *)temp_v1 + 0))) + 0)) + temp_f12);
        (*(s16 *)((u8 *)sp.u54 + 2)) = (s16) (s32) (*(*(f32 **)((u8 *)temp_v1 + 0xC)) + (*(f32 *)((u8 *)((*(u8 **)((u8 *)temp_v1 + 0))) + 4)));
        (*(s16 *)((u8 *)sp.u54 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)((*(u8 **)((u8 *)temp_v1 + 0))) + 8)) + temp_f14);
        (*(s16 *)((u8 *)sp.u54 + 6)) = 0;
        (*(s16 *)((u8 *)sp.u54 + 0x10)) = (s16) (s32) ((*(f32 *)((u8 *)((*(u8 **)((u8 *)temp_v1 + 0))) + 0)) + temp_f12);
        (*(s16 *)((u8 *)sp.u54 + 0x12)) = (s16) (s32) ((*(f32 *)((u8 *)((*(u8 **)((u8 *)temp_v1 + 0))) + 4)) - *(*(f32 **)((u8 *)temp_v1 + 0xC)));
        (*(s16 *)((u8 *)sp.u54 + 0x14)) = (s16) (s32) ((*(f32 *)((u8 *)((*(u8 **)((u8 *)temp_v1 + 0))) + 8)) + temp_f14);
        (*(s16 *)((u8 *)sp.u54 + 0x16)) = 0;
        (*(s16 *)((u8 *)sp.u54 + 0x20)) = (s16) (s32) ((*(f32 *)((u8 *)((*(u8 **)((u8 *)temp_v1 + 0))) + 0)) - temp_f12);
        (*(s16 *)((u8 *)sp.u54 + 0x22)) = (s16) (s32) ((*(f32 *)((u8 *)((*(u8 **)((u8 *)temp_v1 + 0))) + 4)) - *(*(f32 **)((u8 *)temp_v1 + 0xC)));
        (*(s16 *)((u8 *)sp.u54 + 0x24)) = (s16) (s32) ((*(f32 *)((u8 *)((*(u8 **)((u8 *)temp_v1 + 0))) + 8)) - temp_f14);
        (*(s16 *)((u8 *)sp.u54 + 0x26)) = 0;
        (*(s16 *)((u8 *)sp.u54 + 0x30)) = (s16) (s32) ((*(f32 *)((u8 *)((*(u8 **)((u8 *)temp_v1 + 0))) + 0)) - temp_f12);
        (*(s16 *)((u8 *)sp.u54 + 0x32)) = (s16) (s32) (*(*(f32 **)((u8 *)temp_v1 + 0xC)) + (*(f32 *)((u8 *)((*(u8 **)((u8 *)temp_v1 + 0))) + 4)));
        (*(s16 *)((u8 *)sp.u54 + 0x34)) = (s16) (s32) ((*(f32 *)((u8 *)((*(u8 **)((u8 *)temp_v1 + 0))) + 8)) - temp_f14);
        (*(s16 *)((u8 *)sp.u54 + 0x36)) = 0;
        return sp.u50;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_108C00/func_150DBC94.s")
#endif