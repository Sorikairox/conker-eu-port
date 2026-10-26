#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 event_dispatch(s32, s32, ...);

/* was func_150E1310 */
void camera_update_level_events(struct108 *arg0) {
    s32 temp_t1;
    s32 temp_t5;
    s32 temp_t9;
    s32 var_v1;

    if (arg0->unk23E == 9) {
        if (D_800BE9F0 == 0x1E) {
            event_dispatch_alt(0, 0x4044, 1);
        }
        if ((arg0->unk2C != 0x100) && (arg0->unk6C8 == 0)) {
            if (camera_push_mode(arg0, 8, 0, 0, 0) != 0) {
                temp_t1 = arg0->unk84 | 0x300000;
                arg0->unk84 = temp_t1;
                arg0->unk84 = temp_t1 & ~4;
                arg0->unk1B4 = 1;
                arg0->unk1E0 = 3;
                camera_apply_zoom_level(arg0);
            }
            arg0->unk348 = 125.0f;
            arg0->unk34C = 125.0f;
            arg0->unk374 = 220.0f;
            arg0->unk190 = 30.0f;
        } else {
            arg0->unk190 = 0.0f;
        }
        goto block_16;
    }
    if ((arg0->unk2C == 8) && (arg0->unk6C8 == 0) && (camera_pop_mode(arg0, 0) != 0)) {
        arg0->unk34C = 110.0f;
        arg0->unk348 = 110.0f;
        arg0->unk374 = 300.0f;
    }
    var_v1 = D_800BE9F0;
    if (var_v1 == 0x1E) {
        event_dispatch_alt(0, 0x4044, 0);
block_16:
        var_v1 = D_800BE9F0;
    }
    if (var_v1 == 0x2F) {
        arg0->unk84 &= 0x7FFFFFFF;
        goto block_26;
    }
    if (var_v1 == 0x1E) {
        if (event_dispatch(1, 0x4042, 6, 0x9000) != 0) {
            arg0->unk84 &= 0x7FFFFFFF;
        } else {
            arg0->unk84 |= 0x80000000;
        }
        if (event_dispatch(1, 0x4044, 6, 0x2000) != 0) {
            temp_t5 = arg0->unk84 | 0x1010;
            arg0->unk84 = temp_t5;
            arg0->unk84 = temp_t5 & ~8;
        } else {
            temp_t9 = arg0->unk84 & ~0x1010;
            arg0->unk84 = temp_t9;
            arg0->unk84 = temp_t9 | 8;
        }
block_26:
        var_v1 = D_800BE9F0;
    }
    if (var_v1 == 0x1B) {
        if (event_dispatch(1, 0x406E, 6, 0x9000) != 0) {
            arg0->unk84 |= 0x200;
        } else {
            arg0->unk84 &= ~0x200;
        }
        if (event_dispatch(1, 0x406F, 6, 0x9000) != 0) {
            arg0->unk84 |= 0x80000000;
            return;
        }
        arg0->unk84 &= 0x7FFFFFFF;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10EB20/camera_update_level_events.s")
#endif