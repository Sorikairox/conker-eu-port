#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void rain_update(s32);
s32 world_object_sound_play(u8 *, s32, s32, s16, s16, s32);


/* was func_1510AFA0 */
void clock_level_callback(s32 arg0) {
    rain_update(0);
}

extern s32 g_save_stat9; /* was D_800BE804 */

/* was func_1510AFC4 */
void clock_hands_update(u8 *arg0) {
    s32 sp38;
    f32 sp24;
    f32 temp_f2;
    s32 temp_f4;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_t2;
    s32 temp_t6;
    s32 temp_t9;
    s32 temp_v0;
    s32 var_t0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    u32 temp_hi;

    var_v0 = (*(s32 *)((u8 *)arg0 + 0x3C));
    var_v1 = (s32) (var_v0 / 3000) % 60;
    if (((*(s32 *)((u8 *)arg0 + 0x84)) == 0) && (g_save_stat9 != 0)) {
        (*(s32 *)((u8 *)arg0 + 0x84)) = 1;
        temp_hi = (u32) (g_save_stat9 * 0xB4) % 43200U;
        temp_t6 = temp_hi * 0x32;
        var_v0 = temp_t6;
        (*(s32 *)((u8 *)arg0 + 0x3C)) = (s32) temp_hi;
        var_v1 = (s32) (temp_t6 / 3000) % 60;
        (*(s32 *)((u8 *)arg0 + 0x3C)) = temp_t6;
    }
    if (var_v1 < 0) {
        var_v1 += 0x3C;
    }
    temp_t9 = var_v0 + g_frame_ticks;
    (*(s32 *)((u8 *)arg0 + 0x3C)) = temp_t9;
    var_v0_2 = temp_t9;
    if (temp_t9 >= 0x20F580) {
        temp_t2 = var_v0_2 + 0xFFDF0A80;
        (*(s32 *)((u8 *)arg0 + 0x3C)) = temp_t2;
        var_v0_2 = temp_t2;
    }
    temp_lo = var_v0_2 / 50;
    temp_f2 = (f32) (temp_lo / 300) * 2.5f;
    if (temp_f2 > 360.0f) {
        (*(s32 *)((u8 *)arg0 + 0x3C)) = (s32) (var_v0_2 + 0xFFDF0A80);
    }
    var_t0 = (s32) (temp_lo / 60) % 60;
    if (var_t0 < 0) {
        var_t0 += 0x3C;
    }
    if (var_v1 != var_t0) {
        temp_lo_2 = var_t0 / 15;
        if (temp_lo_2 != (var_v1 / 15)) {
            if (!(temp_lo_2 & 3)) {
                temp_f4 = (s32) (temp_f2 / 30.0f);
                (*(s32 *)((u8 *)arg0 + 0x7C)) = temp_f4;
                if (temp_f4 == 0) {
                    (*(s32 *)((u8 *)arg0 + 0x7C)) = 0xC;
                }
            } else {
                (*(s32 *)((u8 *)arg0 + 0x7C)) = 1;
            }
            (*(s32 *)((u8 *)arg0 + 0x80)) = -1;
        }
    }
    temp_v0 = (*(s32 *)((u8 *)arg0 + 0x7C));
    if ((temp_v0 != 0) && (temp_lo != (*(s32 *)((u8 *)arg0 + 0x80)))) {
        (*(s32 *)((u8 *)arg0 + 0x80)) = temp_lo;
        (*(s32 *)((u8 *)arg0 + 0x7C)) = (s32) (temp_v0 - 1);
        sp24 = temp_f2;
        sp38 = var_t0;
        world_object_sound_play(arg0, 0x4CC, 0x7FFF, 0xC8, 0x3E8, 0xC);
    }
    (*(f32 *)((u8 *)arg0 + 0x68)) = 5.0f;
    (*(f32 *)((u8 *)arg0 + 0x108)) = 5.0f;
    (*(f32 *)((u8 *)arg0 + 0xA8)) = (f32) -temp_f2;
    (*(f32 *)((u8 *)arg0 + 8)) = (f32) -((f32) var_t0 * 6.0f);
}
s32 world_object_sound_play(u8 *, s32, s32, s16, s16, s32);

/* was func_1510B34C */
void clock_pendulum_update(u8 *arg0) {
    f32 x;

    *(f32 *)(arg0 + 0x80) += (3.1415927f * g_frame_ticks) / 50.0f;
    x = cosf(*(f32 *)(arg0 + 0x80)) * 10.0f;
    *(f32 *)(arg0 + 0x60) = *(f32 *)(arg0 + 0) - x;
    *(f32 *)(arg0 + 0) = x;
    if (*(s32 *)(arg0 + 0x7C) == 0) {
        if (*(f32 *)(arg0 + 0x80) >= 3.1415927f) {
            *(s32 *)(arg0 + 0x7C) = 1;
            world_object_sound_play(arg0, 0x4CA, 0x2EE0, 0xC8, 0x3E8, 4);
        }
    } else if (*(f32 *)(arg0 + 0x80) >= 6.2831855f) {
        *(s32 *)(arg0 + 0x7C) = 0;
        *(f32 *)(arg0 + 0x80) -= 6.2831855f;
        world_object_sound_play(arg0, 0x4CB, 0x2EE0, 0xC8, 0x3E8, 4);
    }
}
