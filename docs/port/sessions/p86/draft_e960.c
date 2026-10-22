/* the zoom effect state at arg0 + 0x18 */
typedef struct {
    u8  pad0[0x10];
    u32 step;           /* 0x10: 16.16 source advance per destination pixel */
    u8  pad14[4];
    u32 x0;             /* 0x18 rectangle (inclusive) */
    u32 y0;             /* 0x1C */
    u32 x1;             /* 0x20 */
    u32 y1;             /* 0x24 */
    u8  pad28[0x30 - 0x28];
    s16 colMap[0x280];  /* 0x30: source column per destination column */
    s16 rowMap[0x200];  /* 0x530: source row per destination row */
} Zoom150CE960;

/* Nearest-neighbour zoom of the rectangle (x0, y0) .. (x1, y1) of the 16-bit frame buffer `fb` (rows of
 * D_800BE620 pixels) in place, when arg0[0x2C] bit 0 is set. Rows are done bottom-up and right to left so a source
 * pixel is read before it is overwritten; a row with the same source as the row below is a copy of it. */
void func_150CE960(u8 *arg0, u16 *fb) {
    Zoom150CE960 *z;
    u32 acc;
    u32 src;
    u32 i;
    s32 x, y;

    z = (Zoom150CE960 *) (arg0 + 0x18);
    if (!(arg0[0x2C] & 1)) {
        return;
    }
    acc = 0;
    src = z->x0;
    for (i = z->x0; i <= z->x1; i++) {
        z->colMap[i] = src;
        acc += z->step;
        if (acc >= 0x10000) {
            src = i;
            acc -= 0x10000;
        }
    }
    acc = 0;
    src = z->y0;
    for (i = z->y0; i <= z->y1; i++) {
        z->rowMap[i] = src;
        acc += z->step;
        if (acc >= 0x10000) {
            src = i;
            acc -= 0x10000;
        }
    }
    for (y = z->y1; y >= (s32) z->y0; y--) {
        if (y != (s32) z->y1 && z->rowMap[y + 1] == z->rowMap[y]) {
            memcpy((s32) &fb[y * D_800BE620 + z->x0], (u8 **) &fb[(y + 1) * D_800BE620 + z->x0],
                   (z->x1 - z->x0) * 2 + 2);
        } else {
            for (x = z->x1; x >= (s32) z->x0; x--) {
                fb[y * D_800BE620 + x] = fb[z->rowMap[y] * D_800BE620 + z->colMap[x]];
            }
        }
    }
}
