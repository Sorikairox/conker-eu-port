// trail_shrink: motion handler 4 of a trail (D_8008A780): drops the newest point each frame and re-ramps the rest.
/* Count obj +0x2C, ring of +0x25 points obj +0x94 (0x14 bytes, u16 texture t at +0x10) from the oldest +0x2D to the
 * head +0x2E. Returns 0 (the trail ends) when fewer than 3 points are left; else removes the head point and sets
 * the texture t of the others to a 0..0x1000 ramp (0x1000..0 with rec +0x18 flag 0x20, rec = obj +0x98), returns 1. */
s32 func_15149350(u8 *obj) {
    u8 *rec;
    u8 *pts;
    s32 i;
    u16 t;
    u16 step;

    if (*(s8 *)(obj + 0x2C) < 3) {
        return 0;
    }
    obj[0x2C] = *(s8 *)(obj + 0x2C) - 1;
    rec = *(u8 **)(obj + 0x98);
    pts = *(u8 **)(obj + 0x94);
    step = 0x1000 / *(s8 *)(obj + 0x2C);
    t = (rec[0x18] & 0x20) ? 0x1000 : 0;
    i = *(s8 *)(obj + 0x2D);
    obj[0x2E] = *(s8 *)(obj + 0x2E) - 1;
    if (*(s8 *)(obj + 0x2E) < 0) {
        obj[0x2E] = obj[0x25] - 1;
    }
    if (i != *(s8 *)(obj + 0x2E)) {
        do {
            *(u16 *)(pts + i * 0x14 + 0x10) = t;
            if (rec[0x18] & 0x20) {
                t -= step;
            } else {
                t += step;
            }
            i++;
            if (i == obj[0x25]) {
                i = 0;
            }
        } while (i != *(s8 *)(obj + 0x2E));
    }
    return 1;
}
