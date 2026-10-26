#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
extern u8 g_vec3_zero[]; /* was D_800A5860 */


s32 vec3_normalize_len(f32 *, f32 *, f32 *, s32 *);
s32 tracer_hit_update(s32, s32 *, u8 *, s32 *, s32 *, f32, s32, u8 *, s32 *, s8 *, s32, f32, u8 *, s32, s32, s32, s32, s32);
s32 vec3_make_basis(f32 *, s32 *, s32 *);
void vec3_to_yaw_pitch_deg(void *, f32 *, f32 *);
s32 mdl_particle_spawn_ex(void *, s32, s32, s32, s32, s32, s32);
s32 memcpy(s32, s32 *, s32); /* as declared later in this file */

// light_effect_spawn: the muzzle-fire light (object_muzzle_fire) and others. Optional end points: a3's point copied
// (arg4 set) or resolved by vec3_normalize_len (when a2 and a3 are given), else a1's point resolved; any failed resolve
// returns. tracer_hit_update fills the 0xB4-byte light block (from arg5, the position a0, the points, arg7 / arg8 /
// arg9 / arg10 / arg12 / arg13 / arg15 / arg17 and the option byte: arg11 -> 1, arg12 -> 2, arg13 -> 4,
// | 1 when the block's +4 exceeds 150); vec3_make_basis gives its direction. The effect (mdl_particle_spawn_ex, 0xB4 extra
// bytes, arg18 / arg19) moves from a0 along the direction x arg6, angles from vec3_to_yaw_pitch_deg, colour g_vec3_zero,
// owner arg9 (kind byte +0x3B) and, when arg16 is set, sound 0x4650 at a0 (sound_play_at = sound_voice_play_at(0, ...),
// called directly because the C sound_play_at is void and drops the handle); the light block goes to +0x170.
/* was func_150F79F0 */
void beam_light_effect_spawn(f32 *a0, void *a1, void *a2, void *a3, u8 arg4, u8 *arg5, f32 arg6, f32 arg7, f32 arg8, u8 *arg9,
                   u8 arg10, u8 arg11, u8 arg12, u8 arg13, s32 arg14, s8 arg15, s32 arg16, u8 arg17, u8 arg18,
                   s32 arg19) {
    struct {
        f32 u00[2];         /* 0x00 = 1 */
        f32 u08[2];         /* 0x08 = 0.02 */
        f32 angB;           /* 0x10, vec3_to_yaw_pitch_deg */
        f32 angA;           /* 0x14, vec3_to_yaw_pitch_deg */
        f32 u18;            /* 0x18 = 0 */
        f32 u1C[3];         /* 0x1C = 1 */
        f32 pos[3];         /* 0x28 */
        f32 vel[3];         /* 0x34 */
        f32 colour[3];      /* 0x40, g_vec3_zero */
        f32 u4C;            /* 0x4C = 0 */
        s32 u50;            /* 0x50 = 0x120 */
        s16 u54;            /* 0x54 = 300 */
        s16 u56;            /* 0x56 = 0x2F */
        u8 u58;             /* 0x58 = 0 */
        s32 u5C;            /* 0x5C = 0 */
        u8 u60[10];         /* 0x60: FF, 0x13, 0.. */
        u8 u6A;             /* 0x6A = 0 */
        u8 *owner;          /* 0x6C */
        u8 ownerKind;       /* 0x70 */
        s16 u72;            /* 0x72 = 1 */
        s16 u74;            /* 0x74 = 0xFF */
        s32 sound;          /* 0x78 */
    } fx;
    struct {
        u8 u00[4];
        f32 u04;            /* 0x04 */
        u8 u08[0x30];
        f32 dir[3];         /* 0x38, vec3_make_basis */
        u8 u44[0x20];
        s32 u64;            /* 0x64 = arg14 */
        u8 u68[4];          /* 0x68, tracer_hit_update */
        f32 u6C;            /* 0x6C = arg6 */
        u8 flags;           /* 0x70 */
        f32 u74[3];         /* 0x74, vec3_make_basis */
        f32 u80[3];         /* 0x80, vec3_make_basis */
        f32 u8C;            /* 0x8C = 0 */
        f32 u90;            /* 0x90 = 0 */
        f32 u94;            /* 0x94 = 70 arg7 */
        s32 pos[3];         /* 0x98 */
        f32 dir70[3];       /* 0xA4 */
        s8 uB0;             /* 0xB0 = arg15 */
    } lt;                   /* 0xB4 bytes */
    s32 ptA[3];
    s32 ptB[3];
    s32 hasA;
    s32 hasB;
    u8 *e;
    s32 i;

    hasA = arg4;
    hasB = 0;
    if (arg4) {
        ptA[0] = ((s32 *) a3)[0];
        ptA[1] = ((s32 *) a3)[1];
        ptA[2] = ((s32 *) a3)[2];
    }
    lt.flags = (arg13 ? 4 : 0) | (arg11 ? 1 : 0) | (arg12 ? 2 : 0);
    lt.uB0 = arg15;
    if (a2 != NULL && a3 != NULL) {
        if (!arg4) {
            if (vec3_normalize_len(a3, (f32 *) ptA, NULL, NULL) == 0) {
                return;
            }
            hasA = 1;
        }
    } else if (a1 != NULL) {
        if (vec3_normalize_len(a1, (f32 *) ptB, NULL, NULL) == 0) {
            return;
        }
        hasB = 1;
    }
    if (tracer_hit_update((s32) arg5, (s32 *) &lt, (u8 *) a0, hasB ? ptB : NULL, (s32 *) lt.u68, arg7, arg10, a2,
                      hasA ? ptA : NULL, (s8 *) &lt.flags, 1, arg8, arg9, arg15, arg12, arg13, 0, arg17) == 0) {
        return;
    }
    if (vec3_make_basis(lt.dir, (s32 *) lt.u74, (s32 *) lt.u80) == 0) {
        return;
    }
    lt.u64 = arg14;
    lt.u90 = 0.0f;
    lt.u8C = 0.0f;
    lt.u94 = 70.0f * arg7;
    lt.pos[0] = ((s32 *) a0)[0];
    lt.pos[1] = ((s32 *) a0)[1];
    lt.pos[2] = ((s32 *) a0)[2];
    lt.dir70[0] = lt.dir[0] * 70.0f;
    lt.dir70[1] = lt.dir[1] * 70.0f;
    lt.dir70[2] = lt.dir[2] * 70.0f;
    lt.u6C = arg6;
    lt.flags |= (150.0f < lt.u04) ? 1 : 0;
    fx.u00[0] = 1.0f;
    fx.u00[1] = 1.0f;
    fx.u08[1] = 0.0200000014f;
    fx.u08[0] = 0.0200000014f;
    vec3_to_yaw_pitch_deg(lt.dir, &fx.angA, &fx.angB);
    fx.u1C[0] = 1.0f;
    fx.u1C[1] = 1.0f;
    fx.u1C[2] = 1.0f;
    fx.u18 = 0.0f;
    ((s32 *) fx.pos)[0] = ((s32 *) a0)[0];
    ((s32 *) fx.pos)[1] = ((s32 *) a0)[1];
    ((s32 *) fx.pos)[2] = ((s32 *) a0)[2];
    fx.vel[0] = lt.dir[0] * arg6;
    fx.vel[1] = lt.dir[1] * arg6;
    fx.vel[2] = lt.dir[2] * arg6;
    ((s32 *) fx.colour)[0] = ((s32 *) g_vec3_zero)[0];
    ((s32 *) fx.colour)[1] = ((s32 *) g_vec3_zero)[1];
    ((s32 *) fx.colour)[2] = ((s32 *) g_vec3_zero)[2];
    fx.u50 = 0x120;
    fx.u54 = 300;
    fx.u56 = 0x2F;
    fx.u58 = 0;
    fx.u5C = 0;
    fx.u60[0] = 0xFF;
    fx.u60[1] = 0x13;
    for (i = 2; i < 9; i++) {
        fx.u60[i] = 0;
    }
    fx.u6A = 0;
    fx.u4C = 0.0f;
    fx.owner = arg9;
    fx.ownerKind = arg9[0x3B];
    fx.u72 = 1;
    fx.u74 = 0xFF;
    if (arg16 != 0) {
        fx.sound = sound_voice_play_at(0, arg16, 0x4650, -500, 0, -1, (s32) fx.pos[0], (s32) fx.pos[1], (s32) fx.pos[2],
                                 1000, 2000);
    } else {
        fx.sound = 0;
    }
    e = (u8 *) mdl_particle_spawn_ex(&fx, 0, 0, 0, 0xB4, arg18, arg19);
    if (e != NULL) {
        memcpy((s32) (e + 0x170), (s32 *) &lt, 0xB4);
    }
}

