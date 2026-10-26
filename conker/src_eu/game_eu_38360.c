#include <ultra64.h>

#include "functions.h"
#include "variables.h"

/* was func_1500ABA0 */
void ambient_sounds_reset(s32 arg0) {
    bzero(&g_ambient_slot_ids, 60);
    asset_load_into(&g_ambient_slot_ids, 60, 3, 12, arg0, 10);
    bzero(&g_ambient_voices, 240);
    bzero(&g_ambient_slots, 1560);
}

extern u16 g_ambient_slot_emitter_count[];  /* per ambient sound: loaded even when it is not id 0x3B; was D_800BE898 */
extern s16 g_ambient_slot_tc[];  /* per ambient sound: 2 x s16; was D_800DDFB0 */
extern u8 g_ambient_sound_info[];   /* per sound id, 10 bytes: +2 u16 length, +8 u8 rate (asm rodata_inject block; ROM); was D_80096090 */
u8 *asset_lookup_rom(s32 *arg0, s32 arg1, ...);

// ambient_sounds_load: for each of the 15 ambient sound slots (ids at g_ambient_slot_ids, 4-byte stride; 0xFF = empty)
// clears its voice record (g_ambient_voices, 16 bytes) and, when g_ambient_slot_emitter_count[slot] is set or the id is 0x3B, loads the
// sample (asset_lookup_rom kind 2) into +0 with the 16-byte rounded size in +4 (+0 = NULL when the size or the id's
// length is 0), and sets g_ambient_slot_tc[slot] = { rate * 32 - 1, (length / rate) * 64 / 5 - 1 } (unsigned divisions;
// rate 0 traps like the asm's divu check).
/* was func_1500AC14 */
void ambient_sounds_load(void) {
    u8 *voice = (u8 *) &g_ambient_voices;
    u16 *ids = (u16 *) &g_ambient_slot_ids;
    s16 *timing;
    u8 *info;
    s32 slot;
    u32 id;
    s32 size;
    u8 *data;
    u32 length;
    u32 rate;

    for (slot = 0; slot < 15; slot++, voice += 0x10, ids += 2) {
        id = *ids;
        *(s32 *) (voice + 0) = 0;
        *(s32 *) (voice + 8) = 0;
        *(s32 *) (voice + 4) = 0;
        voice[0xC] = 0;
        if (id == 0xFF) {
            continue;
        }
        if (g_ambient_slot_emitter_count[slot] == 0 && id != 0x3B) {
            continue;
        }
        timing = &g_ambient_slot_tc[slot * 2];
        data = asset_lookup_rom(&size, 2, 0, id);
        info = &g_ambient_sound_info[id * 10];
        *(u8 **) (voice + 0) = data;
        *(s32 *) (voice + 4) = (size + 15) & ~15;
        length = *(u16 *) (info + 2);
        if (size == 0 || length == 0) {
            length = 0;
            *(s32 *) (voice + 0) = 0;
        }
        rate = info[8];
        timing[0] = (rate << 5) - 1;
        timing[1] = (((length / rate) << 6) / 5) - 1;
    }
}
// GOTO hell
/* P180: level-load ambient sound emitters (ambient_emitters_build unit). Emitter records: g_ambient_emitters, 14 bytes each. */
typedef struct {
    s16 x, y, z;    /* +0 position */
    u8 slotMode;    /* +6: mode << 5 | slot */
    u8 phase;       /* +7: slot * 4 + phase (0..3), or 0x3C for one-shot slots */
    u8 id;          /* +8: sound id of the slot */
    u8 pad9;
    u8 kind;        /* +0xA: row index of the placement (triangle flag bits 20-22) */
    u8 unkB;        /* +0xB: cleared after placement */
    u8 unkC;        /* +0xC / +0xD: per-emitter scaled slot parameters (g_ambient_slot_params) */
    u8 unkD;
} AmbientEmitter;
typedef s32 (*AmbientPlacer)(s16 param, u8 kind, s32 slot, s32 mode, s32 index, s16 **tri);
extern AmbientEmitter *g_ambient_emitters; /* was D_800DE148 */
extern u8 g_ambient_phase_period[];      /* per slot: random phase range (sound info +1); was D_800DE000 */
extern u8 g_ambient_flare_frame[];      /* per slot; was D_800DE010 */
extern u8 g_ambient_quad_flag[];      /* per slot: 2 when sound info flag 0x80, else 1; was D_800DE020 */
extern u8 g_ambient_phase_dir_bits[];      /* per slot: random byte; was D_800DE040 */
extern u8 g_ambient_slot_bytes[];      /* per slot: 2 bytes (g_ambient_slot_defaults[slot]); was D_80096074; was D_800DE050 */
extern u8 g_ambient_placement_row[];      /* per slot: placement row (flags & 0x7F); was D_800DE0B0 */
extern u16 g_ambient_phases[];     /* 60 = 15 slots x 4: random start offsets << 8; was D_800DE0C0 */
extern u8 g_ambient_slot_sound_ids[];      /* per slot: sound id; was D_800DDFF0 */
extern s16 g_ambient_slot_params[];     /* per slot: 2 x s16 (sound info +4 / +6); was D_800BE858 */
extern u16 g_ambient_shape_phase_bits;       /* per slot alternating bit (shape placer); was D_800BE850 */
extern u8 g_ambient_slot_defaults[];      /* per slot (ROM); was D_80096074 */
extern f32 g_ambient_tri_uv_points[][2];  /* (u, v) triangle coordinates for the point placers (ROM); was D_80096014 */
extern f32 *g_ambient_shape_points[];    /* shape placer point lists: [0] = pair count, then (x, z) offsets (ROM); was D_80083110 */
extern f32 g_tri_plane_nx;       /* plane of the last tri_compute_plane triangle: a x + b y + c z = d; was D_800CC630 */
extern f32 g_tri_plane_ny; /* was D_800CC634 */
extern f32 g_tri_plane_nz; /* was D_800CC638 */
extern f32 g_tri_plane_d; /* was D_800CC63C */
extern s32 g_ambient_sort_by_z;       /* ambient_emitters_sort sort key: 0 = x, else z; was D_8008D254 */
extern struct { AmbientPlacer place; void *update; s32 unk8; } g_ambient_placer_fns[];  /* placers by type (.game_data); was D_8008D258 */
extern s16 g_ambient_placement_rows[][8][2];  /* per placement row and kind: { placer type, placer param } (.game_data); was D_8008D2A0 */
extern s32 g_level_tri_table;       /* level triangle table: 3 vertex pointers per triangle; was D_800DC26C */
s32 game_gu_random(void);
void *allocate_memory(s32 size, s32 arg1, s32 arg2, s32 arg3);
void collision_select_area(s32 arg0);
void tri_compute_plane(s32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2);
void ambient_emitters_sort(s32 lo, s32 hi);
s32 ambient_emitter_add(u32 index, s32 slot, s32 mode, s16 x, s16 y, s16 z, s32 spread, u8 kind, s32 phase);

