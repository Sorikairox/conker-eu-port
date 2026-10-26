#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* P125 */
extern u8 D_8008D450[];

/* flag_wave_update: waves the two vertex buffers of animated mesh slot i (D_800DDE80 entry: Vtx *buf +8 and +4;
 * D_8008D450 entry (0x38 bytes): f32 speed +0x18 / +0x1C, angle (degrees) +0x20 / +0x24, amplitude +0x28). Per
 * buffer: h = sin(angle) * amplitude; vertices 2 and 3 get x = h, the seven vertices of the rodata list
 * D_800A75F0 (4, 9, 13, 14, 15, 17, 19) x = -h / 2,
 * vertex 6 x = -h / 2 + 18 and vertex 8 x = -h / 2 - 18; then the angle advances by its speed, wrapped below 360. */
/* was func_1517A320 */
void flag_wave_update(u8 i) {
    static const u8 rows[7] = { 4, 9, 13, 14, 15, 17, 19 };
    s32 *slot;
    u8 *e;
    s16 *buf[2];
    f32 *angle[2];
    f32 *speed[2];
    s16 h;
    s16 m;
    s32 k;
    s32 j;

    slot = &D_800DDE80[i * 5];
    e = D_8008D450 + i * 0x38;
    angle[0] = (f32 *) (e + 0x20);
    angle[1] = (f32 *) (e + 0x24);
    speed[0] = (f32 *) (e + 0x18);
    speed[1] = (f32 *) (e + 0x1C);
    buf[1] = (s16 *) slot[1];
    buf[0] = (s16 *) slot[2];
    for (k = 0; k < 2; k++) {
        h = (s32) (sinf(*angle[k] * 0.017453292f) * *(f32 *) (e + 0x28));
        buf[k][0x20 / 2] = h;
        m = -(h >> 1);
        buf[k][0x30 / 2] = h;
        for (j = 0; j < 7; j++) {
            buf[k][rows[j] * 8] = m;
        }
        buf[k][0x60 / 2] = m + 0x12;
        buf[k][0x80 / 2] = m - 0x12;
        *angle[k] += *speed[k];
        if (*angle[k] >= 360.0f) {
            *angle[k] -= 360.0f;
        }
    }
}

/* P139 */
/*
 * drift_object_spawn: creates an object of the given type (node_alloc(type, 0, 0xB8, 1, 0xFF, 1)) and sets it up:
 * position (x, y, z) at +0x90/+0x92/+0x94, s16 velocity +0xA0 / +0xA2 / +0xA4 = (random in -spread/2..,
 * (s8) tilt, random), +0x96..+0x9A cleared, random byte spins +0x9C..+0x9E (each rand % jitter - jitter / 2),
 * scale +0xA8 = (140 + rand & 0x7F) * 0.01, +0xA6 = arg5, +0x9F = colour, +0xAC = mode, +0xAE = arg9, +0xB2 = 0,
 * +0xB3 = 0xFF. Mode 5 starts it one 4x velocity step ahead (x += 4 vx, y -= 4 vy, z += 4 vz). Nothing when
 * the object cannot be created.
 */
/* was func_1517A550 */
void puff_drift_spawn(u8 colour, s16 x, s16 y, s16 z, s8 tilt, u16 arg5, u16 mode, u8 spread, u8 jitter, u8 arg9,
                   s32 type) {
    u8 *obj = node_alloc(type, 0, 0xB8, 1, 0xFF, 1);

    if (obj == NULL) {
        return;
    }
    *(s16 *) (obj + 0x90) = x;
    *(s16 *) (obj + 0x92) = y;
    *(s16 *) (obj + 0x94) = z;
    *(s16 *) (obj + 0xA2) = tilt;
    *(s16 *) (obj + 0xA0) = (u32) random_int() % spread - (spread >> 1);
    *(s16 *) (obj + 0xA4) = (u32) random_int() % spread - (spread >> 1);
    if (mode == 5) {
        *(s16 *) (obj + 0x90) += *(s16 *) (obj + 0xA0) * 4;
        *(s16 *) (obj + 0x92) -= *(s16 *) (obj + 0xA2) * 4;
        *(s16 *) (obj + 0x94) += *(s16 *) (obj + 0xA4) * 4;
    }
    *(s16 *) (obj + 0x96) = 0;
    *(s16 *) (obj + 0x98) = 0;
    *(s16 *) (obj + 0x9A) = 0;
    obj[0x9C] = (u32) random_int() % jitter - (jitter >> 1);
    obj[0x9D] = (u32) random_int() % jitter - (jitter >> 1);
    obj[0x9E] = (u32) random_int() % jitter - (jitter >> 1);
    *(f32 *) (obj + 0xA8) = (f32) ((random_int() & 0x7F) + 0x8C) * 0.01f;
    *(u16 *) (obj + 0xA6) = arg5;
    obj[0x9F] = colour;
    *(u16 *) (obj + 0xAC) = mode;
    obj[0xB2] = 0;
    obj[0xB3] = 0xFF;
    *(s16 *) (obj + 0xAE) = arg9;
}

