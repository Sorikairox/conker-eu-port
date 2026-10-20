extern f32 D_800980CC;
s16 *func_15034790(s16 *arg0, s32 arg1) {
    struct127 *p;
    s32 v;
    f32 k;

    k = D_800980CC;
    arg0[0] = 0x12;
    p = &D_800CC2D0[arg1];
    v = *(s16 *)((u8 *)p + 0x2E6);
    arg0[1] = v * k;
    arg0[2] = 0xE;
    v = -*(s16 *)((u8 *)p + 0x2E4);
    arg0[3] = v * k;
    return arg0 + 4;
}
