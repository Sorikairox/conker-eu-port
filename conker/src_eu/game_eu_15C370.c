#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
Gfx *func_1501A680(Gfx *arg0);
extern s16 D_80083336;

/* camera_read_depth_row: display list that copies one z-buffer row into the camera's depth-row buffer. With
 * w = D_800BE620 (screen width): it loads row +0x8BA (u16) of the z-buffer D_800BEDE4 as a 16-bit texture
 * (w texels, line (w * 2 + 7) / 8, dxt (0x7FF + n) / n with n = max(1, w * 2 / 8)), sets the colour image to
 * the camera's buffer +0x8BC (w wide), scissor w x 1, and draws a w x 1 copy-mode rectangle. Then it restores
 * the frame state (func_1501A680, func_1501A490 with player D_80083336) and the other modes. free_camera_scan_depth
 * (func_1512B728) decodes the copied row. Called by func_1510BF50 when the camera's depth scan is on. */
Gfx *func_1512EB60(Gfx *gdl, struct108 *cam) {
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
    gdl->words.w1 = D_800BEDE4 + (*(u16 *)(p + 0x8BA) * D_800BE620) * 2;
    gdl++;
    gdl->words.w0 = 0xF5100000; /* tile 7 */
    gdl->words.w1 = 0x07000000;
    gdl++;
    gdl->words.w0 = 0xE6000000; /* load sync */
    gdl->words.w1 = 0;
    gdl++;
    lrs = D_800BE620 - 1;
    if (lrs >= 0x7FF) {
        lrs = 0x7FF;
    }
    n = (D_800BE620 * 2) / 8;
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
    gdl->words.w0 = 0xF5100000 | ((((D_800BE620 * 2 + 7) >> 3) & 0x1FF) << 9);
    gdl++;
    gdl->words.w0 = 0xF2000000; /* tile size w x 1 */
    gdl->words.w1 = (((D_800BE620 - 1) << 2) & 0xFFF) << 12;
    gdl++;
    gdl->words.w0 = 0xFF100000 | ((D_800BE620 - 1) & 0xFFF); /* colour image: the camera's row buffer */
    gdl->words.w1 = *(s32 *)(p + 0x8BC);
    gdl++;
    gdl->words.w0 = 0xED000000; /* scissor */
    gdl->words.w1 = ((((s32)((f32)D_800BE620 * 4.0f)) & 0xFFF) << 12) | 4;
    gdl++;
    gdl->words.w1 = 0; /* texture rectangle w x 1 */
    gdl->words.w0 = 0xE4000004 | (((D_800BE620 << 2) & 0xFFF) << 12);
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
    gdl = func_1501A680(gdl);
    gdl = (Gfx *)func_1501A490((s32)gdl, D_80083336, 0, 0, 0, 0);
    gdl->words.w0 = 0xEF082C3F;
    gdl->words.w1 = 0x00552230;
    gdl++;
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15C370/func_1512EB60.s")
#endif