// ambient_slot_setup: sets up ambient sound slot `slot` for sound `id` (0xFF = empty) from its 10-byte sound info
// (g_ambient_sound_info): phase range g_ambient_phase_period (+1; minus 1 and also g_ambient_flare_frame when info flag 0x10), g_ambient_quad_flag (2 when
// flag 0x80), the two slot parameters g_ambient_slot_params (+4 / +6), the id, the placement row (flags & 0x7F, bit 0x80 sets
// the slot's g_ambient_alt_phase_slots bit), g_ambient_pingpong_slots / g_ambient_slow_random_slots bits from info flags 1 / 8; always clears the slot's
// emitter count g_ambient_slot_emitter_count and sets both g_ambient_slot_bytes bytes to g_ambient_slot_defaults[slot].
/* was func_1500AD84 */
void ambient_slot_setup(s32 slot, s32 id, s32 flags) {
    u8 *info;
    u8 infoFlags;
    u8 b;

    if (id != 0xFF) {
        info = &g_ambient_sound_info[id * 10];
        infoFlags = info[0];
        g_ambient_phase_period[slot] = info[1];
        if (infoFlags & 0x10) {
            g_ambient_phase_period[slot] = info[1] - 1;
            g_ambient_flare_frame[slot] = info[1] - 1;
        } else {
            g_ambient_flare_frame[slot] = 0;
        }
        if (infoFlags & 0x80) {
            g_ambient_quad_flag[slot] = 2;
        } else {
            g_ambient_quad_flag[slot] = 1;
        }
        g_ambient_slot_params[slot * 2 + 0] = *(s16 *) (info + 4);
        g_ambient_slot_params[slot * 2 + 1] = *(s16 *) (info + 6);
        g_ambient_slot_sound_ids[slot] = id;
        g_ambient_placement_row[slot] = flags & 0xFF7F;
        if (flags & 0x80) {
            g_ambient_alt_phase_slots |= 1 << slot;
        }
        if (infoFlags & 1) {
            g_ambient_pingpong_slots |= 1 << slot;
        }
        if (infoFlags & 8) {
            g_ambient_slow_random_slots |= 1 << slot;
        }
    } else {
        g_ambient_phase_period[slot] = 0;
    }
    b = g_ambient_slot_defaults[slot];
    g_ambient_slot_emitter_count[slot] = 0;
    g_ambient_slot_bytes[slot * 2 + 0] = b;
    g_ambient_slot_bytes[slot * 2 + 1] = b;
}

