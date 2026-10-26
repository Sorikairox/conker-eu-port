#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void emit_sparks_by_angles(u8 *arg0, s32 arg1, s32 arg2);
extern s32 g_projectile_break_sfx[2]; /* break sound ids; was D_80088AD4 */
extern s32 g_projectile_bounce_sfx;    /* bounce sound id; was D_80088ADC */
void *memcpy(void *, const void *, s32);

/* rodata copies (NM link drops the asm rodata) */
static const f32 D_800A0180_c[1] = { 0.001f }; /* 0x3A83126F */
static const f32 D_800A0184_c[1] = { 1e-05f }; /* 0x3727C5AC */
static const f32 D_800A0188_c[1] = { 0.661f }; /* 0x3F29374C */

/* effect3d_spawn_oriented record (0x58 bytes) */
typedef struct {
    /* 0x00 */ u8 u00;
    /* 0x01 */ u8 u01;
    /* 0x02 */ s16 u02;
    /* 0x04 */ s16 u04;
    /* 0x06 */ u8 pad06[2];
    /* 0x08 */ s32 u08;
    /* 0x0C */ s32 u0C;
    /* 0x10 */ u8 colour[4];
    /* 0x14 */ f32 scale[2];
    /* 0x1C */ f32 pos[3];
    /* 0x28 */ f32 u28[6];
    /* 0x40 */ s32 u40;
    /* 0x44 */ u8 u44[4];
    /* 0x48 */ u8 pad48[8];
    /* 0x50 */ s32 u50;
    /* 0x54 */ s16 u54;
    /* 0x56 */ s16 u56;
} Rec8EC0A;

/* emit_sparks_by_angles burst request (0x88 bytes) */
typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 u0C;
    /* 0x10 */ f32 u10;
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ s16 u24[10];
    /* 0x38 */ u8 u38;
    /* 0x39 */ u8 u39;
    /* 0x3A */ u8 u3A;
    /* 0x3B */ u8 pad3B;
    /* 0x3C */ s32 u3C;
    /* 0x40 */ s32 u40[5];
    /* 0x54 */ u8 u54;
    /* 0x55 */ u8 u55;
    /* 0x56 */ u8 u56;
    /* 0x57 */ u8 pad57;
    /* 0x58 */ s32 u58;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ s32 u60;
    /* 0x64 */ s32 u64;
    /* 0x68 */ s32 u68;
    /* 0x6C */ s32 u6C;
    /* 0x70 */ s32 u70;
    /* 0x74 */ s32 u74;
    /* 0x78 */ s32 u78;
    /* 0x7C */ u8 u7C;
    /* 0x7D */ u8 u7D;
    /* 0x7E */ u8 pad7E[2];
    /* 0x80 */ s16 u80;
    /* 0x82 */ s16 u82;
    /* 0x84 */ s32 u84;
} Burst8EC0B;