// sprite_particle_update: update handler of the puff_drift_spawn sprite particles (tables next to puff_sprite_draw).
// Moves the screen position +0x90 / +0x92 / +0x94 by the velocity +0xA0 / -+0xA2 / +0xA4 and the rotation
// +0x96..+0x9A by the s8 spins +0x9C..+0x9E; mode 5 (+0xAC) adds gravity (+0xA2 += 1). While the life +0xA6 is
// below the mode value, the x / z velocities lose a random part (rand % +0xAE) towards zero. The life runs down by the
// frame step D_800BE9E4; once out, alpha +0xB3 fades by 4 per step. Freed (node_destroy) at alpha 0, or when the
// frame counter +0xB2 is non-zero and its low and high nibbles are equal.
/* was func_1517A75C */
void puff_drift_update(u8 *obj) {
    s32 vy = *(s16 *) (obj + 0xA2);
    u32 mode;
    s32 life;
    s32 v;
    s32 sign;
    u32 r;
    s32 a;
    u8 alpha;

    *(s16 *) (obj + 0x90) += *(s16 *) (obj + 0xA0);
    *(s16 *) (obj + 0x92) -= vy;
    *(s16 *) (obj + 0x94) += *(s16 *) (obj + 0xA4);
    *(s16 *) (obj + 0x96) += *(s8 *) (obj + 0x9C);
    *(s16 *) (obj + 0x98) += *(s8 *) (obj + 0x9D);
    *(s16 *) (obj + 0x9A) += *(s8 *) (obj + 0x9E);
    mode = *(u16 *) (obj + 0xAC);
    if (mode == 5) {
        *(s16 *) (obj + 0xA2) = vy + 1;
        mode = *(u16 *) (obj + 0xAC);
    }
    life = *(u16 *) (obj + 0xA6);
    if (life < (s32) mode) {
        r = (u32) random_int() % *(u16 *) (obj + 0xAE);
        v = *(s16 *) (obj + 0xA0);
        sign = 1;
        if (v < 0) {
            sign = -1;
        }
        *(s16 *) (obj + 0xA0) = v + -sign * r;
        r = (u32) random_int() % *(u16 *) (obj + 0xAE);
        v = *(s16 *) (obj + 0xA4);
        sign = 1;
        if (v < 0) {
            sign = -1;
        }
        *(s16 *) (obj + 0xA4) = v + -sign * r;
        life = *(u16 *) (obj + 0xA6);
    }
    v = life - D_800BE9E4;
    if (v < 0) {
        a = obj[0xB3] - D_800BE9E4 * 4;
        v = 0;
        if (a < 0) {
            a = 0;
        }
        obj[0xB3] = a;
    }
    alpha = obj[0xB3];
    *(u16 *) (obj + 0xA6) = v;
    if (alpha == 0 || (obj[0xB2] != 0 && (obj[0xB2] & 0xF) == (obj[0xB2] >> 4))) {
        node_destroy((struct102 *) obj);
    }
}

/* was func_1517A904 */
s32 puff_identity_stub(s32 arg0) {
    return arg0;
}

s32 view_point_cull_test(u8 *, f32, f32, f32, f32, f32, f32, f32, f32 *, f32 *);
u8 *gfx_other_mode_cached(s32, s32, s32, s8 *);
s32 puff_texture_set(s32 arg0, s32 arg1);
extern f32 D_800D9F40;     /* screen width */
extern f32 D_800D9F3C;     /* screen height */
extern f32 D_800D3A00[2];  /* frustum side slopes */
extern f32 D_800DA030[][4][4];
extern Gfx D_8008D190[];
extern s32 D_800D30BC;

