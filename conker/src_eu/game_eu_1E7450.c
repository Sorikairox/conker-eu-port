#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void *node_spawn_sprite(void *, s32, s32, s8, u8, s32);
extern u8 *g_sprite_tex_descs[]; /* was D_8008CDEC */
f32 sinf(f32);
f32 cosf(f32);

// spark_sprite_launch: launches one spark sprite (node_spawn_sprite, texture g_sprite_tex_descs[tex]) from (x, y + 1, z): the
// direction is angle + 180 +- angSpread / 2 degrees, the start point is moved dist along it, the horizontal speed is
// speed +- speedSpread / 2 (speedSpread 0 counts as 1) and the vertical speed rise +- riseSpread / 2 (gravity -160).
// mode 2 tints it 68 38 10, other modes are white; random byte at +0x2B. `unused` (the caller's -80) is not read.
/* was func_151B9C40 */
void spark_sprite_launch(s32 tex, s32 mode, s16 x, s16 y, s16 z, s32 unused, f32 angle, s16 angSpread, s16 rise,
                   s16 riseSpread, s16 speed, s16 speedSpread, s16 dist, s16 hi, s16 size, u8 room, s32 owner) {
    struct {
        /* 0x00 */ void *tex;
        /* 0x04 */ s32 u4;
        /* 0x08 */ s32 mode;
        /* 0x0C */ s16 uC;
        /* 0x0E */ s16 uE;
        /* 0x10 */ s16 pos[3];
        /* 0x16 */ s16 vel[2];
        /* 0x1A */ s16 size;
        /* 0x1C */ u8 pad1C[3];
        /* 0x1F */ u8 u1F;
        /* 0x20 */ s16 rise;
        /* 0x22 */ s16 gravity;
        /* 0x24 */ s16 u24;
        /* 0x26 */ s16 u26;
        /* 0x28 */ s16 u28;
        /* 0x2A */ u8 u2A;
        /* 0x2B */ u8 u2B;
        /* 0x2C */ u8 colour[4];
        /* 0x30 */ u8 pad30[4];
        /* 0x34 */ s16 u34;
    } rec;
    s32 y0;
    f32 sn;
    f32 cs;
    f32 rad;
    f32 spd;
    f32 d;
    s32 r;
    u8 red;
    u8 green;
    u8 blue;

    y0 = y;
    angle += 180.0f;
    angle += (f32) (s32) ((u32) random_int() % (u32) angSpread - (angSpread >> 1));
    rad = angle * 0.017453292f;
    sn = sinf(rad);
    cs = cosf(rad);
    if (speedSpread == 0) {
        speedSpread = 1;
    }
    r = (u32) random_int() % (u32) speedSpread - (speedSpread >> 1);
    d = dist;
    x = (s32) (x + d * sn);
    z = (s32) (z + d * cs);
    spd = speed + (f32) r;
    y++;
    r = rise + (s32) ((u32) random_int() % (u32) riseSpread - (riseSpread >> 1));
    if (mode == 2) {
        red = 0x68;
        green = 0x38;
        blue = 0x10;
    } else {
        red = 0xFF;
        green = 0xFF;
        blue = 0xFF;
    }
    rec.tex = g_sprite_tex_descs[tex];
    rec.u4 = (hi << 16) | (y0 & 0xFFFF);
    rec.uE = 0x100;
    rec.pos[0] = x;
    rec.mode = mode;
    rec.uC = 0;
    rec.size = size;
    rec.u1F = 0;
    rec.rise = r;
    rec.gravity = -0xA0;
    rec.u24 = size;
    rec.u26 = size;
    rec.u28 = 0x190;
    rec.u2A = 0;
    rec.pos[1] = y;
    rec.pos[2] = z;
    rec.vel[0] = (s32) (spd * sn);
    rec.vel[1] = (s32) (spd * cs);
    rec.u2B = random_int();
    rec.colour[3] = 0xFF;
    rec.u34 = 0;
    rec.colour[0] = red;
    rec.colour[1] = green;
    rec.colour[2] = blue;
    node_spawn_sprite(&rec, 0, 0, -1, room, owner);
}

