#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_1500C2A0 */
void debris_counts_reset(void) {
    s32 i;

    for (i = 0; i < 233; i++) {
        D_800DC468[i] = 0;
    }

    D_800DC460 = 0;
    D_800DC464 = 0;
    D_800DC63C = 0;
}


s32 spawn_zone_pick_point(struct_eu_15144598 *, f32 *, f32 *, f32 *, f32 *);
void collision_select_area(s32);
s32 zone_tree_find_leaf(s32, s32);
s32 mdl_particle_spawn(f32 *, s32, s32, s32, s32, s32);
extern u16 g_debris_a_sound_ids[9]; /* sound ids; the heavy ones (0x48, 0x4B, 0x4E..0x51) get smaller pieces; was D_800964A0 */
extern f32 g_debris_a_density;    /* pieces per unit of record length x scale; was D_800964D0 */
extern f32 g_debris_a_rand_scale;    /* 1 / 65535; was D_800964D4 */
extern f32 g_debris_a_pi;    /* pi; was D_800964D8 */
extern f32 g_debris_a_p3c_range; /* was D_800964DC */
extern f32 g_debris_a_p3c_min; /* was D_800964E0 */
extern f32 g_debris_a_p40_range; /* was D_800964E4 */
extern f32 g_debris_a_p48_range; /* was D_800964E8 */

// record_debris_spawn: g_record_start_handlers entry 0x22 (level-start record). With n = length x scale x g_debris_a_density
// (length = spawn_region_volume(rec)), spawns a piece while n > 1 (n -= 1 each): at a random point of the record
// (spawn_zone_pick_point: x / z and the height range lo..hi), at a random height in the middle half of the range, with
// a random radius (up to the distance to the nearer end), angle, spins and one of the g_debris_a_sound_ids sounds, on the
// ground level of (x, z) (zone_tree_find_leaf), spawned by mdl_particle_spawn (kind 3). The start dispatcher passes no scale
// (N64: a1 = the dispatcher's own address as an f32, ~3e-26), so nothing is spawned from there.
/* was func_1500C2F0 */
void record_debris_spawn(struct_eu_15144598 *rec, f32 scale) {
    struct {
        f32 u00;            /* 0x00 = 1 */
        f32 u04;            /* 0x04 = 1 */
        f32 size[2];        /* 0x08 */
        f32 spin[3];        /* 0x10, degrees */
        f32 u1C[3];         /* 0x1C = 1 */
        f32 pos[3];         /* 0x28 */
        f32 angle;          /* 0x34 */
        f32 y2;             /* 0x38 */
        f32 u3C;            /* 0x3C */
        f32 u40;            /* 0x40 */
        f32 u44;            /* 0x44 = 0 */
        f32 u48;            /* 0x48 */
        f32 radius;         /* 0x4C */
        s32 u50;            /* 0x50 = 0x5D40 */
        s16 u54;            /* 0x54 = 300 */
        u16 sound;          /* 0x56 */
        u8 u58;             /* 0x58 = 0 */
        s32 ground;         /* 0x5C, zone_tree_find_leaf */
        u8 u60[8];          /* 0x60: FF, E, 0.. */
        u8 u68;             /* 0x68 = 2 */
        u8 pad69;
        u8 u6A;             /* 0x6A = 0 */
        s32 u6C;            /* 0x6C = 0 */
        u8 u70;             /* 0x70 = 0 */
        s16 u72;            /* 0x72 = 1 */
        s16 u74;            /* 0x74 = 0xFF */
    } blk;
    f32 n;
    f32 hi;
    f32 lo;
    f32 h;
    f32 y;
    f32 da;
    f32 db;
    f32 near;
    u32 c;
    u16 id;
    s32 i;

#define RND() (c = osGetCount(), (f32) ((c * random_int()) & 0xFFFF) * g_debris_a_rand_scale)
    n = spawn_region_volume(rec) * scale * g_debris_a_density;
    if (!(1.0f < n)) {
        return;
    }
    blk.u00 = 1.0f;
    blk.u04 = 1.0f;
    blk.u1C[0] = 1.0f;
    blk.u1C[1] = 1.0f;
    blk.u1C[2] = 1.0f;
    blk.u50 = 0x5D40;
    blk.u54 = 300;
    blk.u58 = 0;
    blk.u60[0] = 0xFF;
    blk.u60[1] = 0xE;
    for (i = 2; i < 8; i++) {
        blk.u60[i] = 0;
    }
    blk.u68 = 2;
    blk.u6A = 0;
    blk.u6C = 0;
    blk.u70 = 0;
    blk.u72 = 1;
    blk.u74 = 0xFF;
    blk.u44 = 0.0f;
    do {
        spawn_zone_pick_point(rec, &blk.pos[0], &blk.pos[2], &hi, &lo);
        h = hi - lo;
        y = RND() * (h * 0.5f) + (lo + h * 0.25f);
        blk.y2 = y;
        blk.pos[1] = y;
        da = y - hi;
        da = (da < 0.0f) ? -da : da;
        db = y - lo;
        db = (db < 0.0f) ? -db : db;
        near = (db < da) ? db : da;
        blk.radius = (RND() * 0.75f + 0.25f) * near;
        blk.angle = (RND() * 2.0f) * g_debris_a_pi;
        blk.u3C = RND() * g_debris_a_p3c_range + g_debris_a_p3c_min;
        blk.spin[0] = RND() * 360.0f;
        blk.spin[1] = RND() * 360.0f;
        blk.spin[2] = RND() * 360.0f;
        blk.u40 = RND() * g_debris_a_p40_range;
        blk.u48 = RND() * g_debris_a_p48_range;
        c = osGetCount();
        id = g_debris_a_sound_ids[(c * random_int()) % 9];
        blk.sound = id;
        if (id == 0x4B || id == 0x48 || id == 0x4E || id == 0x4F || id == 0x50 || id == 0x51) {
            blk.size[0] = RND() * 0.25f + 0.5f;
        } else {
            blk.size[0] = RND() * 0.25f + 1.0f;
        }
        blk.size[1] = blk.size[0];
        collision_select_area(0);
        blk.ground = zone_tree_find_leaf((s32) blk.pos[0], (s32) blk.pos[2]);
        mdl_particle_spawn((f32 *) &blk, 3, 0xFF, 0, 0xFF, 1);
        n -= 1.0f;
    } while (1.0f < n);
#undef RND
}
s32 spawn_zone_pick_point(struct_eu_15144598 *, f32 *, f32 *, f32 *, f32 *);
void collision_select_area(s32);
s32 particle_spawn_ex(s32 *, s32, s32, s32, s32, s32);
s32 memcpy(s32, f32 *, s32);

