#include <ultra64.h>

#include "functions.h"
#include "variables.h"

#include "macros.h"

void func_15000AC0(void) {
    D_800D9E64 = (u8)0;
}

// jump table
#ifdef NON_MATCHING
extern u8 D_800DC2D8[];       /* camera / sky settings copied from the level header +5..+7 */
extern u8 D_800DC2DB;         /* 1 on level 0x3C (mode 4) */
extern u8 D_800DC2DC;         /* bit 0 of D_800D2E4C->unk14 */
extern s32 D_800DC2E0;        /* per player: two Mtx (one per frame buffer) */
extern Vtx *D_800DC2B8[][2];  /* per player: two vertex buffers (one per frame buffer) */
extern s32 *D_8008955C[];
void *allocate_memory(s32, s32, s32, s32);
s32 func_1510D66C(s32, s32 *, s32, s32);
void func_15111DD8(void);

/* Sky gradient of mode 2: a start colour, then three segments (end colour, end row) blended linearly row by
 * row; the rows after the last segment keep its colour. Picked by level (D_800BE9F0). */
typedef struct {
    s32 rgb[3];
    s32 end;
} SkySegment;

typedef struct {
    s32 start[3];
    SkySegment seg[3];
} SkyGradient;

static const SkyGradient sSkyGradients[] = {
    /* level 0x24 */
    { { 0x00, 0x00, 0x00 }, { { { 0x00, 0x00, 0x1F }, 0x7B }, { { 0x03, 0x1C, 0x36 }, 0xA2 }, { { 0x21, 0x24, 0x31 }, 0xB7 } } },
    /* level 0x2B */
    { { 0x00, 0x00, 0x00 }, { { { 0x00, 0x00, 0x5D }, 0x85 }, { { 0x1C, 0x15, 0x93 }, 0x9C }, { { 0x0A, 0x22, 0xFF }, 0xB4 } } },
    /* levels 0, 0x29, 0x2D, 0x30 */
    { { 0x00, 0x00, 0xBF }, { { { 0xD0, 0xD5, 0xFF }, 0xA7 }, { { 0x12, 0x4E, 0x19 }, 0xB1 }, { { 0x00, 0xC7, 0x00 }, 0xDD } } },
    /* other levels */
    { { 0x00, 0x67, 0x38 }, { { { 0xC8, 0xD5, 0x2E }, 0x23 }, { { 0xFF, 0x3E, 0x12 }, 0x63 }, { { 0x00, 0x00, 0x00 }, 0xC8 } } },
};

/*
 * P74: per-level setup of the sky / backdrop buffers (called by func_15007B3C with D_800BE9F0; the argument is
 * unused). D_800DC2D8[0..2] = level header +5..+7. Backdrop mode = header +8 (4 becomes 2 when D_800BE616 is set):
 *  - 4: per player (0..D_80082FA0) a vertex buffer of 2 x n vertices (n = 0x1C0 with D_80082FA0 == 1, else 0x130),
 *       D_800DC2B0 loaded as asset (0xD, header +9) by func_1502B7F0, 0x168 entries of D_8008955C[+9] requested
 *       when D_80038080 is set, two Mtx per player in D_800DC2E0, D_800DC2DB = (level == 0x3C).
 *  - 2: D_800DC2B0 = 256-row sky gradient texture (4 RGBA32 texels per row, sSkyGradients), two Mtx per player in
 *       D_800DC2E0, and per player two 4-vertex quads (+-0x6D6, z -1000, s 0x2000) in D_800DC2B8 (read by
 *       func_1510FD50 / game_eu_FF530.c).
 *  - 1: func_15111DD8.
 * Always: D_800DC2DC = bit 0 of D_800D2E4C->unk14.
 */