extern f32 g_spark_sprite_shrink; /* was D_800AA964 */
extern f32 g_spark_sprite_wobble_scale; /* was D_800AA968 */
f32 math_cos_u8(u8);
s32 decal_spawn_at(f32, f32, f32, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32, s32);

/* was func_151B9F14 */
void spark_sprite_update(u8 *arg0) {
    f32 sp5C;
    s16 sp5A;
    s32 sp50;
    u8 sp4F;
    s16 temp_a1;
    s16 temp_v0;
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_v1;
    s32 var_v0;
    u8 temp_t9;

    temp_a2 = (*(s32 *)((u8 *)arg0 + 0x18));
    if (temp_a2 == 1) {
        temp_t9 = ((*(u8 *)((u8 *)arg0 + 0x3B)) + (g_frame_ticks * 4) + (g_frame_ticks * 2)) & 0xFF;
        (*(u8 *)((u8 *)arg0 + 0x3B)) = temp_t9;
        (*(s16 *)((u8 *)arg0 + 0x2A)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x2A)) * g_spark_sprite_shrink);
        sp50 = temp_a2;
        sp4F = temp_t9;
        sp5C = (f32) (*(s16 *)((u8 *)arg0 + 0x2A));
        (*(s16 *)((u8 *)arg0 + 0x34)) = (s16) (s32) ((math_sin_u8(temp_t9) + 3.0f) * sp5C * g_spark_sprite_wobble_scale);
        (*(s16 *)((u8 *)arg0 + 0x36)) = (s16) (s32) ((math_cos_u8(sp4F) + 3.0f) * sp5C * g_spark_sprite_wobble_scale);
    } else {
        temp_a1 = (*(s16 *)((u8 *)arg0 + 0x34));
        temp_a0 = (s32) (*(s32 *)((u8 *)arg0 + 0x14)) >> 0x10;
        if (temp_a0 != temp_a1) {
            var_v0 = temp_a1 - (g_frame_ticks * 4);
            if (var_v0 < temp_a0) {
                var_v0 = temp_a0;
            }
            (*(s16 *)((u8 *)arg0 + 0x36)) = (s16) var_v0;
            (*(s16 *)((u8 *)arg0 + 0x34)) = (s16) var_v0;
        }
    }
    temp_v0 = (*(s16 *)((u8 *)arg0 + 0x22));
    if ((s16) (*(s32 *)((u8 *)arg0 + 0x14)) >= temp_v0) {
        (*(s16 *)((u8 *)arg0 + 0x38)) = 0;
        if (temp_a2 == 0) {
            sp5A = (s16) (*(s32 *)((u8 *)arg0 + 0x14));
            if ((random_int() & 0xFF) < 0x40) {
                decal_spawn_at((f32) (*(s16 *)((u8 *)arg0 + 0x20)), (f32) sp5A, (f32) (*(s16 *)((u8 *)arg0 + 0x24)), 0xA, 0, 0x13, 0.0f, 0, 0x32, 0xF, 0x100, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            }
            if ((random_int() & 0xFF) < 0xF) {
                random_int();
                sound_play_at(0x70, 0x1388U, 0, 0U, 0, (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x20)), (s16) (s32) sp5A, (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x24)), 0x1F4, 0x7D0);
            }
        }
    } else {
        temp_v1 = temp_v0 - (s16) (*(s32 *)((u8 *)arg0 + 0x14));
        if (((*(s16 *)((u8 *)arg0 + 0x30)) < 0) && (temp_v1 < 0x40)) {
            (*(s8 *)((u8 *)arg0 + 0x3F)) = (s8) (temp_v1 * 4);
        }
    }
}
/* was func_151BA1A0 */
void spark_sprite_burst_spawn(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s16 argA, s16 argB, s16 argC, s32 argD, u8 argE, s32 argF) {
    u8 *temp_v0;

    temp_v0 = node_alloc(7, argF, 0x2C, 0, (u8) (s32) argE, 1U);
    if (temp_v0 != NULL) {
        (*(s8 *)((u8 *)temp_v0 + 0x14)) = (s8) arg0;
        (*(s8 *)((u8 *)temp_v0 + 0x15)) = (s8) arg1;
        (*(s16 *)((u8 *)temp_v0 + 0x16)) = arg2;
        (*(s16 *)((u8 *)temp_v0 + 0x18)) = arg3;
        (*(s16 *)((u8 *)temp_v0 + 0x1A)) = arg4;
        (*(s16 *)((u8 *)temp_v0 + 0x1C)) = arg5;
        (*(s16 *)((u8 *)temp_v0 + 0x1E)) = arg6;
        (*(s16 *)((u8 *)temp_v0 + 0x20)) = arg7;
        (*(s16 *)((u8 *)temp_v0 + 0x22)) = arg8;
        (*(s16 *)((u8 *)temp_v0 + 0x24)) = arg9;
        (*(s16 *)((u8 *)temp_v0 + 0x26)) = argA;
        (*(s16 *)((u8 *)temp_v0 + 0x28)) = argB;
        (*(s16 *)((u8 *)temp_v0 + 0x2A)) = argC;
        (*(s32 *)((u8 *)temp_v0 + 0x10)) = argD;
    }
}