/* was func_1500C8D0 */
void record_particle_spawn_a(struct_eu_15144598 *arg0, f32 arg1) {
    struct {
        f32 u80;
        f32 u84;
        u8 pad88[0x4];
        f32 u8C;
        s8 u90;
        s8 u91;
        s8 u92;
        s8 u93;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        u8 padA4[0x4];
        s32 uA8;
        s32 uAC;
        s16 uB0;
        s16 uB2;
        s32 uB4;
        s32 uB8;
        s8 uBC;
        s8 uBD;
        s8 uBE;
        s8 uBF;
        s8 uC0;
        s8 uC1;
        s8 uC2;
        s8 uC3;
        s8 uC4;
        s8 uC5;
        s16 uC6;
        s16 uC8;
        s16 uCA;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        f32 uF4;
        f32 uF8;
        f32 uFC;
        s32 u100;
        s32 u104;
        s8 u108;
        s8 u109;
        s8 u10A;
        s8 u10B;
        s8 u10C;
        s8 u10D;
    } sp;
    s32 sp64;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f2;
    f32 var_f10;
    f32 var_f10_2;
    f32 var_f10_3;
    f32 var_f16;
    f32 var_f18;
    f32 var_f20;
    f32 var_f26;
    f32 var_f6;
    f32 var_f6_2;
    s32 temp_t0;
    s32 temp_t0_2;
    s32 temp_t2;
    s32 temp_t4;
    s32 temp_t6;
    s32 temp_t6_2;
    s32 temp_t8;
    s32 temp_v0;
    s32 var_s0;
    s32 var_v1;
    u32 temp_s0;
    u32 temp_s0_10;
    u32 temp_s0_2;
    u32 temp_s0_3;
    u32 temp_s0_4;
    u32 temp_s0_5;
    u32 temp_s0_6;
    u32 temp_s0_7;
    u32 temp_s0_8;
    u32 temp_s0_9;

    var_f26 = spawn_region_volume(arg0) * arg1 * 0.000002f;
    if (var_f26 > 1.0f) {
        sp.uB0 = 0x4403;
        sp.uA8 = 0x200005;
        sp.uBF = 0xFF;
        sp.uAC = 0;
        sp.uB4 = 0;
        sp.uB8 = 0;
        sp.uBC = 0;
        sp.uBD = 0;
        sp.uBE = 0;
        sp.uC0 = 0;
        sp.uC1 = 0;
        sp.uC2 = 0;
        sp.uC4 = 0xFF;
        sp.uE4 = 0.0f;
        sp.uE8 = 0.0f;
        sp.uEC = 0.0f;
        sp.uCA = 1;
        sp.uCC = 1.0f;
        sp.uB2 = 0x12C;
        sp.uC6 = 1;
        sp.uC8 = 0xFF;
        sp.u108 = 6;
        sp.u109 = 8;
        sp.u10A = 0x17;
        sp.u10B = -1;
        sp.u10C = -1;
        sp.u10D = 0;
        sp.u90 = 0;
        sp.u91 = 0;
        sp.u9C = 1.0f;
        sp.uA0 = 1.0f;
        do {
            temp_s0 = osGetCount();
            temp_t0 = (random_int() * temp_s0) & 0xFFFF;
            var_f10 = (f32) temp_t0;
            if (temp_t0 < 0) {
                var_f10 += 4294967296.0f;
            }
            temp_f20 = (var_f10 * 0.000015259022f * 350.0f) + 50.0f;
            if (random_int() & 1) {
                sp.uC5 = 0x58;
                sp.uD4 = temp_f20;
                sp.uD0 = temp_f20;
                sp.u8C = temp_f20;
            } else {
                sp.uC5 = 0x40;
                temp_f0 = temp_f20 * 0.7f;
                sp.uD4 = temp_f0;
                sp.uD0 = temp_f0;
                sp.u8C = temp_f0;
            }
            temp_s0_2 = osGetCount();
            sp.uC3 = ((u32) (random_int() * temp_s0_2) % 101U) + 0x32;
            temp_s0_3 = osGetCount();
            sp.u92 = ((random_int() * temp_s0_3) & 3) + 2;
            temp_s0_4 = osGetCount();
            sp.u93 = ((random_int() * temp_s0_4) & 3) + 2;
            temp_s0_5 = osGetCount();
            temp_t4 = (random_int() * temp_s0_5) & 0xFFFF;
            var_f18 = (f32) temp_t4;
            if (temp_t4 < 0) {
                var_f18 += 4294967296.0f;
            }
            sp.u94 = ((var_f18 * 0.000015259022f * 0.25f) + 0.2f) * sp.u8C;
            temp_s0_6 = osGetCount();
            temp_t6 = (random_int() * temp_s0_6) & 0xFFFF;
            var_f6 = (f32) temp_t6;
            if (temp_t6 < 0) {
                var_f6 += 4294967296.0f;
            }
            sp.u98 = ((var_f6 * 0.000015259022f * 0.25f) + 0.2f) * sp.u8C;
            var_v1 = 0;
            if (random_int() & 1) {
                var_v1 = 0x40;
            }
            sp64 = var_v1;
            if (random_int() & 1) {
                var_s0 = 0x80;
            } else {
                var_s0 = 0;
            }
            sp.u100 = var_s0 | var_v1 | 0xC000 | 0x10000 | 0x20000;
            spawn_zone_pick_point(arg0, &sp.uD8, &sp.uE0, &sp.u84, &sp.u80);
            temp_f20_2 = sp.u84 - sp.u80;
            temp_s0_7 = osGetCount();
            temp_t6_2 = (random_int() * temp_s0_7) & 0xFFFF;
            var_f10_2 = (f32) temp_t6_2;
            if (temp_t6_2 < 0) {
                var_f10_2 += 4294967296.0f;
            }
            temp_f2 = (var_f10_2 * 0.000015259022f * (temp_f20_2 * 0.5f)) + (sp.u80 + (temp_f20_2 * 0.25f));
            sp.uF4 = temp_f2;
            temp_f12 = fabsf(temp_f2 - sp.u84);
            sp.uDC = temp_f2;
            temp_f0_2 = fabsf(temp_f2 - sp.u80);
            if (temp_f0_2 < temp_f12) {
                var_f20 = temp_f0_2;
            } else {
                var_f20 = temp_f12;
            }
            temp_s0_8 = osGetCount();
            temp_t8 = (random_int() * temp_s0_8) & 0xFFFF;
            var_f6_2 = (f32) temp_t8;
            if (temp_t8 < 0) {
                var_f6_2 += 4294967296.0f;
            }
            sp.uFC = ((var_f6_2 * 0.000015259022f * 0.75f) + 0.25f) * var_f20;
            temp_s0_9 = osGetCount();
            temp_t0_2 = (random_int() * temp_s0_9) & 0xFFFF;
            var_f16 = (f32) temp_t0_2;
            if (temp_t0_2 < 0) {
                var_f16 += 4294967296.0f;
            }
            sp.uF0 = 2.0f * (var_f16 * 0.000015259022f) * 3.1415927f;
            temp_s0_10 = osGetCount();
            temp_t2 = (random_int() * temp_s0_10) & 0xFFFF;
            var_f10_3 = (f32) temp_t2;
            if (temp_t2 < 0) {
                var_f10_3 += 4294967296.0f;
            }
            sp.uF8 = (var_f10_3 * 0.000015259022f * 0.013f) + 0.0050000004f;
            collision_select_area(0);
            sp.u104 = zone_tree_find_leaf((s32) sp.uD8, (s32) sp.uE0);
            temp_v0 = particle_spawn_ex(&sp.uA8, 2, 0, 0x1C, 0xFF, 1);
            if (temp_v0 != 0) {
                memcpy(temp_v0 + 0xA8, &sp.u8C, 0x1C);
            }
            var_f26 -= 1.0f;
        } while (var_f26 > 1.0f);
    }
}
s32 spawn_zone_pick_point(struct_eu_15144598 *, f32 *, f32 *, f32 *, f32 *);
void collision_select_area(s32);
s32 memcpy(s32, f32 *, s32);

