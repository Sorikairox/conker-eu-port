s32 func_15141F78(s32, s32 *, f32, u8, f32 *, s32);
extern f32 D_800A1840;
extern f32 D_800A1844;
void func_150EB610(u8 *arg0, u8 arg1, s32 arg2) {
    f32 pos[3];
    s32 buf[9];
    s32 a;
    u8 **q = &arg0; // fakematch: address-taken arg0 forces the home-slot reload (shape C)

    a = arg1;
    if (*(s32 *)(*q + 0x1D4) != 0) {
        if (func_150EB4D0(pos, *q, (s32)buf, arg1) != 0) {
            func_15141F78(0xA, buf, arg2 * D_800A1840, (u32)(*(f32 *)(*q + 0x40) * D_800A1844), pos, a);
        }
    }
}
