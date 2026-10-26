#include <ultra64.h>
#include "functions.h"
#include "variables.h"


int game_gu_random(void);

/* was func_1500F240 */
s32 mist_puff_spawn(f32 arg0, f32 arg1, f32 arg2) {
    struct {
        s32 u48;
        s16 u4C;
        s8 u4E;
        u8 pad4F[0x1];
        s32 u50;
        s32 u54;
        s8 u58;
        s8 u59;
        s8 u5A;
        s8 u5B;
        s8 u5C;
        s8 u5D;
        u8 pad5E[0x2];
        s32 u60;
    } sp;

    sp.u4E = 0x38;
    sp.u50 = 0;
    sp.u54 = (game_gu_random() % 4096) + 0x4000;
    sp.u48 = 0x20014;
    sp.u4C = 1;
    sp.u58 = 0xFF;
    sp.u59 = 0xFF;
    sp.u5A = 0;
    sp.u5B = 0;
    sp.u5C = 0;
    sp.u5D = 0xFF;
    sp.u60 = 0x30001;
    return sprite_fx_spawn_quad((s32) &sp.u48, 0, 0U, 0U, arg0, arg1, arg2, 110.0f, 110.0f, 0U, 0U, 0, 0xFFU, 0);
}
/* was func_1500F328 */
void level_fx_spawn_box_a(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct260 *temp_v0;

    temp_v0 = effect_node_create_nodraw((s16) ((random_int() & 0x7F) + 0xA), 1, -1, 1U, 0U, 0xA, 0xFFU, 0);
    if (temp_v0 != NULL) {
        (*(s16 *)((u8 *)temp_v0 + 0x28)) = (s16) arg0;
        (*(s16 *)((u8 *)temp_v0 + 0x2A)) = (s16) arg1;
        (*(s16 *)((u8 *)temp_v0 + 0x2C)) = (s16) arg2;
        (*(s16 *)((u8 *)temp_v0 + 0x2E)) = (s16) arg3;
        (*(s8 *)((u8 *)temp_v0 + 0x30)) = 1;
    }
}

extern s32 g_mist_puff_handles[]; /* was D_800D9CF0 */
void area_drift_emitter_create(void *arg0, u8 arg1);

/* emitter spec copied by area_drift_emitter_create (0x50 bytes) */
typedef struct {
    /* 0x00 */ s16 angle;       /* heading byte angle - 0x40 */
    /* 0x02 */ s16 h02, h04, h06;
    /* 0x08 */ f32 pos[3];
    /* 0x14 */ f32 dir[3];      /* end - start */
    /* 0x20 */ f32 f20, f24, f28, f2C, f30, f34;
    /* 0x38 */ s16 h38, h3A;
    /* 0x3C */ f32 f3C, f40;
    /* 0x44 */ s16 h44, h46;
    /* 0x48 */ s32 w48, w4C;
} DriftSpecF3BC;

/* rodata copies (NM link drops the asm rodata) */
static const f32 D_8009661C_c[1] = { 0.24000002f };  /* 0x3E75C291 */
static const f32 D_80096620_c[1] = { 0.497f };       /* 0x3EFE76C9 */
static const f32 D_80096624_c[1] = { 0.31500003f };  /* 0x3EA147AF */
static const f32 D_80096634_c[1] = { 40.743664f };   /* 0x4222F983, 256 / 2pi */
static const f32 D_80096600_c[5] = { -1692.0f, 4054.0f, 3890.0f, 4380.0f, 4218.0f };
/* drift paths: start x y z, end x y z (end y = start y: no vertical drift) */
static const f32 D_80096614_c[9][6] = {
    { 2686.0f, -1667.0f, 2063.0f, 2810.0f, -1667.0f, 1637.0f },
    { 2810.0f, -1667.0f, 1637.0f, 2667.0f, -1668.0f, 1236.0f },
    { 2667.0f, -1668.0f, 1236.0f, 2220.0f, -1676.0f, 1025.0f },
    { 1894.0f, -1674.0f, 788.0f, 1841.0f, -1677.0f, 557.0f },
    { 1841.0f, -1677.0f, 557.0f, 1594.0f, -1678.0f, 455.0f },
    { 1594.0f, -1678.0f, 455.0f, 1400.0f, -1678.0f, 613.0f },
    { 1253.0f, -1673.0f, 668.0f, 1075.0f, -1682.0f, 572.0f },
    { 1075.0f, -1682.0f, 572.0f, 872.0f, -1680.0f, 687.0f },
    { 872.0f, -1680.0f, 687.0f, 772.0f, -1676.0f, 931.0f },
};

// level_mist_setup: level-object init (g_level_obj_init_fns[8]): two level_fx_spawn_box_a spawns, four mist_puff_spawn objects whose
// handles go to g_mist_puff_handles[0..3] (x 4054 / 3890 / 4380 / 4218, y -1692, z 0 / -78 / -664 / -740), then nine
// drifting emitters (area_drift_emitter_create, flag 1) along a chain of path segments; each spec gets its start, the vector to
// the segment end and the heading atan2(dx, dz) as a byte angle - 0x40.
/* was func_1500F3BC */
void level_mist_setup(void) {
    DriftSpecF3BC spec;
    const f32 *seg;
    s32 i;

    level_fx_spawn_box_a(0x1612, -0x553, -0x2DC, -0x69F);
    level_fx_spawn_box_a(0x1633, -0x553, -0x3C2, -0x69F);
    g_mist_puff_handles[0] = mist_puff_spawn(D_80096600_c[1], D_80096600_c[0], 0.0f);
    g_mist_puff_handles[1] = mist_puff_spawn(D_80096600_c[2], D_80096600_c[0], -78.0f);
    g_mist_puff_handles[2] = mist_puff_spawn(D_80096600_c[3], D_80096600_c[0], -664.0f);
    g_mist_puff_handles[3] = mist_puff_spawn(D_80096600_c[4], D_80096600_c[0], -740.0f);

    spec.w48 = 3;
    spec.w4C = 2;
    spec.h02 = 0x12;
    spec.h04 = -0x15;
    spec.h06 = 0xF;
    spec.h38 = 0x9B;
    spec.h3A = 0x64;
    spec.h44 = 0x29;
    spec.h46 = 0x29;
    spec.f20 = 7.0f;
    spec.f24 = 10.0f;
    spec.f28 = 0.0f;
    spec.f2C = D_8009661C_c[0];
    spec.f30 = 2.0f;
    spec.f34 = 6.0f;
    spec.f3C = D_80096620_c[0];
    spec.f40 = D_80096624_c[0];
    for (i = 0; i < 9; i++) {
        seg = D_80096614_c[i];
        spec.pos[0] = seg[0];
        spec.pos[1] = seg[1];
        spec.pos[2] = seg[2];
        spec.dir[0] = seg[3] - seg[0];
        spec.dir[1] = seg[4] - seg[1];
        spec.dir[2] = seg[5] - seg[2];
        spec.angle = (s32) (math_atan2f(spec.dir[0], spec.dir[2]) * D_80096634_c[0]) - 0x40;
        area_drift_emitter_create(&spec, 1);
    }
}
