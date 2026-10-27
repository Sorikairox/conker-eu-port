#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_151D6440 */
u8 *fb_ghost_copy_draw(u8 *gdl, s32 src_image, s32 unused_x, s32 unused_mode) {
    u32 saved_height;
    s32 saved_band_rows;
    u32 saved_row_end;
    s32 col_last_fx;
    s32 row_last_fx;
    s32 col0_fx;
    s32 col_last;
    s32 settile_w0;
    s32 row0_fx;
    s32 band_rows;
    s32 band_cols;
    s32 height;
    u32 col0;
    u32 row_end;
    u32 col_end;
    u32 row0;
    u8 *cmd1;
    u8 *cmd10;
    u8 *cmd11;
    u8 *cmd12;
    u8 *cmd13;
    u8 *cmd14;
    u8 *cmd2;
    u8 *cmd3;
    u8 *cmd4;
    u8 *cmd5;
    u8 *cmd6;
    u8 *cmd7;
    u8 *cmd8;
    u8 *cmd9;
    u8 *cmd;

    height = g_framebuffer_height;
    (*(s32 *)((u8 *)gdl + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)gdl + 4)) = 0;
    cmd1 = gdl + 8;
    (*(s32 *)((u8 *)cmd1 + 0)) = 0xFCFFFFFF;
    (*(s32 *)((u8 *)cmd1 + 4)) = 0xFFFCF279;
    cmd2 = cmd1 + 8;
    (*(s32 *)((u8 *)cmd2 + 0)) = 0xEF000CFF;
    (*(s32 *)((u8 *)cmd2 + 4)) = 0x0F0A4000;
    cmd3 = cmd2 + 8;
    (*(s32 *)((u8 *)cmd3 + 0)) = 0xD9000000;
    (*(s32 *)((u8 *)cmd3 + 4)) = 0;
    cmd4 = cmd3 + 8;
    (*(s32 *)((u8 *)cmd4 + 4)) = -1;
    (*(s32 *)((u8 *)cmd4 + 0)) = 0xD7000002;
    cmd = cmd4 + 8;
    band_rows = 0x10;
    row0 = 0;
    if (height != 0) {
        do {
            row_end = row0 + band_rows;
            col0 = 0;
            band_cols = 0x80;
            if ((u32) height < row_end) {
                band_rows = height - row0;
                row_end = row0 + band_rows;
            }
            if (g_framebuffer_width != 0) {
                row0_fx = (row0 * 4) & 0xFFF;
                row_last_fx = ((row_end - 1) * 4) & 0xFFF;
                saved_band_rows = band_rows;
                saved_height = (u32) height;
                saved_row_end = row_end;
                do {
                    col_end = col0 + band_cols;
                    if ((u32) g_framebuffer_width < col_end) {
                        band_cols = g_framebuffer_width - col0;
                        col_end = col0 + band_cols;
                    }
                    (*(s32 *)((u8 *)cmd + 0)) = (s32) (((g_framebuffer_width - 1) & 0xFFF) | 0xFD100000);
                    cmd5 = cmd + 8;
                    (*(s32 *)((u8 *)cmd + 4)) = src_image;
                    col_last = col_end - 1;
                    settile_w0 = ((((u32) (((col_last - col0) * 2) + 9) >> 3) & 0x1FF) << 9) | 0xF5100000;
                    (*(s32 *)((u8 *)cmd5 + 0)) = settile_w0;
                    cmd6 = cmd5 + 8;
                    (*(s32 *)((u8 *)cmd5 + 4)) = 0x07000000;
                    (*(s32 *)((u8 *)cmd6 + 0)) = 0xE6000000;
                    (*(s32 *)((u8 *)cmd6 + 4)) = 0;
                    cmd7 = cmd6 + 8;
                    col0_fx = ((col0 * 4) & 0xFFF) << 0xC;
                    col_last_fx = ((col_last * 4) & 0xFFF) << 0xC;
                    (*(s32 *)((u8 *)cmd7 + 0)) = (s32) (col0_fx | 0xF4000000 | row0_fx);
                    (*(s32 *)((u8 *)cmd7 + 4)) = (s32) (col_last_fx | 0x07000000 | row_last_fx);
                    cmd8 = cmd7 + 8;
                    (*(s32 *)((u8 *)cmd8 + 0)) = 0xE7000000;
                    (*(s32 *)((u8 *)cmd8 + 4)) = 0;
                    cmd9 = cmd8 + 8;
                    (*(s32 *)((u8 *)cmd9 + 0)) = settile_w0;
                    (*(s32 *)((u8 *)cmd9 + 4)) = 0;
                    cmd10 = cmd9 + 8;
                    (*(s32 *)((u8 *)cmd10 + 4)) = (s32) (col_last_fx | row_last_fx);
                    (*(s32 *)((u8 *)cmd10 + 0)) = (s32) (col0_fx | 0xF2000000 | row0_fx);
                    cmd11 = cmd10 + 8;
                    (*(s32 *)((u8 *)cmd11 + 4)) = (s32) (col0_fx | row0_fx);
                    (*(s32 *)((u8 *)cmd11 + 0)) = (s32) ((((col_end * 4) & 0xFFF) << 0xC) | 0xE4000000 | ((row_end * 4) & 0xFFF));
                    cmd12 = cmd11 + 8;
                    (*(s32 *)((u8 *)cmd12 + 0)) = 0xE1000000;
                    (*(s32 *)((u8 *)cmd12 + 4)) = (s32) ((col0 << 0x15) | ((row0 << 5) & 0xFFFF));
                    cmd13 = cmd12 + 8;
                    (*(s32 *)((u8 *)cmd13 + 0)) = 0xF1000000;
                    (*(s32 *)((u8 *)cmd13 + 4)) = 0x04000400;
                    cmd14 = cmd13 + 8;
                    (*(s32 *)((u8 *)cmd14 + 0)) = 0xE7000000;
                    (*(s32 *)((u8 *)cmd14 + 4)) = 0;
                    cmd = cmd14 + 8;
                    col0 = col_end;
                } while (col_end < (u32) g_framebuffer_width);
                row_end = saved_row_end;
                band_rows = saved_band_rows;
                height = (s32) saved_height;
            }
            row0 = row_end;
        } while (row_end < (u32) height);
    }
    (*(s32 *)((u8 *)cmd + 0)) = 0xEF080C3F;
    (*(s32 *)((u8 *)cmd + 4)) = 0x0F0A4000;
    return cmd + 8;
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
u8 *fb_ghost_image_draw(u8 *gdl, s32 image, s32 right_trim, s32 alpha) {
    s32 height;
    s32 strip_addr;
    u32 next_row;
    u32 block_lrs;
    u32 row_words;
    u32 row_bytes;
    u32 dxt_den;
    u32 load_lrs;
    u32 dxt_num;
    u32 row;
    u8 *cmd1;
    u8 *cmd10;
    u8 *cmd11;
    u8 *cmd12;
    u8 *cmd13;
    u8 *cmd14;
    u8 *cmd2;
    u8 *cmd3;
    u8 *cmd4;
    u8 *cmd5;
    u8 *cmd6;
    u8 *cmd7;
    u8 *cmd8;
    u8 *cmd9;
    u8 *cmd;

    strip_addr = image;
    (*(s32 *)((u8 *)gdl + 0)) = 0xFA000000;
    (*(s32 *)((u8 *)gdl + 4)) = (s32) ((alpha & 0xFF) | ~0xFF);
    cmd1 = gdl + 8;
    (*(s32 *)((u8 *)cmd1 + 4)) = -0x805;
    (*(s32 *)((u8 *)cmd1 + 0)) = 0xFC11FE23;
    cmd2 = cmd1 + 8;
    (*(s32 *)((u8 *)cmd2 + 0)) = 0xEF000CFF;
    (*(s32 *)((u8 *)cmd2 + 4)) = 0x504340;
    cmd3 = cmd2 + 8;
    (*(s32 *)((u8 *)cmd3 + 0)) = 0xD9000000;
    (*(s32 *)((u8 *)cmd3 + 4)) = 0;
    cmd4 = cmd3 + 8;
    (*(s32 *)((u8 *)cmd4 + 4)) = -1;
    (*(s32 *)((u8 *)cmd4 + 0)) = 0xD7000002;
    cmd = cmd4 + 8;
    row = 0;
    height = g_framebuffer_height;
    if (g_framebuffer_height != 0) {
        row_bytes = g_framebuffer_width * 2;
        block_lrs = (g_framebuffer_width * 4) - 1;
        row_words = row_bytes >> 3;
        do {
#ifdef PORT
            /* P335: the N64 adds 0x80000000 to turn the KSEG0 image pointer into a physical address for the RDP. Here
             * the image is a wasm pointer and the sum named some other memory (the ghost read garbage); the port's
             * display-list addresses take wasm pointers as they are. */
            (*(s32 *)((u8 *)cmd + 4)) = (s32) strip_addr;
#else
            (*(s32 *)((u8 *)cmd + 4)) = (s32) (strip_addr + 0x80000000);
#endif
            (*(s32 *)((u8 *)cmd + 0)) = 0xFD100000;
            cmd5 = cmd + 8;
            (*(s32 *)((u8 *)cmd5 + 0)) = 0xF5100000;
            (*(s32 *)((u8 *)cmd5 + 4)) = 0x07000000;
            cmd6 = cmd5 + 8;
            (*(s32 *)((u8 *)cmd6 + 0)) = 0xE6000000;
            (*(s32 *)((u8 *)cmd6 + 4)) = 0;
            cmd7 = cmd6 + 8;
            (*(s32 *)((u8 *)cmd7 + 0)) = 0xF3000000;
            cmd8 = cmd7 + 8;
            if (block_lrs < 0x7FFU) {
                load_lrs = block_lrs;
            } else {
                load_lrs = 0x7FF;
            }
            if (row_words == 0) {
                dxt_num = 1;
            } else {
                dxt_num = row_words;
            }
            if (row_words == 0) {
                dxt_den = 1;
            } else {
                dxt_den = row_words;
            }
            (*(s32 *)((u8 *)cmd7 + 4)) = (s32) ((((u32) (dxt_num + 0x7FF) / dxt_den) & 0xFFF) | 0x07000000 | ((load_lrs & 0xFFF) << 0xC));
            cmd9 = cmd8 + 8;
            (*(s32 *)((u8 *)cmd8 + 0)) = 0xE7000000;
            (*(s32 *)((u8 *)cmd8 + 4)) = 0;
            (*(s32 *)((u8 *)cmd9 + 0)) = (s32) (((((u32) (row_bytes + 7) >> 3) & 0x1FF) << 9) | 0xF5100000);
            (*(s32 *)((u8 *)cmd9 + 4)) = 0;
            cmd10 = cmd9 + 8;
            (*(s32 *)((u8 *)cmd10 + 0)) = 0xF2000000;
            (*(s32 *)((u8 *)cmd10 + 4)) = (s32) (((((g_framebuffer_width - 1) * 4) & 0xFFF) << 0xC) | 0xC);
            cmd11 = cmd10 + 8;
            next_row = row + 4;
            (*(s32 *)((u8 *)cmd11 + 0)) = (s32) (((((g_framebuffer_width - right_trim) * 4) & 0xFFF) << 0xC) | 0xE4000000 | ((next_row * 4) & 0xFFF));
            (*(s32 *)((u8 *)cmd11 + 4)) = (s32) ((row * 4) & 0xFFF);
            cmd12 = cmd11 + 8;
            (*(s32 *)((u8 *)cmd12 + 0)) = 0xE1000000;
            (*(s32 *)((u8 *)cmd12 + 4)) = 0;
            cmd13 = cmd12 + 8;
            (*(s32 *)((u8 *)cmd13 + 0)) = 0xF1000000;
            (*(s32 *)((u8 *)cmd13 + 4)) = 0x04000400;
            cmd14 = cmd13 + 8;
            (*(s32 *)((u8 *)cmd14 + 0)) = 0xE7000000;
            (*(s32 *)((u8 *)cmd14 + 4)) = 0;
            cmd = cmd14 + 8;
            row = next_row;
            strip_addr += g_framebuffer_width * 8;
        } while (next_row < (u32) height);
    }
    return cmd;
}
/* fb_ghost_set_mode: the frame-blend ("ghost" / motion blur) effect. alpha 0 = off; pass 2 = blend inside the player
 * scene (after the sky), 1 = over the whole frame, 0 = off. While on, fb_ghost_render draws the previous frame's
 * copy (g_fb_ghost_image) over the new frame with this alpha, then copies the new frame into it. Called by scene
 * track events (scene_event_run_c event 0x76, e.g. Conker's hangover wake-up on level 0x29: alpha 210, pass 1) and by the
 * camera cut fade (alpha 210, pass 2). Skipped on level 6 without the Expansion Pak.
 * PORT option PORT_OPT_NO_DRUNK_FX (P331): every request becomes "off", so the effect never starts. */
