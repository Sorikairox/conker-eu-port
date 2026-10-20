s32 func_151A2FC4(u8 *, s16, s16, f32, f32, f32, s32, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_15150258(u8 *arg0, s32 arg1, s32 arg2) {
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    s32 temp_s1;
    s32 temp_s3;
    s32 var_s2;

    var_s2 = (func_150ADA20() % (u32) ((*(s32 *)((u8 *)arg0 + 0xC)) + 1)) + (*(s32 *)((u8 *)arg0 + 8));
    if (var_s2 != 0) {
        do {
            temp_s3 = func_150ADA20();
            temp_s1 = func_150ADA20();
            temp_f20 = func_150ADA68();
            temp_f22 = func_150ADA68();
            temp_f24 = func_150ADA68();
            func_151A2FC4(arg0 + 0x10, (s16) (((u32) temp_s3 % (u32) ((*(s16 *)((u8 *)arg0 + 2)) + 1)) + (*(s16 *)((u8 *)arg0 + 0))), (s16) (((u32) temp_s1 % (u32) ((*(s16 *)((u8 *)arg0 + 6)) + 1)) + (*(s16 *)((u8 *)arg0 + 4))), (temp_f20 * (*(f32 *)((u8 *)arg0 + 0x20))) + (*(f32 *)((u8 *)arg0 + 0x1C)), (temp_f22 * (*(f32 *)((u8 *)arg0 + 0x28))) + (*(f32 *)((u8 *)arg0 + 0x24)), (temp_f24 * (*(f32 *)((u8 *)arg0 + 0x30))) + (*(f32 *)((u8 *)arg0 + 0x2C)), (func_150ADA20() % (u32) ((*(s32 *)((u8 *)arg0 + 0x38)) + 1)) + (*(s32 *)((u8 *)arg0 + 0x34)), (*(f32 *)((u8 *)arg0 + 0x3C)), (*(f32 *)((u8 *)arg0 + 0x40)), (*(f32 *)((u8 *)arg0 + 0x44)), (*(f32 *)((u8 *)arg0 + 0x48)), (s32) (*(s16 *)((u8 *)arg0 + 0x4C)), (s32) (*(s16 *)((u8 *)arg0 + 0x4E)), (s32) (*(s16 *)((u8 *)arg0 + 0x50)), (s32) (*(s16 *)((u8 *)arg0 + 0x52)), (s32) (*(s16 *)((u8 *)arg0 + 0x54)), (s32) (*(s16 *)((u8 *)arg0 + 0x56)), (s32) (*(s8 *)((u8 *)arg0 + 0x58)), (u8) arg1, arg2);
            var_s2 -= 1;
        } while (var_s2 != 0);
    }
}
