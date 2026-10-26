#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 event_dispatch(s32, s32, ...);
void camera_set_followed_obj(struct108 *, s32);

/* was func_150D0B60 */
void camera_toggle_follow_on_event(struct108 *arg0) {
    if (!(g_save_progress_bits->unk0 & 0x80)) {
        if (event_dispatch(0, 0x2000, 0xBB) != -1) {
            if (camera_push_mode(arg0, arg0->unk2C, 0, arg0->unk134, 8) != 0) {
                arg0->unk84 |= 0x01000000;
                camera_set_followed_obj(arg0, D_800CC335 - 1);
                arg0->unk190 = 100.0f;
            }
        } else if (camera_pop_mode(arg0, 8) != 0) {
            camera_set_followed_obj(arg0, 0);
            arg0->unk190 = 0.0f;
        }
    }
}
