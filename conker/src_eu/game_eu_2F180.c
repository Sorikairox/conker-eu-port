#include <ultra64.h>

#include "functions.h"
#include "variables.h"

#include "macros.h"
// hoisted declarations of the NON_MATCHING bodies
s32 quadtree_filter_box_tris(s32 x0, s32 x1, s32 z0, s32 z1, s32 *xmin, s32 *zmax, u16 *in, u16 **out);
s32 quadtree_tri_box_test(struct_eu_bytes24 arg0);
void quadtree_write_leaf_list(s32 x0, s32 x1, s32 z0, s32 z1, u16 *list);
extern s32 g_level_tri_table;   /* triangle table: 3 vertex pointers (s16 x, y, z) per entry; was D_800DC26C */
extern s32 g_coll_tri_y_bounds;   /* grid table: s16 x, z per entry; was D_800DC274 */

/* was func_15001970 */
void collision_build_reset(void) {
    s32 pad;
    s32 tmp;

    g_collision_total_tris = 0;
    g_collision_full_bounds = 0;
    *g_coll_area_tri_counts = 0;
    *g_collision_area_tris_1 = 0;
    g_collision_area_tris_2 = 0;
    tmp = g_level_collision_buf_sizes[g_level_id];
    g_collision_area_tris_3 = 0;
    g_collision_buf_cursor = allocate_memory(tmp, 1, 0, 0);
    g_collision_buf_end = tmp + g_collision_buf_cursor;
    g_collision_buf_start = g_collision_buf_cursor;
}

extern s32 g_level_quadtree_pool_sizes[];   /* node pool size per level (rodata); was D_80091EA0 */
extern s32 g_quadtree_pool_base;     /* node pool base; was D_800B11EC */
extern s16 g_pvs_row; /* was D_800DC260 */
extern s16 g_quadtree_stat_1; /* was D_800DC262 */
extern s16 g_quadtree_stat_2; /* was D_800DC264 */
extern s16 g_quadtree_stat_3; /* was D_800DC266 */
void os_pi_get_access(void);  /* __osPiGetAccess */
void os_pi_rel_access(void);  /* __osPiRelAccess */

/* Node pool for the level quadtrees (quadtree_alloc_node hands out 14-byte nodes, quadtree_write_leaf_list appends the leaf lists).
 * The size per level doubles unless the cart word at ROM 0xD24 is 0x98CCE31A. */
/* was func_15001A08 */
void quadtree_alloc_node_pool(void) {
    s32 size;
    s32 word;

    size = g_level_quadtree_pool_sizes[g_level_id];
    os_pi_get_access();
    while (IO_READ(PI_STATUS_REG) & 3) {
    }
    word = IO_READ(g_os_rom_base | 0xB0000D24);
    os_pi_rel_access();
    if (word != 0x98CCE31A) {
        size <<= 1;
    }
    g_quadtree_pool_base = allocate_memory(size, 1, 0, 0);   /* implicit int declaration (collision_build_reset) */
    g_quadtree_pool_cursor = (u8 *) g_quadtree_pool_base;
    g_quadtree_node_count = 0;
    g_quadtree_leaf_count = 0;
    g_pvs_row = 0;
    g_quadtree_stat_1 = 0;
    g_quadtree_stat_2 = 0;
    g_quadtree_stat_3 = 0;
}
// NON-MATCHING: JUSTREG (US draft)
// void quadtree_alloc_node_pool(void) {
//     s32 sp24;
//     s32 tmp;
//     s32 sp1C;
//
//     tmp = g_level_id;
//     sp24 = g_text_icon_b9[tmp];
//
//     __osPiGetAccess();
//
//     while ((IO_READ(PI_STATUS_REG) & 3)) {};
//
//     tmp = g_os_rom_base | 0xB0000D24 | 0xA0000000;
//     sp1C = *(s32*)tmp;
//
//     __osPiRelAccess();
//
//     if (sp1C != 0x98CCE31A) {
//         sp24 <<= 1;
//     }
//
//     D_800B0DDC = allocate_memory(sp24, 1, 0, 0);
//     g_quadtree_pool_cursor = D_800B0DDC;
//     g_quadtree_node_count = 0;
//     g_quadtree_leaf_count = 0;
//     D_800DBE30 = 0;
//     D_800DBE32 = 0;
//     D_800DBE34 = 0;
//     D_800DBE36 = 0;
// }

