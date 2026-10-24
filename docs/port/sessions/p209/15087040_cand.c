// rail_node_distance: straight-line distance between track nodes `a` and `b` of D_800D2778 (0 when either is
// 0xFF, no node).
f32 func_15087040(s32 a, s32 b) {
    s16 *pa;
    s16 *pb;
    f32 dx;
    f32 dy;
    f32 dz;

    if (a == 0xFF || b == 0xFF) {
        return 0.0f;
    }
    pa = (s16 *) &D_800D2778[a];
    pb = (s16 *) &D_800D2778[b];
    dx = pa[0] - pb[0];
    dy = pa[1] - pb[1];
    dz = pa[2] - pb[2];
    return sqrtf(dx * dx + dy * dy + dz * dz);
}