// projectile_bounce_update: handler (g_mdl_particle_land_fns table: obj, x, y, z, w, ext; returns keep). +0x3C = +0x10 + w.
// Speed +0x140 <= 15: stops (+0x72 / +0x78 = 1, low byte of +0x60 cleared), turns the velocity (0, 0, 200) by
// mtxf_rotate_xyz_deg(+0x20, +0x24, +0x28) into +0x20..+0x28 and adds +0x38..+0x40 (keep). Speed > 30: breaks: a
// effect3d_spawn_oriented flash record at (x, w, z) (random size, gets an 8-byte random spin at +0x128 of the new record), a
// emit_sparks_by_angles burst, a random break sound (g_projectile_break_sfx) at +0x38..+0x40; returns 0. Otherwise bounces: scales
// +0x44..+0x58 by +0x14 (flipping +0x48) and plays g_projectile_bounce_sfx (keep).
/* was func_150B8EC0 */
s32 projectile_bounce_update(u8 *obj, f32 x, f32 y, f32 z, f32 w, u8 *ext) {
    f32 mtx[4][4];
    Burst8EC0B b;
    f32 spin[2];
    Rec8EC0A a;
    f32 speed;
    f32 k;
    s32 r0, r1, r2;
    u8 *rec;

    *(f32 *) (obj + 0x3C) = *(f32 *) (obj + 0x10) + w;
    speed = *(f32 *) (obj + 0x140);
    if (!(15.0f < speed)) {
        obj[0x72] = 1;
        obj[0x78] = 1;
        *(s32 *) (obj + 0x60) &= ~0xFF;
        mtxf_rotate_xyz_deg(mtx, *(f32 *) (obj + 0x20), *(f32 *) (obj + 0x24), *(f32 *) (obj + 0x28));
        mtxf_transform_point(mtx, 0.0f, 0.0f, 200.0f, (f32 *) (obj + 0x20), (f32 *) (obj + 0x24), (f32 *) (obj + 0x28));
        *(f32 *) (obj + 0x20) += *(f32 *) (obj + 0x38);
        *(f32 *) (obj + 0x24) += *(f32 *) (obj + 0x3C);
        *(f32 *) (obj + 0x28) += *(f32 *) (obj + 0x40);
        return 1;
    }
    if (30.0f < speed) {
        a.u54 = 0x19;
        a.u56 = 0xA;
        a.u00 = 4;
        a.u01 = 0;
        a.u02 = 0x3B02;
        a.u04 = (u32) random_int() % 31 + 40;
        a.u08 = 0;
        a.u0C = 0;
        a.colour[0] = 0xFF;
        a.colour[1] = 0xFF;
        a.colour[2] = 0xFF;
        a.colour[3] = 0xFF;
        k = (random_float() * 25.0f + 25.0f) * D_800A0180_c[0];
        a.u44[0] = 0xFF;
        a.u44[1] = 0xFF;
        a.u44[2] = 0;
        a.u44[3] = 7;
        a.u40 = 0x0C5C0001;
        a.pos[0] = x;
        a.scale[0] = k;
        a.scale[1] = k;
        a.u28[0] = 0.0f;
        a.u28[1] = 0.0f;
        a.u28[2] = 0.0f;
        a.u28[3] = 0.0f;
        a.u28[4] = 0.0f;
        a.u28[5] = 0.0f;
        a.pos[1] = w;
        a.pos[2] = z;
        spin[0] = (random_float() * 80.0f + 50.0f) * D_800A0184_c[0];
        a.u50 = *(s32 *) (obj + 0x128);
        r0 = random_int();
        r1 = random_int();
        r2 = random_int();
        rec = (u8 *) effect3d_spawn_oriented((s32) &a, (s32) &g_effect3d_default_params, 0x18, 0, 0, (r0 & 1) * 2 + (r1 & 1), r2 & 0xFF, 500.0f,
                                   500.0f, 0, (s32) ext, *(s32 *) (obj + 0x14C), *(s32 *) (obj + 0x168), 0, 8,
                                   obj[0xC], obj[1]);
        if (rec != NULL) {
            memcpy(rec + 0x128, spin, 8);
        }
        b.pos[0] = x;
        b.u0C = 3.0f;
        b.u10 = 3.0f;
        b.u1C = 10.0f;
        b.u20 = 10.0f;
        b.u24[2] = 0;
        b.u24[0] = 6;
        b.u24[1] = 6;
        b.u24[3] = 0xFF;
        b.u24[4] = -0x3F;
        b.u24[5] = 0x1D;
        b.u24[6] = 3;
        b.u24[7] = 3;
        b.u24[8] = 0x32;
        b.u24[9] = 0x14;
        b.u38 = 1;
        b.u39 = 0x21;
        b.u3A = 0x48;
        b.u3C = 1;
        b.u40[0] = 0;
        b.u40[1] = 0;
        b.u40[2] = 0;
        b.u40[3] = 0;
        b.u40[4] = 0;
        b.u54 = 0;
        b.u55 = 0x9B;
        b.u56 = 0x64;
        b.pos[1] = w;
        b.pos[2] = z;
        b.u14 = D_800A0188_c[0];
        b.u18 = 0.0f;
        b.u58 = *(s32 *) (obj + 0x14C);
        b.u60 = 0;
        b.u64 = 0x220005;
        b.u68 = 0x1D0600;
        b.u6C = 1;
        b.u70 = 0x3B;
        b.u74 = 0x80;
        b.u78 = 0x20;
        b.u7C = 0;
        b.u7D = 7;
        b.u80 = 0xA;
        b.u82 = 0x19;
        b.u5C = *(s32 *) (obj + 0x168);
        b.u84 = *(s32 *) (obj + 0x128);
        emit_sparks_by_angles((u8 *) &b, obj[0xC], obj[1]);
        sound_play_at(g_projectile_break_sfx[random_int() & 1], 0x7D00, 0, 0, 0, *(f32 *) (obj + 0x38), w + 25.0f,
                      *(f32 *) (obj + 0x40), 1000, 4000);
        return 0;
    }
    k = *(f32 *) (obj + 0x14);
    *(f32 *) (obj + 0x44) *= k;
    *(f32 *) (obj + 0x48) = -*(f32 *) (obj + 0x48) * k;
    *(f32 *) (obj + 0x4C) *= k;
    *(f32 *) (obj + 0x50) *= k;
    *(f32 *) (obj + 0x54) *= k;
    *(f32 *) (obj + 0x58) *= k;
    sound_play_at(g_projectile_bounce_sfx, 0x7D00, 0, 0, 0, *(f32 *) (obj + 0x38), *(f32 *) (obj + 0x3C), *(f32 *) (obj + 0x40),
                  1000, 4000);
    return 1;
}

