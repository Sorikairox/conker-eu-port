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
// vertex_colours_store: appends the colours (+0xC..+0xE) of `count` 16-byte vertices to the colour store
// D_800BE930[0] at index D_800BE948.
void func_15012C34(u8 *vtx, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        D_800BE930[0][COLOURS_STORED * 3 + 0] = vtx[i * 16 + 0xC];
        D_800BE930[0][COLOURS_STORED * 3 + 1] = vtx[i * 16 + 0xD];
        D_800BE930[0][COLOURS_STORED * 3 + 2] = vtx[i * 16 + 0xE];
        COLOURS_STORED++;
    }
}
