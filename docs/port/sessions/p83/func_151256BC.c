/* Camera shake: while shaking (flag 0x80000, or +0x5F0 bit 3 without flag 0x40000) the phase +0x29C advances
 * by a random 0..4 degrees per tick (wrapped to 2 pi), else it decays by 8 % per frame. The amplitude +0x5EC
 * follows 4 sin(phase) by 4 %; eye +0x2F8 and target +0x2BC are pulled towards each other by
 * amp * 0.05 * (4, 4) when shaking hard, (1, 20) otherwise (func_1508EF80 = lerp). */
#define CAM_W(o) (*(s32 *)(p + (o)))
#define CAM_H(o) (*(s16 *)(p + (o)))
#define CAM_F(o) (*(f32 *)(p + (o)))
void func_151256BC(struct108 *arg0) {
    u8 *p = (u8 *)arg0;
    f32 t;
    f32 eyeK;
    f32 targetK;

    if ((CAM_W(0x2C) & 0x80000) || ((CAM_W(0x5F0) & 8) && !(CAM_W(0x2C) & 0x40000))) {
        CAM_F(0x29C) += (f32)((u32)func_150ADA20() % 3) * 2 * 0.017453292f * D_800BE9A4;
        while (6.2831855f < CAM_F(0x29C)) {
            CAM_F(0x29C) -= 6.2831855f;
        }
        CAM_F(0x5EC) += (sinf(CAM_F(0x29C)) * 4.0f - CAM_F(0x5EC)) * 0.04f;
        t = CAM_F(0x5EC) * 0.05f;
        if (CAM_W(0x2C) & 0x80000) {
            eyeK = 4.0f;
            targetK = 4.0f;
        } else {
            eyeK = 1.0f;
            targetK = 20.0f;
        }
        func_1508EF80(p + 0x2F8, p + 0x2BC, t * eyeK, p + 0x2F8);
        func_1508EF80(p + 0x2BC, p + 0x2F8, t * targetK, p + 0x2BC);
        return;
    }
    if (CAM_F(0x29C) == 0.0f) {
        return;
    }
    CAM_F(0x29C) -= CAM_F(0x29C) * 0.08f;
    CAM_F(0x5EC) += (sinf(CAM_F(0x29C)) * 4.0f - CAM_F(0x5EC)) * 0.04f;
    t = CAM_F(0x5EC) * 0.05f;
    func_1508EF80(p + 0x2F8, p + 0x2BC, t, p + 0x2F8);
    func_1508EF80(p + 0x2BC, p + 0x2F8, t * 20.0f, p + 0x2BC);
}
#undef CAM_W
#undef CAM_H
#undef CAM_F
