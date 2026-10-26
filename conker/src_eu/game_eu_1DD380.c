#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 collision_floor_probe(f32 *, s32, f32, s32);
s32 hitinfo_from_obj_floor(s32, struct127 *);
extern u8 D_800AA4D0[];
extern u8 D_800AA4DC[];
/* was func_151AFB70 */
s32 obj_bone_ground_probe(f32 *arg0, u8 *arg1, s32 arg2, u8 arg3) {
    f32 sp2C[3];

    if ((arg3 != 1) && (arg3 != 2)) {
        return 0;
    }
    mtx_transform_point_or_origin((arg3 == 1) ? D_800AA4DC : D_800AA4D0, arg0, (arg3 == 1) ? *(u8 **)(arg1 + 0x1D4) + 0x800 : *(u8 **)(arg1 + 0x1D4) + 0x640);
    if (arg2 == 0) {
        return 1;
    }
    sp2C[0] = arg0[0];
    sp2C[1] = arg0[1] + 100.0f;
    sp2C[2] = arg0[2];
    hitinfo_from_obj_floor(arg2, (struct127 *) arg1);
    return collision_floor_probe(sp2C, 0, arg0[1] - 500.0f, arg2);
}

/* was func_151AFC70 */
s32 obj_handler_stub(s32 arg0, s32 arg1) {
    return 0xC;
}

#ifdef NON_MATCHING
/* P292 */
void ground_colour_by_depth(f32, f32 *, f32 *, f32 *);
void spawn_circle_random_emit(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5, s16 arg6, u8 arg7, s32 arg8, f32 arg9, s32 argA, u8 argB);
void *memcpy(void *, const void *, s32);

/* rodata D_800AA4E8 / D_800AA4EC (bit-exact copies: the NM link drops this file's .late_rodata) */
static const f32 sSplashScaleA[1] = { 0.001f };     /* 0x3A83126F */
static const f32 sSplashScaleB[1] = { 0.001f };     /* 0x3A83126F */

/* IDO's f32 -> u32 conversion: <= -1, >= 2^32 and NaN give 0xFFFFFFFF (undefined in C, wasm traps) */
#define SPLASH_F2U(f) ((!((f) > -1.0f) || (f) >= 4294967296.0f) ? 0xFFFFFFFFU : (u32) (f))

// object_ground_splash: handler of D_8008A0B4 entry 12 (EU 0x8008A4B4, called by obj_interaction_update with (obj, arg1, 0)):
// when obj has a model (+0x1D4) and obj_bone_ground_probe finds its effect point (pos) and the ground under it for mode arg1
// (1 / 2), spawns a 0x50-type splash particle there (effect3d_spawn_oriented_simple: 4 vertices tinted by ground_colour_by_depth's colour of
// pos z in level 0x14, white elsewhere; size 0.091..0.112, height from obj's u16 +0x7A >> 8, +10 for mode 1, -10 otherwise;
// its +0x128 gets a lifetime / scale pair) and a dust ring (spawn_circle_random_emit: radius 29..46, 5..15 frames). arg2 unused.
/* was func_151AFC84 */
void object_ground_splash(u8 *obj, s32 arg1, s32 arg2) {
    struct {
        s16 r, g, b, a, z;
    } verts[4];
    struct {
        u8 type;            /* 0x00 */
        s16 u02;            /* 0x02 */
        s16 life;           /* 0x04 */
        s32 u08;            /* 0x08 */
        s32 u0C;            /* 0x0C */
        u8 col[4];          /* 0x10 */
        f32 size[2];        /* 0x14 */
        f32 pos[3];         /* 0x1C */
        f32 u28[3];         /* 0x28 */
        f32 u34;            /* 0x34 */
        f32 u38[2];         /* 0x38 */
        s32 flags;          /* 0x40 */
        u8 u44[4];          /* 0x44 */
    } part;
    struct {
        s16 life;           /* +0x128 */
        f32 scale;          /* +0x12C */
    } tail;
    f32 r, g, b;
    s32 ground[9];          /* obj_bone_ground_probe's ground record: [0] = height (f32), +4 passed on */
    f32 pos[3];
    s32 cr, cg, cb;
    s32 i;
    s32 height;
    s16 ringLife;
    u8 *p;

    if (obj == NULL || *(void **) (obj + 0x1D4) == NULL) {
        return;
    }
    if (obj_bone_ground_probe(pos, obj, (s32) ground, (u8) arg1) == 0) {
        return;
    }
    if (D_800BE9F0 == 0x14) {
        ground_colour_by_depth(pos[2], &r, &g, &b);
        cr = SPLASH_F2U(r) & 0xFF;
        cg = SPLASH_F2U(g) & 0xFF;
        cb = SPLASH_F2U(b) & 0xFF;
    } else {
        cr = 0xFF;
        cg = 0xFF;
        cb = 0xFF;
    }
    for (i = 0; i < 4; i++) {
        verts[i].r = cr;
        verts[i].g = cg;
        verts[i].b = cb;
        verts[i].a = 0xB4;
        verts[i].z = 0;
    }
    part.type = 0x50;
    part.u02 = 0x2502;
    part.life = random_int() % 61U + 0x58;
    part.u08 = 0;
    part.u0C = 0;
    part.col[0] = 0xFF;
    part.col[1] = 0xFF;
    part.col[2] = 0xFF;
    part.col[3] = 0xFF;
    part.size[0] = part.size[1] = (random_float() * 21.0f + 91.0f) * sSplashScaleA[0];
    part.pos[0] = pos[0];
    part.pos[1] = *(f32 *) &ground[0];
    part.pos[2] = pos[2];
    part.u28[0] = 0.0f;
    part.u28[1] = 0.0f;
    part.u28[2] = 0.0f;
    part.u34 = 1.0f;
    part.u38[0] = 1.0f;
    part.u38[1] = 1.0f;
    part.flags = 0x401C0001;
    part.u44[0] = random_int() % 41U + 0x50;
    part.u44[1] = 0xFF;
    tail.life = part.life - random_int() % 6U - 8;
    tail.scale = (random_float() * 40.0f + 51.0f) * part.size[0] * sSplashScaleB[0];
    part.u44[2] = 0;
    part.u44[3] = 6;
    height = (*(u16 *) (obj + 0x7A) >> 8) - ((arg1 == 1) ? -10 : 10);
    p = (u8 *) effect3d_spawn_oriented_simple((s32) &part, (s32) verts, 0, 0x16, 0, 0, height, 500.0f, 500.0f, 0, (s32) &ground[1], 1, 8,
                             0xFF, 0);
    if (p != NULL) {
        memcpy(p + 0x128, &tail, 8);
    }
    ringLife = random_int() % 11U + 5;
    spawn_circle_random_emit(pos[0], pos[1], pos[2], random_float() * 17.0f + 29.0f, 0, 0xFF, ringLife, 0x10, 0, 0.0f, 0, 0xFF);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DD380/object_ground_splash.s")
#endif

/* was func_151B0184 */
s32 splash_alpha_fade_by_life8(u8 *arg0) {
    s16 temp_v0 = *(s16 *)(arg0 + 0x1C);
    s32 temp_v1;

    if (temp_v0 < 32) {
        temp_v1 = temp_v0 << 3;
        if (temp_v1 < arg0[0x28]) {
            arg0[0x28] = temp_v1;
        }
    }
    return 1;
}

/* was func_eu_151B01B8 */
s32 splash_sprite_update(u8 *arg0)
{
  f32 temp_f0;
  s32 temp_v1;
  u8 *p;
  p = arg0 + 0x128;
  if ((*((s32 *) (((u8 *) arg0) + 0x58))) & 1)
  {
    temp_v1 = *((s16 *) (((u8 *) arg0) + 0x1C));
    if (temp_v1 < 0x20)
    {
      if ((temp_v1 * 8) < ((s32) (*((u8 *) (((u8 *) arg0) + 0x5C)))))
      {
        *((u8 *) (((u8 *) arg0) + 0x5C)) = (u8) (temp_v1 * 8);
      }
    }
    temp_v1 = *((s16 *) (((u8 *) arg0) + 0x1C));
    temp_f0 = temp_f0;
    if ((*((s16 *) p)) < temp_v1)
    {
      temp_f0 = (*((f32 *) (p + 4))) * D_800BE9A4;
      *((f32 *) (((u8 *) arg0) + 0x2C)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x2C))) + temp_f0);
      *((f32 *) (((u8 *) arg0) + 0x30)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x30))) + temp_f0);
    }
  }
  return 1;
}

