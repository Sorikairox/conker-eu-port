#include <ultra64.h>
#include "functions.h"
#include "variables.h"


struct210 *effect3d_spawn_default(s32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s32 arg6, u8 arg7, s32 arg8);
void *memcpy(void *, const void *, s32);

/* spark_record_spawn's input (emit_coloured_points's S_2de4) */
typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 vel[3];
    /* 0x18 */ f32 a;
    /* 0x1C */ f32 b;
    /* 0x20 */ u8 rgba[4];
    /* 0x24 */ s32 life;
    /* 0x28 */ f32 size[2];
    /* 0x30 */ f32 z;
} SparkIn_D3C0;

/* effect3d_spawn_default parameter block (sp74) */
typedef struct {
    /* 0x00 */ u8 type;
    /* 0x02 */ s16 flags;
    /* 0x04 */ s16 life;
    /* 0x08 */ s32 w8;
    /* 0x0C */ s32 wC;
    /* 0x10 */ u8 rgba[4];
    /* 0x14 */ f32 size[2];
    /* 0x1C */ f32 pos[3];
    /* 0x28 */ f32 rot[3];
    /* 0x34 */ f32 u34[3];
    /* 0x40 */ s32 w40;
    /* 0x44 */ u8 b44;
    /* 0x45 */ u8 b45;
    /* 0x46 */ u8 b46;
    /* 0x47 */ u8 b47;
} SparkSpec_D3C0;

/* the 0x40 bytes copied to the record's +0x110 (sp34) */
typedef struct {
    /* 0x00 */ f32 vel[3];
    /* 0x0C */ f32 b;
    /* 0x10 */ f32 a;
    /* 0x14 */ f32 spin[3];
    /* 0x20 */ f32 u20;         // never set (stack garbage, as in the asm)
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 u28;
    /* 0x2C */ f32 u2C;
    /* 0x30 */ f32 u30;
    /* 0x34 */ f32 u34;
    /* 0x38 */ f32 u38;
    /* 0x3C */ f32 z;
} SparkExtra_D3C0;

// spark_record_spawn: spawns one type 0x57 effect record (effect3d_spawn_default, flags 0x2D03, 0xC03E1) for emit_coloured_points's
// spark description: life, colour (alpha 0xFF; the 4th byte goes to +0x44), size and position from `in`, a random
// orientation (0..360 each axis). The record's +0x110 block gets in's velocity, b, a, z and random spins
// ((rand * 20000 - 10000) / 1000 per axis) and rates. room / group go to the spawner's last two arguments.
// The asm returns the record; every caller ignores it (void as in their prototypes).
/* was func_150CD3C0 */
void spark_record_spawn(SparkIn_D3C0 *in, u8 room, u8 group) {
    SparkExtra_D3C0 x;
    SparkSpec_D3C0 s;
    u8 *rec;

    s.type = 0x57;
    s.flags = 0x2D03;
    s.w8 = 0;
    s.wC = 0;
    s.life = in->life;
    s.rgba[0] = in->rgba[0];
    s.rgba[1] = in->rgba[1];
    s.rgba[3] = 0xFF;
    s.rgba[2] = in->rgba[2];
    s.size[0] = in->size[0];
    s.size[1] = in->size[1];
    s.pos[0] = in->pos[0];
    s.pos[1] = in->pos[1];
    s.pos[2] = in->pos[2];
    s.rot[0] = random_float() * 360.0f;
    s.rot[1] = random_float() * 360.0f;
    s.rot[2] = random_float() * 360.0f;
    s.w40 = 0xC03E1;
    s.u34[0] = 0.0f;
    s.u34[1] = 0.0f;
    s.u34[2] = 0.0f;
    s.b45 = 0xFF;
    s.b46 = 0;
    s.b47 = 6;
    s.b44 = in->rgba[3];
    x.vel[0] = in->vel[0];
    x.vel[1] = in->vel[1];
    x.vel[2] = in->vel[2];
    x.z = in->z;
    x.a = in->a;
    x.b = in->b;
    x.spin[0] = (random_float() * 20000.0f - 10000.0f) * 0.001f;
    x.spin[1] = (random_float() * 20000.0f - 10000.0f) * 0.001f;
    x.u24 = 0.0f;
    x.spin[2] = (random_float() * 20000.0f - 10000.0f) * 0.001f;
    x.u28 = (random_float() * 206.0f + 58.0f) * 0.001f;
    x.u30 = 0.0f;
    x.u2C = random_float() * 360.0f;
    x.u34 = random_float() * 1210.0f * 0.0001f;
    x.u38 = (random_float() * 12960.0f + 15241.0f) * 0.0001f;
    rec = (u8 *) effect3d_spawn_default((s32) &s, 0x13, 0x1E, 0, 0x11, 0, 0x40, room, group);
    if (rec != NULL) {
        memcpy(rec + 0x110, &x, sizeof(x));
    }
}

