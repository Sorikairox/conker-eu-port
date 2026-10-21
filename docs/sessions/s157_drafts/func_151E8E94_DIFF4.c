extern f32 D_800901BC;
extern f32 D_800901C0;

Gfx *func_151E8E94(Gfx *gdl, s32 xl, s32 yl, s32 xh, s32 yh, s32 tile, s32 s, s32 t, s32 dsdx, s32 dtdy) {
    if (D_800901BC != 1.0f) {
        xl = xl * D_800901BC;
        xh = xh * D_800901BC;
        yl = yl * D_800901C0;
        yh = yh * D_800901C0;
        dsdx = dsdx / D_800901BC;
        dtdy = dtdy / D_800901C0;
    }
    gSPScisTextureRectangle(gdl++, xl, yl, xh, yh, tile, s, t, dsdx, dtdy);
    return gdl;
}
