f32 func_1505D34C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4);
void func_1505D408(struct127 *arg0, struct127 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7);

/* Box test of record `rec` (at x, y, z; height `scale`, radius `radius`) against object `o` (id 0x34, called by
 * func_1505D6F0): o's box has radius r and height h (scaled by o +0x14C / +0x150), centre offset (ox, oz) turned
 * by o's heading (func_1505D34C) and height cy (scaled by +0x150). The vertical distance is scaled by
 * (scale + r / h) / 2; inside the sphere of radius radius + r: func_1505D408 (push out). */
void func_1505D5D0(struct127 *rec, struct127 *o, f32 x, f32 y, f32 z, f32 scale, f32 radius, s32 i, f32 r, f32 h,
                   f32 cy, f32 ox, f32 oz) {
    f32 dx;
    f32 dy;
    f32 dz;
    f32 d2;
    f32 lim;

    dx = func_1505D34C(o->unk40, ox, oz, *(f32 *)((u8 *)o + 0x14C), &oz);
    r = r * *(f32 *)((u8 *)o + 0x14C);
    h = h * *(f32 *)((u8 *)o + 0x150);
    dx = x - (o->x_position + dx);
    dz = z - (o->z_position + oz);
    dy = y - (o->y_position + cy * *(f32 *)((u8 *)o + 0x150));
    dy = dy * ((scale + r / h) * 0.5f);
    d2 = dx * dx + dy * dy + dz * dz;
    lim = radius + r;
    if (d2 < lim * lim) {
        func_1505D408(rec, o, dx, dy, dz, d2, lim, i);
    }
}
