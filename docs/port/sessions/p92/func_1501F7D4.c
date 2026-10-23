/* Path point lookup for actor `actor` of cutscene slot `slot` at distance `dist` along its path: binary search of
 * the segment start lengths (SceneActor +4, D_800C39E8 key count entries) gives `seg` (*segOut); a segment change
 * (SceneActor +0x3C) prepares the segment's cubic (func_15020920: coefficients D / C / B / A at +0x08 / +0x14 /
 * +0x20 / +0x2C, xyz each). Curved segment (key shape +6 == 0): binary search of the 101 sample lengths
 * (SceneActor +0x38) gives the sample k; out[0..2] / out[3..5] = the cubic at u = k * 0.01 and (k + 1) * 0.01;
 * returns k. Straight segment: out[0..2] = out[3..5] = the point between the middle control points (func_15020090)
 * at the distance's fraction of the segment; the asm then returns an uninitialised stack word (callers only read
 * the result of a curved segment): 0 here. A slot without keys leaves `seg` uninitialised in the asm (0 here). */
s32 func_1501F7D4(s32 actor, f32 dist, f32 *out, s32 slot, s32 *segOut) {
    SceneActor *a;
    f32 pts[12];
    f32 *tab;
    f32 *c;
    f32 *o;
    f32 frac;
    f32 u;
    s32 lo;
    s32 hi;
    s32 mid;
    s32 seg;
    s32 k;
    s32 j;
    u16 shape;

    a = &D_800C3E70[slot][actor];
    seg = 0;
    lo = 0;
    hi = D_800C39E8[slot][actor] - 1;
    if (hi >= 0) {
        tab = a->keys;
        do {
            mid = (lo + hi) / 2;
            if (dist < tab[mid]) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
            if (tab[mid] <= dist && dist <= tab[mid + 1]) {
                break;
            }
        } while (lo <= hi);
        seg = mid;
    }
    *segOut = seg;
    if (seg != a->pad3C[0]) {
        func_15020920(actor, seg, slot);
    }
    shape = *(u16 *)(D_eu_800C3C88[slot][actor] + seg * 8 + 6);
    func_15020090((u8 *)pts, D_eu_800C3C88[slot][actor], seg, D_800C39E8[slot][actor]);
    if (shape == 0) {
        tab = a->state;
        lo = 0;
        hi = 100;
        do {
            k = (lo + hi) / 2;
            if (dist < tab[k]) {
                hi = k - 1;
            } else {
                lo = k + 1;
            }
            if (tab[k] <= dist && dist <= tab[k + 1]) {
                break;
            }
        } while (lo <= hi);
        c = (f32 *)a->pad8;
        for (j = 0; j < 2; j++) {
            u = (f32)(k + j) * D_80096D80;
            o = out + j * 3;
            o[0] = c[0] + ((c[9] * u + c[6]) * u + c[3]) * u;
            o[1] = c[1] + ((c[10] * u + c[7]) * u + c[4]) * u;
            o[2] = c[2] + ((c[11] * u + c[8]) * u + c[5]) * u;
        }
        return k;
    }
    tab = a->keys;
    if (tab[seg + 1] - tab[seg] == 0.0f) {
        frac = 0.0f;
    } else {
        frac = (dist - tab[seg]) / (tab[seg + 1] - tab[seg]);
    }
    for (j = 0; j < 2; j++) {
        o = out + j * 3;
        o[0] = pts[3] + (pts[6] - pts[3]) * frac;
        o[1] = pts[4] + (pts[7] - pts[4]) * frac;
        o[2] = pts[5] + (pts[8] - pts[5]) * frac;
    }
    return 0;
}
