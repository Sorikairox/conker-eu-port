#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A1C90[];
extern u8 D_800A1CA8[];
#endif

typedef struct {
    u8  pad0[0x8];
    s32 *unk8;
    u8  unkC;
} struct_eu_11CB90_60;

typedef struct {
    u8  pad0[0x12C];
    s32 unk12C[1];
} struct_eu_11CB90_elem;

void func_150F0820(void *arg0);
void func_150F0898(void *arg0);
void func_150F0900(void *arg0);
void func_150F0968(void *arg0);
void func_151617C4(void *arg0);
void func_151617E4(void *arg0);

#ifdef NON_MATCHING
extern u16 D_80088EA0[3];

/*
 * object_7B_pulse_scale: per-frame "breathing" of object type 0x7B (func_150348D4's case 0x7B; func_150F20C8 below
 * builds the same object's joint entries). A shared phase (the s16 at D_800CC298 + 0x14) advances by
 * D_80088EA0[sel] * D_800BE9E4 (speeds 720 / 2000 / 3000: sel 1 when the object's +0x2E4 flags have both bits 0-1
 * set, sel 2 when both bits 2-3 are set, else 0); the scale 0.9 + 0.35 * (cos(phase) + 1) / 2 (0.9 .. 1.25, the
 * phase in 1/65536 turns) multiplies the 3x3 part of the 4x4 float matrix at the model's (+0x1D4) +0xF80.
 * The asm leaves a pointer in v0; no caller reads it (void).
 */
