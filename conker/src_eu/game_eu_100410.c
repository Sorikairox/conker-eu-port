#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_150D2C9C(s32, u8 *, u8, u8);
void func_150D2C00(u8 *arg0)
{
  u8 **q = &arg0; // fakematch: arg0 reloaded from its home (shape C)
  if ((*q)[0x78] & 1)
  {
    s32 *v = (s32 *) ((*q) + 0x28);
    v[3] -= D_800BE9E4;
    if (v[3] < 0)
    {
      func_150D2C9C(v[0], (u8 *) (&v[4]), (*q)[0xC], (*q)[1]);
      v[3] = v[1] + (func_150ADA20() % ((u32) (v[2] + 1)));
    }
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_100410/func_150D2C9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_100410/func_150D2E34.s")

#ifdef NON_MATCHING
s32 memcpy(s32, s32, s32);

u8 *func_150D327C(u8 *arg0, s16 arg1) {
    struct {
        u8 u47;
        u8 pad48[0x8];
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        u8 pad68[0x4];
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        u8 pad8C[0x4];
        u8 * u90;
        u8 * u94;
    } sp;
    u8 *sp3C;
    s32 sp38;
    f32 sp28;
    f32 *temp_v0;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f8;
    s32 temp_a1;
    u8 *temp_t1;
    u8 *temp_t5;
    u8 *temp_t7;
    u8 *temp_v1;
    u8 *temp_v1_2;

    func_151D6310(arg0 + 0x100, arg1, 0x40, &sp.u94, &sp.u47);
    sp.u90 = sp.u94;
    if (sp.u94 != NULL) {
        if (sp.u47 != 0) {
            temp_v1 = arg0 + (arg1 * 4);
            temp_a1 = arg0 + 0xC0;
            sp38 = temp_a1;
            sp3C = temp_v1;
            memcpy((*(s32 *)((u8 *)temp_v1 + 0x100)), temp_a1, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v1 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_v0 = func_15144B34((s32) arg1);
        sp.u80 = (*(f32 *)((u8 *)arg0 + 0x40)) - (*(f32 *)((u8 *)arg0 + 0x34));
        sp.u84 = (*(f32 *)((u8 *)arg0 + 0x44)) - (*(f32 *)((u8 *)arg0 + 0x38));
        temp_f8 = (*(f32 *)((u8 *)arg0 + 0x48)) - (*(f32 *)((u8 *)arg0 + 0x3C));
        sp.u88 = temp_f8;
        temp_f2 = (*(f32 *)((u8 *)arg0 + 0x38));
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x34));
        sp.u78 = temp_f2 + sp.u84;
        temp_f12 = (*(f32 *)((u8 *)arg0 + 0x3C));
        sp.u7C = temp_f12 + temp_f8;
        temp_f14 = temp_f0 + (sp.u80 * 0.5f);
        sp.u6C = temp_f2 + (sp.u84 * 0.5f);
        sp.u70 = temp_f12 + (temp_f8 * 0.5f);
        sp.u5C = temp_f14 - (*(f32 *)((u8 *)temp_v0 + 0));
        sp.u60 = sp.u6C - (*(f32 *)((u8 *)temp_v0 + 4));
        sp.u74 = temp_f0 + sp.u80;
        sp.u64 = sp.u70 - (*(f32 *)((u8 *)temp_v0 + 8));
        func_150ADD90(temp_f12, temp_f14, &sp.u80, &sp.u5C, &sp.u50);
        sp28 = sp.u50;
        temp_f0_2 = (sp.u50 * sp.u50) + (sp.u54 * sp.u54) + (sp.u58 * sp.u58);
        if (temp_f0_2 != 0.0f) {
            temp_f2_2 = (*(f32 *)((u8 *)arg0 + 0x2C)) / sqrtf(temp_f0_2);
            sp.u50 = sp28 * temp_f2_2;
            sp.u54 *= temp_f2_2;
            sp.u58 *= temp_f2_2;
        } else {
            sp.u50 = 0.0f;
            sp.u54 = 0.0f;
            sp.u58 = 0.0f;
        }
        temp_v1_2 = arg0 + 0x110;
        (*(s16 *)((u8 *)sp.u94 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - sp.u50);
        (*(s16 *)((u8 *)sp.u94 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) - sp.u54);
        (*(s16 *)((u8 *)sp.u94 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - sp.u58);
        (*(s16 *)((u8 *)sp.u94 + 8)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1_2 + 4));
        (*(s16 *)((u8 *)sp.u94 + 6)) = 0;
        temp_t5 = sp.u94 + 0x10;
        sp.u94 = temp_t5;
        (*(s16 *)((u8 *)temp_t5 + 0)) = (s16) (s32) (sp.u74 - sp.u50);
        (*(s16 *)((u8 *)sp.u94 + 2)) = (s16) (s32) (sp.u78 - sp.u54);
        (*(s16 *)((u8 *)sp.u94 + 4)) = (s16) (s32) (sp.u7C - sp.u58);
        (*(s16 *)((u8 *)sp.u94 + 8)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1_2 + 0));
        (*(s16 *)((u8 *)temp_t5 + 6)) = 0;
        temp_t7 = sp.u94 + 0x10;
        sp.u94 = temp_t7;
        (*(s16 *)((u8 *)temp_t7 + 0)) = (s16) (s32) (sp.u74 + sp.u50);
        (*(s16 *)((u8 *)sp.u94 + 2)) = (s16) (s32) (sp.u78 + sp.u54);
        (*(s16 *)((u8 *)sp.u94 + 4)) = (s16) (s32) (sp.u7C + sp.u58);
        (*(s16 *)((u8 *)sp.u94 + 8)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1_2 + 0));
        (*(s16 *)((u8 *)temp_t7 + 6)) = 0;
        temp_t1 = sp.u94 + 0x10;
        sp.u94 = temp_t1;
        (*(s16 *)((u8 *)temp_t1 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + sp.u50);
        (*(s16 *)((u8 *)sp.u94 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + sp.u54);
        (*(s16 *)((u8 *)sp.u94 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + sp.u58);
        (*(s16 *)((u8 *)sp.u94 + 8)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1_2 + 4));
        (*(s16 *)((u8 *)temp_t1 + 6)) = 0;
        return sp.u90;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_100410/func_150D327C.s")
#endif
s32 func_150D368C(u8 *arg0) {
    u8 *temp_s0;

    *(f32 *)(arg0 + 0x128) = (*(f32 *)(arg0 + 0x130) * D_800BE9A4) + *(f32 *)(arg0 + 0x128);
    *(f32 *)(arg0 + 0x12C) = (*(f32 *)(arg0 + 0x134) * D_800BE9A4) + *(f32 *)(arg0 + 0x12C);
    temp_s0 = arg0 + 0x110;
    (*(f32 *)((u8 *)temp_s0 + 0x18)) = func_15144B68((*(f32 *)((u8 *)arg0 + 0x128)));
    (*(f32 *)((u8 *)temp_s0 + 0x1C)) = func_15144B68((*(f32 *)((u8 *)temp_s0 + 0x1C)));
    *(f32 *)(temp_s0 + 0) = *(f32 *)(temp_s0 + 8) + (*(f32 *)(temp_s0 + 0x10) * sinf(*(f32 *)(temp_s0 + 0x18)));
    *(f32 *)(temp_s0 + 4) = *(f32 *)(temp_s0 + 0xC) + (*(f32 *)(temp_s0 + 0x14) * sinf(*(f32 *)(temp_s0 + 0x1C)));
    (*(f32 *)((u8 *)temp_s0 + 0x28)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x28)) - D_800BE9A4);
    (*(s8 *)((u8 *)arg0 + 0x5C)) = (s8) (u32) ((*(f32 *)((u8 *)temp_s0 + 0x28)) * (*(f32 *)((u8 *)temp_s0 + 0x2C)));
    if ((*(f32 *)((u8 *)temp_s0 + 0x28)) > 0.0f) {
        return 1;
    }
    return 0;
}

void func_150D380C(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *p;
    if (arg2 == 0x34) {
        p = (*(u8 **)&arg0) + 0x28;
        if (arg1[0] == p[0x51]) {
            func_150D2C9C(*(s32 *)p, p + 0x10, arg0[0xC], arg0[1]);
        }
    }
}
