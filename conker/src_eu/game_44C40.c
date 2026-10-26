#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15017790 */
void level_state_clear(void) {
    save_block_realloc_random();
    bzero(g_save_progress_bits, 0x1B);
    bzero(&g_level_state_blk_2e50, 0x10);
    bzero(&D_800D2E60, 9);
    bzero(&g_event_states, 0xCC);
    g_game_over_disabled = (u8)0;
}

/* was func_150177F8 */
void level_state_init(void) {
    event_list_unload(1);
    bzero(&g_event_list, 0xC);
    event_timers_reset();
    g_camera_event_heading = g_level_init_heading_f;
    g_level_state_u8_2e41 = 0xA;
    g_level_state_u8_2e42 = 6;
    D_800D3858 = 0;
    g_game_over_disabled = 0;
}

/* was func_15017868 */
void level_apply_flag_entries(void) {
    u16 *temp_v0;
    s32 i;

    for (i = 0; i < D_800D2F3C; i++) {
        temp_v0 = event_find((s16)D_800D2F40[i]);
        if ((temp_v0 != 0) && ((temp_v0[0] & 0x1000) != 0)) {
            temp_v0[1] = g_level_id;
        }

    }
    event_list_unload(0);
    event_start_level_events(*(((s16*)&g_level_id)+1), 1); // er?
}

u8 **allocate_memory(s32, s32, s32, s32);
void zones_build_overlap_masks(u8 *, u32);
extern s32 D_800D34F0;
extern s32 D_800D3510;
extern u8 **g_camera_zone_list; /* was D_800D3690 */
extern s32 g_camera_zone_count; /* was D_800D3694 */

/* was func_15017930 */
void zones_load(s32 arg0) {
    s32 temp_t9;
    s32 var_a0;
    s32 var_a1;
    s32 var_a1_2;
    u32 temp_lo;
    u32 temp_v0;
    u32 var_a3;
    u32 var_a3_2;
    u8 **temp_v0_3;
    u8 **var_a0_2;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 temp_v0_2;
    u8 temp_v0_4;

    temp_v0 = asset_load_ptr((s32 *) &D_800D34B8, 3, 0xC, arg0, 5);
    temp_lo = temp_v0 / 52U;
    D_800D3094 = (s32) temp_v0;
    D_800D3094 = (s32) temp_lo;
    zones_build_overlap_masks(D_800D34B8, temp_lo);
    g_camera_zone_count = 0;
    g_camera_zone_list = NULL;
    var_a3 = 0;
    if (D_800D3094 != 0) {
        var_a1 = 0;
        do {
            var_a3 += 1;
            temp_v1 = &D_800D34B8[var_a1];
            temp_t9 = (s32) (*(u8 *)((u8 *)temp_v1 + 0x15)) >> 2;
            var_a0 = temp_t9;
            if (temp_t9 == 1) {
                temp_v0_2 = (*(u8 *)((u8 *)temp_v1 + 0x17));
                if (temp_v0_2 != 2) {
                    if (temp_v0_2 != 0) {
                        if (temp_v0_2 == 6) {
                            goto block_6;
                        }
                    } else {
                        goto block_6;
                    }
                } else {
block_6:
                    g_camera_zone_count += 1;
                    var_a0 = (s32) (*(u8 *)((u8 *)temp_v1 + 0x15)) >> 2;
                }
            }
            if (var_a0 != 2) {
                if (var_a0 == 7) {
                    goto block_9;
                }
            } else {
block_9:
                (*(s32 *)((u8 *)temp_v1 + 0x20)) = 0;
            }
            var_a1 += 0x34;
        } while (var_a3 < (u32) D_800D3094);
    }
    if (g_camera_zone_count != 0) {
        temp_v0_3 = allocate_memory(g_camera_zone_count * 4, 1, 0, 0);
        g_camera_zone_list = temp_v0_3;
        if (temp_v0_3 != NULL) {
            var_a0_2 = temp_v0_3;
            var_a3_2 = 0;
            var_a1_2 = 0;
            if (D_800D3094 != 0) {
                do {
                    var_a3_2 += 1;
                    temp_v1_2 = &D_800D34B8[var_a1_2];
                    if (((s32) (*(u8 *)((u8 *)temp_v1_2 + 0x15)) >> 2) == 1) {
                        temp_v0_4 = (*(u8 *)((u8 *)temp_v1_2 + 0x17));
                        if (temp_v0_4 != 2) {
                            if (temp_v0_4 != 0) {
                                if (temp_v0_4 == 6) {
                                    goto block_18;
                                }
                            } else {
                                goto block_18;
                            }
                        } else {
block_18:
                            *var_a0_2 = &D_800D34B8[var_a1_2];
                            var_a0_2 = (u8 * *)((u8 *)var_a0_2 + (4));
                        }
                    }
                    var_a1_2 += 0x34;
                } while (var_a3_2 < (u32) D_800D3094);
            }
        }
    }
    bzero(&D_800D3510, 0x180);
    bzero(&D_800D34F0, 0x20);
}
void trigger_cache_angles(u8 *);
void zone_compute_bbox(u8 *, u8 *);
extern u8 *g_trigger_zones; /* was D_800D34BC */
extern u64 g_zone_always_mask[3]; /* was D_800D34C0 */
extern u64 g_zone_overlap_mask[3]; /* was D_800D34D8 */

