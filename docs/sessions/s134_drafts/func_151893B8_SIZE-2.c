s32 func_1502DE10(u8);

void func_151893B8(u8 *arg0) {
    u8 n;
    s32 sz;
    s32 a;
    s32 b;
    s32 i;
    s32 j;
    u8 *src;

    n = arg0[1];
    sz = func_1502DE10(*(*(u8 **)(arg0 + 0x10) + 4));
    a = D_800BE9C0 * (sz * n);
    b = (D_800BE9C0 ^ 1) * (sz * n);
    i = 0;
    j = 1;
    if (n > 0) {
        do {
            if (j == n) {
                src = *(u8 **)(*(u8 **)(arg0 + 0x10) + 0x1D4);
                if (src == NULL) {
                    arg0[2] = 0;
                    return;
                }
            } else {
                src = *(u8 **)(arg0 + 8) + ((j * sz + b) << 6);
            }
            bcopy(src, *(u8 **)(arg0 + 8) + ((i * sz + a) << 6), sz << 6);
            i = j;
        } while (j++ != n);
    }
    if (arg0[1] != arg0[2]) {
        arg0[2]++;
    }
}
