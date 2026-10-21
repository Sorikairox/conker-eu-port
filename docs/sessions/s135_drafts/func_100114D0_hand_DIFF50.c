s32 func_1000A420(s32, s32, s32, f32, s32, s32, s32, s32, s32, s32 *, s32 *, s32 *);

s32 func_100114D0(s32 x, s32 y, s32 z, s32 arg3, s32 arg4, s32 arg5, s32 *arg6, s32 *arg7, s32 *arg8) {
    SfxListener *best;
    SfxListener *p;
    u32 i;
    u32 min;
    u32 d;
    s32 ret;
    s32 vol;
    s32 dx;
    s32 dy;
    s32 dz;

    best = D_80042308;
    if (D_80082FA0 != 0) {
        p = D_80042308;
        min = -1;
        for (i = 0; i <= (u32)D_80082FA0; i++, p++) {
            dx = x - p->ex;
            dy = y - p->ey;
            dz = z - p->ez;
            d = dx * dx + dy * dy + dz * dz;
            if (d < min) {
                min = d;
                best = p;
            }
        }
    }
    ret = func_1000A420(x - best->ex, y - best->ey, z - best->ez, best->f, x - best->x, y - best->y, z - best->z,
                        arg4, arg5, arg6, &vol, arg8);
    *arg7 = (u32)(vol * arg3) >> 15;
    return ret;
}
