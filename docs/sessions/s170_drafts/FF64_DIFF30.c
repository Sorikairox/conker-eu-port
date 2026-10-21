Gfx *func_1517FF64(Gfx *gfx, s32 x0, s32 y0, s32 x1, s32 y1, s32 i) {
    s32 t;
    s32 l, u, r, d;

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
    l = VP(i, 0x2C);
    u = VP(i, 0x24);
    r = VP(i, 0x30);
    d = VP(i, 0x28);
    if (d <= y0 || y1 <= u || r <= x0 || x1 <= l) {
        return gfx;
    }
    {
        s32 a, b, c, e;
        a = (x0 < l) ? l : ((r < x0) ? r : x0);
        b = (y0 < u) ? u : ((d < y0) ? d : y0);
        c = (x1 < l) ? l : ((r < x1) ? r : x1);
        e = (y1 < u) ? u : ((d < y1) ? d : y1);
        gDPFillRectangle(gfx++, a, b, c, e);
    }
    return gfx;
}