/* was func_1500CE4C */
void record_scatter_spawn(struct_eu_15144598 *arg0, f32 arg1) {
    struct {
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        f32 uB0;
        f32 uB4;
        s8 uB8;
        s8 uB9;
        s16 uBA;
        s16 uBC;
        u8 padBE[0x2];
        s32 uC0;
        s32 uC4;
        s8 uC8;
        s8 uC9;
        s8 uCA;
        s8 uCB;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        f32 uF4;
        s32 uF8;
        s8 uFC;
        s8 uFD;
        s8 uFE;
        s8 uFF;
        s32 u100;
    } sp;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f2;
    f32 var_f10;
    f32 var_f10_2;
    f32 var_f10_3;
    f32 var_f16;
    f32 var_f18;
    f32 var_f18_2;
    f32 var_f20;
    f32 var_f26;
    f32 var_f4;
    f32 var_f6;
    f32 var_f8;
    f32 var_f8_2;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t3;
    s32 temp_t3_2;
    s32 temp_t5;
    s32 temp_t5_2;
    s32 temp_t7;
    s32 temp_t7_2;
    s32 temp_t9;
    s32 temp_t9_2;
    u32 temp_s0;
    u32 temp_s0_10;
    u32 temp_s0_11;
    u32 temp_s0_2;
    u32 temp_s0_3;
    u32 temp_s0_4;
    u32 temp_s0_5;
    u32 temp_s0_6;
    u32 temp_s0_7;
    u32 temp_s0_8;
    u32 temp_s0_9;
    u8 *temp_v0;

    var_f26 = spawn_region_volume(arg0) * arg1 * 0.0000002f;
    if (var_f26 > 1.0f) {
        sp.uB8 = 0x57;
        sp.uB9 = 0;
        sp.uBA = 0x3B03;
        sp.uBC = 0x12C;
        sp.uC0 = 0;
        sp.uC4 = 0;
        sp.uCB = 0xFF;
        sp.uEC = 0.0f;
        sp.uF0 = 0.0f;
        sp.uF4 = 0.0f;
        sp.uF8 = 0x037C0000;
        sp.uFD = 0xFF;
        sp.uFE = 0;
        sp.uFF = 6;
        sp.uB0 = 0.0f;
        sp.uC8 = 0xFF;
        sp.uC9 = 0xFF;
        sp.uCA = 0xFF;
        do {
            temp_s0 = osGetCount();
            temp_t7 = (random_int() * temp_s0) & 0xFFFF;
            var_f10 = (f32) temp_t7;
            if (temp_t7 < 0) {
                var_f10 += 4294967296.0f;
            }
            temp_f0 = (var_f10 * 0.000015259022f * 12.0f) + 10.0f;
            sp.uCC = temp_f0;
            sp.uD0 = temp_f0;
            spawn_zone_pick_point(arg0, &sp.uD4, &sp.uDC, &sp.u98, &sp.u94);
            temp_f20 = sp.u98 - sp.u94;
            temp_s0_2 = osGetCount();
            temp_t9 = (random_int() * temp_s0_2) & 0xFFFF;
            var_f18 = (f32) temp_t9;
            if (temp_t9 < 0) {
                var_f18 += 4294967296.0f;
            }
            temp_f2 = (var_f18 * 0.000015259022f * (temp_f20 * 0.5f)) + (sp.u94 + (temp_f20 * 0.25f));
            sp.u9C = temp_f2;
            temp_f12 = fabsf(temp_f2 - sp.u98);
            sp.uD8 = temp_f2;
            temp_f0_2 = fabsf(temp_f2 - sp.u94);
            if (temp_f0_2 < temp_f12) {
                var_f20 = temp_f0_2;
            } else {
                var_f20 = temp_f12;
            }
            temp_s0_3 = osGetCount();
            temp_t1 = (random_int() * temp_s0_3) & 0xFFFF;
            var_f16 = (f32) temp_t1;
            if (temp_t1 < 0) {
                var_f16 += 4294967296.0f;
            }
            sp.uA0 = ((var_f16 * 0.000015259022f * 0.75f) + 0.25f) * var_f20;
            temp_s0_4 = osGetCount();
            temp_t3 = (random_int() * temp_s0_4) & 0xFFFF;
            var_f10_2 = (f32) temp_t3;
            if (temp_t3 < 0) {
                var_f10_2 += 4294967296.0f;
            }
            sp.uA4 = 2.0f * (var_f10_2 * 0.000015259022f) * 3.1415927f;
            temp_s0_5 = osGetCount();
            temp_t5 = (random_int() * temp_s0_5) & 0xFFFF;
            var_f18_2 = (f32) temp_t5;
            if (temp_t5 < 0) {
                var_f18_2 += 4294967296.0f;
            }
            sp.uA8 = (var_f18_2 * 0.000015259022f * 0.013f) + 0.0050000004f;
            temp_s0_6 = osGetCount();
            temp_t7_2 = (random_int() * temp_s0_6) & 0xFFFF;
            var_f8 = (f32) temp_t7_2;
            if (temp_t7_2 < 0) {
                var_f8 += 4294967296.0f;
            }
            sp.uAC = var_f8 * 0.000015259022f;
            temp_s0_7 = osGetCount();
            temp_t9_2 = (random_int() * temp_s0_7) & 0xFFFF;
            var_f10_3 = (f32) temp_t9_2;
            if (temp_t9_2 < 0) {
                var_f10_3 += 4294967296.0f;
            }
            sp.uB4 = var_f10_3 * 0.000015259022f;
            temp_s0_8 = osGetCount();
            temp_t1_2 = (random_int() * temp_s0_8) & 0xFFFF;
            var_f4 = (f32) temp_t1_2;
            if (temp_t1_2 < 0) {
                var_f4 += 4294967296.0f;
            }
            sp.uE0 = var_f4 * 0.000015259022f * 360.0f;
            temp_s0_9 = osGetCount();
            temp_t3_2 = (random_int() * temp_s0_9) & 0xFFFF;
            var_f8_2 = (f32) temp_t3_2;
            if (temp_t3_2 < 0) {
                var_f8_2 += 4294967296.0f;
            }
            sp.uE4 = var_f8_2 * 0.000015259022f * 360.0f;
            temp_s0_10 = osGetCount();
            temp_t5_2 = (random_int() * temp_s0_10) & 0xFFFF;
            var_f6 = (f32) temp_t5_2;
            if (temp_t5_2 < 0) {
                var_f6 += 4294967296.0f;
            }
            sp.uE8 = var_f6 * 0.000015259022f * 360.0f;
            temp_s0_11 = osGetCount();
            sp.uFC = ((u32) (random_int() * temp_s0_11) % 156U) + 0x64;
            collision_select_area(0);
            sp.u100 = zone_tree_find_leaf((s32) sp.uD4, (s32) sp.uDC);
            temp_v0 = effect3d_spawn_full(&sp.uB8, (s32) ((u8 *)&D_800A4AA0), 0x23U, 0U, 0U, 0x1EU, 0U, 3, 0xFF, 0x1C, 0xFFU, 1);
            if (temp_v0 != NULL) {
                memcpy(temp_v0 + 0x110, &sp.u9C, 0x1C);
            }
            var_f26 -= 1.0f;
        } while (var_f26 > 1.0f);
    }
}
s32 spawn_zone_pick_point(struct_eu_15144598 *, f32 *, f32 *, f32 *, f32 *);
void collision_select_area(s32);
s32 mdl_particle_spawn(f32 *, s32, s32, s32, s32, s32);