/* P43 (level load): per-zone records (0x28 bytes at g_trigger_zones: u64 mask[3], u8 count at +0x18, s16 box x / y / z
 * min-max at +0x1A..+0x24) from zone_compute_bbox for each 0x34-byte zone of arg0; g_zone_always_mask = zones with (+0x15 & 3) == 3
 * or +0x16 & 8 (not +0x16 & 4), g_zone_overlap_mask = the others without 8 / 4; then for every g_zone_overlap_mask zone i the mask of the
 * g_zone_overlap_mask zones j whose box overlaps i's on all three axes (count in +0x18). The 64-bit masks are __ll_lshift calls in
 * the asm (difftest compares the call sequence; the shift itself is the stub). The asm returns no value. */
#define B20_OVL(a, b, lo, hi) \
    ((*(s16 *)((b) + (lo)) >= *(s16 *)((a) + (lo)) && *(s16 *)((b) + (lo)) < *(s16 *)((a) + (hi))) \
     || (*(s16 *)((b) + (lo)) < *(s16 *)((a) + (lo)) && *(s16 *)((a) + (lo)) < *(s16 *)((b) + (hi))) \
     || (*(s16 *)((a) + (lo)) < *(s16 *)((b) + (hi)) && *(s16 *)((b) + (hi)) < *(s16 *)((a) + (hi))))

