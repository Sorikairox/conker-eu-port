#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* was func_1512DD50 */
void camera_orbit_point_init(u8 *arg0) {
    struct {
        f32 u20;
        f32 u24;
        f32 u28;
        u8 pad2C[0x14];
        f32 u40;
    } sp;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f4;
    f32 var_f6;
    s32 temp_t0;
    s32 temp_t1;
    u8 *temp_v0;
    u8 *temp_v1;

    sp.u40 = (f32) (*(s16 *)((u8 *)arg0 + 0x710));
    temp_f2 = (f32) (*(s16 *)((u8 *)arg0 + 0x712));
    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x720)) * temp_f2;
    temp_f12 = (*(f32 *)((u8 *)arg0 + 0x724)) * temp_f2;
    temp_f0_2 = (*(f32 *)((u8 *)arg0 + 0x728)) * temp_f0;
    temp_f14 = -temp_f0 * (*(f32 *)((u8 *)arg0 + 0x72C));
    (*(f32 *)((u8 *)arg0 + 0x878)) = (f32) ((f32) (*(s16 *)((u8 *)arg0 + 0x70E)) - temp_f12);
    (*(f32 *)((u8 *)arg0 + 0x874)) = (f32) ((f32) (*(s16 *)((u8 *)arg0 + 0x70C)) - temp_f0_2);
    (*(f32 *)((u8 *)arg0 + 0x87C)) = (f32) (sp.u40 - temp_f14);
    sp.u20 = 2.0f * temp_f0_2;
    sp.u24 = 2.0f * temp_f12;
    sp.u28 = 2.0f * temp_f14;
    temp_f2_2 = 1.0f / vec3f_magnitude(&sp.u20);
    temp_v0 = arg0 + 0x870;
    temp_v1 = arg0 + 0x6FC;
    (*(f32 *)((u8 *)temp_v0 + 0x1C)) = temp_f2_2;
    (*(f32 *)((u8 *)temp_v0 + 0x10)) = (f32) (temp_f2_2 * sp.u20);
    (*(f32 *)((u8 *)temp_v0 + 0x14)) = (f32) (temp_f2_2 * sp.u24);
    (*(f32 *)((u8 *)temp_v0 + 0x18)) = (f32) (temp_f2_2 * sp.u28);
    temp_t0 = (*(s32 *)((u8 *)temp_v1 + 0x20));
    var_f6 = (f32) temp_t0;
    if (temp_t0 < 0) {
        var_f6 += 4294967296.0f;
    }
    (*(f32 *)((u8 *)temp_v0 + 0x20)) = var_f6;
    temp_t1 = (*(s32 *)((u8 *)temp_v1 + 8));
    var_f4 = (f32) temp_t1;
    if (temp_t1 < 0) {
        var_f4 += 4294967296.0f;
    }
    (*(f32 *)((u8 *)temp_v0 + 0x24)) = var_f4;
    (*(f32 *)((u8 *)temp_v0 + 0x28)) = 0.0f;
    (*(f32 *)((u8 *)temp_v0 + 0x2C)) = 0.0f;
    (*(s8 *)((u8 *)temp_v0 + 0)) = (s8) (*(s32 *)((u8 *)temp_v1 + 0x1C));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_15B200/camera_orbit_point_init.s")
#endif
// void camera_orbit_point_init(struct108 *arg0) {
//     s32 pad;
//     struct17 tmp;
//
//     f32 temp_f0;
//     f32 temp_f0_2;
//     f32 temp_f12;
//     f32 temp_f14;
//     f32 temp_f2;
//
//     struct127 *temp_v0;
//     struct164 *temp_v1;
//
//     temp_f2 = arg0->unk712;
//     temp_f0 = arg0->unk720 * temp_f2;
//     temp_f12 = arg0->unk724 * temp_f2;
//     temp_f0_2 = arg0->unk728 * temp_f0;
//     temp_f14 = -temp_f0 * arg0->unk72C;
//
//     arg0->unk874 = arg0->unk70C - temp_f0_2;
//     arg0->unk878 = arg0->unk70E - temp_f12;
//     arg0->unk87C = arg0->unk710 - temp_f14;
//
//     tmp.unk0 = 2.0f * temp_f0_2;
//     tmp.unk4 = 2.0f * temp_f12;
//     tmp.unk8 = 2.0f * temp_f14;
//
//     temp_f2 = 1.0f / vec3f_magnitude(&tmp);
//     temp_v0 = arg0->unk870;
//     temp_v0->unk1C = temp_f2;
//     temp_v0->unk10 = temp_f2 * tmp.unk0;
//     temp_v0->unk14 = temp_f2 * tmp.unk4;
//     temp_v0->unk18 = temp_f2 * tmp.unk8;
//     temp_v1 = arg0->unk6FC;
//     temp_v0->unk20 = temp_v1->unk20;
//     temp_v0->unk24 = temp_v1->unk8;
//     temp_v0->unk28 = 0.0f;
//     temp_v0->unk2C = 0.0f;
//     temp_v0->unk0 = (s8) temp_v1->unk1C;
// }