s32 ray_cast_world(struct127 *, f32, f32, f32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);
void object_take_hit(u8 *obj, u8 *attacker, u8 *pos, f32 *pos2, u8 *rec, s32 flags, f32 *dir, u8 arg7, s32 arg8);
void rocket_explode(u8 *arg0, u8 arg1, s32 arg2);

/* rodata copies (NM link drops the asm rodata) */
static const f32 D_800A1F94_c[1] = { 0.014285714f }; /* 0x3C6A0EA1, 1 / 70 */
static const f32 D_800A1F98_c[1] = { 8.318001f };    /* 0x41051688 */
static const f32 D_800A1F9C_c[1] = { 0.467f };       /* 0x3EEF1AA0 */
static const f32 D_800A1FA0_c[1] = { 6.4814816f };   /* 0x40CF684C */
static const f32 D_800A1FA4_c[1] = { 4.712389f };    /* 0x4096CBE4, 3 pi / 2 */

/* ray_cast_world hit result */
typedef struct {
    /* 0x00 */ u8 *obj;
    /* 0x04 */ u8 pad04[4];
    /* 0x08 */ u8 pos[0x18];
    /* 0x20 */ f32 pos2[3];
    /* 0x2C */ u8 pad2C[0x2D];
    /* 0x59 */ u8 count;
    /* 0x5A */ u8 pad5A[2];
} Hit7E34;

