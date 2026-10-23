extern u8 D_800D2780;
// point_bands_build: groups the D_800D2778 points by band (byte +6, 6 bands) and keeps each band's height range
// (+2). The used bands go in D_800D2770 (count D_800D2780) and the split heights between consecutive used bands in
// D_800D2788 (midpoint of band i's top and band i+1's bottom; a last 100000 entry ends func_15086218's search).
// Returns 1 when two consecutive bands overlap. Level start (func_15085FE0).
s32 func_15086058(void) {
    f32 top[6];
    f32 bottom[6];
    s32 overlap = 0;
    s32 i;
    struct_eu_800D2778 *p;
    f32 y;
    u8 a;
    u8 b;

    for (i = 0; i < 6; i++) {
        bottom[i] = 10000.0f;
        top[i] = -10000.0f;
    }
    for (i = 0, p = D_800D2778; i < D_80087630; i++, p++) {
        y = p->unk2;
        if (y < bottom[p->pad6]) {
            bottom[p->pad6] = y;
        }
        if (top[p->pad6] < y) {
            top[p->pad6] = y;
        }
    }
    D_800D2780 = 0;
    for (i = 0; i < 6; i++) {
        if (bottom[i] <= top[i]) {
            D_800D2770[D_800D2780++] = i;
        }
    }
    for (i = 0; i < D_800D2780 - 1; i++) {
        a = D_800D2770[i];
        b = D_800D2770[i + 1];
        D_800D2788[i] = (bottom[b] + top[a]) * 0.5f;
        if (bottom[b] < top[a]) {
            overlap = 1;
        }
    }
    D_800D2788[i] = 100000.0f;
    return overlap;
}
