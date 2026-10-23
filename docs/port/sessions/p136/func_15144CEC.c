void func_150A7EE0(u8 *, f32, f32, f32, f32 *, f32 *, f32 *, f32 *);
extern u8 D_800DA130[]; /* per view: 4x4 f32 projection matrix (0x40 bytes) */
extern f32 D_800D9F40;

/*
 * world_to_screen: projects the world point pos (3 f32) with view `view`'s matrix (D_800DA130 + view * 0x40,
 * func_150A7EE0) into scr[0..1], *oz and *ow (each out pointer may be NULL: a local is used). Fails (0) when
 * w >= 6000, w <= D_800D9F40 or w == 0; else *oinv = 1 / w and scr becomes the viewport position: x = inv * x *
 * (half width +0x0C + 5) + centre x +0x34, y = centre y +0x38 - inv * y * (half height +0x10 + 5) of
 * D_800BE628 + view * 0x180. Returns 1.
 */
s32 func_15144CEC(f32 *pos, f32 *scr, f32 *oz, f32 *ow, f32 *oinv, u8 view) {
    f32 z, w, inv;
    u8 *vp;

    if (oz == NULL) {
        oz = &z;
    }
    if (ow == NULL) {
        ow = &w;
    }
    if (oinv == NULL) {
        oinv = &inv;
    }
    func_150A7EE0(D_800DA130 + (view << 6), pos[0], pos[1], pos[2], &scr[0], &scr[1], oz, ow);
    if (*ow >= 6000.0f || *ow <= D_800D9F40) {
        return 0;
    }
    if (*ow == 0.0f) {
        return 0;
    }
    *oinv = 1.0f / *ow;
    vp = (u8 *) D_800BE628 + view * 0x180;
    scr[0] = *oinv * (scr[0] * (*(f32 *) (vp + 0x0C) + 5.0f)) + *(f32 *) (vp + 0x34);
    vp = (u8 *) D_800BE628 + view * 0x180;
    scr[1] = *(f32 *) (vp + 0x38) - *oinv * (scr[1] * (*(f32 *) (vp + 0x10) + 5.0f));
    return 1;
}
