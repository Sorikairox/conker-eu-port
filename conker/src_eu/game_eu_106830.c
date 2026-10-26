#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_150D9020 */
void trail_get_emit_point(f32 *arg0, f32 *arg1) {
    arg1[0] = arg0[5];
    arg1[1] = arg0[6] + 20.0f;
    arg1[2] = arg0[7];
}

/* was func_150D904C */
void trail_get_aim(s32 arg0, s32 arg1) {
    f32 sp34[3];
    f32 sp28[3];

    func_15145740(arg0, (s32)sp34, (s32)sp28, arg1, D_800BE616 ? D_800A0F10 : D_800A0F14);
}

#ifdef NON_MATCHING
extern f32 D_800A0F18;
int func_151EFDD0(void);
void func_1000D96C(s32 arg0, s32 arg1, s32 arg2);

// obj_spawn_effect50_with_sound: for an object with a character record (+0x31C), starts a sound 0x1B6 / 0x1B7
// (random, func_10010F88; 1500 or, outside level 0x34, 5000 frames) and an effect record of kind 0x50
// (func_15147FF0, 300 frames) at the object's position + 20 in y (trail_get_emit_point); its 0x50-byte data (rec + 0x98)
// holds the object, its id, the position (twice), the aim of trail_get_aim, the sound handle and a flag byte (bit 0
// cleared when the character record's +0x84 is set). In level 10 a func_1000D96C(10, 0x37, 0) cue comes first.
/* was func_150D9098 */
void obj_spawn_effect50_with_sound(u8 *obj) {
    struct {
        u8 *obj;        // 0x00 (sp58)
        u8 id;          // 0x04
        f32 pos0[3];    // 0x08
        f32 pos1[3];    // 0x14
        f32 aim[3];     // 0x20
        f32 u2C;        // 0x2C
        s16 sound;      // 0x30
        f32 u34;        // 0x34
        f32 u38;        // 0x38
        f32 u3C;        // 0x3C
        f32 u40;        // 0x40
        f32 u44;        // 0x44
        f32 u48;        // 0x48
        u8 flags;       // 0x4C
        u8 u4D;         // 0x4D
    } data;
    struct {
        f32 pos[3];     // 0x00 (spAC)
        s16 time;       // 0x0C
        s16 u0E;        // 0x0E
        s32 u10;        // 0x10
        u8 u14;         // 0x14
        u8 u15;         // 0x15
        s32 u18;        // 0x18
    } spec;
    u8 *rec;

    if (*(u8 **) (obj + 0x31C) == NULL) {
        return;
    }
    if (D_800BE9F0 == 10) {
        func_1000D96C(10, 0x37, 0);
    }
    trail_get_emit_point((f32 *) obj, spec.pos);
    data.flags = 1;
    data.u4D = 0;
    data.obj = obj;
    data.id = obj[0x3B];
    data.pos0[0] = spec.pos[0];
    data.pos0[1] = spec.pos[1];
    data.pos0[2] = spec.pos[2];
    data.pos1[0] = spec.pos[0];
    data.pos1[1] = spec.pos[1];
    data.pos1[2] = spec.pos[2];
    trail_get_aim((s32) obj, (s32) data.aim);
    data.u3C = D_800A0F18;
    if (D_800BE9F0 == 0x34) {
        data.sound = func_10010F88(0x1B6 + func_151EFDD0() % 2, 0x7FFF, 0, 0, 0, 0, 0, 0, 500, 1500);
    } else {
        data.sound = func_10010F88(0x1B6 + func_151EFDD0() % 2, 0x7FFF, 0, 0, 0, 0, 0, 0, 500, 5000);
    }
    data.u34 = 0.0f;
    data.u2C = 0.0f;
    data.u40 = 0.0f;
    data.u44 = 0.0f;
    data.u48 = 0.0f;
    data.u38 = -16384.0f;
    if (*(u8 **) (obj + 0x31C) != NULL && (*(u8 **) (obj + 0x31C))[0x84] != 0) {
        data.flags &= ~1;
    }
    spec.u15 = 0x32;
    spec.time = 0x12C;
    spec.u0E = 0x36;
    spec.u10 = 2;
    spec.u14 = 5;
    spec.u18 = 0;
    rec = func_15147FF0(&spec, 0x50, 0x24, 0xE, 1, 0x11, 3, 0xFF, 0, 0xFF, 1);
    if (rec != NULL) {
        memcpy(*(u8 **) (rec + 0x98), &data, 0x50);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/obj_spawn_effect50_with_sound.s")
#endif

extern f32 D_800A0F1C;
extern f32 D_800A0F20;

/* was func_150D9304 */
void trail_point_integrate(f32 *arg0, f32 *arg1, f32 arg2) {
    vertex sp4 = *(vertex *)arg1;

    arg1[1] += D_800A0F1C * arg2;
    arg0[0] += sp4.x * arg2;
    arg0[1] += sp4.y * arg2 + D_800A0F20 * arg2 * arg2;
    arg0[2] += sp4.z * arg2;
}

/* was func_150D939C */
void trail_stop_emitting(u8 *arg0) {
    arg0[0x30] = 0;
    *(u16 *)(arg0 + 0x1E) &= ~2;
    *(u16 *)(arg0 + 0x1E) |= 8;
    *(u16 *)(arg0 + 0x1E) |= 1;
    *(u16 *)(arg0 + 0x1C) = 0x28;
}

#ifdef NON_MATCHING
// path_points_catch_up: P250. Handler (s32 (u8 *), function table at ELF file offset 0x24A5D8, next to
// trail_emit_update) of an object that walks a ring of 0x24-byte points (+0x94; +0x25 = point count, +0x2E = last
// processed point, +0x2D = current point, +0x2C = state). Returns 0 at once when the state is < 2 and flag 8 of +0x1E
// is set. Otherwise every point from the last processed one back to the current one (walking backwards around the
// ring) gets trail_point_integrate(point, point + 0xC, D_800BE9A4); +0x54..0x5C becomes the current point's position (zero
// in state <= 0). The timer +0x4D of the record at +0x98 advances by D_800BE9E4; past 50 it restarts and the
// record's owner (+0) part +0x31C gets its counter +0x1AA bumped. Returns 1.
/* was func_150D93CC */
s32 path_points_catch_up(u8 *p) {
    u8 *pts = *(u8 **) (p + 0x94);
    u8 *rec = *(u8 **) (p + 0x98);
    s32 i;

    if (*(s8 *) (p + 0x2C) < 2 && (*(u16 *) (p + 0x1E) & 8)) {
        return 0;
    }
    i = *(s8 *) (p + 0x2E);
    if (i != *(s8 *) (p + 0x2D)) {
        do {
            i--;
            if (i < 0) {
                i = p[0x25] - 1;
            }
            trail_point_integrate((f32 *) (pts + i * 0x24), (f32 *) (pts + i * 0x24 + 0xC), D_800BE9A4);
        } while (i != *(s8 *) (p + 0x2D));
    }
    if (*(s8 *) (p + 0x2C) > 0) {
        s32 *pos = (s32 *) (pts + *(s8 *) (p + 0x2D) * 0x24);   /* copied as words, like the asm */

        *(s32 *) (p + 0x54) = pos[0];
        *(s32 *) (p + 0x58) = pos[1];
        *(s32 *) (p + 0x5C) = pos[2];
    } else {
        *(f32 *) (p + 0x54) = 0.0f;
        *(f32 *) (p + 0x58) = 0.0f;
        *(f32 *) (p + 0x5C) = 0.0f;
    }
    *(s8 *) (rec + 0x4D) += D_800BE9E4;
    if (*(s8 *) (rec + 0x4D) >= 0x33) {
        u8 *owner = *(u8 **) rec;
        u8 *part;

        if (owner != NULL && (part = *(u8 **) (owner + 0x31C)) != NULL) {
            *(s16 *) (part + 0x1AA) += 1;
        }
        *(s8 *) (rec + 0x4D) = 0;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/path_points_catch_up.s")
#endif

#ifdef NON_MATCHING
extern f32 D_800A0F24;
extern f32 D_800A0F28;
extern f32 D_800A0F2C;
extern f32 D_800A0F34;
/* was func_150D952C */
s32 trail_emit_update(u8 *arg0) {
    struct {
        f32 uAC;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        u8 padD0[0x8];
        f32 uD8;
        f32 uDC;
        u8 padE0[0xC];
        f32 uEC;
        f32 uF0;
        f32 uF4;
        f32 uF8;
        f32 uFC;
        f32 u100;
    } sp;
    u8 *sp88;
    u8 *sp84;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp60;
    f32 *temp_a0;
    f32 *temp_s2;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    f32 temp_f4;
    f32 temp_f6;
    f32 temp_f8;
    f32 var_f0;
    f32 var_f12;
    f32 var_f14;
    f32 var_f16;
    f32 var_f20;
    f32 var_f2;
    s32 temp_s5;
    s8 temp_v1_2;
    u8 *temp_s1;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_s1 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_s5 = (*(s32 *)((u8 *)arg0 + 0x94));
    temp_s2 = (*(f32 **)((u8 *)temp_s1 + 0));
    if (((*(u8 *)((u8 *)((*(u8 **)((u8 *)temp_s2 + 0x31C))) + 0x78)) != 3) || ((s32) (*(u8 *)((u8 *)temp_s2 + 0x1CA)) <= 0)) {
        trail_stop_emitting(arg0);
    }
    if (((*(s32 *)((u8 *)temp_s2 + 0)) == 0) || ((*(u8 *)((u8 *)temp_s1 + 4)) != (*(u8 *)((u8 *)temp_s2 + 0x3B)))) {
        return 0;
    }
    trail_get_emit_point(temp_s2, &sp.uF8);
    trail_get_aim((s32) temp_s2, (s32) &sp.uEC);
    temp_v1 = temp_s1 + 0x20;
    (*(f32 *)((u8 *)arg0 + 0x10)) = (f32) (*(f32 *)((u8 *)(&sp.uF8) + 0));
    (*(s32 *)((u8 *)arg0 + 0x14)) = (s32) (*(s32 *)((u8 *)(&sp.uF8) + 4));
    (*(s32 *)((u8 *)arg0 + 0x18)) = (s32) (*(s32 *)((u8 *)(&sp.uF8) + 8));
    if ((*(u8 *)((u8 *)temp_s1 + 0x4C)) & 1) {
        if ((*(u16 *)((u8 *)((*(u8 **)((u8 *)temp_s2 + 0x31C))) + 0x8A)) & 0x2000) {
            var_f0 = D_800A0F24;
            (*(f32 *)((u8 *)temp_s1 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x3C)) + (D_800A0F28 * D_800BE9A4));
            if ((*(f32 *)((u8 *)temp_s1 + 0x3C)) > D_800A0F24) {
                goto block_11;
            }
        } else {
            var_f0 = D_800A0F2C;
            (*(f32 *)((u8 *)temp_s1 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x3C)) - (D_800A0F28 * D_800BE9A4));
            if ((*(f32 *)((u8 *)temp_s1 + 0x3C)) < D_800A0F2C) {
block_11:
                (*(f32 *)((u8 *)temp_s1 + 0x3C)) = var_f0;
            }
        }
    }
    temp_v0 = temp_s1 + 0x14;
    (*(f32 *)((u8 *)temp_s1 + 0x34)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x34)) + (D_800A0F34 * D_800BE9A4));
    temp_f2 = (*(f32 *)((u8 *)temp_s1 + 0x34));
    if (temp_f2 > 1.0f) {
        (*(f32 *)((u8 *)(&sp.uB8) + 0)) = (*(f32 *)((u8 *)temp_v0 + 0));
        var_f20 = (*(f32 *)((u8 *)temp_s1 + 0x2C)) + D_800BE9A4;
        (*(s32 *)((u8 *)(&sp.uB8) + 4)) = (s32) (*(s32 *)((u8 *)temp_v0 + 4));
        temp_f0 = 1.0f / temp_f2;
        (*(s32 *)((u8 *)(&sp.uB8) + 8)) = (s32) (*(s32 *)((u8 *)temp_v0 + 8));
        (*(f32 *)((u8 *)(&sp.uAC) + 0)) = (*(f32 *)((u8 *)temp_v1 + 0));
        (*(s32 *)((u8 *)(&sp.uAC) + 4)) = (s32) (*(s32 *)((u8 *)temp_v1 + 4));
        (*(s32 *)((u8 *)(&sp.uAC) + 8)) = (s32) (*(s32 *)((u8 *)temp_v1 + 8));
        var_f16 = var_f20 * temp_f0;
        temp_f4 = sp.u100 - (*(f32 *)((u8 *)temp_s1 + 0x1C));
        temp_f26 = (sp.uF8 - (*(f32 *)((u8 *)temp_s1 + 0x14))) * temp_f0;
        sp.uD8 = temp_f4;
        temp_f28 = (sp.uFC - (*(f32 *)((u8 *)temp_s1 + 0x18))) * temp_f0;
        temp_f6 = sp.uEC - (*(f32 *)((u8 *)temp_s1 + 0x20));
        sp.uC4 = temp_f6;
        sp60 = temp_f4;
        temp_f8 = sp.uF0 - (*(f32 *)((u8 *)temp_s1 + 0x24));
        sp.uC8 = temp_f8;
        sp84 = temp_v1;
        sp88 = temp_v0;
        temp_f10 = sp.uF4 - (*(f32 *)((u8 *)temp_s1 + 0x28));
        sp.uCC = temp_f10;
        var_f2 = temp_f6 * temp_f0;
        var_f12 = temp_f8 * temp_f0;
        var_f14 = temp_f10 * temp_f0;
        do {
            temp_a0 = ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24) + temp_s5;
            (*(f32 *)((u8 *)temp_a0 + 0)) = (*(f32 *)((u8 *)(&sp.uB8) + 0));
            (*(s32 *)((u8 *)temp_a0 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.uB8) + 4));
            (*(s32 *)((u8 *)temp_a0 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.uB8) + 8));
            (*(f32 *)((u8 *)temp_a0 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x3C)) * sp.uAC);
            (*(f32 *)((u8 *)temp_a0 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x3C)) * sp.uB0);
            (*(f32 *)((u8 *)temp_a0 + 0x18)) = 0.0f;
            (*(s8 *)((u8 *)temp_a0 + 0x1C)) = 0xFF;
            (*(f32 *)((u8 *)temp_a0 + 0x20)) = 0.0f;
            (*(f32 *)((u8 *)temp_a0 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x3C)) * sp.uB4);
            sp.uDC = var_f16;
            sp70 = var_f14;
            sp74 = var_f12;
            sp78 = var_f2;
            trail_point_integrate(temp_a0, ((f32 *)((u8 *)temp_a0 + 0xC)), var_f20);
            (*(s8 *)((u8 *)arg0 + 0x2E)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2E)) + 1);
            var_f20 -= var_f16;
            if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2E)) = 0;
            }
            temp_v1_2 = (*(s8 *)((u8 *)arg0 + 0x2D));
            (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) + 1);
            if (temp_v1_2 == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) (temp_v1_2 + 1);
                if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                }
                (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
            }
            sp.uB8 += temp_f26;
            sp.uBC += temp_f28;
            sp.uC0 += temp_f4 * temp_f0;
            sp.uAC += var_f2;
            sp.uB0 += var_f12;
            sp.uB4 += var_f14;
            (*(f32 *)((u8 *)temp_s1 + 0x34)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x34)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s1 + 0x34)) > 1.0f);
        (*(f32 *)((u8 *)sp88 + 0)) = (f32) (*(f32 *)((u8 *)(&sp.uB8) + 0));
        (*(s32 *)((u8 *)sp88 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.uB8) + 4));
        (*(s32 *)((u8 *)sp88 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.uB8) + 8));
        (*(f32 *)((u8 *)sp84 + 0)) = (f32) (*(f32 *)((u8 *)(&sp.uAC) + 0));
        (*(s32 *)((u8 *)sp84 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.uAC) + 4));
        (*(s32 *)((u8 *)sp84 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.uAC) + 8));
        (*(f32 *)((u8 *)temp_s1 + 0x2C)) = var_f20;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/trail_emit_update.s")
