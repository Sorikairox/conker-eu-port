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
void func_15012C34(u8 *vtx, s32 count);
void func_15012E88(u32 *dl);
// level_vertex_colours_backup: level load. Allocates the colour store for the level chunks (flag 1) and the
// room records (flag 2) and copies their vertex colours into it, then (flag 4) the per-entry colour lists of the
// colour groups, and finally lists the env colour commands of the level DL (func_15012E88).
void func_15012760(void) {
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
                func_15012C34(D_800B1220[i], D_800B1250[i]);
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
                func_15012C34(*(u8 **) (ROOM_REC(i) + 0x28), *(u16 *) (ROOM_REC(i) + 0x16));
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
    func_15012E88((u32 *) D_800B0E00[0]);
}
