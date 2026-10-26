#include <ultra64.h>

#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
extern s32 *D_800B1240;
extern u8 *D_800B1244;
u8 *allocate_memory(s32, s32, s32, s32);
extern u8 D_800B1248;
extern s32 D_800B1214[];
extern s32 D_800B1224[];
extern s32 D_800B1254[];
extern s32 D_800B1260;
extern s32 D_800B1220[];
extern s32 D_800B1250[];
extern s32 D_800B1230[];
extern s32 *D_80082EB0[];
s32 asset_load_with_subfiles(s32 *, s32, s32 *, s32, ...);
void gfx_dl_relocate_segments(Gfx *, s32, s32);
s32 texture_resolve_dl_ids(Gfx *, s32, s32, s32, s16 **);
s32 texture_cache_lookup(s32, s32 *, s32, s32);


// what is this loop doing?
/* Relocates a level model's {ptr, ptr, x} table (12-byte entries, ends at ptr0 == 0) by base: the table
 * pointer goes to D_800B1240[idx] (made absolute when non-zero) and its entry count to D_800B1244[idx]. */
/* was func_15003120 */
void level_model_relocate_table(s32 idx, s32 base, s32 table) {
    s32 n;
    s32 off;
    s32 *e;

    D_800B1240[idx] = table;
    D_800B1244[idx] = 0;
    if (table == 0) {
        return;
    }
    D_800B1240[idx] += base;
    n = 0;
    off = 0;
    e = (s32 *)D_800B1240[idx];
    if (e[0] != 0) {
        do {
            e[0] += base;
            n++;
            e = (s32 *)(D_800B1240[idx] + off);
            off += 12;
            e[1] += base;
            e = (s32 *)(D_800B1240[idx] + off);
        } while (e[0] != 0);
    }
    D_800B1244[idx] = n;
}
/* Level model loader: asset (2, 4, level) is a list of count {model header, size} pairs. Each header's
 * offsets +0 (display list), +8, +0x10 are made absolute, its {ptr, ptr, x} table at +0x20 is relocated by
 * level_model_relocate_table (D_800B1240 / D_800B1244). Parts 0..3 also set D_800B0E00[i] (level DL), D_800B1220[i]
 * (vertex base = header + 0x28), D_800B1250[i] (vertex count = (DL - vertices) / 16), D_800B1230[i] (+8);
 * part 0 calls collision_set_tri_flags_table(+0x10). Then the level's texture preload list D_80082EB0[D_800B0DF0->0x4B]
 * (age 0x3E). Allocations: count * 4 bytes (D_800B1240) and count bytes (D_800B1244), both
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
    D_800B1260 = (s32)ent;
    p = D_800B1214;
    q = D_800B1224;
    r = D_800B1254;
    do {
        *p++ = 0;
        *q++ = 0;
        *r++ = 0;
    } while (r != &D_800B1260);
    texture_table_reset();
    if (found != 0) {
        D_800B1240 = (s32 *)allocate_memory(count * 4, 1, 0, 0);
        D_800B1244 = (u8 *)allocate_memory(count, 1, 0, 0);
        bzero(D_800B1244, count);
        bzero(D_800B1240, count);
        D_800B1248 = count;
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
                D_800B1220[i] = (s32)(hdr + 0x28);
                D_800B0E00[i] = *(s32 *)(hdr + 0x0);
                D_800B1250[i] = (u32)(*(s32 *)(hdr + 0x0) - (s32)(hdr + 0x28)) >> 4;
                D_800B1230[i] = *(s32 *)(hdr + 0x8);
                if (i == 0) {
                    collision_set_tri_flags_table(*(s32 *)(hdr + 0x10));
                }
                gfx_dl_relocate_segments((Gfx *)D_800B0E00[i], D_800B1220[i] + 0xFF000000, (s32)hdr);
                texture_resolve_dl_ids((Gfx *)D_800B0E00[i], 0, 1, 0x3F, NULL);
            } else {
                gfx_dl_relocate_segments((Gfx *)*(s32 *)(hdr + 0x0), 0, (s32)hdr);
            }
        }
    }
    if (((u8 *)D_800B0DF0)[0x4B] != 0) {
        id = D_80082EB0[((u8 *)D_800B0DF0)[0x4B]][0];
        off = 4;
        while (id != 0) {
            texture_cache_lookup(id, &size, 0x3E, 0);
            id = *(s32 *)((u8 *)D_80082EB0[((u8 *)D_800B0DF0)[0x4B]] + off);
            off += 4;
        }
    }
}
/* was func_150034B4 */
s32 texture_table_reset(void) {
      s32 i;

      for (i = 0; i < 7764; i++) {
          D_800B0E58[i] = -1;
          D_800BC448[i] = 0;
      }

      D_800D9F58 = 0xFFFF; // -1 s16?
      D_800D9F5C = -1;

      if ((D_800BE9F0 != 1) && (D_800BE9F0 != 50)) {
          D_800D9F60 = 0;
      } else {
          D_800D9F60 = 1;
      }
}

u8 *allocate_memory(s32, s32, s32, s32);
void heap_free(s32);
extern u8 D_1A3B40[];
extern u16 D_800920D0[];
extern s16 D_800B8BB8[];

/* build a table of 16-bit words read from ROM: for each entry, DMA 16 bytes at the (even-aligned) ROM
   position, take the big-endian halfword at offset 2 from the real (possibly odd) position, then advance
   by the entry's length */
