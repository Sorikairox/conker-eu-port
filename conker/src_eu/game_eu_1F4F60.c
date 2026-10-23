#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 func_150ACEA0(f32, f32, f32, f32, f32, f32, s32, void *, f32 *, f32 *, f32 *, f32 *, s32 *, s32, f32);
void func_151C7B1C(f32 *, void *, f32 *, void *, void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32, s32);

// record_beam_start: D_80082EA0 entry 8 (level-start record). Unless rec +0x14 is 1: the segment from the record's
// point (s16 x, y, z) along the length +8 rotated by the angles +0xC / +0x10; two ray casts (func_150ACEA0) from its
// middle towards both ends give the end points (geometry hits); when both hit, func_151C7B1C builds the beam between
// them with the colour +0x1C (r, g, b bytes) and the option bits / bytes of +0x18 and +0x20. Always returns 1.
s32 func_151C7750(u8 *rec) {
    f32 m[4][4];
    f32 p0[3];
    f32 p1[3];
    f32 d[3];
    f32 mid[3];
    u8 triA[0x14];
    f32 hitA[3];
    u8 triB[0x14];
    f32 hitB[3];
    f32 distA;
    f32 distB;
    s32 auxA;
    s32 auxB;
    s32 okA;
    s32 okB;
    u32 opt;
    u32 col;
    u32 sc;

    if (rec[0x14] == 1) {
        return 1;
    }
    p0[0] = *(s16 *) (rec + 0);
    p0[1] = *(s16 *) (rec + 2);
    p0[2] = *(s16 *) (rec + 4);
    func_150A8050(m, *(f32 *) (rec + 0xC), *(f32 *) (rec + 0x10), 0.0f);
    func_150A7E40(m, 0.0f, *(s16 *) (rec + 8), 0.0f, &p1[0], &p1[1], &p1[2]);
    p1[0] += p0[0];
    p1[1] += p0[1];
    p1[2] += p0[2];
    d[0] = p1[0] - p0[0];
    d[1] = p1[1] - p0[1];
    d[2] = p1[2] - p0[2];
    mid[0] = d[0] * 0.5f + p0[0];
    mid[1] = d[1] * 0.5f + p0[1];
    mid[2] = d[2] * 0.5f + p0[2];
    okA = func_150ACEA0(mid[0], mid[1], mid[2], -d[0], -d[1], -d[2], 0, triA, &hitA[0], &hitA[1], &hitA[2], &distA,
                        &auxA, 0, 0.0f);
    okB = func_150ACEA0(mid[0], mid[1], mid[2], d[0], d[1], d[2], 0, triB, &hitB[0], &hitB[1], &hitB[2], &distB,
                        &auxB, 0, 0.0f);
    if (okA == 0 || okB == 0) {
        return 1;
    }
    opt = *(u32 *) (rec + 0x18);
    col = *(u32 *) (rec + 0x1C);
    sc = *(u32 *) (rec + 0x20);
    func_151C7B1C(hitA, triA, hitB, triB, rec, rec, col & 0xFF, (col >> 8) & 0xFF, (col >> 16) & 0xFF,
                  (opt >> 24) & 1, opt & 0xFF, (opt >> 8) & 0xFF, (opt >> 16) & 0xFF, (opt >> 25) & 1, (opt >> 26) & 1,
                  ((opt >> 27) & 1) == 0, ((opt >> 29) & 1) == 0, (opt >> 30) & 1, (opt >> 28) & 1,
                  (f32) (sc & 0xFF) * 0.024639944f, (f32) ((sc >> 8) & 0xFF) * 0.003079993f, (opt >> 31) == 0, 0xFF, 1);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C7750.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C7B1C.s")

#ifdef NON_MATCHING
void func_15145548(void *, void *, void *, void *, f32 *);
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
s32 memcpy(s32, u8 *, s32);

u8 *func_151C8448(u8 *arg0, s16 arg1) {
    struct {
        u8 u43;
        u8 pad44[0x4];
        f32 u48;
        u8 pad4C[0x18];
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 * u7C;
        u8 * u80;
        u8 * u84;
    } sp;
    u8 *sp38;
    u8 *sp34;
    u8 *sp30;                                     /* compiler-managed */
    f32 sp2C;
    f32 *temp_a2;
    f32 *temp_v0_2;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f4;
    f32 var_f12;
    f32 var_f14;
    f32 var_f16;
    s16 temp_a1;
    s32 temp_v0;
    u8 *temp_a1_2;
    u8 *temp_t0;
    u8 *temp_t1;
    u8 *temp_t3;
    u8 *temp_t6;
    u8 *temp_v1;

    temp_a1 = arg1;
    temp_t0 = arg0 + 0x110;
    if (!((*(u8 *)((u8 *)arg0 + 0x196)) & 2)) {
        return NULL;
    }
    if ((*(u8 *)((u8 *)temp_t0 + 0x86)) & 4) {
        temp_v0 = 1 << temp_a1;
        if (!((*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_t0 + 0x8C))) + 2)) & temp_v0) && !((*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_t0 + 0x90))) + 2)) & temp_v0)) {
            return NULL;
        }
    }
    arg1 = temp_a1;
    sp38 = temp_t0;
    func_151D6310(arg0 + 0x100, temp_a1, 0x40, &sp.u84, &sp.u43);
    sp.u80 = sp.u84;
    if (sp.u84 != NULL) {
        if (sp.u43 != 0) {
            temp_v1 = arg0 + (arg1 * 4);
            temp_a1_2 = arg0 + 0xC0;
            sp30 = temp_a1_2;
            sp34 = temp_v1;
            memcpy((*(s32 *)((u8 *)temp_v1 + 0x100)), temp_a1_2, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v1 + 0x100)) + 0x40, temp_a1_2, 0x40);
        }
        temp_v0_2 = func_15144B34((s32) arg1);
        temp_a2 = temp_v0_2;
        sp.u70 = (*(f32 *)((u8 *)arg0 + 0x40)) - (*(f32 *)((u8 *)arg0 + 0x34));
        sp.u74 = (*(f32 *)((u8 *)arg0 + 0x44)) - (*(f32 *)((u8 *)arg0 + 0x38));
        sp.u7C = temp_v0_2;
        sp.u78 = (*(f32 *)((u8 *)arg0 + 0x48)) - (*(f32 *)((u8 *)arg0 + 0x3C));
        func_15145548(arg0 + 0x34, &sp.u70, temp_a2, &sp.u64, 0);
        temp_f0 = sp.u64 - (*(f32 *)((u8 *)sp.u7C + 0));
        temp_f2 = sp.u68 - (*(f32 *)((u8 *)sp.u7C + 4));
        temp_f12 = sp.u6C - (*(f32 *)((u8 *)sp.u7C + 8));
        temp_f18 = (sp.u74 * temp_f12) - (temp_f2 * sp.u78);
        temp_f4 = (sp.u78 * temp_f0) - (temp_f12 * sp.u70);
        sp30 = (u8 *)(s32)temp_f4;
        temp_f10 = (sp.u70 * temp_f2) - (temp_f0 * sp.u74);
        sp2C = temp_f10;
        temp_f14 = (temp_f18 * temp_f18) + (temp_f4 * temp_f4) + (temp_f10 * temp_f10);
        sp.u48 = temp_f14;
        if (temp_f14 == 0.0f) {
            var_f12 = 0.0f;
            var_f14 = 0.0f;
            var_f16 = 0.0f;
        } else {
            temp_f2_2 = (*(f32 *)((u8 *)arg0 + 0x30)) / sqrtf(sp.u48);
            var_f12 = temp_f18 * temp_f2_2;
            var_f14 = (s32)sp30 * (s32)temp_f2_2;
            var_f16 = sp2C * temp_f2_2;
        }
        (*(s16 *)((u8 *)sp.u84 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x40)) - var_f12);
        (*(s16 *)((u8 *)sp.u84 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x44)) - var_f14);
        (*(s16 *)((u8 *)sp.u84 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x48)) - var_f16);
        (*(s16 *)((u8 *)sp.u84 + 8)) = (s16) (s32) (*(f32 *)((u8 *)sp38 + 0));
        (*(s16 *)((u8 *)sp.u84 + 6)) = 0;
        temp_t1 = sp.u84 + 0x10;
        sp.u84 = temp_t1;
        (*(s16 *)((u8 *)temp_t1 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - var_f12);
        (*(s16 *)((u8 *)sp.u84 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) - var_f14);
        (*(s16 *)((u8 *)sp.u84 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - var_f16);
        (*(s16 *)((u8 *)temp_t1 + 8)) = (s16) (s32) (*(f32 *)((u8 *)sp38 + 4));
        (*(s16 *)((u8 *)sp.u84 + 6)) = 0;
        temp_t6 = sp.u84 + 0x10;
        sp.u84 = temp_t6;
        (*(s16 *)((u8 *)temp_t6 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + var_f12);
        (*(s16 *)((u8 *)sp.u84 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + var_f14);
        (*(s16 *)((u8 *)sp.u84 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + var_f16);
        (*(s16 *)((u8 *)temp_t6 + 8)) = (s16) (s32) (*(f32 *)((u8 *)sp38 + 4));
        (*(s16 *)((u8 *)sp.u84 + 6)) = 0;
        temp_t3 = sp.u84 + 0x10;
        sp.u84 = temp_t3;
        (*(s16 *)((u8 *)temp_t3 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x40)) + var_f12);
        (*(s16 *)((u8 *)sp.u84 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x44)) + var_f14);
        (*(s16 *)((u8 *)sp.u84 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x48)) + var_f16);
        (*(s16 *)((u8 *)temp_t3 + 8)) = (s16) (s32) (*(f32 *)((u8 *)sp38 + 0));
        (*(s16 *)((u8 *)sp.u84 + 6)) = 0;
        return sp.u80;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C8448.s")
#endif
#ifdef NON_MATCHING
s32 func_151C8880(u8 *arg0) {
    s16 temp_v1;
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 *temp_a1;
    u8 *temp_a1_2;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_4;
    u8 *temp_v0_5;
    u8 *temp_v0_6;
    u8 *temp_v1_2;
    u8 *temp_v1_3;

    temp_s0 = arg0 + 0x110;
    if ((*(u8 *)((u8 *)arg0 + 0x196)) & 1) {
        temp_v1 = (*(s16 *)((u8 *)temp_s0 + 0x84));
        (*(s16 *)((u8 *)temp_s0 + 0x82)) = (s16) ((*(s16 *)((u8 *)temp_s0 + 0x82)) + D_800BE9E4);
        if ((*(s16 *)((u8 *)temp_s0 + 0x82)) >= temp_v1) {
            do {
                (*(s16 *)((u8 *)temp_s0 + 0x82)) = (s16) ((*(s16 *)((u8 *)temp_s0 + 0x82)) - temp_v1);
            } while ((*(s16 *)((u8 *)temp_s0 + 0x82)) >= temp_v1);
        }
        if ((*(s16 *)((u8 *)temp_s0 + 0x82)) < (*(s16 *)((u8 *)temp_s0 + 0x7E))) {
            (*(u8 *)((u8 *)temp_s0 + 0x86)) = (u8) ((*(u8 *)((u8 *)temp_s0 + 0x86)) | 2);
        } else {
            (*(u8 *)((u8 *)temp_s0 + 0x86)) = (u8) ((*(u8 *)((u8 *)temp_s0 + 0x86)) & 0xFFFD);
        }
    }
    temp_s0_2 = arg0 + 0x110;
    if ((*(u8 *)((u8 *)arg0 + 0x196)) & 2) {
        (*(f32 *)((u8 *)temp_s0_2 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_s0_2 + 0x18)) + ((*(f32 *)((u8 *)temp_s0_2 + 0x20)) * D_800BE9A4));
        (*(f32 *)((u8 *)temp_s0_2 + 0x1C)) = (f32) ((*(f32 *)((u8 *)temp_s0_2 + 0x1C)) + ((*(f32 *)((u8 *)temp_s0_2 + 0x24)) * D_800BE9A4));
        (*(f32 *)((u8 *)temp_s0_2 + 0x18)) = func_15144B68((*(f32 *)((u8 *)temp_s0_2 + 0x18)));
        (*(f32 *)((u8 *)temp_s0_2 + 0x1C)) = func_15144B68((*(f32 *)((u8 *)temp_s0_2 + 0x1C)));
        (*(f32 *)((u8 *)temp_s0_2 + 0)) = (f32) ((func_150AD78C((*(f32 *)((u8 *)temp_s0_2 + 0x18))) * (*(f32 *)((u8 *)temp_s0_2 + 0x10))) + (*(f32 *)((u8 *)temp_s0_2 + 8)));
        temp_v0 = (*(u8 **)((u8 *)temp_s0_2 + 0x2C));
        (*(f32 *)((u8 *)temp_s0_2 + 4)) = (f32) ((func_150AD78C((*(f32 *)((u8 *)temp_s0_2 + 0x1C))) * (*(f32 *)((u8 *)temp_s0_2 + 0x14))) + (*(f32 *)((u8 *)temp_s0_2 + 0xC)));
        if (temp_v0 != NULL) {
            (*(s8 *)((u8 *)((*(u8 **)((u8 *)temp_v0 + 0x14))) + 9)) = 0;
        }
        temp_v0_2 = (*(u8 **)((u8 *)temp_s0_2 + 0x88));
        if ((temp_v0_2 != NULL) && ((*(u8 *)((u8 *)temp_s0_2 + 0x86)) & 0x10)) {
            (*(s8 *)((u8 *)temp_v0_2 + 0x14)) = 0;
        }
    } else {
        temp_v0_3 = (*(u8 **)((u8 *)temp_s0_2 + 0x2C));
        if (temp_v0_3 != NULL) {
            (*(s8 *)((u8 *)((*(u8 **)((u8 *)temp_v0_3 + 0x14))) + 9)) = 1;
        }
        temp_v0_4 = (*(u8 **)((u8 *)temp_s0_2 + 0x88));
        if (temp_v0_4 != NULL) {
            (*(s8 *)((u8 *)temp_v0_4 + 0x14)) = 1;
        }
    }
    (*(f32 *)((u8 *)temp_s0_2 + 0x54)) = (f32) ((*(f32 *)((u8 *)temp_s0_2 + 0x54)) + (0.080000006f * D_800BE9A4));
    if ((*(f32 *)((u8 *)temp_s0_2 + 0x54)) > 1.0f) {
        do {
            if ((*(u8 *)((u8 *)temp_s0_2 + 0x86)) & 2) {
                (*(u8 *)((u8 *)temp_s0_2 + 0x58)) = (u8) ((*(u8 *)((u8 *)temp_s0_2 + 0x58)) ^ 1);
            }
            (*(f32 *)((u8 *)temp_s0_2 + 0x54)) = (f32) ((*(f32 *)((u8 *)temp_s0_2 + 0x54)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s0_2 + 0x54)) > 1.0f);
    }
    if ((*(u8 *)((u8 *)temp_s0_2 + 0x58)) != 0) {
        temp_v0_5 = (*(u8 **)((u8 *)temp_s0_2 + 0x40));
        (*(s32 *)((u8 *)temp_v0_5 + 0x60)) = (s32) ((*(s32 *)((u8 *)temp_v0_5 + 0x60)) & 0xFFFDFFFF);
        temp_v1_2 = (*(u8 **)((u8 *)temp_s0_2 + 0x44));
        (*(s32 *)((u8 *)temp_v1_2 + 0x60)) = (s32) ((*(s32 *)((u8 *)temp_v1_2 + 0x60)) | 0x20000);
        temp_a0 = (*(u8 **)((u8 *)temp_s0_2 + 0x4C));
        (*(s32 *)((u8 *)temp_a0 + 0x60)) = (s32) ((*(s32 *)((u8 *)temp_a0 + 0x60)) & 0xFFFDFFFF);
        temp_a1 = (*(u8 **)((u8 *)temp_s0_2 + 0x50));
        (*(s32 *)((u8 *)temp_a1 + 0x60)) = (s32) ((*(s32 *)((u8 *)temp_a1 + 0x60)) | 0x20000);
    } else {
        temp_v0_6 = (*(u8 **)((u8 *)temp_s0_2 + 0x40));
        (*(s32 *)((u8 *)temp_v0_6 + 0x60)) = (s32) ((*(s32 *)((u8 *)temp_v0_6 + 0x60)) | 0x20000);
        temp_v1_3 = (*(u8 **)((u8 *)temp_s0_2 + 0x44));
        (*(s32 *)((u8 *)temp_v1_3 + 0x60)) = (s32) ((*(s32 *)((u8 *)temp_v1_3 + 0x60)) & 0xFFFDFFFF);
        temp_a0_2 = (*(u8 **)((u8 *)temp_s0_2 + 0x4C));
        (*(s32 *)((u8 *)temp_a0_2 + 0x60)) = (s32) ((*(s32 *)((u8 *)temp_a0_2 + 0x60)) | 0x20000);
        temp_a1_2 = (*(u8 **)((u8 *)temp_s0_2 + 0x50));
        (*(s32 *)((u8 *)temp_a1_2 + 0x60)) = (s32) ((*(s32 *)((u8 *)temp_a1_2 + 0x60)) & 0xFFFDFFFF);
    }
    if ((*(u8 *)((u8 *)temp_s0_2 + 0x86)) & 8) {
        (*(s8 *)((u8 *)arg0 + 0x5C)) = (s8) (u32) ((func_150AD78C((*(f32 *)((u8 *)temp_s0_2 + 0x98))) * 112.5f) + 142.5f);
        (*(f32 *)((u8 *)temp_s0_2 + 0x98)) = func_15144B68((*(f32 *)((u8 *)temp_s0_2 + 0x98)) + ((*(f32 *)((u8 *)temp_s0_2 + 0x9C)) * D_800BE9A4));
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C8880.s")
#endif
void func_151C8C24(u8 *arg0, s32 arg1) {
    s32 sp18[2];
    if (arg0 != NULL) {
        sp18[0] = (s32)arg0;
        sp18[1] = arg1;
        func_151403A8(sp18, 0x20);
    }
}

s32 func_151C8D90(s32, u8 *);
void func_151C8F4C(s32, u8 *);
void func_151C8C5C(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *v;
    u8 **q = &arg0;
    switch (arg2) {
    case 0x20:
        v = (*q) + 0x110;
        if ((v[0x86] & 0x10) && (*(s32 *)(v + 0x28) == arg1[1])) {
            if (func_151C8D90(arg1[0], (*q))) {
                func_151C8F4C(arg1[0], (*q));
            }
        }
        break;
    case 0x3A:
        v = (*q) + 0x110;
        if (*(s32 *)(v + 0x28) == arg1[0]) {
            switch (((u8 *)arg1)[4]) {
            case 0: v[0x86] |= 2; break;
            case 1: v[0x86] &= ~2; break;
            case 2: func_151C8F4C(0, (*q)); break;
            }
        }
        break;
    }
}

s32 func_151C8D5C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s16 *arg6) {
    u8 *p;
    s16 *q;
    p = *(u8 **)(arg0 + 0x18);
    q = arg6;
    if (!(p[0x86] & 2)) {
        *q = 0;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C8D90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C8F4C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C957C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C9748.s")

void func_151C9A84(struct210 *arg0) {
    u8 *p;
    struct102 *a;
    struct210 **pa = &arg0; // fakematch: arg0 address taken keeps it in its home slot

    p = (u8 *)*pa + 0x110;
    if (*(s32 *)((u8 *)*pa + 0x13C) != 0) {
        func_1516972C(*(struct102 **)(p + 0x2C));
        func_1000FD38(func_151C8D5C, p, 0);
    }
    p = (u8 *)*pa;
    a = *(struct102 **)(p + 0x144);
    p += 0x110;
    if (a != NULL) {
        func_1516972C(a);
    }
    if (*(struct102 **)(p + 0x38) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x38));
    }
    if (*(struct102 **)(p + 0x3C) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x3C));
    }
    if (*(struct102 **)(p + 0x40) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x40));
    }
    if (*(struct102 **)(p + 0x44) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x44));
    }
    if (*(struct102 **)(p + 0x48) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x48));
    }
    if (*(struct102 **)(p + 0x4C) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x4C));
    }
    if (*(struct102 **)(p + 0x50) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x50));
    }
    func_1513CA6C(arg0);
}