s32 trigger_point_in_kind3(s32 arg0, s16 arg1, s16 arg2, s16 arg3);
s32 collision_ray_cast(f32, f32, f32, f32, f32, f32, s32, void *, f32 *, f32 *, f32 *, s32, s32 *, s32, f32);
s32 prop_is_flagged(s32);
void emit_sparks_from_surface(u8 *arg0, s32 arg1, s32 arg2);

/* rodata copies (NM link drops the asm rodata) */
static const f32 D_800A018C_c[1] = { 0.001f };      /* 0x3A83126F */
static const f32 D_800A0190_c[1] = { 1e-05f };      /* 0x3727C5AC */
static const f32 D_800A0194_c[1] = { 0.26500002f }; /* 0x3E87AE15 */
static const f32 D_800A0198_c[1] = { 0.16100001f }; /* 0x3E24DD30 */
static const f32 D_800A019C_c[1] = { 0.0053999997f }; /* 0x3BB0F27B */
static const f32 D_800A01A0_c[1] = { 0.013499999f }; /* 0x3C5D2F1A */

/* collision_ray_cast surface record (0x12 bytes) */
typedef struct {
    s16 v[9];
} Surf9424;

/* emit_sparks_from_surface burst request (0xA4 bytes) */
typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 dir[3];
    /* 0x18 */ Surf9424 surf;
    /* 0x2A */ u8 pad2A[2];
    /* 0x2C */ f32 u2C;
    /* 0x30 */ f32 u30;
    /* 0x34 */ f32 u34;
    /* 0x38 */ f32 u38;
    /* 0x3C */ f32 u3C;
    /* 0x40 */ f32 u40;
    /* 0x44 */ f32 u44;
    /* 0x48 */ s16 u48[6];
    /* 0x54 */ u8 u54;
    /* 0x55 */ u8 u55;
    /* 0x56 */ u8 u56;
    /* 0x57 */ u8 pad57;
    /* 0x58 */ s32 u58;
    /* 0x5C */ s32 u5C[5];
    /* 0x70 */ u8 u70;
    /* 0x71 */ u8 u71;
    /* 0x72 */ u8 u72;
    /* 0x73 */ u8 pad73;
    /* 0x74 */ s32 u74;
    /* 0x78 */ s32 u78;
    /* 0x7C */ s32 u7C;
    /* 0x80 */ s32 u80;
    /* 0x84 */ s32 u84;
    /* 0x88 */ s32 u88;
    /* 0x8C */ s32 u8C;
    /* 0x90 */ s32 u90;
    /* 0x94 */ s32 u94;
    /* 0x98 */ u8 u98;
    /* 0x99 */ u8 u99;
    /* 0x9A */ u8 pad9A[2];
    /* 0x9C */ s16 u9C;
    /* 0x9E */ s16 u9E;
    /* 0xA0 */ s32 uA0;
} Burst9424;

