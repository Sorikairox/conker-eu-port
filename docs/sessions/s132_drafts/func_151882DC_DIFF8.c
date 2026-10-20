extern f32 D_8008D918;
void func_151F05C0(f32 mf[4][4]);
void func_151882DC(f32 mf[4][4], f32 r, f32 p, f32 h) {
    f32 sinr, sinp, sinh, cosr, cosp, cosh;

    r *= D_8008D918;
    p *= D_8008D918;
    h *= D_8008D918;
    sinr = sinf(r);
    cosr = cosf(r);
    sinp = sinf(p);
    cosp = cosf(p);
    sinh = sinf(h);
    cosh = cosf(h);
    func_151F05C0(mf);
    mf[0][0] = cosp * cosh - sinr * sinp * sinh;
    mf[0][1] = cosp * sinh + sinr * sinp * cosh;
    mf[0][2] = -sinp * cosr;
    mf[1][0] = -cosr * sinh;
    mf[1][1] = cosr * cosh;
    mf[1][2] = sinr;
    mf[2][0] = sinp * cosh + sinr * cosp * sinh;
    mf[2][1] = sinp * sinh - sinr * cosp * cosh;
    mf[2][2] = cosr * cosp;
}
