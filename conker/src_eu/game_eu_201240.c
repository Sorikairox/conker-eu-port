#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* P203 */
/* P203: the 0x12-byte surface record a ray hit leaves (copied from the caller's hit when it has one) */
typedef struct {
    s16 v[9];
} ImpactSurface;
/* P203: spark burst spec for func_151530A8 (0x74 bytes; bytes 0x59..0x5B and 0x6B are never set) */
typedef struct {
    s32 count;        /* 0x00 5 >> D_800DCE50 */
    s32 count2;       /* 0x04 4 >> D_800DCE50 */
    f32 pos[3];       /* 0x08 */
    f32 speed;        /* 0x14 8.25 */
    f32 spread;       /* 0x18 5.86 */
    f32 f1C, f20;     /* 0x1C, 0x20 0 */
    f32 f24, f28;     /* 0x24 7, 0x28 16 */
    s16 h2C, h2E;     /* 0x2C 0, 0x2E 0xFF */
    s16 h30, h32;     /* 0x30 -61, 0x32 80 */
    s32 w34, w38;     /* 0x34 3, 0x38 1 */
    s16 h3C, h3E, h40; /* 0x3C 12, 0x3E 10, 0x40 1 */
    u8 b42, b43, b44; /* 0x42 4, 0x43 2, 0x44 3 */
    u8 rgba0[4];      /* 0x45 white */
    u8 rgba1[4];      /* 0x49 0 */
    u8 rgba2[4];      /* 0x4D white */
    u8 rgba3[4];      /* 0x51 0 */
    u8 b55, b56, b57, b58; /* 0x55 0xFF, 0 , 1, 0x24 */
    u8 pad59[3];
    s32 w5C, w60;     /* 0x5C 0x200005, 0x60 0x60600 */
    s16 h64, h66, h68; /* 0x64 10, 0x66 25, 0x68 1 */
    u8 b6A, pad6B;    /* 0x6A 0 */
    f32 f6C;          /* 0x6C 1 */
    u8 b70, b71, b72, b73; /* 0x70 0xFF, 0, 0xFF, 0xFF */
} ImpactSparks;
/* P203: particle spec for func_15132FBC (0x76 bytes used; 0x59..0x5B, 0x69, 0x6B, 0x71 never set) */
typedef struct {
    f32 scale[4];     /* 0x00 1, 1, 0.65, 0.65 */
    f32 rot[3];       /* 0x10 / 0x14 from the direction (func_15145974), 0x18 0 */
    f32 one[3];       /* 0x1C 1, 1, 1 */
    f32 pos[3];       /* 0x28 */
    f32 vel[3];       /* 0x34 */
    f32 spin[4];      /* 0x40 */
    s32 tex;          /* 0x50 0x39E8 / 0x3980 */
    s16 life;         /* 0x54 */
    s16 kind;         /* 0x56 the spark type of the impact kind */
    u8 b58, pad59[3]; /* 0x58 0 */
    s32 w5C;          /* 0x5C 0 */
    u8 b60, b61;      /* 0x60 0xFF, 0x61 8 / 12 */
    u8 b62[6];        /* 0x62 0 */
    u8 b68, pad69;    /* 0x68 2 */
    u8 b6A, pad6B;    /* 0x6A 0 */
    s32 w6C;          /* 0x6C 0 */
    u8 b70, pad71;    /* 0x70 0 */
    s16 h72, h74;     /* 0x72 12, 0x74 21 */
} ImpactParticle;
/* P203: the trail block copied to the particle +0x170 (0x10 bytes, 0x02..0x03 never set) */
typedef struct {
    s16 life;
    s16 pad;
    f32 f4, f8, fC;
} ImpactTrail;
s32 func_150ACEA0(f32, f32, f32, f32, f32, f32, f32 *, ImpactSurface *, f32 *, f32 *, f32 *, f32 *, s32 *, s32, f32);
u8 func_15145C90(s32 arg0);
void func_15145974(f32 *dir, f32 *yaw, f32 *pitch);
s32 func_15145128(f32 *dir, f32 *out, f32 *a, f32 *b);
s32 func_151530A8(ImpactSparks *spec, u8 arg1, s32 arg2);
u8 *func_15132FBC(ImpactParticle *spec, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
void *func_15102EA0(f32 size, u8 arg1, ImpactSurface *surf, f32 *pos, s16 life, u8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9);
s32 func_1000EC24(s32, s32, s32, s32, s32, s32, s32); /* a function (init_EB00.c), passed by address */
void *memcpy(void *, const void *, s32);
extern u8 D_800DCE50;  /* spark count shift (0 = full) */
extern f32 D_800DCE54; /* spark chance */

// impact_effect_spawn: P203: effects where a shot or blow hits `pos` coming along `dir`. The surface: the caller's
// hit record (`hit`, 0x12 bytes) at pos, else a ray from pos - dir along dir (func_150ACEA0) gives the hit point,
// surface and material id (-1 when nothing is hit). kind (0..5, others do nothing) picks the particle type (0x34,
// 0x4D, 0x57, 0x58, 0x0C, none). `big` = a random odd number or a surface without material (func_15145C90 == 0).
// Kind 1 (bullet) plays a ricochet: a random 0x459..0x45B one-shot (func_1000FA64, only in one-player mode, then
// the follow-up sound 0x106) when big, else 0xB0, through func_10010E78 at the position. With chance D_800DCE54 a
// spark burst (func_151530A8, 5 >> D_800DCE50 sparks). In one- and two-player modes the particle of the kind: when
// big a fast debris piece thrown back along the surface normal (func_15145128) with random spin, else a slow puff
// with a trail block (+0x170) along the direction's angles. A material surface that was hit also gets a decal
// (func_15102EA0, size 15..35, life 300). arg4 / arg5 are passed to every spawner (view / owner).
// Returns 0: the asm leaves the last callee's v0, which no caller reads (s32 for game_eu_981C0's prototype).
s32 func_151D3A30(f32 *pos, f32 *dir, ImpactSurface *hit, s32 kind, s32 arg4, s32 arg5) {
    f32 hit_pos[3];
    ImpactSurface surf;
    s32 surf_id;
    f32 ray_t, ray_u;
    ImpactSparks sparks;
    ImpactParticle part;
    ImpactTrail trail;
    f32 normal[3];
    f32 na, nb;
    f32 speed;
    s32 type, big, snd;
    u8 found, material;
    u8 *p;

    kind &= 0xFF;
    if (kind >= 6) {
        return 0;
    }
    switch (kind) {
        case 4:
            type = 0xC;
            break;
        case 2:
            type = 0x57;
            break;
        case 3:
            type = 0x58;
            break;
        case 0:
            type = 0x34;
            break;
        case 1:
            type = 0x4D;
            break;
        default:
            type = 0;
            break;
    }
    if (hit == NULL) {
        if (func_150ACEA0(pos[0] - dir[0], pos[1] - dir[1], pos[2] - dir[2], dir[0], dir[1], dir[2], &ray_u, &surf,
                          &hit_pos[0], &hit_pos[1], &hit_pos[2], &ray_t, &surf_id, 0, 0.0f) != 0) {
            found = TRUE;
        } else {
            found = FALSE;
            surf_id = -1;
        }
    } else {
        surf_id = -1;
        hit_pos[0] = pos[0];
        hit_pos[1] = pos[1];
        hit_pos[2] = pos[2];
        surf = *hit;
        found = TRUE;
    }
    material = func_15145C90(surf_id);
    if ((func_150ADA20() & 1) || material == 0) {
        big = TRUE;
    } else {
        big = FALSE;
    }
    if (kind == 1) {
        if (big) {
            snd = (u32) func_150ADA20() % 3 + 0x459;
            if (D_80082FA0 == 0) {
                func_1000FA64(snd, (s32) pos[0], (s32) pos[1], (s32) pos[2], 0x4000, 0x4B0, 0x320, (s32) func_1000EC24,
                              (void *) 0x28, 0, 0, 0);
                snd = 0x106;
            }
        } else {
            snd = 0xB0;
        }
        func_10010E78(0, snd, 0x6590, (u32) func_150ADA20() % 500 - 250, 0, 0, (s32) pos[0], (s32) pos[1],
                      (s32) pos[2], 500, 800);
    }
    if (func_150ADA68() < D_800DCE54) {
        sparks.count = 5 >> D_800DCE50;
        sparks.count2 = 4 >> D_800DCE50;
        sparks.pos[0] = pos[0];
        sparks.pos[1] = pos[1];
        sparks.pos[2] = pos[2];
        sparks.speed = 8.25f;
        sparks.spread = 5.85999966f; /* 0x40BB851E (IDO reads 5.86f as 0x40BB851F) */
        sparks.f1C = 0.0f;
        sparks.f20 = 0.0f;
        sparks.f24 = 7.0f;
        sparks.f28 = 16.0f;
        sparks.h2C = 0;
        sparks.h2E = 0xFF;
        sparks.h30 = -0x3D;
        sparks.h32 = 0x50;
        sparks.w34 = 3;
        sparks.w38 = 1;
        sparks.h3C = 0xC;
        sparks.h3E = 0xA;
        sparks.h40 = 1;
        sparks.b42 = 4;
        sparks.b43 = 2;
        sparks.b44 = 3;
        sparks.rgba0[0] = sparks.rgba0[1] = sparks.rgba0[2] = sparks.rgba0[3] = 0xFF;
        sparks.rgba1[0] = sparks.rgba1[1] = sparks.rgba1[2] = sparks.rgba1[3] = 0;
        sparks.rgba2[0] = sparks.rgba2[1] = sparks.rgba2[2] = sparks.rgba2[3] = 0xFF;
        sparks.rgba3[0] = sparks.rgba3[1] = sparks.rgba3[2] = sparks.rgba3[3] = 0;
        sparks.b55 = 0xFF;
        sparks.b56 = 0;
        sparks.b57 = 1;
        sparks.b58 = 0x24;
        sparks.w5C = 0x200005;
        sparks.w60 = 0x60600;
        sparks.h64 = 0xA;
        sparks.h66 = 0x19;
        sparks.h68 = 1;
        sparks.b6A = 0;
        sparks.f6C = 1.0f;
        sparks.b70 = 0xFF;
        sparks.b71 = 0;
        sparks.b72 = 0xFF;
        sparks.b73 = 0xFF;
        func_151530A8(&sparks, arg4, arg5);
    }
    if (type != 0 && D_80082FA0 < 2) {
        part.pos[0] = pos[0];
        part.pos[1] = pos[1];
        part.pos[2] = pos[2];
        func_15145974(dir, &part.rot[1], &part.rot[0]);
        part.b58 = 0;
        part.w5C = 0;
        part.b60 = 0xFF;
        part.b62[0] = part.b62[1] = part.b62[2] = part.b62[3] = part.b62[4] = part.b62[5] = 0;
        part.b68 = 2;
        part.b6A = 0;
        part.w6C = 0;
        part.b70 = 0;
        part.h72 = 0xC;
        part.h74 = 0x15;
        part.scale[0] = 1.0f;
        part.scale[1] = 1.0f;
        part.one[0] = 1.0f;
        part.one[1] = 1.0f;
        part.one[2] = 1.0f;
        part.scale[3] = 0.65f;
        part.scale[2] = 0.65f;
        part.rot[2] = 0.0f;
        part.kind = type;
        if (big) {
            if (func_15145128(dir, normal, &na, &nb) != 0) {
                speed = func_150ADA68() * 12.0f + 3.0f;
                part.life = (u32) func_150ADA20() % 11 + 0x1E;
                part.vel[0] = -normal[0] * speed;
                part.vel[1] = -normal[1] * speed;
                part.vel[2] = -normal[2] * speed;
                part.spin[0] = (func_150ADA68() * 203280.0f + -101640.0f) * 0.0001f;
                part.spin[1] = (func_150ADA68() * 203280.0f + -101640.0f) * 0.0001f;
                part.spin[2] = (func_150ADA68() * 203280.0f + -101640.0f) * 0.0001f;
                part.spin[3] = (func_150ADA68() * 449.0f + -744.0f) * 0.001f;
                part.tex = 0x39E8;
                part.b61 = 8;
                func_15132FBC(&part, 3, 0xFF, 0, arg4, arg5);
            }
        } else {
            trail.life = (func_150ADA20() & 0xF) + 0x14;
            trail.f4 = 0.0f;
            trail.f8 = (func_150ADA68() * 10000.0f + 10000.0f) * 0.0001f;
            trail.fC = (func_150ADA68() * 21000.0f + 4000.0f) * 0.0001f;
            part.life = 0x12C;
            part.vel[0] = 0.0f;
            part.vel[1] = 0.0f;
            part.vel[2] = 0.0f;
            part.spin[0] = part.rot[0];
            part.spin[1] = part.rot[1];
            part.spin[2] = part.rot[2];
            part.tex = 0x3980;
            part.b61 = 0xC;
            part.spin[3] = 0.0f;
            p = func_15132FBC(&part, 3, 0xFF, 0x10, arg4, arg5);
            if (p != NULL) {
                memcpy(p + 0x170, &trail, sizeof(trail));
            }
        }
    }
    if (found && material != 0) {
        func_15102EA0(func_150ADA68() * 20.0f + 15.0f, 0xFF, &surf, hit_pos, 0x12C, 1, 1, 0, arg4, arg5);
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D3A30.s")
#endif

s32 func_151D4300(u8 *arg0) {
    u8 *v;

    v = arg0 + 0x170;
    if (*(s16 *)(arg0 + 0x170) > 0) {
        *(f32 *)(v + 4) = (*(f32 *)(v + 8) * D_800BE9A4) + *(f32 *)(v + 4);
        *(f32 *)(v + 4) = func_15144B68(*(f32 *)(v + 4));
        *(f32 *)(arg0 + 0x24) = *(f32 *)(arg0 + 0x54) + (*(f32 *)(v + 0xC) * sinf(*(f32 *)(v + 4)));
        *(s16 *)(v + 0) = *(s16 *)(v + 0) - D_800BE9E4;
    } else {
        *(vertex *)(arg0 + 0x20) = *(vertex *)(arg0 + 0x50);
    }
    return 1;
}

void func_151D43B4(s32 arg0, s32 arg1, void *arg2, u8 arg3, f32 arg4) {
    u8 *temp_v0;
    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x1D4));
    if (temp_v0 != 0) {
        func_15143134(arg2, (u8 *) arg1, (u8 *)((s32)temp_v0 + (arg3 << 6)));
        return;
    }
    (*(f32 *)((u8 *)arg1 + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0x14));
    (*(f32 *)((u8 *)arg1 + 4)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x18)) + arg4);
    (*(f32 *)((u8 *)arg1 + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 0x1C));
}

