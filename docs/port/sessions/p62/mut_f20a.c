/*
 * P62: adjustment entries of object type 0x7B for func_150342D0 (object i, buffer p): a shared angle (the s16 at
 * D_800CC298 + 0x12) swings down by D_800BE9E4 * 0x222 per call while object i's +0x84 is 0x21 (to at least
 * -0x1999, -6553.6 as a float) and back up otherwise (below 0x1555, 5461.33); the sum is compared as an int, not
 * an s16. Then six entries {joint * 6 + 4, angle} for joints 29..34; returns the end of the entries.
 */
s16 *func_150F20C8(s16 *p, s32 i) {
    s16 *angle = (s16 *)((u8 *)&D_800CC298 + 0x12);
    s32 step = D_800BE9E4 * 0x222;
    s32 v;
    s32 k;

    if (*(u16 *)((u8 *)&D_800CC2D0[i] + 0x84) == 0x21) {
        v = *angle - step;
        if ((f32)(s16)v > -6553.6f) {
            *angle = v;
        } else {
            *angle = -0x1999;
        }
    } else {
        v = *angle + step;
        if ((f32)v < 5461.3335f) {
            *angle = v;
        } else {
            *angle = 0x1555;
        }
    }
    for (k = 0; k < 6; k++) {
        p[k * 2] = 29 * 6 + 4 + k * 6;
        p[k * 2 + 1] = *angle;
    }
    return p + 12;
}
