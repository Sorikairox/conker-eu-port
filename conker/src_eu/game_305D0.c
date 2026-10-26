#include <ultra64.h>

#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
extern s32 *g_level_model_colour_groups; /* was D_800B1240 */
extern u8 *g_level_model_colour_counts; /* was D_800B1244 */
u8 *allocate_memory(s32, s32, s32, s32);
extern u8 g_level_model_colour_group_count; /* was D_800B1248 */
extern s32 g_level_dl_tinted_extra[]; /* was D_800B1214 */
extern s32 g_level_part_vtx_base_1[]; /* was D_800B1224 */
extern s32 g_level_part_vtx_count_1[]; /* was D_800B1254 */
extern s32 g_level_model_entries; /* was D_800B1260 */
extern s32 g_level_part_vtx[]; /* was D_800B1220 */
extern s32 g_level_part_vtx_count[]; /* was D_800B1250 */
extern s32 g_level_part_hdr8[]; /* was D_800B1230 */
extern s32 *g_level_tex_preload_lists[]; /* was D_80082EB0 */
s32 asset_load_with_subfiles(s32 *, s32, s32 *, s32, ...);
void gfx_dl_relocate_segments(Gfx *, s32, s32);
s32 texture_resolve_dl_ids(Gfx *, s32, s32, s32, s16 **);
s32 texture_cache_lookup(s32, s32 *, s32, s32);


// what is this loop doing?
/* Relocates a level model's {ptr, ptr, x} table (12-byte entries, ends at ptr0 == 0) by base: the table
 * pointer goes to g_level_model_colour_groups[idx] (made absolute when non-zero) and its entry count to g_level_model_colour_counts[idx]. */
/* was func_15003120 */
void level_model_relocate_table(s32 idx, s32 base, s32 table) {
    s32 n;
    s32 off;
    s32 *e;

    g_level_model_colour_groups[idx] = table;
    g_level_model_colour_counts[idx] = 0;
    if (table == 0) {
        return;
    }
    g_level_model_colour_groups[idx] += base;
    n = 0;
    off = 0;
    e = (s32 *)g_level_model_colour_groups[idx];
    if (e[0] != 0) {
        do {
            e[0] += base;
            n++;
            e = (s32 *)(g_level_model_colour_groups[idx] + off);
            off += 12;
            e[1] += base;
            e = (s32 *)(g_level_model_colour_groups[idx] + off);
        } while (e[0] != 0);
    }
    g_level_model_colour_counts[idx] = n;
}
/* Level model loader: asset (2, 4, level) is a list of count {model header, size} pairs. Each header's
 * offsets +0 (display list), +8, +0x10 are made absolute, its {ptr, ptr, x} table at +0x20 is relocated by
 * level_model_relocate_table (g_level_model_colour_groups / g_level_model_colour_counts). Parts 0..3 also set g_level_part_dls[i] (level DL), g_level_part_vtx[i]
 * (vertex base = header + 0x28), g_level_part_vtx_count[i] (vertex count = (DL - vertices) / 16), g_level_part_hdr8[i] (+8);
 * part 0 calls collision_set_tri_flags_table(+0x10). Then the level's texture preload list g_level_tex_preload_lists[g_level_header->0x4B]
 * (age 0x3E). Allocations: count * 4 bytes (g_level_model_colour_groups) and count bytes (g_level_model_colour_counts), both
 * allocate_memory(n, 1, 0, 0); both are cleared with bzero(p, count) (count bytes, also for the word array). */
