#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 memcpy(s32, s32, s32);
#endif


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

#ifdef NON_MATCHING
void func_1514373C(f32, f32, f32 *, f32 *);

void func_150D2E34(u8 *arg0) {
    struct {
        f32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        u8 padD8[0x4];
        s8 uDC;
        s8 uDD;
        s16 uDE;
        s16 uE0;
        u8 padE2[0x2];
        s32 uE4;
        s32 uE8;
        u8 uEC;
        u8 uED;
        u8 uEE;
        s8 uEF;
        f32 uF0;
        f32 uF4;
        f32 uF8;
        f32 uFC;
        f32 u100;
        f32 u104;
        f32 u108;
        f32 u10C;
        f32 u110;
        f32 u114;
        f32 u118;
        s32 u11C;
        s8 u120;
        s8 u121;
        s8 u122;
        s8 u123;
        s32 u124;
        s8 u128;
    } sp;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f4;
    u8 *temp_s0;
    u8 *temp_s2;
    u8 *temp_v0;

    temp_s0 = arg0 + 0x28;
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + ((*(f32 *)((u8 *)arg0 + 0x30)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x40)) + D_800BE9A4);
    if ((*(f32 *)((u8 *)arg0 + 0x3C)) > 1.0f) {
        temp_s2 = (*(u8 **)((u8 *)temp_s0 + 0));
        sp.uC0 = 0.0f;
        sp.uC4 = 0.0f;
        sp.uDC = 0x59;
        sp.uDD = 0;
        sp.uDE = 0x5A03;
        sp.uE0 = 0x16;
        sp.uE4 = 0;
        sp.uE8 = 0;
        sp.uD4 = 9.0f;
        sp.uEC = (*(u8 *)((u8 *)temp_s0 + 0x5C));
        sp.uED = (*(u8 *)((u8 *)temp_s0 + 0x5D));
        sp.uEF = 0xFF;
        sp.uF4 = 1.0f;
        sp.uEE = (*(u8 *)((u8 *)temp_s0 + 0x5E));
        sp.uF8 = (f32) (*(s16 *)((u8 *)temp_s2 + 0));
        sp.uFC = (f32) (*(s16 *)((u8 *)temp_s2 + 2));
        sp.u110 = 1.0f;
        sp.u114 = 1.0f;
        sp.u118 = 1.0f;
        sp.u11C = 0x026C0000;
        sp.u121 = 0xFF;
        sp.u122 = 0;
        sp.u123 = 6;
        sp.u124 = 0;
        sp.u128 = 0xFF;
        sp.u100 = (f32) (*(s16 *)((u8 *)temp_s2 + 4));
        do {
            temp_f4 = 22.0f - (*(f32 *)((u8 *)temp_s0 + 0x18));
            sp.uD0 = temp_f4;
            if (temp_f4 > 0.0f) {
                func_1514373C((*(f32 *)((u8 *)temp_s0 + 4)), (f32) (*(s16 *)((u8 *)temp_s2 + 6)), &sp.u9C, &sp.uA4);
                sp.uA0 = (f32) (*(s16 *)((u8 *)temp_s2 + 8));
                func_150A7E40(temp_s0 + 0x1C, sp.u9C, sp.uA0, sp.uA4, &sp.u104, &sp.u108, &sp.u10C);
                sp.uF0 = (func_150ADA68() * 25.0f) + 50.0f;
                temp_f2 = (func_150ADA68() * 1024.0f) + -2560.0f + 2048.0f;
                sp.uA8 = temp_f2;
                sp.uB0 = temp_f2;
                temp_f2_2 = (func_150ADA68() * 1024.0f) + 1536.0f + 2048.0f;
                sp.uAC = temp_f2_2;
                sp.uB4 = temp_f2_2;
                sp.uB8 = (func_150ADA68() * 768.0f) + 768.0f;
                sp.uBC = (func_150ADA68() * 768.0f) + 768.0f;
                sp.uC8 = ((func_150ADA68() * 80.0f) + 50.0f) * 0.001f;
                sp.uCC = ((func_150ADA68() * 80.0f) + 50.0f) * 0.001f;
                sp.u120 = (s8) (u32) (sp.uD4 * sp.uD0);
                temp_v0 = func_1513D2F0(&sp.uDC, (s32) ((u8 *)&D_800A4AA0), 0U, 0x26U, 0U, 0x1FU, 0U, 0, 0, 0x30, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                if (temp_v0 != NULL) {
                    memcpy(temp_v0 + 0x110, &sp.uA8, 0x30);
                }
            }
            (*(f32 *)((u8 *)temp_s0 + 4)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 4)) + (*(f32 *)((u8 *)temp_s0 + 0x10)));
            (*(f32 *)((u8 *)temp_s0 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x18)) - (*(f32 *)((u8 *)temp_s0 + 0xC)));
            (*(f32 *)((u8 *)temp_s0 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x14)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s0 + 0x14)) > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_100410/func_150D2E34.s")
#endif
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
