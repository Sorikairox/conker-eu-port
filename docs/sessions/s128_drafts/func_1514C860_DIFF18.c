typedef s32 (*Cb1514C860)(s32, s16, f32, f32, f32, f32, f32, f32, u8, u8, f32, s32, f32, s32, u8);
extern Cb1514C860 D_8008ADA0[];

void func_1514C860(f32 x, f32 y, f32 z, f32 r, u8 ang0, s8 step, s16 n, u8 type, s32 arg8, f32 arg9, s32 argA, u8 argB) {
    s16 i;
    u8 ang;
    f32 c;
    f32 s;
    f32 pz;

    ang = ang0;
    for (i = 0; i < n; i++) {
        c = func_151423D8(ang - 0x40);
        s = func_151423D8(ang);
        pz = r * s + z;
        if (D_8008ADA0[type] != NULL) {
            if (D_8008ADA0[type](1, i, x + r * c, y, pz, x, y, z, ang, ang0, r, arg8, arg9, argA, argB) == 0) {
                return;
            }
        }
        ang += step;
    }
}