/* was func_15001B10 */
u16* quadtree_alloc_node(void) {
    u16 *temp_v0;

    g_quadtree_pool_cursor = ALIGN4(g_quadtree_pool_cursor);
    g_quadtree_node_count += 1;

    temp_v0 = (u16*)g_quadtree_pool_cursor;
    temp_v0[6] = 0;
    temp_v0[2] = 0;

    g_quadtree_pool_cursor += 14;
    return temp_v0;
}

/* was func_15001B5C */
void quadtree_pool_put_byte(u8 arg0) {
    *g_quadtree_pool_cursor++ = arg0;
}

/* was func_15001B8C */
void quadtree_pool_put_u16_be(u16 arg0) {
   g_quadtree_pool_cursor[0] = (arg0 >> 8);
   g_quadtree_pool_cursor[1] = arg0 & 0xFF;
   g_quadtree_pool_cursor += 2;
}

/* was func_15001BC8 */
void quadtree_build_area(s32 arg0, s16 *arg1, s16 *arg2) {
    u16 *tmp;
    s16 *sp20;
    s32 i;

    collision_select_area(arg0);
    g_quadtree_leaf_max_tris = 10;
    g_quadtree_min_half_size = 512;
    sp20 = allocate_memory((g_coll_tri_count + 1) << 1, 1, 0, 0);

    *sp20 = g_coll_tri_count;
    for (i = 0; i < g_coll_tri_count; i++) {
        sp20[i + 1] = i;
    }

    tmp = quadtree_build_node(0, 0, 32768, 32768, 0, sp20);
    g_quadtree_roots[arg0] = tmp;
    quadtree_link_siblings(tmp, 0);
    heap_free(sp20);

    // regalloc fix:
    if (1) { }

    if (arg1 != 0) {
        *arg1 = g_quadtree_node_count;
    }
    if (arg2 != 0) {
        *arg2 = g_quadtree_leaf_count;
    }
}

/* was func_15001CEC */
void quadtree_build_area_flat(s32 arg0) {
    u16 *temp_v0;
    s16 *sp20;
    s32 i;

    collision_select_area(arg0);
    temp_v0 = quadtree_alloc_node();

    g_quadtree_roots[arg0] = temp_v0;

    *((s16*)temp_v0 + 0) = 32768;
    temp_v0[1] = 32767;
    temp_v0[2] = 0;
    temp_v0[3] = -32768;
    temp_v0[4] = 0;
    temp_v0[5] = 0;
    temp_v0[6] = 0;

    sp20 = allocate_memory((g_coll_tri_count + 1) << 1, 1, 0, 0);

    *sp20 = g_coll_tri_count;
    for (i = 0; i < g_coll_tri_count; i++) {
        sp20[i + 1] = i;
    }

    quadtree_write_leaf_list(-0x8000, 0x8000, -0x8000, 0x8000, sp20);
    heap_free(sp20);
}

