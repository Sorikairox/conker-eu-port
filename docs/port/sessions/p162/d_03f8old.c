s32 func_151030B8(u8 *, u8, u8 *, u8 *, f32 *, s32, s32, f32, f32 *, s32, s32, s32, s32, s32);
void func_15145EA4(f32 **, f32 **, void *, s32);
s32 func_151C284C(f32 *, f32 *, s32, s32, s32, s32, f32, f32, f32, f32, f32, s32, u8 *, s32, s32, s32, s32, s32, s32, s32, s32, f32, s32, s32, s32, s32, s32);
extern s32 D_800A1A10;
extern s32 D_800A1A28;
extern s32 D_800A1A40;
s32 func_150F03F8(u8 *arg0, u8 arg1, u8 arg2, s32 arg3) {
    struct {
        f32 u98;
        f32 u9C;
        s32 uA0;
        s32 uA4;
        s32 uA8;
        s8 uAC;
        s8 uAD;
        s16 uAE;
        s8 uB0;
        u8 padB1[0x3];
        f32 * uB4;
        f32 * uB8;
        u8 * uBC;
        u8 * uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        s32 uDC;
    } sp;
    s32 sp94;
    f32 sp90;
    f32 sp8C;
    s32 sp88;
    u8 *sp84;
    s32 temp_t0;
    s32 temp_v0_2;
    u8 *temp_v0;

    if (arg0 == NULL) {
        return 0;
    }
    if ((s32) arg1 >= 2) {
        return 0;
    }
    if ((*(s32 *)((u8 *)arg0 + 0x1D4)) == 0) {
        return 0;
    }
    if ((*(s32 *)((u8 *)arg0 + 0x2EC)) < 0x5A) {
        return 0;
    }
    temp_t0 = arg1 * 0xC;
    temp_v0 = arg1 + &D_800A1A40;
    sp.uBC = temp_t0 + &D_800A1A10;
    sp.uC0 = temp_t0 + &D_800A1A28;
    sp.uB4 = &sp.uD0;
    sp.uB8 = &sp.uC4;
    sp84 = temp_v0;
    func_15145EA4(&sp.uBC, &sp.uB4, (*temp_v0 << 6) + (*(s32 *)((u8 *)arg0 + 0x1D4)), 2);
    sp.uC4 -= sp.uD0;
    sp.uC8 -= sp.uD4;
    sp.uCC -= sp.uD8;
    sp8C = func_150ADA68();
    sp90 = func_150ADA68();
    func_150ADA20();
    sp.uDC = func_151C284C(&sp.uD0, &sp.uC4, 0, 0, 0, 0, 150.0f, 0.006666667f, (sp8C * 19.0f) + 38.0f, (sp90 * 363.0f) + 149.0f, 50.0f, 0xFF, arg0, 1, 1, 0, 8, 0, 1, 0, 0xA0038, 0.0f, 0xFF, -1, 0, (s32) arg2, arg3);
    sp.uAC = 3;
    sp.uAD = -1;
    sp.uAE = (func_150ADA20() % 5U) + 4;
    sp.uB0 = 0;
    sp.uA0 = (s32) sp.uD0;
    sp.uA4 = (s32) sp.uD4;
    sp.uA8 = (s32) sp.uD8;
    func_151602C0((Header *) &sp.uAC, (Header2 *) &sp.uA0, (func_150ADA20() % 51U) + 0x50, 0xFF, 0xFF, 0xFF, 0xFFU, 0U, 0, (u8) (s32) arg2, arg3);
    sp.u9C = ((func_150ADA68() * 1906.0f) + 969.0f) * 0.001f;
    sp.u98 = ((func_150ADA68() * 911.0f) + 628.0f) * 0.1f;
    sp88 = func_150ADA20();
    sp94 = func_150ADA20();
    temp_v0_2 = arg1 * 0xC;
    func_151030B8(arg0, *sp84, temp_v0_2 + &D_800A1A10, temp_v0_2 + (u8 *)&D_800A1A28, &sp.u98, ((u32) sp88 % 3U) + 8, 0xFF, (func_150ADA68() * 2000.0f) + 2000.0f, &sp.uD0, 0xFF, 0, -1, (s32) arg2, arg3);
    return sp.uDC;
}
