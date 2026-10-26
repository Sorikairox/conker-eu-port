#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* P155 */
s32 mdl_particle_spawn(void *, s32, s32, s32, s32, s32);
typedef struct {
    s16 count;       /* 0x00: pieces */
    u8 pad2[2];
    f32 pos[3];      /* 0x04: centre */
    s16 model;       /* 0x10 */
    u8 pad12[2];
    f32 radius;      /* 0x14: start offset 0..radius along the direction */
    s16 yawMin;      /* 0x18 */
    s16 yawRange;
    s16 pitchMin;    /* 0x1C */
    s16 pitchRange;
    f32 speedMin;    /* 0x20 */
    f32 speedRange;
    f32 upMin;       /* 0x28: mode 0 vertical speed */
    f32 upRange;
    f32 dir[3];      /* 0x30: modes 2 / 3 velocity */
    f32 sizeMin;     /* 0x3C */
    f32 sizeRange;
    f32 spinMin;     /* 0x44 */
    f32 spinRange;
    f32 rotMin;      /* 0x4C */
    f32 rotRange;
    u8 u54;          /* 0x54..0x59: copied to the piece's extra data */
    u8 u55;
    s16 u56;
    s16 u58;
} Spray74B0;
// debris_spray_spawn: spawns spray->count debris pieces (mdl_particle_spawn, 0x10 extra bytes at +0x170) around
// spray->pos, each in a random direction (yaw / pitch byte angles from the ranges, angle_byte_cos = sin) at
// 0..radius; velocity by `mode`: 0 horizontal along the yaw with a separate vertical speed, 1 along the direction,
// 2 spray->dir, 3 spray->dir times a random speed. Random size (x30 for the model scale), spin and two rotation
// speeds. Each piece gets a shadow / trail (point_emitter_spawn kind 4, size x15, 0.358) whose record is kept at its
// extra +4. Returns 0 (the asm leaves v0 unset; callers ignore it).
/* was func_151A74B0 */
s32 debris_spray_spawn(void *arg0, s32 mode, u8 arg2, s32 arg3) {
    Spray74B0 *s = arg0;
    struct {
        u8 *pos[3];
        f32 size;
        f32 u9C;
        s16 life;
        u8 uA2;
        u8 uA3;
    } trail;
    f32 size;
    struct {
        f32 gravity;
        u8 *trail;
        u8 u54;
        u8 u55;
        s16 u56;
        s16 u58;
        u8 padE2[2];
    } extra;
    struct {
        f32 scale;
        f32 uEC;
        f32 uF0;
        f32 uF4;
        f32 rot[3];
        f32 scale3[3];
        f32 pos[3];
        f32 vel[3];
        f32 spin[3];
        f32 u134;
        s32 flags;
        s16 model;
        s16 tex;
        u8 u140;
        u8 pad141[3];
        s32 u144;
        u8 u148;
        u8 u149;
        u8 u14A;
        u8 u14B;
        u8 u14C;
        u8 u14D;
        u8 u14E;
        u8 u14F;
        u8 u150;
        u8 pad151;
        u8 u152;
        u8 pad153;
        s32 u154;
        u8 u158;
        u8 pad159;
        s16 u15A;
        s16 u15C;
    } sp;
    s16 n;
    u8 yaw;
    u8 pitch;
    f32 sy, cy, sp_, cp;
    f32 r, h, v;
    u8 *p;
    u8 *t;

    n = s->count;
    sp.scale3[0] = 1.0f;
    sp.scale3[1] = 1.0f;
    sp.scale3[2] = 1.0f;
    sp.flags = 0x21E9;
    sp.u140 = 0;
    sp.tex = 0x1B;
    sp.rot[0] = 0.0f;
    sp.rot[1] = 0.0f;
    sp.rot[2] = 0.0f;
    sp.spin[1] = 0.0f;
    sp.model = s->model;
    sp.uEC = 0.2f;
    extra.gravity = -18.0f;
    extra.u54 = s->u54;
    extra.u55 = s->u55;
    extra.u56 = s->u56;
    sp.u144 = 0;
    sp.u148 = 0xFF;
    sp.u149 = 1;
    sp.u14A = 5;
    sp.u14B = 4;
    sp.u14C = 0;
    sp.u14D = 0;
    sp.u14E = 1;
    sp.u14F = 0;
    sp.u150 = 0;
    sp.u152 = 0;
    sp.u154 = 0;
    sp.u158 = 0;
    sp.u15A = 0x20;
    sp.u15C = 7;
    extra.u58 = s->u58;
    while (n-- != 0) {
        yaw = random_int() % (u32)(s->yawRange + 1) + s->yawMin;
        pitch = random_int() % (u32)(s->pitchRange + 1) + s->pitchMin;
        sy = angle_byte_cos(yaw - 0x40);
        cy = angle_byte_cos(yaw);
        sp_ = angle_byte_cos(pitch - 0x40);
        cp = angle_byte_cos(pitch);
        r = random_float() * s->radius;
        h = r * cp;
        sp.pos[0] = s->pos[0] + h * sy;
        sp.pos[1] = s->pos[1] - r * sp_;
        sp.pos[2] = s->pos[2] + h * cy;
        switch ((u8)mode) {
        case 0:
            v = random_float() * s->speedRange + s->speedMin;
            sp.vel[1] = random_float() * s->upRange + s->upMin;
            sp.vel[0] = v * sy;
            sp.vel[2] = v * cy;
            break;
        case 1:
            v = random_float() * s->speedRange + s->speedMin;
            h = v * cp;
            sp.vel[0] = h * sy;
            sp.vel[1] = -v * sp_;
            sp.vel[2] = h * cy;
            break;
        case 2:
            ((s32 *)sp.vel)[0] = ((s32 *)s->dir)[0];
            ((s32 *)sp.vel)[1] = ((s32 *)s->dir)[1];
            ((s32 *)sp.vel)[2] = ((s32 *)s->dir)[2];
            break;
        case 3:
            v = random_float() * s->speedRange + s->speedMin;
            sp.vel[0] = s->dir[0] * v;
            sp.vel[1] = s->dir[1] * v;
            sp.vel[2] = s->dir[2] * v;
            break;
        }
        size = random_float() * s->sizeRange + s->sizeMin;
        sp.uF4 = size;
        sp.uF0 = size;
        sp.scale = size * 30.0f;
        sp.u134 = random_float() * s->spinRange + s->spinMin;
        sp.spin[0] = random_float() * s->rotRange + s->rotMin;
        sp.spin[2] = random_float() * s->rotRange + s->rotMin;
        p = (u8 *)mdl_particle_spawn(&sp, 0, 0, 0x10, arg2, arg3);
        if (p != NULL) {
            memcpy(p + 0x170, &extra, 0x10);
            trail.pos[0] = p + 0x38;
            trail.pos[1] = p + 0x3C;
            trail.pos[2] = p + 0x40;
            trail.size = 15.0f * sp.uF4;
            trail.life = 300;
            trail.uA2 = 0;
            trail.uA3 = 1;
            trail.u9C = 0.358f;
            *(u8 **)(p + 0x170 + 4) = NULL;
            t = (u8 *)point_emitter_spawn((struct_eu_EF410 *)&trail, 4, arg2, arg3);
            *(u8 **)(p + 0x170 + 4) = t;
            if (t != NULL) {
                memcpy(t + 0x40, &size, 4);
            }
        }
    }
    return 0;
}

