// view_fill_rect: appends a G_FILLRECT (F6) for the rectangle (x0, y0) - (x1, y1) (either corner order) clipped
// to view's screen box (camera D_800BE628 + view * 0x180: f32 left +0x2C, top +0x24, right +0x30, bottom +0x28,
// truncated); nothing when it lies outside (touching counts as outside). Returns the DL end.
u8 *func_1517FF64(u8 *dl, s32 x0, s32 y0, s32 x1, s32 y1, s32 view) {
    u8 *cam;
    s32 left, top, right, bottom;
    s32 t;

    if (x1 < x0) {
        t = x0;
        x0 = x1;
        x1 = t;
    }
    if (y1 < y0) {
        t = y0;
        y0 = y1;
        y1 = t;
    }
    cam = (u8 *) D_800BE628 + view * 0x180;
    left = *(f32 *) (cam + 0x2C);
    top = *(f32 *) (cam + 0x24);
    bottom = *(f32 *) (cam + 0x28);
    right = *(f32 *) (cam + 0x30);
    if (!(y0 < bottom && top < y1 && x0 < right && left < x1)) {
        return dl;
    }
    x0 = (x0 < left) ? left : (right < x0) ? right : x0;
    y0 = (y0 < top) ? top : (bottom < y0) ? bottom : y0;
    x1 = (x1 < left) ? left : (right < x1) ? right : x1;
    y1 = (y1 < top) ? top : (bottom < y1) ? bottom : y1;
    ((s32 *) dl)[1] = ((x0 & 0x3FF) << 14) | ((y0 & 0x3FF) << 2);
    ((s32 *) dl)[0] = 0xF6000000 | ((x1 & 0x3FF) << 14) | ((y1 & 0x3FF) << 2);
    return dl + 8;
}
