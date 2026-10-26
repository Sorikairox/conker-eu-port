#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_151046F0 */
void camera_cut_fade_spawn(s32 arg0, s32 arg1, s32 arg2) {
    u8 *temp_v0;

    temp_v0 = node_alloc(0x64, 0, 0x20, 0, 0xFFU, 1U);
    if (temp_v0 != NULL) {
        (*(s16 *)((u8 *)temp_v0 + 0x18)) = 0xC;
        (*(s8 *)((u8 *)temp_v0 + 0x1A)) = 0;
        (*(s8 *)((u8 *)temp_v0 + 0x1B)) = 0;
        (*(s32 *)((u8 *)temp_v0 + 0x10)) = arg1;
        (*(s32 *)((u8 *)temp_v0 + 0x14)) = arg2;
        (*(s8 *)((u8 *)temp_v0 + 0x1C)) = (s8) arg0;
    }
}

extern s8 g_slowmo_divisor; /* was D_800BEE2C */

/* was func_15104764 */
void camera_cut_fade_update(struct102 *arg0) {
    u8 *sp34;
    u8 *sp30;
    u8 *sp28;
    s32 sp24;
    s32 temp_v0_3;
    s32 temp_v0_5;
    s32 var_a0;
    u16 temp_v0_2;
    u16 temp_v0_4;
    u8 temp_v0;
    u8 temp_v1;

    temp_v0 = arg0->pad1A[0];
    switch (temp_v0) {                              /* irregular */
    case 0:
        temp_v1 = (*(u8 *)((u8 *)arg0 + 0x1C));
        var_a0 = 0;
        if (temp_v1 == 0) {
            if ((*(f32 *)((u8 *)((*(u8 **)((u8 *)((*(u8 **)((u8 *)arg0 + 0x10))) + 0x2D0))) + 8)) >= 19.0f) {
                goto block_11;
            }
        } else if (temp_v1 == 1) {
            temp_v0_2 = (*(u16 *)((u8 *)arg0 + 0x18));
            if (D_800BE9E4 < (s32) temp_v0_2) {
                (*(u16 *)((u8 *)arg0 + 0x18)) = (u16) (temp_v0_2 - D_800BE9E4);
            } else {
block_11:
                var_a0 = 1;
            }
        }
        if (var_a0 != 0) {
            sp34 = (*(u8 **)((u8 *)arg0 + 0x14));
            sp30 = (*(u8 **)((u8 *)arg0 + 0x10));
            arg0->pad1A[0] = 1;
            g_slowmo_divisor = 1;
            n_sndp_stop_all();
            sound_play_2d(0x5B2, 0x7FFFU, 0U, 0, 0U);
            sound_play_2d(0x5B2, 0x7FFFU, 0x7FU, -0x64, 0U);
            sound_play_2d(0x5B2, 0x7FFFU, 0U, 0, 0U);
            sound_play_2d(0x5B2, 0x7FFFU, 0x7FU, -0x64, 0U);
            fb_ghost_set_mode(0xD2, 2);
            camera_set_followed_obj((*(u8 **)((u8 *)sp30 + 0x318)), (*(u8 *)((u8 *)sp34 + 0x13F)));
            (*(f32 *)((u8 *)((*(u8 **)((u8 *)sp30 + 0x318))) + 0x674)) = 0.0f;
            return;
        }
        return;
    case 1:
        temp_v0_3 = arg0->pad1A[1] + (D_800BEA08 * 0xA);
        if (temp_v0_3 >= 0xFF) {
            arg0->pad1A[1] = 0xFF;
            arg0->pad1A[0] = 2;
            (*(u16 *)((u8 *)arg0 + 0x18)) = 0x96U;
            return;
        }
        arg0->pad1A[1] = (u8) temp_v0_3;
        return;
    case 2:
        temp_v0_4 = (*(u16 *)((u8 *)arg0 + 0x18));
        if (D_800BEA08 < (s32) temp_v0_4) {
            (*(u16 *)((u8 *)arg0 + 0x18)) = (u16) (temp_v0_4 - D_800BEA08);
            return;
        }
        g_slowmo_divisor = 0;
        sp28 = (*(u8 **)((u8 *)arg0 + 0x10));
        music_set_all_paused(0, arg0);
        camera_set_followed_obj((*(u8 **)((u8 *)sp28 + 0x318)), (*(u8 *)((u8 *)sp28 + 0x13F)));
        (*(f32 *)((u8 *)((*(u8 **)((u8 *)sp28 + 0x318))) + 0x674)) = 0.0f;
        arg0->pad1A[0] = 3;
        return;
    case 3:
        temp_v0_5 = arg0->pad1A[1] - (D_800BEA08 * 0xA);
        if (temp_v0_5 <= 0) {
            node_destroy(arg0);
            fb_ghost_set_mode(0, 0);
            return;
        }
        sp24 = temp_v0_5;
        fb_ghost_set_mode((s32) (temp_v0_5 * 0xD2) >> 8, 2, arg0);
        arg0->pad1A[1] = (u8) temp_v0_5;
        break;
    }
}
Gfx *screen_view_fill_colour(Gfx *gfx, s32 a, s32 r, s32 g, s32 b, s32 i);

// obj_fog_alpha_gfx: with i == 0 and a non-zero alpha byte at obj +0x1B, appends screen_view_fill_colour's colour command
// (alpha * 63 / 256, colour 0, 0, 0, index 0) to gfx; returns the new display list end (gfx unchanged otherwise).
/* was func_15104A0C */
Gfx *obj_fog_alpha_gfx(Gfx *gfx, u8 *obj, s16 i) {
    if (i == 0 && obj[0x1B] != 0) {
        return screen_view_fill_colour(gfx, (obj[0x1B] * 63) >> 8, 0, 0, 0, i);
    }
    return gfx;
}

/* was func_151044F4 */
s32 held_obj_byte7d_get(void) {
    u8 *temp_v1 = g_obj0_state;
    s32 ret = 0;

    if (temp_v1 != NULL) {
        return temp_v1[0x7D];
    }
    return ret;
}