/* was func_15001DE0 */
u16 *quadtree_build_node(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u16 *temp_v0;
    u16 *temp_v0_2;
    u16 *temp_v0_3;
    u16 *temp_v0_4;

    s32 sp7C;
    s32 sp78;

    s32 tmp0;
    s32 tmp1;

    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s32 sp50;
    s32 sp54;
    s32 sp58;

    tmp0 = g_quadtree_leaf_max_tris;
    tmp1 = g_quadtree_min_half_size;

    sp54 = arg0 - arg2;
    sp50 = arg0 + arg2;
    sp4C = arg1 - arg3;
    sp48 = arg1 + arg3;

    if ((quadtree_filter_box_tris(sp54, sp50, sp4C, sp48, &sp7C, &sp78, arg5, &sp58) < tmp0) || (arg2 < tmp1)) {
        temp_v0 = quadtree_alloc_node();
        g_quadtree_leaf_count = (g_quadtree_leaf_count + 1);
        temp_v0[0] = sp7C;
        temp_v0[1] = sp78;
        temp_v0[3] = arg2;
        temp_v0[4] = arg0;
        temp_v0[5] = arg1;
        temp_v0[2] = 0;
        temp_v0[6] = 0;
        quadtree_write_leaf_list(sp54, sp50, sp4C, sp48, sp58);
    } else {
        temp_v0 = quadtree_alloc_node();
        temp_v0[0] = sp7C;
        temp_v0[1] = sp78;
        temp_v0[3] = arg2;
        temp_v0[4] = arg0;
        temp_v0[5] = arg1;
        temp_v0[2] = 0;

        temp_v0_2 = quadtree_build_node(arg0 - (arg2 >> 1), arg1 - (arg3 >> 1), arg2 >> 1, arg3 >> 1, 0, sp58);
        temp_v0[6] = (s32)temp_v0_2 - (s32)temp_v0;
        temp_v0_3 = quadtree_build_node(arg0 - (arg2 >> 1), (arg3 >> 1) + arg1, arg2 >> 1, arg3 >> 1, 0, sp58);
        temp_v0_2[2] = (s32)temp_v0_3 - (s32)temp_v0_2;
        temp_v0_4 = quadtree_build_node((arg2 >> 1) + arg0, arg1 - (arg3 >> 1), arg2 >> 1, arg3 >> 1, 0, sp58);
        temp_v0_3[2] = (s32)temp_v0_4 - (s32)temp_v0_3;
        temp_v0_4[2] = (s32)quadtree_build_node((arg2 >> 1) + arg0, (arg3 >> 1) + arg1, arg2 >> 1, arg3 >> 1, 0, sp58) - (s32)temp_v0_4;
    }
    heap_free(sp58);
    return temp_v0;
}

// 3 loops
/* Leaf list of a quadtree node, appended to the node pool after the node: the entries of the u16 index list
 * `list` (list[0] = count) whose triangle (relative to the box centre, (x0 + x1) / 2 and (z0 + z1) / 2) passes
 * the box test quadtree_tri_box_test (0 = inside). The first kept index is written as a big-endian halfword | 0x8000;
 * the next ones as one byte (index - previous) when that is below 0x80, else again as a halfword | 0x8000.
 * A 0 byte ends the list. Vertex pointers up to 0x80000000 count as (0, 0, 0). */
/* was func_15002008 */
void quadtree_write_leaf_list(s32 x0, s32 x1, s32 z0, s32 z1, u16 *list) {
    s32 n;
    s32 prev;
    s32 k;
    s32 d;
    u16 *src;
    u16 *end;
    union {
        struct_eu_bytes24 s;
        f32 v[9];
    } tri;

    quadtree_set_test_box((f32) (x1 - x0), 32000.0f, (f32) (z1 - z0));
    prev = -1;
    n = list[0];
    if (n > 0) {
        src = &list[1];
        end = &list[n + 1];
        do {
            u16 idx = *src;
            u32 *verts = (u32 *) (g_level_tri_table + idx * 12);

            for (k = 0; k < 3; k++) {
                s16 *p = (s16 *) verts[k];
                if ((u32) p < 0x80000001) {
                    tri.v[k * 3 + 0] = 0.0f;
                    tri.v[k * 3 + 1] = 0.0f;
                    tri.v[k * 3 + 2] = 0.0f;
                } else {
                    tri.v[k * 3 + 0] = (f32) (p[0] - (x0 + x1) / 2);
                    tri.v[k * 3 + 1] = (f32) p[1];
                    tri.v[k * 3 + 2] = (f32) (p[2] - (z0 + z1) / 2);
                }
            }
            if (quadtree_tri_box_test(tri.s) == 0) {
                if (prev == -1) {
                    quadtree_pool_put_u16_be(idx | 0x8000);
                } else {
                    d = idx - prev;
                    if (d < 0x80) {
                        quadtree_pool_put_byte(d & 0xFF);
                    } else {
                        quadtree_pool_put_u16_be(idx | 0x8000);
                    }
                }
                prev = idx;
            }
            src++;
        } while (src != end);
    }
    quadtree_pool_put_byte(0);
}