void func_151C9B88(struct210 *arg0) {
    u8 *p;
    struct102 *a;
    struct210 **pa = &arg0; // fakematch: arg0 address taken keeps it in its home slot

    p = (u8 *)*pa + 0x110;
    if (*(s32 *)((u8 *)*pa + 0x13C) != 0) {
        func_1516972C(*(struct102 **)(p + 0x2C));
        func_1000FD38(func_151C8D5C, p, 0);
    }
    p = (u8 *)*pa;
    a = *(struct102 **)(p + 0x144);
    p += 0x110;
    if (a != NULL) {
        func_1516972C(a);
    }
    if (*(struct102 **)(p + 0x38) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x38));
    }
    if (*(struct102 **)(p + 0x3C) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x3C));
    }
    if (*(struct102 **)(p + 0x40) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x40));
    }
    if (*(struct102 **)(p + 0x44) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x44));
    }
    if (*(struct102 **)(p + 0x48) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x48));
    }
    if (*(struct102 **)(p + 0x4C) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x4C));
    }
    if (*(struct102 **)(p + 0x50) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x50));
    }
    func_1513CAA0(arg0);
}

s32 func_151C9C8C(u8 *arg0, s32 arg1) {
    s32 *q = &arg1; // fakematch: arg1 home store
    u8 *p = *(u8 **)(arg0 + 0x170) + 0x110;
    if (p[0x86] & 2) {
        return 1;
    }
    return 0;
}