#endif
#ifdef NON_MATCHING
typedef struct {
    u8 b[0x12];
} TrailSurf;

typedef struct {
    u8 *obj;          /* 0x00 object hit */
    f32 dist;         /* 0x04 distance along the segment */
    f32 pos[3];       /* 0x08 hit point */
    u8 pad14[0x30];
    TrailSurf surf;   /* 0x44 surface record of a world hit */
    u8 pad56[3];
    u8 count;         /* 0x59 0 = nothing hit, 1 = world, >= 2 = an object */
    u8 pad5A[0xE];
} TrailHit;           /* func_15081A90's hit record */

f32 sqrtf(f32);
f32 func_15143E64(f32 *);
s32 func_15081A90(u8 *, f32, f32, f32, f32, f32, f32, TrailHit *, f32, s32, s32, s32, s32, s32, s32);
void trail_hit_effects(u8 *, TrailHit *, f32 *);
void move_xz_towards(f32, f32, f32, f32 *, f32 *);
f32 func_150484A0(f32, f32);
s32 obj_send_hit(u8 *, s32, u16, s32);
f32 func_15144528(f32, f32, f32);
extern f32 D_800BE9A4;
static const f32 trail_max_len[1] = { 1195.0f };       /* D_800A0F38 */
static const f32 trail_no_inv[1] = { -9999.0f };       /* D_800A0F3C, D_800A0F40 */
static const f32 trail_push_k[1] = { 0.0010526315f };  /* D_800A0F44 */
static const f32 trail_push_a[1] = { 0.455f };         /* D_800A0F48 */
static const f32 trail_push_b[1] = { 0.201f };         /* D_800A0F4C */
static const f32 trail_slow[1] = { 0.72f };            /* D_800A0F50 */
static const f32 trail_dir_k[1] = { -0.07f };          /* D_800A0F54 */
static const f32 trail_ang_k[1] = { 10430.378f };      /* D_800A0F58 (0x10000 / 2 pi) */
static const f32 trail_s_speed[1] = { -395.0f };       /* D_800A0F5C */
static const f32 trail_s_range[1] = { 16383.0f };      /* D_800A0F60, D_800A0F68 */
static const f32 trail_s_k[1] = { 29.029999f };        /* D_800A0F64 */
static const f32 trail_fade[1] = { 0.80200005f };      /* D_800A0F6C */