// puff_sprite_draw: draw handler of the puff sprite objects (types 8, 9, 0xC, 0x59) for `player`. Except for
// types 0xC and 0x59, a puff outside the player's view (view_point_cull_test) is skipped; a culled type 8 puff that was seen
// by this player (obj + 0xB2 bit 1 << player) also gets bit 0x10 << player. Otherwise it marks itself seen (all but
// type 9), sets the texture (puff_texture_set, obj + 0x9F), builds its matrix (rotation 0x96.., scale 0xA8, position
// 0x90..) and draws D_8008D190 with alpha obj + 0xB3 (prim colour reloaded only when it changed, D_800DD880).
/* was func_1517A910 */
s32 puff_sprite_draw(s32 gfxArg, u8 *obj, s16 player) {
    Gfx *gfx;
    Mtx *mtx;
    f32 scale;
    s8 flag;
    s32 mode;

    if (obj[0] != 0xC && obj[0] != 0x59) {
        if (view_point_cull_test((u8 *) D_800DA030[player], *(s16 *) (obj + 0x90), *(s16 *) (obj + 0x92),
                          *(s16 *) (obj + 0x94), D_800D9F40, D_800D9F3C, D_800D3A00[0], D_800D3A00[1], NULL,
                          NULL) != 0) {
            if (obj[0] == 8 && (obj[0xB2] & (1 << player))) {
                obj[0xB2] |= 0x10 << player;
            }
            return gfxArg;
        }
    }
    if (obj[0] != 9) {
        obj[0xB2] |= 1 << player;
    }
    gfx = (Gfx *) puff_texture_set(gfxArg, obj[0x9F]);
    scale = *(f32 *) (obj + 0xA8);
    mtx = &((Mtx *) (obj + 0x10))[D_800BE9C0];
    mtx_build_rot_scale_trans(mtx, *(s16 *) (obj + 0x96), *(s16 *) (obj + 0x98), *(s16 *) (obj + 0x9A), scale, scale, scale,
                  *(s16 *) (obj + 0x90), *(s16 *) (obj + 0x92), *(s16 *) (obj + 0x94));
    gSPMatrix(gfx++, &((Mtx *) (obj + 0x10))[D_800BE9C0], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (obj[0xB3] != D_800DD880) {
        gDPPipeSync(gfx++);
        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, obj[0xB3]);
        D_800DD880 = obj[0xB3];
    }
    flag = 0;
    if (obj[0] == 8 || obj[0] == 9) {
        mode = 0x5049D8;
    } else {
        mode = 0x504240;
    }
    gfx = (Gfx *) gfx_other_mode_cached((s32) gfx, D_800D30BC | 0x82CA0, mode, &flag);
    gSPDisplayList(gfx++, D_8008D190);
    return (s32) gfx;
}

s32 collision_find_floor_default_range(s32, s32, f32 *, s32, s32, s32, f32, f32, f32, f32, s32, s32);

/* was func_1517ABB4 */
void puff_ground_chip_spawn(f32 arg0, u8 arg1, s16 arg2, s16 arg3, s16 arg4)
{
  u8 *obj;
  s32 n;
  f32 d;
  s32 h;
  s32 pad;
  n = arg0;
  if (n != 0)
  {
    obj = node_alloc(9, 0, 0xB8, 1, 0xFF, 1);
    if (obj)
    {
      collision_find_floor_default_range(0, 0, &d, 0, 0, 0, arg2, arg3, arg4, arg3, 0, 0);
 if (0) {} // fakematch: block boundary, puts the shared s16 store value in v0
      *((s16 *) (obj + 0x92)) = (*((s16 *) (obj + 0xB0)) = d + 3.0f);
      *((s16 *) (obj + 0x90)) = arg2;
      *((s16 *) (obj + 0x94)) = arg4;
      *((s16 *) (obj + 0x96)) = 0x5A;
      *((s16 *) (obj + 0x98)) = random_int() % 360U;
      *((s16 *) (obj + 0x9A)) = 0;
      *((s16 *) (obj + 0xA0)) = 0;
      *((s16 *) (obj + 0xA4)) = 0;
      *((u8 *) (obj + 0x9F)) = arg1;
      *((f32 *) (obj + 0xA8)) = ((s32) ((random_int() % 80U) + 0x64)) * 0.01f;
      *((s16 *) (obj + 0xA2)) = arg0 * 0.4f;
      h = arg0 * 0.5f;
      *((s8 *) (obj + 0x9C)) = (random_int() % ((u32) n)) - h;
      *((s8 *) (obj + 0x9D)) = (random_int() % ((u32) n)) - h;
      *((s8 *) (obj + 0x9E)) = (random_int() % ((u32) n)) - h;
      *((s16 *) (obj + 0xA6)) = 0;
      *((u8 *) (obj + 0xB3)) = 0xFF;
    }
  }
}