/* was func_150031EC */
void level_load_models(s32 level) {
    s32 found;
    s32 count;
    s32 size;
    s32 *ent;
    u8 *hdr;
    u32 i;
    s32 *p;
    s32 *q;
    s32 *r;
    s32 off;
    s32 id;

    if (level >= 0x45) {
        level = 0;
    }
    ent = (s32 *)asset_load_with_subfiles(&found, 0, &count, 2, 4, level);
    g_level_model_entries = (s32)ent;
    p = g_level_dl_tinted_extra;
    q = g_level_part_vtx_base_1;
    r = g_level_part_vtx_count_1;
    do {
        *p++ = 0;
        *q++ = 0;
        *r++ = 0;
    } while (r != &g_level_model_entries);
    texture_table_reset();
    if (found != 0) {
        g_level_model_colour_groups = (s32 *)allocate_memory(count * 4, 1, 0, 0);
        g_level_model_colour_counts = (u8 *)allocate_memory(count, 1, 0, 0);
        bzero(g_level_model_colour_counts, count);
        bzero(g_level_model_colour_groups, count);
        g_level_model_colour_group_count = count;
        for (i = 0; i < (u32)count; i++, ent += 2) {
            hdr = (u8 *)ent[0];
            if (hdr == NULL || ent[1] == 0) {
                continue;
            }
            if (*(s32 *)(hdr + 0x0) != 0) {
                *(s32 *)(hdr + 0x0) += (s32)hdr;
            }
            if (*(s32 *)(hdr + 0x8) != 0) {
                *(s32 *)(hdr + 0x8) += (s32)hdr;
            }
            if (*(s32 *)(hdr + 0x10) != 0) {
                *(s32 *)(hdr + 0x10) += (s32)hdr;
            }
            level_model_relocate_table(i, (s32)hdr, *(s32 *)(hdr + 0x20));
            if (i < 4) {
                g_level_part_vtx[i] = (s32)(hdr + 0x28);
                g_level_part_dls[i] = *(s32 *)(hdr + 0x0);
                g_level_part_vtx_count[i] = (u32)(*(s32 *)(hdr + 0x0) - (s32)(hdr + 0x28)) >> 4;
                g_level_part_hdr8[i] = *(s32 *)(hdr + 0x8);
                if (i == 0) {
                    collision_set_tri_flags_table(*(s32 *)(hdr + 0x10));
                }
                gfx_dl_relocate_segments((Gfx *)g_level_part_dls[i], g_level_part_vtx[i] + 0xFF000000, (s32)hdr);
                texture_resolve_dl_ids((Gfx *)g_level_part_dls[i], 0, 1, 0x3F, NULL);
            } else {
                gfx_dl_relocate_segments((Gfx *)*(s32 *)(hdr + 0x0), 0, (s32)hdr);
            }
        }
    }
    if (((u8 *)g_level_header)[0x4B] != 0) {
        id = g_level_tex_preload_lists[((u8 *)g_level_header)[0x4B]][0];
        off = 4;
        while (id != 0) {
            texture_cache_lookup(id, &size, 0x3E, 0);
            id = *(s32 *)((u8 *)g_level_tex_preload_lists[((u8 *)g_level_header)[0x4B]] + off);
            off += 4;
        }
    }
}
/* was func_150034B4 */
s32 texture_table_reset(void) {
      s32 i;

      for (i = 0; i < 7764; i++) {
          g_texture_table_ids[i] = -1;
          g_texture_table_flags[i] = 0;
      }

      g_texture_last_id_a = 0xFFFF; // -1 s16?
      g_texture_last_id_b = -1;

      if ((g_level_id != 1) && (g_level_id != 50)) {
          g_texture_level_mode = 0;
      } else {
          g_texture_level_mode = 1;
      }
}

u8 *allocate_memory(s32, s32, s32, s32);
void heap_free(s32);
extern u8 D_1A3B40[];
extern u16 g_texture_rom_sizes[]; /* was D_800920D0 */
extern s16 g_texture_expanded_sizes[]; /* was D_800B8BB8 */

/* build a table of 16-bit words read from ROM: for each entry, DMA 16 bytes at the (even-aligned) ROM
   position, take the big-endian halfword at offset 2 from the real (possibly odd) position, then advance
   by the entry's length */
