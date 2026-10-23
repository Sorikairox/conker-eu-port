s32 func_15145128(f32 *, f32 *, f32 *, f32 *);
f32 func_15143E64(f32 *);
// ray_hit_object_bounds: intersects the ray start + t * dir with an object's bounding sphere, squashed vertically:
// centre = the object position (+0x14) raised by +0xD6, radius +0xD2, y scaled by +0xDC into sphere space and by
// +0xE0 back. Returns 0 for a zero-length direction or a miss; on a hit stores the entry / exit points (hitIn,
// hitOut) and their distances from start (distIn, distOut) and returns 1.
s32 func_15082020(f32 *start, f32 *dir, u8 *obj, f32 *hitIn, f32 *hitOut, f32 *distIn, f32 *distOut) {
    f32 center[3];
    f32 p[3];
    f32 d[3];
    f32 c[3];
    f32 rel[3];
    f32 ys;
    f32 yback;

    center[0] = *(f32 *)(obj + 0x14);
    center[1] = *(f32 *)(obj + 0x18) + *(s16 *)(obj + 0xD6);
    center[2] = *(f32 *)(obj + 0x1C);
    yback = *(f32 *)(obj + 0xE0);
    ys = *(f32 *)(obj + 0xDC);
    p[0] = start[0];
    p[1] = start[1] * ys;
    p[2] = start[2];
    d[0] = dir[0];
    d[1] = dir[1] * ys;
    d[2] = dir[2];
    if (func_15145128(d, d, NULL, NULL) == 0) {
        return 0;
    }
    c[0] = center[0];
    c[1] = center[1] * ys;
    c[2] = center[2];
    if (func_151452C4((struct17 *)p, (struct17 *)d, (struct17 *)c, *(s16 *)(obj + 0xD2), (s32)hitIn, (s32)hitOut, distIn,
                      distOut) == 0) {
        return 0;
    }
    hitIn[1] *= yback;
    hitOut[1] *= yback;
    rel[0] = hitIn[0] - start[0];
    rel[1] = hitIn[1] - start[1];
    rel[2] = hitIn[2] - start[2];
    *distIn = func_15143E64(rel);
    rel[0] = hitOut[0] - start[0];
    rel[1] = hitOut[1] - start[1];
    rel[2] = hitOut[2] - start[2];
    *distOut = func_15143E64(rel);
    return 1;
}
