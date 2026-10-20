s32 func_1502DE10(u8);
void func_15034A18(u8 *arg0) {
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    f32 (*m)[4][4];

    if (*(s32 *)(arg0 + 0x1D4) != 0 && *(s32 *)(arg0 + 0x9C) != 0) {
        n = func_1502DE10(arg0[4]) - 1;
        m = *(f32 (**)[4][4])(arg0 + 0x1D4);
        for (i = (n < 31) ? n : 31; i >= 0; i--) {
            if (*(s32 *)(arg0 + 0x9C) & (1 << i)) {
                for (j = 0; j < 3; j++) {
                    for (k = 0; k < 3; k++) {
                        m[i][j][k] = 0.0f;
                    }
                }
            }
        }
    }
}
