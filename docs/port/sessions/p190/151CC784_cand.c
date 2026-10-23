/*
 * obj_height_in_range: P190. A height clamped to [obj +0x88, obj +0x8C]: with flag 4 of obj[0x7C] the point
 * D_800C3958[(s8)obj[0xC4]] +0x28 percent of the way from +0x88 to +0x8C, else the middle of +0x19C / +0x1A0 of
 * the object at obj +0x70.
 */
f32 func_151CC784(u8 *arg0) {
    f32 lo, hi, h;
    u8 *o;

    if (arg0[0x7C] & 4) {
        lo = *(f32 *)(arg0 + 0x88);
        h = lo + (*(f32 *)(arg0 + 0x8C) - lo) * (*(f32 *)((u8 *)D_800C3958 + (s8)arg0[0xC4] * 0x44 + 0x28) * 0.01f);
    } else {
        o = *(u8 **)(arg0 + 0x70);
        lo = *(f32 *)(arg0 + 0x88);
        h = (*(f32 *)(o + 0x19C) + *(f32 *)(o + 0x1A0)) * 0.5f;
    }
    if (h < lo) {
        return lo;
    }
    hi = *(f32 *)(arg0 + 0x8C);
    if (hi < h) {
        return hi;
    }
    return h;
}
