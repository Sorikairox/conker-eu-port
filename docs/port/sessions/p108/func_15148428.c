extern s32 (*D_8008A780[])(u8 *);
extern s32 (*D_8008A798[])(u8 *);
extern s32 (*D_8008A7CC[])(u8 *, s32, s32, s32, f32, s32); /* = D_8008A7D0 - 4: the hit handlers */

// trail_step: per-frame step of a trail particle (type table D_8008A5A0 entry 1).
/* obj +0x98 is the trail record (func_15148310): +0x20 / +0x21 select the motion handlers (D_8008A780 / D_8008A798,
 * 0 = none), +0x22 the end handler (D_8008A7CC, the hit handler table D_8008A7D0 shifted by one); +0x18 flag 0x40 fades the alpha +0x1B in with the timer (obj +0x1C
 * times rate +0x1E, while the timer is below +0x1C). Stores the oldest point (index +0x2D of the +0x94 point list,
 * 0x14 bytes each) in obj +0x54, or 0 when the list is empty. Returns 0 when a handler ends the trail, else 1. */
s32 func_15148428(u8 *obj) {
    u8 *rec = *(u8 **)(obj + 0x98);
    s8 done = 0;
    s32 a;

    if (rec[0x20] != 0) {
        if (!D_8008A780[rec[0x20]](obj)) {
            done = 1;
        }
    }
    if (rec[0x21] != 0 && !done) {
        if (!D_8008A798[rec[0x21]](obj)) {
            done = 1;
        }
    }
    if ((rec[0x18] & 0x40) && !done && *(s16 *)(obj + 0x1C) < *(s16 *)(rec + 0x1C)) {
        a = *(s16 *)(obj + 0x1C) * *(s16 *)(rec + 0x1E);
        if (a < rec[0x1B]) {
            rec[0x1B] = a;
        }
    }
    if (done && rec[0x22] != 0) {
        /* the asm leaves a1 = 0 (the return value) and a2 = 1 (done) in the argument registers */
        D_8008A7CC[rec[0x22]](obj, 0, 1, 0, 0.0f, 0);
    }
    if (*(s8 *)(obj + 0x2C) > 0) {
        u8 *p = *(u8 **)(obj + 0x94) + *(s8 *)(obj + 0x2D) * 0x14;

        *(s32 *)(obj + 0x54) = *(s32 *)(p + 0);
        *(s32 *)(obj + 0x58) = *(s32 *)(p + 4);
        *(s32 *)(obj + 0x5C) = *(s32 *)(p + 8);
    } else {
        *(f32 *)(obj + 0x54) = 0.0f;
        *(f32 *)(obj + 0x58) = 0.0f;
        *(f32 *)(obj + 0x5C) = 0.0f;
    }
    return !done;
}