// projectile_wall_hit: handler of g_mdl_particle_wall_fns (`s32 (*)(obj, hit, x, y, z)`, slot 1; 0 = destroyed). Speed = +0x140
// - |+0x48|. Up to 6: bounces off the wall: stops x / z (+0x44 / +0x4C), keeps +0x48 (scaled by +0x14 if upwards),
// moves to the hit point (hit +0x14..+0x1C), scales +0x50..+0x58 by +0x14 and plays g_projectile_bounce_sfx (keep). Faster: breaks;
// unless trigger_point_in_kind3 rejects the hit point, ray casts back from (x, y, z) along the last move (collision_ray_cast) and at
// the hit spawns a effect3d_spawn_oriented flash (if prop_is_flagged accepts the surface; random 8-byte spin at +0x128) and a
// emit_sparks_from_surface debris burst against the move; always plays a random break sound g_projectile_break_sfx; returns 0.
/* was func_150B9424 */
s32 projectile_wall_hit(u8 *obj, u8 *hit, f32 x, f32 y, f32 z) {
    Burst9424 b;
    f32 spin[2];
    Rec8EC0A a;
    s32 surfId;
    Surf9424 surf;
    f32 hp[3];
    f32 d[3];
    f32 vy;
    f32 k;
    s32 r0, r1, r2;
    u8 *rec;

    vy = *(f32 *) (obj + 0x48);
    if (!(6.0f < *(f32 *) (obj + 0x140) - fabsf(vy))) {
        *(f32 *) (obj + 0x44) = 0.0f;
        *(f32 *) (obj + 0x4C) = 0.0f;
        if (0.0f < vy) {
            *(f32 *) (obj + 0x48) = vy * *(f32 *) (obj + 0x14);
        }
        k = *(f32 *) (obj + 0x14);
        *(f32 *) (obj + 0x38) = *(f32 *) (hit + 0x14);
        *(f32 *) (obj + 0x3C) = *(f32 *) (hit + 0x18);
        *(f32 *) (obj + 0x40) = *(f32 *) (hit + 0x1C);
        *(f32 *) (obj + 0x50) *= k;
        *(f32 *) (obj + 0x54) *= k;
        *(f32 *) (obj + 0x58) *= k;
        sound_play_at(g_projectile_bounce_sfx, 0xFA00, 0, 0, 0, *(f32 *) (hit + 0x14), *(f32 *) (hit + 0x18), *(f32 *) (hit + 0x1C),
                      1000, 4000);
        return 1;
    }
    if (trigger_point_in_kind3(1, *(f32 *) (hit + 0x14), *(f32 *) (hit + 0x18), *(f32 *) (hit + 0x1C)) == 0) {
        d[0] = *(f32 *) (obj + 0x38) - x;
        d[1] = *(f32 *) (obj + 0x3C) - y;
        d[2] = *(f32 *) (obj + 0x40) - z;
        if (collision_ray_cast(x, y, z, d[0], d[1], d[2], 0, &surf, &hp[0], &hp[1], &hp[2], 0, &surfId, 0, 0.0f) != 0) {
            if (prop_is_flagged(surfId) != 0) {
                a.u54 = 0x19;
                a.u56 = 0xA;
                a.u00 = 4;
                a.u01 = 0;
                a.u02 = 0x3B02;
                a.u04 = (u32) random_int() % 31 + 40;
                a.u08 = 0;
                a.u0C = 0;
                a.colour[0] = 0xFF;
                a.colour[1] = 0xFF;
                a.colour[2] = 0xFF;
                a.colour[3] = 0xFF;
                k = (random_float() * 25.0f + 25.0f) * D_800A018C_c[0];
                a.scale[1] = k;
                a.scale[0] = k;
                a.pos[0] = hp[0];
                a.pos[1] = hp[1];
                a.pos[2] = hp[2];
                a.u40 = 0x0C5C0001;
                a.u44[0] = 0xFF;
                a.u44[1] = 0xFF;
                a.u44[2] = 0;
                a.u44[3] = 7;
                a.u28[0] = 0.0f;
                a.u28[1] = 0.0f;
                a.u28[2] = 0.0f;
                a.u28[3] = 0.0f;
                a.u28[4] = 0.0f;
                a.u28[5] = 0.0f;
                spin[0] = (random_float() * 80.0f + 50.0f) * D_800A0190_c[0];
                a.u50 = *(s32 *) (obj + 0x128);
                r0 = random_int();
                r1 = random_int();
                r2 = random_int();
                rec = (u8 *) effect3d_spawn_oriented((s32) &a, (s32) &g_effect3d_default_params, 0x18, 0, 0, (r0 & 1) * 2 + (r1 & 1), r2 & 0xFF,
                                           500.0f, 500.0f, 0, (s32) &surf, *(s32 *) (obj + 0x14C),
                                           *(s32 *) (obj + 0x168), 0, 8, obj[0xC], obj[1]);
                if (rec != NULL) {
                    memcpy(rec + 0x128, spin, 8);
                }
            }
            b.dir[0] = -d[0];
            b.dir[1] = -d[1];
            b.dir[2] = -d[2];
            b.surf = surf;
            b.u2C = 502.0f;
            b.pos[0] = hp[0];
            b.pos[1] = hp[1];
            b.pos[2] = hp[2];
            b.u48[0] = 6;
            b.u48[1] = 6;
            b.u30 = 3.0f;
            b.u34 = 3.0f;
            b.u48[2] = 3;
            b.u48[3] = 3;
            b.u48[4] = 0x32;
            b.u48[5] = 0x14;
            b.u54 = 1;
            b.u55 = 0x21;
            b.u56 = 0x48;
            b.u58 = 1;
            b.u5C[0] = 0;
            b.u5C[1] = 0;
            b.u5C[2] = 0;
            b.u5C[3] = 0;
            b.u5C[4] = 0;
            b.u70 = 0;
            b.u71 = 0x9B;
            b.u72 = 0x64;
            b.u38 = D_800A0194_c[0];
            b.u3C = D_800A0198_c[0];
            b.u40 = D_800A019C_c[0];
            b.u44 = D_800A01A0_c[0];
            b.u74 = *(s32 *) (obj + 0x14C);
            b.u7C = 0;
            b.u80 = 0x220005;
            b.u84 = 0x1D0600;
            b.u88 = 1;
            b.u8C = 0x3B;
            b.u90 = 0x80;
            b.u94 = 0x20;
            b.u98 = 0;
            b.u99 = 7;
            b.u9C = 0xA;
            b.u9E = 0x19;
            b.u78 = *(s32 *) (obj + 0x168);
            b.uA0 = *(s32 *) (obj + 0x128);
            emit_sparks_from_surface((u8 *) &b, obj[0xC], obj[1]);
        }
    }
    sound_play_at(g_projectile_break_sfx[random_int() & 1], 0x7D00, 0, 0, 0, *(f32 *) (obj + 0x38), *(f32 *) (obj + 0x3C),
                  *(f32 *) (obj + 0x40), 1000, 4000);
    return 0;
}