/* was func_151D6CA0 */
void fb_ghost_set_mode(s32 alpha /* was arg0 */, s32 pass /* was arg1 */) {
    if (g_level_id == 6 && g_mem_expansion_pak == 0) {
        return;
    }
#ifdef PORT
    if (port_option(PORT_OPT_NO_DRUNK_FX)) {
        pass = 0;
    }
#endif
    if (pass == 0) {
        alpha = 0;
    }
    g_fb_ghost_alpha = alpha;
    if (alpha != 0) {
        g_fb_ghost_pass = pass;
    } else {
        g_fb_ghost_pass = 0;
    }
    if (alpha == 0 && g_fb_ghost_image != 0) {
        heap_set_block_tag((s32 *)g_fb_ghost_image, 3);
        g_fb_ghost_image = 0;
    }
}

s32 allocate_memory(s32, s32, s32, s32);
u8 *render_set_color_image(u8 *);
u8 *fb_ghost_copy_draw(u8 *, s32, s32, s32);
u8 *fb_ghost_image_draw(u8 *, s32, s32, s32);

/* was func_151D6D28 */
u8 *fb_ghost_render(u8 *gdl) {
    s32 new_image;
    u8 *cmd_after_scissor;
    u8 *cmd_after_copy;
    u8 *cmd;

    cmd = gdl;
    if (((g_fb_ghost_alpha == 0) && (g_level_id != 0x32) && (g_level_id != 0x33)) || (g_game_paused != 0)) {

    } else if (g_fb_ghost_alpha != 0) {
        (*(s32 *)((u8 *)cmd + 0)) = 0xE7000000;
        (*(s32 *)((u8 *)cmd + 4)) = 0;
        cmd += 8;
        if (g_fb_ghost_image != 0) {
            cmd = fb_ghost_image_draw(cmd, g_fb_ghost_image, 0, g_fb_ghost_alpha);
            goto block_10;
        }
        new_image = allocate_memory(g_framebuffer_width * g_framebuffer_height * 2, 1, 3, 1);
        g_fb_ghost_image = new_image;
        if (new_image == 0) {

        } else {
block_10:
            (*(s32 *)((u8 *)cmd + 0)) = (s32) (((g_framebuffer_width - 1) & 0xFFF) | 0xFF100000);
            cmd_after_scissor = cmd + 8;
            (*(s32 *)((u8 *)cmd + 4)) = (s32) g_fb_ghost_image;
            (*(s32 *)((u8 *)cmd_after_scissor + 0)) = 0xED000000;
            (*(s32 *)((u8 *)cmd_after_scissor + 4)) = (s32) ((((s32) ((f32) g_framebuffer_width * 4.0f) & 0xFFF) << 0xC) | ((s32) ((f32) g_framebuffer_height * 4.0f) & 0xFFF));
            cmd_after_copy = fb_ghost_copy_draw(cmd_after_scissor + 8, g_framebuffers[g_dl_buf_index], 0, 4);
            (*(s32 *)((u8 *)cmd_after_copy + 0)) = 0xEF082C3F;
            (*(s32 *)((u8 *)cmd_after_copy + 4)) = 0x552230;
            (*(s32 *)((u8 *)cmd_after_copy + 8)) = 0xD9FFFFFF;
            (*(s32 *)((u8 *)cmd_after_copy + 0xC)) = 0x220405;
            cmd = render_set_color_image(cmd_after_copy + 0x10);
        }
    }
    return cmd;
}