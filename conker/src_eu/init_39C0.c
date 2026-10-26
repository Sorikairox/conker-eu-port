#include <ultra64.h>

#include "functions.h"
#include "variables.h"

void framebuffer_fill_color(s32 arg0, s32 arg1, s32 arg2);


/* was func_100039C0 */
void video_init_screen(void) {
    g_framebuffer_width = 292; // screen width px
    g_framebuffer_height = 216; // screen height px
    g_text_scale_x_alias = (f32) g_framebuffer_width / 292.0f;
    g_text_scale_y_alias = (f32) g_framebuffer_height / 216.0f;
    g_zbuffer_alias = allocate_memory(g_framebuffer_width * g_framebuffer_height * 2, 255, 3, 0);
    framebuffer_fill_color(0, 0, 0);
    screen_setup_viewports(g_framebuffer_width, g_framebuffer_height);
    // EU: the VI mode is no longer set here
}

/* was func_10003ACC */
void framebuffer_fill_color(s32 arg0, s32 arg1, s32 arg2) {
    s16 *var_v1_2;
    s16 temp_t8;
    s32 temp_a1;
    s32 temp_t0;
    s32 var_t2;
    s32 var_v1;
    u8 *var_v1_3;

    var_v1 = (*(s32 *)((u8 *)g_framebuffers + 0));
    var_t2 = 0;
    temp_t0 = (s32) (g_framebuffer_width * g_framebuffer_height * 2) >> 1;
    if (var_v1 != 0) {
        if (temp_t0 > 0) {
            do {
                var_t2 += 1;
                var_v1 += 2;
                (*(s16 *)((u8 *)var_v1 + -2)) = (s16) (((arg0 << 8) & 0xF800) | ((arg1 * 8) & 0x7C0) | ((arg2 >> 2) & 0x3E) | 1);
            } while (var_t2 < temp_t0);
            var_t2 = 0;
        }
        if (temp_t0 > 0) {
            temp_t8 = ((arg0 << 8) & 0xF800) | ((arg1 * 8) & 0x7C0) | ((arg2 >> 2) & 0x3E) | 1;
            temp_a1 = temp_t0 & 3;
            if (temp_a1 != 0) {
                var_v1_2 = g_framebuffers[1] + (0 * 2);
                do {
                    var_t2 += 1;
                    *var_v1_2 = temp_t8;
                    var_v1_2 += 2;
                } while (temp_a1 != var_t2);
                if (var_t2 != temp_t0) {
                    goto block_10;
                }
            } else {
block_10:
                var_v1_3 = g_framebuffers[1] + (var_t2 * 2);
                do {
                    var_t2 += 4;
                    (*(s16 *)((u8 *)var_v1_3 + 2)) = temp_t8;
                    (*(s16 *)((u8 *)var_v1_3 + 4)) = temp_t8;
                    (*(s16 *)((u8 *)var_v1_3 + 6)) = temp_t8;
                    var_v1_3 += 8;
                    (*(s16 *)((u8 *)var_v1_3 + -8)) = temp_t8;
                } while (var_t2 != temp_t0);
            }
        }
    }
}
// EU only
extern s32 g_vi_mode; /* was D_8002AF20 */

/* was func_10003C10 */
void vi_mode_set_window(s32 arg0, s32 arg1, f32 arg2, f32 arg3) {
    s32 temp_a2;
    s32 temp_f8;
    s32 temp_t6;
    s32 temp_v0;
    s32 var_t0;
    s32 var_v1;
    u32 temp_t2;

    if (g_eeprom_writes_disabled == 0) {
        temp_v0 = arg1 + 0x3F;
        temp_a2 = arg0 + 0x8C;
        temp_f8 = (s32) (517.0f * arg3);
        var_t0 = (s32) (585.0f * arg2);
        var_v1 = temp_f8;
        if ((arg0 + var_t0 + 0x8C) >= 0x31B) {
            var_t0 = 0x31A - temp_a2;
        }
        if ((temp_v0 + temp_f8) >= 0x272) {
            var_v1 = 0x271 - temp_v0;
        }
        (*(s32 *)((u8 *)(&g_vi_mode) + 0x1C)) = (s32) ((temp_a2 << 0x10) | (temp_a2 + var_t0));
        temp_t6 = (temp_v0 << 0x10) | (temp_v0 + var_v1);
        (*(u32 *)((u8 *)(&g_vi_mode) + 0x20)) = (u32) (512.0f - (f32) (var_t0 - 0x249));
        (*(s32 *)((u8 *)(&g_vi_mode) + 0x30)) = temp_t6;
        (*(s32 *)((u8 *)(&g_vi_mode) + 0x44)) = temp_t6;
        temp_t2 = (u32) (1024.0f - ((f32) (var_v1 - 0x1AB) * 1.95f));
        (*(u32 *)((u8 *)(&g_vi_mode) + 0x2C)) = temp_t2;
        (*(u32 *)((u8 *)(&g_vi_mode) + 0x40)) = temp_t2;
    }
}