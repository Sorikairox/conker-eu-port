s32 func_15189E70(s16 *, s32);
extern s32 D_800B1214;
extern f32 D_800965C0, D_800965C4, D_800965C8, D_800965CC;

void func_1500E8C0(void) {

    struct {
        s16 u40;
        s16 u42;
        s16 u44;
        s16 u46;
        f32 u48;
        f32 u4C;
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        s16 u78;
        s16 u7A;
        f32 u7C;
        f32 u80;
        s16 u84;
        s16 u86;
        s32 u88;
        s32 u8C;
    } sp;

    func_15195AA8(*D_800B0E00, D_800902E8, 0, -1, 0, 0, 0, -6);
    func_15195AA8(D_800B1214, D_800902E8, 0, -1, 0, 1, 0, -6);
    sp.u68 = D_800965C0;
    sp.u70 = 5.0f;
    sp.u74 = 6.0f;
    sp.u60 = 8.0f;
    sp.u64 = 7.0f;
    sp.u6C = 0.0f;
    sp.u88 = 3;
    sp.u8C = 2;
    sp.u40 = 0x34;
    sp.u42 = 0x12;
    sp.u44 = -0x28;
    sp.u46 = 0xF;
    sp.u78 = 0x9B;
    sp.u7A = 0x64;
    sp.u84 = 0x29;
    sp.u86 = 0x29;
    sp.u50 = 400.0f;
    sp.u54 = 0.0f;
    sp.u58 = 0.0f;
    sp.u5C = 900.0f - sp.u50;
    sp.u7C = D_800965C4;
    sp.u80 = D_800965C8;
    sp.u48 = 800.0f;
    sp.u4C = D_800965CC;
    func_15189E70(&sp.u40, 1);
    func_1000FA64(0x61FU, (D_800BE9F0 == 6) ? 0x34 : 7, 0, 0, 0x2EE0, 0x3E8U, 0x190, (s32) func_1000EF40, NULL, 0, 0x48, 0);
}