/* was func_151A799C */
s32 debris_piece_update(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = arg0 + 0x170;
    if (*(s16 *)(arg0 + 0x64) < 0x20) {
        if (*(struct102 **)(temp_v0 + 4) != NULL) {
            node_destroy(*(struct102 **)(temp_v0 + 4));
            *(struct102 **)(temp_v0 + 4) = NULL;
        }
    }
    return 1;
}

void spark_spawn_burst(f32, f32, f32, f32, s16, f32, f32, f32, f32, s16, s16, u8);
/* P317: NM signature = D_80089CD4's dispatcher type (wasm call_indirect); arg3 is the f32 the asm passes on */
/* was func_151A79EC */
s32 debris_piece_on_ground(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, u8 *arg5)
{
  u8 *p;
  u8 b;
  p = arg0 + 0x170;
  *((f32 *) (arg0 + 0x3C)) = (*((f32 *) (arg0 + 0x10))) + arg4;
  if ((*((s32 *) (arg0 + 0x174))) != 0)
  {
    node_destroy(*((struct102 **) (p + 4)));
    *((struct102 **) (p + 4)) = 0;
  }
  if ((*((f32 *) p)) < (*((f32 *) (arg0 + 0x48))))
  {
    *((s32 *) (arg0 + 0x60)) &= ~7;
    *((s32 *) (arg0 + 0x60)) &= ~8;
    *((s32 *) (arg0 + 0x60)) &= ~0x40;
    *((s32 *) (arg0 + 0x60)) &= ~0x20;
    *((f32 *) (arg0 + 0x44)) = 0.0f;
    *((f32 *) (arg0 + 0x48)) = 0.0f;
    *((f32 *) (arg0 + 0x4C)) = 0.0f;
    if ((*((s16 *) (arg0 + 0x64))) > 0x20)
    {
      *((s16 *) (arg0 + 0x64)) = 0x20;
    }
    if (p[8] != 0)
    {
      b = 0;
      if (p[9] != 0)
      {
        b = 1;
      }
      spark_spawn_burst(arg1, arg4, arg3, (*((f32 *) (arg0 + 0x18))) * 35.0f, (random_int() % 3U) + 2, *((f32 *) (arg0 + 0x18)), (*((f32 *) (arg0 + 0x18))) * 0.5f, *((f32 *) (arg0 + 0x18)), (*((f32 *) (arg0 + 0x18))) * 0.5f, *((s16 *) (p + 0xA)), *((s16 *) (p + 0xC)), b);
    }
  }
  else
  {
    *((f32 *) (arg0 + 0x44)) *= *((f32 *) (arg0 + 0x14));
    *((f32 *) (arg0 + 0x48)) = (*((f32 *) (arg0 + 0x14))) * (-(*((f32 *) (arg0 + 0x48))));
    *((f32 *) (arg0 + 0x4C)) *= *((f32 *) (arg0 + 0x14));
    *((f32 *) (arg0 + 0x50)) *= *((f32 *) (arg0 + 0x14));
    *((f32 *) (arg0 + 0x54)) *= *((f32 *) (arg0 + 0x14));
    *((f32 *) (arg0 + 0x58)) *= *((f32 *) (arg0 + 0x14));
  }
  return 1;
}

