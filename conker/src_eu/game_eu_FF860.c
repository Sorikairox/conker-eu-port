#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 D_800A0CB0;
/* was func_150D2050 */
void ambient_red_flicker_bright_update(s32 arg0) {
    f32 *sp28;
    sp28 = (f32 *)((arg0 ^ 0) + 0x28); sp28 = sp28;
    fx_random_flicker_update(arg0 + 0x30, 10.0f, arg0 + 0x2C, 86.0f, 170.0f, 255.0f, D_800A0CB0, sp28);
    light_set_level_colour(*sp28, ((u8 *)&D_800DCD20)[1], ((u8 *)&D_800DCD20)[2], 0);
}

s32 event_dispatch(s32, s32, ...);

/* was func_150D20E0 */
void player_sync_flag10_event(u8 *arg0) {
    if (event_dispatch(1, 0x402C, 6, 0x2000) != 0) {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x10);
        return;
    }
    (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & ~0x10);
}
