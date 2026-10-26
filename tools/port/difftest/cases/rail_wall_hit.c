// rail_wall_hit: where the move from (x, z) by (dx, dz) first crosses a wall: the type-1 nodes of g_rail_nodes in the
// height band of `y` (node +6 = rail_band_for_height(y)) and their links (+9..+0xD) to higher-numbered type-1 nodes form
// segments; a segment counts when the move's start and end lie on different sides of its line and the crossing
// point lies within the segment. Returns -1 when none is hit, else the move length times the crossing fraction of
// the last segment whose line the move crossed (Rare uses that fraction, not the smallest one it keeps).
f32 rail_wall_hit(f32 x, f32 y, f32 z, f32 dx, f32 dz) {
    struct_eu_800D2778 *a;
    struct_eu_800D2778 *b;
    s32 band;
    s32 i;
    s32 k;
    u8 link;
    f32 ex;
    f32 ez;
    f32 c;
    f32 d0;
    f32 d1;
    f32 a0;
    f32 a1;
    f32 s;
    f32 hit;
    f32 best;

    band = rail_band_for_height(y);
    best = 100.0f;
    s = 0.0f; // only read after a crossing set it
    for (i = 0; i < g_rail_node_count; i++) {
        a = &g_rail_nodes[i];
        if (((u8 *) a)[0xE] != 1 || ((u8 *) a)[6] != band) {
            continue;
        }
        for (k = 0; k < 5; k++) {
            link = ((u8 *) a)[9 + k];
            if (link == 0xFF || link <= i) {
                continue;
            }
            b = &g_rail_nodes[link];
            if (((u8 *) b)[0xE] != 1) {
                continue;
            }
            // side of the segment's line (normal (ez, -ex)) for the start and the end of the move
            ez = b->unk4 - a->unk4;
            ex = -(f32) (b->unk0 - a->unk0);
            c = -(a->unk0 * ez + ex * a->unk4);
            d0 = x * ez + z * ex + c;
            d1 = (x + dx) * ez + (z + dz) * ex + c;
            if (!((d1 < 0.0f && 0.0f <= d0) || (d0 < 0.0f && 0.0f <= d1))) {
                continue;
            }
            a1 = d1;
            if (d1 < 0.0f) {
                a1 = -d1;
            }
            a0 = d0;
            if (d0 < 0.0f) {
                a0 = -d0;
            }
            s = a0 / (a0 + a1);
            // position of the crossing point and of b along the segment (a = 0)
            ex = -ex;
            c = -(a->unk0 * ex + ez * a->unk4);
            hit = (s * dx + x) * ex + (s * dz + z) * ez + c;
            d1 = b->unk0 * ex + ez * b->unk4 + c;
            if ((0.0f < d1 && 0.0f < hit && hit <= d1) || (d1 < 0.0f && hit < 0.0f && d1 <= hit)) {
                if (s < best) {
                    best = s;
                }
            }
        }
    }
    if (best <= 1.0f) {
        return sqrtf(dx * dx + dz * dz) * s;
    }
    return -1.0f;
}
