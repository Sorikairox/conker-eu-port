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
