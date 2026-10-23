/* Free camera step of camera `arg0` (called by func_1512B670). Unless func_1512BAAC handles the frame, the eye
 * (+0x2BC / +0x2C0 / +0x2C4; the height kept 40 below the holder's ceiling +0x17C when it is above its floor
 * +0x180, unless +0x84 bit 0x10) is projected to the screen (func_1501A764 into D_800DC620 / 624 / 628). Off the
 * player's viewport (D_800BE628 entry +0x24..+0x30; x / y clamped first) +0x5F8 = 1 and +0x8B8 = 0. Else +0x8B8 = 1,
 * +0x8BA = y, func_1512B728 gets the clamped point and the depth, func_1512BCA0 gives the turn +0x3EC and the drop
 * D_800DC62C: a turn above 3 rotates the target +0x2F8 about the eye (func_1508EF80) and eases it in (speed 6 / 8,
 * * 1.2 with buttons 3 of the input record), +0x5F8 = 0; else +0x5F8 = 1. The drop lowers +0x2FC; +0x240 == 1 is
 * cleared, +0x698 always. */
void func_1512B2C4(u8 *arg0) {
    u8 *p = arg0;
    u8 *hold;
    u8 *e;
    f32 y;
    f32 sp[3];
    f32 speed;
    f32 rate;
    s32 xi;
    s32 yi;
    s32 lo;
    s32 hi;
    s32 v;
    s32 depth;

    y = *(f32 *)(p + 0x2C0);
    if (func_1512BAAC(p) != 0) {
        return;
    }
    if (!(*(s32 *)(p + 0x84) & 0x10)) {
        hold = *(u8 **)(p + 0x3D0);
        if (*(f32 *)(hold + 0x180) < *(f32 *)(hold + 0x17C) && *(f32 *)(hold + 0x17C) - 40.0f <= y) {
            y = *(f32 *)(hold + 0x17C) - 40.0f;
        }
    }
    func_1501A764(p[0x23D], *(f32 *)(p + 0x2BC), y, *(f32 *)(p + 0x2C4), &D_800DC620, &D_800DC624, &D_800DC628);
    e = (u8 *)D_800BE628 + p[0x23D] * 0x180;
    depth = (s32)D_800DC628;
    lo = (s32)*(f32 *)(e + 0x2C);
    v = (s32)D_800DC620;
    if (v < lo) {
        xi = lo;
    } else {
        hi = (s32)*(f32 *)(e + 0x30);
        xi = (hi < v) ? hi : v;
    }
    lo = (s32)*(f32 *)(e + 0x24);
    v = (s32)D_800DC624;
    if (v < lo) {
        yi = lo;
    } else {
        hi = (s32)*(f32 *)(e + 0x28);
        yi = (hi < v) ? hi : v;
    }
    if ((f32)xi < *(f32 *)(e + 0x2C) || *(f32 *)(e + 0x30) <= (f32)xi || (f32)yi < *(f32 *)(e + 0x24) ||
        *(f32 *)(e + 0x28) <= (f32)yi) {
        *(s16 *)(p + 0x5F8) = 1;
        p[0x8B8] = 0;
        return;
    }
    p[0x8B8] = 1;
    *(s16 *)(p + 0x8BA) = yi;
    func_1512B728(p, xi, yi, depth);
    sp[0] = *(f32 *)(p + 0x2F8);
    sp[1] = *(f32 *)(p + 0x2FC);
    sp[2] = *(f32 *)(p + 0x300);
    func_1512BCA0(p, (f32 *)(p + 0x3EC), &D_800DC62C);
    if (3.0f < fabsf(*(f32 *)(p + 0x3EC))) {
        func_1508EF80((u8 *)sp, p + 0x2BC, *(f32 *)(p + 0x3EC), (u8 *)sp);
        speed = 6.0f;
        rate = 8.0f;
        if (**(u16 **)(p + 0x36C) & 3) {
            speed = 6.0f * 1.2f;
            rate = 8.0f * 1.2f;
        }
        func_150498A0((f32 *)(p + 0x2F8), sp[0], (f32 *)(p + 0x3FC), speed, rate, *(f32 *)(p + 0x7B4));
        func_150498A0((f32 *)(p + 0x2FC), sp[1], (f32 *)(p + 0x400), speed, rate, *(f32 *)(p + 0x7B4));
        func_150498A0((f32 *)(p + 0x300), sp[2], (f32 *)(p + 0x404), speed, rate, *(f32 *)(p + 0x7B4));
        *(s16 *)(p + 0x5F8) = 0;
    } else {
        *(s16 *)(p + 0x5F8) = 1;
    }
    if (D_800DC62C != 0.0f) {
        *(f32 *)(p + 0x2FC) -= D_800DC62C;
    }
    if (*(s32 *)(p + 0x240) == 1) {
        *(s32 *)(p + 0x240) = 0;
    }
    *(s32 *)(p + 0x698) = 0;
}