void vec3_from_angles_rad(f32, f32, f32, void *);

/* was func_150CD68C */
s32 spark_record_update_motion(u8 *arg0) {
    u8 *sp20;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f12;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f16;
    f32 var_f16_2;
    f32 var_f18;
    f32 var_f18_2;
    f32 var_f18_3;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *temp_v1_3;

    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x114));
    temp_f12 = (*(f32 *)((u8 *)arg0 + 0x11C));
    (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x34)) + ((*(f32 *)((u8 *)arg0 + 0x110)) * g_frame_step_f));
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((temp_f2 * g_frame_step_f) + (0.5f * temp_f12 * g_frame_step_f * g_frame_step_f)));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + ((*(f32 *)((u8 *)arg0 + 0x118)) * g_frame_step_f));
    (*(f32 *)((u8 *)arg0 + 0x114)) = (f32) (temp_f2 + (temp_f12 * g_frame_step_f));
    var_v0 = g_frame_ticks;
    if (var_v0 != 0) {
        temp_a1 = -(var_v0 & 3);
        temp_a0 = temp_a1 + var_v0;
        if (temp_a1 != 0) {
            temp_v1 = arg0 + 0x110;
            temp_f0 = (*(f32 *)((u8 *)temp_v1 + 0x10));
            var_v0 -= 1;
            var_f18 = (*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0;
            var_f16 = (*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0;
            if (temp_a0 != var_v0) {
                do {
                    (*(f32 *)((u8 *)temp_v1 + 0)) = var_f18;
                    (*(f32 *)((u8 *)temp_v1 + 8)) = var_f16;
                    var_f18 = (*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0;
                    var_v0 -= 1;
                    var_f16 = (*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0;
                } while (temp_a0 != var_v0);
            }
            (*(f32 *)((u8 *)temp_v1 + 0)) = var_f18;
            (*(f32 *)((u8 *)temp_v1 + 8)) = var_f16;
            if (var_v0 != 0) {
                goto block_5;
            }
        } else {
block_5:
            temp_v1_2 = arg0 + 0x110;
            temp_f0_2 = (*(f32 *)((u8 *)temp_v1_2 + 0x10));
            var_v0_2 = var_v0 - 4;
            var_f16_2 = (*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2;
            if (var_v0_2 != 0) {
                do {
                    (*(f32 *)((u8 *)temp_v1_2 + 0)) = var_f16_2;
                    var_v0_2 -= 4;
                    (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1_2 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1_2 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1_2 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2);
                    var_f16_2 = (*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2;
                    (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
                } while (var_v0_2 != 0);
            }
            (*(f32 *)((u8 *)temp_v1_2 + 0)) = var_f16_2;
            (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
        }
    }
    temp_v1_3 = arg0 + 0x110;
    if ((*(f32 *)((u8 *)temp_v1_3 + 4)) > 0.0f) {
        var_v0_3 = g_frame_ticks;
        if (var_v0_3 != 0) {
            temp_a1_2 = -(var_v0_3 & 3);
            temp_f0_3 = (*(f32 *)((u8 *)temp_v1_3 + 0x10));
            if (temp_a1_2 != 0) {
                temp_a0_2 = temp_a1_2 + var_v0_3;
                var_v0_3 -= 1;
                var_f18_2 = (*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3;
                if (temp_a0_2 != var_v0_3) {
                    do {
                        (*(f32 *)((u8 *)temp_v1_3 + 4)) = var_f18_2;
                        var_v0_3 -= 1;
                        var_f18_2 = (*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3;
                    } while (temp_a0_2 != var_v0_3);
                }
                (*(f32 *)((u8 *)temp_v1_3 + 4)) = var_f18_2;
                if (var_v0_3 != 0) {
                    goto block_14;
                }
            } else {
block_14:
                var_v0_4 = var_v0_3 - 4;
                var_f18_3 = (*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3;
                if (var_v0_4 != 0) {
                    do {
                        (*(f32 *)((u8 *)temp_v1_3 + 4)) = var_f18_3;
                        var_v0_4 -= 4;
                        (*(f32 *)((u8 *)temp_v1_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3);
                        (*(f32 *)((u8 *)temp_v1_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3);
                        (*(f32 *)((u8 *)temp_v1_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3);
                        var_f18_3 = (*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3;
                    } while (var_v0_4 != 0);
                }
                (*(f32 *)((u8 *)temp_v1_3 + 4)) = var_f18_3;
                (*(f32 *)((u8 *)temp_v1_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3);
                (*(f32 *)((u8 *)temp_v1_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3);
                (*(f32 *)((u8 *)temp_v1_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3);
            }
        }
    }
    temp_f2_2 = (*(f32 *)((u8 *)temp_v1_3 + 0x3C));
    if ((*(f32 *)((u8 *)temp_v1_3 + 4)) < temp_f2_2) {
        (*(f32 *)((u8 *)temp_v1_3 + 4)) = temp_f2_2;
    }
    if ((*(f32 *)((u8 *)temp_v1_3 + 4)) < 0.0f) {
        sp20 = temp_v1_3;
        vec3_from_angles_rad((*(f32 *)((u8 *)temp_v1_3 + 0x2C)), ((*(f32 *)((u8 *)temp_v1_3 + 0x38)) * sinf((*(f32 *)((u8 *)temp_v1_3 + 0x30)))) + 1.5707964f, (*(f32 *)((u8 *)temp_v1_3 + 0x24)), arg0 + 0x4C);
        (*(f32 *)((u8 *)temp_v1_3 + 0x24)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 0x24)) + ((*(f32 *)((u8 *)temp_v1_3 + 0x28)) * g_frame_step_f));
        (*(f32 *)((u8 *)temp_v1_3 + 0x30)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 0x30)) + ((*(f32 *)((u8 *)temp_v1_3 + 0x34)) * g_frame_step_f));
        if ((*(f32 *)((u8 *)temp_v1_3 + 0x30)) > 6.2831855f) {
            do {
                (*(f32 *)((u8 *)temp_v1_3 + 0x30)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 0x30)) - 6.2831855f);
            } while ((*(f32 *)((u8 *)temp_v1_3 + 0x30)) > 6.2831855f);
        }
        if ((*(f32 *)((u8 *)temp_v1_3 + 0x30)) < 0.0f) {
            do {
                (*(f32 *)((u8 *)temp_v1_3 + 0x30)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 0x30)) + 6.2831855f);
            } while ((*(f32 *)((u8 *)temp_v1_3 + 0x30)) < 0.0f);
        }
    }
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x40)) + (*(f32 *)((u8 *)temp_v1_3 + 0x14)));
    (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x44)) + (*(f32 *)((u8 *)temp_v1_3 + 0x18)));
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x48)) + (*(f32 *)((u8 *)temp_v1_3 + 0x1C)));
    return 1;
}
void vtx_slot_buffer_get(void *, s16, s32, void *, u8 *);
void *memcpy(void *, const void *, s32);

// sprite_quad_build: entry of the D_8008A1E0 draw table (`s16 *(u8 *, s16 slot)`, same family as beam_quad_build).
// Gets 0x40 bytes of vertices for the view slot from the record's buffers at +0x100 (vtx_slot_buffer_get; on a fresh
// buffer the matrix at +0xC0 is copied into both halves of it) and returns them (NULL when none). The four corners
// (+/- half width +0x2C, +/- half height +0x30, z 0) are rotated by the angles +0x40 / +0x44 / +0x48
// (mtxf_rotate_xyz_deg / mtxf_transform_point) and stored as s16 x, y, z with flag 0. (The asm also sums the position +0x34 and,
// when +0x114 < 0, the offset +0x4C into a stack vector it never reads; that dead code is left out.)
/* was func_150CDAAC */
s16 *spark_record_quad_build(u8 *arg0, s16 arg1) {
    s16 *vtx;
    s16 *ret;
    u8 fresh;
    u8 *buf;
    f32 mtx[4][4];
    f32 p[4][3];
    s32 i;

    vtx_slot_buffer_get(arg0 + 0x100, arg1, 0x40, &vtx, &fresh);
    ret = vtx;
    if (vtx == NULL) {
        return NULL;
    }
    if (fresh) {
        buf = *(u8 **) (arg0 + 0x100 + arg1 * 4);
        memcpy(buf, arg0 + 0xC0, 0x40);
        memcpy(*(u8 **) (arg0 + 0x100 + arg1 * 4) + 0x40, arg0 + 0xC0, 0x40);
    }
    p[0][0] = *(f32 *) (arg0 + 0x2C);
    p[0][1] = *(f32 *) (arg0 + 0x30);
    p[0][2] = 0.0f;
    p[1][0] = -*(f32 *) (arg0 + 0x2C);
    p[1][1] = *(f32 *) (arg0 + 0x30);
    p[1][2] = 0.0f;
    p[2][0] = -*(f32 *) (arg0 + 0x2C);
    p[2][1] = -*(f32 *) (arg0 + 0x30);
    p[2][2] = 0.0f;
    p[3][0] = *(f32 *) (arg0 + 0x2C);
    p[3][1] = -*(f32 *) (arg0 + 0x30);
    p[3][2] = 0.0f;
    mtxf_rotate_xyz_deg(mtx, *(f32 *) (arg0 + 0x40), *(f32 *) (arg0 + 0x44), *(f32 *) (arg0 + 0x48));
    for (i = 0; i < 4; i++) {
        mtxf_transform_point(mtx, p[i][0], p[i][1], 0.0f, &p[i][0], &p[i][1], &p[i][2]);
        vtx[0] = (s32) p[i][0];
        vtx[1] = (s32) p[i][1];
        vtx[2] = (s32) p[i][2];
        vtx[3] = 0;
        vtx += 8;
    }
    return ret;
}

void vec2_from_angle_rad(f32, f32, f32 *, f32 *);
void emit_coloured_points(u8 *arg0, u8 arg1, s32 arg2);
extern f32 g_shooting_star_lanes[5];   /* base angles (radians) of the five shooting-star lanes; was D_80088C14 */
extern f32 g_shooting_star_k_0b24, g_shooting_star_k_0b28, g_shooting_star_k_0b2c; /* was D_800A0B24; was D_800A0B28; was D_800A0B2C */
extern f64 g_shooting_star_k_0b30, g_shooting_star_k_0b38; /* was D_800A0B30; was D_800A0B38 */
extern f32 g_shooting_star_k_0b40, g_shooting_star_deg_to_rad, g_shooting_star_k_0b48, g_shooting_star_k_0b4c, g_shooting_star_k_0b50, g_shooting_star_k_0b54, g_shooting_star_k_0b58, g_shooting_star_k_0b5c; /* was D_800A0B40; was D_800A0B44; was D_800A0B48; was D_800A0B4C; was D_800A0B50; was D_800A0B54; was D_800A0B58; was D_800A0B5C */
extern f32 g_shooting_star_k_0b60, g_shooting_star_k_0b64, g_shooting_star_k_0b68, g_shooting_star_k_0b6c, g_shooting_star_k_0b70; /* was D_800A0B60; was D_800A0B64; was D_800A0B68; was D_800A0B6C; was D_800A0B70 */

// shooting_star_sky_update: sky effect object. Its accumulator (+0x28) grows by g_shooting_star_k_0b24 * frame time * rate
// (+0x2C); every whole unit picks one of the five lane angles g_shooting_star_lanes (+ random * g_shooting_star_k_0b40) and, when that
// direction is within g_shooting_star_k_0b48 of the current camera heading (camera +0x380 - 180, wrapped to 0..360, times
// g_shooting_star_deg_to_rad = degrees to radians), spawns a streak (emit_coloured_points) placed by vec2_from_angle_rad at a random distance
// (g_shooting_star_k_0b30 + random * g_shooting_star_k_0b38) and height (500 + g_shooting_star_k_0b50 + random * g_shooting_star_k_0b4c).
/* was func_150CDD08 */
void shooting_star_sky_update(u8 *obj) {
    struct {
        s32 type;
        s32 life;
        f32 x;
        f32 y;
        f32 z;
        s16 rot;
        s16 unk16;
        s16 unk18;
        s16 unk1A;
        f32 unk1C;
        f32 unk20;
        f32 unk24;
        f32 unk28;
        f32 unk2C;
        u8 unk30;
        u8 pad31;
        s16 unk32;
        s16 unk34;
        u8 pad36[2];
        f32 unk38;
        f32 unk3C;
        f32 unk40;
        f32 unk44;
        f32 unk48;
    } spr;
    f32 lanes[5];
    f32 ang, h, r;
    u8 k;

    *(f32 *) (obj + 0x28) += g_shooting_star_k_0b24 * g_frame_step_f * *(f32 *) (obj + 0x2C);
    if (!(1.0f < *(f32 *) (obj + 0x28))) {
        return;
    }
    spr.unk18 = -0x17;
    spr.unk1A = 6;
    spr.unk30 = 0;
    spr.unk24 = g_shooting_star_k_0b28;
    spr.unk48 = g_shooting_star_k_0b2c;
    do {
        lanes[0] = g_shooting_star_lanes[0];
        lanes[1] = g_shooting_star_lanes[1];
        lanes[2] = g_shooting_star_lanes[2];
        lanes[3] = g_shooting_star_lanes[3];
        lanes[4] = g_shooting_star_lanes[4];
        k = (u32) random_int() % 5;
        ang = random_float() * g_shooting_star_k_0b40 + lanes[k];
        h = *(f32 *) ((u8 *) g_player_views + g_cur_view_player * 0x9A0 + 0x380) - 180.0f;
        while (360.0f < h) {
            h -= 360.0f;
        }
        while (h < 0.0f) {
            h += 360.0f;
        }
        if (fabsf(ang - h * g_shooting_star_deg_to_rad) < g_shooting_star_k_0b48) {
            r = random_float();
            spr.y = r * g_shooting_star_k_0b4c + g_shooting_star_k_0b50 + 500.0f;
            vec2_from_angle_rad(ang, (f32) (r * g_shooting_star_k_0b38 + g_shooting_star_k_0b30), &spr.x, &spr.z);
            spr.type = 0xF;
            spr.life = 0x14;
            spr.unk16 = 0xC;
            spr.unk32 = 0x226;
            spr.unk34 = 0;
            spr.unk3C = 15.0f;
            spr.unk38 = 15.0f;
            spr.unk44 = g_shooting_star_k_0b54;
            spr.unk40 = g_shooting_star_k_0b54;
            spr.unk1C = g_shooting_star_k_0b64;
            spr.unk20 = g_shooting_star_k_0b68;
            spr.unk28 = g_shooting_star_k_0b6c;
            spr.unk2C = g_shooting_star_k_0b70;
            spr.rot = (s32) (((ang + g_shooting_star_k_0b58) - g_shooting_star_k_0b5c) * g_shooting_star_k_0b60);
            emit_coloured_points((u8 *) &spr, obj[0xC], obj[1]);
        }
        *(f32 *) (obj + 0x28) -= 1.0f;
    } while (1.0f < *(f32 *) (obj + 0x28));
}

/* was func_150CE07C */
void shooting_star_set_rate(s32 arg0) {
    u8 *temp_v1;

    if ((arg0 >= 0) && (arg0 < 0x100) && (g_shooting_star_obj != NULL)) {
        temp_v1 = g_shooting_star_obj + 0x28;
        *(f32 *)(temp_v1 + 4) = arg0 * g_shooting_star_rate_scale;
    }
}