/* Quadtree build helper of quadtree_build_node: keeps the entries of the u16 index list `in` (in[0] = count)
 * whose triangle (relative to the box centre) passes the box test quadtree_tri_box_test (0 = inside), writes
 * them to a new list *out (in[0] layout; the caller frees it) and returns their count. *xmin / *zmax get
 * the grid-snapped x minimum / z maximum of the kept entries (grid step 2 << g_last_player_index). */
/* was func_15002248 */
s32 quadtree_filter_box_tris(s32 x0, s32 x1, s32 z0, s32 z1, s32 *xmin, s32 *zmax, u16 *in, u16 **out) {
    s32 step = 1 << (g_last_player_index + 1);
    s32 lo = step - 1;
    s32 mask = -step;
    s32 n;
    s32 cnt;
    s32 found;
    s32 i;
    s32 k;
    u16 *list;
    u16 *src;
    union {
        struct_eu_bytes24 s;
        f32 v[9];
    } tri;

    quadtree_set_test_box((f32) (x1 - x0), 32000.0f, (f32) (z1 - z0));
    n = in[0] + 1;
    cnt = 0;
    list = (u16 *) allocate_memory(n * 2, 1, 0, 0);
    *out = list;
    *xmin = 0;
    *zmax = 0;
    found = 0;
    src = &in[1];
    for (i = 1; i < n; i++, src++) {
        u16 idx = *src;
        u32 *verts = (u32 *) (g_level_tri_table + idx * 12);
        s16 *g;
        s32 a;
        s32 b;

        for (k = 0; k < 3; k++) {
            s16 *p = (s16 *) verts[k];
            if ((u32) p < 0x80000001) {
                tri.v[k * 3 + 0] = 0.0f;
                tri.v[k * 3 + 1] = 0.0f;
                tri.v[k * 3 + 2] = 0.0f;
            } else {
                tri.v[k * 3 + 0] = (f32) (p[0] - ((x0 + x1) >> 1));
                tri.v[k * 3 + 1] = (f32) p[1];
                tri.v[k * 3 + 2] = (f32) (p[2] - ((z0 + z1) >> 1));
            }
        }
        if (quadtree_tri_box_test(tri.s) != 0) {
            continue;
        }
        list[++cnt] = idx;
        g = (s16 *) (g_coll_tri_y_bounds + idx * 4);
        a = (g[0] - lo) & mask;
        b = ((g[1] + lo) & mask) + lo;
        if (!found) {
            found = 1;
            *xmin = a;
            *zmax = b;
        } else {
            if (a < *xmin) {
                *xmin = a;
            }
            if (*zmax < b) {
                *zmax = b;
            }
        }
    }
    list[0] = cnt;
    return cnt;
}
/* was func_15002560 */
void quadtree_link_siblings(struct_eu_qnode *arg0, struct_eu_qnode *arg1) {
    struct_eu_qnode *s1;
    struct_eu_qnode *s0;
    s32 off;

    for (;;) {
        if (arg0 == NULL) {
            return;
        }
        if (arg0->unk4 == 0) {
            if (arg1 != NULL) {
                off = (u8 *)arg1 - (u8 *)arg0;
            } else {
                off = 0;
            }
            arg0->unk4 = off;
        }
        if (arg0->unkC == 0) {
            return;
        }
        s1 = (struct_eu_qnode *)((u8 *)arg0 + arg0->unkC);
        while (s1->unk4 != 0) {
            s0 = (struct_eu_qnode *)((u8 *)s1 + s1->unk4);
            quadtree_link_siblings(s1, s0);
            s1 = s0;
        }
        arg0 = s1;
    }
}

