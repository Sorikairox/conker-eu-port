#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_151846C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_151848D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15185360.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15185514.s")

u8 *func_151859C4(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 q;
    f32 temp_f16;

    q = (*(f32 *)(arg0 + 8) - *(f32 *)(arg0 + 4)) / ((*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) - (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8)));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * q + *(f32 *)(arg0 + 0);
    temp_f16 = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * q + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = temp_f16;
    *(f32 *)(arg2 + 4) = temp_f16;
    *(s16 *)(arg2 + 0xC) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * q + (f32) *(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * q + (f32) *(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * q + (f32) *(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}

s32 func_15185AC4(f32 *arg0) {
    return arg0[2] < arg0[1];
}

u8 *func_15185AEC(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 q;

    q = (*(f32 *)(arg0 + 8) + *(f32 *)(arg0 + 0)) / ((*(f32 *)(arg0 + 8) - *(f32 *)(arg1 + 8)) + (*(f32 *)(arg0 + 0) - *(f32 *)(arg1 + 0)));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * q + *(f32 *)(arg0 + 0);
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * q + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = -*(f32 *)(arg2 + 0);
    *(s16 *)(arg2 + 0xC) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * q + (f32) *(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * q + (f32) *(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * q + (f32) *(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}

s32 func_15185BEC(f32 *arg0) {
    return arg0[0] < -arg0[2];
}

u8 *func_15185C18(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 q;

    q = (*(f32 *)(arg0 + 8) + *(f32 *)(arg0 + 4)) / ((*(f32 *)(arg0 + 8) - *(f32 *)(arg1 + 8)) + (*(f32 *)(arg0 + 4) - *(f32 *)(arg1 + 4)));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * q + *(f32 *)(arg0 + 0);
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * q + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = -*(f32 *)(arg2 + 4);
    *(s16 *)(arg2 + 0xC) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * q + (f32) *(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * q + (f32) *(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * q + (f32) *(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}

s32 func_15185D20(f32 *arg0) {
    return arg0[1] < -arg0[2];
}

u8 *func_15185D4C(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 q;

    q = (*(f32 *)(arg0 + 8) - *(f32 *)(arg0 + 0)) / ((*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) - (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8)));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * q + *(f32 *)(arg0 + 0);
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * q + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = *(f32 *)(arg2 + 0);
    *(s16 *)(arg2 + 0xC) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * q + (f32) *(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * q + (f32) *(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * q + (f32) *(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}

s32 func_15185E44(f32 *arg0) {
    return arg0[2] < arg0[0];
}

u8 *func_15185E6C(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 q;

    q = (D_800D3AA8 - *(f32 *)(arg0 + 8)) / (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * q + *(f32 *)(arg0 + 0);
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * q + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = D_800D3AA8;
    *(s16 *)(arg2 + 0xC) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * q + (f32) *(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * q + (f32) *(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * q + (f32) *(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}

s32 func_15185F6C(f32 *arg0) {
    return D_800D3AA8 < arg0[2];
}

u8 *func_15185F98(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 q;

    q = (D_800D3AAC - *(f32 *)(arg0 + 8)) / (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * q + *(f32 *)(arg0 + 0);
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * q + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = D_800D3AAC;
    *(s16 *)(arg2 + 0xC) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * q + (f32) *(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * q + (f32) *(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * q + (f32) *(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}

s32 func_15186098(f32 *arg0) {
    return arg0[2] < D_800D3AAC;
}

typedef struct {
    f32 x, y, z;
    s16 s, t, u;
} ClipVtx_60C4;
ClipVtx_60C4 *func_151860C4(ClipVtx_60C4 *a, ClipVtx_60C4 *b, ClipVtx_60C4 *out) {
    f32 t;

    t = a->x / (a->x - b->x);
    out->x = 0.0f;
    out->y = a->y + (b->y - a->y) * t;
    out->z = a->z + (b->z - a->z) * t;
    out->s = a->s + (b->s - a->s) * t;
    out->t = a->t + (b->t - a->t) * t;
    out->u = a->u + (b->u - a->u) * t;
    return out + 1;
}

s32 func_151861B4(f32 *arg0) {
    return *arg0 <= 0.0f;
}

ClipVtx_60C4 *func_151861DC(ClipVtx_60C4 *a, ClipVtx_60C4 *b, ClipVtx_60C4 *out) {
    f32 t;

    t = a->y / (a->y - b->y);
    out->y = 0.0f;
    out->x = a->x + (b->x - a->x) * t;
    out->z = a->z + (b->z - a->z) * t;
    out->s = a->s + (b->s - a->s) * t;
    out->t = a->t + (b->t - a->t) * t;
    out->u = a->u + (b->u - a->u) * t;
    return out + 1;
}

s32 func_151862CC(f32 *arg0) {
    return arg0[1] <= 0.0f;
}

s32 func_151862F4(f32 *arg0) {
    return *arg0 > 0.0f;
}

s32 func_1518631C(f32 *arg0) {
    return arg0[1] > 0.0f;
}

extern ClipVtx_60C4 *(*D_8008D838[])(ClipVtx_60C4 *, ClipVtx_60C4 *, ClipVtx_60C4 *);
extern s32 (*D_8008D860[])(ClipVtx_60C4 *);
ClipVtx_60C4 *func_15186344(ClipVtx_60C4 *in, s32 n, s32 plane, ClipVtx_60C4 *out) {
    ClipVtx_60C4 *prev = &in[n - 1];
    ClipVtx_60C4 *(*isect)(ClipVtx_60C4 *, ClipVtx_60C4 *, ClipVtx_60C4 *) = D_8008D838[plane];
    s32 (*inside)(ClipVtx_60C4 *) = D_8008D860[plane];
    ClipVtx_60C4 *cur = in;
    s32 i;

    for (i = 0; i < n; i++) {
        if (inside(cur)) {
            if (inside(prev)) {
                *out++ = *cur;
            } else {
                out = isect(prev, cur, out);
                *out++ = *cur;
            }
        } else if (inside(prev)) {
            out = isect(prev, cur, out);
        }
        prev = cur;
        cur++;
    }
    return out;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15186494.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15186A9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15186D04.s")

#ifdef NON_MATCHING
extern s32 D_800DE44C;
extern s32 D_800DE450;
extern s32 D_800DE454;
extern s32 D_800DE460;
extern s32 D_800DE464;
extern s32 D_800DE468;
extern f32 D_800DE46C;
extern s8 D_800DE470;
extern s8 D_800DE471;

void func_15187820(s32 arg0) {
    D_800DE44C = 0x258;
    D_800DE450 = 0xB4;
    D_800DE454 = 0x5A;
    D_800DE460 = 0x3F8;
    D_800DE464 = 0;
    D_800DE468 = 1;
    D_800DE46C = 1.0f;
    D_800DE470 = 1;
    D_800DE471 = 1;
    switch (arg0) {                                 /* irregular */
    case 33:
        D_800DE44C = 0x12C0;
        D_800DE450 = 0x12BF;
        D_800DE454 = 0x12BE;
        D_800DE460 = 0x3F2;
        D_800DE464 = 1;
        D_800DE468 = 4;
        D_800DE470 = 0;
        return;
    case 34:
        D_800DE44C = 0x960;
        D_800DE450 = 0x95F;
        D_800DE454 = 0x95E;
        D_800DE468 = 4;
        D_800DE470 = 0;
        return;
    case 20:
        D_800DE471 = 0;
        return;
    case 41:
        D_800DE44C = 0x4B0;
        D_800DE450 = 0x258;
        D_800DE454 = 0x12C;
        return;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15187820.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15187954.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15187B50.s")

#ifdef NON_MATCHING
void func_15187EE8(struct102 *arg0) {
    f32 temp_f0;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v1;
    s16 var_a0;
    s16 var_v1;
    s32 var_a1;
    u8 *temp_v0_3;
    u8 *var_v0;

    temp_v0 = (*(s16 *)((u8 *)arg0 + 0xA8));
    if (temp_v0 < 0) {
        func_10004074((*(s32 *)((u8 *)arg0 + 0xA4)), arg0);
        func_1516972C(arg0);
        return;
    }
    (*(s16 *)((u8 *)arg0 + 0xA8)) = (s16) (temp_v0 + D_800BE9E4);
    temp_v0_2 = (*(s16 *)((u8 *)arg0 + 0xA8));
    if ((*(s16 *)((u8 *)arg0 + 0xAA)) < temp_v0_2) {
        (*(s16 *)((u8 *)arg0 + 0xA8)) = -0xA;
        return;
    }
    var_a1 = 0;
    if (temp_v0_2 >= 0) {
        do {
            temp_v0_3 = (*(s32 *)((u8 *)arg0 + 0xA4)) + var_a1;
            temp_v1 = (*(s16 *)((u8 *)temp_v0_3 + 0x94));
            if (temp_v1 < (*(s16 *)((u8 *)temp_v0_3 + 0x96))) {
                (*(s16 *)((u8 *)temp_v0_3 + 0x94)) = (s16) (temp_v1 + D_800BE9E4);
                var_v0 = (*(s32 *)((u8 *)arg0 + 0xA4)) + var_a1;
                var_a0 = (*(s16 *)((u8 *)var_v0 + 0x96));
                var_v1 = (*(s16 *)((u8 *)var_v0 + 0x94));
                if (var_a0 < var_v1) {
                    (*(s16 *)((u8 *)var_v0 + 0x94)) = var_a0;
                    var_v0 = (*(s32 *)((u8 *)arg0 + 0xA4)) + var_a1;
                    var_v1 = (*(s16 *)((u8 *)var_v0 + 0x94));
                    var_a0 = (*(s16 *)((u8 *)var_v0 + 0x96));
                }
                temp_f0 = (*(f32 *)((u8 *)var_v0 + 0x8C));
                (*(f32 *)((u8 *)var_v0 + 0x90)) = (f32) ((*(f32 *)((u8 *)var_v0 + 0x90)) + (temp_f0 - (((temp_f0 / 3.0f) * (f32) var_v1) / (f32) var_a0)));
            }
            var_a1 += 0xA0;
        } while (var_a1 != 0x780);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15187EE8.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15188008.s")

#ifdef NON_MATCHING
s32 func_151F05C0(u8 *);
extern f32 D_8008D918;

void func_151882DC(u8 *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp44;
    f32 sp3C;
    f32 sp34;
    f32 sp30;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f22;

    temp_f12 = arg1 * D_8008D918;
    arg1 = temp_f12;
    arg2 *= D_8008D918;
    arg3 *= D_8008D918;
    sp44 = sinf(temp_f12);
    temp_f20 = cosf(arg1);
    temp_f22 = sinf(arg2);
    sp34 = cosf(arg2);
    sp3C = sinf(arg3);
    sp30 = cosf(arg3);
    func_151F05C0(arg0);
    temp_f0 = sp44 * temp_f22;
    (*(f32 *)((u8 *)arg0 + 0x18)) = sp44;
    (*(f32 *)((u8 *)arg0 + 0)) = (f32) ((sp34 * sp30) - (temp_f0 * sp3C));
    (*(f32 *)((u8 *)arg0 + 4)) = (f32) ((sp34 * sp3C) + (temp_f0 * sp30));
    (*(f32 *)((u8 *)arg0 + 8)) = (f32) (-temp_f22 * temp_f20);
    temp_f0_2 = sp44 * sp34;
    (*(f32 *)((u8 *)arg0 + 0x10)) = (f32) (-temp_f20 * sp3C);
    (*(f32 *)((u8 *)arg0 + 0x14)) = (f32) (temp_f20 * sp30);
    (*(f32 *)((u8 *)arg0 + 0x20)) = (f32) ((temp_f22 * sp30) + (temp_f0_2 * sp3C));
    (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) (temp_f20 * sp34);
    (*(f32 *)((u8 *)arg0 + 0x24)) = (f32) ((temp_f22 * sp3C) - (temp_f0_2 * sp30));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_151882DC.s")
#endif