void func_15000AD0(s32 level) {
    const SkyGradient *g;
    const SkySegment *s;
    u32 *tex;
    Vtx *buf;
    Vtx *v;
    s32 from[3];
    s32 col[3];
    s32 n;
    s32 p;
    s32 i;
    s32 j;
    s32 k;
    s32 row;
    u32 rgba;

    D_800DC2D8[0] = D_800B0DF0->unk5;
    D_800DC2D8[1] = D_800B0DF0->unk6;
    D_800DC2D8[2] = D_800B0DF0->unk7;
    if (D_800BE616 != 0 && D_800B0DF0->unk8 == 4) {
        D_800B0DF0->unk8 = 2;
    }

    if (D_800B0DF0->unk8 == 4) {
        n = (D_80082FA0 == 1) ? 0x1C0 : 0x130;
        for (p = 0; p <= D_80082FA0; p++) {
            buf = allocate_memory(n * 2 * sizeof(Vtx), 1, 2, 0);
            D_800DC2B8[p][0] = buf;
            D_800DC2B8[p][1] = buf + n;
        }
        func_1502B7F0(&D_800DC2B0, 2, 0xD, D_800B0DF0->unk9);
        if (D_80038080 != 0) {
            for (i = 0; i < 0x168; i++) {
                func_1510D66C(*D_8008955C[D_800B0DF0->unk9] + i, NULL, 0x3F, 0);
            }
        }
        D_800DC2E0 = (s32) allocate_memory((D_80082FA0 + 1) * 2 * sizeof(Mtx), 1, 2, 0);
        D_800DC2DB = (D_800BE9F0 == 0x3C) ? 1 : 0;
    } else if (D_800B0DF0->unk8 == 2) {
        tex = allocate_memory(0x100 * 4 * sizeof(u32), 1, 1, 0);
        D_800DC2B0 = (s32) tex;
        switch (D_800BE9F0) {
            case 0x24:
                g = &sSkyGradients[0];
                break;
            case 0x2B:
                g = &sSkyGradients[1];
                break;
            case 0:
            case 0x29:
            case 0x2D:
            case 0x30:
                g = &sSkyGradients[2];
                break;
            default:
                g = &sSkyGradients[3];
                break;
        }
        for (k = 0; k < 3; k++) {
            from[k] = g->start[k];
            col[k] = g->start[k];
        }
        row = 0;
        for (j = 0; j < 3; j++) {
            s = &g->seg[j];
            for (i = row; i < s->end; i++) {
                for (k = 0; k < 3; k++) {
                    col[k] = from[k] + (s->rgb[k] - from[k]) * (i - row) / (s->end - row);
                }
                rgba = (col[0] << 24) | (col[1] << 16) | (col[2] << 8);
                tex[i * 4 + 0] = rgba;
                tex[i * 4 + 1] = rgba;
                tex[i * 4 + 2] = rgba;
                tex[i * 4 + 3] = rgba;
            }
            for (k = 0; k < 3; k++) {
                from[k] = s->rgb[k];
            }
            row = s->end;
        }
        rgba = (from[0] << 24) | (from[1] << 16) | (from[2] << 8);
        for (i = row; i < 0x100; i++) {
            tex[i * 4 + 0] = rgba;
            tex[i * 4 + 1] = rgba;
            tex[i * 4 + 2] = rgba;
            tex[i * 4 + 3] = rgba;
        }

        D_800DC2E0 = (s32) allocate_memory((D_80082FA0 + 1) * 2 * sizeof(Mtx), 1, 1, 0);
        for (p = 0; p <= D_80082FA0; p++) {
            buf = allocate_memory(2 * 4 * sizeof(Vtx), 1, 1, 0);
            D_800DC2B8[p][0] = buf;
            D_800DC2B8[p][1] = buf + 4;
            for (j = 0; j < 2; j++) {
                v = D_800DC2B8[p][j];
                for (k = 0; k < 4; k++) {
                    v[k].v.ob[0] = (k == 0 || k == 3) ? -0x6D6 : 0x6D6;
                    v[k].v.ob[1] = (k < 2) ? 0x6D6 : -0x6D6;
                    v[k].v.ob[2] = -1000;
                    v[k].v.flag = 0;
                    v[k].v.tc[0] = 0x2000;
                }
            }
        }
    } else if (D_800B0DF0->unk8 == 1) {
        func_15111DD8();
    }

    D_800DC2DC = (D_800D2E4C->unk14 & 1) ? 1 : 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15000AD0.s")
#endif
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
