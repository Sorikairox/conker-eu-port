#include <ultra64.h>

#include "functions.h"
#include "variables.h"

#include "macros.h"

void func_15000AC0(void) {
    D_800D9E64 = (u8)0;
}

// jump table
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15000AD0.s")
// loops!
#ifdef NON_MATCHING
extern s32 D_800DC26C;    /* triangle table: 3 vertex pointers per triangle (12 bytes) */
extern s32 D_800DC270;    /* per triangle: s16 x min, z min, x max, z max */
extern s32 D_800DC274;    /* per triangle: s16 y min, y max */
extern s32 D_800D3048[];  /* segment table */
extern u8 D_800D3088;     /* 1 while object DLs are scanned: segment addresses lose 0x01000000 */

/* Collision triangle scan of a level DL (ends at G_ENDDL 0xDF): G_VTX (0x01) loads vertex pointers into a 32-entry
 * cache (the loop runs from the first vertex v0 = end - n to n - 1, as the asm does), G_TRI1 (0x05, index bytes
 * 1-3 / 2), G_TRI2 (0x06, 5-bit fields at bits 17 / 9 / 1 of both words) and Rare's 0x1x (four triangles, 5-bit
 * fields) append triangles at D_800DBE38: the 3 vertex pointers and the bounds (x / z in D_800DC270, y in D_800DC274;
 * full range when D_800DBE63 is set). The bounds are recomputed only when cache entry 0 holds a pointer above
 * 0x100000; otherwise the previous triangle's bounds are written again. */
void func_15001460(s32 arg0) {
    s32 verts[35];
    s16 idx[12];
    s16 vmax[3];
    s16 vmin[3];
    s32 i;
    s32 count;
    s32 ntri;
    s32 t;
    s32 c;
    s32 k;
    s32 n;
    s32 start;
    u32 w0;
    u32 w1;
    u32 addr;
    s32 op;
    s16 v;
    s16 *tri;
    s16 *b;
    u32 *cmd;

    if (arg0 == 0) {
        return;
    }
    vmin[0] = vmin[1] = vmin[2] = 0;
    vmax[0] = vmax[1] = vmax[2] = 0;
    i = 0;
    count = D_800DBE38;
    while ((op = ((s8 *) arg0)[i * 8]) != -0x21) {
        cmd = (u32 *) (arg0 + i * 8);
        ntri = 0;
        if ((op >> 4) == 1) {
            w0 = cmd[0];
            w1 = cmd[1];
            idx[0] = (w1 >> 25) & 0x1F;
            idx[1] = (w1 >> 20) & 0x1F;
            idx[2] = (w1 >> 15) & 0x1F;
            idx[3] = (w1 >> 10) & 0x1F;
            idx[4] = (w1 >> 5) & 0x1F;
            idx[5] = w1 & 0x1F;
            idx[6] = (w0 >> 10) & 0x1F;
            idx[7] = (w0 >> 5) & 0x1F;
            idx[8] = w0 & 0x1F;
            idx[9] = (w0 >> 23) & 0x1F;
            idx[10] = (w0 >> 18) & 0x1F;
            idx[11] = ((w1 >> 30) & 3) | ((w0 >> 13) & 0x1C);
            ntri = 4;
        } else if (op == 6) {
            w0 = cmd[0];
            w1 = cmd[1];
            idx[0] = (w0 >> 17) & 0x1F;
            idx[1] = (w0 >> 9) & 0x1F;
            idx[2] = (w0 >> 1) & 0x1F;
            idx[3] = (w1 >> 17) & 0x1F;
            idx[4] = (w1 >> 9) & 0x1F;
            idx[5] = (w1 >> 1) & 0x1F;
            ntri = 2;
        } else if (op == 1) {
            addr = cmd[1];
            if ((addr >> 24) & 0xF) {
                addr = D_800D3048[(addr >> 24) & 0xF] + addr - (D_800D3088 << 24);
            }
            n = (s16) ((cmd[0] >> 12) & 0xFF);
            start = (s16) (((cmd[0] >> 1) & 0x7F) - n);
            for (k = start; k < n; k++) {
                verts[k] = addr;
                addr += 16;
            }
        } else if (op == 5) {
            for (k = 0; k < 3; k++) {
                idx[k] = ((u8 *) cmd)[1 + k] >> 1;
            }
            ntri = 1;
        }
        for (t = 0; t < ntri; t++) {
            tri = &idx[t * 3];
            if ((u32) verts[0] >= 0x100001) {
                for (c = 0; c < 3; c++) {
                    if (D_800DBE63 != 0) {
                        vmin[c] = -0x8000;
                        vmax[c] = 0x7FFF;
                    } else {
                        v = *(s16 *) (verts[tri[0]] + c * 2);
                        vmax[c] = v;
                        vmin[c] = v;
                        for (k = 1; k < 3; k++) {
                            v = *(s16 *) (verts[tri[k]] + c * 2);
                            if (v < vmin[c]) {
                                vmin[c] = v;
                            } else if (vmax[c] < v) {
                                vmax[c] = v;
                            }
                        }
                    }
                }
            }
            for (k = 0; k < 3; k++) {
                ((s32 *) D_800DC26C)[count * 3 + k] = verts[tri[k]];
            }
            b = (s16 *) (D_800DC270 + count * 8);
            b[0] = vmin[0];
            b[2] = vmax[0];
            b[1] = vmin[2];
            b[3] = vmax[2];
            b = (s16 *) (D_800DC274 + count * 4);
            b[0] = vmin[1];
            b[1] = vmax[1];
            count++;
        }
        i++;
    }
    D_800DBE38 = count;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001460.s")
#endif
