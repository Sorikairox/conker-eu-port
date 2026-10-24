// rail_spline_points: the four spline control points of a rail record (nodes rec[0x2B..0x2E] of D_800D2778) as
// separate x / y / z float arrays: each node's position moved by rec->unk0 toward its first type-4 link (x and z only;
// the node itself when it has none); a missing node (0xFF) gives (i * 64, 0, 0). Returns 4 (the point count; the
// callers ignore it).
s32 func_150893AC(struct_eu_80087640 *rec, s32 *xs, s32 *ys, s32 *zs) {
    struct_eu_800D2778 *node;
    struct_eu_800D2778 *to;
    u8 *p;
    u8 id;
    u8 link;
    s32 i;
    s32 k;

    for (i = 0; i < 4; i++) {
        id = ((u8 *) rec)[0x2B + i];
        if (id == 0xFF) {
            ((f32 *) xs)[i] = i << 6;
            ((f32 *) ys)[i] = 0.0f;
            ((f32 *) zs)[i] = 0.0f;
            continue;
        }
        node = &D_800D2778[id];
        to = node;
        p = (u8 *) node;
        for (k = 0; k < 5; k++) {
            link = p[9 + k];
            if (link != 0xFF && ((u8 *) &D_800D2778[link])[0xE] == 4) {
                to = &D_800D2778[link];
                break;
            }
        }
        ((f32 *) xs)[i] = node->unk0 + (f32) (to->unk0 - node->unk0) * rec->unk0;
        ((f32 *) ys)[i] = node->unk2;
        ((f32 *) zs)[i] = node->unk4 + (f32) (to->unk4 - node->unk4) * rec->unk0;
    }
    return i;
}