/* was func_15017B20 */
void zones_build_overlap_masks(u8 *arg0, u32 arg1) {
    s32 n = arg1;
    s32 i, j;
    u8 *e;
    u8 *ri;
    u8 *rj;
    u64 *wi;
    u64 *wj;
    u64 *mi;
    u64 bi, bj;

    g_trigger_zones = (u8 *)allocate_memory(n * 0x28, 1, 1, 0);
    for (i = 0; i < n; i++) {
        trigger_cache_angles(arg0 + i * 0x34);
        zone_compute_bbox(arg0 + i * 0x34, g_trigger_zones + i * 0x28);
    }
    bzero(g_zone_always_mask, 0x18);
    for (i = 0, e = arg0; i < n; i++, e += 0x34) {
        if (((e[0x15] & 3) == 3 || (e[0x16] & 8)) && !(e[0x16] & 4)) {
            g_zone_always_mask[i >> 6] |= (u64)1 << (i & 0x3F);
        }
    }
    bzero(g_zone_overlap_mask, 0x18);
    for (i = 0, e = arg0; i < n; i++, e += 0x34) {
        if ((e[0x15] & 3) != 3 && !(e[0x16] & 8) && !(e[0x16] & 4)) {
            g_zone_overlap_mask[i >> 6] |= (u64)1 << (i & 0x3F);
        }
    }
    wi = g_zone_overlap_mask;
    bi = 1;
    for (i = 0; i < n; i++) {
        ri = g_trigger_zones + i * 0x28;
        ri[0x18] = 0;
        if (*wi & bi) {
            bj = 1;
            wj = g_zone_overlap_mask;
            mi = (u64 *)ri;
            bzero(ri, 0x18);
            for (j = 0; j < n; j++) {
                ri = g_trigger_zones + i * 0x28;
                rj = g_trigger_zones + j * 0x28;
                if ((*wj & bj) && B20_OVL(ri, rj, 0x1A, 0x1C) && B20_OVL(ri, rj, 0x1E, 0x20)
                    && B20_OVL(ri, rj, 0x22, 0x24)) {
                    *mi |= bj;
                    ri[0x18]++;
                }
                bj <<= 1;
                if (bj == 0) {
                    wj++;
                    mi++;
                    bj = 1;
                }
            }
        }
        bi <<= 1;
        if (bi == 0) {
            wi++;
            bi = 1;
        }
    }
}
void mtxf_translate(f32 (*)[4], s32, s32, s32); /* axis as f32 bit patterns (game_D5250.c) */
void mtxf_rotate_xyz_deg(f32 (*)[4], f32, f32, f32);
void mtxf_mul(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void mtxf_transform_point(f32 (*)[4], f32, f32, f32, f32 *, f32 *, f32 *);

/* P64 (level load): bounding box of a 0x34-byte zone (s16 x / y / z at +0, size +6 / +8 / +0xA, f32 angles +0xC /
 * +0x10, shape = +0x15 & 3) into the 0x28-byte zone record `out` (s16 min x / max x / min y / max y / min z / max z
 * at +0x1A..+0x24). Shape 0: cylinder-like (size6, size8 / 2, size6), 1: cube (size6), 2: box (size6, size8 / 2,
 * sizeA), each rotated by mtxf_translate / mtxf_rotate_xyz_deg except shape 1; shape 3 gives the point box. The eight
 * corners (+-1, +-1, +-1) of the transformed unit cube are taken; min / max start at 0, so the box always holds the
 * zone origin, and a corner only raises the max when it did not lower the min (as the asm does). */
/* was func_15017FA4 */
void zone_compute_bbox(u8 *zone, u8 *out) {
    f32 rot[4][4];
    f32 m[4][4];
    f32 cx, cy, cz;
    f32 px, py, pz;
    s32 point_only = FALSE;
    s32 min_x = 0, max_x = 0, min_y = 0, max_y = 0, min_z = 0, max_z = 0;
    s32 i;
    union {
        f32 f;
        s32 bits;
    } sx, sy, sz; /* functions.h declares mtxf_scale (scale matrix) with s32 arguments: f32 bit patterns */

    switch (zone[0x15] & 3) {
        case 0:
            mtxf_translate(rot, 0, 0x3F800000, 0); /* (0, 1.0f, 0) */
            sx.f = *(s16 *)(zone + 6);
            sy.f = *(s16 *)(zone + 8) * 0.5f;
            sz.f = *(s16 *)(zone + 6);
            mtxf_scale(m, sx.bits, sy.bits, sz.bits);
            mtxf_mul(rot, m, m);
            mtxf_rotate_xyz_deg(rot, *(f32 *)(zone + 0xC), *(f32 *)(zone + 0x10), 0.0f);
            mtxf_mul(m, rot, m);
            break;
        case 1:
            sx.f = *(s16 *)(zone + 6);
            sy.f = *(s16 *)(zone + 6);
            sz.f = *(s16 *)(zone + 6);
            mtxf_scale(m, sx.bits, sy.bits, sz.bits);
            break;
        case 2:
            mtxf_translate(rot, 0, 0x3F800000, 0); /* (0, 1.0f, 0) */
            sx.f = *(s16 *)(zone + 6);
            sy.f = *(s16 *)(zone + 8) * 0.5f;
            sz.f = *(s16 *)(zone + 0xA);
            mtxf_scale(m, sx.bits, sy.bits, sz.bits);
            mtxf_mul(rot, m, m);
            mtxf_rotate_xyz_deg(rot, *(f32 *)(zone + 0xC), *(f32 *)(zone + 0x10), 0.0f);
            mtxf_mul(m, rot, m);
            break;
        default:
            point_only = TRUE;
            break;
    }

    if (!point_only) {
        for (i = 0; i < 8; i++) {
            cx = (i & 1) ? 1.0f : -1.0f;
            cy = (i & 2) ? 1.0f : -1.0f;
            cz = (i & 4) ? 1.0f : -1.0f;
            mtxf_transform_point(m, cx, cy, cz, &px, &py, &pz);
            if (px < min_x) {
                min_x = px;
            } else if (max_x < px) {
                max_x = px;
            }
            if (py < min_y) {
                min_y = py;
            } else if (max_y < py) {
                max_y = py;
            }
            if (pz < min_z) {
                min_z = pz;
            } else if (max_z < pz) {
                max_z = pz;
            }
        }
    }
    *(s16 *)(out + 0x1A) = *(s16 *)(zone + 0) + min_x;
    *(s16 *)(out + 0x1C) = *(s16 *)(zone + 0) + max_x;
    *(s16 *)(out + 0x1E) = *(s16 *)(zone + 2) + min_y;
    *(s16 *)(out + 0x20) = *(s16 *)(zone + 2) + max_y;
    *(s16 *)(out + 0x22) = *(s16 *)(zone + 4) + min_z;
    *(s16 *)(out + 0x24) = *(s16 *)(zone + 4) + max_z;
}
