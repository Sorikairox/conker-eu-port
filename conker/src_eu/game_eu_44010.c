#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void *allocate_memory(s32, s32, s32, s32);
u32 asset_load_into(u8 *, s32, s32, s32, s32);
s32 asset_get_size(s32, s32, s32);
void level_entry_data_load(s32);
u8 setup_next_free_id(s32, s32);
void setup_entries_spawn_range(s32, s32, s32);
s32 warp_request_cancel(s32);
extern u8 D_1A3750[];
extern u8 D_1A3840[];
extern u8 D_1A3B40[];
extern s32 g_obj_update_counter; /* was D_800D1968 */
extern u8 g_setup_level_first; /* was D_800D2521 */
extern u8 *g_setup_entry_flags; /* was D_800D252C */


extern u8 g_setup_type_count; /* was D_800BE9B0 */
extern u16 g_setup_type_ids; /* was D_800BE9B8 */
extern s32 g_setup_type_sound_tables; /* was D_800BE9C8 */
extern u8 g_setup_entry_count; /* was D_800D2520 */

/* was func_15016800 */
void setup_load_type_assets(void) {
    struct {
        s32 u50;
    } sp;
    s32 var_a1;
    s32 var_s1;
    s32 var_v0;
    s32 var_v1;
    u16 *var_v1_2;
    u8 temp_a2;
    u8 temp_s0;

    g_setup_type_count = 0;
    temp_a2 = g_setup_entry_count;
    sp.u50 = 0;
    var_s1 = 0;
    if ((s32) temp_a2 > 0) {
        do {
            var_a1 = 0;
            temp_s0 = g_setup_entries->pad4[var_s1];
            var_v0 = 0;
            if ((s32) g_setup_type_count > 0) {
                var_v1_2 = &g_setup_type_ids;
loop_4:
                var_v0 += 1;
                if (temp_s0 == *var_v1_2) {
                    var_a1 = 1;
                } else {
                    var_v1_2 += 2;
                    if (var_v0 < (s32) g_setup_type_count) {
                        goto loop_4;
                    }
                }
            }
            if (var_a1 != 0) {
                var_v1 = temp_a2 * 0x30;
            } else {
                if ((s32) temp_s0 < 0xBB) {
                    asset_load_ptr(&sp.u50, 2, 0x12, temp_s0);
                }
                var_v1 = temp_a2 * 0x30;
                if (sp.u50 != 0) {
                    *(s32 *)((u8 *)&g_setup_type_sound_tables + (g_setup_type_count * 4)) = sp.u50;
                    (&g_setup_type_ids)[g_setup_type_count] = (u16) temp_s0;
                    g_setup_type_count += 1;
                }
            }
            var_s1 += 0x30;
        } while (var_s1 < var_v1);
    }
}
/* P36: level setup load (level arg0). DMAs the fixed player-slot setup table (ROM D_1A3840..D_1A3B40 for the
 * multiplayer-style levels 0x1A / 0x24 / 0x2B / 0x2D / 0x30 / 0x33 / 0x34 / 0x3F, else D_1A3750..D_1A3840) into
 * g_setup_entries (allocated with room for the level's setup asset (2, 0xE, level) from asset_get_size), g_setup_level_first =
 * g_setup_entry_count = its entry count (0x30 bytes each), then appends the level's entries (asset_load_into) and counts them in
 * g_setup_entry_count; level_entry_data_load(level); allocates + clears g_setup_entry_flags (spawned flags, 1 byte each) and g_setup_respawn_timers (respawn
 * timers, u16); g_obj_update_counter = 0. Each player slot i < g_player_count enabled in the mask g_player_active_mask gets e[2] = 0, a type
 * byte e[4] (and extra fields) from its character player_stat_get(i, 1), flag 0x4000000 in levels 0x32 / 0x33, and the
 * position / angle of object g_objects[i]; disabled slots get e[2] = 1. setup_load_type_assets(); entries with e[0x28] == 0
 * get setup_next_free_id(count, i). Finally the player slots are spawned (setup_entries_spawn_range(level, 1, 1)), warp_request_cancel(0),
 * then the other entries (setup_entries_spawn_range(level, 1, 0)). */