/* was func_15003570 */
void texture_build_size_table(void) {
    u8 *buf = allocate_memory(0x10, 1, 2, 0);
    u32 rom = (u32)D_1A3B40;
    u16 *len = g_texture_rom_sizes;
    s16 *out = g_texture_expanded_sizes;
    s32 odd;

    do {
        if (rom & 1) {
            rom--;
            odd = 1;
        } else {
            odd = 0;
        }
        rom_dma_read(rom, buf, 0x10, 1);
        *out++ = (buf[odd + 2] << 8) | buf[odd + 3];
        rom += *len++ + odd;
    } while (out != (s16 *)g_texture_cache_ages);
    heap_free((s32)buf);
}
// NON-MATCHING: something along these lines
// void texture_build_size_table(void) {
//     s32 temp_s4;
//     s32 phi_s0;
//     s32 phi_s1;
//
//     s32 i;
//     u8 *temp_v0;
//     s16 *phi_s2;
//     s16 *phi_s3;
//
//     temp_s4 = allocate_memory(16, 1, 2, 0);
//
//     phi_s0 = 0x1A37E0; // 1718240
//     phi_s2 = D_80091D20;
//     phi_s3 = D_800B87A0;
//
//     for (i = 0; i < 7764; i++) {
//         if ((phi_s0 & 1) != 0) {
//             phi_s0 = phi_s0 - 1;
//             phi_s1 = 1;
//         } else {
//             phi_s1 = 0;
//         }
//         rom_dma_read(phi_s0, temp_s4, 16, 1);
//         temp_v0 = temp_s4 + phi_s1;
//         phi_s2[i] = (*temp_v0 << 24) + (*(temp_v0 + 1) << 16) + (*(temp_v0 + 2) << 8) + *(temp_v0 + 3);
//         phi_s0 = phi_s3[i];
//     }
//
//     heap_free(temp_s4);
// }

void collision_scan_level_dl(s32);
void collision_alloc_area_arrays(void);
s32 collision_max_area_tris(void);
void collision_select_area(s32);
extern s32 g_collision_scan_count; /* was D_800D304C */
extern s8 g_collision_scan_objects; /* was D_800D3088 */
extern s32 g_floor_hits; /* was D_800D3720 */
extern s32 g_level_tri_vis_flags_end; /* was D_800D3A8C */
extern s32 g_level_tri_table; /* was D_800DC26C */