/* was func_1500D3AC */
void record_debris_spawn_c(struct_eu_15144598 *arg0, f32 arg1) {
    struct {
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        f32 uDC;
        f32 uE0;
        s32 uE4;
        s16 uE8;
        s16 uEA;
        s8 uEC;
        u8 padED[0x3];
        s32 uF0;
        s8 uF4;
        s8 uF5;
        s8 uF6;
        s8 uF7;
        s8 uF8;
        s8 uF9;
        s8 uFA;
        s8 uFB;
        s8 uFC;
        u8 padFD[0x1];
        s8 uFE;
        u8 padFF[0x1];
        s32 u100;
        s8 u104;
        u8 pad105[0x1];
        s16 u106;
        s16 u108;
    } sp;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f2;
    f32 var_f10;
    f32 var_f10_2;
    f32 var_f10_3;
    f32 var_f16;
    f32 var_f16_2;
    f32 var_f18;
    f32 var_f18_2;
    f32 var_f18_3;
    f32 var_f20;
    f32 var_f30;
    f32 var_f6;
    f32 var_f8;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t3;
    s32 temp_t3_2;
    s32 temp_t5;
    s32 temp_t5_2;
    s32 temp_t7;
    s32 temp_t7_2;
    s32 temp_t9;
    s32 temp_t9_2;
    u32 temp_s0;
    u32 temp_s0_10;
    u32 temp_s0_2;
    u32 temp_s0_3;
    u32 temp_s0_4;
    u32 temp_s0_5;
    u32 temp_s0_6;
    u32 temp_s0_7;
    u32 temp_s0_8;
    u32 temp_s0_9;

    var_f30 = spawn_region_volume(arg0) * arg1 * 0.0000002f;
    if (var_f30 > 1.0f) {
        sp.u94 = 1.0f;
        sp.u98 = 1.0f;
        sp.uB0 = 1.0f;
        sp.uB4 = 1.0f;
        sp.uB8 = 1.0f;
        sp.uE4 = 0x4D40;
        sp.uE8 = 0x12C;
        sp.uEC = 0;
        sp.uF4 = 0xFF;
        sp.uF5 = 0xE;
        sp.uF6 = 0;
        sp.uF7 = 0;
        sp.uF8 = 0;
        sp.uF9 = 0;
        sp.uFA = 0;
        sp.uFB = 0;
        sp.uFC = 2;
        sp.uFE = 0;
        sp.u100 = 0;
        sp.u104 = 0;
        sp.u106 = 1;
        sp.u108 = 0xFF;
        sp.uEA = 0x53;
        sp.uD8 = 0.0f;
        do {
            spawn_zone_pick_point(arg0, &sp.uBC, &sp.uC4, &sp.u90, &sp.u8C);
            temp_f20 = sp.u90 - sp.u8C;
            temp_s0 = osGetCount();
            temp_t5 = (random_int() * temp_s0) & 0xFFFF;
            var_f18 = (f32) temp_t5;
            if (temp_t5 < 0) {
                var_f18 += 4294967296.0f;
            }
            temp_f2 = (var_f18 * 0.000015259022f * (temp_f20 * 0.5f)) + (sp.u8C + (temp_f20 * 0.25f));
            sp.uCC = temp_f2;
            temp_f12 = fabsf(temp_f2 - sp.u90);
            sp.uC0 = temp_f2;
            temp_f0 = fabsf(temp_f2 - sp.u8C);
            if (temp_f0 < temp_f12) {
                var_f20 = temp_f0;
            } else {
                var_f20 = temp_f12;
            }
            temp_s0_2 = osGetCount();
            temp_t7 = (random_int() * temp_s0_2) & 0xFFFF;
            var_f10 = (f32) temp_t7;
            if (temp_t7 < 0) {
                var_f10 += 4294967296.0f;
            }
            sp.uE0 = ((var_f10 * 0.000015259022f * 0.75f) + 0.25f) * var_f20;
            temp_s0_3 = osGetCount();
            temp_t9 = (random_int() * temp_s0_3) & 0xFFFF;
            var_f16 = (f32) temp_t9;
            if (temp_t9 < 0) {
                var_f16 += 4294967296.0f;
            }
            sp.uC8 = 2.0f * (var_f16 * 0.000015259022f) * 3.1415927f;
            temp_s0_4 = osGetCount();
            temp_t1 = (random_int() * temp_s0_4) & 0xFFFF;
            var_f18_2 = (f32) temp_t1;
            if (temp_t1 < 0) {
                var_f18_2 += 4294967296.0f;
            }
            sp.uD0 = (var_f18_2 * 0.000015259022f * 0.013f) + 0.0050000004f;
            temp_s0_5 = osGetCount();
            temp_t3 = (random_int() * temp_s0_5) & 0xFFFF;
            var_f8 = (f32) temp_t3;
            if (temp_t3 < 0) {
                var_f8 += 4294967296.0f;
            }
            sp.uA4 = var_f8 * 0.000015259022f * 360.0f;
            temp_s0_6 = osGetCount();
            temp_t5_2 = (random_int() * temp_s0_6) & 0xFFFF;
            var_f18_3 = (f32) temp_t5_2;
            if (temp_t5_2 < 0) {
                var_f18_3 += 4294967296.0f;
            }
            sp.uA8 = var_f18_3 * 0.000015259022f * 360.0f;
            temp_s0_7 = osGetCount();
            temp_t7_2 = (random_int() * temp_s0_7) & 0xFFFF;
            var_f16_2 = (f32) temp_t7_2;
            if (temp_t7_2 < 0) {
                var_f16_2 += 4294967296.0f;
            }
            sp.uAC = var_f16_2 * 0.000015259022f * 360.0f;
            temp_s0_8 = osGetCount();
            temp_t9_2 = (random_int() * temp_s0_8) & 0xFFFF;
            var_f10_2 = (f32) temp_t9_2;
            if (temp_t9_2 < 0) {
                var_f10_2 += 4294967296.0f;
            }
            sp.uD4 = var_f10_2 * 0.000015259022f * 1.6f;
            temp_s0_9 = osGetCount();
            temp_t1_2 = (random_int() * temp_s0_9) & 0xFFFF;
            var_f6 = (f32) temp_t1_2;
            if (temp_t1_2 < 0) {
                var_f6 += 4294967296.0f;
            }
            sp.uDC = var_f6 * 0.000015259022f * 1.6f;
            temp_s0_10 = osGetCount();
            temp_t3_2 = (random_int() * temp_s0_10) & 0xFFFF;
            var_f10_3 = (f32) temp_t3_2;
            if (temp_t3_2 < 0) {
                var_f10_3 += 4294967296.0f;
            }
            temp_f0_2 = (var_f10_3 * 0.000015259022f * 0.25f) + 1.0f;
            sp.u9C = temp_f0_2;
            sp.uA0 = temp_f0_2;
            collision_select_area(0);
            sp.uF0 = zone_tree_find_leaf((s32) sp.uBC, (s32) sp.uC4);
            mdl_particle_spawn(&sp.u94, 3, 0xFF, 0, 0xFF, 1);
            var_f30 -= 1.0f;
        } while (var_f30 > 1.0f);
    }
}
// void record_debris_spawn_c(s32 arg0, f32 arg1) {
//
//     f32 temp_f0;
//     struct171 tmp;
//     f32 temp_f12;
//     f32 phi_f18;
//     f32 phi_f30; // main tmp
//
//
//     phi_f30 = spawn_region_volume(arg0) * arg1 * D_8009616C;
//
//     if (phi_f30 > 1.0f) {
//         tmp.unk8 = 1.0f;
//         tmp.unkC = 1.0f;
//         tmp.unk24 = 1.0f;
//         tmp.unk28 = 1.0f;
//         tmp.unk2C = 1.0f;
//         tmp.unk58 = 19776;
//         tmp.unk5C = 300;
//         tmp.unk60 = 0;
//         tmp.unk68 = 255;
//         tmp.unk69 = 14;
//         tmp.unk6A = 0;
//         tmp.unk6B = 0;
//         tmp.unk6C = 0;
//         tmp.unk6D = 0;
//         tmp.unk6E = 0;
//         tmp.unk6F = 0;
//         tmp.unk70 = 2;
//         tmp.unk72 = 0;
//         tmp.unk74 = 0;
//         tmp.unk78 = 0;
//         tmp.unk7A = 1;
//         tmp.unk7C = 0xFF;
//         tmp.unk5E = 0x53;
//         tmp.unk4C = 0.0f;
//
//         do {
//             spawn_zone_pick_point(arg0, &tmp.unk30, &tmp.unk38, &tmp.unk4, &tmp.unk0);
//             phi_f18 = (u16) (osGetCount() * random_int());
//             tmp.unk34 = tmp.unk40 = (phi_f18 * D_80096170 * ((tmp.unk4 - tmp.unk0) * 0.5f)) + (tmp.unk0 + ((tmp.unk4 - tmp.unk0) * 0.25f));
//
//             temp_f12 = fabsf(tmp.unk40 - tmp.unk4);
//             temp_f0 = fabsf(tmp.unk40 - tmp.unk0);
//
//             if (temp_f0 < temp_f12) {
//                 temp_f0 = temp_f0;
//             } else {
//                 temp_f0 = temp_f12;
//             }
//             phi_f18 = (u16) (osGetCount() * random_int());
//             tmp.unk54 = ((phi_f18 * D_80096170 * 0.75f) + 0.25f) * temp_f0;
//
//             phi_f18 = (u16) (osGetCount() * random_int());
//             tmp.unk3C = ((phi_f18 * D_80096170) + (phi_f18 * D_80096170)) * D_80096174;
//
//             phi_f18 = (u16)(osGetCount() * random_int());
//             tmp.unk44 = (phi_f18 * D_80096170 * D_80096178) + D_8009617C;
//
//             phi_f18 = (u16) (osGetCount() * random_int());
//             tmp.unk18 = phi_f18 * D_80096170 * 360.0f;
//
//             phi_f18 = (u16) (osGetCount() * random_int());
//             tmp.unk1C = phi_f18 * D_80096170 * 360.0f;
//
//             phi_f18 = (u16) (osGetCount() * random_int());
//             tmp.unk20 = phi_f18 * D_80096170 * 360.0f;
//
//             phi_f18 = (u16) (osGetCount() * random_int());
//             tmp.unk48 = phi_f18 * D_80096170 * D_80096180;
//
//             phi_f18 = (u16) (osGetCount() * random_int());
//             tmp.unk50 = phi_f18 * D_80096170 * D_80096184;
//
//             phi_f18 = (u16) (osGetCount() * random_int());
//             tmp.unk10 = tmp.unk14 = (phi_f18 * D_80096170 * 0.25f) + 1.0f;
//
//             collision_select_area(0);
//             tmp.unk64 = zone_tree_find_leaf(tmp.unk30, tmp.unk38);
//             func_15132A4C(&tmp, 3, 0xFF, 0, 0xFF, 1);
//
//         } while ((phi_f30 -= 1.0f) > 1.0f);
//     }
// }