/* was func_150025FC */
void collision_load_level_grid(void) {
    s32 tmp0;
    s32 tmp1;
    s32 tmp2;
    s32 tmp3;

    tmp0 = g_quadtree0_node_count;
    tmp1 = g_quadtree0_leaf_count;

    g_pvs_row_bytes = (((tmp0 + 7) / 8) + 0xF) & 0xFFF0;
    tmp2 = asset_load(0, 2, 5, g_level_id << 1);
    tmp3 = asset_load(0, 2, 5, (g_level_id << 1) + 1);
    if (tmp2 == 0) {
        g_pvs_stream = 0;
    } else {
        pvs_setup(g_pvs_row_bytes, tmp1, tmp2, tmp3);
        heap_free(tmp3);
    }
}

/* was func_150026C4 */
void collision_begin_area(s32 arg0) {
    g_collision_area_tri_count = 0;
    collision_select_area(arg0);
}

/* was func_150026E8 */
void collision_end_area(s32 arg0) {
    g_coll_area_tri_counts[arg0] = g_collision_area_tri_count;
    g_coll_tri_count = g_collision_area_tri_count;
    g_collision_total_tris += g_collision_area_tri_count;
}

/* was func_15002724 */
void collision_count_dl_tris(s32 arg0) {
    g_collision_area_tri_count += dl_count_triangles(arg0);
}

/* was func_15002754 */
void collision_alloc_area_arrays(void) {
    g_collision_buf_cursor = (g_collision_buf_cursor + 3) & ~3;
    g_coll_area_tri_tables[g_collision_cur_area] = g_collision_buf_cursor;
    g_collision_buf_cursor += g_collision_area_tri_count * 12;
    g_coll_area_xz_bounds[g_collision_cur_area] = g_collision_buf_cursor;
    g_collision_buf_cursor += g_collision_area_tri_count * 8;
    g_coll_area_y_bounds[g_collision_cur_area] = g_collision_buf_cursor;
    g_collision_buf_cursor += g_collision_area_tri_count * 4;
    collision_select_area(g_collision_cur_area);
    g_collision_area_tri_count = 0;
}


/* was func_150027F8 */
s32 dl_count_triangles(Gfx *arg0) {
    s32 i;
    s32 count;
    s32 cmd;

    if (arg0 == NULL) {
        return 0;
    }
    i = 0;
    count = 0;
    while ((cmd = ((s8 *)&arg0[i])[0]) != -0x21) {
        i++;
        if ((cmd >> 4) == 1) {
            count += 4;
        } else if (cmd == 6) {
            count += 2;
        } else if (cmd == 5) {
            count += 1;
        }
    }
    return count;
}

/* was func_15002878 */
s32 collision_max_area_tris(void) {
    s32 i;
    s32 tmp;
    s32 highest;

    highest = *g_coll_area_tri_counts;

    for (i = 0; i < 3; i++) {
        tmp = g_collision_area_tris_1[i];
        if (highest < tmp) {
            highest = tmp;
        }
    }

    return highest;
}

extern s32 g_model_dl_tables[];    /* per model: its display-list table (one list used here); was D_800C48A8 */
extern u16 g_model_tri_counts[];    /* per model: triangle count; was D_800C5D38 */
extern u16 g_model_vtx_range_count[];    /* per model: vertex-range count; was D_800C6318 */

/* g_model_vtx_ranges[model] entries: a run of vertices loaded by G_VTX and the matrix group (G_MTX) they belong to */
typedef struct ModelVtxRange {
    u32 start;  /* model base g_model_bases[model] + vertex offset */
    s32 count;
    s32 group;  /* (G_MTX address & 0xFFFFFF) >> 6 */
} ModelVtxRange;

#define DL_OP(dl, k) (((u8 *) (dl))[(k) * 8])