/* effect3d_spawn_full trail puff record (0x58 bytes) */
typedef struct {
    /* 0x00 */ u8 u00;
    /* 0x01 */ u8 u01;
    /* 0x02 */ s16 u02;
    /* 0x04 */ s16 u04;
    /* 0x06 */ u8 pad06[2];
    /* 0x08 */ s32 u08;
    /* 0x0C */ s32 u0C;
    /* 0x10 */ u8 colour[4];
    /* 0x14 */ f32 u14[2];
    /* 0x1C */ f32 pos[3];
    /* 0x28 */ f32 u28[3];
    /* 0x34 */ f32 scale[3];
    /* 0x40 */ s32 u40;
    /* 0x44 */ u8 u44[4];
    /* 0x48 */ s32 u48;
    /* 0x4C */ u8 u4C;
    /* 0x4D */ u8 pad4D[3];
    /* 0x50 */ s32 u50;
    /* 0x54 */ u8 pad54[4];
} Puff7E34;

/* 0x2C bytes copied to +0x110 of each puff */
typedef struct {
    /* 0x00 */ f32 u00[3];
    /* 0x0C */ f32 u0C[3];
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 u28;
} PuffExtra7E34;

// rocket_update: handler of the D_80089C80 table (`s32 (*)(u8 *)`, returns 1 while alive). Block d = +0x170. Step
// dt = frame time g_frame_step_f, capped at the remaining life d +0x68. Moves its sound (+0x88) to the position; with d
// +0x70 & 2 ray casts the move (ray_cast_world from the position along d +0x38 for d +0x6C * dt, filter
// !(d +0x70 & 4), d +0xB0): on 2+ hits applies object_take_hit (flags 0x1A, d +0x38) and, with d +0x70 & 1, explodes
// (rocket_explode) and dies. Then moves by the velocity +0x44 * dt; when not dead counts the life down (at 0 dies,
// exploding with d +0x70 & 1 at the position). Trail: d +0x8C += distance, d +0x90 += dt; every 70 units of d +0x8C
// one effect3d_spawn_full smoke puff at d +0x98 (stepped by d +0xA4, d +0x90 by d +0x94), its +0x110 extra from d
// +0x74..+0x88 and (27 - d +0x90) * 6.48 alpha.
/* was func_150F7E34 */
s32 rocket_update(u8 *obj) {
    Puff7E34 rec;
    PuffExtra7E34 extra;
    Hit7E34 hit;
    s8 alive = 1;
    u8 *d = obj + 0x170;
    struct127 *owner = *(struct127 **) (obj + 0x7C);
    f32 dt;
    f32 dist;
    f32 n;
    u8 *puff;

    dt = g_frame_step_f;
    if (*(f32 *) (d + 0x68) < dt) {
        dt = *(f32 *) (d + 0x68);
    }
    if (*(s32 *) (obj + 0x88) != 0) {
        sound_voice_update_pan(*(s32 *) (obj + 0x88), *(f32 *) (obj + 0x38), *(f32 *) (obj + 0x3C), *(f32 *) (obj + 0x40));
    }
    dist = *(f32 *) (d + 0x6C) * dt;
    if (d[0x70] & 2) {
        ray_cast_world(owner, *(f32 *) (obj + 0x38), *(f32 *) (obj + 0x3C), *(f32 *) (obj + 0x40), *(f32 *) (d + 0x38),
                      *(f32 *) (d + 0x3C), *(f32 *) (d + 0x40), (u8 *) &hit, dist, 1, 0, !(d[0x70] & 4),
                      (s8) d[0xB0], 0, 0);
        if (hit.count >= 2) {
            object_take_hit(hit.obj, (u8 *) owner, hit.pos, hit.pos2, (u8 *) &hit, 0x1A, (f32 *) (d + 0x38), obj[0xC],
                          obj[1]);
            if (d[0x70] & 1) {
                rocket_explode(hit.pos, obj[0xC], obj[1]);
            }
            alive = 0;
        }
    }
    *(f32 *) (obj + 0x38) += *(f32 *) (obj + 0x44) * dt;
    *(f32 *) (obj + 0x3C) += *(f32 *) (obj + 0x48) * dt;
    *(f32 *) (obj + 0x40) += *(f32 *) (obj + 0x4C) * dt;
    if (alive == 1) {
        *(f32 *) (d + 0x68) -= g_frame_step_f;
        if (*(f32 *) (d + 0x68) <= 0.0f) {
            alive = 0;
            if (d[0x70] & 1) {
                rocket_explode(obj + 0x38, obj[0xC], obj[1]);
            }
        }
    }
    *(f32 *) (d + 0x8C) += dist;
    *(f32 *) (d + 0x90) += dt;
    n = *(f32 *) (d + 0x8C) * D_800A1F94_c[0];
    if (1.0f < n) {
        extra.u00[0] = *(f32 *) (d + 0x74);
        extra.u00[1] = *(f32 *) (d + 0x78);
        extra.u00[2] = *(f32 *) (d + 0x7C);
        extra.u0C[0] = *(f32 *) (d + 0x80);
        extra.u0C[1] = *(f32 *) (d + 0x84);
        extra.u0C[2] = *(f32 *) (d + 0x88);
        extra.u24 = D_800A1F98_c[0];
        extra.u28 = D_800A1F98_c[0];
        rec.u00 = 0x7A;
        rec.u01 = 0;
        rec.u02 = 0x4404;
        rec.u04 = 0xA;
        rec.u08 = 0;
        rec.u0C = 0;
        rec.colour[0] = 0xFF;
        rec.colour[1] = 0xFF;
        rec.colour[2] = 0xFF;
        rec.colour[3] = 0xFF;
        rec.u14[0] = 0.0f;
        rec.u14[1] = 0.0f;
        extra.u20 = D_800A1F9C_c[0];
        rec.u28[0] = ((f32 *) g_vec3_zero)[0];
        rec.u28[1] = ((f32 *) g_vec3_zero)[1];
        rec.u28[2] = ((f32 *) g_vec3_zero)[2];
        rec.scale[0] = 1.0f;
        rec.scale[1] = 1.0f;
        rec.scale[2] = 1.0f;
        rec.u40 = 0xCC0008;
        rec.u44[1] = 0xFF;
        rec.u44[2] = 0;
        rec.u44[3] = 6;
        rec.u48 = 0;
        rec.u4C = 0xFF;
        rec.u50 = 0;
        do {
            extra.u1C = D_800A1FA4_c[0];
            extra.u18 = 27.0f - *(f32 *) (d + 0x90);
            rec.pos[0] = *(f32 *) (d + 0x98);
            rec.pos[1] = *(f32 *) (d + 0x9C);
            rec.pos[2] = *(f32 *) (d + 0xA0);
            rec.u44[0] = (u32) (extra.u18 * D_800A1FA0_c[0]);
            puff = effect3d_spawn_full(&rec, (s32) &D_800A4AA0, 0x24, 0, 0, 0x21, 0, 0, 0, 0x2C, obj[0xC], obj[1]);
            if (puff != NULL) {
                memcpy((s32) (puff + 0x110), (s32 *) &extra, 0x2C);
            }
            *(f32 *) (d + 0x8C) -= 70.0f;
            *(f32 *) (d + 0x90) -= *(f32 *) (d + 0x94);
            *(f32 *) (d + 0x98) += *(f32 *) (d + 0xA4);
            *(f32 *) (d + 0x9C) += *(f32 *) (d + 0xA8);
            *(f32 *) (d + 0xA0) += *(f32 *) (d + 0xAC);
            n -= 1.0f;
        } while (1.0f < n);
    }
    return alive;
}

