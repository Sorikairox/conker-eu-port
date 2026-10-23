// trail_grow: motion handler 1 of a trail (D_8008A780): moves the points and adds one per frame until full.
/* Points obj +0x94 (0x14 bytes: x, y, z, vy, u16 t at +0x10) in a ring of +0x25 from the oldest +0x2D to the head
 * +0x2E (exclusive), count +0x2C. Each point falls by gravity rec +0x10 (rec = obj +0x98) into its vy and moves by
 * (rec +4, vy, rec +0xC) times the frame time D_800BE9A4. While the ring has room, the obj position (+0x10) is added
 * at the head with vy = rec +8 and the texture t of all points is ramped 0..0x1000 (0x1000..0 with rec +0x18 flag
 * 0x20); once full, rec +0x20 becomes 3 (func_15149114, if rec +0x18 & 0x17) or 2 (func_15149064). Returns 1. */
s32 func_15148E34(u8 *obj) {
    u8 *pts = *(u8 **)(obj + 0x94);
    u8 *rec = *(u8 **)(obj + 0x98);
    u8 *p;
    s32 i;
    s32 n;
    u16 t;
    u16 step;

    i = *(s8 *)(obj + 0x2D);
    while (i != *(s8 *)(obj + 0x2E)) {
        p = pts + i * 0x14;
        i++;
        *(f32 *)(p + 0xC) -= *(f32 *)(rec + 0x10) * D_800BE9A4;
        *(f32 *)(p + 0x0) += *(f32 *)(rec + 0x4) * D_800BE9A4;
        *(f32 *)(p + 0x4) += *(f32 *)(p + 0xC) * D_800BE9A4;
        *(f32 *)(p + 0x8) += *(f32 *)(rec + 0xC) * D_800BE9A4;
        if (i == obj[0x25]) {
            i = 0;
        }
    }
    n = *(s8 *)(obj + 0x2C);
    if (n >= obj[0x25] - 1) {
        rec[0x20] = (rec[0x18] & 0x17) ? 3 : 2;
        return 1;
    }
    t = (rec[0x18] & 0x20) ? 0x1000 : 0;
    step = 0; /* the asm leaves it unset for an empty trail (only the first point is then written) */
    if (n != 0) {
        step = 0x1000 / n;
    }
    obj[0x2C] = n + 1;
    p = pts + *(s8 *)(obj + 0x2E) * 0x14;
    *(s32 *)(p + 0) = *(s32 *)(obj + 0x10);
    *(s32 *)(p + 4) = *(s32 *)(obj + 0x14);
    *(s32 *)(p + 8) = *(s32 *)(obj + 0x18);
    *(f32 *)(pts + *(s8 *)(obj + 0x2E) * 0x14 + 0xC) = *(f32 *)(rec + 8);
    obj[0x2E]++;
    if (*(s8 *)(obj + 0x2E) == obj[0x25]) {
        obj[0x2E] = 0;
    }
    i = *(s8 *)(obj + 0x2D);
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