void func_151C9CBC(s32 arg0, s32 arg1) {
    s32 tmp[2];
    tmp[0] = arg1;
    *(u8 *)(tmp + 1) = arg0;
    func_151403A8(tmp, 0x3A);
}

s32 func_1504715C(s32 *, struct127 *);
#ifdef NON_MATCHING
/* P170 */
s32 func_15046F70(f32 *, s32, f32, s32 *);
f32 func_150ADA68(void);
s32 func_150ADA20(void);
void func_150E856C(f32, u8, s32 *, f32 *, s32, s32, s32, s32, s32, s32, u8, s32);
void func_151D5404(struct17 *, f32, f32, f32, s16, s16, s32, s32);
void func_151D58E4(struct17 *, f32, f32, f32, s16, s32, s32);
s32 func_151D5AC4(struct17 *, u8, s32);
void func_151D45A4(struct17 *, u8, s32);
void func_150E892C(struct17 *, s16, u8, s32);
s32 func_15154728(f32 *, f32, f32, f32, f32, s32, s32);
s32 func_15136C3C(struct127 *, s32, s32, s32, s32, s32, s32, s32);
u16 func_10010F88(s32 arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9);
void func_151CA070(struct127 *arg0, u8 arg1, s32 arg2);

// object_explode: the big explosion at an object (135 units above its position +0x14/+0x18/+0x1C). On the ground
// (+0x2D8 == 0) a scorch mark (func_150E856C) where a ray 200 units down hits a floor with flag 1, and the debris
// burst func_15136C3C; then the blast effects func_151D5404 / func_151D58E4 / func_151D5AC4 / func_151D45A4, the
// sparks func_150E892C (at the scorch point when there is one), the flash func_15154728, the sound 0x60D, and in
// the air the extra burst func_151CA070. Nothing for a NULL object.
void func_151C9740(struct127 *obj, u8 arg1, s32 arg2) {
    s32 ground[9];  /* floor query (func_1504715C / func_15046F70): f32 height at +0, flags byte +0x1C */
    struct17 probe;
    u8 inAir;
    u8 scorched;
    struct17 mark;
    struct17 pos;
    f32 r;
    u32 a;
    u32 b;

    if (obj == NULL) {
        return;
    }
    pos.unk0 = *(f32 *) ((u8 *) obj + 0x14);
    pos.unk4 = *(f32 *) ((u8 *) obj + 0x18) + 135.0f;
    pos.unk8 = *(f32 *) ((u8 *) obj + 0x1C);
    scorched = 0;
    inAir = (*(f32 *) ((u8 *) obj + 0x2D8) != 0.0f) ? 1 : 0;
    if (!inAir) {
        probe = pos;
        func_1504715C(ground, obj);
        if (func_15046F70((f32 *) &probe, 0, pos.unk4 - 200.0f, ground) != 0 && (((u8 *) ground)[0x1C] & 1)) {
            mark.unk0 = probe.unk0;
            mark.unk4 = *(f32 *) &ground[0];
            mark.unk8 = probe.unk8;
            scorched = 1;
            r = func_150ADA68();
            a = func_150ADA20();
            b = func_150ADA20();
            func_150E856C(r * 125.0f + 204.0f, a % 101 + 155, &ground[1], (f32 *) &mark, b % 302 + 500, 0, 1, 0, 0,
                          0, arg1, 0);
        }
    }
    func_151D5404(&pos, 506.0f, 1013.0f, 0.000987166888f, 15, 20, arg1, arg2);
    func_151D58E4(&pos, 506.0f, 1013.0f, 0.000987166888f, 5, arg1, arg2);
    func_151D5AC4(&pos, arg1, arg2);
    func_151D45A4(&pos, arg1, arg2);
    func_150E892C(scorched ? &mark : &pos, (u32) func_150ADA20() % 62 + 120, arg1, arg2);
    r = func_150ADA68();
    func_15154728((f32 *) &pos, r + r + 8.0f, 2.4641099f, (u32) func_150ADA20() % 56 + 200, 0.0f, arg1, arg2);
    if (!inAir) {
        func_15136C3C(obj, 0, 0, 1, 0, 0, arg1, arg2);
    }
    func_10010F88(0x60D, 0x7D00, 0, 0, 0, (s32) pos.unk0, (s32) pos.unk4, (s32) pos.unk8, 500, 1000);
    if (inAir) {
        func_151CA070(obj, arg1, arg2);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C9740.s")
#endif

void func_151AC3F0(struct17 *, s32 *, s32, u8, s32);
void func_151CA070(struct127 *arg0, u8 arg1, s32 arg2) {
    struct17 pos;
    s32 sp20[9];

    pos.unk0 = *(f32 *)((u8 *)arg0 + 0x14);
    pos.unk4 = *(f32 *)((u8 *)arg0 + 0x180) + 2.0f;
    pos.unk8 = *(f32 *)((u8 *)arg0 + 0x1C);
    func_1504715C(sp20, arg0);
    func_151AC3F0(&pos, sp20, 2, arg1, arg2);
}

s32 func_151CA0E0(u8 *arg0)
{
  u8 *new_var2;
  u8 *new_var;
  new_var = arg0;
  new_var2 = *((u8 **) (new_var + 0x18));
  if ((*((u8 *) (new_var2 + 0x6F))) == 0)
  {
    *((s8 *) ((*((u8 **) (arg0 + 0x14))) + 9)) = 0;
  }
  else
  {
    *((s8 *) ((*((u8 **) (new_var + 0x14))) + 9)) = 1;
  }
  return 1;
}

s32 func_151CA114(u8 *arg0, s8 *arg1)
{
  u8 *new_var;
  new_var = *((u8 **) (((u8 *) arg0) + 0x188)); // fakematch: pointer in a named local (permuter)
  if ((*((u8 *) (((u8 *) new_var) + 0x6F))) == 0)
  {
    *arg1 = 1;
  }
  else
  {
    *((s32 *) (((u8 *) arg0) + 0x58)) = (s32) ((*((s32 *) (((u8 *) arg0) + 0x58))) & (~2));
    *arg1 = 0;
  }
  return 1;
}