extern f32 g_pulse_sprite_alpha_scale; /* was D_800A1FA8 */
/* was func_150F83A0 */
s32 pulse_sprite_update(u8 *arg0)
{
  u8 *v = arg0 + 0x110;
  f32 f;
  *((s8 *) (arg0 + 0x5C)) = (s8) ((u32) ((*((f32 *) (arg0 + 0x128))) * g_pulse_sprite_alpha_scale));
  f = (*((f32 *) (v + 0x24))) + ((*((f32 *) (v + 0x28))) * sinf(*((f32 *) (arg0 + 0x12C))));
  *((f32 *) (arg0 + 0x30)) = f;
  *((f32 *) (arg0 + 0x2C)) = f;
  *((f32 *) (v + 0x1C)) = wrap_angle_rad(((*((f32 *) (v + 0x20))) * g_frame_step_f) + (*((f32 *) (v + 0x1C))));
  *((f32 *) (v + 0x18)) = (*((f32 *) (v + 0x18))) - g_frame_step_f;
  if ((*((f32 *) (v + 0x18))) < 0.0f)
  {
    return 0;
  }
  return 1;
}

/* P224: entry of draw table g_effect3d_draw_fns, whose dispatcher (func_1513DB70 area, game_169510) uses the result: the
   matching C is void, but its compiled code returns the callee's v0, so the NM variant returns it. */
