#include <ultra64.h>
#include "functions.h"
#include "variables.h"


Gfx *render_set_color_image(Gfx *arg0);
extern s16 g_render_scissor_mode; /* was D_80083336 */

/* camera_read_depth_row: display list that copies one z-buffer row into the camera's depth-row buffer. With
 * w = g_framebuffer_width (screen width): it loads row +0x8BA (u16) of the z-buffer g_zbuffer as a 16-bit texture
 * (w texels, line (w * 2 + 7) / 8, dxt (0x7FF + n) / n with n = max(1, w * 2 / 8)), sets the colour image to
 * the camera's buffer +0x8BC (w wide), scissor w x 1, and draws a w x 1 copy-mode rectangle. Then it restores
 * the frame state (render_set_color_image, render_set_scissor with player g_render_scissor_mode) and the other modes. free_camera_scan_depth
 * (freecam_scan_depth) decodes the copied row. Called by player_view_dl_build when the camera's depth scan is on. */
/* was func_1512EB60 */
Gfx *camera_read_depth_row(Gfx *gdl, struct108 *cam) {
    u8 *p = (u8 *)cam;
    s32 lrs;
    s32 n;

    gdl->words.w0 = 0xE7000000; /* pipe sync */
    gdl->words.w1 = 0;
    gdl++;
    gdl->words.w0 = 0xEF202CFF; /* other modes: copy */
    gdl->words.w1 = 0;
    gdl++;
    gdl->words.w0 = 0xFD100000; /* texture image: 16-bit, z-buffer row */
    gdl->words.w1 = g_zbuffer + (*(u16 *)(p + 0x8BA) * g_framebuffer_width) * 2;
    gdl++;
    gdl->words.w0 = 0xF5100000; /* tile 7 */
    gdl->words.w1 = 0x07000000;
    gdl++;
    gdl->words.w0 = 0xE6000000; /* load sync */
    gdl->words.w1 = 0;
    gdl++;
    lrs = g_framebuffer_width - 1;
    if (lrs >= 0x7FF) {
        lrs = 0x7FF;
    }
    n = (g_framebuffer_width * 2) / 8;
    if (n <= 0) {
        n = 1;
    }
    gdl->words.w0 = 0xF3000000; /* load block */
    gdl->words.w1 = 0x07000000 | (((0x7FF + n) / n) & 0xFFF) | ((lrs & 0xFFF) << 12);
    gdl++;
    gdl->words.w0 = 0xE7000000;
    gdl->words.w1 = 0;
    gdl++;
    gdl->words.w1 = 0; /* tile 0, line (w * 2 + 7) / 8 */
    gdl->words.w0 = 0xF5100000 | ((((g_framebuffer_width * 2 + 7) >> 3) & 0x1FF) << 9);
    gdl++;
    gdl->words.w0 = 0xF2000000; /* tile size w x 1 */
    gdl->words.w1 = (((g_framebuffer_width - 1) << 2) & 0xFFF) << 12;
    gdl++;
    gdl->words.w0 = 0xFF100000 | ((g_framebuffer_width - 1) & 0xFFF); /* colour image: the camera's row buffer */
    gdl->words.w1 = *(s32 *)(p + 0x8BC);
    gdl++;
    gdl->words.w0 = 0xED000000; /* scissor */
    gdl->words.w1 = ((((s32)((f32)g_framebuffer_width * 4.0f)) & 0xFFF) << 12) | 4;
    gdl++;
    gdl->words.w1 = 0; /* texture rectangle w x 1 */
    gdl->words.w0 = 0xE4000004 | (((g_framebuffer_width << 2) & 0xFFF) << 12);
    gdl++;
    gdl->words.w0 = 0xE1000000;
    gdl->words.w1 = 0;
    gdl++;
    gdl->words.w0 = 0xF1000000;
    gdl->words.w1 = 0x10000400;
    gdl++;
    gdl->words.w0 = 0xE7000000;
    gdl->words.w1 = 0;
    gdl++;
    gdl = render_set_color_image(gdl);
    gdl = (Gfx *)render_set_scissor((s32)gdl, g_render_scissor_mode, 0, 0, 0, 0);
    gdl->words.w0 = 0xEF082C3F;
    gdl->words.w1 = 0x00552230;
    gdl++;
    return gdl;
}