/* was func_15016950 */
void level_setup_load(s32 arg0) {
    u8 *tbl;
    u8 *tblEnd;
    u32 size;
    u32 n;
    s32 cnt;
    s32 i;
    s32 off;
    s32 ch;
    u8 *e;
    u8 *obj;

    model_kind_tables_clear();
    switch (arg0) {
        case 0x1A:
        case 0x24:
        case 0x2B:
        case 0x2D:
        case 0x30:
        case 0x33:
        case 0x34:
        case 0x3F:
            tbl = D_1A3840;
            tblEnd = D_1A3B40;
            break;
        default:
            tbl = D_1A3750;
            tblEnd = D_1A3840;
            break;
    }
    size = tblEnd - tbl;
    g_setup_entries = allocate_memory(asset_get_size(2, 0xE, arg0) + size, 1, 2, 0);
    rom_dma_read((s32) tbl, (void *) g_setup_entries, size, 1);
    n = size / 0x30;
    g_setup_entry_count = n;
    g_setup_level_first = n & 0xFF;
    g_setup_entry_count += asset_load_into((u8 *) g_setup_entries + (n & 0xFF) * 0x30, 0, 2, 0xE, arg0) / 0x30;
    level_entry_data_load(arg0);
    cnt = g_setup_entry_count;
    g_setup_entry_flags = allocate_memory(cnt, 1, 0, 0);
    g_setup_respawn_timers = allocate_memory(cnt * 2, 1, 0, 0);
    bzero(g_setup_entry_flags, cnt);
    bzero(g_setup_respawn_timers, cnt * 2);
    g_obj_update_counter = 0;
    for (i = 0, off = 0; i < g_player_count; i++, off += 0x30) {
        if (((1 << i) & (u16) g_player_active_mask) == 0) {
            ((u8 *) g_setup_entries)[off + 2] = 1;
            continue;
        }
        ch = player_stat_get((s16) i, 1);
        e = (u8 *) g_setup_entries + off;
        e[2] = 0;
        if ((u32) ch < 41) {
            switch (ch) {
                case 0:
                    if (g_level_id == 0x36 || g_level_id == 0x3A || g_level_id == 0x40) {
                        e[4] = 0x96;
                    } else {
                        e[4] = 0;
                    }
                    break;
                case 16:
                    e[4] = 0x96;
                    break;
                case 1:
                    e[4] = 0x3B;
                    break;
                case 2:
                    e[4] = 0x98;
                    break;
                case 3:
                    e[4] = 0x75;
                    break;
                case 4:
                    e[4] = 0x80;
                    break;
                case 37:
                    e[4] = 0xB0;
                    *(f32 *) (e + 0x24) = 0.6f;
                    *(f32 *) (e + 0x20) = *(f32 *) (e + 0x24);
                    break;
                case 38:
                    e[4] = 0xB1;
                    *(f32 *) (e + 0x24) = 0.6f;
                    *(f32 *) (e + 0x20) = *(f32 *) (e + 0x24);
                    break;
                case 39:
                    e[4] = 0xB2;
                    break;
                case 40:
                    e[4] = 0xB4;
                    break;
                case 33:
                    e[4] = 0x9F;
                    break;
                case 34:
                    e[4] = 0xA0;
                    break;
                case 11:
                    e[4] = 0x88;
                    break;
                case 35:
                    e[4] = 0x9B;
                    e[3] = 0x15;
                    break;
                case 36:
                    e[4] = 0x9A;
                    e[3] = 0x15;
                    break;
                case 17: case 18: case 19: case 20: case 21: case 22:
                case 23: case 24: case 25: case 26: case 27: case 28:
                    e[4] = 0x9C;
                    break;
                case 29: case 30: case 31: case 32:
                    e[4] = 0x9D;
                    break;
                case 12: case 13: case 14: case 15:
                    e[4] = 0x90;
                    if (i < g_human_player_count) {
                        e[3] = 1;
                    } else {
                        e[3] = 0xC;
                    }
                    *(s32 *) (e + 0x18) |= 4;
                    e[0xD] = 0xD;
                    break;
                case 8:
                    e[4] = 0x77;
                    e[3] = 0x1E;
                    e[0x10] = 0xAA;
                    if (i < g_human_player_count) {
                        e[0xD] = 1;
                    } else {
                        e[0xD] = 3;
                    }
                    *(s32 *) (e + 0x18) |= 0x180000;
                    e[0xE] |= 0x80;
                    break;
                case 10:
                    e[4] = 0x77;
                    e[3] = 0x25;
                    e[0x10] = 0xA8;
                    e[0xD] = 3;
                    *(s32 *) (e + 0x18) |= 0x100000;
                    break;
                case 9:
                    e[4] = 0x53;
                    e[3] = 0x1F;
                    e[0x10] = 0xA8;
                    e[0xD] = 2;
                    *(f32 *) (e + 0x20) = 0.7f;
                    *(f32 *) (e + 0x24) = 0.7f;
                    *(s32 *) (e + 0x18) |= 1;
                    break;
            }
        }
        if (g_level_id == 0x33 || g_level_id == 0x32) {
            *(s32 *) (e + 0x18) |= 0x4000000;
        }
        obj = (u8 *) g_objects + i * 0x32C;
        *(s16 *) (e + 6) = (s32) *(f32 *) (obj + 0x14);
        *(s16 *) (e + 8) = (s32) *(f32 *) (obj + 0x18);
        *(s16 *) (e + 0xA) = (s32) *(f32 *) (obj + 0x1C);
        e[0xC] = *(u16 *) (obj + 0x76) >> 8;
    }
    setup_load_type_assets();
    for (i = 0, off = 0; i < g_setup_entry_count; i++, off += 0x30) {
        if (((u8 *) g_setup_entries)[off + 0x28] == 0) {
            ((u8 *) g_setup_entries)[off + 0x28] = setup_next_free_id(g_setup_entry_count, i);
        }
    }
    setup_entries_spawn_range(arg0, 1, 1);
    warp_request_cancel(0);
    setup_entries_spawn_range(arg0, 1, 0);
}
/* g_setup_entry_count: setup entry count, g_setup_level_first: first entry of the level's own part; g_path_points (EU 0x800D2524, s32 *
 * in variables.h): per entry its data block; g_path_point_counts: per entry the block's kind byte; g_player_count (EU
 * 0x8009012C): player slot count. */

