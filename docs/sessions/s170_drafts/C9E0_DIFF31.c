extern s32 (*D_8008ADA0[])(s32, s16, f32, f32, f32, f32, f32, f32, s32, s32, f32, s32, f32, s32, u8);
void func_1514C9E0(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, u8 arg7, s32 arg8, f32 arg9, s32 argA, u8 argB) {
    s32 pad[2]; // fakematch: frame
    s16 i;
    f32 dx, dy, dz;
    f32 x, y, z;
    f32 k;

    i = 0;
    if (arg6 < 2.0f) {
        return;
    }
    y = arg1;
    if ((s32)arg6 & 1) {
        k = 1.0f / (arg6 - 1.0f);
        dx = (arg3 - arg0) * k;
        dy = (arg4 - arg1) * k;
        dz = (arg5 - arg2) * k;
    } else {
        k = 1.0f / (arg6 - 1.0f);
        dx = (arg3 - arg0) * k;
        dy = (arg4 - arg1) * k;
        dz = (arg5 - arg2) * k;
    }
    x = arg0;
    z = arg2;
    do {
        if (D_8008ADA0[arg7] != NULL) {
            if (D_8008ADA0[arg7](0, i, x, y, z, arg0, arg1, arg2, 0, 0, 0.0f, arg8, arg9, argA, argB) == 0) {
                return;
            }
        }
        arg6 -= 1.0f;
        i++;
        x += dx;
        y += dy;
        z += dz;
    } while (arg6 > 0.0f);
}