/* was func_150B9A40 */
s32 fx_rise_grow_update(u8 *arg0) {
    f32 *temp_v0;

    if ((*(s16 *)((u8 *)arg0 + 0x1C)) < 0x50) {
        temp_v0 = arg0 + 0x110;
        *temp_v0 += 0.3f * g_frame_step_f;
        (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) - *temp_v0);
    }
    if ((*(s16 *)((u8 *)arg0 + 0x1C)) >= 0x73) {
        (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x2C)) * 1.35f);
        (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x30)) * 1.35f);
        return 1;
    }
    if ((*(s16 *)((u8 *)arg0 + 0x1C)) < 0x41) {
        (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x30)) + 1.2f);
    }
    return 1;
}
/* was func_150B9ADC */
s32 fx_fade_in_alpha_update(u8 *arg0) {
    s16 temp_v0 = *(s16 *)(arg0 + 0x1C);
    if (temp_v0 < 32) {
        arg0[0x5C] = temp_v0 * 8;
    }
    return 1;
}

/* was func_150B9AFC */
s32 fx_fade_in_28_update(struct102 *arg0) {
    s16 temp_v0 = arg0->unk1C;
    if (temp_v0 < 64) {
        arg0->unk28 = temp_v0 * 4;
    }
    return 1;
}

s32 collision_floor_probe(f32 *, s32, f32, f32 *);
void emit_sparks_by_angles(u8 *arg0, s32 arg1, s32 arg2);
extern s32 g_thrown_land_sfx;    /* landing sound id; was D_80088AE0 */
void *memcpy(void *, const void *, s32);

/* rodata copies (NM link drops the asm rodata) */
static const f32 D_800A01B0_c[1] = { 2500.0f };   /* 0x451C4000 */
static const f32 D_800A01B4_c[1] = { 1.3f };      /* 0x3FA66666 */
static const f32 D_800A01B8_c[1] = { 1.3f };      /* 0x3FA66666 */
static const f32 D_800A01BC_c[1] = { 0.001f };    /* 0x3A83126F */
static const f32 D_800A01C0_c[1] = { 1e-05f };    /* 0x3727C5AC */
static const f32 D_800A01C4_c[1] = { 3.1000001f }; /* 0x40466667 */
static const f32 D_800A01C8_c[1] = { 0.70500004f }; /* 0x3F347AE2 */
static const f32 D_800A01CC_c[1] = { 0.31f };     /* 0x3E9EB852 */
static const f32 D_800A01D0_c[1] = { 0.2f };      /* 0x3E4CCCCD */