/* was func_1517ADBC */
void puff_ground_chip_update(struct102 *arg0) {
    s32 t;
    s16 v;
    t = *(u16 *)((u8 *)arg0 + 0xA6);
    if (t == 0) {
        *(s16 *)((u8 *)arg0 + 0x90) += *(s16 *)((u8 *)arg0 + 0xA0);
        *(s16 *)((u8 *)arg0 + 0x92) += *(s16 *)((u8 *)arg0 + 0xA2);
        *(s16 *)((u8 *)arg0 + 0x94) += *(s16 *)((u8 *)arg0 + 0xA4);
        if (*(s16 *)((u8 *)arg0 + 0xA2) > 0) {
            (*(s16 *)((u8 *)arg0 + 0xA2))--;
            if (*(s16 *)((u8 *)arg0 + 0xA2) <= 0) {
                *(s16 *)((u8 *)arg0 + 0xA2) = -3;
            }
        }
        v = *(s16 *)((u8 *)arg0 + 0xB0);
        t = *(s16 *)((u8 *)arg0 + 0x92) - v;
        if (t <= 0) {
            *(s16 *)((u8 *)arg0 + 0x96) = 0x5A;
            *(s16 *)((u8 *)arg0 + 0x9A) = 0;
            *(u16 *)((u8 *)arg0 + 0xA6) = 60;
            *(s16 *)((u8 *)arg0 + 0x92) = v;
        } else {
            *(s16 *)((u8 *)arg0 + 0x96) += *(s8 *)((u8 *)arg0 + 0x9C);
            *(s16 *)((u8 *)arg0 + 0x98) += *(s8 *)((u8 *)arg0 + 0x9D);
            *(s16 *)((u8 *)arg0 + 0x9A) += *(s8 *)((u8 *)arg0 + 0x9E);
        }
    } else {
        t = t - D_800BE9E4;
        if (t > 0) {
            *(u16 *)((u8 *)arg0 + 0xA6) = t;
            *(s8 *)((u8 *)arg0 + 0xB3) = (t * 256) / 60;
        } else {
            node_destroy(arg0);
        }
    }
}

/* was func_1517AEC8 */
s32 puff_draw_begin(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_800DD880 = -1;
    if ((arg1 == 0xC) || (arg1 == 0x59)) {
        arg0 = puff_identity_stub(arg0);
    }
    return arg0;
}

extern s32 D_800DD5E0;
extern u8 D_800909C4[];
/* was func_1517AF18 */
s32 puff_texture_set(s32 arg0, s32 arg1) {
    s32 sp30[6]; // fakematch: stack layout guess (frame 0x48, &sp30[1] at 0x34)
    if (arg1 != D_800DD5E0) {
        arg0 = sprite_load_texture(arg0, D_800909C4, (u32)arg1 << 8, &sp30[1], 0, 0, 0, 2, 3);
        D_800DD5E0 = arg1;
    }
    return arg0;
}

void puff_ground_chip_spawn(f32, u8, s16, s16, s16);

/* was func_1517AF90 */
void puff_ground_chips_burst(f32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  s32 i;
  s32 x;
  s32 z;
  s32 m;
  f32 h;
  f32 f;
  if (arg0 < 12.0f)
  {
    return;
  }
  m = arg0 * 8.0f;
  arg0 *= 0.5f;
  for (i = 0; i < arg4; i++)
  {
    x = random_int() & 0x3F;
    z = random_int() & 0x3F;
    x -= 0x20;
    z -= 0x20;
    f = ((((u32) random_int()) % m) >> 4) + arg0;
    puff_ground_chip_spawn(f, random_int() & 1, arg1 + x, arg2, arg3 + z);
  }

}

/* was func_1517B0EC */
void puff_view_dl_begin(s32 arg0, s32 arg1, s16 arg2) {
    view_dl_begin(arg0, arg2);
}
