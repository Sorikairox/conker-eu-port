/* P197 */
extern f32 D_800D9F40; /* screen width (also the near-depth bound here) */
extern f32 D_800D3A00[2];

/* cvt.w.s with the default FCSR mode: round to nearest, ties to even */
#define VIEW66F0_RINT(f)                                                                             \
    (((f) >= 8388608.0f || (f) <= -8388608.0f) ? (s32)(f)                                            \
     : ((f) >= 0.0f) ? (s32)(((f) + 8388608.0f) - 8388608.0f)                                       \
                     : -(s32)((-(f) + 8388608.0f) - 8388608.0f))

/*
 * view_sphere_depth: P197: view test of a box around (x, y, z) (hand asm, FR=1 odd FPRs as singles, epilogue
 * func_150A6834), the frustum variant of func_150A6840 without a camera record: m (4x4 floats) maps the point to
 * (u, v, w); outside when w - r > -D_800D9F40 (in front of the near bound) or w + r < -far, or when u / v scaled by
 * D_800D3A00[0] / [1] leave +-(depth + half size) with the half sizes r / ry scaled by 0.70710677 (sqrt(1/2)),
 * depth = -w (the asm's c.ule / c.olt: a NaN passes every test). Returns 0 when outside, else round(-w) (0 stays 0).
 */
s32 func_150A66F0(f32 *m, f32 x, f32 y, f32 z, f32 r, f32 ry, f32 far) {
    f32 u, v, w, depth, lim, rs, rys;

    w = (m[2] * x + m[6] * y) + (m[10] * z + m[14]);
    if (w - r > -D_800D9F40) {
        return 0;
    }
    if (w + r < -far) {
        return 0;
    }
    depth = -w;
    u = (m[0] * x + m[4] * y) + (m[8] * z + m[12]);
    rs = r * 0.70710677f;
    lim = depth + rs;
    if ((u - rs) * D_800D3A00[0] > lim) {
        return 0;
    }
    if ((u + rs) * D_800D3A00[0] < -lim) {
        return 0;
    }
    v = (m[1] * x + m[5] * y) + (m[9] * z + m[13]);
    rys = ry * 0.70710677f;
    if ((v - rys) * D_800D3A00[1] > lim) {
        return 0;
    }
    if ((v + rys) * D_800D3A00[1] < -lim) {
        return 0;
    }
    return VIEW66F0_RINT(depth);
}