// ambient_emitter_add: writes emitter `index` (g_ambient_emitters, 14 bytes) of slot `slot` at (x, y, z) and returns
// index + 1; when index is not below the level's emitter capacity - 1 (g_level_header +0x18) nothing is written and
// the capacity - 1 is returned. Phase byte: 0x3C for slots with a range below 2, else slot * 4 + (phase & 1) for
// g_ambient_alt_phase_slots slots or slot * 4 + (index & 3). +0xC / +0xD = the slot parameters scaled by a random factor
// (0x100 + rand % spread, the second one + 4 * (rand % spread) more when the sound info has flag 4) >> 10, or
// the parameters >> 2 when spread is 0.
/* was func_1500AF08 */
s32 ambient_emitter_add(u32 index, s32 slot, s32 mode, s16 x, s16 y, s16 z, s32 spread, u8 kind, s32 phase) {
    s32 limit = *(u16 *) ((u8 *) g_level_header + 0x18) - 1;
    AmbientEmitter *e;
    s16 scale;
    s16 *param;

    if (!(index < (u32) limit)) {
        return limit;
    }
    g_ambient_emitters[index].x = x;
    g_ambient_emitters[index].y = y;
    g_ambient_emitters[index].z = z;
    if (g_ambient_phase_period[slot] >= 2) {
        if (g_ambient_alt_phase_slots & (1 << slot)) {
            g_ambient_emitters[index].phase = slot * 4 + (phase & 1);
        } else {
            g_ambient_emitters[index].phase = (index & 3) + slot * 4;
        }
    } else {
        g_ambient_emitters[index].phase = 0x3C;
    }
    g_ambient_emitters[index].slotMode = (mode << 5) | slot;
    g_ambient_emitters[index].kind = kind;
    g_ambient_emitters[index].id = g_ambient_slot_sound_ids[slot];
    param = &g_ambient_slot_params[slot * 2];
    if (spread != 0) {
        scale = game_gu_random() % spread + 0x100;
        g_ambient_emitters[index].unkC = (param[0] * scale) >> 10;
        if (g_ambient_sound_info[g_ambient_slot_sound_ids[slot] * 10] & 4) {
            scale = (game_gu_random() % spread) * 4 + scale;
        }
        g_ambient_emitters[index].unkD = (param[1] * scale) >> 10;
    } else {
        g_ambient_emitters[index].unkC = param[0] >> 2;
        g_ambient_emitters[index].unkD = param[1] >> 2;
    }
    return index + 1;
}

