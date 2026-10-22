/* Heading of actor `actor` of cutscene slot `slot` at `t` percent (clamped to 0..100) of its path length (needs
 * >= 2 path keys), in degrees (func_150484A0(dx, dz) * D_80096D8C). func_1501F7D4 finds the segment for that
 * distance: on a curved segment (key shape +6 == 0, func_15020430) the direction runs between the two curve
 * points it returns (first - second), on a straight one between the segment's middle control points
 * (func_15020090, third - second). */
void func_1501FF10(s32 actor, f32 t, f32 *out, s32 slot) {
    f32 pts[12];
    f32 ends[6];
    f32 dx;
    f32 dz;
    s32 seg;

    if (D_800C39E8[slot][actor] < 2) {
        return;
    }
    if (100.0f < t) {
        t = 100.0f;
    }
    if (t < 0.0f) {
        t = 0.0f;
    }
    func_1501F7D4(actor, *(f32 *)D_800C3E70[slot][actor].pad0 * t * D_80096D88, ends, slot, &seg);
    if (*(u16 *)(D_eu_800C3C88[slot][actor] + seg * 8 + 6) == 0) {
        dx = ends[0] - ends[3];
        dz = ends[2] - ends[5];
    } else {
        func_15020090((u8 *)pts, D_eu_800C3C88[slot][actor], seg, D_800C39E8[slot][actor]);
        dx = pts[6] - pts[3];
        dz = pts[8] - pts[5];
    }
    *out = func_150484A0(dx, dz) * D_80096D8C;
}
