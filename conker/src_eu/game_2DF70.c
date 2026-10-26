#include <ultra64.h>

#include "functions.h"
#include "variables.h"

#include "macros.h"

/* was func_15000AC0 */
void texture_scroll_clear(void) {
    g_tex_scroll_count = (u8)0;
}

// jump table
extern u8 g_level_bg_colour[];       /* camera / sky settings copied from the level header +5..+7; was D_800DC2D8 */
extern u8 g_sky_load_all_tiles;         /* 1 on level 0x3C (mode 4); was D_800DC2DB */
extern u8 g_sky_alt_tiles;         /* bit 0 of g_save_progress_bits->unk14; was D_800D2E4C; was D_800DC2DC */
extern s32 g_sky_backdrop_mtx;        /* per player: two Mtx (one per frame buffer); was D_800DC2E0 */
extern Vtx *g_sky_backdrop_vtx[][2];  /* per player: two vertex buffers (one per frame buffer); was D_800DC2B8 */
extern s32 *g_sky_tex_sets[]; /* was D_8008955C */
void *allocate_memory(s32, s32, s32, s32);
s32 texture_cache_lookup(s32, s32 *, s32, s32);
void star_field_generate(void);

/* Sky gradient of mode 2: a start colour, then three segments (end colour, end row) blended linearly row by
 * row; the rows after the last segment keep its colour. Picked by level (g_level_id). */
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
 * P74: per-level setup of the sky / backdrop buffers (called by level_load with g_level_id; the argument is
 * unused). g_level_bg_colour[0..2] = level header +5..+7. Backdrop mode = header +8 (4 becomes 2 when g_mp_mode_active is set):
 *  - 4: per player (0..g_last_player_index) a vertex buffer of 2 x n vertices (n = 0x1C0 with g_last_player_index == 1, else 0x130),
 *       g_sky_asset loaded as asset (0xD, header +9) by asset_load_ptr, 0x168 entries of g_sky_tex_sets[+9] requested
 *       when g_mem_expansion_pak is set, two Mtx per player in g_sky_backdrop_mtx, g_sky_load_all_tiles = (level == 0x3C).
 *  - 2: g_sky_asset = 256-row sky gradient texture (4 RGBA32 texels per row, sSkyGradients), two Mtx per player in
 *       g_sky_backdrop_mtx, and per player two 4-vertex quads (+-0x6D6, z -1000, s 0x2000) in g_sky_backdrop_vtx (read by
 *       func_1510FD50 / game_eu_FF530.c).
 *  - 1: star_field_generate.
 * Always: g_sky_alt_tiles = bit 0 of g_save_progress_bits->unk14.
 */
/* was func_15000AD0 */
void level_setup_sky_backdrop(s32 level) {
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

    g_level_bg_colour[0] = g_level_header->unk5;
    g_level_bg_colour[1] = g_level_header->unk6;
    g_level_bg_colour[2] = g_level_header->unk7;
    if (g_mp_mode_active != 0 && g_level_header->unk8 == 4) {
        g_level_header->unk8 = 2;
    }

    if (g_level_header->unk8 == 4) {
        n = (g_last_player_index == 1) ? 0x1C0 : 0x130;
        for (p = 0; p <= g_last_player_index; p++) {
            buf = allocate_memory(n * 2 * sizeof(Vtx), 1, 2, 0);
            g_sky_backdrop_vtx[p][0] = buf;
            g_sky_backdrop_vtx[p][1] = buf + n;
        }
        asset_load_ptr(&g_sky_asset, 2, 0xD, g_level_header->unk9);
        if (g_mem_expansion_pak != 0) {
            for (i = 0; i < 0x168; i++) {
                texture_cache_lookup(*g_sky_tex_sets[g_level_header->unk9] + i, NULL, 0x3F, 0);
            }
        }
        g_sky_backdrop_mtx = (s32) allocate_memory((g_last_player_index + 1) * 2 * sizeof(Mtx), 1, 2, 0);
        g_sky_load_all_tiles = (g_level_id == 0x3C) ? 1 : 0;
    } else if (g_level_header->unk8 == 2) {
        tex = allocate_memory(0x100 * 4 * sizeof(u32), 1, 1, 0);
        g_sky_asset = (s32) tex;
        switch (g_level_id) {
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

        g_sky_backdrop_mtx = (s32) allocate_memory((g_last_player_index + 1) * 2 * sizeof(Mtx), 1, 1, 0);
        for (p = 0; p <= g_last_player_index; p++) {
            buf = allocate_memory(2 * 4 * sizeof(Vtx), 1, 1, 0);
            g_sky_backdrop_vtx[p][0] = buf;
            g_sky_backdrop_vtx[p][1] = buf + 4;
            for (j = 0; j < 2; j++) {
                v = g_sky_backdrop_vtx[p][j];
                for (k = 0; k < 4; k++) {
                    v[k].v.ob[0] = (k == 0 || k == 3) ? -0x6D6 : 0x6D6;
                    v[k].v.ob[1] = (k < 2) ? 0x6D6 : -0x6D6;
                    v[k].v.ob[2] = -1000;
                    v[k].v.flag = 0;
                    v[k].v.tc[0] = 0x2000;
                }
            }
        }
    } else if (g_level_header->unk8 == 1) {
        star_field_generate();
    }

    g_sky_alt_tiles = (g_save_progress_bits->unk14 & 1) ? 1 : 0;
}
// loops!
extern s32 g_level_tri_table;    /* triangle table: 3 vertex pointers per triangle (12 bytes); was D_800DC26C */
extern s32 g_coll_tri_xz_bounds;    /* per triangle: s16 x min, z min, x max, z max; was D_800DC270 */
extern s32 g_coll_tri_y_bounds;    /* per triangle: s16 y min, y max; was D_800DC274 */
extern s32 g_segment_table[];  /* segment table; was D_800D3048 */
extern u8 g_collision_scan_objects;     /* 1 while object DLs are scanned: segment addresses lose 0x01000000; was D_800D3088 */

/* Collision triangle scan of a level DL (ends at G_ENDDL 0xDF): G_VTX (0x01) loads vertex pointers into a 32-entry
 * cache (the loop runs from the first vertex v0 = end - n to n - 1, as the asm does), G_TRI1 (0x05, index bytes
 * 1-3 / 2), G_TRI2 (0x06, 5-bit fields at bits 17 / 9 / 1 of both words) and Rare's 0x1x (four triangles, 5-bit
 * fields) append triangles at g_collision_area_tri_count: the 3 vertex pointers and the bounds (x / z in g_coll_tri_xz_bounds, y in g_coll_tri_y_bounds;
 * full range when g_collision_full_bounds is set). The bounds are recomputed only when cache entry 0 holds a pointer above
 * 0x100000; otherwise the previous triangle's bounds are written again. */
/* was func_15001460 */
void collision_scan_level_dl(s32 arg0) {
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
    count = g_collision_area_tri_count;
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
                addr = g_segment_table[(addr >> 24) & 0xF] + addr - (g_collision_scan_objects << 24);
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
                    if (g_collision_full_bounds != 0) {
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
                ((s32 *) g_level_tri_table)[count * 3 + k] = verts[tri[k]];
            }
            b = (s16 *) (g_coll_tri_xz_bounds + count * 8);
            b[0] = vmin[0];
            b[2] = vmax[0];
            b[1] = vmin[2];
            b[3] = vmax[2];
            b = (s16 *) (g_coll_tri_y_bounds + count * 4);
            b[0] = vmin[1];
            b[1] = vmax[1];
            count++;
        }
        i++;
    }
    g_collision_area_tri_count = count;
}
