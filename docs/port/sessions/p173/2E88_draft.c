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
// dl_env_colours_list: walks a display list to its G_ENDDL and records each G_SETENVCOLOR command: its index
// (D_800BE970) and RGB (D_800BE950, 3 bytes); D_800BE984 counts them.
void func_15012E88(u32 *dl) {
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