/* was func_150F84D8 */
u8 * pulse_sprite_draw(u8 *arg0, s16 arg1) {
    return (u8 *) sprite_quad_build_axes(arg0, arg0 + 0x110, arg0 + 0x11C, arg1);
}

s32 spark_shower_spawn(u8 *, f32, f32, f32, f32, u8, s32); /* P95: f32 parameter */
void muzzle_light_small_spawn(u8 *, u8, s32);

/* was func_150F850C */
void rocket_explode(u8 *arg0, u8 arg1, s32 arg2) {
    spark_shower_spawn(arg0, 9.0f + random_float() * 3.0f, 0.511905f, 70.0f + random_float() * 70.0f, 0.0f, arg1, arg2); /* P95: float literal (asm passes the bits 0x3F030C35) */
    muzzle_light_small_spawn(arg0, arg1, arg2);
}

/* P159 */
s32 mdl_particle_spawn_ex(void *, s32, s32, s32, s32, s32, s32);
extern u8 g_vec3_zero[]; /* was D_800A5860 */
s32 memcpy(s32, s32 *, s32);
// record_particle_spawn: spawns particle type 0x2F (mdl_particle_spawn_ex) lasting `life` at the record's point rec[0..2]
// with the angles rec[3..5], scale 1 / 0.02 and the colour of g_vec3_zero; the 0x14 extra bytes at +0x170 keep
// the record pointer, its point and 0.0.
/* was func_150F85AC */
void trail_follower_spawn(f32 *rec, s16 life, u8 flag, s32 arg3) {
    struct {
        /* spawn block for mdl_particle_spawn_ex (0x7C bytes) */
        f32 scale[4];
        f32 angle[3];
        f32 one[3];
        f32 pos[3];
        f32 vel[3];
        s32 color[3];
        f32 u4C;
        s32 flags50;
        s16 life;
        s16 type;
        u8 u58;
        u8 pad59[3];
        s32 u5C;
        u8 u60;
        u8 u61;
        u8 u62[7];
        u8 u69;
        u8 u6A;
        u8 pad6B;
        s32 u6C;
        u8 u70;
        u8 pad71;
        s16 u72;
        s16 u74;
        u8 pad76[2];
        s32 u78;
        /* extra data copied to particle +0x170 (0x14 bytes) */
        f32 *rec;
        f32 recPos[3];
        f32 u10;
    } sp;
    s32 i;
    s32 p;

    sp.rec = rec;
    sp.recPos[0] = rec[0];
    sp.recPos[1] = rec[1];
    sp.recPos[2] = rec[2];
    sp.u10 = 0.0f;
    sp.scale[0] = 1.0f;
    sp.scale[1] = 1.0f;
    sp.scale[2] = 0.020000001f; /* 0x3CA3D70B */
    sp.scale[3] = 0.020000001f; /* 0x3CA3D70B */
    sp.angle[0] = rec[3];
    sp.angle[1] = rec[4];
    sp.angle[2] = rec[5];
    sp.one[0] = 1.0f;
    sp.one[1] = 1.0f;
    sp.one[2] = 1.0f;
    sp.pos[0] = rec[0];
    sp.pos[1] = rec[1];
    sp.pos[2] = rec[2];
    sp.vel[0] = 0.0f;
    sp.vel[1] = 0.0f;
    sp.vel[2] = 0.0f;
    sp.color[0] = ((s32 *)g_vec3_zero)[0];
    sp.color[1] = ((s32 *)g_vec3_zero)[1];
    sp.color[2] = ((s32 *)g_vec3_zero)[2];
    sp.u4C = 0.0f;
    sp.flags50 = 0x980;
    sp.life = life;
    sp.type = 0x2F;
    sp.u58 = 0;
    sp.u5C = 0;
    sp.u60 = 0xFF;
    sp.u61 = 0x14;
    for (i = 0; i < 7; i++) {
        sp.u62[i] = 0;
    }
    sp.u6A = 0;
    sp.u6C = 0;
    sp.u70 = 0;
    sp.u72 = 1;
    sp.u74 = 0xFF;
    sp.u78 = 0;
    p = mdl_particle_spawn_ex(&sp, 3, 0xFF, 0, 0xB4, flag, arg3);
    if (p != 0) {
        memcpy(p + 0x170, (s32 *)&sp.rec, 0x14);
    }
}

