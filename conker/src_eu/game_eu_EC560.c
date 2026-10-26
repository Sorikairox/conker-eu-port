#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
extern f32 D_800A0480;
extern f32 D_800A0484;
s32 event_dispatch(s32, s32, ...);

/* was func_150BED50 */
void player_seat_camera_update(struct108 *arg0) {
    s32 sp28;
    s32 temp_t0;
    s32 temp_v0;

    sp28 = event_dispatch(0, event_dispatch(0, 0x2006, 0xB7) | 0x2000, 0xBC);
    temp_v0 = event_dispatch(0, 0x2000, 0xBB);
    if ((sp28 != 0) && (temp_v0 != -1)) {
        event_dispatch_alt(0, 0x400E, 1);
        if (arg0->unk2C != 8) {
            camera_init_controller(arg0);
        }
        if (camera_push_mode(arg0, 8, 0, arg0->unk134, 3) != 0) {
            camera_set_followed_obj(arg0, D_800CC335 - 1);
            temp_t0 = arg0->unk84 | 0x01000200;
            arg0->unk84 = temp_t0;
            arg0->unk73C = 0;
            arg0->unk84 = temp_t0 & ~4;
            arg0->unk674 = 0.0f;
        }
        arg0->unk348 = D_800A0480;
        arg0->unk34C = D_800A0480;
        arg0->unk374 = D_800A0484;
        arg0->unk190 = 0.0f;
        camera_calc_relative_yaw(arg0);
        return;
    }
    if (camera_pop_mode(arg0, 3) != 0) {
    s32 pad;
        camera_set_followed_obj(arg0, 0);
        arg0->unk674 = 0.0f;
        event_dispatch_alt(0, 0x400E, 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EC560/player_seat_camera_update.s")
#endif