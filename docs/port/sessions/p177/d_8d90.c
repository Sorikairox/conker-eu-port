s32 func_1507C7C0(u8 *, s16 *, s16 *, s16 *);
s32 func_151451F0(f32 *, f32 *, f32 *, f32, f32, s32, s32, f32 *, f32 *);

// beam_hits_object: whether the beam segment of `rec` (end points +0x34 / +0x40) crosses `obj`'s collision body.
/* The body is an ellipsoid of radius (model kind obj +4 < 0xBB, not 0xFF: D_800D1C90[kind] +0x1A x obj +0x14C, else
 * 50) around obj's position raised by half its height (func_1507C7C0); the segment's y is scaled by radius /
 * half-height about that centre to make it a sphere, then func_151451F0 tests the ray (start, unit direction) against
 * the sphere within the segment length. 0 when the height is 0 or the segment has no length. */
s32 func_151C8D90(u8 *obj, u8 *rec) {
    f32 centre[3];
    f32 start[3];
    f32 dir[3];
    f32 len;
    f32 hitA[3];
    f32 hitB[3];
    f32 tA;
    f32 tB;
    f32 inv;
    f32 radius;
    f32 half;
    f32 scale;
    f32 endY;
    s16 height;
    s16 width;
    s16 rad;
    u8 kind;

    kind = obj[4];
    if (kind < 0xBB && kind != 0xFF) {
        radius = *(s16 *)((u8 *)D_800D1C90[kind] + 0x1A) * *(f32 *)(obj + 0x14C);
    } else {
        radius = 50.0f;
    }
    func_1507C7C0(obj, &height, &width, &rad);
    if ((f32)height == 0.0f) {
        return 0;
    }
    half = (f32)height * 0.5f;
    centre[0] = *(f32 *)(obj + 0x14);
    centre[1] = *(f32 *)(obj + 0x18) + half;
    centre[2] = *(f32 *)(obj + 0x1C);
    scale = radius / half;
    start[0] = *(f32 *)(rec + 0x34);
    start[1] = (*(f32 *)(rec + 0x38) - centre[1]) * scale + centre[1];
    start[2] = *(f32 *)(rec + 0x3C);
    endY = (*(f32 *)(rec + 0x44) - centre[1]) * scale + centre[1];
    dir[0] = *(f32 *)(rec + 0x40) - start[0];
    dir[1] = endY - start[1];
    dir[2] = *(f32 *)(rec + 0x48) - start[2];
    if (!func_15145128(dir, dir, (s32 *)&len, (s32 *)&inv)) {
        return 0;
    }
    if (func_151451F0(start, dir, centre, radius, len, (s32)hitA, (s32)hitB, &tA, &tB) == 0) {
        return 0;
    }
    return 1;
}