/*
 * P65: per-model collision / skinning tables from the model's display list (g_model_dl_tables[id][0], Gfx words):
 * g_model_vtx_ranges[id] = the vertex ranges (one per G_VTX, merged with the previous range when contiguous and in the
 * same G_MTX group), sorted by start address, g_model_vtx_range_count[id] = their count; g_model_coll_tris[id] = the triangles
 * (g_model_tri_counts[id] of them) as 3 vertex byte offsets (into the model's vertex block, from base + 0x38) each, from
 * G_TRI1 (0x05), G_TRI2 (0x06) and the packed 4-triangle commands 0x10..0x1F (5-bit indices). Already built: 0.
 * Allocation failure: 1. Vertex buffer indices are assumed < 32, as in the game's lists (the asm's buffer is 32 words).
 */
/* was func_150028BC */
s32 model_build_collision_tables(s32 id) {
    s32 vtxOfs[32];
    s32 idx[3];
    ModelVtxRange *ranges;
    ModelVtxRange *last;
    ModelVtxRange tmp;
    u32 *dl;
    u32 *cmd;
    u32 base;
    u32 start;
    s32 w0, w1;
    s32 j, k, v, t, n, dst, ofs;
    s32 nVtxCmds = 0;
    s32 nRanges;
    s32 nTris;
    s32 group = 0;
    u8 op;

    if (g_model_vtx_ranges[id] != 0) {
        return 0;
    }

    /* count the G_VTX commands: at most one range each */
    for (j = 0; j < 1; j++) {
        dl = ((u32 **) g_model_dl_tables[id])[j];
        for (k = 0; DL_OP(dl, k) != 0xDF; k++) {
            if (DL_OP(dl, k) == 0x01) {
                nVtxCmds++;
            }
        }
    }
    g_model_vtx_ranges[id] = allocate_memory(nVtxCmds * sizeof(ModelVtxRange), 1, 0, 2);
    if (g_model_vtx_ranges[id] == 0) {
        return 1;
    }
    g_model_coll_tris[id] = allocate_memory(g_model_tri_counts[id] * 12, 1, 0, 2);
    if (g_model_coll_tris[id] == 0) {
        heap_free(g_model_vtx_ranges[id]);
        g_model_vtx_ranges[id] = 0;
        return 1;
    }

    base = ((s32 *) &g_model_bases)[id];
    nRanges = 0;
    nTris = 0;
    for (j = 0; j < 1; j++) {
        dl = ((u32 **) g_model_dl_tables[id])[j];
        for (k = 0; DL_OP(dl, k) != 0xDF; k++) {
            cmd = &dl[k * 2];
            op = DL_OP(dl, k);
            w0 = cmd[0];
            w1 = cmd[1];
            if (op == 0x01) {
                /* G_VTX: n vertices from segment offset w1 into buffer slots end - n .. end - 1 */
                n = (w0 >> 12) & 0xFF;
                dst = ((w0 >> 1) & 0x7F) - n;
                ofs = (w1 & 0xFFFFFF) - 0x38;
                for (v = 0; v < n; v++) {
                    vtxOfs[dst + v] = v * 16 + ofs;
                }
                start = base + (((u32) (w1 - 0x38) & 0xFFFFFF) >> 4) * 16;
                ranges = (ModelVtxRange *) g_model_vtx_ranges[id];
                last = &ranges[nRanges - 1];
                if (nRanges != 0 && start == last->count * 16 + last->start && group == last->group) {
                    last->count += n;
                } else {
                    ranges[nRanges].start = start;
                    nRanges++;
                    ranges[nRanges - 1].group = group;
                    ranges[nRanges - 1].count = n;
                }
            } else if (op == 0xDA) {
                /* G_MTX: following vertices belong to this matrix */
                group = (w1 & 0xFFFFFF) >> 6;
            } else if (op == 0x05) {
                /* G_TRI1: buffer indices * 2 in bytes 1..3 */
                for (v = 0; v < 3; v++) {
                    ((s32 *) g_model_coll_tris[id])[nTris * 3 + v] = vtxOfs[((u8 *) cmd)[1 + v] >> 1];
                }
                nTris++;
            } else if (op == 0x06) {
                /* G_TRI2: bytes 1..3 and 5..7 */
                for (t = 0; t < 8; t += 4) {
                    for (v = 0; v < 3; v++) {
                        ((s32 *) g_model_coll_tris[id])[nTris * 3 + v] = vtxOfs[((u8 *) cmd)[t + 1 + v] >> 1];
                    }
                    nTris++;
                }
            } else if ((op >> 4) == 1) {
                /* 0x10..0x1F: four triangles with 5-bit buffer indices packed in w1 and w0 */
                for (t = 0; t < 4; t++) {
                    if (t == 0) {
                        idx[0] = (w1 >> 25) & 0x1F;
                        idx[1] = (w1 >> 20) & 0x1F;
                        idx[2] = (w1 >> 15) & 0x1F;
                    } else if (t == 1) {
                        idx[0] = (w1 >> 10) & 0x1F;
                        idx[1] = (w1 >> 5) & 0x1F;
                        idx[2] = w1 & 0x1F;
                    } else if (t == 2) {
                        idx[0] = (w0 >> 10) & 0x1F;
                        idx[1] = (w0 >> 5) & 0x1F;
                        idx[2] = w0 & 0x1F;
                    } else {
                        idx[0] = (w0 >> 23) & 0x1F;
                        idx[1] = (w0 >> 18) & 0x1F;
                        idx[2] = ((w1 >> 30) & 3) | ((w0 >> 13) & 0x1C);
                    }
                    for (v = 0; v < 3; v++) {
                        ((s32 *) g_model_coll_tris[id])[nTris * 3 + v] = vtxOfs[idx[v]];
                    }
                    nTris++;
                }
            }
        }
    }

    /* gnome sort of the ranges by start address */
    g_model_vtx_range_count[id] = nRanges;
    k = 1;
    while (k < g_model_vtx_range_count[id]) {
        ranges = (ModelVtxRange *) g_model_vtx_ranges[id];
        if (ranges[k].start < ranges[k - 1].start) {
            tmp = ranges[k];
            ranges[k] = ranges[k - 1];
            ((ModelVtxRange *) g_model_vtx_ranges[id])[k - 1] = tmp;
            if (k >= 2) {
                k--;
            }
        } else {
            k++;
        }
    }
    return 0;
}