s32 vec3_normalize_len(f32 *, f32 *, f32 *, s32 *);
s32 vec3_make_basis(f32 *, s32 *, s32 *);
s32 memcpy(s32, s32 *, s32);

/* was func_150F873C */
s32 trail_follower_update(u8 *arg0) {
    struct {
        s32 u98;
        u8 pad9C[0x8];
        s32 uA4;
        u8 padA8[0x8];
        f32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        s8 uC4;
        s8 uC5;
        s16 uC6;
        s16 uC8;
        u8 padCA[0x2];
        s32 uCC;
        s32 uD0;
        s8 uD4;
        s8 uD5;
        s8 uD6;
        s8 uD7;
        f32 uD8;
        f32 uDC;
        s32 uE0;
        u8 padE4[0x8];
        s32 uEC;
        u8 padF0[0x8];
        f32 uF8;
        f32 uFC;
        f32 u100;
        s32 u104;
        s8 u108;
        s8 u109;
        s8 u10A;
        s8 u10B;
        s32 u10C;
        s8 u110;
        u8 pad111[0x3];
        s32 u114;
        u8 pad118[0x8];
        f32 u120;
        f32 u124;
        u8 pad128[0x4];
        f32 u12C;
        f32 u130;
        f32 u134;
        s32 u138;
        f32 u13C;
        f32 u140;
        f32 u144;
        f32 u148;
    } sp;
    f32 sp94;
    f32 var_f20;
    u8 *temp_t4;
    u8 *temp_s0;
    u8 *temp_s5;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x170));
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) (*(f32 *)((u8 *)temp_v0 + 4));
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) (*(f32 *)((u8 *)temp_v0 + 8));
    (*(f32 *)((u8 *)arg0 + 0x20)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0xC));
    (*(f32 *)((u8 *)arg0 + 0x24)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x10));
    (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x14));
    sp.u140 = (*(f32 *)((u8 *)arg0 + 0x38)) - (*(f32 *)((u8 *)arg0 + 0x174));
    sp.u144 = (*(f32 *)((u8 *)arg0 + 0x3C)) - (*(f32 *)((u8 *)arg0 + 0x178));
    sp.u148 = (*(f32 *)((u8 *)arg0 + 0x40)) - (*(f32 *)((u8 *)arg0 + 0x17C));
    (*(f32 *)((u8 *)arg0 + 0x180)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x180)) + g_frame_step_f);
    if (vec3_normalize_len(&sp.u140, &sp.u12C, &sp.u13C, &sp.u138) != 0) {
        temp_s0 = arg0 + 0x170;
        var_f20 = sp.u13C * 0.05f;
        sp.u120 = sp.u130 * 20.0f;
        sp.u124 = sp.u134 * 20.0f;
        if (var_f20 > 1.0f) {
            sp94 = (*(f32 *)((u8 *)temp_s0 + 0x10)) / var_f20;
            vec3_make_basis(&sp.u140, &sp.u98, &sp.uA4);
            temp_t4 = ((u8 *)&g_vec3_zero);
            sp.uC4 = 0x7A;
            sp.uC5 = 0;
            sp.uC6 = 0x4404;
            sp.uC8 = 0xA;
            sp.uCC = 0;
            sp.uD0 = 0;
            sp.uD4 = 0xFF;
            sp.uD5 = 0xFF;
            sp.uD6 = 0xFF;
            sp.uD7 = 0xFF;
            sp.uB8 = 0.46300003f;
            sp.uBC = 8.241f;
            sp.uDC = 0.0f;
            sp.uD8 = 0.0f;
            sp.uC0 = 3.889f;
            (*(s32 *)((u8 *)(&sp.uEC) + 0)) = (s32) (*(s32 *)((u8 *)temp_t4 + 0));
            (*(s32 *)((u8 *)(&sp.uEC) + 4)) = (s32) (*(s32 *)((u8 *)temp_t4 + 4));
            (*(s32 *)((u8 *)(&sp.uEC) + 8)) = (s32) (*(s32 *)((u8 *)temp_t4 + 8));
            sp.uF8 = 1.0f;
            sp.uFC = 1.0f;
            sp.u100 = 1.0f;
            sp.u104 = 0xCC0008;
            sp.u109 = 0xFF;
            sp.u10A = 0;
            sp.u10B = 6;
            sp.u10C = 0;
            sp.u110 = 0xFF;
            sp.u114 = 0;
            temp_s5 = temp_s0 + 4;
            do {
                sp.uB4 = 4.712389f;
                sp.uB0 = 27.0f - (*(f32 *)((u8 *)temp_s0 + 0x10));
                (*(s32 *)((u8 *)(&sp.uE0) + 0)) = (s32) (*(s32 *)((u8 *)temp_s5 + 0));
                (*(s32 *)((u8 *)(&sp.uE0) + 4)) = (s32) (*(s32 *)((u8 *)temp_s5 + 4));
                (*(s32 *)((u8 *)(&sp.uE0) + 8)) = (s32) (*(s32 *)((u8 *)temp_s5 + 8));
                sp.u108 = (s8) (u32) (sp.uB0 * 6.4814816f);
                temp_v0_2 = effect3d_spawn_full(&sp.uC4, (s32) ((u8 *)&D_800A4AA0), 0x24U, 0U, 0U, 0x21U, 0U, 0, 0, 0x2C, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                if (temp_v0_2 != NULL) {
                    memcpy(temp_v0_2 + 0x110, &sp.u98, 0x2C);
                }
                var_f20 -= 1.0f;
                (*(f32 *)((u8 *)temp_s0 + 4)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 4)) + (sp.u12C * 20.0f));
                (*(f32 *)((u8 *)temp_s0 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 8)) + sp.u120);
                (*(f32 *)((u8 *)temp_s0 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0xC)) + sp.u124);
                (*(f32 *)((u8 *)temp_s0 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x10)) - sp94);
            } while (var_f20 > 1.0f);
        }
    }
    return 1;
}