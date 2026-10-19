s32 func_1518A930(u8 *, f32 *, f32, s32 *, f32 *, f32, f32, s32, s32, s32, s32, s32, s32);

void func_15151500(u8 *arg0, u8 arg1, u8 arg2, s32 arg3) {
    f32 spBC[3];
    f32 spA8[3];
    s32 sp9C;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f26;
    s32 temp_s1;
    s32 temp_s2;
    s32 var_s3;

    temp_f26 = 2.0f * (*(f32 *)((u8 *)arg0 + 0x2C));
    spBC[1] = 0.0f;
    var_s3 = (func_150ADA20() % (u32) ((*(s32 *)((u8 *)arg0 + 4)) + 1)) + (*(s32 *)((u8 *)arg0 + 0));
    if (var_s3 != 0) {
        do {
            spA8[0] = func_150ADA68() * 360.0f;
            spA8[1] = func_150ADA68() * 360.0f;
            spA8[2] = func_150ADA68() * 360.0f;
            temp_s1 = func_150ADA20();
            temp_s2 = func_150ADA20();
            func_15143794((s16) (((u32) temp_s1 % (u32) ((*(s16 *)((u8 *)arg0 + 0x1E)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x1C))), (s16) (((u32) temp_s2 % (u32) ((*(s16 *)((u8 *)arg0 + 0x22)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x20))), (func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x28))) + (*(f32 *)((u8 *)arg0 + 0x24)), &sp9C);
            spBC[0] = (func_150ADA68() * temp_f26) - (*(f32 *)((u8 *)arg0 + 0x2C));
            spBC[2] = (func_150ADA68() * temp_f26) - (*(f32 *)((u8 *)arg0 + 0x2C));
            temp_f22 = func_150ADA68();
            temp_f20 = func_150ADA68();
            func_1518A930(arg0 + 8, spA8, (temp_f22 * (*(f32 *)((u8 *)arg0 + 0x18))) + (*(f32 *)((u8 *)arg0 + 0x14)), &sp9C, spBC, (temp_f20 * (*(f32 *)((u8 *)arg0 + 0x34))) + (*(f32 *)((u8 *)arg0 + 0x30)), (*(f32 *)((u8 *)arg0 + 0x38)), (s32) (*(u8 *)((u8 *)arg0 + 0x3C)), (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x40)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x3E)), arg1, 0, arg2, arg3);
            var_s3 -= 1;
        } while (var_s3 != 0);
    }
}
