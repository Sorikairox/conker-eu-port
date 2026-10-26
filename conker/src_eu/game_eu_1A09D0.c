#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
extern s8 D_800DD6E0[];

/* reset the two 16-byte tables, then keep arg0 in the first entry */
/* was func_15172C50 */
void warp_requests_reset(u8 arg0) {
    s32 i;

    for (i = 0; i < 16; i++) {
        D_800DD6E0[i] = -1;
        (&D_800DD2C0)[i] = 0;
    }
    D_800DD2C0 = arg0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A09D0/warp_requests_reset.s")
#endif
s32 screen_fade_start(s32, s32, s32, s32, s32, s32);
extern s8 D_800DD6E0[];

/* was func_15173218 */
void warp_request_cancel(s32 arg0) {
    s8 *temp_v0 = D_800DD6E0 + arg0;
    if (*temp_v0 != -1) {
        *temp_v0 = -1;
        screen_fade_start(0, 0, 0, 0, 1, arg0);
        screen_fade_start(0, 0, 0, 0x32, 0, arg0);
    }
}

/* was func_15173298 */
void warp_player_to_entry(u8 *arg0, s32 arg1) {
    u8 *t;
    obj_place_at_start(arg0, arg1, 1);
    *(u16 *)(arg0 + 0x2F8) &= 0xFFEF;
    if (D_800BE9B4 == 0) {
        t = *(u8 **)(arg0 + 0x31C);
        if (t != NULL) {
            t[0x56] = 3;
        }
    }
}

s32 game_request_transition(s32, s8, s32, s32, s32);
s32 screen_fade_is_done(s32);

/* was func_15172D80 */
void warp_request_update(s32 arg0) {
    if (D_800DD6E0[arg0] != -1) {
        if (D_800CC2D0[arg0].health == 0) {
            D_800DD6E0[arg0] = -1;
            screen_fade_start(0, 0, 0, 0x32, 0, arg0);
        }
        if (screen_fade_is_done(arg0) != 0) {
            if (D_800BE9F0 != D_800DD6E0[arg0]) {
                game_request_transition(1, D_800DD6E0[arg0], 0, 0, 0);
                return;
            }
            warp_request_cancel(arg0);
            warp_player_to_entry((u8 *)&D_800CC2D0[arg0], (&D_800DD2C0)[arg0]);
        }
    }
}

/* was func_151733EC */
void warp_request_start(struct127 *arg0, s32 arg1, s32 arg2) {
    s32 temp_v1;

    temp_v1 = arg0->unk127;
    if ((arg0->health != 0) && ((arg0->unk31C == NULL) || ((s8) arg0->unk31C->pad17[0xC] <= 0))) {
        if (arg0->camera != NULL) {
            if (D_800DD6E0[temp_v1] == -1) {
                screen_fade_start(0, 0, 0, 0xA, 1, (s32) temp_v1);
                arg0->unk2F8 |= 0x10;
                D_800DD6E0[temp_v1] = (s8) arg1;
                (&D_800DD2C0)[temp_v1] = (u8) arg2;
            }
        } else if (arg1 == D_800BE9F0) {
            warp_player_to_entry((u8 *) arg0, arg2);
        }
    }
}