// level_entry_data_load: allocates and clears the per-entry block pointers g_path_points and kind bytes g_path_point_counts for
// the g_setup_entry_count setup entries; each player slot (i < g_player_count) gets a zeroed 16-byte block of kind 2. Then the
// level's asset (2, 0x10, level) gives 8-byte records {offset, kind} for the entries from g_setup_level_first on: a record
// with a non-zero offset sets the entry's kind (low byte) and its block = asset + offset.
/* was func_150170C4 */
void level_entry_data_load(s32 level) {
    u8 *asset = NULL;
    u32 *rec;
    s32 n = g_setup_entry_count;
    s32 i;
    u8 **blocks;

    g_path_points = allocate_memory(n * 4, 1, 0, 0);
    g_path_point_counts = allocate_memory(n, 1, 0, 0);
    bzero(g_path_points, n * 4);
    bzero(g_path_point_counts, n);
    for (i = 0; i < g_player_count; i++) {
        blocks = (u8 **) g_path_points;
        blocks[i] = allocate_memory(0x10, 1, 2, 0);
        bzero(((u8 **) g_path_points)[i], 0x10);
        g_path_point_counts[i] = 2;
    }
    if (asset_load_ptr((s32 *) &asset, 2, 0x10, level) == 0) {
        return;
    }
    for (i = g_setup_level_first; i < g_setup_entry_count; i++) {
        rec = (u32 *) (asset + (i - g_setup_level_first) * 8);
        if (rec[0] != 0) {
            g_path_point_counts[i] = rec[1];
            ((u8 **) g_path_points)[i] = asset + rec[0];
        }
    }
}
