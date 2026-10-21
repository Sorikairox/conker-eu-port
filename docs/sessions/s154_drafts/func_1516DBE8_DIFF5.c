extern s32 (*D_8008CF40[])(u8 *);

void func_1516DBE8(u8 *arg0) {
    s32 v;

    v = arg0[0x24];
    if (v != 0) {
        v -= D_800BE9E4;
        if (v < 0) {
            v = 0;
        }
        arg0[0x24] = v;
    }
    if (D_8008CF40[arg0[0x23]](arg0) == 1) {
        if (*(u8 **)(arg0 + 0x30) != NULL) {
            *(s16 *)(*(u8 **)(arg0 + 0x30) + 4) = 0;
        }
        func_1516972C((struct102 *)arg0);
    } else {
        s32 t;
        v = *(s16 *)(arg0 + 0x10);
        v = (v << 8) + arg0[0x25];
        t = v + *(s16 *)(arg0 + 0x18) * D_800BE9E4;
        *(s16 *)(arg0 + 0x10) = t >> 8;
        arg0[0x25] = t;
    }
}
