#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* Level vertex colour backup (filled at level load, flags at level header byte +0x21):
 *  g_vtx_colour_backup[4]  per level geometry chunk 0..3: its slice of the colour store (3 bytes per vertex); [0] is also
 *                 the store itself (vertex_colours_store writes through it)
 *  g_vtx_colour_group_backup     u8 ** per colour group: per entry of the group, the RGB of its listed vertices
 *  g_vtx_colour_room_base     u16 per room record: first colour index in the store (0xFFFF: none)
 *  g_vtx_colour_stored     u16 number of colours stored so far
 *  g_level_env_colours_rgb / g_level_env_colour_cmds / g_level_env_colour_count: RGB, DL command index and count of the G_SETENVCOLOR commands of
 *                 g_level_part_dls's display list (dl_env_colours_list) */
extern u8 *g_vtx_colour_backup[4]; /* was D_800BE930 */
extern u8 *g_level_part_vtx[4];  /* level geometry chunks: vertex arrays; was D_800B1220 */
extern s32 g_level_part_vtx_count[4];  /* level geometry chunks: vertex counts; was D_800B1250 */
extern u8 **g_level_model_colour_groups;    /* per colour group: entries {pad, u16 *vertex indices (+4), s32 count (+8)} (12 bytes); was D_800B1240 */
extern u8 *g_level_model_colour_counts;     /* per colour group: entry count; was D_800B1244 */
extern u8 g_level_model_colour_group_count;      /* number of colour groups; was D_800B1248 */
extern u8 g_level_env_colour_count; /* was D_800BE984 */
#define COLOUR_GROUPS (*(u8 ****) g_vtx_colour_group_backup)
#define ROOM_COLOUR_BASE (*(u16 **) g_vtx_colour_room_base)
#define COLOURS_STORED (*(u16 *) g_vtx_colour_stored)
#define LEVEL_FLAGS (((u8 *) g_level_header)[0x21])
#define ROOM_REC(i) ((u8 *) g_world_objs + (i) * 0xA0) /* +0x16 u16 vertex count, +0x28 vertex array */
void vertex_colours_store(u8 *vtx, s32 count);
void dl_env_colours_list(u32 *dl);