// ambient_place_points: placer type 0: `count` emitters on the triangle at the (u, v) points g_ambient_tri_uv_points[i]
// (p = v0 + (v1 - v0) u, then p + (v2 - p) v per axis), spread 0x80; returns the next emitter index.
/* was func_1500B1F4 */
s32 ambient_place_points(s16 count, u8 kind, s32 slot, s32 mode, s32 index, s16 **tri) {
    s32 i;
    f32 a;
    s16 x;
    s32 y;
    s32 z;

    if (count == 0) {
        return index;
    }
    for (i = 0; i != count; i++) {
        a = (f32) (tri[1][0] - tri[0][0]) * g_ambient_tri_uv_points[i][0] + (f32) tri[0][0];
        x = (s32) (((f32) tri[2][0] - a) * g_ambient_tri_uv_points[i][1] + a);
        a = (f32) (tri[1][1] - tri[0][1]) * g_ambient_tri_uv_points[i][0] + (f32) tri[0][1];
        y = (s32) (((f32) tri[2][1] - a) * g_ambient_tri_uv_points[i][1] + a);
        a = (f32) (tri[1][2] - tri[0][2]) * g_ambient_tri_uv_points[i][0] + (f32) tri[0][2];
        z = (s32) (((f32) tri[2][2] - a) * g_ambient_tri_uv_points[i][1] + a);
        index = ambient_emitter_add(index, slot, mode, x, y, z, 0x80, kind, index);
    }
    return index;
}

// ambient_place_shape: placer type 4: emitters at the (x, z) offsets of point list g_ambient_shape_points[shape] around the
// triangle's centroid, y on the triangle's plane (tri_compute_plane; the centroid's y when the plane is vertical);
// phase = g_ambient_shape_phase_bits >> slot, then the slot's g_ambient_shape_phase_bits bit flips. Returns the next emitter index.
/* was func_1500B3B0 */
s32 ambient_place_shape(s16 shape, u8 kind, s32 slot, s32 mode, s32 index, s16 **tri) {
    f32 v[3][3];
    f32 cx = 0.0f;
    f32 cy = 0.0f;
    f32 cz = 0.0f;
    f32 *pts;
    u32 k;
    s32 i;
    f32 x;
    f32 y;
    f32 z;

    for (i = 0; i < 3; i++) {
        v[i][0] = tri[i][0];
        v[i][1] = tri[i][1];
        v[i][2] = tri[i][2];
        cx += v[i][0] / 3.0f;
        cy += v[i][1] / 3.0f;
        cz += v[i][2] / 3.0f;
    }
    tri_compute_plane(*(s32 *) &v[0][0], v[0][1], v[0][2], v[1][0], v[1][1], v[1][2], v[2][0], v[2][1], v[2][2]);
    pts = g_ambient_shape_points[shape];
    for (k = 1; (f32) k <= pts[0] * 2.0f; k += 2) {
        x = pts[k] + cx;
        z = pts[k + 1] + cz;
        if (g_tri_plane_ny == 0.0f) {
            y = cy;
        } else {
            y = (g_tri_plane_d - g_tri_plane_nx * x - g_tri_plane_nz * z) / g_tri_plane_ny;
        }
        index = ambient_emitter_add(index, slot, mode, (s32) x, (s32) y, (s32) z, 0x80, kind, g_ambient_shape_phase_bits >> slot);
    }
    g_ambient_shape_phase_bits ^= 1 << slot;
    return index;
}

// ambient_place_centre_sfx: placer type 1: one emitter at the triangle's centroid (integer mean), and a positional
// sound 0x4D there with volume `volume` (0x3E above 62.5).
/* was func_1500B714 */
s32 ambient_place_centre_sfx(s16 volume, u8 kind, s32 slot, s32 mode, s32 index, s16 **tri) {
    s16 x = (tri[2][0] + tri[0][0] + tri[1][0]) / 3;
    s16 y = (tri[2][1] + tri[0][1] + tri[1][1]) / 3;
    s16 z = (tri[2][2] + tri[0][2] + tri[1][2]) / 3;
    u16 vol;

    index = ambient_emitter_add(index, slot, mode, x, y, z, 0x80, kind, index);
    vol = volume;
    if (62.5f < (f32) (u16) volume) {
        vol = 0x3E;
    }
    sfx_emitter_start(0x4D, x, y, z, 0x8000, vol, vol >> 3, 0, NULL, 0, 0, 0);
    return index;
}