void spark_sprite_launch(s32, s32, s16, s16, s16, s32, f32, s16, s16, s16, s16, s16, s16, s16, s16, u8, s32);

// burst_emitter_finish: emits the object's burst at its anchor (the f32 position at obj+0x10 if any, else the s16
// position at obj+0x16): obj+0x28 shots with the parameters at obj+0x1C..0x26, then 4 more with the first two
// widened (x1.5 / x2), all through spark_sprite_launch (types obj+0x14 / 0x15, angle -80, spread 360, life 15). Then counts
// obj+0x2A down by the frame step g_frame_ticks and frees the object when it goes negative (node_destroy).
/* was func_151BA260 */
void spark_sprite_burst_update(u8 *obj) {
    f32 *anchor = *(f32 **) (obj + 0x10);
    s16 x;
    s16 y;
    s16 z;
    s32 i;
    s32 t;

    if (anchor == NULL) {
        x = *(s16 *) (obj + 0x16);
        y = *(s16 *) (obj + 0x18);
        z = *(s16 *) (obj + 0x1A);
    } else {
        x = (s32) anchor[0];
        y = (s32) anchor[1];
        z = (s32) anchor[2];
    }
    for (i = 0; i < *(s16 *) (obj + 0x28); i++) {
        spark_sprite_launch(obj[0x14], obj[0x15], x, y, z, -0x50, 0.0f, 0x168, *(s16 *) (obj + 0x1C), *(s16 *) (obj + 0x1E),
                      *(s16 *) (obj + 0x20), *(s16 *) (obj + 0x22), 0xF, *(s16 *) (obj + 0x24), *(s16 *) (obj + 0x26),
                      obj[0xC], obj[1]);
    }
    for (i = 0; i < 4; i++) {
        spark_sprite_launch(obj[0x14], obj[0x15], x, y, z, -0x50, 0.0f, 0x168, (*(s16 *) (obj + 0x1C) * 3) / 2,
                      *(s16 *) (obj + 0x1E) * 2, *(s16 *) (obj + 0x20), *(s16 *) (obj + 0x22), 0xF,
                      *(s16 *) (obj + 0x24), *(s16 *) (obj + 0x26), obj[0xC], obj[1]);
    }
    t = *(s16 *) (obj + 0x2A) - g_frame_ticks;
    if (t < 0) {
        node_destroy((struct102 *) obj);
    } else {
        *(s16 *) (obj + 0x2A) = t;
    }
}
