/* Place actor `actor` of cutscene slot `slot` at `t` percent (clamped to 0..100) of its path length (SceneActor
 * +0, needs >= 2 path keys). func_1501F7D4 finds the segment `seg` holding that distance, two points (ends[0..2],
 * ends[3..5]) and the sample `k` of the actor's length table (SceneActor +0x38). On a curved segment (key shape
 * +6 == 0, func_15020430) the position is interpolated between the two points by the distance's fraction between
 * the lengths of samples k and k + 1; on a straight one it is the first point. */
void func_1501FD34(s32 actor, f32 t, f32 *x, f32 *y, f32 *z, s32 slot) {
    SceneActor *a;
    f32 ends[6];
    f32 dist;
    f32 frac;
    f32 *len;
    s32 seg;
    s32 k;

    if (D_800C39E8[slot][actor] < 2) {
        return;
    }
    if (100.0f < t) {
        t = 100.0f;
    }
    if (t < 0.0f) {
        t = 0.0f;
    }
    a = &D_800C3E70[slot][actor];
    dist = *(f32 *)a->pad0 * t * D_80096D84;
    k = func_1501F7D4(actor, dist, ends, slot, &seg);
    if (*(u16 *)(D_eu_800C3C88[slot][actor] + seg * 8 + 6) == 0) {
        len = (f32 *)a->state + k;
        if (len[1] - len[0] == 0.0f) {
            frac = 0.0f;
        } else {
            frac = (dist - len[0]) / (len[1] - len[0]);
        }
        *x = (ends[3] - ends[0]) * frac + ends[0];
        *y = (ends[4] - ends[1]) * frac + ends[1];
        *z = (ends[5] - ends[2]) * frac + ends[2];
    } else {
        *x = ends[0];
        *y = ends[1];
        *z = ends[2];
    }
}
