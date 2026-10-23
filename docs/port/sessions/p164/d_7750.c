s32 func_150ACEA0(f32, f32, f32, f32, f32, f32, s32, void *, f32 *, f32 *, f32 *, f32 *, s32 *, s32, f32);
void func_151C7B1C(f32 *, void *, f32 *, void *, void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32, s32);

// record_beam_start: D_80082EA0 entry 8 (level-start record). Unless rec +0x14 is 1: the segment from the record's
// point (s16 x, y, z) along the length +8 rotated by the angles +0xC / +0x10; two ray casts (func_150ACEA0) from its
// middle towards both ends give the end points (geometry hits); when both hit, func_151C7B1C builds the beam between
// them with the colour +0x1C (r, g, b bytes) and the option bits / bytes of +0x18 and +0x20. Always returns 1.
s32 func_151C7750(u8 *rec) {
    f32 m[4][4];
    f32 p0[3];
    f32 p1[3];
    f32 d[3];
    f32 mid[3];
    u8 triA[0x14];
    f32 hitA[3];
    u8 triB[0x14];
    f32 hitB[3];
    f32 distA;
    f32 distB;
    s32 auxA;
    s32 auxB;
    s32 okA;
    s32 okB;
    u32 opt;
    u32 col;
    u32 sc;

    if (rec[0x14] == 1) {
        return 1;
    }
    p0[0] = *(s16 *) (rec + 0);
    p0[1] = *(s16 *) (rec + 2);
    p0[2] = *(s16 *) (rec + 4);
    func_150A8050(m, *(f32 *) (rec + 0xC), *(f32 *) (rec + 0x10), 0.0f);
    func_150A7E40(m, 0.0f, *(s16 *) (rec + 8), 0.0f, &p1[0], &p1[1], &p1[2]);
    p1[0] += p0[0];
    p1[1] += p0[1];
    p1[2] += p0[2];
    d[0] = p1[0] - p0[0];
    d[1] = p1[1] - p0[1];
    d[2] = p1[2] - p0[2];
    mid[0] = d[0] * 0.5f + p0[0];
    mid[1] = d[1] * 0.5f + p0[1];
    mid[2] = d[2] * 0.5f + p0[2];
    okA = func_150ACEA0(mid[0], mid[1], mid[2], -d[0], -d[1], -d[2], 0, triA, &hitA[0], &hitA[1], &hitA[2], &distA,
                        &auxA, 0, 0.0f);
    okB = func_150ACEA0(mid[0], mid[1], mid[2], d[0], d[1], d[2], 0, triB, &hitB[0], &hitB[1], &hitB[2], &distB,
                        &auxB, 0, 0.0f);
    if (okA == 0 || okB == 0) {
        return 1;
    }
    opt = *(u32 *) (rec + 0x18);
    col = *(u32 *) (rec + 0x1C);
    sc = *(u32 *) (rec + 0x20);
    func_151C7B1C(hitA, triA, hitB, triB, rec, rec, col & 0xFF, (col >> 8) & 0xFF, (col >> 16) & 0xFF,
                  (opt >> 24) & 1, opt & 0xFF, (opt >> 8) & 0xFF, (opt >> 16) & 0xFF, (opt >> 25) & 1, (opt >> 26) & 1,
                  ((opt >> 27) & 1) == 0, ((opt >> 29) & 1) == 0, (opt >> 30) & 1, (opt >> 28) & 1,
                  (f32) (sc & 0xFF) * 0.024639944f, (f32) ((sc >> 8) & 0xFF) * 0.003079993f, (opt >> 31) == 0, 0xFF, 1);
    return 1;
}
