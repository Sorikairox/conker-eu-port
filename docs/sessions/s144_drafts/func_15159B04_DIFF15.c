s32 func_15046EF0(f32 *, s32, s32, u8 *);
s32 func_1514672C(f32 *);
s32 func_15159C2C(u8 *, u8 *);
s32 func_151D8E20();

u8 func_15159B04(u8 *arg0, u8 *arg1) {
    u8 flag;
    f32 v[4];

    flag = 1;
    if (func_15159C2C(arg0, arg1) != 0) {
        if (*(f32 *)(arg0 + 0x5C) > 0.0f) {
        v[0] = *(f32 *)(arg0 + 0x4C) + *(f32 *)(arg0 + 0x40);
        v[1] = *(f32 *)(arg1 + 4);
        v[2] = *(f32 *)(arg0 + 0x54) + *(f32 *)(arg0 + 0x48);
        if (func_1514672C(v) == 0) {
            return 0;
        }
        if (func_15046EF0(v, 0, *(s32 *)(arg0 + 0x44), arg0 + 0x80) != 0) {
            v[1] = *(f32 *)(arg0 + 0x80);
            if (arg0[0x9D] == 3) {
                func_151DBCBC(func_151D8E20(), *(f32 *)(arg0 + 0xA8) * 0.2f, 0xFF, (s32)(arg0 + 0x84), v, arg0[0xC], arg0[1]);
            }
            flag = 0;
        }
        }
    } else {
        flag = 0;
    }
    return flag;
}
