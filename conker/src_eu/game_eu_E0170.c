#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_150B2960 */
s32 emit_handler_ten(s32 arg0, s32 arg1) {
    return 10;
}

void spawn_circle_random_emit(f32, f32, f32, f32, s32, s32, s32, s32, s32, f32, s32, s32);
s32 explosion_light_spawn(f32 *, s32, s32);

/* was func_150B2974 */
void obj_blast_fx_spawn(u8 *arg0, s32 arg1, s32 arg2) {
    f32 sp3C[3];

    sp3C[0] = *(f32 *)(arg0 + 0x14);
    sp3C[1] = *(f32 *)(arg0 + 0x180);
    sp3C[2] = *(f32 *)(arg0 + 0x1C);
    spawn_circle_random_emit(sp3C[0], sp3C[1], sp3C[2], 135.0f, 0, 0xFF, (random_int() % 15U) + 0x1B, 7, 0, 0.0f, 0, 0xFF);
    rumble_all_players_at((struct17 *)sp3C, 1502.0f, 3000.0f, 0.00033333333f, 0xC, 0xF, 0xFF, 0);
    explosion_light_spawn(sp3C, 0xFF, 0);
}

/* P243: readable C for emit_point_spark (game_eu_E0170, 116 insns). */
// emit_point_spark: D_8008ADA0 spawn handler (`s32 (s32 mode, s16 i, f32 x, f32 y, f32 z, f32 x0, f32 y0, f32 z0, s32 a,
// s32 angle0, f32 r, s32 arg8, f32 arg9, s32 argA, s32 argB)`): queues one line_fx_spawn particle (the S_3f24 record of
// game_eu_17D3C0) at (x, y, z) flying out along the byte angle a with a random pitch of -30..-10 (rand % 21 - 30):
// velocity (10 sin(p) sin(a - 0x40), -10 sin(p - 0x40), 10 sin(p) sin(a)) (angle_byte_cos = byte-angle sine), random
// sizes 0.859 * r + 3.608 / 0.309 * r + 2.371 / 1.39 * r + 3.21 (rodata D_8009FCD0..E4), two palette-8 colour
// triples (fx_pick_random_color) with alpha 0xFF, 9, life 18..24 (rand % 7 + 18), 0x1601, -1, 8, 0x1F; owner byte argB.
// Always returns 1 (go on).
typedef struct {
    f32 pos[3];
    f32 vel[3];
    f32 a;
    f32 b;
    u8 c[9];
    s16 d;
    u16 e;
    f32 f;
    s8 g;
    s16 h;
    s16 i;
} Spark2A50;
f32 angle_byte_cos(u8);
void fx_pick_random_color(u8, u8 *, u8 *, u8 *);
s32 line_fx_spawn(Spark2A50 *, u8, s32, u8, s32);

/* was func_150B2A50 */
s32 emit_point_spark(s32 mode, s16 i, f32 x, f32 y, f32 z, f32 x0, f32 y0, f32 z0, s32 a, s32 angle0, f32 r, s32 arg8,
                  f32 arg9, s32 argA, s32 argB) {
    Spark2A50 sp;
    f32 ca, sa, cp, spd;
    s16 pitch;

    ca = angle_byte_cos((a - 0x40) & 0xFF);
    sa = angle_byte_cos(a & 0xFF);
    pitch = (u32) random_int() % 21U - 30;
    cp = angle_byte_cos((pitch - 0x40) & 0xFF);
    spd = 10.0f * angle_byte_cos(pitch & 0xFF);
    sp.pos[0] = x;
    sp.pos[1] = y;
    sp.pos[2] = z;
    sp.vel[0] = spd * ca;
    sp.vel[1] = -10.0f * cp;
    sp.vel[2] = spd * sa;
    sp.a = random_float() * 0.859f + 3.6080003f;
    sp.b = random_float() * 0.30900002f + 2.371f;
    fx_pick_random_color(8, &sp.c[0], &sp.c[1], &sp.c[2]);
    fx_pick_random_color(8, &sp.c[4], &sp.c[5], &sp.c[6]);
    sp.c[3] = 0xFF;
    sp.c[7] = 0xFF;
    sp.c[8] = 9;
    sp.d = (u32) random_int() % 7U + 0x12;
    sp.f = random_float() * 1.39f + 3.21f;
    sp.e = 0x1601;
    sp.g = -1;
    sp.h = 8;
    sp.i = 0x1F;
    line_fx_spawn(&sp, 1, 0, argB & 0xFF, 1);
    return 1;
}
