void func_15143794(s16, s16, f32, void *);
s32 func_151A2C9C(f32 *, f32 *, f32 *, s32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_151BC920(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
    f32 sp6C[9];
    f32 temp_f2;

    sp6C[6] = arg0;
    sp6C[7] = arg1;
    sp6C[8] = arg2;
    func_15143794((s16) (func_150ADA20() & 0xFF), (s16) ((func_150ADA20() % 65U) - 0x20), func_150ADA68() * 1680.0f * 0.01f, &sp6C[3]);
    sp6C[0] = 0.0f;
    sp6C[1] = 0.0f;
    temp_f2 = ((func_150ADA68() * 202.0f) + 208.0f) * 0.001f;
    sp6C[2] = 0.0f;
    sp6C[3] += -arg3 * D_800BEDC8 * temp_f2;
    sp6C[4] += -arg4 * D_800BEDC8 * temp_f2;
    sp6C[5] += -arg5 * D_800BEDC8 * temp_f2;
    func_151A2C9C(&sp6C[6], sp6C, &sp6C[3], 0x3F800000, ((func_150ADA68() * 1049.0f) + -1022.0f) * 0.001f, (func_150ADA68() * 124.0f) + 202.0f, (func_150ADA20() & 0xF) + 0x14, (func_150ADA20() % 201U) + 0x37, 0xF, 0xF, 0, -1, 0xCB, 0, 0, (s32) (*(u8 *)((u8 *)arg6 + 0xC)), (s32) (*(u8 *)((u8 *)arg6 + 1)));
}
