#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 event_dispatch(s32, s32, ...);
s32 camera_pop_mode(struct108 *arg0, s32 arg1);
void camera_set_followed_obj(struct108 *, s32);
extern s32 D_80088E30;

// player_mode_flags_update: player state handler (D_80089A10 table). When event flags 0x2006/0xB7 -> 0xBC and
// 0x2000/0xBB are both set, sets flags 0x405D..0x4061 and (unless state +0x2C is 0x100 or +0x6C8 is busy) enters the
// mode: camera_push_mode(.., 8, 0, 0, 3) success sets +0x84 bits 0x1100004 (clears 2), +0x674 = 0, anim
// camera_set_followed_obj(+0x3D0->0x65 - 1), +0x5F0 |= 0x10; then speeds +0x348 / +0x34C = 320, +0x374 = 550 (D_800A1850),
// +0x190 = 180, D_80088E30 = 1, flag 0x405C cleared. Otherwise leaves it (camera_pop_mode(.., 3): +0x190 = 0, anim
// +0x23D, +0x5F0 &= ~0x10, +0x674 = 0, D_80088E30 = 0), sets 0x405C, clears 0x405D..0x4061 and mirrors event
// 0x4040 / 6 / 0x9000 into +0x84 bit 0x80.
/* was func_150EB740 */
void camera_update_event_lock(u8 *obj) {
    s32 a;
    s32 b;
    s32 c;

    a = event_dispatch(0, 0x2006, 0xB7);
    b = event_dispatch(0, a | 0x2000, 0xBC);
    c = event_dispatch(0, 0x2000, 0xBB);
    if (b != 0 && c != 0) {
        event_dispatch_alt(0, 0x405D, 1);
        event_dispatch_alt(0, 0x405E, 1);
        event_dispatch_alt(0, 0x405F, 1);
        event_dispatch_alt(0, 0x4060, 1);
        event_dispatch_alt(0, 0x4061, 1);
        if (*(s32 *) (obj + 0x2C) == 0x100 || *(s32 *) (obj + 0x6C8) != 0) {
            return;
        }
        if (camera_push_mode((struct108 *) obj, 8, 0, 0, 3) != 0) {
            *(s32 *) (obj + 0x84) |= 0x1100004;
            *(s32 *) (obj + 0x84) &= ~2;
            *(f32 *) (obj + 0x674) = 0.0f;
            camera_set_followed_obj((struct108 *) obj, (*(u8 **) (obj + 0x3D0))[0x65] - 1);
            *(s32 *) (obj + 0x5F0) |= 0x10;
        }
        *(s32 *) (obj + 0x134) = 0;
        *(f32 *) (obj + 0x348) = 320.0f;
        *(f32 *) (obj + 0x34C) = 320.0f;
        *(f32 *) (obj + 0x374) = 550.0f; /* D_800A1850 */
        *(f32 *) (obj + 0x190) = 180.0f;
        D_80088E30 = 1;
        event_dispatch_alt(0, 0x405C, 0);
        return;
    }
    if (camera_pop_mode((struct108 *) obj, 3) != 0) {
        *(f32 *) (obj + 0x190) = 0.0f;
        camera_set_followed_obj((struct108 *) obj, obj[0x23D]);
        *(s32 *) (obj + 0x5F0) &= ~0x10;
        *(f32 *) (obj + 0x674) = 0.0f;
        D_80088E30 = 0;
    }
    event_dispatch_alt(0, 0x405C, 1);
    event_dispatch_alt(0, 0x405D, 0);
    event_dispatch_alt(0, 0x405E, 0);
    event_dispatch_alt(0, 0x405F, 0);
    event_dispatch_alt(0, 0x4060, 0);
    event_dispatch_alt(0, 0x4061, 0);
    if (event_dispatch(1, 0x4040, 6, 0x9000) != 0) {
        *(s32 *) (obj + 0x84) |= 0x80;
    } else {
        *(s32 *) (obj + 0x84) &= ~0x80;
    }
}
