#define F(o) (*(f32 *)(arg0 + (o)))
s32 func_1514AB04(u8 *arg0) {
    f32 damp;
    f32 dx;
    f32 dy;
    f32 dz;

    damp = F(0x140);
    F(0x130) *= damp;
    F(0x134) += F(0x13C) * D_800BE9A4;
    F(0x138) *= damp;
    dx = F(0x130) * D_800BE9A4;
    dy = F(0x134) * D_800BE9A4;
    dz = F(0x138) * D_800BE9A4;
    F(0x34) += dx;
    F(0x38) += dy;
    F(0x3C) += dz;
    F(0x40) += dx;
    F(0x44) += dy;
    F(0x48) += dz;
    F(0x40) = F(0x34) + (F(0x40) - F(0x34)) * F(0x54);
    F(0x44) = F(0x38) + (F(0x44) - F(0x38)) * F(0x54);
    F(0x48) = F(0x3C) + (F(0x48) - F(0x3C)) * F(0x54);
    return 1;
}
#undef F
