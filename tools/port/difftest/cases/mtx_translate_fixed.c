/* guTranslate-style fixed-point Mtx: identity with the translation (x, y, z) in s15.16 */
void mtx_translate_fixed(s16 *mtx, f32 x, f32 y, f32 z) {
    s32 *w = (s32 *)mtx;
    s32 ix, iy, iz;
    s32 i;

    for (i = 0; i < 16; i++) {
        w[i] = 0;
    }
    ix = (s32)(x * 65536.0f);
    iy = (s32)(y * 65536.0f);
    iz = (s32)(z * 65536.0f);
    mtx[0] = 1;
    mtx[5] = 1;
    mtx[10] = 1;
    mtx[15] = 1;
    mtx[12] = (u32)ix >> 16;
    mtx[13] = (u32)iy >> 16;
    mtx[14] = (u32)iz >> 16;
    mtx[28] = ix;
    mtx[29] = iy;
    mtx[30] = iz;
}
