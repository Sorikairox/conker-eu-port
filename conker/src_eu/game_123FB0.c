#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 event_dispatch(s32, s32, ...);
f32 vec3f_dot(struct17 *, struct17 *);
void math_spring_approach_angle(f32 *, f32, s32 *, f32, f32, f32);
extern struct17 g_camera_segment_start;  /* (0, 98, -5530); was D_800A1F50 */
extern struct17 g_camera_segment_end;  /* (0, 98, 1198); was D_800A1F5C */
extern struct17 D_800D9E70;

// camera_segment_track: while button state (event_dispatch(1, 0x4003, 6, 0x2000)) holds and the target object
// (+0x3D0) is alive, sets flags 0xC0001000 in +0x84 and steers the camera: t = the projection of +0x2A4 on the
// segment g_camera_segment_start -> g_camera_segment_end (0.75 x, clamped to 0..1); the two button groups pick a side offset of -900 / +900
// (distance 220) or none (294); event_dispatch_alt gets (offset, -20, 6728 t - 5530); the angle +0x37C eases towards the
// D_800D9E70 heading - 180 (math_spring_approach_angle) and +0x39C is it in radians. Otherwise the flags are cleared.
/* was func_150F6B00 */
void camera_segment_track(struct108 *arg0) {
    struct17 toObj;
    struct17 axis;
    struct17 dir;
    f32 invLen;
    f32 t;
    f32 offset;

    if (event_dispatch(1, 0x4003, 6, 0x2000) != 0 && arg0->unk3D0->health != 0) {
        arg0->unk84 |= 0xC0001000;
        vec3_diff(&g_camera_segment_start, (struct17 *) &arg0->unk2A4, &toObj);
        vec3_diff(&g_camera_segment_start, &g_camera_segment_end, &axis);
        invLen = 1.0f / vec3f_magnitude((f32 *) &axis);
        vec3_normalize(&axis, &dir);
        t = vec3f_dot(&dir, &toObj) * invLen * 0.75f;
        if (t < 0.0f) {
            t = 0.0f;
        } else if (1.0f < t) {
            t = 1.0f;
        }
        if (event_dispatch(4, 0x2000, 0xAC, 0x4040, 0x4041, 0x4042, 0x4043) != 0) {
            offset = 0.0f * t + -900.0f;
            arg0->unk374 = 220.0f;
        } else if (event_dispatch(4, 0x2000, 0xAC, 0x4047, 0x4046, 0x4045, 0x4044) != 0) {
            offset = 0.0f * t + 900.0f;
            arg0->unk374 = 220.0f;
        } else {
            offset = 0.0f * t;
            arg0->unk374 = 294.0f;
        }
        event_dispatch_alt(3, 0x4003, 3, (s32) offset, (s32) -20.0f, (s32) (6728.0f * t + -5530.0f));
        math_spring_approach_angle(&arg0->unk37C, vec3_heading_deg(&D_800D9E70) - 180.0f, &arg0->unk7C8, 8.0f, 10.0f,
                      arg0->unk7B4);
        arg0->unk39C = arg0->unk37C * 0.017453292f;
    } else {
        arg0->unk84 &= 0x3FFFEFFF;
    }
}
// NON-MATCHING: 90% there
// void camera_segment_track(struct108 *arg0) {
//     struct190 tmp;
//
//     f32 phi_f2;
//     f32 temp_f2;
//     f32 phi_f0_2;
//
//     // event_dispatch has variable number of args
//     if ((event_dispatch(1, 16387, 6, 8192) != 0) && (arg0->unk3D0->unk1CA != 0)) {
//         arg0->unk84 |= 0xC0001000;
//         vec3_diff(&D_800A1B80, &arg0->unk2A4, &tmp.unk14);
//         vec3_diff(&D_800A1B80, &D_800A1B8C, &tmp.unk8);
//         tmp.unk0 = 1.0f / vec3f_magnitude(&tmp.unk8);
//         vec3_normalize(&tmp.unk8, &tmp.unk20);
//         temp_f2 = func_150AD900(&tmp.unk20, &tmp.unk14) * tmp.unk0 * 0.75f;
//         if (temp_f2 < 0.0f) {
//             phi_f2 = 0.0f;
//         } else {
//             if (temp_f2 > 1.0f) {
//                 phi_f0_2 = 1.0f;
//             } else {
//                 phi_f0_2 = temp_f2;
//             }
//             phi_f2 = phi_f0_2;
//         }
//         tmp.unk4 = phi_f2;
//         if (event_dispatch(4, 8192, 172, 16448, 16449, 16450, 16451) != 0) {
//             phi_f0_2 = (0.0f * tmp.unk4) + -900.0f;
//             arg0->unk374 = 220.0f;
//         } else {
//             if (event_dispatch(4, 8192, 172, 16455, 16454, 16453, 16452) != 0) {
//                 phi_f0_2 = (0.0f * tmp.unk4) + 900.0f;
//                 arg0->unk374 = 220.0f;
//             } else {
//                 phi_f0_2 = 0.0f * tmp.unk4;
//                 arg0->unk374 = 294.0f;
//             }
//         }
//         // takes a variable number of args
//         event_dispatch_alt(3, 16387, 3, phi_f0_2, -20.0f, ((s32)(D_800A1B98 * phi_f2) + D_800A1B9C));
//         func_15049688(&arg0->unk37C, vec3_heading_deg(&D_800D9A50) - 180.0f, &arg0->unk7C8, 8.0f, 10.0f, arg0->unk7B4);
//         arg0->unk39C = arg0->unk37C * D_800A1BA0;
//     } else {
//         arg0->unk84 = arg0->unk84 & 0x3FFFEFFF;
//     }
// }
