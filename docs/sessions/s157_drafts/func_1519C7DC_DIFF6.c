extern f32 D_800BEDC8;
typedef struct {
    f32 v[3];
} Vec3C;

s32 func_1519C7DC(u8 *arg0) {
    f32 *p = (f32 *)(arg0 + 0x110);
    Vec3C v0;
    Vec3C w0;
    f32 dt2;
    f32 a0, a1, a2, a3, a4, a5;
    s32 i;

    dt2 = D_800BE9A4 * D_800BE9A4;
    v0 = *(Vec3C *)p;
    w0 = *(Vec3C *)(arg0 + 0x11C);
    *(f32 *)(arg0 + 0x114) += *(f32 *)(arg0 + 0x128) * D_800BE9A4;
    *(f32 *)(arg0 + 0x120) += *(f32 *)(arg0 + 0x128) * D_800BE9A4;
    i = D_800BE9E4;
    while (i > 0) {
        i--;
        p[0] *= p[7];
        p[1] *= p[7];
        p[2] *= p[7];
        p[3] *= p[8];
        p[4] *= p[8];
        p[5] *= p[8];
    }
    a0 = (p[0] - v0.v[0]) * D_800BEDC8;
    a1 = (p[1] - v0.v[1]) * D_800BEDC8;
    a2 = (p[2] - v0.v[2]) * D_800BEDC8;
    a3 = (p[3] - w0.v[0]) * D_800BEDC8;
    a4 = (p[4] - w0.v[1]) * D_800BEDC8;
    a5 = (p[5] - w0.v[2]) * D_800BEDC8;
    *(f32 *)(arg0 + 0x34) += v0.v[0] * D_800BE9A4 + 0.5f * a0 * dt2;
    *(f32 *)(arg0 + 0x38) += v0.v[1] * D_800BE9A4 + 0.5f * a1 * dt2;
    *(f32 *)(arg0 + 0x3C) += v0.v[2] * D_800BE9A4 + 0.5f * a2 * dt2;
    *(f32 *)(arg0 + 0x40) += w0.v[0] * D_800BE9A4 + 0.5f * a3 * dt2;
    *(f32 *)(arg0 + 0x44) += w0.v[1] * D_800BE9A4 + 0.5f * a4 * dt2;
    *(f32 *)(arg0 + 0x48) += w0.v[2] * D_800BE9A4 + 0.5f * a5 * dt2;
    return 1;
}
