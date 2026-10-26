#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* Level vertex colour backup (filled at level load, flags at level header byte +0x21):
 *  D_800BE930[4]  per level geometry chunk 0..3: its slice of the colour store (3 bytes per vertex); [0] is also
 *                 the store itself (vertex_colours_store writes through it)
 *  D_800BE940     u8 ** per colour group: per entry of the group, the RGB of its listed vertices
 *  D_800BE944     u16 per room record: first colour index in the store (0xFFFF: none)
 *  D_800BE948     u16 number of colours stored so far
 *  D_800BE950 / D_800BE970 / D_800BE984: RGB, DL command index and count of the G_SETENVCOLOR commands of
 *                 D_800B0E00's display list (dl_env_colours_list) */
extern u8 *D_800BE930[4];
extern u8 *D_800B1220[4];  /* level geometry chunks: vertex arrays */
extern s32 D_800B1250[4];  /* level geometry chunks: vertex counts */
extern u8 **D_800B1240;    /* per colour group: entries {pad, u16 *vertex indices (+4), s32 count (+8)} (12 bytes) */
extern u8 *D_800B1244;     /* per colour group: entry count */
extern u8 D_800B1248;      /* number of colour groups */
extern u8 D_800BE984;
#define COLOUR_GROUPS (*(u8 ****) D_800BE940)
#define ROOM_COLOUR_BASE (*(u16 **) D_800BE944)
#define COLOURS_STORED (*(u16 *) D_800BE948)
#define LEVEL_FLAGS (((u8 *) D_800B0DF0)[0x21])
#define ROOM_REC(i) ((u8 *) D_800DBEF4 + (i) * 0xA0) /* +0x16 u16 vertex count, +0x28 vertex array */
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
        total = D_800B1250[0] + D_800B1250[1] + D_800B1250[2] + D_800B1250[3];
    }
    if (LEVEL_FLAGS & 2) {
        for (i = 0; i < D_800DC320; i++) {
            total += *(u16 *) (ROOM_REC(i) + 0x16);
        }
    }
    D_800BE930[0] = allocate_memory(total * 3, 1, 0, 0);
    if (D_800BE930[0] == NULL) {
        D_800BE930[1] = NULL;
        return;
    }
    COLOURS_STORED = 0;
    D_800BE984 = 0;
    if (LEVEL_FLAGS & 1) {
        for (i = 0; i < 4; i++) {
            if (D_800B1220[i] != NULL) {
                /* literal: based on D_800BE930[0], which is NULL here when chunk 0 has no vertices */
                D_800BE930[i] = D_800BE930[0] + COLOURS_STORED * 3;
                vertex_colours_store(D_800B1220[i], D_800B1250[i]);
            } else {
                D_800BE930[i] = NULL;
            }
        }
    }
    if (LEVEL_FLAGS & 2) {
        ROOM_COLOUR_BASE = allocate_memory(D_800DC320 * 2, 1, 0, 0);
        for (i = 0; i < D_800DC320; i++) {
            if (*(u16 *) (ROOM_REC(i) + 0x16) != 0) {
                ROOM_COLOUR_BASE[i] = COLOURS_STORED;
                vertex_colours_store(*(u8 **) (ROOM_REC(i) + 0x28), *(u16 *) (ROOM_REC(i) + 0x16));
            } else {
                ROOM_COLOUR_BASE[i] = 0xFFFF;
            }
        }
    }
    if (LEVEL_FLAGS & 4) {
        COLOUR_GROUPS = allocate_memory(D_800B1248 * 4, 1, 0, 0);
        bzero(COLOUR_GROUPS, D_800B1248 * 4);
        for (i = 0; i < D_800B1248; i++) {
            if (D_800B1244[i] == 0) {
                continue;
            }
            COLOUR_GROUPS[i] = allocate_memory(D_800B1244[i] * 4, 1, 0, 0);
            ent = D_800B1240[i];
            for (j = 0; j < D_800B1244[i]; j++, ent += 0xC) {
                COLOUR_GROUPS[i][j] = allocate_memory(*(s32 *) (ent + 8) * 3, 1, 0, 0);
                /* groups 0..3 are the level chunks, the others room records 0.. */
                vtx = (i < 4) ? D_800B1220[i] : *(u8 **) (ROOM_REC(i - 4) + 0x28);
                for (k = 0; k < *(s32 *) (ent + 8); k++) {
                    idx = *(u16 **) (ent + 4);
                    COLOUR_GROUPS[i][j][k * 3 + 0] = vtx[idx[k] * 16 + 0xC];
                    COLOUR_GROUPS[i][j][k * 3 + 1] = vtx[idx[k] * 16 + 0xD];
                    COLOUR_GROUPS[i][j][k * 3 + 2] = vtx[idx[k] * 16 + 0xE];
                }
            }
        }
    }
    dl_env_colours_list((u32 *) D_800B0E00[0]);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_3FF70/level_vertex_colours_backup.s")
#endif

#ifdef NON_MATCHING
// vertex_colours_store: appends the colours (+0xC..+0xE) of `count` 16-byte vertices to the colour store
// D_800BE930[0] at index D_800BE948.
/* was func_15012C34 */
void vertex_colours_store(u8 *vtx, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        D_800BE930[0][COLOURS_STORED * 3 + 0] = vtx[i * 16 + 0xC];
        D_800BE930[0][COLOURS_STORED * 3 + 1] = vtx[i * 16 + 0xD];
        D_800BE930[0][COLOURS_STORED * 3 + 2] = vtx[i * 16 + 0xE];
        COLOURS_STORED++;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_3FF70/vertex_colours_store.s")
#endif

#ifdef NON_MATCHING
// dl_env_colours_list: walks a display list to its G_ENDDL and records each G_SETENVCOLOR command: its index
// (D_800BE970) and RGB (D_800BE950, 3 bytes); D_800BE984 counts them.
/* was func_15012E88 */
void dl_env_colours_list(u32 *dl) {
    s32 i;
    u8 *rgb;

    for (i = 0; (s8) (dl[0] >> 24) != -0x21 /* 0xDF G_ENDDL */; i++, dl += 2) {
        if ((s8) (dl[0] >> 24) == -5 /* 0xFB G_SETENVCOLOR */) {
            ((u16 *) D_800BE970)[D_800BE984] = i;
            rgb = (u8 *) D_800BE950 + D_800BE984 * 3;
            rgb[0] = dl[1] >> 24;
            rgb[1] = dl[1] >> 16;
            rgb[2] = dl[1] >> 8;
            D_800BE984++;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_3FF70/dl_env_colours_list.s")
#endif

/* was func_15012F40 */
void clear_dfc00_table(void) {
    s32 i;

    for (i = 0; i < 0x1E3; i++) {
        D_800DFC00[i] = 0;
    }
}