void func_150F1F80(struct127 *object) {
    u8 *obj = (u8 *) object;
    s16 *phase = (s16 *)((u8 *)&D_800CC298 + 0x14);
    u16 speeds[3];
    s32 flags;
    s32 sel;
    f32 scale;
    f32 *m;
    s32 r;
    s32 c;

    speeds[0] = D_80088EA0[0];
    speeds[1] = D_80088EA0[1];
    speeds[2] = D_80088EA0[2];
    flags = *(s32 *)(obj + 0x2E4);
    sel = 0;
    if ((flags & 3) == 3) {
        sel = 1;
    }
    if ((flags & 0xC) == 0xC) {
        sel = 2;
    }
    *phase += speeds[sel] * D_800BE9E4;
    /* 0.35000002f: the ROM constant is 0x3EB33334, one ulp above 0.35f */
    scale = (cosf(*phase * (6.2831855f / 65536.0f)) + 1.0f) * 0.5f * 0.35000002f + 0.9f;
    m = (f32 *)(*(u8 **)(obj + 0x1D4) + 0xF80);
    for (r = 0; r < 3; r++) {
        for (c = 0; c < 3; c++) {
            m[r * 4 + c] *= scale;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11F790/func_150F1F80.s")
#endif

#ifdef NON_MATCHING
/*
 * P62: adjustment entries of object type 0x7B for func_150342D0 (object i, buffer p): a shared angle (the s16 at
 * D_800CC298 + 0x12) swings down by D_800BE9E4 * 0x222 per call while object i's +0x84 is 0x21 (to at least
 * -0x1999, -6553.6 as a float) and back up otherwise (below 0x1555, 5461.33); the sum is compared as an int, not
 * an s16. Then six entries {joint * 6 + 4, angle} for joints 29..34; returns the end of the entries.
 */
s16 *func_150F20C8(s16 *p, s32 i) {
    s16 *angle = (s16 *)((u8 *)&D_800CC298 + 0x12);
    s32 step = D_800BE9E4 * 0x222;
    s32 v;
    s32 k;

    if (*(u16 *)((u8 *)&D_800CC2D0[i] + 0x84) == 0x21) {
        v = *angle - step;
        if ((f32)v > -6553.6f) {
            *angle = v;
        } else {
            *angle = -0x1999;
        }
    } else {
        v = *angle + step;
        if ((f32)v < 5461.3335f) {
            *angle = v;
        } else {
            *angle = 0x1555;
        }
    }
    for (k = 0; k < 6; k++) {
        p[k * 2] = 29 * 6 + 4 + k * 6;
        p[k * 2 + 1] = *angle;
    }
    return p + 12;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11F790/func_150F20C8.s")
#endif

void func_eu_150F2230(u8 *arg0) {
    if ((*(u16 *)((u8 *)arg0 + 0x84)) == 0x14) {
        (*(u8 *)((u8 *)arg0 + 0x68)) = 0x1B;
    } else {
        (*(u8 *)((u8 *)arg0 + 0x68)) = 0xC;
    }
    (*(u8 *)((u8 *)arg0 + 0x69)) = 0x13;
    if (((*(s32 *)((u8 *)arg0 + 0x2E4)) & 3) == 3) {
        (*(u8 *)((u8 *)arg0 + 0x69)) = 0x14;
    }
    if (((*(s32 *)((u8 *)arg0 + 0x2E4)) & 0xC) == 0xC) {
        (*(u8 *)((u8 *)arg0 + 0x69)) = 0x17;
    }
}

#ifdef NON_MATCHING
s32 func_15150D7C(s32 *, s32 *, s32 *, s32, s32, s32, s32, s32, s32, s32, f32, s32, s32, s32, s32);
s32 func_15154728(f32 *, f32, f32, f32, f32, s32, s32); /* P95: f32 (was the bit pattern as an int) */
s32 func_151D5AC4(f32 *, s32, s32);
extern s32 D_800A1C9C;
extern s32 D_800A1CB0;

void func_151D58E4(void *, f32, f32, f32, u8, u8, s32); /* P95 */
void func_150F2290(u8 *arg0, s32 arg1, s32 arg2) {
    struct {
        s32 u60;
        s32 u64;
        s32 u68;
        u8 pad6C[0x8];
        s16 u74;
        s16 u76;
        s16 u78;
        s16 u7A;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        s16 u8C;
        s16 u8E;
        f32 u90;
        f32 u94;
        f32 u98;
        s32 u9C;
        s32 uA0;
        s32 uA4;
        u8 padA8[0x8];
        s16 uB0;
        s16 uB2;
        s16 uB4;
        s16 uB6;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        s16 uC8;
        s16 uCA;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        s8 uDC;
        u8 padDD[0x3];
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
    } sp;
    f32 sp58;
    f32 var_f10;
    s32 temp_s1;
    s32 temp_t8;

    temp_s1 = arg1 & 0xFF;
    if (arg0 != NULL) {
        sp.uE4 = (*(f32 *)((u8 *)arg0 + 0x14));
        sp.uE8 = (*(f32 *)((u8 *)arg0 + 0x18)) + 20.0f;
        sp.uEC = (*(f32 *)((u8 *)arg0 + 0x1C));
        sp.uE0 = ((*(f32 *)((u8 *)arg0 + 0x14C)) + (*(f32 *)((u8 *)arg0 + 0x150))) * 0.5f;
        func_151D5404((struct17 *) &sp.uE4, 506.0f, 1013.0f, 0.0009871669f, 0xF, 0x14, temp_s1, arg2);
        func_151D58E4(&sp.uE4, 506.0f, 1013.0f, 0.0009871669f, 5, temp_s1, arg2); /* P95: was 0x43FD0000 as an int */
        func_151D5AC4(&sp.uE4, temp_s1 & 0xFF, arg2);
        func_10010F88((func_150ADA20() & 8) + 0x2B6, 0x7FFFU, 0, 0U, 0, (s16) (s32) sp.uE4, (s16) (s32) sp.uE8, (s16) (s32) sp.uEC, 0xFA0, 0x1770);
        func_151D45A4(&sp.uE4, temp_s1 & 0xFF, arg2);
        sp58 = func_150ADA68();
        temp_t8 = (func_150ADA20() % 56U) + 0xC8;
        var_f10 = (f32) temp_t8;
        if (temp_t8 < 0) {
            var_f10 += 4294967296.0f;
        }
        func_15154728(&sp.uE4, (sp58 * 4.0f) + 12.0f, 1.6409999f, var_f10, 0.0f, temp_s1, arg2); /* P95: was 0x3FD20C49 as an int */
        sp.u9C = 3;
        sp.uA0 = 0;
        (*(f32 *)((u8 *)(&sp.uA4) + 0)) = (f32) (*(f32 *)((u8 *)(&sp.uE4) + 0));
        (*(s32 *)((u8 *)(&sp.uA4) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.uE4) + 4));
        (*(s32 *)((u8 *)(&sp.uA4) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.uE4) + 8));
        sp.uB8 = 30.0f;
        sp.uBC = 20.0f;
        sp.uC0 = -1.8550001f;
        sp.uB0 = 0;
        sp.uB2 = 0xFF;
        sp.uB4 = -0x40;
        sp.uB6 = 0x2C;
        sp.uC8 = 0x3C;
        sp.uCA = 0x14;
        sp.uCC = 1.0f * sp.uE0;
        sp.uD0 = 0.0f * sp.uE0;
        sp.uD8 = 0.0f;
        sp.uDC = 0xC;
        sp.uC4 = 0.698f;
        sp.uD4 = 8.990001f;
        func_15150D7C(&sp.u9C, ((u8 *)&D_800A1C90), &D_800A1C9C, 3, 0, 0, 0, 1, -1, 0, 0.0f, 0, 0, temp_s1, arg2);
        sp.u60 = 5;
        sp.u64 = 3;
        (*(f32 *)((u8 *)(&sp.u68) + 0)) = (f32) (*(f32 *)((u8 *)(&sp.uE4) + 0));
        (*(s32 *)((u8 *)(&sp.u68) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.uE4) + 4));
        (*(s32 *)((u8 *)(&sp.u68) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.uE4) + 8));
        sp.u7C = 25.0f;
        sp.u80 = 15.0f;
        sp.u74 = 0;
        sp.u76 = 0xFF;
        sp.u78 = -0x40;
        sp.u7A = 0x1E;
        sp.u8C = 0x46;
        sp.u8E = 0x14;
        sp.u84 = -1.2390001f;
        sp.u88 = 0.37600002f;
        sp.u90 = 0.503f;
        sp.u94 = 0.256f;
        sp.u98 = 13.933001f;
        func_15152700(&sp.u60, ((u8 *)&D_800A1CA8), &D_800A1CB0, 2, 0.0f, 0U, (u8) temp_s1, arg2);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11F790/func_150F2290.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11F790/func_150F2670.s")

#ifdef NON_MATCHING
s32 func_15143874(s16, f32, f32 *, f32 *); /* P95: f32 parameter */
#else
s32 func_15143874(s16, s32, f32 *, f32 *);
#endif

void func_150F2230(u8 *arg0, u8 arg1, s32 arg2) {
    f32 sp2C[3];
    s32 sp20[3];

    if ((*(s32 *)(arg0 + 0x1D4) != 0) && ((*(u8 *)(arg0 + 0x74) & 0xF) != 0xF)) {
        sp2C[0] = 0.0f;
        sp2C[1] = 0.0f;
        sp2C[2] = 0.0f;
#ifdef NON_MATCHING
        func_15143874(func_150ADA20() & 0xFF, 100.0f, sp2C, &sp2C[2]); /* P95: float literal (asm passes the bits 0x42C80000) */
#else
        func_15143874(func_150ADA20() & 0xFF, 0x42C80000, sp2C, &sp2C[2]);
#endif
        func_15143134(sp2C, sp20, *(s32 *)(arg0 + 0x1D4) + 0x4C0);
        func_151C384C(sp20, arg1, arg2);
    }
}
