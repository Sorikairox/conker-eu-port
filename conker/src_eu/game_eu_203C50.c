#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_151D6440 */
u8 *fb_ghost_copy_draw(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u32 sp8C;
    s32 sp84;
    u32 sp34;
    s32 temp_a1;
    s32 temp_s1;
    s32 temp_t0;
    s32 temp_t1;
    s32 temp_t2;
    s32 temp_t7;
    s32 var_a1;
    s32 var_s0;
    s32 var_v1;
    u32 var_a2;
    u32 var_a3;
    u32 var_a3_2;
    u32 var_v0;
    u8 *temp_a0;
    u8 *temp_a0_10;
    u8 *temp_a0_11;
    u8 *temp_a0_12;
    u8 *temp_a0_13;
    u8 *temp_a0_14;
    u8 *temp_a0_2;
    u8 *temp_a0_3;
    u8 *temp_a0_4;
    u8 *temp_a0_5;
    u8 *temp_a0_6;
    u8 *temp_a0_7;
    u8 *temp_a0_8;
    u8 *temp_a0_9;
    u8 *var_a0;

    var_v1 = g_framebuffer_height;
    (*(s32 *)((u8 *)arg0 + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)arg0 + 4)) = 0;
    temp_a0 = arg0 + 8;
    (*(s32 *)((u8 *)temp_a0 + 0)) = 0xFCFFFFFF;
    (*(s32 *)((u8 *)temp_a0 + 4)) = 0xFFFCF279;
    temp_a0_2 = temp_a0 + 8;
    (*(s32 *)((u8 *)temp_a0_2 + 0)) = 0xEF000CFF;
    (*(s32 *)((u8 *)temp_a0_2 + 4)) = 0x0F0A4000;
    temp_a0_3 = temp_a0_2 + 8;
    (*(s32 *)((u8 *)temp_a0_3 + 0)) = 0xD9000000;
    (*(s32 *)((u8 *)temp_a0_3 + 4)) = 0;
    temp_a0_4 = temp_a0_3 + 8;
    (*(s32 *)((u8 *)temp_a0_4 + 4)) = -1;
    (*(s32 *)((u8 *)temp_a0_4 + 0)) = 0xD7000002;
    var_a0 = temp_a0_4 + 8;
    var_a1 = 0x10;
    var_v0 = 0;
    if (var_v1 != 0) {
        do {
            var_a3 = var_v0 + var_a1;
            var_a2 = 0;
            var_s0 = 0x80;
            if ((u32) var_v1 < var_a3) {
                var_a1 = var_v1 - var_v0;
                var_a3 = var_v0 + var_a1;
            }
            if (g_framebuffer_width != 0) {
                temp_t7 = (var_v0 * 4) & 0xFFF;
                temp_s1 = ((var_a3 - 1) * 4) & 0xFFF;
                sp84 = var_a1;
                sp8C = (u32) var_v1;
                sp34 = var_a3;
                do {
                    var_a3_2 = var_a2 + var_s0;
                    if ((u32) g_framebuffer_width < var_a3_2) {
                        var_s0 = g_framebuffer_width - var_a2;
                        var_a3_2 = var_a2 + var_s0;
                    }
                    (*(s32 *)((u8 *)var_a0 + 0)) = (s32) (((g_framebuffer_width - 1) & 0xFFF) | 0xFD100000);
                    temp_a0_5 = var_a0 + 8;
                    (*(s32 *)((u8 *)var_a0 + 4)) = arg1;
                    temp_t1 = var_a3_2 - 1;
                    temp_t2 = ((((u32) (((temp_t1 - var_a2) * 2) + 9) >> 3) & 0x1FF) << 9) | 0xF5100000;
                    (*(s32 *)((u8 *)temp_a0_5 + 0)) = temp_t2;
                    temp_a0_6 = temp_a0_5 + 8;
                    (*(s32 *)((u8 *)temp_a0_5 + 4)) = 0x07000000;
                    (*(s32 *)((u8 *)temp_a0_6 + 0)) = 0xE6000000;
                    (*(s32 *)((u8 *)temp_a0_6 + 4)) = 0;
                    temp_a0_7 = temp_a0_6 + 8;
                    temp_t0 = ((var_a2 * 4) & 0xFFF) << 0xC;
                    temp_a1 = ((temp_t1 * 4) & 0xFFF) << 0xC;
                    (*(s32 *)((u8 *)temp_a0_7 + 0)) = (s32) (temp_t0 | 0xF4000000 | temp_t7);
                    (*(s32 *)((u8 *)temp_a0_7 + 4)) = (s32) (temp_a1 | 0x07000000 | temp_s1);
                    temp_a0_8 = temp_a0_7 + 8;
                    (*(s32 *)((u8 *)temp_a0_8 + 0)) = 0xE7000000;
                    (*(s32 *)((u8 *)temp_a0_8 + 4)) = 0;
                    temp_a0_9 = temp_a0_8 + 8;
                    (*(s32 *)((u8 *)temp_a0_9 + 0)) = temp_t2;
                    (*(s32 *)((u8 *)temp_a0_9 + 4)) = 0;
                    temp_a0_10 = temp_a0_9 + 8;
                    (*(s32 *)((u8 *)temp_a0_10 + 4)) = (s32) (temp_a1 | temp_s1);
                    (*(s32 *)((u8 *)temp_a0_10 + 0)) = (s32) (temp_t0 | 0xF2000000 | temp_t7);
                    temp_a0_11 = temp_a0_10 + 8;
                    (*(s32 *)((u8 *)temp_a0_11 + 4)) = (s32) (temp_t0 | temp_t7);
                    (*(s32 *)((u8 *)temp_a0_11 + 0)) = (s32) ((((var_a3_2 * 4) & 0xFFF) << 0xC) | 0xE4000000 | ((var_a3 * 4) & 0xFFF));
                    temp_a0_12 = temp_a0_11 + 8;
                    (*(s32 *)((u8 *)temp_a0_12 + 0)) = 0xE1000000;
                    (*(s32 *)((u8 *)temp_a0_12 + 4)) = (s32) ((var_a2 << 0x15) | ((var_v0 << 5) & 0xFFFF));
                    temp_a0_13 = temp_a0_12 + 8;
                    (*(s32 *)((u8 *)temp_a0_13 + 0)) = 0xF1000000;
                    (*(s32 *)((u8 *)temp_a0_13 + 4)) = 0x04000400;
                    temp_a0_14 = temp_a0_13 + 8;
                    (*(s32 *)((u8 *)temp_a0_14 + 0)) = 0xE7000000;
                    (*(s32 *)((u8 *)temp_a0_14 + 4)) = 0;
                    var_a0 = temp_a0_14 + 8;
                    var_a2 = var_a3_2;
                } while (var_a3_2 < (u32) g_framebuffer_width);
                var_a3 = sp34;
                var_a1 = sp84;
                var_v1 = (s32) sp8C;
            }
            var_v0 = var_a3;
        } while (var_a3 < (u32) var_v1);
    }
    (*(s32 *)((u8 *)var_a0 + 0)) = 0xEF080C3F;
    (*(s32 *)((u8 *)var_a0 + 4)) = 0x0F0A4000;
    return var_a0 + 8;
}
/* was func_151D6760 */
void fb_blur_average(u8 *arg0) {
    s16 temp_t7;
    s32 temp_t3;
    s32 var_a2;
    s32 var_t2;
    u16 temp_t1;
    u16 temp_t4;
    u16 temp_t4_2;
    u16 var_t0;
    u16 var_t1;
    u8 *temp_a3;
    u8 *var_a0;
    u8 *var_a1;

    var_a1 = arg0;
    var_a2 = 0;
    if (g_framebuffer_height > 0) {
        temp_t3 = g_framebuffer_width - 1;
        do {
            temp_a3 = var_a1 + 2;
            var_a0 = temp_a3;
            var_t0 = (*(u16 *)((u8 *)var_a1 + 2));
            var_t1 = (*(u16 *)((u8 *)var_a1 + 4));
            var_t2 = 1;
            if ((temp_t3 >= 2) && ((temp_t4 = var_t0, (((g_framebuffer_width - 2) & 1) == 0)) || (var_t0 = var_t1 & 0xFFFF, var_t1 = (*(u16 *)((u8 *)temp_a3 + 4)), var_t2 = 2, (*(s16 *)((u8 *)temp_a3 + 2)) = (s16) (((((((s32) var_t0 >> 0xB) & 0x1F) + (((s32) temp_t4 >> 0xC) & 0xF) + (((s32) var_t1 >> 0xC) & 0xF)) & 0x3E) << 0xA) | ((((((s32) var_t0 >> 6) & 0x1F) + (((s32) temp_t4 >> 7) & 0xF) + (((s32) var_t1 >> 7) & 0xF)) & 0x3E) << 5) | (((((s32) var_t0 >> 1) & 0x1F) + (((s32) temp_t4 >> 2) & 0xF) + (((s32) var_t1 >> 2) & 0xF)) & 0x3E) | 1), var_a0 = temp_a3 + 2, (temp_t3 != 2)))) {
                do {
                    temp_t1 = (*(u16 *)((u8 *)var_a0 + 4));
                    temp_t7 = ((((((s32) var_t1 >> 0xB) & 0x1F) + (((s32) var_t0 >> 0xC) & 0xF) + (((s32) temp_t1 >> 0xC) & 0xF)) & 0x3E) << 0xA) | ((((((s32) var_t1 >> 6) & 0x1F) + (((s32) var_t0 >> 7) & 0xF) + (((s32) temp_t1 >> 7) & 0xF)) & 0x3E) << 5) | (((((s32) var_t1 >> 1) & 0x1F) + (((s32) var_t0 >> 2) & 0xF) + (((s32) temp_t1 >> 2) & 0xF)) & 0x3E) | 1;
                    temp_t4_2 = var_t1;
                    var_t0 = temp_t1 & 0xFFFF;
                    (*(s16 *)((u8 *)var_a0 + 2)) = temp_t7;
                    var_t1 = (*(u16 *)((u8 *)var_a0 + 6));
                    var_t2 += 2;
                    (*(u16 *)((u8 *)var_a0 + 4)) = (u16) (((((((s32) var_t0 >> 0xB) & 0x1F) + (((s32) temp_t4_2 >> 0xC) & 0xF) + (((s32) var_t1 >> 0xC) & 0xF)) & 0x3E) << 0xA) | ((((((s32) var_t0 >> 6) & 0x1F) + (((s32) temp_t4_2 >> 7) & 0xF) + (((s32) var_t1 >> 7) & 0xF)) & 0x3E) << 5) | (((((s32) var_t0 >> 1) & 0x1F) + (((s32) temp_t4_2 >> 2) & 0xF) + (((s32) var_t1 >> 2) & 0xF)) & 0x3E) | 1);
                    var_a0 += 4;
                } while (var_t2 != temp_t3);
            }
            var_a2 += 1;
            var_a1 += g_framebuffer_width * 2;
        } while (var_a2 != g_framebuffer_height);
    }
}
/* was func_151D69C8 */
u8 *fb_ghost_image_draw(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp34;
    s32 var_t5;
    u32 temp_a2;
    u32 temp_s0;
    u32 temp_t0;
    u32 temp_v1;
    u32 var_a2;
    u32 var_t1;
    u32 var_t2;
    u32 var_t3;
    u8 *temp_a0;
    u8 *temp_a0_10;
    u8 *temp_a0_11;
    u8 *temp_a0_12;
    u8 *temp_a0_13;
    u8 *temp_a0_14;
    u8 *temp_a0_2;
    u8 *temp_a0_3;
    u8 *temp_a0_4;
    u8 *temp_a0_5;
    u8 *temp_a0_6;
    u8 *temp_a0_7;
    u8 *temp_a0_8;
    u8 *temp_a0_9;
    u8 *var_a0;

    var_t5 = arg1;
    (*(s32 *)((u8 *)arg0 + 0)) = 0xFA000000;
    (*(s32 *)((u8 *)arg0 + 4)) = (s32) ((arg3 & 0xFF) | ~0xFF);
    temp_a0 = arg0 + 8;
    (*(s32 *)((u8 *)temp_a0 + 4)) = -0x805;
    (*(s32 *)((u8 *)temp_a0 + 0)) = 0xFC11FE23;
    temp_a0_2 = temp_a0 + 8;
    (*(s32 *)((u8 *)temp_a0_2 + 0)) = 0xEF000CFF;
    (*(s32 *)((u8 *)temp_a0_2 + 4)) = 0x504340;
    temp_a0_3 = temp_a0_2 + 8;
    (*(s32 *)((u8 *)temp_a0_3 + 0)) = 0xD9000000;
    (*(s32 *)((u8 *)temp_a0_3 + 4)) = 0;
    temp_a0_4 = temp_a0_3 + 8;
    (*(s32 *)((u8 *)temp_a0_4 + 4)) = -1;
    (*(s32 *)((u8 *)temp_a0_4 + 0)) = 0xD7000002;
    var_a0 = temp_a0_4 + 8;
    var_t3 = 0;
    sp34 = g_framebuffer_height;
    if (g_framebuffer_height != 0) {
        temp_v1 = g_framebuffer_width * 2;
        temp_s0 = (g_framebuffer_width * 4) - 1;
        temp_t0 = temp_v1 >> 3;
        do {
            (*(s32 *)((u8 *)var_a0 + 4)) = (s32) (var_t5 + 0x80000000);
            (*(s32 *)((u8 *)var_a0 + 0)) = 0xFD100000;
            temp_a0_5 = var_a0 + 8;
            (*(s32 *)((u8 *)temp_a0_5 + 0)) = 0xF5100000;
            (*(s32 *)((u8 *)temp_a0_5 + 4)) = 0x07000000;
            temp_a0_6 = temp_a0_5 + 8;
            (*(s32 *)((u8 *)temp_a0_6 + 0)) = 0xE6000000;
            (*(s32 *)((u8 *)temp_a0_6 + 4)) = 0;
            temp_a0_7 = temp_a0_6 + 8;
            (*(s32 *)((u8 *)temp_a0_7 + 0)) = 0xF3000000;
            temp_a0_8 = temp_a0_7 + 8;
            if (temp_s0 < 0x7FFU) {
                var_t1 = temp_s0;
            } else {
                var_t1 = 0x7FF;
            }
            if (temp_t0 == 0) {
                var_t2 = 1;
            } else {
                var_t2 = temp_t0;
            }
            if (temp_t0 == 0) {
                var_a2 = 1;
            } else {
                var_a2 = temp_t0;
            }
            (*(s32 *)((u8 *)temp_a0_7 + 4)) = (s32) ((((u32) (var_t2 + 0x7FF) / var_a2) & 0xFFF) | 0x07000000 | ((var_t1 & 0xFFF) << 0xC));
            temp_a0_9 = temp_a0_8 + 8;
            (*(s32 *)((u8 *)temp_a0_8 + 0)) = 0xE7000000;
            (*(s32 *)((u8 *)temp_a0_8 + 4)) = 0;
            (*(s32 *)((u8 *)temp_a0_9 + 0)) = (s32) (((((u32) (temp_v1 + 7) >> 3) & 0x1FF) << 9) | 0xF5100000);
            (*(s32 *)((u8 *)temp_a0_9 + 4)) = 0;
            temp_a0_10 = temp_a0_9 + 8;
            (*(s32 *)((u8 *)temp_a0_10 + 0)) = 0xF2000000;
            (*(s32 *)((u8 *)temp_a0_10 + 4)) = (s32) (((((g_framebuffer_width - 1) * 4) & 0xFFF) << 0xC) | 0xC);
            temp_a0_11 = temp_a0_10 + 8;
            temp_a2 = var_t3 + 4;
            (*(s32 *)((u8 *)temp_a0_11 + 0)) = (s32) (((((g_framebuffer_width - arg2) * 4) & 0xFFF) << 0xC) | 0xE4000000 | ((temp_a2 * 4) & 0xFFF));
            (*(s32 *)((u8 *)temp_a0_11 + 4)) = (s32) ((var_t3 * 4) & 0xFFF);
            temp_a0_12 = temp_a0_11 + 8;
            (*(s32 *)((u8 *)temp_a0_12 + 0)) = 0xE1000000;
            (*(s32 *)((u8 *)temp_a0_12 + 4)) = 0;
            temp_a0_13 = temp_a0_12 + 8;
            (*(s32 *)((u8 *)temp_a0_13 + 0)) = 0xF1000000;
            (*(s32 *)((u8 *)temp_a0_13 + 4)) = 0x04000400;
            temp_a0_14 = temp_a0_13 + 8;
            (*(s32 *)((u8 *)temp_a0_14 + 0)) = 0xE7000000;
            (*(s32 *)((u8 *)temp_a0_14 + 4)) = 0;
            var_a0 = temp_a0_14 + 8;
            var_t3 = temp_a2;
            var_t5 += g_framebuffer_width * 8;
        } while (temp_a2 < (u32) sp34);
    }
    return var_a0;
}
/* was func_151D6CA0 */
void fb_ghost_set_mode(s32 arg0, s32 arg1) {
    if (g_level_id == 6 && g_mem_expansion_pak == 0) {
        return;
    }
    if (arg1 == 0) {
        arg0 = 0;
    }
    g_fb_ghost_alpha = arg0;
    if (arg0 != 0) {
        g_fb_ghost_pass = arg1;
    } else {
        g_fb_ghost_pass = 0;
    }
    if (arg0 == 0 && g_fb_ghost_image != 0) {
        heap_set_block_tag((s32 *)g_fb_ghost_image, 3);
        g_fb_ghost_image = 0;
    }
}