// ambient_place_points_fixed_57: placer type 2: as type 0 with spread 0, then the slot's phase range = 0x57.
// (count 0: the asm returns a stale v0; C returns index)
/* was func_1500B8F4 */
s32 ambient_place_points_range57(s16 count, u8 kind, s32 slot, s32 mode, s32 index, s16 **tri) {
    s32 i;
    f32 a;
    s16 x;
    s32 y;
    s32 z;

    for (i = 0; i != count; i++) {
        a = (f32) (tri[1][0] - tri[0][0]) * g_ambient_tri_uv_points[i][0] + (f32) tri[0][0];
        x = (s32) (((f32) tri[2][0] - a) * g_ambient_tri_uv_points[i][1] + a);
        a = (f32) (tri[1][1] - tri[0][1]) * g_ambient_tri_uv_points[i][0] + (f32) tri[0][1];
        y = (s32) (((f32) tri[2][1] - a) * g_ambient_tri_uv_points[i][1] + a);
        a = (f32) (tri[1][2] - tri[0][2]) * g_ambient_tri_uv_points[i][0] + (f32) tri[0][2];
        z = (s32) (((f32) tri[2][2] - a) * g_ambient_tri_uv_points[i][1] + a);
        index = ambient_emitter_add(index, slot, mode, x, y, z, 0, kind, index);
    }
    g_ambient_phase_period[slot] = 0x57;
    return index;
}

// ambient_place_points_fixed_8: placer type 3: as type 2 with phase range 8.
/* was func_1500BAB8 */
s32 ambient_place_points_range8(s16 count, u8 kind, s32 slot, s32 mode, s32 index, s16 **tri) {
    s32 i;
    f32 a;
    s16 x;
    s32 y;
    s32 z;

    for (i = 0; i != count; i++) {
        a = (f32) (tri[1][0] - tri[0][0]) * g_ambient_tri_uv_points[i][0] + (f32) tri[0][0];
        x = (s32) (((f32) tri[2][0] - a) * g_ambient_tri_uv_points[i][1] + a);
        a = (f32) (tri[1][1] - tri[0][1]) * g_ambient_tri_uv_points[i][0] + (f32) tri[0][1];
        y = (s32) (((f32) tri[2][1] - a) * g_ambient_tri_uv_points[i][1] + a);
        a = (f32) (tri[1][2] - tri[0][2]) * g_ambient_tri_uv_points[i][0] + (f32) tri[0][2];
        z = (s32) (((f32) tri[2][2] - a) * g_ambient_tri_uv_points[i][1] + a);
        index = ambient_emitter_add(index, slot, mode, x, y, z, 0, kind, index);
    }
    g_ambient_phase_period[slot] = 8;
    return index;
}

// ambient_place_points_fixed_21: placer type 5: as type 2 with phase range 0x21.
/* was func_1500BC7C */
s32 ambient_place_points_range21(s16 count, u8 kind, s32 slot, s32 mode, s32 index, s16 **tri) {
    s32 i;
    f32 a;
    s16 x;
    s32 y;
    s32 z;

    for (i = 0; i != count; i++) {
        a = (f32) (tri[1][0] - tri[0][0]) * g_ambient_tri_uv_points[i][0] + (f32) tri[0][0];
        x = (s32) (((f32) tri[2][0] - a) * g_ambient_tri_uv_points[i][1] + a);
        a = (f32) (tri[1][1] - tri[0][1]) * g_ambient_tri_uv_points[i][0] + (f32) tri[0][1];
        y = (s32) (((f32) tri[2][1] - a) * g_ambient_tri_uv_points[i][1] + a);
        a = (f32) (tri[1][2] - tri[0][2]) * g_ambient_tri_uv_points[i][0] + (f32) tri[0][2];
        z = (s32) (((f32) tri[2][2] - a) * g_ambient_tri_uv_points[i][1] + a);
        index = ambient_emitter_add(index, slot, mode, x, y, z, 0, kind, index);
    }
    g_ambient_phase_period[slot] = 0x21;
    return index;
}

