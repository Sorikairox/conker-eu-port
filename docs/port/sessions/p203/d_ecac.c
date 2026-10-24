void func_151D6310(s32, s16, s32, u8 **, u8 *);
f32 func_15048A40(u8);
f32 func_150489B0(u8);
extern f32 D_800DD608[]; /* per view: sin of the camera yaw */
extern f32 D_800DD618[]; /* per view: cos of the camera yaw */

// particle_quad_velocity_build: P203: entry 5 of the particle draw table D_8008A1BC (game_169510): builds the 4
// vertices of the particle `p` for view `view` (a quad stretched along its screen-space motion, e.g. the
// character-effect flames). func_151D6310 gives the view's vertex block (p +0x100[view], 0x40 bytes); when it is
// new, both of its halves get the template vertices p +0xC0. Lean: the motion since the last frame (+0x40 - +0x34,
// +0x48 - +0x3C) across the view (cos / sin of the view, D_800DD618 / D_800DD608) times D_800BEDC8, then
// sqrt(|t|) * p +0x160, at most pi / 2, negative for a forward motion; byte angle = lean * 256 / (2 pi) (Rare's
// unsigned conversion makes every negative angle 0xFF). Half width p +0x2C, half height p +0x30 rotated by the
// angle (func_15048A40 sin, func_150489B0 cos) around the position p +0x34; the s16 corners go to +0x00, +0x10,
// +0x20, +0x30 of the block (the view's horizontal axis is (cos, -sin) in x / z). Returns the block, NULL when
// none is available.
u8 *func_1518ECAC(u8 *p, s16 view) {
    u8 *blk;
    u8 fresh;
    s16 *v;
    f32 s, c, t, lean, sn, cs, a, b, hs, hc, e;
    s32 n, neg;
    u8 ang;

    func_151D6310((s32) (p + 0x100), view, 0x40, &blk, &fresh);
    if (blk == NULL) {
        return NULL;
    }
    if (fresh) {
        memcpy(*(u8 **) (p + 0x100 + view * 4), (u8 **) (p + 0xC0), 0x40);
        memcpy(*(u8 **) (p + 0x100 + view * 4) + 0x40, (u8 **) (p + 0xC0), 0x40);
    }
    s = D_800DD608[view];
    c = D_800DD618[view];
    t = ((*(f32 *) (p + 0x40) - *(f32 *) (p + 0x34)) * c - s * (*(f32 *) (p + 0x48) - *(f32 *) (p + 0x3C))) *
        D_800BEDC8;
    neg = TRUE;
    if (t < 0.0f) {
        t = -t;
        neg = FALSE;
    }
    lean = sqrtf(t) * *(f32 *) (p + 0x160);
    if (1.5707964f < lean) {
        lean = 1.5707964f;
    }
    if (neg) {
        lean = -lean;
    }
    /* (u32) conversion as IDO does it: truncation, a negative result becomes 0xFFFFFFFF */
    n = (s32) (lean * 40.7436638f);
    ang = (n < 0) ? 0xFF : n;
    sn = func_15048A40(ang);
    cs = func_150489B0(ang);
    a = *(f32 *) (p + 0x2C) * cs;
    b = *(f32 *) (p + 0x2C) * sn;
    hs = *(f32 *) (p + 0x30) * sn;
    hc = *(f32 *) (p + 0x30) * cs;
    v = (s16 *) blk;
    v[0] = *(f32 *) (p + 0x34) + a * c;
    v[1] = *(f32 *) (p + 0x38) + b;
    v[2] = *(f32 *) (p + 0x3C) - a * s;
    v[8] = *(f32 *) (p + 0x34) + -a * c;
    v[9] = *(f32 *) (p + 0x38) - b;
    v[10] = *(f32 *) (p + 0x3C) - -a * s;
    e = -(a + hs);
    v[16] = *(f32 *) (p + 0x34) + e * c;
    v[17] = (*(f32 *) (p + 0x38) + hc) - b;
    v[18] = *(f32 *) (p + 0x3C) - e * s;
    e = a - hs;
    v[24] = *(f32 *) (p + 0x34) + e * c;
    v[25] = (*(f32 *) (p + 0x38) + hc) + b;
    v[26] = *(f32 *) (p + 0x3C) - e * s;
    return blk;
}