/* was func_15003668 */
void collision_build_level_tris(s32 arg0) {
    s32 temp_s3;
    s32 temp_t7;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    g_coll_quadtrees_built = 0;
    collision_build_reset();
    g_collision_scan_objects = 0;
    collision_begin_area(0);
    collision_count_dl_tris((*(s32 *)((u8 *)g_level_part_dls + 0)));
    collision_alloc_area_arrays();
    collision_scan_level_dl((*(s32 *)((u8 *)g_level_part_dls + 0)));
    collision_end_area(0);
    collision_begin_area(1);
    collision_count_dl_tris((*(s32 *)((u8 *)g_level_part_dls + 0xC)));
    collision_alloc_area_arrays();
    collision_scan_level_dl((*(s32 *)((u8 *)g_level_part_dls + 0xC)));
    collision_end_area(1);
    collision_begin_area(2);
    var_s1 = 0;
    var_s0 = 0;
    if (g_world_obj_count > 0) {
        do {
            temp_v0 = &g_world_objs->pad[var_s0];
            if (((*(u8 *)((u8 *)temp_v0 + 0x4F)) & 0x60) != 0x20) {
                collision_count_dl_tris((*(s32 *)((u8 *)temp_v0 + 0x1C)));
            }
            var_s1 += 1;
            var_s0 += 0xA0;
        } while (var_s1 < g_world_obj_count);
        var_s1 = 0;
    }
    collision_alloc_area_arrays();
    g_collision_scan_objects = 1;
    g_collision_scan_count = 0;
    var_s0_2 = 0;
    if (g_world_obj_count > 0) {
        do {
            temp_v0_2 = &g_world_objs->pad[var_s0_2];
            if (((*(u8 *)((u8 *)temp_v0_2 + 0x4F)) & 0x60) != 0x20) {
                temp_s3 = g_collision_area_tri_count;
                (*(s16 *)((u8 *)temp_v0_2 + 0x58)) = (s16) temp_s3;
                collision_scan_level_dl((*(s32 *)((u8 *)(&g_world_objs->pad[var_s0_2]) + 0x1C)));
                (*(s16 *)((u8 *)(&g_world_objs->pad[var_s0_2]) + 0x56)) = (s16) (g_collision_area_tri_count - temp_s3);
            } else {
                (*(s16 *)((u8 *)temp_v0_2 + 0x58)) = 0;
                (*(s16 *)((u8 *)(&g_world_objs->pad[var_s0_2]) + 0x56)) = 0;
            }
            var_s1 += 1;
            var_s0_2 += 0xA0;
        } while (var_s1 < g_world_obj_count);
    }
    collision_end_area(2);
    g_collision_scan_objects = 0;
    (*(s32 *)((u8 *)(&g_floor_hits) + 0)) = 0;
    (*(s32 *)((u8 *)(&g_floor_hits) + 4)) = (s32) (g_level_tri_table << 8);
    collision_select_area(0);
    temp_t7 = (collision_max_area_tris() + 7) & ~7;
    g_level_tri_vis_flags = (s32) g_mem_scratch_area;
    g_level_tri_vis_flags_end = g_mem_scratch_area + temp_t7;
    collision_select_area(2);
}
// NON-MATCHING: 40% there
// void collision_build_level_tris(s32 arg0) {
//     struct131 *temp_v0_2;
//     s32 temp_t7;
//     s32 i;
//     s32 tmp0;
//
//     g_coll_quadtrees_built = (u8)0;
//     collision_build_reset();
//     D_800D2C68 = (u8)0;
//     collision_begin_area(0);
//     collision_count_dl_tris(g_level_part_dls[0]); // ->unk0
//     collision_alloc_area_arrays();
//     collision_scan_level_dl(g_level_part_dls[0]); // ->unk0
//     collision_end_area(0);
//     collision_begin_area(1);
//     collision_count_dl_tris(g_level_part_dls[3]);
//     collision_alloc_area_arrays();
//     collision_scan_level_dl(g_level_part_dls[3]);
//     collision_end_area(1);
//     collision_begin_area(2);
//
//     if (D_800DBEF0 > 0) {
//         for (i = 0; i < D_800DBEF0; i++) {
//             temp_v0_2 = &g_world_objs[i];
//             if (((u8)temp_v0_2->unk4F & 0x60) != 32) {
//                 collision_count_dl_tris(temp_v0_2->unk1C);
//             }
//         }
//     }
//
//     collision_alloc_area_arrays();
//     D_800D2C68 = (u8)1;
//     D_800D2C2C = 0;
//
//     for (i = 0; i < D_800DBEF0; i++) {
//         temp_v0_2 = &g_world_objs[i];
//         if (((u8)temp_v0_2->unk4F & 0x60) != 32) {
//             temp_v0_2->unk58 = g_collision_area_tri_count;
//             temp_v0_2->unk56 = 0; //g_collision_area_tri_count - g_collision_area_tri_count;
//             collision_scan_level_dl(temp_v0_2->unk1C);
//         } else {
//             temp_v0_2->unk58 = 0;
//             temp_v0_2->unk56 = 0;
//         }
//     }
//
//     collision_end_area(2);
//     D_800D2C68 = 0;
//     D_800D3300->unk0 = 0;
//     D_800D3300->unk4 = (s32) (D_800DBE3C << 8);
//     collision_select_area(0);
//     temp_t7 = (collision_max_area_tris() + 7) & ~7; // ALIGN8
//     g_level_tri_vis_flags = g_mem_scratch_area;
//     D_800D366C = (s32) (g_mem_scratch_area + temp_t7);
//     collision_select_area(2);
// }

/* was func_150038A0 */
void collision_build_quadtrees(void) {
    quadtree_alloc_node_pool();
    quadtree_build_area(0, &g_quadtree0_node_count, &g_quadtree0_leaf_count);
    quadtree_build_area(1, 0, 0);
    quadtree_build_area_flat(2);
    collision_select_area(0);
    collision_load_level_grid();
    g_coll_quadtrees_built = (u8)1;
}

/* was func_1500390C */
s32 texture_table_find(s32 arg0) {
    s32 i;

    for (i = 0; i < 7764; i++) {
        if (arg0 == g_texture_table_ids[i]) {
            return i;
        }
    }
    return -1;
}