void vec3_from_angles_byte(s16, s16, f32, void *);
s32 particle_spawn_basic(void *, s32, s32, u8, s32);
/* was func_151B0238 */
s32 spawn_emit_mud_particle(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    struct {
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
        s32 u44;
        s8 u48;
        s8 u49;
        s8 u4A;
        u8 u4B;
        u8 u4C;
        u8 u4D;
        s8 u4E;
        s8 u4F;
        u8 u50;
        s8 u51;
        s16 u52;
        s16 u54;
        s16 u56;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        u8 pad70[0xC];
        s32 u7C[3];
        f32 u88;
        s32 u8C;
        u8 pad90[4];
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        u8 pad98[0x10];
    } sp;
    s32 obj;
    f32 scale;

    sp.u51 = 0x29;
    sp.u3C = 0xE03;
    sp.u34 = 0x200005;
    sp.u38 = 0;
    sp.u3E = (random_int() & 0xF) + 0x19;
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u4C = 0xB0;
    sp.u4D = 0xA0;
    sp.u4E = 0x2A;
    sp.u48 = 0x40;
    sp.u49 = 0xB;
    sp.u4A = 0x6A;
    sp.u4B = 0xFF;
    sp.u4F = (random_int() % 156U) + 0x64;
    sp.u50 = 0xFF;
    sp.u94 = 3;
    sp.u95 = 3;
    sp.u5C = sp.u60 = (random_float() * 202.0f) + 101.0f;
    sp.u64 = arg2;
    sp.u68 = arg3;
    sp.u6C = arg4;
    vec3_from_angles_byte(arg8, (s16) ((random_int() % 21U) - 0x14), ((random_float() * 301.0f) + 500.0f) * 0.01f, sp.u7C);
    sp.u8C = 0xE05;
    sp.u88 = 0.0f;
    if (random_int() & 1) {
        sp.u8C |= 0x40;
    }
    if (random_int() & 1) {
        sp.u8C |= 0x80;
    }
    sp.u96 = 6;
    sp.u97 = -1;
    sp.u52 = 0xF;
    sp.u54 = 0x11;
    sp.u56 = 0x19;
    sp.u58 = 1.04f;
    scale = 0.94900006f;
    obj = particle_spawn_basic(&sp, 1, 4, argE, 1);
    if (obj != 0) {
        memcpy(obj + 0xA8, &scale, 4);
    }
    return 1;
}

/* was func_151B0454 */
s32 particle_damp_velocity(u8 *arg0, s32 arg1) {
    s32 i;
    f32 *p = (f32 *)(arg0 + 0xA8);
    for (i = D_800BE9E4; i != 0; i--) {
        *(f32 *)(arg0 + 0x58) *= *p;
        *(f32 *)(arg0 + 0x60) *= *p;
    }
    return 1;
}