s32 spawn_zone_pick_point(struct_eu_15144598 *, f32 *, f32 *, f32 *, f32 *);
void collision_select_area(s32);
s32 zone_tree_find_leaf(s32, s32);
s32 mdl_particle_spawn(f32 *, s32, s32, s32, s32, s32);
extern u16 g_debris_b_sound_ids[14]; /* sound ids; 0x39 gets g_debris_b_size_scale-scaled pieces; was D_800964B4; was D_80096554 */
extern f32 g_debris_b_density;    /* pieces per unit of record length x scale; was D_80096538 */
extern f32 g_debris_b_rand_scale;    /* 1 / 65535; was D_8009653C */
extern f32 D_eu_80096540; /* pi */
extern f32 g_debris_b_p3c_range; /* was D_80096544 */
extern f32 g_debris_b_p3c_min; /* was D_80096548 */
extern f32 g_debris_b_p40_range; /* was D_8009654C */
extern f32 g_debris_b_p48_range; /* was D_80096550 */
extern f32 g_debris_b_size_scale; /* was D_80096554 */

// record_debris_spawn_b: g_record_start_handlers entry 0x26 (level-start record). As record_debris_spawn (record_debris_spawn) with
// n = length x scale x g_debris_b_density, other constants, the 14 g_debris_b_sound_ids sounds and sizes 0.5..0.75 (x g_debris_b_size_scale
// for sound 0x39). Spawns nothing from the start dispatcher (no scale passed).
/* was func_1500D8C8 */
void record_debris_spawn_b(struct_eu_15144598 *rec, f32 scale) {
    struct {
        f32 u00;            /* 0x00 = 1 */
        f32 u04;            /* 0x04 = 1 */
        f32 size[2];        /* 0x08 */
        f32 spin[3];        /* 0x10, degrees */
        f32 u1C[3];         /* 0x1C = 1 */
        f32 pos[3];         /* 0x28 */
        f32 angle;          /* 0x34 */
        f32 y2;             /* 0x38 */
        f32 u3C;            /* 0x3C */
        f32 u40;            /* 0x40 */
        f32 u44;            /* 0x44 = 0 */
        f32 u48;            /* 0x48 */
        f32 radius;         /* 0x4C */
        s32 u50;            /* 0x50 = 0x5D40 */
        s16 u54;            /* 0x54 = 300 */
        u16 sound;          /* 0x56 */
        u8 u58;             /* 0x58 = 0 */
        s32 ground;         /* 0x5C, zone_tree_find_leaf */
        u8 u60[8];          /* 0x60: FF, E, 0.. */
        u8 u68;             /* 0x68 = 2 */
        u8 pad69;
        u8 u6A;             /* 0x6A = 0 */
        s32 u6C;            /* 0x6C = 0 */
        u8 u70;             /* 0x70 = 0 */
        s16 u72;            /* 0x72 = 1 */
        s16 u74;            /* 0x74 = 0xFF */
    } blk;
    f32 n;
    f32 hi;
    f32 lo;
    f32 h;
    f32 y;
    f32 da;
    f32 db;
    f32 near;
    u32 c;
    u16 id;
    s32 i;

#define RND() (c = osGetCount(), (f32) ((c * random_int()) & 0xFFFF) * g_debris_b_rand_scale)
    n = spawn_region_volume(rec) * scale * g_debris_b_density;
    if (!(1.0f < n)) {
        return;
    }
    blk.u00 = 1.0f;
    blk.u04 = 1.0f;
    blk.u1C[0] = 1.0f;
    blk.u1C[1] = 1.0f;
    blk.u1C[2] = 1.0f;
    blk.u50 = 0x4D40;
    blk.u54 = 300;
    blk.u58 = 0;
    blk.u60[0] = 0xFF;
    blk.u60[1] = 0xE;
    for (i = 2; i < 8; i++) {
        blk.u60[i] = 0;
    }
    blk.u68 = 2;
    blk.u6A = 0;
    blk.u6C = 0;
    blk.u70 = 0;
    blk.u72 = 1;
    blk.u74 = 0xFF;
    blk.u44 = 0.0f;
    do {
        spawn_zone_pick_point(rec, &blk.pos[0], &blk.pos[2], &hi, &lo);
        h = hi - lo;
        y = RND() * (h * 0.5f) + (lo + h * 0.25f);
        blk.y2 = y;
        blk.pos[1] = y;
        da = y - hi;
        da = (da < 0.0f) ? -da : da;
        db = y - lo;
        db = (db < 0.0f) ? -db : db;
        near = (db < da) ? db : da;
        blk.radius = (RND() * 0.75f + 0.25f) * near;
        blk.angle = (RND() * 2.0f) * D_eu_80096540;
        blk.u3C = RND() * g_debris_b_p3c_range + g_debris_b_p3c_min;
        blk.spin[0] = RND() * 360.0f;
        blk.spin[1] = RND() * 360.0f;
        blk.spin[2] = RND() * 360.0f;
        blk.u40 = RND() * g_debris_b_p40_range;
        blk.u48 = RND() * g_debris_b_p48_range;
        c = osGetCount();
        id = g_debris_b_sound_ids[(c * random_int()) % 14];
        blk.sound = id;
        blk.size[0] = blk.size[1] = RND() * 0.25f + 0.5f;
        if (id == 0x39) {
            blk.size[0] = blk.size[0] * g_debris_b_size_scale;
            blk.size[1] = blk.size[1] * g_debris_b_size_scale;
        }
        collision_select_area(0);
        blk.ground = zone_tree_find_leaf((s32) blk.pos[0], (s32) blk.pos[2]);
        mdl_particle_spawn((f32 *) &blk, 3, 0xFF, 0, 0xFF, 1);
        n -= 1.0f;
    } while (1.0f < n);
#undef RND
}