// trail_update: per-frame update of an object's point trail (the ring of 0x24-byte points at obj+0x94: pos +0x00,
// segment length +0x18, alpha +0x1C, texture s +0x20; count obj+0x25, points in use obj+0x2C, tail obj+0x2D,
// head obj+0x2E; data = obj+0x98: owner object +0x00, sound +0x30, texture scroll +0x38). Walking from the newest point
// (or the live position obj+0x10 when obj+0x1E bit 1 is set) to the tail it measures each segment (func_15143E64)
// and cuts the trail at 1195 units (shortens the segment and drops the older points). Every segment is ray-cast
// (func_15081A90, owner skipped): on a hit, trail_hit_effects spawns the impact effects; an object hit (count >= 2) is
// flagged (+0x2EC) and, by kind (+0x4), stunned (0x3A: state 10), pushed (0x10: move_xz_towards along the hit / trail
// direction, state 0xF), set to state 3 (0x91) / 0x2C (0x90) or damaged (obj_send_hit 0xE0036 with the trail's
// heading); the trail then ends at the hit point and the sound (data+0x30) plays there (func_1000F91C). Finally it
// scrolls the texture (data+0x38, -395 / s, wrapped to +-16383 by func_15144528), gives each point its s, and fades
// the oldest 80.2% of the length out (alpha 155 -> 0). Returns 1.
/* was func_150D99AC */
s32 trail_stream_update(u8 *obj) {
    u8 *data = *(u8 **)(obj + 0x98);
    u8 *pts = *(u8 **)(obj + 0x94);
    u8 *owner = *(u8 **)data;
    u8 *cur;
    u8 *nxt;
    u8 *hobj;
    TrailHit hit;
    f32 dir[3];
    f32 unit[3];
    f32 total;
    f32 len, inv, cut;
    f32 dx, dz, s;
    f32 sum, fade, rest, rinv;
    s32 i;

    if (*(s8 *)(obj + 0x2C) >= 2) {
        total = 0.0f;
        i = *(s8 *)(obj + 0x2E);
        if (*(u16 *)(obj + 0x1E) & 2) {
            cur = obj + 0x10;
        } else {
            i--;
            if (i < 0) {
                i = *(u8 *)(obj + 0x25) - 1;
            }
            cur = pts + i * 0x24;
        }
        do {
            inv = trail_no_inv[0];
            i--;
            if (i < 0) {
                i = *(u8 *)(obj + 0x25) - 1;
            }
            nxt = pts + i * 0x24;
            dir[0] = *(f32 *)(nxt + 0) - *(f32 *)(cur + 0);
            dir[1] = *(f32 *)(nxt + 4) - *(f32 *)(cur + 4);
            dir[2] = *(f32 *)(nxt + 8) - *(f32 *)(cur + 8);
            len = func_15143E64(dir);
            total += len;
            *(f32 *)(nxt + 0x18) = len;
            if (trail_max_len[0] < total) {
                /* too long: shorten this segment to the limit and drop the older points */
                len = *(f32 *)(nxt + 0x18);
                if (len != 0.0f) {
                    inv = 1.0f / len;
                    unit[0] = dir[0] * inv;
                    unit[1] = dir[1] * inv;
                    unit[2] = dir[2] * inv;
                    cut = (total - trail_max_len[0]) * inv;
                    *(f32 *)(nxt + 0) -= dir[0] * cut;
                    *(f32 *)(nxt + 4) -= dir[1] * cut;
                    *(f32 *)(nxt + 8) -= dir[2] * cut;
                    *(f32 *)(nxt + 0x18) *= 1.0f - cut;
                }
                total = trail_max_len[0];
                while (i != *(s8 *)(obj + 0x2D)) {
                    (*(s8 *)(obj + 0x2D))++;
                    if (*(u8 *)(obj + 0x25) == *(s8 *)(obj + 0x2D)) {
                        *(s8 *)(obj + 0x2D) = 0;
                    }
                    (*(s8 *)(obj + 0x2C))--;
                }
            }
            len = *(f32 *)(nxt + 0x18);
            if (len != 0.0f) {
                if (inv == trail_no_inv[0]) {
                    inv = 1.0f / len;
                    unit[0] = dir[0] * inv;
                    unit[1] = dir[1] * inv;
                    unit[2] = dir[2] * inv;
                    len = *(f32 *)(nxt + 0x18);
                }
                func_15081A90(owner, *(f32 *)(cur + 0), *(f32 *)(cur + 4), *(f32 *)(cur + 8), unit[0], unit[1],
                              unit[2], &hit, len, 0, 0, 1, -1, 0, 0);
                if (hit.count != 0) {
                    trail_hit_effects(obj, &hit, unit);
                    hobj = hit.obj;
                    if (hit.count >= 2) {
                        *(s32 *)(hobj + 0x2EC) = 1;
                        if (*(u8 *)(hobj + 4) == 0x3A) {
                            *(u8 *)(hobj + 0x232) = 10;
                            *(s32 *)(hobj + 0x218) = 0;
                        } else if (*(u8 *)(hobj + 4) == 0x10 && *(u8 *)(hobj + 0x251) == 1) {
                            move_xz_towards(*(f32 *)(hobj + 0x14) - hit.pos[0], *(f32 *)(hobj + 0x1C) - hit.pos[2],
                                          (1.0f - (total - 50.0f) * trail_push_k[0]) * trail_push_a[0] + trail_push_b[0],
                                          (f32 *)(hobj + 0x164), (f32 *)(hobj + 0x168));
                            if (*(u8 *)(hobj + 0x232) == 0xF) {
                                *(s32 *)(hobj + 0x218) = 0;
                            }
                        } else if (*(u8 *)(hobj + 4) == 0x10) {
                            dx = *(f32 *)(nxt + 0) - *(f32 *)(owner + 0x14);
                            dz = *(f32 *)(nxt + 8) - *(f32 *)(owner + 0x1C);
                            if (*(u8 *)(hobj + 0x232) == 0x10) {
                                *(f32 *)(hobj + 0x3C) *= trail_slow[0];
                                s = 1.0f / (sqrtf(dx * dx + dz * dz) * trail_dir_k[0]);
                                move_xz_towards(dx * s, dz * s, 0.7f, (f32 *)(hobj + 0x164), (f32 *)(hobj + 0x168));
                            }
                            if (*(u8 *)(hobj + 0x125) == 0) {
                                *(u8 *)(hobj + 0x232) = 0xF;
                                *(s32 *)(hobj + 0x218) = 0;
                            }
                        } else if (*(u8 *)(hobj + 4) == 0x91) {
                            *(u8 *)(hobj + 0x232) = 3;
                            *(s32 *)(hobj + 0x218) = 0;
                        } else if (*(u8 *)(hobj + 4) == 0x90) {
                            *(u8 *)(hobj + 0x232) = 0x2C;
                            *(s32 *)(hobj + 0x218) = 0;
                        } else {
                            s32 slot = (owner - (u8 *)D_800CC2D0) / 0x32C;
                            u32 ang = func_150484A0(unit[0], unit[2]) * trail_ang_k[0];

                            obj_send_hit(hobj, 0xE0036, (u16)((ang - 0x4000) | 1), slot);
                        }
                    }
                    /* the trail ends at the hit point */
                    *(f32 *)(nxt + 0) = hit.pos[0];
                    *(f32 *)(nxt + 4) = hit.pos[1];
                    *(f32 *)(nxt + 8) = hit.pos[2];
                    total -= *(f32 *)(nxt + 0x18);
                    *(f32 *)(nxt + 0x18) = hit.dist;
                    total += *(f32 *)(nxt + 0x18);
                    while (i != *(s8 *)(obj + 0x2D)) {
                        (*(s8 *)(obj + 0x2D))++;
                        if (*(u8 *)(obj + 0x25) == *(s8 *)(obj + 0x2D)) {
                            *(s8 *)(obj + 0x2D) = 0;
                        }
                        (*(s8 *)(obj + 0x2C))--;
                    }
                    if (*(u16 *)(data + 0x30) != 0) {
                        func_1000F91C(*(u16 *)(data + 0x30), 0x7FFF, 0, 0, 0, (s16)(s32)*(f32 *)(nxt + 0),
                                      (s16)(s32)*(f32 *)(nxt + 4), (s16)(s32)*(f32 *)(nxt + 8), 500, 5000);
                    }
                }
            }
            cur = nxt;
        } while (i != *(s8 *)(obj + 0x2D));
    }

    if (*(s8 *)(obj + 0x2C) >= 2) {
        /* texture scroll; each point's s = scroll + 29.03 per unit of length from the head */
        *(f32 *)(data + 0x38) += trail_s_speed[0] * D_800BE9A4;
        *(f32 *)(data + 0x38) = func_15144528(*(f32 *)(data + 0x38), trail_s_range[0], -16384.0f);
        sum = 0.0f;
        i = *(s8 *)(obj + 0x2E) - 1;
        for (;;) {
            if (i < 0) {
                i = *(u8 *)(obj + 0x25) - 1;
            }
            nxt = pts + i * 0x24;
            sum += *(f32 *)(nxt + 0x18);
            *(f32 *)(nxt + 0x20) = func_15144528(*(f32 *)(data + 0x38) + sum * trail_s_k[0], trail_s_range[0], -16384.0f);
            if (i == *(s8 *)(obj + 0x2D)) {
                break;
            }
            i--;
        }
    }

    if (*(s8 *)(obj + 0x2C) >= 2) {
        /* alpha 155 up to 80.2% of the length, then a linear fade to the tail */
        fade = total * trail_fade[0];
        rest = total - fade;
        rinv = 1.0f / rest;
        sum = 0.0f;
        i = *(s8 *)(obj + 0x2E) - 1;
        for (;;) {
            if (i < 0) {
                i = *(u8 *)(obj + 0x25) - 1;
            }
            nxt = pts + i * 0x24;
            sum += *(f32 *)(nxt + 0x18);
            if (fade < sum) {
                *(u8 *)(nxt + 0x1C) = (u32)((rest - (sum - fade)) * rinv * 155.0f);
            } else {
                *(u8 *)(nxt + 0x1C) = 155;
            }
            if (i == *(s8 *)(obj + 0x2D)) {
                break;
            }
            i--;
        }
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/trail_stream_update.s")
#endif

#ifdef NON_MATCHING
f32 sqrtf(f32);
void func_151D6310(void *, s16, s32, void *, u8 *);
Gfx *func_15142E24(Gfx *, void *, s32, s32, s32, s32, s32, s32, s32, u8 *, s32);
Gfx *func_15142B7C(Gfx *gfx, s32 set, s32 clear);
Gfx *gfx_set_combine_mode(Gfx *, u8, u8 *);
Gfx *func_15142FBC(Gfx *, s32, s32, u8 *);
extern u8 D_800915E8[];
extern s32 D_800A4EA8[];
extern s32 D_800D30BC;

// trail_draw_ribbon: draws the object's point trail as a camera-facing textured ribbon. The trail is a ring of
// 0x24-byte points at obj+0x94 (pos +0x00, alpha +0x1C, texture s +0x20; count obj+0x25, head obj+0x2E, tail
// obj+0x2D, at least 2 points: obj+0x2C). It walks back from the newest point (or from the live position obj+0x10
// with s = data+0x38 when obj+0x1E bit 1 is set) to the tail; every segment a->b gets a quad whose half-width is
// 4 units along (a - b) x (P - camera), 4 vertices (tc t 0x400 / 0, white, the alpha of b) and two triangles. When s
// drops along a segment (texture wrap), the last two vertices are copied for the next quad and the drawn ones get
// s - 0x8000. Vertices come from func_151D6310 (count * 32 + 0xA0 bytes); returns the advanced display list.
/* was func_150DA1FC */
Gfx *trail_draw_ribbon(u8 *obj, Gfx *gfx, s16 id) {
    u8 *pts = *(u8 **)(obj + 0x94);  /* 0x24-byte trail points */
    u8 *data = *(u8 **)(obj + 0x98);
    u8 *pb;
    Vtx *vtx;
    f32 *cam;
    u8 flag;
    f32 a[3];  /* newer point of the segment */
    f32 b[3];  /* older point */
    f32 sa, sb;
    f32 e[3], d[3], n[3];
    f32 len2, inv;
    s32 i, prev;
    u8 alpha;
    s32 t;

    if (*(s8 *)(obj + 0x2C) < 2) {
        return gfx;
    }
    func_151D6310(obj + 0x84, id, *(u8 *)(obj + 0x25) * 32 + 0xA0, &vtx, NULL);
    if (vtx == NULL) {
        return gfx;
    }
    cam = func_15144B34(id);
    flag = 1;
    gfx = func_15142E24(gfx, D_800915E8, 0, 0, 0, 0, 0x92, 0, 0, &flag, 3);
    gfx = func_15142B7C(gfx, 0x220005, 0x1D0600);
    gfx = gfx_set_combine_mode(gfx, 0x4E, &flag);
    gfx = func_15142FBC(gfx, D_800D30BC | 0x80000 | 0x2CA0, D_800A4EA8[7] | D_800A4EA8[6], &flag);

    if (*(u16 *)(obj + 0x1E) & 2) {
        i = *(s8 *)(obj + 0x2E) - 1;
        if (i < 0) {
            i = *(u8 *)(obj + 0x25) - 1;
        }
        a[0] = *(f32 *)(obj + 0x10);
        a[1] = *(f32 *)(obj + 0x14);
        a[2] = *(f32 *)(obj + 0x18);
        sa = *(f32 *)(data + 0x38);
    } else {
        prev = *(s8 *)(obj + 0x2E) - 1;
        if (prev < 0) {
            prev = *(u8 *)(obj + 0x25) - 1;
        }
        i = prev - 1;
        if (i < 0) {
            i = *(u8 *)(obj + 0x25) - 1;
        }
        a[0] = *(f32 *)(pts + prev * 0x24 + 0);
        a[1] = *(f32 *)(pts + prev * 0x24 + 4);
        a[2] = *(f32 *)(pts + prev * 0x24 + 8);
        sa = *(f32 *)(pts + prev * 0x24 + 0x20);
    }
    pb = pts + i * 0x24;
    b[0] = *(f32 *)(pb + 0);
    b[1] = *(f32 *)(pb + 4);
    b[2] = *(f32 *)(pb + 8);
    sb = *(f32 *)(pb + 0x20);
    alpha = *(u8 *)(pb + 0x1C);

    /* first edge: the two vertices at a */
    d[0] = a[0] - cam[0];
    d[1] = a[1] - cam[1];
    d[2] = a[2] - cam[2];
    e[0] = a[0] - b[0];
    e[1] = a[1] - b[1];
    e[2] = a[2] - b[2];
    n[0] = e[1] * d[2] - d[1] * e[2];
    n[1] = e[2] * d[0] - d[2] * e[0];
    n[2] = e[0] * d[1] - d[0] * e[1];
    len2 = n[0] * n[0] + n[1] * n[1] + n[2] * n[2];
    if (len2 == 0.0f) {
        n[0] = n[1] = n[2] = 0.0f;
    } else {
        inv = 4.0f / sqrtf(len2);
        n[0] *= inv;
        n[1] *= inv;
        n[2] *= inv;
    }
    t = sa;
    vtx->v.ob[0] = (s32)(a[0] + n[0]);
    vtx->v.ob[1] = (s32)(a[1] + n[1]);
    vtx->v.ob[2] = (s32)(a[2] + n[2]);
    vtx->v.tc[0] = t;
    vtx->v.tc[1] = 0x400;
    vtx->v.cn[0] = vtx->v.cn[1] = vtx->v.cn[2] = 0xFF;
    vtx->v.cn[3] = alpha;
    vtx->v.flag = 0;
    vtx++;
    vtx->v.ob[0] = (s32)(a[0] - n[0]);
    vtx->v.ob[1] = (s32)(a[1] - n[1]);
    vtx->v.ob[2] = (s32)(a[2] - n[2]);
    vtx->v.tc[0] = t;
    vtx->v.tc[1] = 0;
    vtx->v.cn[0] = vtx->v.cn[1] = vtx->v.cn[2] = 0xFF;
    vtx->v.cn[3] = alpha;
    vtx->v.flag = 0;
    vtx++;

    do {
        /* the two vertices at b, then the quad a-b */
        d[0] = b[0] - cam[0];
        d[1] = b[1] - cam[1];
        d[2] = b[2] - cam[2];
        e[0] = a[0] - b[0];
        e[1] = a[1] - b[1];
        e[2] = a[2] - b[2];
        n[0] = e[1] * d[2] - d[1] * e[2];
        n[1] = e[2] * d[0] - d[2] * e[0];
        n[2] = e[0] * d[1] - d[0] * e[1];
        len2 = n[0] * n[0] + n[1] * n[1] + n[2] * n[2];
        if (len2 == 0.0f) {
            n[0] = n[1] = n[2] = 0.0f;
        } else {
            inv = 4.0f / sqrtf(len2);
            n[0] *= inv;
            n[1] *= inv;
            n[2] *= inv;
        }
        t = sb;
        vtx->v.ob[0] = (s32)(b[0] + n[0]);
        vtx->v.ob[1] = (s32)(b[1] + n[1]);
        vtx->v.ob[2] = (s32)(b[2] + n[2]);
        vtx->v.tc[0] = t;
        vtx->v.tc[1] = 0x400;
        vtx->v.cn[0] = vtx->v.cn[1] = vtx->v.cn[2] = 0xFF;
        vtx->v.cn[3] = alpha;
        vtx->v.flag = 0;
        vtx++;
        vtx->v.ob[0] = (s32)(b[0] - n[0]);
        vtx->v.ob[1] = (s32)(b[1] - n[1]);
        vtx->v.ob[2] = (s32)(b[2] - n[2]);
        vtx->v.tc[0] = t;
        vtx->v.tc[1] = 0;
        vtx->v.cn[0] = vtx->v.cn[1] = vtx->v.cn[2] = 0xFF;
        vtx->v.cn[3] = alpha;
        vtx->v.flag = 0;
        vtx++;
        gfx->words.w0 = 0x01004008; gfx->words.w1 = (u32)(vtx - 4); gfx++;  /* gSPVertex(vtx - 4, 4, 0) */
        gfx->words.w0 = 0x05000204; gfx->words.w1 = 0; gfx++;               /* gSP1Triangle(0, 1, 2) */
        gfx->words.w0 = 0x05020604; gfx->words.w1 = 0; gfx++;               /* gSP1Triangle(1, 3, 2) */
        if (sb < sa) {
            memcpy(vtx, vtx - 2, 2 * sizeof(Vtx));
            vtx[-2].v.tc[0] -= 0x8000;
            vtx[-1].v.tc[0] -= 0x8000;
            vtx += 2;
        }
        prev = i;
        i--;
        pb -= 0x24;
        if (i < 0) {
            i = *(u8 *)(obj + 0x25) - 1;
            pb = pts + i * 0x24;
        }
        a[0] = *(f32 *)(pts + prev * 0x24 + 0);
        a[1] = *(f32 *)(pts + prev * 0x24 + 4);
        a[2] = *(f32 *)(pts + prev * 0x24 + 8);
        b[0] = *(f32 *)(pb + 0);
        b[1] = *(f32 *)(pb + 4);
        b[2] = *(f32 *)(pb + 8);
        sa = *(f32 *)(pts + prev * 0x24 + 0x20);
        alpha = *(u8 *)(pb + 0x1C);
        sb = *(f32 *)(pb + 0x20);
    } while (prev != *(s8 *)(obj + 0x2D));
    return gfx;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/trail_draw_ribbon.s")
#endif

/* was func_150DAA04 */
void trail_stop_sound(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    u16 temp_a1 = *(u16 *)(temp_v0 + 0x30);

    if (temp_a1 != 0) {
        func_100111C8(temp_a1);
    }
}

/* was func_150DAA34 */
void trail_free(s32 arg0) {
    trail_stop_sound(arg0);
    func_15147E64(arg0);
}

/* was func_150DAA60 */
void trail_free_alt(s32 arg0) {
    trail_stop_sound(arg0);
    func_15147E98(arg0);
}

/* was func_150DAA8C */
void trail_handle_msg(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = *(u8 **)((u8 *)arg0 + 0x98);
    if (arg2 == 0x44) {
        if ((u16)(*(s32 *)v == *(s32 *)arg1 || v[4] == arg1[4])) { // fakematch: permuter artifact (u16 cast of the condition)
            *(f32 *)(v + 0x3C) = *(f32 *)(arg1 + 8);
dummy_label: ; // fakematch: permuter artifact (unused label)
        }
    } else if (arg2 == 0) {
        s32 t = *(s32 *)arg1;
        if (t == *(s32 *)v || arg1[4] == v[4]) {
            node_destroy(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)v) {
            *(s32 *)v = *(s32 *)(arg1 + 4);
            v[4] = arg1[9];
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)v) {
            *(s32 *)v = *(s32 *)arg1;
            v[4] = arg1[8];
        }
    }
}

/* was func_150DAB6C */
void trail_send_aim_msg(u8 *arg0, f32 arg1) {
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = arg1;
    func_151482D4(&tmp, 0x44);
}

s32 func_15131D98(s32, s32, u8 *, s32);
#ifdef NON_MATCHING
void func_15131EC8(s32, f32, u8 *); /* P95: f32 (float bits were passed as an int) */
#else
void func_15131EC8(s32, s32, u8 *);
#endif

/* was func_150DABA8 */
s32 particle_move_step(s32 arg0, s32 arg1) {
    u8 *sp20;
    u8 *temp_a2;

    temp_a2 = arg0 + 0xA8;
    sp20 = temp_a2;
    func_15131D98(arg0, arg0 + 0xAC, temp_a2, arg0 + 0xAA);
#ifdef NON_MATCHING
    func_15131EC8(arg0 + 0x58, (*(f32 *)((u8 *)temp_a2 + 0xC)), temp_a2); /* P95: f32 (float bits were passed as an int) */
#else
    func_15131EC8(arg0 + 0x58, (*(s32 *)((u8 *)temp_a2 + 0xC)), temp_a2);
#endif
    return 1;
}

#ifdef NON_MATCHING
void func_150475B0(f32 *, TrailHit *);
void func_1515423C(u8 *, s32, s32, u8, s32);
void func_151541F4(u8 *, s32, s32, u8, s32);
static const f32 hitfx_spark_rate[1] = { 0.19900002f };   /* D_800A0F70 */
static const f32 hitfx_spark_rand[1] = { 0.15400001f };   /* D_800A0F74 */
static const f32 hitfx_spark_k[1] = { 0.993627f };        /* D_800A0F78 */
static const f32 hitfx_spark_size[1] = { 1.038235f };     /* D_800A0F7C */
static const f32 hitfx_spark_life_k[1] = { 0.091000006f }; /* D_800A0F80 */
static const f32 hitfx_spark_life[1] = { 0.101f };        /* D_800A0F84 */
static const f32 hitfx_dust_rate[1] = { 0.060000002f };   /* D_800A0F88 */
static const f32 hitfx_dust_q[6] = { 3.48f, 2.6599998f, 1.3310001f, 1.1600001f, 0.015f, 0.0069999998f }; /* D_800A0F8C..0FA0 */
static const f32 hitfx_dust_q30[1] = { 0.2f };            /* D_800A0FA4 */
static const f32 hitfx_smoke_rate[1] = { 0.2f };          /* D_800A0FA8 */
static const f32 hitfx_smoke_rand[1] = { 0.104f };        /* D_800A0FAC */

// trail_hit_effects: impact effects of a trail segment hit (trail_stream_update), with emission accumulators in the trail
// data (obj+0x98: +0x40 smoke, +0x44 dust, +0x48 sparks; one emission per whole unit). A hit on a character (count
// >= 2, kind 0x33 / 0x3A) emits spark particles (func_151307F0 with a 0x66-byte spec at the hit point, random size,
// life, flip bits 0x80 / 0x40 and alpha; the 16-byte random tail goes to particle+0xA8). Any other hit emits debris
// (func_1515423C, pushed back along -dir, for objects; func_151541F4 with the surface record hit+0x44 for the world)
// from a func_150475B0 frame. A world hit (count 1) also puffs smoke (impact_debris_spawn kind 3).
/* was func_150DABFC */
void trail_hit_effects(u8 *obj, TrailHit *hit, f32 *dir) {
    u8 *data = *(u8 **)(obj + 0x98);
    struct {
        u8 b[4];       /* 0x00 (sp140) */
        f32 spin[2];   /* 0x04 */
        f32 k;         /* 0x0C */
    } tail;
    struct {
        s32 u00;       /* 0x00 (sp150) */
        s32 u04;
        s16 u08;
        s16 u0A;       /* random life 70..80 */
        s32 u0C;
        s32 u10;
        u8 col0[4];    /* 0x14 */
        u8 col1[4];    /* 0x18 (alpha [3] random) */
        u8 u1C;
        u8 u1D;
        s16 u1E;
        s16 u20;
        s16 u22;
        f32 u24;
        f32 size[2];   /* 0x28 */
        f32 pos[3];    /* 0x30 */
        f32 vel[3];    /* 0x3C */
        f32 acc[3];    /* 0x48 */
        f32 u54;       /* random */
        s32 flags;     /* 0x58 */
        u8 pad5C[4];
        u8 u60[6];
    } spark;
    u8 frame[0x24];    /* spD4: func_150475B0 output */
    struct {
        f32 pos[3];    /* 0x00 (spF8) */
        f32 f[6];      /* 0x0C */
        s16 h[8];      /* 0x24 */
        u8 u34;
        f32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
    } debris;
    struct {
        u8 u00;        /* 0x00 (spA8) */
        f32 back[3];   /* 0x04 */
        f32 v0[3];     /* 0x10 */
        f32 v1[3];     /* 0x1C */
        f32 range;     /* 0x28 */
    } objfx;
    struct {
        f32 back[3];   /* 0x00 (sp84) */
        TrailSurf surf; /* 0x0C: the hit surface record */
        f32 range;     /* 0x20 */
    } wallfx;
    f32 v[3];
    s32 a, b, r1, r2;
    f32 f;
    s32 k;

    if (hit->count == 0) {
        return;
    }
    if (hit->count >= 2 && (*(u8 *)(hit->obj + 4) == 0x33 || *(u8 *)(hit->obj + 4) == 0x3A)) {
        *(f32 *)(data + 0x48) += (hitfx_spark_rate[0] + random_float() * hitfx_spark_rand[0]) * D_800BE9A4;
        if (1.0f < *(f32 *)(data + 0x48)) {
            spark.u08 = 0x5103;
            spark.u22 = 0x2E;
            spark.col1[1] = 0x55;
            spark.u1D = 0x6C;
            spark.u00 = 0x200005;
            spark.u1E = 0x2E;
            spark.u20 = 5;
            spark.flags = 0x90DE07;
            spark.u60[0] = 8;
            spark.u60[1] = 6;
            spark.u60[2] = 0x24;
            spark.u60[3] = 0xFF;
            spark.u04 = 0;
            spark.u0C = 0;
            spark.u10 = 0;
            spark.u60[4] = 0xFF;
            spark.u60[5] = 0;
            spark.col0[0] = 0xDD;
            spark.col0[1] = 0xD3;
            spark.col0[2] = 0xCD;
            spark.col0[3] = 0xFF;
            spark.col1[0] = 0x57;
            spark.col1[2] = 0x5A;
            spark.u1C = 0xFF;
            spark.vel[0] = spark.vel[1] = spark.vel[2] = 0.0f;
            tail.k = hitfx_spark_k[0];
            spark.u24 = hitfx_spark_size[0];
            spark.pos[0] = hit->pos[0];
            spark.pos[1] = hit->pos[1];
            spark.pos[2] = hit->pos[2];
            spark.acc[0] = ((f32 *)D_800A5860)[0];
            spark.acc[1] = ((f32 *)D_800A5860)[1];
            spark.acc[2] = ((f32 *)D_800A5860)[2];
            do {
                tail.b[0] = random_int();
                tail.b[1] = random_int();
                tail.b[2] = (u32)random_int() % 5 + 4;
                tail.b[3] = (u32)random_int() % 5 + 4;
                tail.spin[0] = random_float() * 10.0f;
                tail.spin[1] = random_float() * 10.0f;
                spark.u54 = random_float() * hitfx_spark_life_k[0] + hitfx_spark_life[0];
                spark.flags &= ~0xC0;
                a = (random_int() & 1) ? 0x80 : 0;
                b = (random_int() & 1) ? 0x40 : 0;
                spark.flags |= b | a;
                spark.col1[3] = (u32)random_int() % 101 + 100;
                spark.u0A = (u32)random_int() % 11 + 70;
                spark.size[1] = spark.size[0] = random_float() * 116.0f + 131.0f;
                k = func_151307F0((s32)&spark, 1, 0, 16, *(u8 *)(obj + 0xC), *(u8 *)(obj + 1));
                if (k != 0) {
                    memcpy((u8 *)k + 0xA8, &tail, 16);
                }
                *(f32 *)(data + 0x48) -= 1.0f;
            } while (1.0f < *(f32 *)(data + 0x48));
        }
    } else {
        f = hitfx_dust_rate[0];
        *(f32 *)(data + 0x44) += (f + random_float() * f) * D_800BE9A4;
        if (1.0f < *(f32 *)(data + 0x44)) {
            func_150475B0((f32 *)frame, hit);
            debris.pos[0] = hit->pos[0];
            debris.pos[1] = hit->pos[1];
            debris.pos[2] = hit->pos[2];
            debris.f[0] = hitfx_dust_q[0];
            debris.f[1] = hitfx_dust_q[1];
            debris.f[2] = hitfx_dust_q[2];
            debris.f[3] = hitfx_dust_q[3];
            debris.f[4] = hitfx_dust_q[4];
            debris.f[5] = hitfx_dust_q[5];
            debris.h[0] = 1;
            debris.h[1] = 2;
            debris.h[2] = 3;
            debris.h[3] = 1;
            debris.h[4] = 0x14;
            debris.h[5] = 0xA;
            debris.h[6] = 0xC8;
            debris.h[7] = 0x37;
            debris.u34 = 3;
            debris.u38 = hitfx_dust_q30[0];
            debris.u3C = 0x10;
            debris.u3E = 0xF;
            debris.u40 = 0;
            if (hit->count >= 2) {
                objfx.u00 = 1;
                objfx.back[0] = -dir[0];
                objfx.back[1] = -dir[1];
                objfx.back[2] = -dir[2];
                v[0] = ((f32 *)D_800A5860)[0];
                v[1] = ((f32 *)D_800A5860)[1];
                v[2] = ((f32 *)D_800A5860)[2];
                objfx.v1[0] = v[0];
                objfx.v1[1] = v[1];
                objfx.v1[2] = v[2];
                objfx.v0[0] = v[0];
                objfx.v0[1] = v[1];
                objfx.v0[2] = v[2];
                objfx.range = 300.0f;
                do {
                    func_1515423C((u8 *)&objfx, (s32)&debris, (s32)frame, *(u8 *)(obj + 0xC), *(u8 *)(obj + 1));
                    *(f32 *)(data + 0x44) -= 1.0f;
                } while (1.0f < *(f32 *)(data + 0x44));
            } else {
                wallfx.back[0] = -dir[0];
                wallfx.back[1] = -dir[1];
                wallfx.back[2] = -dir[2];
                wallfx.surf = hit->surf;
                wallfx.range = 300.0f;
                do {
                    func_151541F4((u8 *)&wallfx, (s32)&debris, (s32)frame, *(u8 *)(obj + 0xC), *(u8 *)(obj + 1));
                    *(f32 *)(data + 0x44) -= 1.0f;
                } while (1.0f < *(f32 *)(data + 0x44));
            }
        }
    }

    if (hit->count == 1) {
        *(f32 *)(data + 0x40) += (hitfx_smoke_rate[0] + random_float() * hitfx_smoke_rand[0]) * D_800BE9A4;
        if (1.0f < *(f32 *)(data + 0x40)) {
            do {
                f = random_float();
                r1 = random_int();
                r2 = random_int();
                impact_debris_spawn(3, f * 30.0f + 15.0f, (u32)r1 % 101 + 100, (s32)&hit->surf, (struct17 *)hit->pos,
                              (u32)r2 % 81 + 60, 1, 1, 1, *(u8 *)(obj + 0xC), *(u8 *)(obj + 1));
                *(f32 *)(data + 0x40) -= 1.0f;
            } while (1.0f < *(f32 *)(data + 0x40));
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/trail_hit_effects.s")
#endif