/* was func_15002F40 */
void collision_set_step_size(s32 arg0) {
    if (arg0 == 50 || arg0 == 51) {
        g_collision_floor_step = 150.0f;
        return;
    }
    if (g_mp_mode_active) {
        g_collision_floor_step = 85.0f;
        return;
    }
    g_collision_floor_step = 50.0f;
}

/* was func_15002FA0 */
s32 xor_f0f0f0f0(s32 arg0) {
    return arg0 ^ 0xF0F0F0F0;
}

/* was func_15002FB4 */
void level_load_header(s32 arg0) {
    struct00 *sp3C; // TBD
    s32 sp38;
    s32 sp34;
    struct104 *temp_v0;
    s32 sp2C;

    sp3C = asset_load_with_subfiles(&sp34, 0, &sp38, 2, 21, arg0);
    if ((sp38 != 0) && ((sp3C->unk4 << 8) != 0)) {
        g_level_header = sp3C->unk0;
        if (sp34 == 0) {
            g_dbg_crash_marker = 0xC000037;
            func_150AD770();
        }
        if (g_level_header == 0) {
            g_dbg_crash_marker = 0xC000037;
            func_150AD770();
        }
    }
    func_151EF040(xor_f0f0f0f0(0x40F0FAAC), &sp2C);
    sp2C = xor_f0f0f0f0(sp2C);
    if (sp2C != 0xE7B00F09) {
        temp_v0 = g_level_header;
        temp_v0->unk12 >>= 1;
    }

    temp_v0 = g_level_header;
    if (temp_v0->unk12 != 0) {
        g_level_event_count = temp_v0->unk12;
        g_level_event_ids = sp3C->unk8;
    } else {
        g_level_event_count = 0U;
        g_level_event_ids = 0;
    }

    if ((g_human_player_count_us >= 2) && (temp_v0->unk8 == 4)) {
        temp_v0->unk8 = 2U;
    }
}

/* was func_1500310C */
void level_stub_noop(void) {
}
