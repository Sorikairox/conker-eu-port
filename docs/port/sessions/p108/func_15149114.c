s32 func_15046F70(f32 *, s32, f32, u8 *);
s32 func_1518CAEC(u8 *, s32, s32, s32, f32);
s32 func_1518CC0C(u8 *, s32, s32, s32, f32, s32);
s32 func_151DA938(u8 *, s32, s32, s32, f32, s32);
s32 func_151DAA88(void *, s32, s32, s32, f32, s32);
extern s32 (*D_8008A7D0[])(u8 *, s32, s32, s32, f32, s32);
extern s32 (*D_8008A7F0[])(u8 *, s32, s32, s32, f32, s32);

// trail_fall: motion handler 3 of a full trail (D_8008A780): moves the points and checks the oldest for a hit.
/* Points as func_15148E34 (all of them, from the head +0x2E back to the oldest +0x2D). With rec +0x18 & 0x17 (rec =
 * obj +0x98) and the oldest point moving down, the segment from its old height to the new one is tested against
 * the collision (func_15046F70, result in obj +0x60..); on a hit the handler rec +0x24 (D_8008A7F0, when the hit
 * kind obj +0x7D is 3) or rec +0x23 (D_8008A7D0) gets the old position, the hit height +0x60 and obj +0x64.
 * Returns 0 when that handler does, else 1. */
s32 func_15149114(u8 *obj) {
    u8 *rec = *(u8 **)(obj + 0x98);
    u8 *pts = *(u8 **)(obj + 0x94);
    s32 old[3]; /* the oldest point before the move (x, y, z as words) */
    f32 seg[3];
    u8 *p;
    s32 i;
    s32 k;

    if (rec[0x18] & 7) {
        p = pts + *(s8 *)(obj + 0x2D) * 0x14;
        old[0] = *(s32 *)(p + 0);
        old[1] = *(s32 *)(p + 4);
        old[2] = *(s32 *)(p + 8);
    } else {
        old[0] = old[1] = old[2] = 0; /* unset in the asm (only read when rec +0x18 has 0x10 but none of 7) */
    }
    i = *(s8 *)(obj + 0x2E);
    do {
        i--;
        if (i < 0) {
            i = obj[0x25] - 1;
        }
        p = pts + i * 0x14;
        *(f32 *)(p + 0xC) -= *(f32 *)(rec + 0x10) * D_800BE9A4;
        *(f32 *)(p + 0x0) += *(f32 *)(rec + 0x4) * D_800BE9A4;
        *(f32 *)(p + 0x4) += *(f32 *)(p + 0xC) * D_800BE9A4;
        *(f32 *)(p + 0x8) += *(f32 *)(rec + 0xC) * D_800BE9A4;
    } while (i != *(s8 *)(obj + 0x2D));

    if (!(rec[0x18] & 0x17)) {
        return 1;
    }
    p = pts + *(s8 *)(obj + 0x2D) * 0x14;
    if (!(*(f32 *)(p + 4) < *(f32 *)&old[1])) {
        return 1;
    }
    seg[0] = *(f32 *)(p + 0);
    seg[1] = *(f32 *)&old[1];
    seg[2] = *(f32 *)(pts + *(s8 *)(obj + 0x2D) * 0x14 + 8);
    if (!func_15046F70(seg, 0, *(f32 *)(pts + *(s8 *)(obj + 0x2D) * 0x14 + 4), obj + 0x60)) {
        return 1;
    }
    if (obj[0x7D] == 3) {
        k = rec[0x24];
        if (k == 0) {
            return 1;
        }
        return D_8008A7F0[k](obj, old[0], old[1], old[2], *(f32 *)(obj + 0x60), (s32)(obj + 0x64)) != 0;
    }
    k = rec[0x23];
    if (k == 0) {
        return 1;
    }
    return D_8008A7D0[k](obj, old[0], old[1], old[2], *(f32 *)(obj + 0x60), (s32)(obj + 0x64)) != 0;
}
