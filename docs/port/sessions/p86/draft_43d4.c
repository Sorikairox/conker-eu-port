/* the D_800DBEF4 record fields func_151143D4 uses (0xA0 bytes) */
typedef struct {
    u8  pad0[0x38];
    void (*update)(void *);   /* 0x38 */
    u8  pad3C[0x5A - 0x3C];
    s16 pos[3];               /* 0x5A */
    u8  pad60[0x6E - 0x60];
    u8  busy;                 /* 0x6E */
    u8  flags;                /* 0x6F: 0x40 = needs update */
    u8  pad70[0x80 - 0x70];
    s32 extra;                /* 0x80 */
    u8  pad84[0xA0 - 0x84];
} Rec151143D4;

/* a D_800D23C0 group (0x18 bytes): ids[] are (type << 12 | record index); type 2 = D_800DBEF4 record */
typedef struct {
    u8  pad0[2];
    u16 count;                /* 0x2 */
    u8  pad4[4];
    u16 ids[8];               /* 0x8 */
} Group151143D4;

extern s32 D_800DC3C8;

/* Runs the update callback of every pending record (flags & 0x40, not busy): first the first
 * D_800DC320 - D_800DC3C8 records, then the type-2 groups. In a group, the first record's position (0x5A..0x5E)
 * and 0x80 value are copied to each following member before its update. arg0 is not used. */
void func_151143D4(s32 arg0) {
    Rec151143D4 *rec;
    Group151143D4 *grp;
    s16 x, y, z;
    s32 extra;
    s32 n, i, j;
    u16 id;

    x = y = z = 0;
    extra = 0;
    n = D_800DC320 - D_800DC3C8;
    for (i = 0; i < n; i++) {
        rec = (Rec151143D4 *) D_800DBEF4 + i;
        if ((rec->flags & 0x40) == 0x40 && rec->busy == 0) {
            rec->update(rec);
        }
    }
    for (i = 0; i < (s32) D_80087380; i++) {
        grp = (Group151143D4 *) D_800D23C0 + i;
        if ((grp->ids[0] >> 12) != 2) {
            continue;
        }
        for (j = 0; j < grp->count; j++) {
            id = ((Group151143D4 *) D_800D23C0)[i].ids[j];
            if ((id >> 12) != 2) {
                continue;
            }
            rec = (Rec151143D4 *) D_800DBEF4 + (id & 0xFFF);
            if ((rec->flags & 0x40) == 0x40 && rec->busy == 0) {
                if (j != 0) {
                    rec->pos[0] = x;
                    rec->pos[1] = y;
                    rec->pos[2] = z;
                    rec->extra = extra;
                }
                rec->update(rec);
                grp = (Group151143D4 *) D_800D23C0 + i;   /* the callback may move the groups */
            }
            if (j == 0) {
                x = rec->pos[0];
                y = rec->pos[1];
                z = rec->pos[2];
                extra = rec->extra;
            }
        }
    }
}
