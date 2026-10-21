extern s32 (*D_8008B068[])(u8 *);

void func_15155200(u8 *arg0) {
    s32 pad; // fakematch: puts done at sp+0x1B
    s8 done = 0;
    s16 v;

    if (*(u16 *)(arg0 + 0x24) & 1) {
        *(s16 *)(arg0 + 0x22) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x22) < 0) {
            done = 1;
        }
    }
    if ((arg0[0x68] & 0xF) && !done) {
        if (D_8008B068[arg0[0x68] & 0xF](arg0) == 0) {
            done = 1;
        }
    }
    if (*(u16 *)(arg0 + 0x24) & 8) {
        if (*(s16 *)(arg0 + 0x22) < *(s16 *)(arg0 + 0x26)) {
            v = *(s16 *)(arg0 + 0x22) * *(s16 *)(arg0 + 0x28);
            if (v < arg0[0x2E]) {
                arg0[0x2E] = v;
            }
        }
    }
    if (done) {
        func_1516972C((struct102 *)arg0);
    }
}
