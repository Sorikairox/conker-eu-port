/* Camera transition (+0x7F4 state: 0 idle, 1 start, 2 running): moves the eye +0x2BC from the start point +0x7F8
 * to the end point +0x804 (end x / z follow the player, y from func_15124C38) over +0x834 ticks (countdown
 * +0x840, progress t = +0x830), blending yaw +0x37C, distance D_800DC430, height D_800DC434 and the extra
 * angles +0x5E8 / +0x3A8 (func_15048720 = angle lerp). The camera mode +0x23C cancels it. Returns 0 when idle,
 * nonzero while it runs (on the last tick the asm returns the +0x3D0 pointer left in v0; func_15048720 does
 * not touch v0), the state itself for an unknown state. */
s32 func_15128030(struct108 *arg0) {
    u8 *p = (u8 *)arg0;
    u8 *t = p + 0x7F4;
    u8 *pl;
    f32 dx;
    f32 dz;
    f32 yaw;
    s32 last;

#define TF(o) (*(f32 *)(t + (o)))
#define PF(o) (*(f32 *)(p + (o)))
#define PL (*(u8 **)(p + 0x3D0))
    if (p[0x23C] != 0) {
        *(u16 *)(t + 0x40) = 0;
        *(u16 *)t = 0;
        TF(0x2C) = 999.0f;
        return 0;
    }
    switch (*(u16 *)t) {
        case 0:
            return 0;
        case 1:
            pl = PL;
            dx = PF(0x2F8) - *(f32 *)(pl + 0x14);
            dz = PF(0x300) - *(f32 *)(pl + 0x1C);
            TF(0x1C) = sqrtf(dx * dx + dz * dz);
            PF(0x5E8) = 0.0f;
            PF(0x660) = 0.0f;
            PF(0x3A8) = 0.0f;
            PF(0x65C) = 0.0f;
            PF(0x83C) = PF(0x2FC) - PF(0x35C);
            func_15125594(arg0);
            TF(0x20) = PF(0x37C);
            func_15128D50(arg0, &TF(0x34), &TF(0x38));
            *(s16 *)(p + 0x840) = *(u16 *)(t + 0x40);
            TF(0x3C) = 0.0f;
            *(u16 *)t = 2;
            /* fallthrough */
        case 2:
            break;
        default:
            return *(u16 *)t;
    }
    last = *(s16 *)(p + 0x840) == 0;
    if (p[0x23C] != 0) {
        TF(0x3C) = 1.0f;
        last = TRUE;
        *(s16 *)(p + 0x840) = 0;
    } else {
        TF(0x3C) = 1.0f - (f32) * (s16 *)(p + 0x840) / (f32) * (u16 *)(t + 0x40);
    }
    func_15123568(arg0);
    TF(0x28) = PF(0x374);
    PF(0x838) = PF(0x348);
    TF(0x10) = *(f32 *)(PL + 0x14);
    func_15124C38(arg0, &TF(0x14));
    yaw = TF(0x2C);
    TF(0x18) = *(f32 *)(PL + 0x1C);
    while (yaw < 0.0f) {
        yaw += 360.0f;
    }
    pl = PL;
    PF(0x2A4) = *(f32 *)(pl + 0x14);
    PF(0x2A8) = *(f32 *)(pl + 0x18);
    PF(0x2AC) = *(f32 *)(pl + 0x1C);
    PF(0x390) = yaw;
    while (PF(0x390) < -360.0f) {
        PF(0x390) += 360.0f;
    }
    PF(0x2BC) = TF(0x4) + (TF(0x10) - TF(0x4)) * TF(0x3C);
    PF(0x2C0) = TF(0x8) + (TF(0x14) - TF(0x8)) * TF(0x3C);
    PF(0x2C4) = TF(0xC) + (TF(0x18) - TF(0xC)) * TF(0x3C);
    if (*(s32 *)(p + 0x2C) != 0x40) {
        PF(0x37C) = yaw = func_15048720(TF(0x3C), TF(0x20), TF(0x2C));
        PF(0x39C) = yaw * 0.017453292f;
    }
    D_800DC430 = TF(0x1C) + (TF(0x28) - TF(0x1C)) * TF(0x3C);
    D_800DC434 = PF(0x83C) + (PF(0x838) - PF(0x83C)) * TF(0x3C);
    PF(0x5E8) = func_15048720(TF(0x3C), 0.0f, TF(0x34));
    PF(0x3A8) = func_15048720(TF(0x3C), 0.0f, TF(0x38));
    if (last) {
        *(u16 *)(t + 0x40) = 0;
        *(u16 *)t = 0;
        *(s32 *)(p + 0x84) |= 8;
        TF(0x2C) = 999.0f;
        return 1;
    }
    *(s16 *)(p + 0x840) -= D_800BE9E4;
    if (*(s16 *)(p + 0x840) < 0) {
        *(s16 *)(p + 0x840) = 0;
    }
    return 1;
#undef TF
#undef PF
#undef PL
}
