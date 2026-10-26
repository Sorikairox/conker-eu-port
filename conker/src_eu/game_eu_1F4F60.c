#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 func_150ACEA0(f32, f32, f32, f32, f32, f32, s32, void *, f32 *, f32 *, f32 *, f32 *, s32 *, s32, f32);
u8 *laser_create(f32 *, u8 *, f32 *, u8 *, u8 *, u8 *, u8, u8, u8, u8, s16, s16, s16, u8, u8, u8, u8, u8, u8, f32, f32, u8, u8, s32);

// record_beam_start: D_80082EA0 entry 8 (level-start record). Unless rec +0x14 is 1: the segment from the record's
// point (s16 x, y, z) along the length +8 rotated by the angles +0xC / +0x10; two ray casts (func_150ACEA0) from its
// middle towards both ends give the end points (geometry hits); when both hit, laser_create builds the beam between
// them with the colour +0x1C (r, g, b bytes) and the option bits / bytes of +0x18 and +0x20. Always returns 1.
/* was func_151C7750 */
s32 laser_record_start(u8 *rec) {
    f32 m[4][4];
    f32 p0[3];
    f32 p1[3];
    f32 d[3];
    f32 mid[3];
    u8 triA[0x14];
    f32 hitA[3];
    u8 triB[0x14];
    f32 hitB[3];
    f32 distA;
    f32 distB;
    s32 auxA;
    s32 auxB;
    s32 okA;
    s32 okB;
    u32 opt;
    u32 col;
    u32 sc;

    if (rec[0x14] == 1) {
        return 1;
    }
    p0[0] = *(s16 *) (rec + 0);
    p0[1] = *(s16 *) (rec + 2);
    p0[2] = *(s16 *) (rec + 4);
    mtxf_rotate_xyz_deg(m, *(f32 *) (rec + 0xC), *(f32 *) (rec + 0x10), 0.0f);
    mtxf_transform_point(m, 0.0f, *(s16 *) (rec + 8), 0.0f, &p1[0], &p1[1], &p1[2]);
    p1[0] += p0[0];
    p1[1] += p0[1];
    p1[2] += p0[2];
    d[0] = p1[0] - p0[0];
    d[1] = p1[1] - p0[1];
    d[2] = p1[2] - p0[2];
    mid[0] = d[0] * 0.5f + p0[0];
    mid[1] = d[1] * 0.5f + p0[1];
    mid[2] = d[2] * 0.5f + p0[2];
    okA = func_150ACEA0(mid[0], mid[1], mid[2], -d[0], -d[1], -d[2], 0, triA, &hitA[0], &hitA[1], &hitA[2], &distA,
                        &auxA, 0, 0.0f);
    okB = func_150ACEA0(mid[0], mid[1], mid[2], d[0], d[1], d[2], 0, triB, &hitB[0], &hitB[1], &hitB[2], &distB,
                        &auxB, 0, 0.0f);
    if (okA == 0 || okB == 0) {
        return 1;
    }
    opt = *(u32 *) (rec + 0x18);
    col = *(u32 *) (rec + 0x1C);
    sc = *(u32 *) (rec + 0x20);
    laser_create(hitA, triA, hitB, triB, rec, rec, col & 0xFF, (col >> 8) & 0xFF, (col >> 16) & 0xFF,
                  (opt >> 24) & 1, opt & 0xFF, (opt >> 8) & 0xFF, (opt >> 16) & 0xFF, (opt >> 25) & 1, (opt >> 26) & 1,
                  ((opt >> 27) & 1) == 0, ((opt >> 29) & 1) == 0, (opt >> 30) & 1, (opt >> 28) & 1,
                  (f32) (sc & 0xFF) * 0.024639944f, (f32) ((sc >> 8) & 0xFF) * 0.003079993f, (opt >> 31) == 0, 0xFF, 1);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/laser_record_start.s")
#endif

#ifdef NON_MATCHING
/* P175 */
void collision_select_area(s32);
s32 light_create_flicker_preset(void *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 vec3_normalize_len(f32 *, f32 *, s32 *, s32 *);
void laser_end_pieces_spawn(u8 **out, f32 *pos, u8 *tri, f32 *dir, s32 ground, u8 alt, u8 noshadow, u8 arg7, s32 arg8);
u8 *laser_glow_spawn(u8 *rec, f32 *from, f32 *to, u8 r, u8 g, u8 b, s32 ground, u8 noshadow, u8 arg8, s32 arg9);
s32 laser_hum_sound_update(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s16 *arg6);
s32 memcpy(s32, u8 *, s32);

/* The beam's emitter block (0xA0 bytes, copied to the beam record +0x110; read by laser_update / laser_draw). */
typedef struct {
    f32 u00[4];      /* 0x00: random sizes */
    f32 u10[2];      /* 0x10 */
    f32 phase[2];    /* 0x18: random 0..2pi */
    f32 rate[2];     /* 0x20: random 0.05..0.13 */
    u8 *owner2;      /* 0x28: arg5 */
    s32 sound;       /* 0x2C: light_create_flicker_preset handle or 0 */
    u8 pad30[4];     /* 0x30: never written */
    u8 *glowA;       /* 0x34: written in the record after the copy */
    u8 *glowB;       /* 0x38 */
    u8 *pieceA[3];   /* 0x3C: laser_end_pieces_spawn at end A */
    u8 *pieceB[3];   /* 0x48: at end B */
    f32 u54;         /* 0x54 = 0 */
    u8 u58;          /* 0x58 = 0 */
    u8 pad59;
    u8 triA[0x12];   /* 0x5A: hit triangle A */
    u8 triB[0x12];   /* 0x6C: hit triangle B */
    s16 len[3];      /* 0x7E: args 10..12 */
    s16 len01;       /* 0x84: arg10 + arg11 */
    u8 opt;          /* 0x86: option bits */
    u8 pad87;
    u8 *owner;       /* 0x88: arg4 (the level record) */
    s32 groundA;     /* 0x8C */
    s32 groundB;     /* 0x90 */
    u8 u94;          /* 0x94: arg17 */
    f32 u98;         /* 0x98: arg19 */
    f32 u9C;         /* 0x9C: arg20 */
} BeamEmit;

/* The beam record's spawn block (effect3d_spawn argument 0, 0x58 bytes, as particle_emitter_spawn's). */
typedef struct {
    u8 kind;         /* 0x00 = 0x59 */
    u8 u01;          /* 0x01 = 6 */
    u16 flags;       /* 0x02 = 0x5A03 */
    u16 life;        /* 0x04 = 300 */
    u8 pad06[2];
    s32 u08;         /* 0x08 = 0 */
    s32 u0C;         /* 0x0C = 0 */
    u8 rgba[4];      /* 0x10 */
    f32 size[2];     /* 0x14 = 0, 20 */
    f32 from[3];     /* 0x1C: end A */
    f32 to[3];       /* 0x28: end B */
    f32 d[3];        /* 0x34: B - A */
    s32 u40;         /* 0x40 */
    u8 u44[4];       /* 0x44 = FF, FF, 0, 6 */
    u8 pad48[0x10];
} BeamSpawn;

// beam_create: builds a beam between two geometry hits (laser_record_start, record_beam_start). Needs a ground id at
/* both ends (zone_tree_find_leaf). Spawns the three end pieces at each end (laser_end_pieces_spawn, base oriented by the hit
 * triangle; if any of the six fails, all are freed and nothing is built), an optional hum (arg9: light_create_flicker_preset at
 * the middle) and the beam record (effect3d_spawn, kind 0x59, colour r / g / b) whose +0x110 gets the emitter block
 * (BeamEmit: random sizes / phases / rates, pieces, triangles, args 10..12, option bits). With arg16 and a valid
 * direction (vec3_normalize_len) a glow record (laser_glow_spawn) runs 500 units inwards from 20 units inside each end.
 * Unless arg21 (repeat) the owner's +0x14 is set to 1 (one-shot). With the hum, sfx_emitter_start attaches the
 * laser_hum_sound_update sound callback. Returns the beam record or NULL. */
/* was func_151C7B1C */
u8 *laser_create(f32 *hitA, u8 *triA, f32 *hitB, u8 *triB, u8 *owner, u8 *arg5, u8 r, u8 g, u8 b, u8 hum,
                  s16 len0, s16 len1, s16 len2, u8 opt0, u8 opt1, u8 noshadow, u8 glow, u8 arg17, u8 opt3,
                  f32 arg19, f32 arg20, u8 repeat, u8 arg22, s32 arg23) {
    BeamEmit e;
    BeamSpawn spawn;
    struct {
        u8 u0;       /* = 2 */
        u8 u1;       /* = 2 */
        s16 life;    /* = 300 */
        u8 u4;       /* = 0 */
    } snd;
    s32 mid[3];
    f32 neg[3];
    f32 u[3];
    s32 w0;
    s32 w1;
    f32 p[3];
    f32 q[3];
    f32 rp[3];
    f32 rq[3];
    f32 ux;
    f32 uy;
    f32 uz;
    f32 vx;
    f32 vy;
    f32 vz;
    u8 *rec;
    u8 alt;
    s32 i;

    collision_select_area(0);
    e.groundA = zone_tree_find_leaf((s32) hitA[0], (s32) hitA[2]);
    e.groundB = zone_tree_find_leaf((s32) hitB[0], (s32) hitB[2]);
    if (e.groundA == 0 || e.groundB == 0) {
        return NULL;
    }
    e.owner = owner;
    e.opt = (repeat ? 0x10 : 0) | (opt0 ? 1 : 0) | (opt1 ? 0 : 2) | (noshadow ? 4 : 0) | (opt3 ? 8 : 0);
    if (!repeat) {
        owner[0x14] = 1;
    }
    e.u98 = arg19;
    e.u9C = arg20;
    e.u94 = arg17;
    for (i = 0; i < 0x12; i++) {
        e.triA[i] = triA[i];
    }
    for (i = 0; i < 0x12; i++) {
        e.triB[i] = triB[i];
    }
    e.len01 = len0 + len1;
    e.len[0] = len0;
    e.len[1] = len1;
    e.len[2] = len2;
    e.u00[0] = e.u00[2] = random_float() * 1024.0f + -2560.0f + 2048.0f;
    e.u00[1] = e.u00[3] = random_float() * 1024.0f + 1536.0f + 2048.0f;
    e.u10[0] = random_float() * 768.0f + 768.0f;
    e.u10[1] = random_float() * 768.0f + 768.0f;
    e.phase[0] = random_float() * 6.2831855f;
    e.phase[1] = random_float() * 6.2831855f;
    e.rate[0] = (random_float() * 80.0f + 50.0f) * 0.001f;
    e.rate[1] = (random_float() * 80.0f + 50.0f) * 0.001f;
    spawn.d[0] = hitB[0] - hitA[0];
    spawn.d[1] = hitB[1] - hitA[1];
    spawn.d[2] = hitB[2] - hitA[2];
    alt = r < b;
    neg[0] = -spawn.d[0];
    neg[1] = -spawn.d[1];
    neg[2] = -spawn.d[2];
    /* laser_end_pieces_spawn leaves the pointers unwritten when the hit triangle is degenerate (stack garbage on N64) */
    for (i = 0; i < 3; i++) {
        e.pieceA[i] = NULL;
        e.pieceB[i] = NULL;
    }
    laser_end_pieces_spawn(e.pieceA, hitA, triA, neg, e.groundA, alt, noshadow, arg22, 0);
    laser_end_pieces_spawn(e.pieceB, hitB, triB, spawn.d, e.groundB, alt, noshadow, arg22, 0);
    if (e.pieceA[0] == NULL || e.pieceA[1] == NULL || e.pieceA[2] == NULL || e.pieceB[0] == NULL ||
        e.pieceB[1] == NULL || e.pieceB[2] == NULL) {
        for (i = 0; i < 3; i++) {
            if (e.pieceA[i] != NULL) {
                node_destroy((struct102 *) e.pieceA[i]);
            }
        }
        for (i = 0; i < 3; i++) {
            if (e.pieceB[i] != NULL) {
                node_destroy((struct102 *) e.pieceB[i]);
            }
        }
        return NULL;
    }
    e.u58 = 0;
    e.u54 = 0.0f;
    e.owner2 = arg5;
    if (hum) {
        mid[0] = (s32) (hitA[0] + spawn.d[0] * 0.5f);
        mid[1] = (s32) (hitA[1] + spawn.d[1] * 0.5f);
        mid[2] = (s32) (hitA[2] + spawn.d[2] * 0.5f);
        snd.u0 = 2;
        snd.u1 = 2;
        snd.life = 300;
        snd.u4 = 0;
        e.sound = light_create_flicker_preset(&snd, mid, r, g, b, 0xFF, 0, 0, 0x10, arg22, arg23);
    } else {
        e.sound = 0;
    }
    spawn.kind = 0x59;
    spawn.u01 = 6;
    spawn.flags = 0x5A03;
    spawn.life = 300;
    spawn.u08 = 0;
    spawn.u0C = 0;
    spawn.rgba[0] = r;
    spawn.rgba[1] = g;
    spawn.rgba[2] = b;
    spawn.rgba[3] = 0xFF;
    spawn.size[0] = 0.0f;
    spawn.size[1] = 20.0f;
    spawn.from[0] = hitA[0];
    spawn.from[1] = hitA[1];
    spawn.from[2] = hitA[2];
    spawn.to[0] = hitB[0];
    spawn.to[1] = hitB[1];
    spawn.to[2] = hitB[2];
    spawn.u40 = ((D_800BE9F0 == 0x36) ? 0 : 0x2000000) | 0x6C0000 | 0x40000000;
    spawn.u44[0] = 0xFF;
    spawn.u44[1] = 0xFF;
    spawn.u44[2] = 0;
    spawn.u44[3] = 6;
    rec = (u8 *) effect3d_spawn((s32) &spawn, (s32) &D_800A4AA0, 0x1A, 0, 0, 0x18, 0, 0xA0, arg22, arg23);
    if (rec == NULL) {
        return NULL;
    }
    memcpy((s32) (rec + 0x110), (u8 *) &e, 0xA0);
    u[0] = spawn.d[0];
    u[1] = spawn.d[1];
    u[2] = spawn.d[2];
    if (vec3_normalize_len(u, u, &w0, &w1) != 0 && glow) {
        /* from 20 units inside each end, 500 units inwards */
        ux = u[0] * 20.0f;
        uy = u[1] * 20.0f;
        uz = u[2] * 20.0f;
        vx = u[0] * 500.0f;
        vy = u[1] * 500.0f;
        vz = u[2] * 500.0f;
        p[0] = hitA[0] + ux;
        p[1] = hitA[1] + uy;
        p[2] = hitA[2] + uz;
        q[0] = vx + p[0];
        q[1] = vy + p[1];
        q[2] = vz + p[2];
        rp[0] = hitB[0] - ux;
        rp[1] = hitB[1] - uy;
        rp[2] = hitB[2] - uz;
        rq[0] = rp[0] - vx;
        rq[1] = rp[1] - vy;
        rq[2] = rp[2] - vz;
        ((BeamEmit *) (rec + 0x110))->glowA = laser_glow_spawn(rec, p, q, r, g, b, e.groundA, noshadow, arg22, arg23);
        ((BeamEmit *) (rec + 0x110))->glowB = laser_glow_spawn(rec, rp, rq, r, g, b, e.groundB, noshadow, arg22, arg23);
    } else {
        ((BeamEmit *) (rec + 0x110))->glowA = NULL;
        ((BeamEmit *) (rec + 0x110))->glowB = NULL;
    }
    if (((BeamEmit *) (rec + 0x110))->sound != 0) {
        sfx_emitter_start(0x4D0, mid[0], mid[1], mid[2], 0x1F40, 0xFA, 0x64, (s32) laser_hum_sound_update, rec + 0x110, 0, 8,
                      random_int() & 0xFF);
    }
    return rec;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/laser_create.s")
#endif

#ifdef NON_MATCHING
void segment_closest_point(void *, void *, void *, void *, f32 *);
void vtx_slot_buffer_get(s32 *, s16, s32, s32 *, u8 *);
s32 memcpy(s32, u8 *, s32);

/* was func_151C8448 */
u8 *laser_draw(u8 *arg0, s16 arg1) {
    struct {
        u8 u43;
        u8 pad44[0x4];
        f32 u48;
        u8 pad4C[0x18];
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 * u7C;
        u8 * u80;
        u8 * u84;
    } sp;
    u8 *sp38;
    u8 *sp34;
    u8 *sp30;                                     /* compiler-managed */
    f32 sp2C;
    f32 *temp_a2;
    f32 *temp_v0_2;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f4;
    f32 var_f12;
    f32 var_f14;
    f32 var_f16;
    s16 temp_a1;
    s32 temp_v0;
    u8 *temp_a1_2;
    u8 *temp_t0;
    u8 *temp_t1;
    u8 *temp_t3;
    u8 *temp_t6;
    u8 *temp_v1;

    temp_a1 = arg1;
    temp_t0 = arg0 + 0x110;
    if (!((*(u8 *)((u8 *)arg0 + 0x196)) & 2)) {
        return NULL;
    }
    if ((*(u8 *)((u8 *)temp_t0 + 0x86)) & 4) {
        temp_v0 = 1 << temp_a1;
        if (!((*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_t0 + 0x8C))) + 2)) & temp_v0) && !((*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_t0 + 0x90))) + 2)) & temp_v0)) {
            return NULL;
        }
    }
    arg1 = temp_a1;
    sp38 = temp_t0;
    vtx_slot_buffer_get(arg0 + 0x100, temp_a1, 0x40, &sp.u84, &sp.u43);
    sp.u80 = sp.u84;
    if (sp.u84 != NULL) {
        if (sp.u43 != 0) {
            temp_v1 = arg0 + (arg1 * 4);
            temp_a1_2 = arg0 + 0xC0;
            sp30 = temp_a1_2;
            sp34 = temp_v1;
            memcpy((*(s32 *)((u8 *)temp_v1 + 0x100)), temp_a1_2, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v1 + 0x100)) + 0x40, temp_a1_2, 0x40);
        }
        temp_v0_2 = camera_get_pos((s32) arg1);
        temp_a2 = temp_v0_2;
        sp.u70 = (*(f32 *)((u8 *)arg0 + 0x40)) - (*(f32 *)((u8 *)arg0 + 0x34));
        sp.u74 = (*(f32 *)((u8 *)arg0 + 0x44)) - (*(f32 *)((u8 *)arg0 + 0x38));
        sp.u7C = temp_v0_2;
        sp.u78 = (*(f32 *)((u8 *)arg0 + 0x48)) - (*(f32 *)((u8 *)arg0 + 0x3C));
        segment_closest_point(arg0 + 0x34, &sp.u70, temp_a2, &sp.u64, 0);
        temp_f0 = sp.u64 - (*(f32 *)((u8 *)sp.u7C + 0));
        temp_f2 = sp.u68 - (*(f32 *)((u8 *)sp.u7C + 4));
        temp_f12 = sp.u6C - (*(f32 *)((u8 *)sp.u7C + 8));
        temp_f18 = (sp.u74 * temp_f12) - (temp_f2 * sp.u78);
        temp_f4 = (sp.u78 * temp_f0) - (temp_f12 * sp.u70);
        /* P270: the asm spills temp_f4 to sp30 as a float (swc1/lwc1); no int truncation */
        temp_f10 = (sp.u70 * temp_f2) - (temp_f0 * sp.u74);
        sp2C = temp_f10;
        temp_f14 = (temp_f18 * temp_f18) + (temp_f4 * temp_f4) + (temp_f10 * temp_f10);
        sp.u48 = temp_f14;
        if (temp_f14 == 0.0f) {
            var_f12 = 0.0f;
            var_f14 = 0.0f;
            var_f16 = 0.0f;
        } else {
            temp_f2_2 = (*(f32 *)((u8 *)arg0 + 0x30)) / sqrtf(sp.u48);
            var_f12 = temp_f18 * temp_f2_2;
            var_f14 = temp_f4 * temp_f2_2;  /* P270: was (s32)sp30 * (s32)temp_f2_2 (asm mul.s) */
            var_f16 = sp2C * temp_f2_2;
        }
        (*(s16 *)((u8 *)sp.u84 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x40)) - var_f12);
        (*(s16 *)((u8 *)sp.u84 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x44)) - var_f14);
        (*(s16 *)((u8 *)sp.u84 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x48)) - var_f16);
        (*(s16 *)((u8 *)sp.u84 + 8)) = (s16) (s32) (*(f32 *)((u8 *)sp38 + 0));
        (*(s16 *)((u8 *)sp.u84 + 6)) = 0;
        temp_t1 = sp.u84 + 0x10;
        sp.u84 = temp_t1;
        (*(s16 *)((u8 *)temp_t1 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - var_f12);
        (*(s16 *)((u8 *)sp.u84 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) - var_f14);
        (*(s16 *)((u8 *)sp.u84 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - var_f16);
        (*(s16 *)((u8 *)temp_t1 + 8)) = (s16) (s32) (*(f32 *)((u8 *)sp38 + 4));
        (*(s16 *)((u8 *)sp.u84 + 6)) = 0;
        temp_t6 = sp.u84 + 0x10;
        sp.u84 = temp_t6;
        (*(s16 *)((u8 *)temp_t6 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + var_f12);
        (*(s16 *)((u8 *)sp.u84 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + var_f14);
        (*(s16 *)((u8 *)sp.u84 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + var_f16);
        (*(s16 *)((u8 *)temp_t6 + 8)) = (s16) (s32) (*(f32 *)((u8 *)sp38 + 4));
        (*(s16 *)((u8 *)sp.u84 + 6)) = 0;
        temp_t3 = sp.u84 + 0x10;
        sp.u84 = temp_t3;
        (*(s16 *)((u8 *)temp_t3 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x40)) + var_f12);
        (*(s16 *)((u8 *)sp.u84 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x44)) + var_f14);
        (*(s16 *)((u8 *)sp.u84 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x48)) + var_f16);
        (*(s16 *)((u8 *)temp_t3 + 8)) = (s16) (s32) (*(f32 *)((u8 *)sp38 + 0));
        (*(s16 *)((u8 *)sp.u84 + 6)) = 0;
        return sp.u80;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/laser_draw.s")
#endif
#ifdef NON_MATCHING
/* was func_151C8880 */
s32 laser_update(u8 *arg0) {
    s16 temp_v1;
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 *temp_a1;
    u8 *temp_a1_2;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_4;
    u8 *temp_v0_5;
    u8 *temp_v0_6;
    u8 *temp_v1_2;
    u8 *temp_v1_3;

    temp_s0 = arg0 + 0x110;
    if ((*(u8 *)((u8 *)arg0 + 0x196)) & 1) {
        temp_v1 = (*(s16 *)((u8 *)temp_s0 + 0x84));
        (*(s16 *)((u8 *)temp_s0 + 0x82)) = (s16) ((*(s16 *)((u8 *)temp_s0 + 0x82)) + D_800BE9E4);
        if ((*(s16 *)((u8 *)temp_s0 + 0x82)) >= temp_v1) {
            do {
                (*(s16 *)((u8 *)temp_s0 + 0x82)) = (s16) ((*(s16 *)((u8 *)temp_s0 + 0x82)) - temp_v1);
            } while ((*(s16 *)((u8 *)temp_s0 + 0x82)) >= temp_v1);
        }
        if ((*(s16 *)((u8 *)temp_s0 + 0x82)) < (*(s16 *)((u8 *)temp_s0 + 0x7E))) {
            (*(u8 *)((u8 *)temp_s0 + 0x86)) = (u8) ((*(u8 *)((u8 *)temp_s0 + 0x86)) | 2);
        } else {
            (*(u8 *)((u8 *)temp_s0 + 0x86)) = (u8) ((*(u8 *)((u8 *)temp_s0 + 0x86)) & 0xFFFD);
        }
    }
    temp_s0_2 = arg0 + 0x110;
    if ((*(u8 *)((u8 *)arg0 + 0x196)) & 2) {
        (*(f32 *)((u8 *)temp_s0_2 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_s0_2 + 0x18)) + ((*(f32 *)((u8 *)temp_s0_2 + 0x20)) * D_800BE9A4));
        (*(f32 *)((u8 *)temp_s0_2 + 0x1C)) = (f32) ((*(f32 *)((u8 *)temp_s0_2 + 0x1C)) + ((*(f32 *)((u8 *)temp_s0_2 + 0x24)) * D_800BE9A4));
        (*(f32 *)((u8 *)temp_s0_2 + 0x18)) = wrap_angle_rad((*(f32 *)((u8 *)temp_s0_2 + 0x18)));
        (*(f32 *)((u8 *)temp_s0_2 + 0x1C)) = wrap_angle_rad((*(f32 *)((u8 *)temp_s0_2 + 0x1C)));
        (*(f32 *)((u8 *)temp_s0_2 + 0)) = (f32) ((func_150AD78C((*(f32 *)((u8 *)temp_s0_2 + 0x18))) * (*(f32 *)((u8 *)temp_s0_2 + 0x10))) + (*(f32 *)((u8 *)temp_s0_2 + 8)));
        temp_v0 = (*(u8 **)((u8 *)temp_s0_2 + 0x2C));
        (*(f32 *)((u8 *)temp_s0_2 + 4)) = (f32) ((func_150AD78C((*(f32 *)((u8 *)temp_s0_2 + 0x1C))) * (*(f32 *)((u8 *)temp_s0_2 + 0x14))) + (*(f32 *)((u8 *)temp_s0_2 + 0xC)));
        if (temp_v0 != NULL) {
            (*(s8 *)((u8 *)((*(u8 **)((u8 *)temp_v0 + 0x14))) + 9)) = 0;
        }
        temp_v0_2 = (*(u8 **)((u8 *)temp_s0_2 + 0x88));
        if ((temp_v0_2 != NULL) && ((*(u8 *)((u8 *)temp_s0_2 + 0x86)) & 0x10)) {
            (*(s8 *)((u8 *)temp_v0_2 + 0x14)) = 0;
        }
    } else {
        temp_v0_3 = (*(u8 **)((u8 *)temp_s0_2 + 0x2C));
        if (temp_v0_3 != NULL) {
            (*(s8 *)((u8 *)((*(u8 **)((u8 *)temp_v0_3 + 0x14))) + 9)) = 1;
        }
        temp_v0_4 = (*(u8 **)((u8 *)temp_s0_2 + 0x88));
        if (temp_v0_4 != NULL) {
            (*(s8 *)((u8 *)temp_v0_4 + 0x14)) = 1;
        }
    }
    (*(f32 *)((u8 *)temp_s0_2 + 0x54)) = (f32) ((*(f32 *)((u8 *)temp_s0_2 + 0x54)) + (0.080000006f * D_800BE9A4));
    if ((*(f32 *)((u8 *)temp_s0_2 + 0x54)) > 1.0f) {
        do {
            if ((*(u8 *)((u8 *)temp_s0_2 + 0x86)) & 2) {
                (*(u8 *)((u8 *)temp_s0_2 + 0x58)) = (u8) ((*(u8 *)((u8 *)temp_s0_2 + 0x58)) ^ 1);
            }
            (*(f32 *)((u8 *)temp_s0_2 + 0x54)) = (f32) ((*(f32 *)((u8 *)temp_s0_2 + 0x54)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s0_2 + 0x54)) > 1.0f);
    }
    if ((*(u8 *)((u8 *)temp_s0_2 + 0x58)) != 0) {
        temp_v0_5 = (*(u8 **)((u8 *)temp_s0_2 + 0x40));
        (*(s32 *)((u8 *)temp_v0_5 + 0x60)) = (s32) ((*(s32 *)((u8 *)temp_v0_5 + 0x60)) & 0xFFFDFFFF);
        temp_v1_2 = (*(u8 **)((u8 *)temp_s0_2 + 0x44));
        (*(s32 *)((u8 *)temp_v1_2 + 0x60)) = (s32) ((*(s32 *)((u8 *)temp_v1_2 + 0x60)) | 0x20000);
        temp_a0 = (*(u8 **)((u8 *)temp_s0_2 + 0x4C));
        (*(s32 *)((u8 *)temp_a0 + 0x60)) = (s32) ((*(s32 *)((u8 *)temp_a0 + 0x60)) & 0xFFFDFFFF);
        temp_a1 = (*(u8 **)((u8 *)temp_s0_2 + 0x50));
        (*(s32 *)((u8 *)temp_a1 + 0x60)) = (s32) ((*(s32 *)((u8 *)temp_a1 + 0x60)) | 0x20000);
    } else {
        temp_v0_6 = (*(u8 **)((u8 *)temp_s0_2 + 0x40));
        (*(s32 *)((u8 *)temp_v0_6 + 0x60)) = (s32) ((*(s32 *)((u8 *)temp_v0_6 + 0x60)) | 0x20000);
        temp_v1_3 = (*(u8 **)((u8 *)temp_s0_2 + 0x44));
        (*(s32 *)((u8 *)temp_v1_3 + 0x60)) = (s32) ((*(s32 *)((u8 *)temp_v1_3 + 0x60)) & 0xFFFDFFFF);
        temp_a0_2 = (*(u8 **)((u8 *)temp_s0_2 + 0x4C));
        (*(s32 *)((u8 *)temp_a0_2 + 0x60)) = (s32) ((*(s32 *)((u8 *)temp_a0_2 + 0x60)) | 0x20000);
        temp_a1_2 = (*(u8 **)((u8 *)temp_s0_2 + 0x50));
        (*(s32 *)((u8 *)temp_a1_2 + 0x60)) = (s32) ((*(s32 *)((u8 *)temp_a1_2 + 0x60)) & 0xFFFDFFFF);
    }
    if ((*(u8 *)((u8 *)temp_s0_2 + 0x86)) & 8) {
        (*(s8 *)((u8 *)arg0 + 0x5C)) = (s8) (u32) ((func_150AD78C((*(f32 *)((u8 *)temp_s0_2 + 0x98))) * 112.5f) + 142.5f);
        (*(f32 *)((u8 *)temp_s0_2 + 0x98)) = wrap_angle_rad((*(f32 *)((u8 *)temp_s0_2 + 0x98)) + ((*(f32 *)((u8 *)temp_s0_2 + 0x9C)) * D_800BE9A4));
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/laser_update.s")
#endif
/* was func_151C8C24 */
void laser_test_obj_broadcast(u8 *arg0, s32 arg1) {
    s32 sp18[2];
    if (arg0 != NULL) {
        sp18[0] = (s32)arg0;
        sp18[1] = arg1;
        fx_lists_broadcast_a(sp18, 0x20);
    }
}

s32 laser_hits_object(u8 *, u8 *);
void laser_break_effects(u8 *, u8 *);
/* was func_151C8C5C */
void laser_handle_message(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *v;
    u8 **q = &arg0;
    switch (arg2) {
    case 0x20:
        v = (*q) + 0x110;
        if ((v[0x86] & 0x10) && (*(s32 *)(v + 0x28) == arg1[1])) {
            if (laser_hits_object((u8 *)arg1[0], (*q))) {
                laser_break_effects((u8 *)arg1[0], (*q));
            }
        }
        break;
    case 0x3A:
        v = (*q) + 0x110;
        if (*(s32 *)(v + 0x28) == arg1[0]) {
            switch (((u8 *)arg1)[4]) {
            case 0: v[0x86] |= 2; break;
            case 1: v[0x86] &= ~2; break;
            case 2: laser_break_effects(NULL, (*q)); break;
            }
        }
        break;
    }
}

/* was func_151C8D5C */
s32 laser_hum_sound_update(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s16 *arg6) {
    u8 *p;
    s16 *q;
    p = *(u8 **)(arg0 + 0x18);
    q = arg6;
    if (!(p[0x86] & 2)) {
        *q = 0;
    }
    return 0;
}

#ifdef NON_MATCHING
/* P177 */
s32 obj_collision_cylinder(u8 *, s16 *, s16 *, s16 *);
s32 segment_sphere_hit(f32 *, f32 *, f32 *, f32, f32, s32, s32, f32 *, f32 *);

// beam_hits_object: whether the beam segment of `rec` (end points +0x34 / +0x40) crosses `obj`'s collision body.
/* The body is an ellipsoid of radius (model kind obj +4 < 0xBB, not 0xFF: D_800D1C90[kind] +0x1A x obj +0x14C, else
 * 50) around obj's position raised by half its height (obj_collision_cylinder); the segment's y is scaled by radius /
 * half-height about that centre to make it a sphere, then segment_sphere_hit tests the ray (start, unit direction) against
 * the sphere within the segment length. 0 when the height is 0 or the segment has no length. */
/* was func_151C8D90 */
s32 laser_hits_object(u8 *obj, u8 *rec) {
    f32 centre[3];
    f32 start[3];
    f32 dir[3];
    f32 len;
    f32 hitA[3];
    f32 hitB[3];
    f32 tA;
    f32 tB;
    f32 inv;
    f32 radius;
    f32 half;
    f32 scale;
    f32 endY;
    s16 height;
    s16 width;
    s16 rad;
    u8 kind;

    kind = obj[4];
    if (kind < 0xBB && kind != 0xFF) {
        radius = *(s16 *)((u8 *)D_800D1C90[kind] + 0x1A) * *(f32 *)(obj + 0x14C);
    } else {
        radius = 50.0f;
    }
    obj_collision_cylinder(obj, &height, &width, &rad);
    if ((f32)height == 0.0f) {
        return 0;
    }
    half = (f32)height * 0.5f;
    centre[0] = *(f32 *)(obj + 0x14);
    centre[1] = *(f32 *)(obj + 0x18) + half;
    centre[2] = *(f32 *)(obj + 0x1C);
    scale = radius / half;
    start[0] = *(f32 *)(rec + 0x34);
    start[1] = (*(f32 *)(rec + 0x38) - centre[1]) * scale + centre[1];
    start[2] = *(f32 *)(rec + 0x3C);
    endY = (*(f32 *)(rec + 0x44) - centre[1]) * scale + centre[1];
    dir[0] = *(f32 *)(rec + 0x40) - start[0];
    dir[1] = endY - start[1];
    dir[2] = *(f32 *)(rec + 0x48) - start[2];
    if (!vec3_normalize_len(dir, dir, (s32 *)&len, (s32 *)&inv)) {
        return 0;
    }
    if (segment_sphere_hit(start, dir, centre, radius, len, (s32)hitA, (s32)hitB, &tA, &tB) == 0) {
        return 0;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/laser_hits_object.s")
#endif

#ifdef NON_MATCHING
/* P177 */
void fx_scorch_decal_spawn(f32, u8, s32 *, f32 *, s32, s32, s32, s32, s32, s32, u8, s32);
void emit_spray_from_surface(u8 *arg0, u8 arg1, s32 arg2);
u8 *cam_wobble_start_preset(u8 kind, u8 view, u8 *data, u8 arg3, s32 arg4);
s32 obj_send_hit(struct127 *obj, s32 flags, u16 val, s32 arg3);
s32 sfx_cb_delayed_play_2d();
extern s32 D_800AB010[]; /* hit-sound flags by beam piece kind: 0x17, 0x18 */

// beam_hit_effects: the effects when the beam `rec` is broken (by obj, from the 0x20 / 0x3A messages of
/* laser_handle_message; obj NULL for the scripted break). At each end (+0x34 with the surface record +0x16A and the
 * direction +0x4C; +0x40 with +0x17C and the reversed direction): a spark spray (emit_spray_from_surface, the block below),
 * a flash (light_create_with_ctrl kind 3) and a scorch mark (fx_scorch_decal_spawn). With obj: the screen effect preset 2 for obj's
 * view (cam_wobble_start_preset), a rumble (rumble_request) and obj's hit reaction (obj_send_hit, flags D_800AB010 by the
 * piece kind at +0x1A4). Then the two sounds (0x2F5 at end A, 0x2F6 at end B) and node_destroy(rec).
 * (The mark positions are the end points: the asm saves v0 = rec + 0x34 / + 0x40 in the delay slot of the
 * emit_spray_from_surface calls, before the call.) */
/* was func_151C8F4C */
void laser_break_effects(u8 *obj, u8 *rec) {
    struct {
        f32 dir[3];      /* 0x00 */
        u8 hit[0x12];    /* 0x0C surface record */
        u8 pad1E[2];
        f32 range;       /* 0x20 */
        s32 countBase;   /* 0x24 spray parameters (emit_spray_particles) */
        s32 countExtra;  /* 0x28 */
        f32 pos[3];      /* 0x2C */
        f32 speedBase;   /* 0x38 */
        f32 speedRange;  /* 0x3C */
        f32 sizeBase;    /* 0x40 */
        f32 sizeRange;   /* 0x44 */
        f32 size2Base;   /* 0x48 */
        f32 size2Range;  /* 0x4C */
        s32 lifeBase;    /* 0x50 */
        s32 lifeExtra;   /* 0x54 */
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
    } spray;
    struct {
        u8 kind;
        s8 u1;
        s16 size;
        u8 u4;
    } flash;
    s32 at[3];
    structEU_151D8E18 rumble;
    u8 *beam;
    s32 i;
    f32 r;

    spray.range = 491.0f;
    spray.countBase = 5;
    spray.countExtra = 3;
    spray.speedBase = 0.0605f;
    spray.speedRange = 0.0523f;
    spray.sizeBase = 30.0f;
    spray.sizeRange = 83.0f;
    spray.size2Base = 211.0f;
    spray.size2Range = 150.0f;
    spray.lifeBase = 5;
    spray.lifeExtra = 4;
    spray.u58 = 21.0f;
    spray.u5C = 0.698f;
    spray.u60 = -0.44500002f;
    spray.u64 = 0.441f;
    spray.u68 = 0x12;
    spray.u6A = 9;
    spray.u6C = 100;
    spray.u6E = 100;
    spray.u70 = 12;
    spray.u72 = 15;
    spray.u74 = 0;

    spray.pos[0] = *(f32 *)(rec + 0x34);
    spray.pos[1] = *(f32 *)(rec + 0x38);
    spray.pos[2] = *(f32 *)(rec + 0x3C);
    spray.dir[0] = *(f32 *)(rec + 0x4C);
    spray.dir[1] = *(f32 *)(rec + 0x50);
    spray.dir[2] = *(f32 *)(rec + 0x54);
    for (i = 0; i < 0x12; i++) {
        spray.hit[i] = rec[0x16A + i];
    }
    emit_spray_from_surface((u8 *)&spray, rec[0xC], rec[1]);

    beam = rec + 0x110;
    spray.pos[0] = *(f32 *)(rec + 0x40);
    spray.pos[1] = *(f32 *)(rec + 0x44);
    spray.pos[2] = *(f32 *)(rec + 0x48);
    spray.dir[0] = -*(f32 *)(rec + 0x4C);
    spray.dir[1] = -*(f32 *)(rec + 0x50);
    spray.dir[2] = -*(f32 *)(rec + 0x54);
    for (i = 0; i < 0x12; i++) {
        spray.hit[i] = beam[0x6C + i];
    }
    emit_spray_from_surface((u8 *)&spray, rec[0xC], rec[1]);

    at[0] = *(f32 *)(rec + 0x34);
    at[1] = *(f32 *)(rec + 0x38);
    at[2] = *(f32 *)(rec + 0x3C);
    flash.kind = 3;
    flash.u1 = -1;
    flash.size = (random_int() % 9U) + 0x11;
    flash.u4 = 0;
    light_create_with_ctrl((Header *)&flash, (Header2 *)at, (random_int() % 9U) + 5, 0xFF, 0x59, 0, 0xFF, 0, 0, rec[0xC],
                  rec[1]);
    at[0] = *(f32 *)(rec + 0x40);
    at[1] = *(f32 *)(rec + 0x44);
    at[2] = *(f32 *)(rec + 0x48);
    light_create_with_ctrl((Header *)&flash, (Header2 *)at, (random_int() % 9U) + 5, 0xFF, 0x59, 0, 0xFF, 0, 0, rec[0xC],
                  rec[1]);

    r = random_float();
    fx_scorch_decal_spawn(r * 101.0f + 55.0f, (random_int() % 66U) + 0xBE, (s32 *)(beam + 0x5A), (f32 *)(rec + 0x34), -1,
                  1, 1, 0, 0, 0, rec[0xC], 0);
    r = random_float();
    fx_scorch_decal_spawn(r * 101.0f + 55.0f, (random_int() % 66U) + 0xBE, (s32 *)(beam + 0x6C), (f32 *)(rec + 0x40), -1,
                  1, 1, 0, 0, 0, rec[0xC], 0);

    if (obj != NULL) {
        cam_wobble_start_preset(2, (*(u8 **)(obj + 0x318))[0x23D], NULL, rec[0xC], rec[1]);
        rumble.unk0 = 1;
        rumble.unk2 = 0x28;
        rumble.unk5 = 1;
        rumble.unk4 = 8;
        rumble.unk6 = -1;
        rumble_request(&rumble, 0, 0xFF, 0);
    }
    if (obj != NULL) {
        obj_send_hit((struct127 *)obj, D_800AB010[beam[0x94]], 0, -1);
    }
    sound_play_at(0x2F5, 0x7FFF, random_int() % 500U, 0, 0, *(f32 *)(rec + 0x34), *(f32 *)(rec + 0x38),
                  *(f32 *)(rec + 0x3C), 0x7D0, 0x898);
    sfx_emitter_start(0x2F6, *(f32 *)(rec + 0x40), *(f32 *)(rec + 0x44), *(f32 *)(rec + 0x48), 0x7FFF, 0x898, 0x7D0,
                  (s32)sfx_cb_delayed_play_2d, (void *)5, 0, 0, random_int() % 500U);
    node_destroy((struct102 *)rec);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/laser_break_effects.s")
#endif

#ifdef NON_MATCHING
/* P175 */
u8 *particle_emitter_spawn(void *emit, s32 emitSize, void *spawn, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s8 arg7, u8 arg8,
                  s32 arg9);
s32 memcpy(s32, u8 *, s32);

// beam_glow_spawn: one glow of a beam (laser_create): a particle emitter (particle_emitter_spawn, kind 0x15, emitter size
/* 0x64) from `from` to `to` in colour r / g / b with the ground id, shadow flag 0x1000000 when `noshadow`; the
 * beam record is stored at the new record's +0x170. Returns the glow record or NULL. */
/* was func_151C957C */
u8 *laser_glow_spawn(u8 *rec, f32 *from, f32 *to, u8 r, u8 g, u8 b, s32 ground, u8 noshadow, u8 arg8, s32 arg9) {
    struct {
        u8 kind;     /* 0x00 = 0x15 */
        u8 u01;      /* 0x01 = 3 */
        u16 flags;   /* 0x02 = 0x3403 */
        u16 life;    /* 0x04 = 300 */
        u8 pad06[2];
        s32 u08;     /* 0x08 = 0 */
        s32 u0C;     /* 0x0C = 0 */
        u8 rgba[4];  /* 0x10 */
        f32 size[2]; /* 0x14 = 0 */
        f32 from[3]; /* 0x1C */
        f32 to[3];   /* 0x28 */
        f32 scale[3]; /* 0x34 = 1 */
        s32 u40;     /* 0x40 */
        u8 u44[4];   /* 0x44 = FF, FF, 0, 6 */
        s32 ground;  /* 0x48 */
        u8 pad4C[0xC];
    } spawn;
    struct {
        f32 range[4]; /* 0x00: 30.1, 30.1, 40, 40 */
        f32 u10[2];   /* 0x10 = 0 */
        f32 u18;      /* 0x18 = 1 */
        f32 u1C;      /* 0x1C = 0.3 */
        f32 u20;      /* 0x20 = 1e-6 */
        u8 pad24[0x24];
        f32 u48;      /* 0x48 = 1 */
        u8 pad4C[8];
        u8 u54[5];    /* 0x54 = 0 */
        u8 pad59[0xB];
    } emit;
    u8 *glow;

    emit.range[0] = 30.1f;
    emit.range[1] = 30.1f;
    emit.range[2] = 40.0f;
    emit.range[3] = 40.0f;
    emit.u18 = 1.0f;
    emit.u10[0] = 0.0f;
    emit.u10[1] = 0.0f;
    spawn.from[0] = from[0];
    spawn.from[1] = from[1];
    spawn.from[2] = from[2];
    spawn.to[0] = to[0];
    spawn.to[1] = to[1];
    spawn.to[2] = to[2];
    emit.u1C = 0.3f;
    spawn.kind = 0x15;
    spawn.flags = 0x3403;
    spawn.life = 300;
    spawn.u08 = 0;
    spawn.u0C = 0;
    spawn.rgba[0] = r;
    spawn.rgba[3] = 0xFF;
    spawn.size[0] = 0.0f;
    spawn.size[1] = 0.0f;
    spawn.scale[0] = 1.0f;
    spawn.scale[1] = 1.0f;
    spawn.scale[2] = 1.0f;
    spawn.rgba[1] = g;
    spawn.rgba[2] = b;
    spawn.u40 = (noshadow ? 0x1000000 : 0) | 0x24D2006 | 0x40000000;
    spawn.u44[1] = 0xFF;
    spawn.u44[0] = 0xFF;
    spawn.u44[2] = 0;
    spawn.u44[3] = 6;
    spawn.u01 = 3;
    emit.u54[0] = 0;
    emit.u54[1] = 0;
    emit.u54[2] = 0;
    emit.u54[3] = 0;
    emit.u48 = 1.0f;
    emit.u54[4] = 0;
    spawn.ground = ground;
    emit.u20 = 0.000001f;
    glow = particle_emitter_spawn(&emit, 0x64, &spawn, 0, 0, 0, 0, 1, arg8, arg9);
    if (glow != NULL) {
        memcpy((s32) (glow + 0x170), (u8 *) &rec, 4);
    }
    return glow;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/laser_glow_spawn.s")
#endif

#ifdef NON_MATCHING
/* P175 */
s32 mdl_particle_spawn(void *, s32, s32, s32, u8, s32);
s32 mdl_particle_mtx_rot_scale3(s32, u8 *);
s32 tri_calc_normal(u8 *, f32 *, f32 *, f32 *);
void vec3_to_yaw_pitch_deg(f32 *, f32 *, f32 *);
s32 memcpy(s32, u8 *, s32);

// beam_end_pieces_spawn: the three pieces of one beam end (laser_create): from the hit triangle `tri`
// (tri_calc_normal: its normal / axes) the orientation of the base; spawns with mdl_particle_spawn (kind 3) the base
// (sound 0x36, no delay) and two arm pieces (0x37 / 0x38, delay 0x14) at `pos`, writes them to out[0..2] and runs
// mdl_particle_mtx_rot_scale3 on both 0x40-byte parts of each; the arms also get the 0x14-byte animation list at +0x170 (alt set
// = the other model ids). out[] is left unchanged when tri_calc_normal fails.
/* was func_151C9748 */
void laser_end_pieces_spawn(u8 **out, f32 *pos, u8 *tri, f32 *dir, s32 ground, u8 alt, u8 noshadow, u8 arg7, s32 arg8) {
    struct {
        f32 u00;     /* 0x00 = 1 */
        f32 u04;     /* 0x04 = 1 */
        f32 size[2]; /* 0x08 = 0.4 */
        f32 spin[3]; /* 0x10: tilt + 90, heading, 0 */
        f32 u1C[3];  /* 0x1C = 1 */
        f32 pos[3];  /* 0x28 */
        f32 u34[7];  /* 0x34 = 0 */
        s32 flags;   /* 0x50 */
        s16 life;    /* 0x54 = 300 */
        s16 sound;   /* 0x56 */
        u8 u58;      /* 0x58 = 0 */
        s32 ground;  /* 0x5C */
        u8 u60[8];   /* 0x60: FF, 0.. */
        u8 u68;      /* 0x68 */
        s8 u69;      /* 0x69 */
        u8 u6A;      /* 0x6A = 0 */
        s32 u6C;     /* 0x6C = 0 */
        u8 u70;      /* 0x70 = 0 */
        s16 u72;     /* 0x72 = 1 */
        s16 u74;     /* 0x74 = 0xFF */
    } blk;
    struct {
        u8 op0;      /* 0x00 = 2 */
        u8 pad1[3];
        s16 id0;     /* 0x04 */
        u8 op1;      /* 0x06 = 4 */
        u8 pad7;
        s32 v0;      /* 0x08 = 0x3E */
        s16 id1;     /* 0x0C */
        u8 op2;      /* 0x0E = 6 */
        u8 padF;
        s32 v1;      /* 0x10 = 0x3E */
    } anim;
    f32 ax[3];
    f32 ay[3];
    f32 az[3];
    s32 i;
    s32 k;

    if (tri_calc_normal(tri, ax, ay, az) == 0) {
        return;
    }
    vec3_to_yaw_pitch_deg(az, &blk.spin[1], &blk.spin[0]);
    blk.u00 = 1.0f;
    blk.u04 = 1.0f;
    blk.spin[0] += 90.0f;
    blk.u1C[0] = 1.0f;
    blk.u1C[1] = 1.0f;
    blk.u1C[2] = 1.0f;
    blk.size[1] = 0.4f;
    blk.size[0] = 0.4f;
    blk.spin[2] = 0.0f;
    blk.pos[0] = pos[0];
    blk.pos[1] = pos[1];
    blk.pos[2] = pos[2];
    for (i = 0; i < 7; i++) {
        blk.u34[i] = 0.0f;
    }
    blk.flags = (noshadow ? 0x400 : 0) | 0x900 | 0x14000 | 0x40000 | 0x80000;
    blk.ground = ground;
    blk.life = 300;
    blk.sound = 0x36;
    blk.u58 = 0;
    blk.u60[0] = 0xFF;
    for (i = 1; i < 8; i++) {
        blk.u60[i] = 0;
    }
    blk.u68 = 2;
    blk.u6A = 0;
    blk.u6C = 0;
    blk.u70 = 0;
    blk.u72 = 1;
    blk.u74 = 0xFF;
    blk.u69 = -1;
    out[0] = (u8 *) mdl_particle_spawn(&blk, 3, 0xFF, 0, arg7, arg8);
    if (out[0] != NULL) {
        for (i = 0; i < 0x80; i += 0x40) {
            mdl_particle_mtx_rot_scale3((s32) (out[0] + i + 0x90), out[0]);
        }
    }
    blk.u69 = 2;
    anim.op0 = 2;
    anim.op1 = 4;
    anim.op2 = 6;
    anim.v0 = 0x3E;
    anim.v1 = 0x3E;
    blk.u68 = 0;
    for (k = 1; k < 3; k++) {
        if (k == 1) {
            anim.id0 = alt ? 0x87 : 0x8B;
            anim.id1 = alt ? 0x88 : 0x8C;
            blk.sound = 0x37;
        } else {
            anim.id0 = alt ? 0x89 : 0x8D;
            anim.id1 = alt ? 0x8A : 0x8E;
            blk.sound = 0x38;
        }
        out[k] = (u8 *) mdl_particle_spawn(&blk, 3, 0xFF, 0x14, arg7, arg8);
        if (out[k] == NULL) {
            if (k == 1) {
                continue;
            }
            return;
        }
        for (i = 0; i < 0x80; i += 0x40) {
            mdl_particle_mtx_rot_scale3((s32) (out[k] + i + 0x90), out[k]);
        }
        memcpy((s32) (out[k] + 0x170), (u8 *) &anim, 0x14);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/laser_end_pieces_spawn.s")
#endif

/* was func_151C9A84 */
void laser_retire(struct210 *arg0) {
    u8 *p;
    struct102 *a;
    struct210 **pa = &arg0; // fakematch: arg0 address taken keeps it in its home slot

    p = (u8 *)*pa + 0x110;
    if (*(s32 *)((u8 *)*pa + 0x13C) != 0) {
        node_destroy(*(struct102 **)(p + 0x2C));
        sfx_emitter_stop_by_callback(laser_hum_sound_update, p, 0);
    }
    p = (u8 *)*pa;
    a = *(struct102 **)(p + 0x144);
    p += 0x110;
    if (a != NULL) {
        node_destroy(a);
    }
    if (*(struct102 **)(p + 0x38) != NULL) {
        node_destroy(*(struct102 **)(p + 0x38));
    }
    if (*(struct102 **)(p + 0x3C) != NULL) {
        node_destroy(*(struct102 **)(p + 0x3C));
    }
    if (*(struct102 **)(p + 0x40) != NULL) {
        node_destroy(*(struct102 **)(p + 0x40));
    }
    if (*(struct102 **)(p + 0x44) != NULL) {
        node_destroy(*(struct102 **)(p + 0x44));
    }
    if (*(struct102 **)(p + 0x48) != NULL) {
        node_destroy(*(struct102 **)(p + 0x48));
    }
    if (*(struct102 **)(p + 0x4C) != NULL) {
        node_destroy(*(struct102 **)(p + 0x4C));
    }
    if (*(struct102 **)(p + 0x50) != NULL) {
        node_destroy(*(struct102 **)(p + 0x50));
    }
    effect3d_retire(arg0);
}

/* was func_151C9B88 */
void laser_delete(struct210 *arg0) {
    u8 *p;
    struct102 *a;
    struct210 **pa = &arg0; // fakematch: arg0 address taken keeps it in its home slot

    p = (u8 *)*pa + 0x110;
    if (*(s32 *)((u8 *)*pa + 0x13C) != 0) {
        node_destroy(*(struct102 **)(p + 0x2C));
        sfx_emitter_stop_by_callback(laser_hum_sound_update, p, 0);
    }
    p = (u8 *)*pa;
    a = *(struct102 **)(p + 0x144);
    p += 0x110;
    if (a != NULL) {
        node_destroy(a);
    }
    if (*(struct102 **)(p + 0x38) != NULL) {
        node_destroy(*(struct102 **)(p + 0x38));
    }
    if (*(struct102 **)(p + 0x3C) != NULL) {
        node_destroy(*(struct102 **)(p + 0x3C));
    }
    if (*(struct102 **)(p + 0x40) != NULL) {
        node_destroy(*(struct102 **)(p + 0x40));
    }
    if (*(struct102 **)(p + 0x44) != NULL) {
        node_destroy(*(struct102 **)(p + 0x44));
    }
    if (*(struct102 **)(p + 0x48) != NULL) {
        node_destroy(*(struct102 **)(p + 0x48));
    }
    if (*(struct102 **)(p + 0x4C) != NULL) {
        node_destroy(*(struct102 **)(p + 0x4C));
    }
    if (*(struct102 **)(p + 0x50) != NULL) {
        node_destroy(*(struct102 **)(p + 0x50));
    }
    effect3d_free(arg0);
}

/* was func_151C9C8C */
s32 laser_piece_is_on(u8 *arg0, s32 arg1) {
    s32 *q = &arg1; // fakematch: arg1 home store
    u8 *p = *(u8 **)(arg0 + 0x170) + 0x110;
    if (p[0x86] & 2) {
        return 1;
    }
    return 0;
}

/* was func_151C9CBC */
void laser_switch_broadcast(s32 arg0, s32 arg1) {
    s32 tmp[2];
    tmp[0] = arg1;
    *(u8 *)(tmp + 1) = arg0;
    fx_lists_broadcast_a(tmp, 0x3A);
}

s32 hitinfo_from_obj_floor(s32 *, struct127 *);
#ifdef NON_MATCHING
/* P170 */
s32 collision_floor_probe(f32 *, s32, f32, s32 *);
f32 random_float(void);
s32 random_int(void);
void fx_scorch_decal_spawn(f32, u8, s32 *, f32 *, s32, s32, s32, s32, s32, s32, u8, s32);
void rumble_all_players_at(struct17 *, f32, f32, f32, s16, s16, s32, s32);
void cam_shake_all_players(struct17 *, f32, f32, f32, s16, s32, s32);
s32 smoke_cloud_spawn(struct17 *, u8, s32);
void explosion_light_spawn(struct17 *, u8, s32);
void fx_debris_emitter_spawn(struct17 *, s16, u8, s32);
s32 spark_shower_spawn(f32 *, f32, f32, f32, f32, s32, s32);
s32 object_hit_effects(struct127 *, s32, s32, s32, s32, s32, s32, s32);
u16 sound_play_at(s32 arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9);
void object_explode_air_burst(struct127 *arg0, u8 arg1, s32 arg2);

// object_explode: the big explosion at an object (135 units above its position +0x14/+0x18/+0x1C). On the ground
// (+0x2D8 == 0) a scorch mark (fx_scorch_decal_spawn) where a ray 200 units down hits a floor with flag 1, and the debris
// burst object_hit_effects; then the blast effects rumble_all_players_at / cam_shake_all_players / smoke_cloud_spawn / explosion_light_spawn, the
// sparks fx_debris_emitter_spawn (at the scorch point when there is one), the flash spark_shower_spawn, the sound 0x60D, and in
// the air the extra burst object_explode_air_burst. Nothing for a NULL object.
/* was func_151C9740 */
void object_explode_big(struct127 *obj, u8 arg1, s32 arg2) {
    s32 ground[9];  /* floor query (hitinfo_from_obj_floor / collision_floor_probe): f32 height at +0, flags byte +0x1C */
    struct17 probe;
    u8 inAir;
    u8 scorched;
    struct17 mark;
    struct17 pos;
    f32 r;
    u32 a;
    u32 b;

    if (obj == NULL) {
        return;
    }
    pos.unk0 = *(f32 *) ((u8 *) obj + 0x14);
    pos.unk4 = *(f32 *) ((u8 *) obj + 0x18) + 135.0f;
    pos.unk8 = *(f32 *) ((u8 *) obj + 0x1C);
    scorched = 0;
    inAir = (*(f32 *) ((u8 *) obj + 0x2D8) != 0.0f) ? 1 : 0;
    if (!inAir) {
        probe = pos;
        hitinfo_from_obj_floor(ground, obj);
        if (collision_floor_probe((f32 *) &probe, 0, pos.unk4 - 200.0f, ground) != 0 && (((u8 *) ground)[0x1C] & 1)) {
            mark.unk0 = probe.unk0;
            mark.unk4 = *(f32 *) &ground[0];
            mark.unk8 = probe.unk8;
            scorched = 1;
            r = random_float();
            a = random_int();
            b = random_int();
            fx_scorch_decal_spawn(r * 125.0f + 204.0f, a % 101 + 155, &ground[1], (f32 *) &mark, b % 302 + 500, 0, 1, 0, 0,
                          0, arg1, 0);
        }
    }
    rumble_all_players_at(&pos, 506.0f, 1013.0f, 0.000987166888f, 15, 20, arg1, arg2);
    cam_shake_all_players(&pos, 506.0f, 1013.0f, 0.000987166888f, 5, arg1, arg2);
    smoke_cloud_spawn(&pos, arg1, arg2);
    explosion_light_spawn(&pos, arg1, arg2);
    fx_debris_emitter_spawn(scorched ? &mark : &pos, (u32) random_int() % 62 + 120, arg1, arg2);
    r = random_float();
    spark_shower_spawn((f32 *) &pos, r + r + 8.0f, 2.4641099f, (u32) random_int() % 56 + 200, 0.0f, arg1, arg2);
    if (!inAir) {
        object_hit_effects(obj, 0, 0, 1, 0, 0, arg1, arg2);
    }
    sound_play_at(0x60D, 0x7D00, 0, 0, 0, (s32) pos.unk0, (s32) pos.unk4, (s32) pos.unk8, 500, 1000);
    if (inAir) {
        object_explode_air_burst(obj, arg1, arg2);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/object_explode_big.s")
#endif

void debris_burst_spawn(struct17 *, s32 *, s32, u8, s32);
/* was func_151CA070 */
void object_explode_air_burst(struct127 *arg0, u8 arg1, s32 arg2) {
    struct17 pos;
    s32 sp20[9];

    pos.unk0 = *(f32 *)((u8 *)arg0 + 0x14);
    pos.unk4 = *(f32 *)((u8 *)arg0 + 0x180) + 2.0f;
    pos.unk8 = *(f32 *)((u8 *)arg0 + 0x1C);
    hitinfo_from_obj_floor(sp20, arg0);
    debris_burst_spawn(&pos, sp20, 2, arg1, arg2);
}

/* was func_151CA0E0 */
s32 laser_light_sync(u8 *arg0)
{
  u8 *new_var2;
  u8 *new_var;
  new_var = arg0;
  new_var2 = *((u8 **) (new_var + 0x18));
  if ((*((u8 *) (new_var2 + 0x6F))) == 0)
  {
    *((s8 *) ((*((u8 **) (arg0 + 0x14))) + 9)) = 0;
  }
  else
  {
    *((s8 *) ((*((u8 **) (new_var + 0x14))) + 9)) = 1;
  }
  return 1;
}

/* was func_151CA114 */
s32 laser_piece_visibility_update(u8 *arg0, s8 *arg1)
{
  u8 *new_var;
  new_var = *((u8 **) (((u8 *) arg0) + 0x188)); // fakematch: pointer in a named local (permuter)
  if ((*((u8 *) (((u8 *) new_var) + 0x6F))) == 0)
  {
    *arg1 = 1;
  }
  else
  {
    *((s32 *) (((u8 *) arg0) + 0x58)) = (s32) ((*((s32 *) (((u8 *) arg0) + 0x58))) & (~2));
    *arg1 = 0;
  }
  return 1;
}