s32 particle_puff_spawn(f32 *, f32 *, f32 *, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* P95: f32 parameter */
void debris_dust_puff_spawn(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6);
void debris_sprite_fade_update(u8 *arg0);
void debris_sprite_fade_update_b(u8 *arg0);
void debris_piece_free_trail(u8 *arg0);

s32 particle_puff_spawn(f32 *, f32 *, f32 *, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* P95: f32 parameter */

/* was func_151A7BC0 */
void debris_dust_puff_spawn(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
    f32 sp74[9];
    f32 temp_f18;
    f32 sp6C;
    f32 temp_f2;

    sp6C = (*(f32 *)((u8 *)arg6 + 0x40));
    sp74[6] = arg0;
    sp74[7] = arg1;
    sp74[8] = arg2;
    temp_f18 = (random_float() * 166.0f) + 160.0f;
    sp74[0] = 0.0f;
    sp74[1] = 0.0f;
    sp74[2] = 0.0f;
    temp_f2 = temp_f18 * 0.001f;
    sp74[3] = -arg3 * D_800BEDC8 * temp_f2;
    sp74[4] = -arg4 * D_800BEDC8 * temp_f2;
    sp74[5] = -arg5 * D_800BEDC8 * temp_f2;
    particle_puff_spawn(&sp74[6], sp74, &sp74[3], 1.0f, ((random_float() * 591.0f) + -600.0f) * 0.001f, ((random_float() * 500.0f) + 400.0f) * sp6C, ((u32) random_int() % 21U) + 0xF, (random_int() % 101U) + 0x64, 0xF, 0x14, 0, -1, 0x56, 0x27, 0, (s32) (*(u8 *)((u8 *)arg6 + 0xC)), (s32) (*(u8 *)((u8 *)arg6 + 1))); /* P95: float literal (asm passes the bits 0x3F800000) */
}

/* was func_151A7D70 */
void debris_sprite_fade_update(u8 *arg0)
{
  u8 *p = arg0 + 0x50;
  unsigned char t;
  if ((*((s16 *) (arg0 + 0x38))) < (*((s16 *) (arg0 + 0x54))))
  {
    *((s8 *) (arg0 + 0x3F)) = (*((s16 *) (arg0 + 0x56))) * (*((s16 *) (arg0 + 0x38)));
  }
  if ((*((s16 *) (arg0 + 0x38))) < (*((s16 *) (p + 8))))
  {
    short d;
    d = (*((s16 *) (p + 0xA))) * D_800BE9E4;
    *((s16 *) (arg0 + 0x34)) += d;
    *((s16 *) (arg0 + 0x36)) += d;
  }
  if ((*((s16 *) (arg0 + 0x38))) < (*((s16 *) (p + 0))))
  {
    *((s8 *) (arg0 + 0x2F)) = 0x15;
    *((u16 *) (arg0 + 0x44)) |= 0x201;
    t = (*((s16 *) (p + 2))) * (0, (*((s16 *) (arg0 + 0x38)))); // fakematch: comma puts arg0->0x38 in fs of multu (s142 recipe 1)
    *((s32 *) (arg0 + 0x14)) = 0xC000F;
    *((s8 *) (arg0 + 0x42)) = t;
    *((s8 *) (arg0 + 0x41)) = t;
    *((s8 *) (arg0 + 0x40)) = t;
  }
}

#define S(o) (*(s16 *)(arg0 + (o)))
#define S2(o) (*(s16 *)(p + (o)))
/* was func_151A7E2C */
void debris_sprite_fade_update_b(u8 *arg0)
{
  u8 *p = arg0 + 0x50;
  unsigned char t;
  if ((*((s16 *) (arg0 + 0x38))) < (*((s16 *) (arg0 + 0x54))))
  {
    *((s8 *) (arg0 + 0x3F)) = (*((s16 *) (arg0 + 0x56))) * (*((s16 *) (arg0 + 0x38)));
  }
  if ((*((s16 *) (arg0 + 0x38))) < (*((s16 *) (p + 8))))
  {
    short d;
    d = (*((s16 *) (p + 0xA))) * D_800BE9E4;
    *((s16 *) (arg0 + 0x34)) += d;
    *((s16 *) (arg0 + 0x36)) += d;
  }
  t = (*((s16 *) (p + 2))) * (0, (*((s16 *) (arg0 + 0x38)))); // fakematch: comma puts arg0->0x38 in fs of multu (s142 recipe 1)
  *((s8 *) (arg0 + 0x42)) = t;
  *((s8 *) (arg0 + 0x41)) = t;
  *((s8 *) (arg0 + 0x40)) = t;
}

/* was func_151A7EB8 */
void debris_piece_free_trail(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = arg0 + 0x170;
    if (*(s32 *)(arg0 + 0x174) != 0) {
        node_destroy(*(struct102 **)(temp_v0 + 4));
        *(struct102 **)(temp_v0 + 4) = NULL;
    }
}