/* was func_1500BE40 */
void ambient_timer_reset(s32 arg0) {
    g_ambient_quad_bufs[0] = 0;
    g_ambient_quad_bufs[1] = 0;
    g_ambient_quad_max = 110;
}

/* was func_1500BE68 */
void ambient_state_reset(void) {
    g_ambient_flame_phase = 0;
    g_ambient_flame_queue_count = 0;
    g_ambient_pingpong_slots = g_ambient_alt_phase_slots = g_ambient_slow_random_slots = 0;
    g_ambient_emitter_count = 0;
    ambient_timer_reset(0);
}


// ambient_emitters_build: level start: sets up the 15 ambient sound slots (ids / flags at g_ambient_slot_ids), allocates
// the emitter records (capacity g_level_header +0x18, 14 bytes each) and, for every level triangle whose flag word
// (g_coll_tri_flags) has a slot (bits 16-19, 1-based), runs the placer of the slot's row and the triangle's kind (bits
// 20-22) from g_ambient_placement_rows / g_ambient_placer_fns with mode ((flags >> 5) & 3) ^ 3, counting emitters per slot in g_ambient_slot_emitter_count;
// then clears +0xB of every emitter, sorts them by x (ambient_emitters_sort) and seeds the per-slot random offsets
// g_ambient_phases / g_ambient_phase_dir_bits. Skipped when the level has no emitter capacity, in scene 0x1D, or in scene 6 unless
// g_mem_expansion_pak is set.
/* was func_1500BEC0 */
void ambient_emitters_build(void) {
    u16 *slots;
    u32 flags;
    s32 slot;
    s32 kind;
    s16 *placer;
    s32 i;
    s32 q;

    ambient_state_reset();
    if (*(u16 *) ((u8 *) g_level_header + 0x18) == 0) {
        return;
    }
    if ((g_level_id == 6 && g_mem_expansion_pak == 0) || g_level_id == 0x1D) {
        return;
    }
    slots = (u16 *) &g_ambient_slot_ids;
    for (i = 0; i < 15; i++) {
        ambient_slot_setup(i, slots[i * 2], slots[i * 2 + 1]);
    }
    g_ambient_emitters = allocate_memory(*(u16 *) ((u8 *) g_level_header + 0x18) * 14, 1, 2, 0);
    collision_select_area(0);
    if (g_coll_tri_flags != 0) {
        for (i = 0; i < g_coll_tri_count; i++) {
            flags = ((u32 *) g_coll_tri_flags)[i];
            if (flags & 0xF0000) {
                slot = ((flags >> 16) & 0xF) - 1;
                kind = (flags >> 20) & 7;
                placer = g_ambient_placement_rows[g_ambient_placement_row[slot]][kind];
                g_ambient_emitter_count = g_ambient_placer_fns[placer[0]].place(placer[1], kind, slot, ((flags >> 5) & 3) ^ 3, g_ambient_emitter_count,
                                                         (s16 **) (g_level_tri_table + i * 12));
                g_ambient_slot_emitter_count[slot]++;
            }
        }
    }
    for (i = 0; i < g_ambient_emitter_count; i++) {
        g_ambient_emitters[i].unkB = 0;
    }
    g_ambient_sort_by_z = 0;
    ambient_emitters_sort(0, g_ambient_emitter_count - 1);
    for (i = 0; i < 60; i++) {
        q = i >> 2;
        if (g_ambient_phase_period[q] != 0) {
            g_ambient_phases[i] = (game_gu_random() % g_ambient_phase_period[q]) << 8;
        } else {
            g_ambient_phases[i] = 0;
        }
        g_ambient_phase_dir_bits[q] = game_gu_random();
    }
}
