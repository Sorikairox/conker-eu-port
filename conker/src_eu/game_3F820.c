#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void game_gu_ortho(void *, float, float, float, float, float, float, float);

/* was func_15012370 */
void camera_init_player_projections(void) {
    f32 temp_f0;
    f32 temp_f2;
    s32 temp_t0;
    s32 var_s0;
    u8 *temp_v0;

    var_s0 = 0;
    if (D_80082FA0 >= 0) {
        do {
            temp_v0 = D_800BE628 + (var_s0 * 0x180);
            temp_f0 = (*(f32 *)((u8 *)temp_v0 + 4)) * 0.5f;
            temp_f2 = (*(f32 *)((u8 *)temp_v0 + 8)) * 0.5f;
            game_gu_ortho(D_800DD040 + (var_s0 << 6), -temp_f0, temp_f0, -temp_f2, temp_f2, 1.0f, 20000.0f, 1.0f);
            temp_t0 = (var_s0 + 1) & 0xFF;
            var_s0 = temp_t0;
        } while (D_80082FA0 >= temp_t0);
    }
}
// void camera_init_player_projections(void) {
//     f32 temp_f0;
//     f32 temp_f2;
//     u8 i;
//
//     f32 foo = D_80096560; // 20000.0f
//     f32 **tmp = D_800BE628;
//
//     for (i = 0; i <= D_80082FA0; i++) {
//         temp_f0 = tmp[i][1] * 0.5f;
//         temp_f2 = tmp[i][2] * 0.5f;
//         func_151EF954(D_800DCC10[i], -temp_f0, temp_f0, -temp_f2, temp_f2, 1.0f, foo, 1.0f);
//     }
// }

/* was func_15012470 */
void fx_alloc_d88750(void) {
    D_80088750 = timed_queue_create(4, 300, 0);
}

void *memcpy(void *, const void *, unsigned int);
s32 collision_ray_cast(f32, f32, f32, f32, f32, f32, s32, void *, f32 *, f32 *, f32 *, f32 *, s32, s32, f32);
typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} PipeSprayPoint;
extern PipeSprayPoint D_800DCE60[3][10];
// the facing angles of the three pipes: the byte +0xC of each D_8009FCF0 row (a static const PipeSpot table in
// game_eu_E0430.c in the NM build)
static const u8 sPipeAngles[3] = { 0x94, 0xEA, 0x3F };
// pipe_spray_points_init: P259: for each of the three pipes, casts 10 rays (collision_ray_cast) from (0, 300, 0) in
// random directions around the pipe's back-facing angle (yaw = angle - 0x80 + -6..6, pitch -10..5, length 10, angle
// units of 256 per turn via angle_byte_cos) and stores the hits, pulled 3% toward the origin, in D_800DCE60[pipe][i]
// ((0, 0, 0) when nothing is hit); then spawns effect 300 (effect_node_create_nodraw) with the 6-byte parameter block
// {20, 50, 0} at +0x28.
/* was func_150124A0 */
void pipe_spray_points_init(void) {
    struct {
        s16 a;
        s16 b;
        s16 c;
    } params;
    f32 hx;
    f32 hy;
    f32 hz;
    f32 yaw_c;
    f32 yaw_s;
    f32 pitch_c;
    f32 r;
    PipeSprayPoint *pt;
    struct260 *fx;
    s16 yaw;
    s16 pitch;
    s32 pipe;
    s32 i;

    for (pipe = 0; pipe < 3; pipe++) {
        pt = D_800DCE60[pipe];
        for (i = 0; i < 10; i++, pt++) {
            yaw = (u32) random_int() % 13 + sPipeAngles[pipe] - 0x86;
            pitch = (random_int() & 0xF) - 10;
            yaw_c = angle_byte_cos(yaw - 0x40);
            yaw_s = angle_byte_cos(yaw);
            pitch_c = angle_byte_cos(pitch - 0x40);
            r = 10.0f * angle_byte_cos(pitch);
            if (collision_ray_cast(0.0f, 300.0f, 0.0f, r * yaw_c, -10.0f * pitch_c, r * yaw_s, 0, NULL, &hx, &hy, &hz,
                              NULL, 0, 0, 0.0f) == 0) {
                pt->x = 0.0f;
                pt->y = 0.0f;
                pt->z = 0.0f;
            } else {
                pt->x = hx * 0.97f;
                pt->z = hz * 0.97f;
                pt->y = (hy - 300.0f) * 0.97f + 300.0f;
            }
        }
    }
    params.a = 20;
    params.b = 50;
    params.c = 0;
    fx = effect_node_create_nodraw(300, -1, 7, 0, 0, 6, 0xFF, 0);
    if (fx != NULL) {
        memcpy((u8 *) fx + 0x28, &params, 6);
    }
}
