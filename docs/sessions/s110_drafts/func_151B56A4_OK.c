s32 func_151B56A4(f32 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4) {
    s32 pad; // fakematch: frame slot
    f32 v[3];
    u8 flag;

    v[0] = -arg1 * 0.13000001f;
    v[1] = -arg2 * 0.13000001f;
    v[2] = -arg3 * 0.13000001f;
    if (func_150ADA20() & 1) {
        flag = 1;
    } else {
        flag = 0;
    }
    return func_151D9014(arg0, v, 0, func_150ADA68() * 0.126f + -0.702f, (func_150ADA20() & 0xF) + 0xA, func_150ADA20() % 45U + 0x89, func_150ADA68() * 202.0f + 142.0f, flag, 1.7f, 1.7f, 0, 0, 1, 0, arg4, 1);
}