#ifdef NON_MATCHING
/* P159 */
// object_sound_between: plays sound `sound` (func_1505D1C4) at the midpoint of a and b for object obj (its index
// in D_800CC2D0); the facing is obj's u16 at +0x76, minus the s16 at +0x12 of its parent (+0x31C) when it has one.
void func_151D441C(struct127 *obj, f32 *a, f32 *b, s32 sound) {
    u8 *parent;
    u16 facing;

    parent = *(u8 **)((u8 *)obj + 0x31C);
    if (parent != NULL) {
        facing = *(u16 *)((u8 *)obj + 0x76) - *(s16 *)(parent + 0x12);
    } else {
        facing = *(u16 *)((u8 *)obj + 0x76);
    }
    func_1505D1C4((a[0] + b[0]) * 0.5f, (a[1] + b[1]) * 0.5f, (a[2] + b[2]) * 0.5f, sound, obj - D_800CC2D0,
                  facing, 0, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D441C.s")
#endif

void func_151D44C4(u8 *arg0, u8 arg1, s32 arg2) {
    s8 sp48[8];
    s32 sp3C[3];

    sp48[0] = 3;
    sp48[1] = -1;
    *(s16 *)(sp48 + 2) = (func_150ADA20() % 3U) + 4;
    sp48[4] = 0;
    sp3C[0] = *(f32 *)(arg0 + 0);
    sp3C[1] = *(f32 *)(arg0 + 4);
    sp3C[2] = *(f32 *)(arg0 + 8);
    func_151602C0(sp48, sp3C, (func_150ADA20() % 13U) + 0x14, 0xFF, 0xE8, 0xAB, 0xFFU, 0U, 0, arg1, arg2);
}

void func_151D45A4(u8 *arg0, u8 arg1, s32 arg2) {
    s8 sp48[8];
    s32 sp3C[3];

    sp48[0] = 3;
    sp48[1] = -1;
    *(s16 *)(sp48 + 2) = (func_150ADA20() % 11U) + 0x14;
    sp48[4] = 0;
    sp3C[0] = *(f32 *)(arg0 + 0);
    sp3C[1] = *(f32 *)(arg0 + 4);
    sp3C[2] = *(f32 *)(arg0 + 8);
    func_151602C0(sp48, sp3C, (func_150ADA20() % 24U) + 0x22, 0xFF, 0xA1, 0xA2, 0xFFU, 0U, 0, arg1, arg2);
}

#ifdef NON_MATCHING
/* P155 */
void func_1505D1C4(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, u16 arg5, s32 arg6, s32 arg7);
// object_sounds_at: plays the sounds `sound1` and `sound2` (func_1505D1C4) at pos for object obj (its index in
// D_800CC2D0) with `flags` and a source point: with dir, pos - 90 * dir and dir's binary angle - 0x4000 (odd) as
// facing; without, pos raised by half the height of `model` (func_1507C7C0, when given) and facing 0. arg4 is
// unused. Returns 0 (the asm leaves v0 unset; the caller ignores it).
s32 func_151D4684(f32 *pos, f32 *dir, struct127 *obj, struct127 *model, s32 arg4, s32 sound1, s32 sound2, s32 flags) {
    f32 at[3];
    s16 height;
    f32 a;
    u32 angle;
    s32 facing;
    s32 index;

    if (dir != NULL) {
        a = func_150484A0(dir[0], dir[2]) * 10430.378f;
        /* IDO's f32 -> u32 conversion: below 0 gives 0xFFFFFFFF (undefined in C, wasm traps) */
        angle = (a <= -1.0f) ? 0xFFFFFFFF : (u32)a;
        facing = ((angle - 0x4000) | 1) & 0xFFFF;
        at[0] = pos[0] + dir[0] * -90.0f;
        at[1] = pos[1] + dir[1] * -90.0f;
        at[2] = pos[2] + dir[2] * -90.0f;
    } else {
        ((s32 *)at)[0] = ((s32 *)pos)[0];
        ((s32 *)at)[1] = ((s32 *)pos)[1];
        ((s32 *)at)[2] = ((s32 *)pos)[2];
        if (model != NULL) {
            func_1507C7C0(model, &height, NULL, NULL);
            at[1] += height >> 1;
        }
        facing = 0;
    }
    index = obj - D_800CC2D0;
    func_1505D1C4(pos[0], pos[1], pos[2], sound1, index, facing, flags, (s32)at);
    func_1505D1C4(pos[0], pos[1], pos[2], sound2, index, facing, flags, (s32)at);
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D4684.s")
#endif

#ifdef NON_MATCHING
/* P155 */
// object_sound_at: plays sound `sound` (func_1505D1C4) at pos for object obj (its index in D_800CC2D0), with the
// direction of dir (x / z, binary angle - 0x4000, odd) or 0 without dir. arg3 is unused.
void func_151D4898(f32 *pos, f32 *dir, struct127 *obj, s32 arg3, s32 sound) {
    f32 a;
    u32 angle;
    s32 facing;

    facing = 0;
    if (dir != NULL) {
        a = func_150484A0(dir[0], dir[2]) * 10430.378f;
        /* IDO's f32 -> u32 conversion: below 0 gives 0xFFFFFFFF (undefined in C, wasm traps) */
        angle = (a <= -1.0f) ? 0xFFFFFFFF : (u32)a;
        facing = ((angle - 0x4000) | 1) & 0xFFFF;
    }
    func_1505D1C4(pos[0], pos[1], pos[2], sound, obj - D_800CC2D0, facing, 0, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D4898.s")
#endif

typedef struct { f32 x, y, z; } V3;

void func_151D49B8(u8 *arg0, u8 *arg1, s32 arg2, u8 *arg3, f32 arg4, u8 arg5, s32 arg6) {
    struct {
        s32 u38[6];
        u8 pad50[0x4];
        f32 u54[5];
        s32 u68[2];
        f32 u70;
        f32 u74;
        f32 u78;
        s32 u7C;
        u8 pad80[0x8];
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        s32 uA4;
        s16 uA8;
        s16 uAA;
        s8 uAC;
        u8 padAD[0x3];
        s32 uB0;
        u8 uB4;
        s8 uB5;
        s8 uB6;
        s8 uB7;
        s8 uB8;
        s8 uB9;
        s8 uBA;
        s8 uBB;
        s8 uBC;
        u8 padBD[0x1];
        s8 uBE;
        u8 padBF[0x1];
        u8 *uC0;
        u8 uC4;
        u8 padC5[0x1];
        s16 uC6;
        s16 uC8;
        u8 padCA[0x2];
        s32 uCC;
    } sp;

    func_1503F6F4(arg2, &sp.u38[3], &sp.u38[4], &sp.u38[5], &sp.u54[4], &sp.u68[0], &sp.u68[1], &sp.u38[0], &sp.u38[1], &sp.u38[2]);
    sp.u54[4] += 180.0f;
    {
        f32 temp_f0;

        temp_f0 = func_150ADA68();
        sp.u54[0] = 1.0f;
        sp.u54[1] = 1.0f;
        sp.u70 = 1.0f;
        sp.u74 = 1.0f;
        sp.u78 = 1.0f;
        sp.u54[3] = 0.042000003f * arg4;
        sp.u54[2] = sp.u54[3];
        *(V3 *)&sp.u7C = *(V3 *)arg0;
        arg4 = ((temp_f0 * 105.0f) + 199.0f) * 0.001f;
        sp.u88 = (*(f32 *)((u8 *)arg1 + 0)) * arg4;
        sp.u8C = (*(f32 *)((u8 *)arg1 + 4)) * arg4;
        sp.u90 = (*(f32 *)((u8 *)arg1 + 8)) * arg4;
        sp.u94 = ((func_150ADA68() * 6378.0f) + -3189.0f) * 0.001f;
        sp.u98 = 0.0f;
        sp.u9C = ((func_150ADA68() * 6378.0f) + -3189.0f) * 0.001f;
        sp.uA0 = ((func_150ADA68() * 320.0f) + -707.0f) * 0.001f;
        sp.uA4 = 0x29E8;
        sp.uA8 = (func_150ADA20() & 7) + 0x1C;
        sp.uAA = 0x25;
        sp.uAC = 0;
        sp.uB0 = 0;
        sp.uB4 = 0xFF;
        sp.uB5 = 8;
        sp.uB6 = 0;
        sp.uB7 = 0;
        sp.uB8 = 0;
        sp.uB9 = 0;
        sp.uBA = 0;
        sp.uBB = 0;
        sp.uBC = 2;
        sp.uBE = 1;
        sp.uC0 = arg3;
        sp.uC4 = (*(u8 *)((u8 *)arg3 + 0x3B));
        sp.uC6 = 6;
        sp.uC8 = 0x2A;
        func_15132FBC((u8 *)&sp.u54, 3, 0xFF, 0, (s32) arg5, arg6);
    }
}

void func_151D4668(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151494E0(&tmp, 0x3C);
}

#ifdef NON_MATCHING
/* P160 */
void *memcpy(void *, const void *, s32);
extern void (*D_80090010[])(u8 *obj, s32 sound, f32 *point);

typedef struct {
    u8 *obj;     /* 0x00 */
    u8 objId;    /* 0x04: obj[0x3B] */
    s16 sound;   /* 0x06: -1, 0x82 for kind 6 */
    u8 kind;     /* 0x08 */
    f32 unkC;    /* 0x0C */
    u8 flags;    /* 0x10: bit 0 = point valid */
    f32 point[3]; /* 0x14 */
} ObjEffectRec_151D469C; /* 0x20 bytes, copied to the record at +0x28 */

// object_point_effect_spawn: fills a 0x20-byte record (object, kind, the kind's point on the object from the
// D_80090010 handler when the object has bone matrices and obj[0x74] low nibble != 0xF) and spawns event 0x41 /
// kind 0x35 through func_15149130 with it. Returns 0 (callers in game_981E0 declare it implicitly as int).
s32 func_151D469C(u8 *obj, u8 kind, s16 arg2, u8 arg3, s32 arg4) {
    ObjEffectRec_151D469C rec;
    u8 *p;

    rec.obj = obj;
    rec.objId = obj[0x3B];
    rec.sound = -1;
    rec.flags = 0;
    rec.kind = kind;
    rec.unkC = 0.0f;
    if (kind == 6) {
        rec.sound = 0x82;
    }
    if (*(u8 **)(obj + 0x1D4) != NULL && (obj[0x74] & 0xF) != 0xF) {
        D_80090010[kind](obj, rec.sound, rec.point);
        rec.flags |= 1;
    }
    p = (u8 *)func_15149130(arg2, -1, 0x41, -1, 1, 0x35, (struct37 *)0x20, arg3, arg4);
    if (p != NULL) {
        memcpy(p + 0x28, &rec, 0x20);
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D469C.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D4D44.s")

void func_151D51E8(struct102 *arg0, u8 *arg1, u8 arg2)
{
  u8 *p = (u8 *)arg0 + 0x28;
  if (arg2 == 0x3C) {
    if (*(s32 *)p == *(s32 *)arg1 || p[4] == arg1[4]) {
      func_1516972C(arg0);
    }
  } else if (arg2 == 4) {
    if (*(s32 *)p == *(s32 *)arg1 || p[4] == arg1[4]) {
      u8 *q = p + 0x10; // a declaration in the arm = basic-block boundary (unfilled b delay slot, s69)
      *q &= ~1;
    }
  } else {
    func_15149514((s32)arg1, arg2, (s32)p, (s32)(p + 4), (s32)arg0);
  }
}

s32 func_151D52B4(u8 *arg0, s32 arg1) {
    u8 *p = arg0 + 0xA8;

    func_15131D98(arg0, arg0 + 0xAC, p, arg0 + 0xAA);
    func_15131EC8(arg0 + 0x58, *(s32 *)(p + 0xC));
    return 1;
}

#ifdef NON_MATCHING
/* P160: func_151D469C takes the object as a pointer */
// object_bone_point_effects: spawns the point effects of bone points 0 and 1 of obj (func_151D469C kinds 0, 1)
void func_151D5308(s32 arg0) {
    func_151D469C((u8 *)arg0, 0, 0x50, 0xFF, 1);
    func_151D469C((u8 *)arg0, 1, 0x50, 0xFF, 1);
}
#else
void func_151D5308(s32 arg0) {
    func_151D469C(arg0, 0, 0x50, 0xFF, 1);
    func_151D469C(arg0, 1, 0x50, 0xFF, 1);
}
#endif

#ifdef NON_MATCHING
/* P179 */
void func_151C2600(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, f32 arg4);
void func_15137610(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, s32 arg4, s32 arg5);
void func_1507DE4C(struct127 *arg0);
void func_15138C80(struct127 *arg0, s32 arg1, s32 arg2);
s32 func_1505D024(struct127 *, s32, u16, s32);

// object_take_hit: P179: a hit on `obj` by `attacker` (or NULL) at `pos` / `pos2`, direction `dir`, hit record `rec`
/* (or NULL). Body kinds that react with a spark (the list below) get func_151C2600 (attacker, pos, dir, 9, rec +4
 * or 0). A kind-0xA / type-3 hit record (rec +0x58 / +0x59) wears down the shield count obj +0x1CA: at 3 or more it
 * loses one, else it is cleared, func_1507DE4C / func_15138C80 (obj, 0xFF, 1) run and the message flags become
 * 0x100020 (else `flags` | 0x60000). Then func_15137610 (obj, pos, pos2, dir, arg7, arg8); and only if the count
 * was non-zero on entry, the message func_1505D024(obj, flags | 0x80000, (dir angle - 0x4000) | 1, attacker index
 * or -1). The angle is func_150484A0(dir x, dir z) x 65536 / 2pi converted as IDO's float -> unsigned (negative ->
 * 0xFFFF). */
void func_151D535C(u8 *obj, u8 *attacker, u8 *pos, f32 *pos2, u8 *rec, s32 flags, f32 *dir, u8 arg7, s32 arg8) {
    u8 count;
    s32 untouched;
    s32 w;
    u16 angle;

    switch (obj[4]) {
        case 0x09: case 0x0F: case 0x10: case 0x12: case 0x17: case 0x1B: case 0x1E: case 0x28: case 0x29:
        case 0x2A: case 0x2B: case 0x2C: case 0x2E: case 0x38: case 0x41: case 0x42: case 0x4B: case 0x46:
        case 0x47: case 0x49: case 0x4A: case 0x4C: case 0x4D: case 0x4E: case 0x4F: case 0x52: case 0x5D:
        case 0x60: case 0x61: case 0x66: case 0x67: case 0x70: case 0x73: case 0x77: case 0x7B: case 0x89:
        case 0x8C: case 0x8E: case 0x8F: case 0x91: case 0x9E: case 0xA6: case 0xAB: case 0xAC: case 0xB2:
        case 0xB4: case 0x5B:
            func_151C2600(attacker, pos, (u8 *) dir, 9, (rec != NULL) ? *(f32 *)(rec + 4) : 0.0f);
            break;
    }
    count = obj[0x1CA];
    untouched = (count == 0) ? 1 : 0;
    flags |= 0x60000;
    if (rec != NULL && rec[0x59] == 3 && rec[0x58] == 0xA) {
        if (count >= 3) {
            obj[0x1CA] = count - 1;
        } else {
            obj[0x1CA] = 0;
            func_1507DE4C((struct127 *) obj);
            func_15138C80((struct127 *) obj, 0xFF, 1);
            flags = 0x100020;
        }
    }
    func_15137610(obj, (f32 *) pos, pos2, dir, arg7, arg8);
    if (untouched != 0) {
        return;
    }
    w = (s32) (func_150484A0(dir[0], dir[2]) * 10430.378f);
    angle = (w < 0) ? 0xFFFF : w;
    func_1505D024((struct127 *) obj, flags | 0x80000, (u16) ((angle - 0x4000) | 1),
                  (attacker != NULL) ? (struct127 *) attacker - D_800CC2D0 : -1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D535C.s")
#endif

void func_151D56F8(u8 *arg0) {
    if (*(s16 *)(*(u8 **)(arg0 + 0x31C) + 0x24) > 0) {
        *(s16 *)(*(u8 **)(arg0 + 0x31C) + 0x24) -= 1;
    }
    *(s16 *)(*(u8 **)(arg0 + 0x31C) + 0x1AA) += 1;
}

#ifdef NON_MATCHING
void func_151D5724(u8 *arg0, u8 *arg1, struct17 *arg2, struct17 *arg3, struct17 *arg4, u8 *arg5, u8 *arg6, u8 **arg7, u8 **arg8, u8 *arg9) {
    u8 *sp54;
    struct17 sp48;
    struct17 sp3C;
    f32 sp20;
    f32 temp_f0;
    f32 temp_f12;
    f32 var_f14;
    f32 var_f16;
    f32 var_f18;
    u8 *temp_v0;
    u8 *temp_v0_2;

    if ((*(s32 *)((u8 *)arg0 + 0x1D4)) != 0) {
        temp_v0 = (*(u8 **)((u8 *)arg0 + 0x31C));
        if ((temp_v0 != NULL) && (((*(u8 *)((u8 *)temp_v0 + 0x198)) == 2) || ((*(u8 *)((u8 *)temp_v0 + 0x84)) != 0))) {
            sp54 = temp_v0 + 0x13C;
            func_151450B4(arg2, arg3, &sp48);
            func_151450B4(&sp48, arg4, &sp3C);
            if (arg9 != NULL) {
                var_f14 = (*(f32 *)((u8 *)arg9 + 0)) - (*(f32 *)((u8 *)sp54 + 0));
                var_f16 = (*(f32 *)((u8 *)arg9 + 4)) - (*(f32 *)((u8 *)sp54 + 4));
                var_f18 = (*(f32 *)((u8 *)arg9 + 8)) - (*(f32 *)((u8 *)sp54 + 8));
            } else {
                var_f14 = (*(f32 *)((u8 *)arg1 + 0)) - (*(f32 *)((u8 *)sp54 + 0));
                var_f16 = (*(f32 *)((u8 *)arg1 + 4)) - (*(f32 *)((u8 *)sp54 + 4));
                var_f18 = (*(f32 *)((u8 *)arg1 + 8)) - (*(f32 *)((u8 *)sp54 + 8));
            }
            temp_v0_2 = (*(u8 **)((u8 *)arg0 + 0x31C));
            temp_f0 = (*(f32 *)((u8 *)temp_v0_2 + 0x130));
            sp20 = sp3C.unk4;
            temp_f12 = (((*(f32 *)&(sp3C)) * var_f14) + (sp20 * var_f16) + (sp3C.unk8 * var_f18)) / (((*(f32 *)&(sp3C)) * temp_f0) + (sp3C.unk4 * (*(f32 *)((u8 *)temp_v0_2 + 0x134))) + (sp3C.unk8 * (*(f32 *)((u8 *)temp_v0_2 + 0x138))));
            (*(f32 *)((u8 *)arg5 + 0)) = (f32) ((*(f32 *)((u8 *)sp54 + 0)) + (temp_f12 * temp_f0));
            (*(f32 *)((u8 *)arg5 + 4)) = (f32) ((*(f32 *)((u8 *)sp54 + 4)) + (temp_f12 * (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x134))));
            (*(f32 *)((u8 *)arg5 + 8)) = (f32) ((*(f32 *)((u8 *)sp54 + 8)) + (temp_f12 * (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x138))));
            (*(f32 *)((u8 *)arg6 + 0)) = (f32) (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x130));
            (*(f32 *)((u8 *)arg6 + 4)) = (f32) (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x134));
            (*(f32 *)((u8 *)arg6 + 8)) = (f32) (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x138));
            *arg7 = arg5;
            *arg8 = arg6;
            return;
        }
    }
    *arg7 = NULL;
    *arg8 = NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D5724.s")
#endif
#ifdef NON_MATCHING
s32 func_1516547C(s32, s32, s32 *, s32, s32);

void func_151D58E4(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, s32 arg6) {
    struct {
        s32 u3C;
        u8 pad40[0x8];
        f32 u48;
        f32 u4C;
        f32 u50;
    } sp;
    s32 var_s0;

    var_s0 = 0;
    (*(s32 *)((u8 *)(&sp.u3C) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.u3C) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.u3C) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    sp.u48 = arg1;
    sp.u4C = arg2;
    sp.u50 = arg3;
    if ((D_80082FA0 + 1) > 0) {
        do {
            func_1516547C(arg4 & 0xFF, var_s0 & 0xFF, &sp.u3C, arg5 & 0xFF, arg6);
            var_s0 += 1;
        } while (D_80082FA0 >= var_s0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D58E4.s")
#endif
typedef struct {
    struct17 pos;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 unk18;
} Blk_151D5404;
void func_151D5404(struct17 *arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5, s32 arg6, s32 arg7) {
    s32 i;
    Blk_151D5404 sp38;
    structEU_151D8E18 sp30;
    s32 p;

    sp38.pos = *arg0;
    sp38.unkC = arg1;
    sp38.unk10 = arg2;
    sp38.unk14 = arg3;
    sp30.unk0 = 1;
    sp30.unk2 = (func_150ADA20() % (u32) (arg5 + 1)) + arg4;
    sp30.unk4 = 0;
    sp30.unk6 = 0;
    for (i = 0; i < D_80082FA0 + 1; i++) {
        sp30.unk5 = 1 << i;
        sp38.unk18 = i;
        p = func_151D8E18(&sp30, 0x1C, 0xFF, 0);
        if (p != 0) {
            memcpy((u8 *)p + 0x18, &sp38, 0x1C);
        }
    }
}

#ifdef NON_MATCHING
/* P155 */
void func_15150258(u8 *, u8, s32);
// smoke_cloud_spawn: spawns a smoke cloud at pos (f32[3]) through func_15150258 with a fixed emitter block (0x5C
// bytes: 9 puffs over 3 frames, colours 323 / 214 / 203 / 263, sizes 677..895, drift (0.602, -1.732, 1.512) at 45).
// Returns 0 (the asm leaves func_15150258's v0; callers ignore it).
s32 func_151D5AC4(u8 *pos, u8 arg1, s32 arg2) {
    struct {
        s16 u1C;
        s16 u1E;
        s16 u20;
        s16 u22;
        s32 u24;
        s32 u28;
        s32 pos[3];
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        s32 u50;
        s32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        s16 u68;
        s16 u6A;
        s16 u6C;
        s16 u6E;
        s16 u70;
        s16 u72;
        s8 u74;
    } sp;

    sp.u1C = 0;
    sp.u1E = 0xFF;
    sp.u20 = -0x40;
    sp.u22 = 0x4A;
    sp.u24 = 9;
    sp.u28 = 3;
    sp.pos[0] = ((s32 *)pos)[0];
    sp.pos[1] = ((s32 *)pos)[1];
    sp.pos[2] = ((s32 *)pos)[2];
    sp.u38 = 323.0f;
    sp.u3C = 214.0f;
    sp.u40 = 203.0f;
    sp.u44 = 263.0f;
    sp.u48 = 677.0f;
    sp.u4C = 895.0f;
    sp.u50 = 7;
    sp.u54 = 3;
    sp.u58 = 45.0f;
    sp.u5C = 0.60200006f;
    sp.u60 = -1.7320001f;
    sp.u64 = 1.5120001f;
    sp.u68 = 0xF;
    sp.u6A = 0xF;
    sp.u6C = 0x64;
    sp.u6E = 0x64;
    sp.u70 = 0xC;
    sp.u72 = 0x14;
    sp.u74 = 0;
    func_15150258((u8 *)&sp, arg1, arg2);
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D5AC4.s")
#endif

#ifdef NON_MATCHING
s32 func_15154728(u8 *, f32, f32, f32, f32, u8, s32); /* P95: f32 parameter */
#else
void func_15154728(u8 *, f32, s32, f32, f32, u8, s32);
#endif
s32 func_151D5AC4(u8 *, u8, s32);

void func_151D5BF8(u8 *arg0, u8 arg1, s32 arg2) {

    func_151D5AC4(arg0, arg1, arg2);
    func_151D45A4(arg0, arg1, arg2);
#ifdef NON_MATCHING
    func_15154728(arg0, (func_150ADA68() * 4.0f) + 12.0f, 1.6409999f, (func_150ADA20() % 56U) + 0xC8, 0.0f, arg1, arg2); /* P95: float literal (asm passes the bits 0x3FD20C49) */
#else
    func_15154728(arg0, (func_150ADA68() * 4.0f) + 12.0f, 0x3FD20C49, (func_150ADA20() % 56U) + 0xC8, 0.0f, arg1, arg2);
#endif
}

#ifdef NON_MATCHING
/* P155 */
void func_15145EA4(f32 **, f32 **, void *, s32);
void func_151D49B8(u8 *, u8 *, s32, u8 *, f32, u8, s32);
// bone_beam_spawn: unless obj has no bone matrices (+0x1D4) or is hidden (+0x74 low nibble 0xF), transforms the
// points a and b by bone `bone` (func_15145EA4, two points) and starts the effect func_151D49B8 at a's world
// position along b - a (with the bone matrix, obj, scale, alpha and flags).
void func_151D5714(struct127 *obj, f32 *a, f32 *b, u8 bone, f32 scale, u8 alpha, s32 flags) {
    f32 *outs[2];
    f32 *ins[2];
    u8 *mtx;
    f32 dir[3];
    f32 at[3];

    if (obj->unk1D4 == NULL || (((u8 *)obj)[0x74] & 0xF) == 0xF) {
        return;
    }
    outs[0] = at;
    outs[1] = dir;
    mtx = (u8 *)obj->unk1D4 + bone * 64;
    ins[0] = a;
    ins[1] = b;
    func_15145EA4(ins, outs, mtx, 2);
    dir[0] -= at[0];
    dir[1] -= at[1];
    dir[2] -= at[2];
    func_151D49B8((u8 *)at, (u8 *)dir, (s32)mtx, (u8 *)obj, scale, alpha, flags);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D5714.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D5DA8.s")

#ifdef NON_MATCHING
/* P155 */
void func_15145EA4(f32 **, f32 **, void *, s32);
// object_mouth_point: P155: func_15145740 (obj, dir, arg3, arg4, 0.811), then out = `point` transformed by obj's
// bone `bone` (func_15145EA4) or, without bone matrices, obj's position + 49 up + 34 to the side of dir (x / z
// normalised, (0, 1) when both are below 0.0001). Returns 0 (the asm leaves v0 unset; the caller ignores it).
s32 func_151D5FC8(struct127 *obj, f32 *out, f32 *dir, s32 arg3, s32 arg4, f32 *point, u8 bone) {
    f32 *ins[1];
    f32 *outs[1];
    f32 n;
    f32 sx, sz;

    func_15145740(obj, (s32)dir, arg3, arg4, 0.81100005f);
    if (obj->unk1D4 != NULL) {
        outs[0] = out;
        ins[0] = point;
        func_15145EA4(ins, outs, (u8 *)obj->unk1D4 + bone * 64, 1);
        return 0;
    }
    if (fabsf(dir[0]) > 0.0001f || fabsf(dir[2]) > 0.0001f) {
        n = 1.0f / sqrtf(dir[0] * dir[0] + dir[2] * dir[2]);
        sz = dir[2] * n;
        sx = -dir[0] * n;
    } else {
        sz = 1.0f;
        sx = 0.0f;
    }
    out[0] = obj->x_position + 34.0f * sx;
    out[1] = obj->y_position + 49.0f;
    out[2] = obj->z_position + 34.0f * sz;
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D5FC8.s")
#endif

#ifdef NON_MATCHING
/* P159 */
extern s32 (*D_80087030[])(u8 *, s32, s32);
// objects_hit_by_segment: tests the segment start / dir (func_151452C4) against every live object of D_800CC2D0
// (not self, kind byte +4 not 0xFF unless level 0x23, state +5 not 3, flag 0x40 at +0xF8, passing filter
// D_80087030[filter](obj, self, filterArg) unless filter is -1) as a sphere at its position raised by +0xD6 with
// diameter 2 * max(+0xD2, +0xD4). Returns a mask with bit i cleared for each hit object i (all other bits set).
s32 func_151D611C(u8 *start, s32 *dir, u8 *self, s8 filter, s32 filterArg) {
    f32 center[3];
    f32 out0[3];
    f32 out1[3];
    f32 dist0;
    f32 dist1;
    f32 radius;
    s32 mask;
    u8 i;
    u8 *obj;

    mask = -1;
    for (i = 0; i < 25; i++) {
        obj = (u8 *)&D_800CC2D0[i];
        if (*(s32 *)(obj + 0) == 0) {
            continue;
        }
        if (obj[5] == 3) {
            continue;
        }
        if (D_800BE9F0 != 0x23 && obj[4] == 0xFF) {
            continue;
        }
        if (obj == self) {
            continue;
        }
        if ((*(s32 *)(obj + 0xF8) & 0x40) == 0) {
            continue;
        }
        if (filter != -1 && D_80087030[filter](obj, (s32)self, filterArg) == 0) {
            continue;
        }
        if (*(s16 *)(obj + 0xD2) < *(s16 *)(obj + 0xD4)) {
            radius = *(s16 *)(obj + 0xD4);
        } else {
            radius = *(s16 *)(obj + 0xD2);
        }
        center[0] = *(f32 *)(obj + 0x14);
        center[1] = *(f32 *)(obj + 0x18) + (f32)*(s16 *)(obj + 0xD6);
        center[2] = *(f32 *)(obj + 0x1C);
        if (func_151452C4((struct17 *)start, (struct17 *)dir, (struct17 *)center, radius + radius, (s32)out0,
                          (s32)out1, &dist0, &dist1)) {
            mask &= ~(1 << i);
        }
    }
    return mask;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D611C.s")
#endif

s32 allocate_memory(s32, s32, s32, s32);

void func_151D6310(s32 *arg0, s16 arg1, s32 arg2, s32 *arg3, u8 *arg4) {
    u8 dummy;

    if (arg4 == NULL) {
        arg4 = &dummy;
    }
    *arg4 = 0;
    if (arg0[arg1] == 0) {
        arg0[arg1] = allocate_memory(arg2 * 2, 1, 2, 1);
        if (arg0[arg1] == 0) {
            *arg3 = 0;
            return;
        }
        *arg4 = 1;
    }
    *arg3 = arg0[arg1] + (D_800BE9C0 ? 0 : arg2);
}

void func_151D5E30(s32 **arg0)
{
  s32 *new_var;
  u8 i;
  for (i = 0; i < 4; i++)
  {
    s32 *t = arg0[i];
    if (1)
    {
    }
    if (t)
    {
      new_var = arg0[i]; // fakematch: re-load of the element after the test
      func_100043B4(new_var, 3);
 } }
}
