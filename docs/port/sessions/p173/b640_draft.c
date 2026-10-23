extern u16 D_800C5BC0[]; extern u8 *D_800843D0[]; extern u8 D_80096CD0[];
// model_vertex_colours_blend: recolours the object's current vertex buffer (obj+0x28C, slot obj+0x1C8, buffer
// D_800BE9C0). Each vertex's group ((u16 +6 >> 8) & 0x7F, 1..5; 0 = keep) picks a key colour ramp; the group's
// value t in 0..1 (vals[group - 1] when perGroup, else vals[0]) is linearly interpolated between the two key
// colours around it and written to the vertex colour (+0xC..+0xE). Groups 6 and up are skipped.
void func_eu_1501B640(struct127 *obj, f32 *vals, s32 perGroup) {
    u8 *o = (u8 *) obj;
    u8 *vtx;
    u8 *c0;
    u8 *c1;
    s32 i;
    s32 group;
    s32 prev;
    s32 k;
    f32 x;
    f32 seg;
    f32 t;
    u8 idx;
    u8 r;
    u8 g;
    u8 b;

    vtx = *(u8 **) (o + 0x28C + o[0x1C8] * 8 + D_800BE9C0 * 4);
    if (vtx == NULL) {
        return;
    }
    prev = -1;
    for (i = 0; i < D_800C5BC0[o[4]]; i++, vtx += 0x10) {
        group = (*(u16 *) (vtx + 6) & 0x7F00) >> 8;
        if (group == 0) {
            continue;
        }
        if (group != prev) {
            if (group >= 6) {
                continue;
            }
            prev = group;
            k = group - 1;
            x = perGroup ? vals[k] : vals[0];
            seg = 1.0f / (f32) (D_80096CD0[k] - 1);
            idx = (u32) (x / seg);
            c0 = D_800843D0[k] + idx * 3;
            c1 = c0 + 3;
            t = (x - (f32) idx * seg) / seg;
            r = (u32) ((c1[0] - c0[0]) * t + c0[0]);
            g = (u32) ((c1[1] - c0[1]) * t + c0[1]);
            b = (u32) ((c1[2] - c0[2]) * t + c0[2]);
        }
        vtx[0xC] = r;
        vtx[0xD] = g;
        vtx[0xE] = b;
    }
}