/* was func_15003570 */
void texture_build_size_table(void) {
    u8 *buf = allocate_memory(0x10, 1, 2, 0);
    u32 rom = (u32)D_1A3B40;
    u16 *len = D_800920D0;
    s16 *out = D_800B8BB8;
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
    } while (out != (s16 *)D_800BC860);
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
extern s32 D_800D304C;
extern s8 D_800D3088;
extern s32 D_800D3720;
extern s32 D_800D3A8C;
extern s32 D_800DC26C;

/* was func_15003668 */
void collision_build_level_tris(s32 arg0) {
    s32 temp_s3;
    s32 temp_t7;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    D_800DBE62 = 0;
    collision_build_reset();
    D_800D3088 = 0;
    collision_begin_area(0);
    collision_count_dl_tris((*(s32 *)((u8 *)D_800B0E00 + 0)));
    collision_alloc_area_arrays();
    collision_scan_level_dl((*(s32 *)((u8 *)D_800B0E00 + 0)));
    collision_end_area(0);
    collision_begin_area(1);
    collision_count_dl_tris((*(s32 *)((u8 *)D_800B0E00 + 0xC)));
    collision_alloc_area_arrays();
    collision_scan_level_dl((*(s32 *)((u8 *)D_800B0E00 + 0xC)));
    collision_end_area(1);
    collision_begin_area(2);
    var_s1 = 0;
    var_s0 = 0;
    if (D_800DC320 > 0) {
        do {
            temp_v0 = &D_800DBEF4->pad[var_s0];
            if (((*(u8 *)((u8 *)temp_v0 + 0x4F)) & 0x60) != 0x20) {
                collision_count_dl_tris((*(s32 *)((u8 *)temp_v0 + 0x1C)));
            }
            var_s1 += 1;
            var_s0 += 0xA0;
        } while (var_s1 < D_800DC320);
        var_s1 = 0;
    }
    collision_alloc_area_arrays();
    D_800D3088 = 1;
    D_800D304C = 0;
    var_s0_2 = 0;
    if (D_800DC320 > 0) {
        do {
            temp_v0_2 = &D_800DBEF4->pad[var_s0_2];
            if (((*(u8 *)((u8 *)temp_v0_2 + 0x4F)) & 0x60) != 0x20) {
                temp_s3 = D_800DBE38;
                (*(s16 *)((u8 *)temp_v0_2 + 0x58)) = (s16) temp_s3;
                collision_scan_level_dl((*(s32 *)((u8 *)(&D_800DBEF4->pad[var_s0_2]) + 0x1C)));
                (*(s16 *)((u8 *)(&D_800DBEF4->pad[var_s0_2]) + 0x56)) = (s16) (D_800DBE38 - temp_s3);
            } else {
                (*(s16 *)((u8 *)temp_v0_2 + 0x58)) = 0;
                (*(s16 *)((u8 *)(&D_800DBEF4->pad[var_s0_2]) + 0x56)) = 0;
            }
            var_s1 += 1;
            var_s0_2 += 0xA0;
        } while (var_s1 < D_800DC320);
    }
    collision_end_area(2);
    D_800D3088 = 0;
    (*(s32 *)((u8 *)(&D_800D3720) + 0)) = 0;
    (*(s32 *)((u8 *)(&D_800D3720) + 4)) = (s32) (D_800DC26C << 8);
    collision_select_area(0);
    temp_t7 = (collision_max_area_tris() + 7) & ~7;
    D_800D3668 = (s32) D_8003809C;
    D_800D3A8C = D_8003809C + temp_t7;
    collision_select_area(2);
}
// NON-MATCHING: 40% there
// void collision_build_level_tris(s32 arg0) {
//     struct131 *temp_v0_2;
//     s32 temp_t7;
//     s32 i;
//     s32 tmp0;
//
//     D_800DBE62 = (u8)0;
//     collision_build_reset();
//     D_800D2C68 = (u8)0;
//     collision_begin_area(0);
//     collision_count_dl_tris(D_800B0E00[0]); // ->unk0
//     collision_alloc_area_arrays();
//     collision_scan_level_dl(D_800B0E00[0]); // ->unk0
//     collision_end_area(0);
//     collision_begin_area(1);
//     collision_count_dl_tris(D_800B0E00[3]);
//     collision_alloc_area_arrays();
//     collision_scan_level_dl(D_800B0E00[3]);
//     collision_end_area(1);
//     collision_begin_area(2);
//
//     if (D_800DBEF0 > 0) {
//         for (i = 0; i < D_800DBEF0; i++) {
//             temp_v0_2 = &D_800DBEF4[i];
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
//         temp_v0_2 = &D_800DBEF4[i];
//         if (((u8)temp_v0_2->unk4F & 0x60) != 32) {
//             temp_v0_2->unk58 = D_800DBE38;
//             temp_v0_2->unk56 = 0; //D_800DBE38 - D_800DBE38;
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
//     D_800D3668 = D_8003809C;
//     D_800D366C = (s32) (D_8003809C + temp_t7);
//     collision_select_area(2);
// }

/* was func_150038A0 */
void collision_build_quadtrees(void) {
    quadtree_alloc_node_pool();
    quadtree_build_area(0, &D_800DBE2A, &D_800DBE2C);
    quadtree_build_area(1, 0, 0);
    quadtree_build_area_flat(2);
    collision_select_area(0);
    collision_load_level_grid();
    D_800DBE62 = (u8)1;
}

/* was func_1500390C */
s32 texture_table_find(s32 arg0) {
    s32 i;

    for (i = 0; i < 7764; i++) {
        if (arg0 == D_800B0E58[i]) {
            return i;
        }
    }
    return -1;
}