#ifdef NON_MATCHING
void math_spring_approach(f32 *cur, f32 target, f32 *vel, f32 arg3, f32 arg4, f32 arg5);
float sqrtf(float);

// camera_orbit_point_update: camera block at +0x870 (mode byte +0x870, unit direction +0x880..+0x888, side speed
// +0x890, vertical speed +0x894). Sets the point +0x8A8..+0x8B0 to +0x874 plus the direction times the distance
// from +0x2BC to +0x874, then moves it by (vx, +0x894, vz): (vx, vz) = speed times (dz, -dx) / (-dz, dx) / (dx, dz)
// / (-dx, -dz) for modes 0..3 (the asm leaves them unset for other modes). With +0x23C set the camera position
// +0x2F8 jumps to the point and the rates +0x898 / +0x89C become 40; else the rates ease to 10 (math_spring_approach,
// 0.6, 1.4, frame step +0x7B4) and the position eases towards the point (velocity +0x3C0).
/* was func_1512DEA4 */
void camera_orbit_point_update(struct108 *arg0) {
    u8 *p = (u8 *) arg0;
    f32 *c = (f32 *) (p + 0x870); /* c[4] = +0x880 ... */
    f32 dx, dy, dz;
    f32 dist;
    f32 vx, vy, vz; /* the asm leaves vx / vz unset for a mode above 3 */

    dx = *(f32 *) (p + 0x874) - *(f32 *) (p + 0x2BC);
    dy = *(f32 *) (p + 0x878) - *(f32 *) (p + 0x2C0);
    dz = *(f32 *) (p + 0x87C) - *(f32 *) (p + 0x2C4);
    dist = sqrtf(dx * dx + dy * dy + dz * dz);
    *(f32 *) (p + 0x8A8) = *(f32 *) (p + 0x874) + *(f32 *) (p + 0x880) * dist;
    *(f32 *) (p + 0x8AC) = *(f32 *) (p + 0x878) + *(f32 *) (p + 0x884) * dist;
    *(f32 *) (p + 0x8B0) = *(f32 *) (p + 0x87C) + *(f32 *) (p + 0x888) * dist;
    vy = c[9]; /* +0x894 */
    switch (p[0x870]) {
    case 0:
        vx = c[8] * c[6];
        vz = c[8] * -c[4];
        break;
    case 1:
        vx = c[8] * -c[6];
        vz = c[8] * c[4];
        break;
    case 2:
        vx = c[8] * c[4];
        vz = c[8] * c[6];
        break;
    case 3:
        vx = c[8] * -c[4];
        vz = c[8] * -c[6];
        break;
    }
    c[14] += vx; /* +0x8A8 */
    c[15] += vy;
    c[16] += vz;
    if (p[0x23C] != 0) {
        *(f32 *) (p + 0x2F8) = c[14];
        *(f32 *) (p + 0x2FC) = c[15];
        *(f32 *) (p + 0x300) = c[16];
        c[10] = 40.0f;
        c[11] = 40.0f;
    } else {
        math_spring_approach(&c[10], 10.0f, &c[12], 0.6f, 1.4f /* D_800A3AF0 */, *(f32 *) (p + 0x7B4));
        math_spring_approach(&c[11], 10.0f, &c[13], 0.6f, 1.4f /* D_800A3AF4 */, *(f32 *) (p + 0x7B4));
        math_spring_approach((f32 *) (p + 0x2F8), c[14], (f32 *) (p + 0x3C0), c[10], c[11], *(f32 *) (p + 0x7B4));
        math_spring_approach((f32 *) (p + 0x2FC), c[15], (f32 *) (p + 0x3C4), c[10], c[11], *(f32 *) (p + 0x7B4));
        math_spring_approach((f32 *) (p + 0x300), c[16], (f32 *) (p + 0x3C8), c[10], c[11], *(f32 *) (p + 0x7B4));
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_15B200/camera_orbit_point_update.s")
#endif
