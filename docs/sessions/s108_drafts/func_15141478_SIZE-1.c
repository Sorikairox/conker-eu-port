s32 func_15141478(u8 *arg0) {
    f32 *p;
    f32 *q;
    f32 a;

    *(f32 *)(arg0 + 0x180) -= D_800BE9A4;
    if (*(f32 *)(arg0 + 0x180) < 0.0f) {
        p = (f32 *)(arg0 + 0x170);
        p[4] = p[5] * func_150ADA68();
        if (func_150ADA20() & 3) {
            a = p[1];
            p[3] = func_150ADA68() * (p[0] - a) + a;
        } else {
            a = p[0];
            p[3] = func_150ADA68() * (p[2] - a) + a;
        }
    }
    q = (f32 *)(arg0 + 0x110);
    p = (f32 *)(arg0 + 0x170);
    q[0x12] += (p[3] - q[0x12]) * p[6];
    return 1;
}