// level_vertex_colours_backup: level load. Allocates the colour store for the level chunks (flag 1) and the
// room records (flag 2) and copies their vertex colours into it, then (flag 4) the per-entry colour lists of the
// colour groups, and finally lists the env colour commands of the level DL (dl_env_colours_list).
/* was func_15012760 */
void level_vertex_colours_backup(void) {
    s32 total;
    s32 i;
    s32 j;
    s32 k;
    u8 *ent;
    u8 *vtx;
    u16 *idx;

    COLOUR_GROUPS = NULL;
    if (LEVEL_FLAGS == 0) {
        return;
    }
    total = 0;
    if (LEVEL_FLAGS & 1) {
        total = g_level_part_vtx_count[0] + g_level_part_vtx_count[1] + g_level_part_vtx_count[2] + g_level_part_vtx_count[3];
    }
    if (LEVEL_FLAGS & 2) {
        for (i = 0; i < g_world_obj_count; i++) {
            total += *(u16 *) (ROOM_REC(i) + 0x16);
        }
    }
    g_vtx_colour_backup[0] = allocate_memory(total * 3, 1, 0, 0);
    if (g_vtx_colour_backup[0] == NULL) {
        g_vtx_colour_backup[1] = NULL;
        return;
    }
    COLOURS_STORED = 0;
    g_level_env_colour_count = 0;
    if (LEVEL_FLAGS & 1) {
        for (i = 0; i < 4; i++) {
            if (g_level_part_vtx[i] != NULL) {
                /* literal: based on g_vtx_colour_backup[0], which is NULL here when chunk 0 has no vertices */
                g_vtx_colour_backup[i] = g_vtx_colour_backup[0] + COLOURS_STORED * 3;
                vertex_colours_store(g_level_part_vtx[i], g_level_part_vtx_count[i]);
            } else {
                g_vtx_colour_backup[i] = NULL;
            }
        }
    }
    if (LEVEL_FLAGS & 2) {
        ROOM_COLOUR_BASE = allocate_memory(g_world_obj_count * 2, 1, 0, 0);
        for (i = 0; i < g_world_obj_count; i++) {
            if (*(u16 *) (ROOM_REC(i) + 0x16) != 0) {
                ROOM_COLOUR_BASE[i] = COLOURS_STORED;
                vertex_colours_store(*(u8 **) (ROOM_REC(i) + 0x28), *(u16 *) (ROOM_REC(i) + 0x16));
            } else {
                ROOM_COLOUR_BASE[i] = 0xFFFF;
            }
        }
    }
    if (LEVEL_FLAGS & 4) {
        COLOUR_GROUPS = allocate_memory(g_level_model_colour_group_count * 4, 1, 0, 0);
        bzero(COLOUR_GROUPS, g_level_model_colour_group_count * 4);
        for (i = 0; i < g_level_model_colour_group_count; i++) {
            if (g_level_model_colour_counts[i] == 0) {
                continue;
            }
            COLOUR_GROUPS[i] = allocate_memory(g_level_model_colour_counts[i] * 4, 1, 0, 0);
            ent = g_level_model_colour_groups[i];
            for (j = 0; j < g_level_model_colour_counts[i]; j++, ent += 0xC) {
                COLOUR_GROUPS[i][j] = allocate_memory(*(s32 *) (ent + 8) * 3, 1, 0, 0);
                /* groups 0..3 are the level chunks, the others room records 0.. */
                vtx = (i < 4) ? g_level_part_vtx[i] : *(u8 **) (ROOM_REC(i - 4) + 0x28);
                for (k = 0; k < *(s32 *) (ent + 8); k++) {
                    idx = *(u16 **) (ent + 4);
                    COLOUR_GROUPS[i][j][k * 3 + 0] = vtx[idx[k] * 16 + 0xC];
                    COLOUR_GROUPS[i][j][k * 3 + 1] = vtx[idx[k] * 16 + 0xD];
                    COLOUR_GROUPS[i][j][k * 3 + 2] = vtx[idx[k] * 16 + 0xE];
                }
            }
        }
    }
    dl_env_colours_list((u32 *) g_level_part_dls[0]);
}

// vertex_colours_store: appends the colours (+0xC..+0xE) of `count` 16-byte vertices to the colour store
// g_vtx_colour_backup[0] at index g_vtx_colour_stored.
/* was func_15012C34 */
void vertex_colours_store(u8 *vtx, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        g_vtx_colour_backup[0][COLOURS_STORED * 3 + 0] = vtx[i * 16 + 0xC];
        g_vtx_colour_backup[0][COLOURS_STORED * 3 + 1] = vtx[i * 16 + 0xD];
        g_vtx_colour_backup[0][COLOURS_STORED * 3 + 2] = vtx[i * 16 + 0xE];
        COLOURS_STORED++;
    }
}

// dl_env_colours_list: walks a display list to its G_ENDDL and records each G_SETENVCOLOR command: its index
// (g_level_env_colour_cmds) and RGB (g_level_env_colours_rgb, 3 bytes); g_level_env_colour_count counts them.
/* was func_15012E88 */
void dl_env_colours_list(u32 *dl) {
    s32 i;
    u8 *rgb;

    for (i = 0; (s8) (dl[0] >> 24) != -0x21 /* 0xDF G_ENDDL */; i++, dl += 2) {
        if ((s8) (dl[0] >> 24) == -5 /* 0xFB G_SETENVCOLOR */) {
            ((u16 *) g_level_env_colour_cmds)[g_level_env_colour_count] = i;
            rgb = (u8 *) g_level_env_colours_rgb + g_level_env_colour_count * 3;
            rgb[0] = dl[1] >> 24;
            rgb[1] = dl[1] >> 16;
            rgb[2] = dl[1] >> 8;
            g_level_env_colour_count++;
        }
    }
}

/* was func_15012F40 */
void clear_dfc00_table(void) {
    s32 i;

    for (i = 0; i < 0x1E3; i++) {
        g_shared_dl_refcounts[i] = 0;
    }
}