/* effect3d_spawn_oriented record (0x58 bytes; as Rec8EC0A) */
typedef struct {
    /* 0x00 */ u8 u00;
    /* 0x01 */ u8 u01;
    /* 0x02 */ s16 u02;
    /* 0x04 */ s16 u04;
    /* 0x06 */ u8 pad06[2];
    /* 0x08 */ s32 u08;
    /* 0x0C */ s32 u0C;
    /* 0x10 */ u8 colour[4];
    /* 0x14 */ f32 scale[2];
    /* 0x1C */ f32 pos[3];
    /* 0x28 */ f32 u28[6];
    /* 0x40 */ s32 u40;
    /* 0x44 */ u8 u44[4];
    /* 0x48 */ u8 pad48[8];
    /* 0x50 */ s32 u50;
    /* 0x54 */ s16 u54;
    /* 0x56 */ s16 u56;
} Rec9B1CA;

/* emit_sparks_by_angles burst request (0x88 bytes; as Burst8EC0B) */
typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 u0C;
    /* 0x10 */ f32 u10;
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ s16 u24[10];
    /* 0x38 */ u8 u38;
    /* 0x39 */ u8 u39;
    /* 0x3A */ u8 u3A;
    /* 0x3B */ u8 pad3B;
    /* 0x3C */ s32 u3C;
    /* 0x40 */ s32 u40[5];
    /* 0x54 */ u8 u54;
    /* 0x55 */ u8 u55;
    /* 0x56 */ u8 u56;
    /* 0x57 */ u8 pad57;
    /* 0x58 */ s32 u58;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ s32 u60;
    /* 0x64 */ s32 u64;
    /* 0x68 */ s32 u68;
    /* 0x6C */ s32 u6C;
    /* 0x70 */ s32 u70;
    /* 0x74 */ s32 u74;
    /* 0x78 */ s32 u78;
    /* 0x7C */ u8 u7C;
    /* 0x7D */ u8 u7D;
    /* 0x7E */ u8 pad7E[2];
    /* 0x80 */ s16 u80;
    /* 0x82 */ s16 u82;
    /* 0x84 */ s32 u84;
} Burst9B1CB;

typedef struct {
    f32 v[3];
} Vec9B1C;

