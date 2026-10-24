#ifdef NON_MATCHING
// path_pass_points_near_objects: path handler 2 of D_8008FC20 (`s32 (*)(u8 *)`, its result is tested by the path
// updater). For every live object of D_800CC2D0 (+0x00 set, not held: +0x65 == 0) whose team byte +0x3B differs
// from the path owner's (**(arg0 + 0x98))[0x3B], it walks back from the path's head point +0x2E to the current
// point +0x2D (ring of +0x25 points of 0x24 bytes at +0x94). When the object (x +0x14, y +0x18 + s16 +0xE8,
// z +0x1C) is within (radius +0xE4)^2 + 2500 of a point (the height difference scaled by (1 + r / +0xE6) / 2),
// the current point advances to it (wrapping at +0x25), and the remaining count +0x2C drops by one per step.
// Always returns 1.
s32 func_15198D3C(u8 *arg0) {
    u8 *owner = *(u8 **) (arg0 + 0x98);
    u8 *points = *(u8 **) (arg0 + 0x94);
    u8 *obj;
    f32 *pt;
    f32 radius;
    f32 height;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 i;

    for (obj = (u8 *) D_800CC2D0; obj != (u8 *) &D_800D121C; obj += 0x32C) {
        if (*(s32 *) obj == 0 || obj[0x65] != 0 || obj[0x3B] == (*(u8 **) owner)[0x3B]) {
            continue;
        }
        i = *(s8 *) (arg0 + 0x2E);
        while (i != *(s8 *) (arg0 + 0x2D)) {
            i--;
            if (i < 0) {
                i = arg0[0x25] - 1;
            }
            pt = (f32 *) (points + i * 0x24);
            radius = *(s16 *) (obj + 0xE4);
            height = *(s16 *) (obj + 0xE6);
            dx = pt[0] - *(f32 *) (obj + 0x14);
            dz = pt[2] - *(f32 *) (obj + 0x1C);
            dy = (pt[1] - (*(f32 *) (obj + 0x18) + *(s16 *) (obj + 0xE8))) * ((1.0f + radius / height) * 0.5f);
            if (dx * dx + dy * dy + dz * dz < radius * radius + 2500.0f) {
                while (i != *(s8 *) (arg0 + 0x2D)) {
                    (*(s8 *) (arg0 + 0x2D))++;
                    if (arg0[0x25] == *(s8 *) (arg0 + 0x2D)) {
                        *(s8 *) (arg0 + 0x2D) = 0;
                    }
                    (*(s8 *) (arg0 + 0x2C))--;
                }
            }
        }
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15198D3C.s")
#endif
