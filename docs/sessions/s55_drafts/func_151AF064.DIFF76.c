s32 func_151DA6F8(s32, f32 *, f32, s16, s32, f32, s32, s32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_151AF064(s32 arg0, u8 arg1, u8 arg2) {
    f32 sp88[4];
    u8 sp87;
    u8 sp86;
    f32 temp_f12;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 temp_f2;
    f32 sp68;
    s32 sp64;
    s32 sp60;
    f32 sp5C;

    sp87 = func_150ADA20();
    sp86 = (func_150ADA20() & 0x7F) - 0x3F;
    sp7C = func_151423D8(sp87);
    sp78 = func_151423D8(sp87 - 0x40);
    sp74 = func_151423D8(sp86);
    sp70 = func_151423D8(sp86 - 0x40);
    temp_f2 = ((func_150ADA68() * 80.0f) + 20.0f) * 0.1f;
    temp_f12 = temp_f2 * sp74;
    sp88[0] = temp_f12 * sp78;
    sp88[1] = -temp_f2 * sp70;
    sp88[2] = temp_f12 * sp7C;
    sp5C = func_150ADA68();
    sp60 = func_150ADA20();
    sp64 = func_150ADA20();
    sp68 = func_150ADA68();
    func_151DA6F8(arg0, sp88, (sp5C * 0.40600002f) + 0.21000001f, (s16) (((u32) sp60 % 41U) + 0x3C), ((u32) sp64 % 101U) + 0x9B, (sp68 * 4.0f) + 3.1000001f, (func_150ADA20() % 5U) + 3, (s32) arg1, 1.0f, 1.0f, 0, 0, 0, 0x10, 0xF, 0, (s32) arg2, 1);
}
