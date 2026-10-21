s32 func_1515C710(u8 *, f32 *, f32 *, f32 *);

s32 func_15145AD8(f32 *arg0, f32 *arg1, u8 *arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 *arg6, f32 *arg7) {
    f32 v7[3];
    f32 t5;
    f32 t6;
    f32 a[3];
    f32 b[3];
    f32 c[3];
    f32 d4C;
    f32 d48;
    f32 d44;
    f32 e;
    f32 d38;
    f32 scale;

    if (arg5 != NULL) {
        arg5 = &t5;
    }
    if (arg6 != NULL) {
        arg6 = &t6;
    }
    if (arg7 != NULL) {
        arg7 = v7;
    }
    func_1515C710(arg2, arg7, arg5, arg6);
    if (*arg6 == 0.0f) {
        return 0;
    }
    if (*arg5 == 0.0f) {
        return 0;
    }
    e = *(f32 *)(arg2 + 0xE0);
    scale = *(f32 *)(arg2 + 0xDC);
    a[0] = arg0[0];
    a[1] = arg0[1] * scale;
    a[2] = arg0[2];
    b[0] = arg1[0];
    b[1] = arg1[1] * scale;
    b[2] = arg1[2];
    if (func_15145128((struct17 *)b, (struct17 *)b, &d4C, &d38) == 0) {
        return 0;
    }
    c[0] = arg7[0];
    c[1] = arg7[1] * scale;
    c[2] = arg7[2];
    if (func_151451F0((struct17 *)a, (struct17 *)b, (struct17 *)c, *arg5, d4C, (s32)arg3, (s32)arg4, &d48, &d44) == 0) {
        return 0;
    }
    arg3[1] *= e;
    arg4[1] *= e;
    return 1;
}
