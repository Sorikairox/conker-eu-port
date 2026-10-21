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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15187EE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_15188008.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/func_151882DC.s")
