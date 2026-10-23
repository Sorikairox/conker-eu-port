extern s32 (*D_80087030[])(u8 *, s32, s32);
// objects_hit_by_segment: tests the segment start / dir (func_151452C4) against every live object of D_800CC2D0
// (not self, kind byte +4 not 0xFF unless level 0x23, state +5 not 3, flag 0x40 at +0xF8, passing filter
// D_80087030[filter](obj, self, filterArg) unless filter is -1) as a sphere at its position raised by +0xD6 with
// diameter 2 * max(+0xD2, +0xD4). Returns a mask with bit i cleared for each hit object i (all other bits set).
s32 func_151D611C(u8 *start, s32 *dir, u8 *self, s8 filter, s32 filterArg) {
    f32 center[3];
    f32 out0[3];
    f32 out1[3];
    f32 dist0;
    f32 dist1;
    f32 radius;
    s32 mask;
    u8 i;
    u8 *obj;

    mask = -1;
    for (i = 0; i < 25; i++) {
        obj = (u8 *)&D_800CC2D0[i];
        if (*(s32 *)(obj + 0) == 0) {
            continue;
        }
        if (obj[5] == 3) {
            continue;
        }
        if (D_800BE9F0 != 0x23 && obj[4] == 0xFF) {
            continue;
        }
        if (obj == self) {
            continue;
        }
        if ((*(s32 *)(obj + 0xF8) & 0x40) == 0) {
            continue;
        }
        if (filter != -1 && D_80087030[filter](obj, (s32)self, filterArg) == 0) {
            continue;
        }
        if (*(s16 *)(obj + 0xD2) < *(s16 *)(obj + 0xD4)) {
            radius = *(s16 *)(obj + 0xD4);
        } else {
            radius = *(s16 *)(obj + 0xD2);
        }
        center[0] = *(f32 *)(obj + 0x14);
        center[1] = *(f32 *)(obj + 0x18) + (f32)*(s16 *)(obj + 0xD6);
        center[2] = *(f32 *)(obj + 0x1C);
        if (func_151452C4((struct17 *)start, (struct17 *)dir, (struct17 *)center, radius + radius, (s32)out0,
                          (s32)out1, &dist0, &dist1)) {
            mask &= ~(1 << i);
        }
    }
    return mask;
}
