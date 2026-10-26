#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 D_800A0880;
extern f32 D_800A0884;
void light_ctrl_broadcast(u8, u8, s32);

/* was func_150C78E0 */
s32 light_flicker_update(u8 *arg0, u8 *arg1) {
    f32 temp_f0;
    f32 var_f0;
    f32 var_f16;
    s32 temp_t1;
    s32 temp_v1;

    temp_v1 = (*(s32 *)((u8 *)arg0 + 0x38));
    temp_f0 = (f32) (*(s32 *)((u8 *)arg0 + 0x3C)) / 255.0f;
    if (temp_v1 == 0) {
        (*(u8 *)((u8 *)arg0 + 0x13)) = 0xCU;
        if ((*(s32 *)((u8 *)arg1 + 0x2E4)) != 0) {
            light_ctrl_broadcast(0x11, 0x41, 0);
            (*(s32 *)((u8 *)arg1 + 0x2E4)) = 0;
        }
    } else {
        if (temp_v1 < 0x32) {
            temp_t1 = random_int() & 1;
            var_f16 = (f32) temp_t1;
            if (temp_t1 < 0) {
                var_f16 += 4294967296.0f;
            }
            var_f0 = var_f16 * (((f32) (*(s32 *)((u8 *)arg0 + 0x38)) / 50.0f) * 0.25f);
        } else if (temp_v1 < 0xFA) {
            var_f0 = (((f32) (temp_v1 - 0x32) / 200.0f) * 0.75f) + 0.25f;
        } else if ((f32) temp_v1 < D_800A0880) {
            if ((1.0f - 0.25f) < temp_f0) {
                var_f0 = 0.25f;
            } else {
                var_f0 = temp_f0 + 0.25f;
            }
        } else {
            var_f0 = temp_f0 + ((1.0f - temp_f0) * D_800A0884);
        }
        if (D_800BE9E4 >= (*(s32 *)((u8 *)arg0 + 0x38))) {
            (*(s32 *)((u8 *)arg0 + 0x38)) = 0;
        } else {
            (*(s32 *)((u8 *)arg0 + 0x38)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x38)) - D_800BE9E4);
        }
        (*(s32 *)((u8 *)arg0 + 0x3C)) = (s32) (var_f0 * 255.0f);
        if (var_f0 != 0.0f) {
            if ((*(u8 *)((u8 *)arg0 + 0x13)) != 2) {
                sound_play_2d((random_int() & 7) + 0x44B, 0x7D00U, 0x40U, 0, 0U);
            }
            (*(u8 *)((u8 *)arg0 + 0x13)) = 2U;
            if ((*(s32 *)((u8 *)arg1 + 0x2E4)) != 1) {
                light_ctrl_broadcast(0x11, 0x40, 0);
                (*(s32 *)((u8 *)arg1 + 0x2E4)) = 1;
            }
        } else {
            (*(u8 *)((u8 *)arg0 + 0x13)) = 0xCU;
            if ((*(s32 *)((u8 *)arg1 + 0x2E4)) != 0) {
                light_ctrl_broadcast(0x11, 0x41, 0);
                (*(s32 *)((u8 *)arg1 + 0x2E4)) = 0;
            }
        }
    }
    return 0;
}