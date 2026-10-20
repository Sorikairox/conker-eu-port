s32 func_151B5454(f32 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5) {
    s32 pad; // fakematch: frame slot
    f32 v[3];

    v[0] = -arg1 * 0.20500001f;
    v[1] = -arg2 * 0.20500001f;
    v[2] = -arg3 * 0.20500001f;
    return func_151D9014(arg0, v, arg4, func_150ADA68() * 0.497f + -1.0f, func_150ADA20() % 31U + 0x14, func_150ADA20() % 101U + 0x9B, func_150ADA68() * 152.0f + 109.0f, func_150ADA20() & 1, 1.7f, 1.7f, 0, 0, 1, 0, arg5, 1);
}
