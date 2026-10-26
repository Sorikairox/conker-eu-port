#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
// limb_trail_effect_spawn: spawns a type 0x17 effect record (effect3d_spawn_default) along the limb `idx` of obj's skeleton
// (obj + 0x1D4, 0x40-byte matrices): the two limb points D_80088CB0[idx] / D_80088CBC[idx] are transformed by the
// limb's matrix (func_15143134), their scaled difference gives the direction; nothing is spawned when its XZ length
// is below D_800A0FB0. The record gets the start point and the normalised XZ direction, and its fields 0x110..0x138
// come from the per-limb tables (direction, speeds, scales, mode byte).
typedef struct {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 pad1;
    /* 0x02 */ s16 flags;
    /* 0x04 */ s16 span;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ s32 w8;
    /* 0x0C */ s32 wC;
    /* 0x10 */ u8 rgba[4];
    /* 0x14 */ u8 pad14[8];
    /* 0x1C */ f32 pos[3];
    /* 0x28 */ f32 dir[3];
    /* 0x34 */ f32 scale[3];
    /* 0x40 */ s32 w40;
    /* 0x44 */ u8 b44;
    /* 0x45 */ u8 b45;
    /* 0x46 */ u8 pad46[2];
} EffSpawn150DB3F0;

extern f32 D_80088CB0[][3];  // limb start point (limb space)
extern f32 D_80088CBC[][3];  // limb end point (limb space)
extern s32 D_80088CC8[];     // limb matrix index
extern f32 D_80088CCC[];     // direction scale
extern s16 D_80088CD0[];     // record lifetime
extern f32 D_80088CD4[];     // record +0x11C
extern f32 D_80088CD8[];     // record +0x120
extern f32 D_80088CDC[];     // record +0x134
extern u8 D_80088CE0[];      // record +0x138
extern f32 D_80088CE4[];     // record +0x12C
extern f32 D_80088CE8[];     // record +0x130

void func_150DB3F0(u8 *obj, s32 idx, u8 group, s32 arg3) {
    EffSpawn150DB3F0 spec;
    f32 b[3];
    f32 a[3];
    f32 dir[3];
    u8 *bones;
    u8 *mtx;
    f32 scale;
    f32 lenSq;
    f32 inv;
    u8 *rec;

    if (obj == NULL) {
        return;
    }
    bones = *(u8 **) (obj + 0x1D4);
    if (bones == NULL) {
        return;
    }
    mtx = bones + (D_80088CC8[idx] << 6);
    func_15143134(D_80088CB0[idx], a, mtx);
    func_15143134(D_80088CBC[idx], b, mtx);
    scale = D_80088CCC[idx];
    dir[0] = scale * (b[0] - a[0]);
    dir[1] = scale * (b[1] - a[1]);
    dir[2] = scale * (b[2] - a[2]);
    lenSq = dir[0] * dir[0] + dir[2] * dir[2];
    if (fabsf(lenSq) < 0.0001f) {
        return;
    }
    inv = 1.0f / sqrtf(lenSq);
    spec.type = 0x17;
    spec.wC = 0x243A;
    spec.w8 = 0;
    spec.w40 = 0x401;
    spec.b44 = 0xFF;
    spec.b45 = 0xFF;
    spec.rgba[1] = 0xC8;
    spec.rgba[2] = 0xC8;
    spec.rgba[0] = 0xC8;
    spec.rgba[3] = 0xC8;
    spec.flags = 0x401;
    spec.span = D_80088CD0[idx];
    spec.pos[0] = a[0];
    spec.pos[1] = a[1];
    spec.pos[2] = a[2];
    spec.scale[0] = 1.0f;
    spec.scale[1] = 1.0f;
    spec.scale[2] = 1.0f;
    spec.dir[1] = 0.0f;
    spec.dir[0] = dir[2] * inv;
    spec.dir[2] = dir[0] * inv;
    rec = (u8 *) effect3d_spawn_default((s32) &spec, 9, 0, 0, 7, 0, 0x2C, group, arg3);
    if (rec != NULL) {
        *(f32 *) (rec + 0x110) = dir[0];
        *(f32 *) (rec + 0x114) = dir[1];
        *(f32 *) (rec + 0x118) = dir[2];
        *(f32 *) (rec + 0x11C) = D_80088CD4[idx];
        *(f32 *) (rec + 0x120) = D_80088CD8[idx];
        *(f32 *) (rec + 0x12C) = D_80088CE4[idx];
        *(f32 *) (rec + 0x124) = 1.0f;
        *(f32 *) (rec + 0x128) = 1.0f;
        *(f32 *) (rec + 0x130) = D_80088CE8[idx];
        *(f32 *) (rec + 0x134) = D_80088CDC[idx];
        rec[0x138] = D_80088CE0[idx];
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_108C00/func_150DB3F0.s")
#endif

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
#ifdef NON_MATCHING
// anim_event_effect_spawn: animation event 0x32 (func_150268BC): when all five pointers are set and span != 0, spawns
// a type 0x17 effect record (effect3d_spawn_default with flags 0x401, 0x243A, colour 0xC8 x4, lifetime span, group arg6 and
// arg7) and links it to its sources: +0x110 = a0, +0x114 = a1, +0x118 = a2, +0x11C = a4, +0x120 = a3 (P195).
typedef struct {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 pad1;
    /* 0x02 */ s16 flags;
    /* 0x04 */ s16 span;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ s32 w8;
    /* 0x0C */ s32 wC;
    /* 0x10 */ u8 rgba[4];
    /* 0x14 */ u8 pad14[0x40 - 0x14];
    /* 0x40 */ s32 w40;
    /* 0x44 */ u8 b44;
    /* 0x45 */ u8 b45;
    /* 0x46 */ u8 pad46[2];
} EffSpawn150DBA98;

void func_150DBA98(u8 *a0, u8 *a1, u8 *a2, u8 *a3, u8 *a4, s16 span, u8 arg6, s32 arg7) {
    EffSpawn150DBA98 spec;
    u8 *rec;

    if (a0 == NULL || a1 == NULL || a2 == NULL || a3 == NULL || a4 == NULL || span == 0) {
        return;
    }
    spec.type = 0x17;
    spec.wC = 0x243A;
    spec.w40 = 0x401;
    spec.b44 = 0xFF;
    spec.w8 = 0;
    spec.span = span;
    spec.b45 = 0xFF;
    spec.rgba[0] = 0xC8;
    spec.rgba[1] = 0xC8;
    spec.rgba[2] = 0xC8;
    spec.rgba[3] = 0xC8;
    spec.flags = 0x401;
    rec = (u8 *) effect3d_spawn_default((s32) &spec, 0, 0xA, 0, 8, 0, 0x14, arg6, arg7);
    if (rec != NULL) {
        *(u8 **) (rec + 0x110) = a0;
        *(u8 **) (rec + 0x114) = a1;
        *(u8 **) (rec + 0x118) = a2;
        *(u8 **) (rec + 0x11C) = a4;
        *(u8 **) (rec + 0x120) = a3;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_108C00/func_150DBA98.s")
#endif

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
        sp.u44 = angle_byte_cos(temp_f10 & 0xFF);
        temp_v1 = arg0 + 0x110;
        temp_f2 = *(*(f32 **)((u8 *)temp_v1 + 8));
        temp_f12 = temp_f2 * sp.u44;
        temp_f14 = -temp_f2 * angle_byte_cos((temp_f10 - 0x40) & 0xFF);
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