#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void mtx_get_translation(void *, s32, void *);

/* was func_150C1EC0 */
s32 obj_fx_point_foot(s32 arg0, u8 *arg1, s32 arg2) {
    s32 sp1C;
    s32 temp_t6;

    temp_t6 = arg2 & 0xFF;
    switch (temp_t6) {                              /* irregular */
    case 1:
        sp1C = 0x18;
        break;
    case 2:
        sp1C = 0x15;
        break;
    }
    mtx_get_translation((*(s32 *)((u8 *)arg1 + 0x1D4)), sp1C, arg0);
    return 1;
}
/* was func_150C1F2C */
s32 foot_fx_effect_id(s32 arg0, s32 arg1) {
    return 7;
}

s32 spawn_ring_emit(f32, f32, f32, f32, s32, s32, s32, s32, s32, f32, s32, s32);

/* was func_150C1F40 */
void foot_step_ring_effect(u8 *arg0, s32 arg1, s32 arg2) {
    struct {
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
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        s32 uF4;
        s16 uF8;
        s16 uFA;
        s8 uFC;
        u8 padFD[0x3];
        s32 u100;
        s8 u104;
        s8 u105;
        s8 u106;
        s8 u107;
        s8 u108;
        s8 u109;
        s8 u10A;
        s8 u10B;
        s8 u10C;
        u8 pad10D[0x1];
        s8 u10E;
        u8 pad10F[0x1];
        u8 * u110;
        u8 u114;
        u8 pad115[0x1];
        s16 u116;
        s16 u118;
        u8 pad11A[0x6];
        f32 u120;
        f32 u124;
        u8 pad128[0x4];
        f32 u12C;
    } sp;
    f32 sp7C;
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f2;
    s32 temp_s0;
    s32 temp_v1;
    s32 var_s1;
    s32 var_v0;
    u8 *temp_v0;

    if ((*(s32 *)((u8 *)arg0 + 0x1D4)) != 0) {
        sp.u120 = ((*(f32 *)((u8 *)arg0 + 0x14C)) + (*(f32 *)((u8 *)arg0 + 0x150))) * 0.5f;
        obj_fx_point_foot(&sp.u124, arg0, arg1 & 0xFF);
        if (arg1 == 1) {
            var_v0 = 0x10;
        } else {
            var_v0 = -0x10;
        }
        temp_f0 = sp.u120 * 70.0f;
        sp7C = temp_f0;
        spawn_ring_emit(sp.u124, (*(f32 *)((u8 *)arg0 + 0x180)), sp.u12C, temp_f0, (((s32) (*(u16 *)((u8 *)arg0 + 0x76)) >> 8) + 0x40) & 0xFF, var_v0, 8, 0, 0, temp_f0 * 4.04f, 0, 0xFF);
        water_ring_spawn(-1, (s32) sp.u124, (s32) ((f32) (s32) (*(f32 *)((u8 *)arg0 + 0x180)) + 2.0f), (s32) sp.u12C, 8, 0x15, 0, 0xFF, 0);
        sp.uFA = 5;
        sp.uF4 = 0x29E9;
        sp.uFC = 0;
        sp.u100 = 0;
        sp.u104 = 0xFF;
        sp.u105 = 1;
        sp.u106 = 0;
        sp.u107 = 0;
        sp.u108 = 0;
        sp.u109 = 0;
        sp.u10A = 0;
        sp.u10B = 0;
        sp.u10C = 0;
        sp.u10E = 1;
        sp.u110 = arg0;
        sp.uC0 = 1.0f;
        sp.uC4 = 1.0f;
        sp.uC8 = 1.0f;
        sp.uA8 = 0.4f;
        sp.uEC = 0.0f;
        sp.uF0 = -0.9f;
        sp.u116 = 0x10;
        sp.u118 = 0xF;
        sp.u114 = (*(u8 *)((u8 *)arg0 + 0x3B));
        temp_v1 = (random_int() & 7) + 5;
        var_s1 = temp_v1 - 1;
        if (temp_v1 != 0) {
            do {
                temp_s0 = random_int() & 0xFF;
                temp_f20 = ((random_float() * 0.9f) + 0.1f) * 9.0f * sp.u120;
                temp_f22 = angle_byte_cos((temp_s0 - 0x40) & 0xFF);
                temp_f24 = angle_byte_cos(temp_s0 & 0xFF);
                sp.uF8 = (random_int() & 0xF) + 0x1E;
                sp.uCC = (sp7C * temp_f22) + sp.u124;
                sp.uD0 = (*(f32 *)((u8 *)arg0 + 0x180)) + 2.0f;
                sp.uDC = 2.0f * temp_f20;
                sp.uD8 = temp_f20 * temp_f22;
                sp.uD4 = (sp7C * temp_f24) + sp.u12C;
                sp.uE0 = temp_f20 * temp_f24;
                temp_f2 = ((random_float() * 0.9f) + 0.1f) * sp.u120 * 1.5f;
                sp.uAC = temp_f2;
                sp.uB0 = temp_f2;
                sp.uA4 = temp_f2;
                sp.uB4 = random_float() * 360.0f;
                sp.uB8 = random_float() * 360.0f;
                sp.uBC = random_float() * 360.0f;
                sp.uE4 = 25.0f - (random_float() * 50.0f);
                sp.uE8 = 25.0f - (random_float() * 50.0f);
                temp_v0 = mdl_particle_spawn(&sp.uA4, 3, 0xFF, 4, 0xFF, 0);
                if (temp_v0 != NULL) {
                    (*(f32 *)((u8 *)temp_v0 + 0x170)) = (f32) (*(f32 *)((u8 *)arg0 + 0x180));
                }
                var_s1 -= 1;
            } while (var_s1 != 0);
        }
    }
}
/* P243: readable C for emit_point_puff (game_eu_EF6D0, 75 insns). */
// emit_point_puff: g_emit_point_spawn_fns spawn handler (`s32 (s32 mode, s16 i, f32 x, f32 y, f32 z, f32 x0, f32 y0, f32 z0, s32 a,
// s32 angle0, f32 r, s32 arg8, f32 arg9, s32 argA, s32 argB)`, emitters spawn_ring_emit / spawn_line_emit / spawn_circle_random_emit):
// queues one puff_sprite_spawn particle at (x, y, z): drift (x - x0, z - z0) * 10, size (s32) arg9 and (s32) (arg9 *
// 0.1757) (double, the ROM's D_800A05F8), constants 150 / 20 / 600, two fx_pick_random_color colour triples of palette 0,
// alpha bytes 0xFF / 0xFF, a random 12..27 byte and 1 (the record layout of spark_die_spawn_burst). Always returns 1 (go on).
typedef struct {
    f32 pos[3];
    u8 unkC[0xA];
    s16 h16, h18, h1A, h1C, h1E, h20, h22, h24, h26;
    u8 c0[3];
    u8 c1[3];
    u8 b2E, b2F, b30, b31;
} Puff2334;
void fx_pick_random_color(u8, u8 *, u8 *, u8 *);
void puff_sprite_spawn(Puff2334 *, s32);

/* was func_150C2334 */
s32 emit_point_puff(s32 mode, s16 i, f32 x, f32 y, f32 z, f32 x0, f32 y0, f32 z0, s32 a, s32 angle0, f32 r, s32 arg8,
                  f32 arg9, s32 argA, s32 argB) {
    Puff2334 s;
    s16 size;
    s16 sizeB;

    s.pos[0] = x;
    s.pos[1] = y;
    s.pos[2] = z;
    size = (s32) arg9;
    sizeB = (s32) (arg9 * 0.1757);
    s.h1E = (s32) ((x - x0) * 10.0f);
    s.h20 = (s32) ((z - z0) * 10.0f);
    s.h22 = 150;
    s.h26 = 600;
    s.h24 = 20;
    s.h16 = size;
    s.h18 = size;
    s.h1A = sizeB;
    s.h1C = sizeB;
    fx_pick_random_color(0, &s.c0[0], &s.c0[1], &s.c0[2]);
    fx_pick_random_color(0, &s.c1[0], &s.c1[1], &s.c1[2]);
    s.b2E = 0xFF;
    s.b2F = 0xFF;
    s.b30 = (random_int() & 0xF) + 12;
    s.b31 = 1;
    puff_sprite_spawn(&s, 1);
    return 1;
}