// thrown_object_land_check: per-frame check of a thrown / falling object (+0x38..+0x40 position, +0x10 radius)
// against the current holder g_holder_obj (refreshed with obj_find_by_setup_id(1) when gone or not in room 1). Inside
// radius^2 + 2500: if the holder's +0x3C is above 15, half the time it is knocked away (flags on +0x60 / +0x71..+0x78,
// velocity 1.3 * +0x3C * the sin / cos (angle_byte_cos) of the holder's heading +0x76, up 10..25, timer 300; returns
// 1). Otherwise it lands: a effect3d_spawn_oriented dust record on the ground below (collision_floor_probe, ground height kept at
// +0x110; random 8-byte spin at +0x128 of the record), a emit_sparks_by_angles burst and the g_thrown_land_sfx sound; returns 0.
// Out of range it eases +0x20..+0x28 by 0.2 towards g_holder_target_pos (the second holder g_holder_target_obj's position + 50 up)
// and returns 1.
/* was func_150B9B1C */
s32 thrown_object_land_check(u8 *obj) {
    Burst9B1CB b;
    f32 spin[2];
    Rec9B1CA a;
    f32 pos[3];
    f32 s, c;
    f32 dx, dy, dz;
    f32 k;
    s32 r0, r1, r2;
    u8 *h;
    u8 *rec;
    f32 *tgt;

    h = (u8 *) g_holder_obj;
    if (h == NULL || *(s32 *) h == 0 || h[0x3B] != 1) {
        g_holder_obj = obj_find_by_setup_id(1);
        h = (u8 *) g_holder_obj;
    }
    if (h != NULL) {
        dx = *(f32 *) (obj + 0x38) - *(f32 *) (h + 0x14);
        dy = *(f32 *) (obj + 0x3C) - *(f32 *) (h + 0x18);
        dz = *(f32 *) (obj + 0x40) - *(f32 *) (h + 0x1C);
        if (dx * dx + dy * dy + dz * dz < *(f32 *) (obj + 0x10) * *(f32 *) (obj + 0x10) + D_800A01B0_c[0]) {
            if (15.0f < *(f32 *) (h + 0x3C) && (random_int() & 1)) {
                s = angle_byte_cos(*(u16 *) ((u8 *) g_holder_obj + 0x76) >> 8);
                c = angle_byte_cos((*(u16 *) ((u8 *) g_holder_obj + 0x76) >> 8) + 0x40);
                obj[0x71] = 1;
                *(s32 *) (obj + 0x60) |= 0x7D;
                obj[0x73] = 1;
                obj[0x75] = 1;
                obj[0x78] = 0;
                *(f32 *) (obj + 0x44) = *(f32 *) ((u8 *) g_holder_obj + 0x3C) * s * D_800A01B4_c[0];
                *(f32 *) (obj + 0x48) = random_float() * 15.0f + 10.0f;
                *(s16 *) (obj + 0x64) = 0x12C;
                *(s32 *) (obj + 0x60) |= 0x80;
                *(f32 *) (obj + 0x4C) = *(f32 *) ((u8 *) g_holder_obj + 0x3C) * c * D_800A01B8_c[0];
                *(f32 *) (obj + 0x20) = 0.0f;
                *(f32 *) (obj + 0x24) = 0.0f;
                *(f32 *) (obj + 0x28) = 0.0f;
                return 1;
            }
            pos[0] = *(f32 *) (obj + 0x38);
            pos[1] = *(f32 *) (obj + 0x3C) + 100.0f;
            pos[2] = *(f32 *) (obj + 0x40);
            if (collision_floor_probe(pos, 0, *(f32 *) (obj + 0x3C) - 2000.0f, (f32 *) (obj + 0x110)) != 0) {
                pos[1] = *(f32 *) (obj + 0x110);
                a.u54 = 0x19;
                a.u56 = 0xA;
                a.u00 = 4;
                a.u01 = 0;
                a.u02 = 0x3B02;
                a.u04 = (u32) random_int() % 31 + 40;
                a.u08 = 0;
                a.u0C = 0;
                a.colour[0] = 0xFF;
                a.colour[1] = 0xFF;
                a.colour[2] = 0xFF;
                a.colour[3] = 0xFF;
                k = (random_float() * 25.0f + 25.0f) * D_800A01BC_c[0];
                a.scale[1] = k;
                a.scale[0] = k;
                *(Vec9B1C *) a.pos = *(Vec9B1C *) pos;
                a.u40 = 0x0C5C0001;
                a.u44[0] = 0xFF;
                a.u44[1] = 0xFF;
                a.u44[2] = 0;
                a.u44[3] = 7;
                a.u28[0] = 0.0f;
                a.u28[1] = 0.0f;
                a.u28[2] = 0.0f;
                a.u28[3] = 0.0f;
                a.u28[4] = 0.0f;
                a.u28[5] = 0.0f;
                spin[0] = (random_float() * 80.0f + 50.0f) * D_800A01C0_c[0];
                a.u50 = *(s32 *) (obj + 0x128);
                r0 = random_int();
                r1 = random_int();
                r2 = random_int();
                rec = (u8 *) effect3d_spawn_oriented((s32) &a, (s32) &g_effect3d_default_params, 0x18, 0, 0, (r0 & 1) * 2 + (r1 & 1), r2 & 0xFF,
                                           500.0f, 500.0f, 0, (s32) (obj + 0x114), *(s32 *) (obj + 0x14C),
                                           *(s32 *) (obj + 0x168), 0, 8, obj[0xC], obj[1]);
                if (rec != NULL) {
                    memcpy(rec + 0x128, spin, 8);
                }
            }
            *(Vec9B1C *) b.pos = *(Vec9B1C *) (obj + 0x38);
            b.u0C = 3.0f;
            b.u10 = D_800A01C4_c[0];
            b.u24[0] = 6;
            b.u24[1] = 6;
            b.u24[3] = 0xFF;
            b.u24[4] = -0x40;
            b.u24[5] = 0x1E;
            b.u24[2] = 0;
            b.u24[6] = 3;
            b.u24[7] = 3;
            b.u24[8] = 0x1E;
            b.u24[9] = 0x14;
            b.u38 = 1;
            b.u39 = 0x21;
            b.u3A = 0x48;
            b.u3C = 1;
            b.u40[0] = 0;
            b.u40[1] = 0;
            b.u40[2] = 0;
            b.u40[3] = 0;
            b.u40[4] = 0;
            b.u54 = 0;
            b.u55 = 0x9A;
            b.u56 = 0x65;
            b.u14 = D_800A01C8_c[0];
            b.u18 = D_800A01CC_c[0];
            b.u1C = 5.0f;
            b.u20 = 7.0f;
            b.u58 = *(s32 *) (obj + 0x14C);
            b.u60 = 0;
            b.u64 = 0x220005;
            b.u68 = 0x1D0600;
            b.u6C = 1;
            b.u70 = 0x3B;
            b.u74 = 0x80;
            b.u78 = 0x20;
            b.u7C = 0;
            b.u7D = 7;
            b.u80 = 0xA;
            b.u82 = 0x19;
            b.u5C = *(s32 *) (obj + 0x168);
            b.u84 = *(s32 *) (obj + 0x128);
            emit_sparks_by_angles((u8 *) &b, obj[0xC], obj[1]);
            sound_play_at(g_thrown_land_sfx, 0x61A8, 0, 0, 0, *(f32 *) (obj + 0x38), *(f32 *) (obj + 0x3C),
                          *(f32 *) (obj + 0x40), 1000, 4000);
            return 0;
        }
    }

    h = (u8 *) g_holder_target_obj;
    if (h == NULL || *(s32 *) h == 0 || h[0x3B] != 1) {
        g_holder_target_obj = obj_find_by_setup_id(1);
        h = (u8 *) g_holder_target_obj;
    }
    tgt = (f32 *) &g_holder_target_pos;
    if (h != NULL) {
        tgt[0] = *(f32 *) (h + 0x14);
        tgt[1] = *(f32 *) (h + 0x18) + 50.0f;
        tgt[2] = *(f32 *) (h + 0x1C);
    }
    *(f32 *) (obj + 0x20) += D_800A01D0_c[0] * (tgt[0] - *(f32 *) (obj + 0x20));
    *(f32 *) (obj + 0x24) += D_800A01D0_c[0] * (tgt[1] - *(f32 *) (obj + 0x24));
    *(f32 *) (obj + 0x28) += D_800A01D0_c[0] * (tgt[2] - *(f32 *) (obj + 0x28));
    return 1;
}

