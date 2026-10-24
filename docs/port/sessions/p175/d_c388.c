extern s32 (*D_8008B420[])(u8 *, u8 *); /* motion handlers; D_8008B424 = the same table shifted by one */

// particle_streak_step: per-frame step of a streak particle (kind 8 of D_8008A5A0, created by func_1515C2F0).
/* The points (obj +0x94, 0x10 bytes: x, y, z, vy) form a ring of +0x25 entries from the oldest +0x2D to the head
 * +0x2E (exclusive), count +0x2C. Each live point moves by the record's velocity (rec = obj +0x98: vx +4, vz +0xC)
 * and falls by the gravity rec +0x10 into its vy, all scaled by the frame time D_800BE9A4. Then the motion handler
 * rec +0x38 (D_8008B420, -1 = none) runs with (obj, rec); the oldest point is stored in obj +0x54 (0 when the ring
 * is empty). Returns 0 when the handler ends the particle, else 1. */
s32 func_1515C388(u8 *obj) {
    u8 *rec = *(u8 **) (obj + 0x98);
    u8 *pts = *(u8 **) (obj + 0x94);
    u8 done = 0;
    f32 *p;
    f32 vy;
    s32 i;

    if (*(s8 *) (obj + 0x2C) != 0) {
        for (i = *(s8 *) (obj + 0x2D); i != *(s8 *) (obj + 0x2E);) {
            p = (f32 *) (pts + i * 0x10);
            p[0] += *(f32 *) (rec + 4) * D_800BE9A4;
            vy = p[3];
            p[1] += vy * D_800BE9A4 + *(f32 *) (rec + 0x10) * D_800BE9A4 * D_800BE9A4 * 0.5f;
            p[2] += *(f32 *) (rec + 0xC) * D_800BE9A4;
            p[3] = vy + *(f32 *) (rec + 0x10) * D_800BE9A4;
            i++;
            if (i == obj[0x25]) {
                i = 0;
            }
        }
    }
    if (*(s8 *) (rec + 0x38) != -1) {
        done = D_8008B420[*(s8 *) (rec + 0x38)](obj, rec) == 0;
    }
    if (*(s8 *) (obj + 0x2C) > 0) {
        p = (f32 *) (pts + *(s8 *) (obj + 0x2D) * 0x10);
        *(s32 *) (obj + 0x54) = ((s32 *) p)[0];
        *(s32 *) (obj + 0x58) = ((s32 *) p)[1];
        *(s32 *) (obj + 0x5C) = ((s32 *) p)[2];
    } else {
        *(f32 *) (obj + 0x54) = 0.0f;
        *(f32 *) (obj + 0x58) = 0.0f;
        *(f32 *) (obj + 0x5C) = 0.0f;
    }
    if (done) {
        return 0;
    }
    return 1;
}
