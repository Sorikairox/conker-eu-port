#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 event_dispatch(s32, s32, ...);
void camera_set_followed_obj(struct108 *, s32);
void camera_calc_relative_yaw(struct108 *arg0);
extern s32 D_80088BA0;

// player_flight_mode_update: player state handler (D_80089A10 table) for a flag-driven mode with two variants.
// Event flags: b = 0x2010/0xB7 -> 0xBC, c = 0x2000/0xBB, e = 0x2010/0xB7 -> 0xBB.
// Without 0x5071/0x1A: c set and b clear enters state +0x2C (camera_push_mode(+0x2C, 0, +0x134, 3); success sets +0x84
// bit 0x1000000, anim D_800CC335 - 1, +0x674 = 0); c and b set: camera_pop_mode(.., 2), then state 8 (success: anim,
// +0x84 &= ~4, +0x674 = 0, camera_calc_relative_yaw), +0x5F0 |= 0x200, speeds +0x348 / +0x34C = 500, +0x374 = 800; c clear
// leaves the state (camera_pop_mode(.., 3): anim 0, +0x84 &= ~0x1000000, +0x3D4->0x198 = 0, +0x73C = 0, +0x674 = 0
// unless +0x6C8 is busy) and clears +0x5F0 bit 0x200.
// With 0x5071 but not 0x5072: +0x190 = 20 when the pad (+0x36C) has bit 4; without event 0x2000/0x93 +0x190 = 0 and
// stop. Otherwise copies event 0x2011/0xB7 -> 0x9C into 0x9000/0x17, takes t = (0x2011/0xB7 -> 0x9A - 300) / 900
// clamped to 0..1; b clear: speeds 200, +0x190 = 100; b set: +0x190 = 287 + 103 t, +0x374 = 750 + 224 t, speeds
// 231 t. Sets 0x9000/6 slots 1 and 0, clears +0x670 when e is not -1, D_80088BA0 = 0, and with +0x5F0 bit 4 copies
// object 0x10's +0x14..+0x1C into +0x3D0 (if its +0x65 is set); leaves the state as above (also clearing 0x200).
// With 0x5072: when camera_pop_mode(.., 3) succeeds or D_80088BA0 is 0: +0x84 |= 4, D_80088BA0 = 1, anim 0,
// +0x3D4->0x198 = 0, +0x73C = 0, +0x1B4 = 3, camera_apply_zoom_level, +0x190 = 0, +0x674 = 0 unless +0x6C8 is busy.
// Finally (except the early returns) +0x190 = 0 while the pad has bit 4.
/* was func_150C8300 */
void player_flight_mode_update(u8 *obj) {
    s32 b;
    s32 c;
    s32 e;
    s32 v;
    f32 t;
    u8 *other;

    b = event_dispatch(0, event_dispatch(0, 0x2010, 0xB7) | 0x2000, 0xBC);
    c = event_dispatch(0, 0x2000, 0xBB);
    e = event_dispatch(0, event_dispatch(0, 0x2010, 0xB7) | 0x2000, 0xBB);
    if (event_dispatch(0, 0x5071, 0x1A) == 0) {
        if (c != -1 && b == 0) {
            if (camera_push_mode((struct108 *) obj, *(s32 *) (obj + 0x2C), 0, *(s32 *) (obj + 0x134), 3) == 0) {
                return;
            }
            *(s32 *) (obj + 0x84) |= 0x1000000;
            camera_set_followed_obj((struct108 *) obj, D_800CC335 - 1);
            *(f32 *) (obj + 0x674) = 0.0f;
        } else if (c != -1) {
            camera_pop_mode((struct108 *) obj, 2);
            if (camera_push_mode((struct108 *) obj, 8, 0, *(s32 *) (obj + 0x134), 3) != 0) {
                camera_set_followed_obj((struct108 *) obj, D_800CC335 - 1);
                *(s32 *) (obj + 0x84) &= ~4;
                *(f32 *) (obj + 0x674) = 0.0f;
                camera_calc_relative_yaw((struct108 *) obj);
            }
            *(s32 *) (obj + 0x5F0) |= 0x200;
            *(f32 *) (obj + 0x348) = 500.0f;
            *(f32 *) (obj + 0x34C) = 500.0f;
            *(f32 *) (obj + 0x374) = 800.0f;
        } else {
            if (camera_pop_mode((struct108 *) obj, 3) != 0) {
                camera_set_followed_obj((struct108 *) obj, 0);
                *(s32 *) (obj + 0x84) &= ~0x1000000;
                (*(u8 **) (obj + 0x3D4))[0x198] = 0;
                *(s16 *) (obj + 0x73C) = 0;
                if (*(s32 *) (obj + 0x6C8) == 0) {
                    *(f32 *) (obj + 0x674) = 0.0f;
                }
            }
            *(s32 *) (obj + 0x5F0) &= ~0x200;
        }
        return;
    }
    if (event_dispatch(0, 0x5072, 0x1A) == 0) {
        if (**(u16 **) (obj + 0x36C) & 4) {
            *(f32 *) (obj + 0x190) = 20.0f;
        }
        if (event_dispatch(0, 0x2000, 0x93) == 0) {
            *(f32 *) (obj + 0x190) = 0.0f;
            return;
        }
        v = event_dispatch(1, event_dispatch(0, 0x2011, 0xB7) | 0x2000, 0x9C, 0x2000);
        event_dispatch_alt(1, 0x9000, 0x17, v);
        v = event_dispatch(1, event_dispatch(0, 0x2011, 0xB7) | 0x2000, 0x9A, 0x2000);
        t = ((f32) v - 300.0f) / 900.0f;
        if (t < 0.0f) {
            t = 0.0f;
        } else if (1.0f < t) {
            t = 1.0f;
        }
        if (b == 0) {
            *(f32 *) (obj + 0x34C) = 200.0f;
            *(f32 *) (obj + 0x348) = 200.0f;
            *(f32 *) (obj + 0x190) = 100.0f;
        } else {
            *(f32 *) (obj + 0x190) = 103.0f * t + 287.0f;
            *(f32 *) (obj + 0x374) = 224.0f * t + 750.0f;
            *(f32 *) (obj + 0x34C) = 231.0f * t;
            *(f32 *) (obj + 0x348) = 231.0f * t;
        }
        event_dispatch_alt(2, 0x9000, 6, 1, 0x20000);
        event_dispatch_alt(2, 0x9000, 6, 0, 4);
        if (e != -1) {
            *(f32 *) (obj + 0x670) = 0.0f;
        }
        D_80088BA0 = 0;
        if (*(s32 *) (obj + 0x5F0) & 4) {
            other = (u8 *) obj_find_by_setup_id(0x10);
            if (other != NULL && (*(u8 **) (obj + 0x3D0))[0x65] != 0) {
                *(f32 *) (*(u8 **) (obj + 0x3D0) + 0x14) = *(f32 *) (other + 0x14);
                *(f32 *) (*(u8 **) (obj + 0x3D0) + 0x18) = *(f32 *) (other + 0x18);
                *(f32 *) (*(u8 **) (obj + 0x3D0) + 0x1C) = *(f32 *) (other + 0x1C);
            }
        }
        if (camera_pop_mode((struct108 *) obj, 3) != 0) {
            *(s32 *) (obj + 0x5F0) &= ~0x200;
            camera_set_followed_obj((struct108 *) obj, 0);
            *(s32 *) (obj + 0x84) &= ~0x1000000;
            (*(u8 **) (obj + 0x3D4))[0x198] = 0;
            *(s16 *) (obj + 0x73C) = 0;
            if (*(s32 *) (obj + 0x6C8) == 0) {
                *(f32 *) (obj + 0x674) = 0.0f;
            }
        }
    } else if (camera_pop_mode((struct108 *) obj, 3) != 0 || D_80088BA0 == 0) {
        *(s32 *) (obj + 0x84) |= 4;
        D_80088BA0 = 1;
        camera_set_followed_obj((struct108 *) obj, 0);
        (*(u8 **) (obj + 0x3D4))[0x198] = 0;
        *(s16 *) (obj + 0x73C) = 0;
        *(s16 *) (obj + 0x1B4) = 3;
        camera_apply_zoom_level((struct108 *) obj);
        *(f32 *) (obj + 0x190) = 0.0f;
        if (*(s32 *) (obj + 0x6C8) == 0) {
            *(f32 *) (obj + 0x674) = 0.0f;
        }
    }
    if (**(u16 **) (obj + 0x36C) & 4) {
        *(f32 *) (obj + 0x190) = 0.0f;
    }
}