/* P209: void, the caller ignores v0 */
void mtx_look_along_scaled(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32);
/* was func_150BA1F4 */
s32 fx_build_look_matrix(s32 arg0, u8 *arg1) {
    mtx_look_along_scaled(arg0, *(f32 *)(arg1 + 0x18), *(f32 *)(arg1 + 0x1C), *(f32 *)(arg1 + 0x2C), *(f32 *)(arg1 + 0x30), *(f32 *)(arg1 + 0x34), *(f32 *)(arg1 + 0x38), *(f32 *)(arg1 + 0x3C), *(f32 *)(arg1 + 0x40), *(f32 *)(arg1 + 0x20), *(f32 *)(arg1 + 0x24), *(f32 *)(arg1 + 0x28));
    return 1;
}

typedef struct { s32 u0; s16 u4; u8 u6; s32 u8; s32 uC; u8 u10; u8 u11; u8 u12; u8 u13; u8 u14; u8 u15; s32 u18; u8 pad[16]; } BA_S;
/* was func_150BA26C */
void obj_sprite_fx_spawn(u8 *arg0) {
    BA_S s;
    s32 c;
    s32 b;
    s32 a;

    if (*(s16 *)(arg0 + 0x98) == -1) {
        s.u6 = 4;
        s.u8 = 0;
        s.uC = 0;
        s.u0 = 0x11;
        s.u4 = 0x64;
        s.u10 = 0xFF;
        s.u11 = *(s32 *)(arg0 + 0x90);
        s.u12 = 0;
        s.u13 = 0;
        s.u14 = 0;
        s.u15 = 0xFF;
        s.u18 = 0x30001;
        a = random_int();
        b = random_int();
        c = random_int();
        sprite_fx_spawn_at((s32)&s, 0, 2, 0, *(s16 *)(arg0 + 0x9C), *(s16 *)(arg0 + 0xA6) + 2, *(s16 *)(arg0 + 0xA0), *(s16 *)(arg0 + 0xA2), *(s16 *)(arg0 + 0xA2), a & 0xFF, (u8)((b & 1) + (c & 1) * (a = 2)) /* fakematch: permuter, reuses a's register */, 3, 0xFF, 0, arg0[0xC], arg0[1]);
    }
}
