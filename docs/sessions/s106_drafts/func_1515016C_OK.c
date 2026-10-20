s32 func_15145128(u8 *, u8 *, void *, void *);
void func_1515016C(u8 *arg0, u8 arg1, s32 arg2) {
    f32 a[3];
    s32 a1;
    s32 a2;
    f32 b[3];
    s32 b1;
    s32 b2;
    f32 c[3];
    s32 c1;
    s32 c2;
    if (func_15144E80(arg0 + 0xC, (u8 *)a, (u8 *)b, (u8 *)c) != 0) {
        func_15145128((u8 *)a, (u8 *)a, &a1, &a2);
        func_15145128((u8 *)b, (u8 *)b, &b1, &b2);
        func_15145128((u8 *)c, (u8 *)c, &c1, &c2);
        if (func_15144A74((u8 *)c, arg0) < 0.0f) {
            c[0] = -c[0];
            c[1] = -c[1];
            c[2] = -c[2];
        }
        func_1514FE68(arg0 + 0x24, (u8 *)c, (s32 *)a, (s32 *)b, *(f32 *)(arg0 + 0x20), arg1, arg2);
    }
}
