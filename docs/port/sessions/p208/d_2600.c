// mtx_look_along_scaled: P208: builds in `m` (guMtxF2L) the matrix that puts a model at (x0, y0, z0) facing
// (x1, y1, z1): row 2 is the unit direction, row 0 the horizontal side vector (dir.z, 0, -dir.x) normalised, row 1
// the up vector dir x side normalised; every row is scaled per column by (sx, sy, sz), rows 0 / 2 also by `scale`
// and row 1 by `up_scale`. game_eu_E66D0's prototype gives it an s32 result: the callers ignore it, returns 0.
s32 func_15142600(Mtx *m, f32 scale, f32 up_scale, f32 sx, f32 sy, f32 sz, f32 x0, f32 y0, f32 z0, f32 x1, f32 y1,
                  f32 z1) {
    f32 mf[4][4];
    f32 dx, dy, dz, inv, fx, fy, fz, rx, rz, ux, uy, uz;

    dx = x1 - x0;
    dy = y1 - y0;
    dz = z1 - z0;
    inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz);
    fx = dx * inv;
    fy = dy * inv;
    fz = dz * inv;
    inv = 1.0f / sqrtf(fz * fz + -fx * -fx);
    rx = fz * inv;
    rz = -fx * inv;
    ux = fy * rz;
    uy = fz * rx - fx * rz;
    uz = -fy * rx;
    inv = 1.0f / sqrtf(ux * ux + uy * uy + uz * uz);

    mf[0][0] = rx * sx * scale;
    mf[0][1] = 0.0f;
    mf[0][2] = rz * sz * scale;
    mf[0][3] = 0.0f;
    mf[1][0] = ux * inv * sx * up_scale;
    mf[1][1] = uy * inv * sy * up_scale;
    mf[1][2] = uz * inv * sz * up_scale;
    mf[1][3] = 0.0f;
    mf[2][0] = fx * sx * scale;
    mf[2][1] = fy * sy * scale;
    mf[2][2] = fz * sz * scale;
    mf[2][3] = 0.0f;
    mf[3][0] = x0;
    mf[3][1] = y0;
    mf[3][2] = z0;
    mf[3][3] = 1.0f;
    guMtxF2L(mf, m);
    return 0;
}