s32 spawn_zone_pick_point(struct_eu_15144598 *, f32 *, f32 *, f32 *, f32 *);
void collision_select_area(s32);
s32 particle_spawn_ex(s32 *, s32, s32, s32, s32, s32);
s32 memcpy(s32, f32 *, s32);

/* was func_1500DE88 */
void record_particle_spawn_b(struct_eu_15144598 *arg0, f32 arg1) {
    struct {
        f32 u78;
        f32 u7C;
        u8 pad80[0x4];
        f32 u84;
        s8 u88;
        s8 u89;
        s8 u8A;
        s8 u8B;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        u8 pad9C[0x4];
        s32 uA0;
        s32 uA4;
        s16 uA8;
        s16 uAA;
        s32 uAC;
        s32 uB0;
        s8 uB4;
        s8 uB5;
        s8 uB6;
        s8 uB7;
        s8 uB8;
        s8 uB9;
        s8 uBA;
        s8 uBB;
        s8 uBC;
        s8 uBD;
        s16 uBE;
        s16 uC0;
        s16 uC2;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        f32 uF4;
        s32 uF8;
        s32 uFC;
        s8 u100;
        s8 u101;
        s8 u102;
        s8 u103;
        s8 u104;
        s8 u105;
    } sp;
    s32 sp60;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f2;
    f32 var_f10;
    f32 var_f10_2;
    f32 var_f10_3;
    f32 var_f16;
    f32 var_f18;
    f32 var_f20;
    f32 var_f24;
    f32 var_f4;
    f32 var_f6;
    s32 temp_t0;
    s32 temp_t0_2;
    s32 temp_t1;
    s32 temp_t2;
    s32 temp_t2_2;
    s32 temp_t4;
    s32 temp_t8;
    s32 temp_v0;
    s32 var_s0;
    s32 var_v1;
    u32 temp_s0;
    u32 temp_s0_10;
    u32 temp_s0_11;
    u32 temp_s0_12;
    u32 temp_s0_2;
    u32 temp_s0_3;
    u32 temp_s0_4;
    u32 temp_s0_5;
    u32 temp_s0_6;
    u32 temp_s0_7;
    u32 temp_s0_8;
    u32 temp_s0_9;

    var_f24 = spawn_region_volume(arg0) * arg1 * 0.000002f;
    if (var_f24 > 1.0f) {
        sp.uA8 = 0x5103;
        sp.uA0 = 0x200005;
        sp.uB7 = 0xFF;
        sp.uBC = 0xFF;
        sp.uA4 = 0;
        sp.uAC = 0;
        sp.uB0 = 0;
        sp.uB5 = 0;
        sp.uB6 = 0;
        sp.uB9 = 0;
        sp.uBA = 0;
        sp.uDC = 0.0f;
        sp.uE0 = 0.0f;
        sp.uE4 = 0.0f;
        sp.uC2 = 1;
        sp.uC4 = 1.0f;
        sp.uAA = 0x12C;
        sp.uBE = 1;
        sp.uC0 = 0xFF;
        sp.u100 = 8;
        sp.u101 = 6;
        sp.u102 = 0x17;
        sp.u103 = -1;
        sp.u104 = -1;
        sp.u105 = 0;
        sp.u88 = 0;
        sp.u89 = 0;
        sp.u94 = 1.0f;
        sp.u98 = 1.0f;
        sp.uBD = 0x6C;
        do {
            temp_s0 = osGetCount();
            temp_t1 = (random_int() * temp_s0) & 0xFFFF;
            var_f10 = (f32) temp_t1;
            if (temp_t1 < 0) {
                var_f10 += 4294967296.0f;
            }
            temp_f0 = (var_f10 * 0.000015259022f * 600.0f) + 200.0f;
            sp.uCC = temp_f0;
            sp.uC8 = temp_f0;
            sp.u84 = temp_f0;
            temp_s0_2 = osGetCount();
            sp.uBB = ((u32) (random_int() * temp_s0_2) % 71U) + 0x32;
            temp_s0_3 = osGetCount();
            sp.u8A = (s8) ((u32) (random_int() * temp_s0_3) % 3U);
            temp_s0_4 = osGetCount();
            sp.u8B = (s8) ((u32) (random_int() * temp_s0_4) % 3U);
            temp_s0_5 = osGetCount();
            temp_t0 = (random_int() * temp_s0_5) & 0xFFFF;
            var_f10_2 = (f32) temp_t0;
            if (temp_t0 < 0) {
                var_f10_2 += 4294967296.0f;
            }
            sp.u8C = ((var_f10_2 * 0.000015259022f * 0.15f) + 0.3f) * sp.u84;
            temp_s0_6 = osGetCount();
            temp_t2 = (random_int() * temp_s0_6) & 0xFFFF;
            var_f4 = (f32) temp_t2;
            if (temp_t2 < 0) {
                var_f4 += 4294967296.0f;
            }
            sp.u90 = ((var_f4 * 0.000015259022f * 0.15f) + 0.3f) * sp.u84;
            var_v1 = 0;
            if (random_int() & 1) {
                var_v1 = 0x40;
            }
            sp60 = var_v1;
            if (random_int() & 1) {
                var_s0 = 0x80;
            } else {
                var_s0 = 0;
            }
            sp.uF8 = var_s0 | var_v1 | 0xC000 | 0x20000 | 0x800000;
            temp_s0_7 = osGetCount();
            sp.uB8 = ((u32) (random_int() * temp_s0_7) % 56U) + 0x50;
            temp_s0_8 = osGetCount();
            sp.uB4 = ((u32) (random_int() * temp_s0_8) % 46U) + 0xB4;
            spawn_zone_pick_point(arg0, &sp.uD0, &sp.uD8, &sp.u7C, &sp.u78);
            temp_f20 = sp.u7C - sp.u78;
            temp_s0_9 = osGetCount();
            temp_t8 = (random_int() * temp_s0_9) & 0xFFFF;
            var_f16 = (f32) temp_t8;
            if (temp_t8 < 0) {
                var_f16 += 4294967296.0f;
            }
            temp_f2 = (var_f16 * 0.000015259022f * (temp_f20 * 0.5f)) + (sp.u78 + (temp_f20 * 0.25f));
            sp.uEC = temp_f2;
            temp_f12 = fabsf(temp_f2 - sp.u7C);
            sp.uD4 = temp_f2;
            temp_f0_2 = fabsf(temp_f2 - sp.u78);
            if (temp_f0_2 < temp_f12) {
                var_f20 = temp_f0_2;
            } else {
                var_f20 = temp_f12;
            }
            temp_s0_10 = osGetCount();
            temp_t0_2 = (random_int() * temp_s0_10) & 0xFFFF;
            var_f18 = (f32) temp_t0_2;
            if (temp_t0_2 < 0) {
                var_f18 += 4294967296.0f;
            }
            sp.uF4 = ((var_f18 * 0.000015259022f * 0.75f) + 0.25f) * var_f20;
            temp_s0_11 = osGetCount();
            temp_t2_2 = (random_int() * temp_s0_11) & 0xFFFF;
            var_f6 = (f32) temp_t2_2;
            if (temp_t2_2 < 0) {
                var_f6 += 4294967296.0f;
            }
            sp.uE8 = 2.0f * (var_f6 * 0.000015259022f) * 3.1415927f;
            temp_s0_12 = osGetCount();
            temp_t4 = (random_int() * temp_s0_12) & 0xFFFF;
            var_f10_3 = (f32) temp_t4;
            if (temp_t4 < 0) {
                var_f10_3 += 4294967296.0f;
            }
            sp.uF0 = (var_f10_3 * 0.000015259022f * 0.010000001f) + 0.002f;
            collision_select_area(0);
            sp.uFC = zone_tree_find_leaf((s32) sp.uD0, (s32) sp.uD8);
            temp_v0 = particle_spawn_ex(&sp.uA0, 2, 0, 0x1C, 0xFF, 1);
            if (temp_v0 != 0) {
                memcpy(temp_v0 + 0xA8, &sp.u84, 0x1C);
            }
            var_f24 -= 1.0f;
        } while (var_f24 > 1.0f);
    }
}
// NON-MATCHING: not a bad start..
// void record_particle_spawn_b(s32 arg0, f32 arg1) {
//
//     f32 temp_f0;    // tmp
//     f32 phi_f10;    // tmp
//     f32 temp_f12;   // another tmp
//     f32 temp_f22;   // D_800961B4
//     f32 temp_f28;   // D_800961B0
//     f32 temp_f30;   // D_800961AC
//     struct21 *temp_v0;    // dummy struct
//     s32 phi_v1;
//     struct170 tmp;
//
//
//     f32 phi_f24 = spawn_region_volume(arg0) * arg1 * D_800961A8;
//
//     if (phi_f24 > 1.0f) {
//         tmp.unk48 = 20739;
//         tmp.unk40 = 0x200005;
//         tmp.unk57 = 0xFF;
//         tmp.unk5C = 0xFF;
//         tmp.unk44 = 0.0f;
//         tmp.unk4C = 0.0f;
//         tmp.unk50 = 0.0f;
//         tmp.unk55 = 0;
//         tmp.unk56 = 0;
//         tmp.unk59 = 0;
//         tmp.unk5A = 0;
//         tmp.unk7C = 0.0f;
//         tmp.unk80 = 0.0f;
//         tmp.unk84 = 0.0f;
//         tmp.unk62 = 1;
//         tmp.unk64 = 1.0f;
//         tmp.unk4A = 300;
//         tmp.unk5E = 1;
//         tmp.unk60 = 0xFF;
//         tmp.unkA0 = 8;
//         tmp.unkA1 = 6;
//         tmp.unkA2 = 23;
//         tmp.unkA3 = -1;
//         tmp.unkA4 = -1;
//         tmp.unkA5 = 0;
//         tmp.unk28 = 0;
//         tmp.unk29 = 0;
//         tmp.unk34 = 1.0f;
//         tmp.unk38 = 1.0f;
//         tmp.unk5D = 108;
//
//         temp_f30 = D_800961AC;
//         temp_f28 = D_800961B0;
//         temp_f22 = D_800961B4;
//
//         do {
//             phi_f10 = (u16) (osGetCount() * random_int()) ;
//
//             tmp.unk68 = tmp.unk6C = tmp.unk24 = (phi_f10 * temp_f22 * 600.0f) + 200.0f;
//
//             tmp.unk5B = (osGetCount() * random_int()) % 0x47U + 0x32;
//             tmp.unk2A = (osGetCount() * random_int()) % 3U;
//             tmp.unk2B = (osGetCount() * random_int()) % 3U;
//
//             phi_f10 = (u16) (osGetCount() * random_int());
//             tmp.unk2C = ((phi_f10 * temp_f22 * temp_f28) + temp_f30) * tmp.unk24;
//
//             phi_f10 = (u16) (osGetCount() * random_int());
//             tmp.unk30 = ((phi_f10 * temp_f22 * temp_f28) + temp_f30) * tmp.unk24;
//
//             if ((random_int() & 1) != 0) {
//                 tmp.unk0 = 0x40;
//             } else {
//                 tmp.unk0 = 0;
//             }
//
//             if ((random_int() & 1) != 0) {
//                 phi_v1 = 0x80;
//             } else {
//                 phi_v1 = 0;
//             }
//             tmp.unk98 = phi_v1 | tmp.unk0 | 0xC000 | 0x20000 | 0x800000;
//             tmp.unk58 = ((osGetCount() * random_int()) % 0x38U) + 0x50;
//             tmp.unk54 = ((osGetCount() * random_int()) % 0x2EU) + 0xB4;
//             spawn_zone_pick_point(arg0, &tmp.unk70, &tmp.unk78, &tmp.unk1C, &tmp.unk18);
//
//             phi_f10 = (u16) (osGetCount() * random_int());
//
//             temp_f0 = tmp.unk1C - tmp.unk18;
//             tmp.unk8C = (phi_f10 * temp_f22 * (temp_f0 * 0.5f)) + (tmp.unk18 + (temp_f0 * 0.25f));
//             tmp.unk74 = fabsf(tmp.unk8C - tmp.unk1C);
//             temp_f0 = fabsf(tmp.unk74 - tmp.unk18);
//             if (tmp.unk74 < temp_f0) {
//                 temp_f0 = tmp.unk74;
//             }
//
//             phi_f10 = (u16) (osGetCount() * random_int());
//             tmp.unk94 = ((phi_f10 * temp_f22 * 0.75f) + 0.25f) * temp_f0;
//
//             phi_f10 = (u16) (osGetCount() * random_int());
//             temp_f0 = phi_f10 * temp_f22;
//             tmp.unk88 = (temp_f0 + temp_f0) * D_800961B8;
//
//             phi_f10 = (u16) (osGetCount() * random_int());
//             tmp.unk90 = (phi_f10 * temp_f22 * D_800961BC) + D_800961C0;
//             collision_select_area(0);
//             tmp.unk9C = zone_tree_find_leaf(tmp.unk70, tmp.unk78);
//             temp_v0 = func_15130280(&tmp.unk40, 2, 0, 28, 255, 1);
//             if (temp_v0 != NULL) {
//                 memcpy(&temp_v0->unkA8, &tmp.unk24, 28); // memcpy  temp_v0->A8 ?
//             }
//             phi_f24 -= 1.0f;
//         }
//         while (phi_f24 > 1.0f);
//     }
// }