s32 allocate_memory(s32, s32, s32, s32);
u8 *render_set_color_image(u8 *);
u8 *fb_ghost_copy_draw(u8 *, s32, s32, s32);
u8 *fb_ghost_image_draw(u8 *, s32, s32, s32);

/* was func_151D6D28 */
u8 *fb_ghost_render(u8 *arg0) {
    s32 temp_v0;
    u8 *temp_s0;
    u8 *temp_v0_2;
    u8 *var_s0;

    var_s0 = arg0;
    if (((g_fb_ghost_alpha == 0) && (g_level_id != 0x32) && (g_level_id != 0x33)) || (g_game_paused != 0)) {

    } else if (g_fb_ghost_alpha != 0) {
        (*(s32 *)((u8 *)var_s0 + 0)) = 0xE7000000;
        (*(s32 *)((u8 *)var_s0 + 4)) = 0;
        var_s0 += 8;
        if (g_fb_ghost_image != 0) {
            var_s0 = fb_ghost_image_draw(var_s0, g_fb_ghost_image, 0, g_fb_ghost_alpha);
            goto block_10;
        }
        temp_v0 = allocate_memory(g_framebuffer_width * g_framebuffer_height * 2, 1, 3, 1);
        g_fb_ghost_image = temp_v0;
        if (temp_v0 == 0) {

        } else {
block_10:
            (*(s32 *)((u8 *)var_s0 + 0)) = (s32) (((g_framebuffer_width - 1) & 0xFFF) | 0xFF100000);
            temp_s0 = var_s0 + 8;
            (*(s32 *)((u8 *)var_s0 + 4)) = (s32) g_fb_ghost_image;
            (*(s32 *)((u8 *)temp_s0 + 0)) = 0xED000000;
            (*(s32 *)((u8 *)temp_s0 + 4)) = (s32) ((((s32) ((f32) g_framebuffer_width * 4.0f) & 0xFFF) << 0xC) | ((s32) ((f32) g_framebuffer_height * 4.0f) & 0xFFF));
            temp_v0_2 = fb_ghost_copy_draw(temp_s0 + 8, g_framebuffers[g_dl_buf_index], 0, 4);
            (*(s32 *)((u8 *)temp_v0_2 + 0)) = 0xEF082C3F;
            (*(s32 *)((u8 *)temp_v0_2 + 4)) = 0x552230;
            (*(s32 *)((u8 *)temp_v0_2 + 8)) = 0xD9FFFFFF;
            (*(s32 *)((u8 *)temp_v0_2 + 0xC)) = 0x220405;
            var_s0 = render_set_color_image(temp_v0_2 + 0x10);
        }
    }
    return var_s0;
}