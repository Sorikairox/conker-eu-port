void func_15156928(struct102 *arg0p) {
    u8 *arg0 = (u8 *)arg0p;
    s32 done;
    s16 t;

    done = 0;
    if (arg0[0x40] & 1) {
        *(s16 *)(arg0 + 0x42) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x42) < 0) {
            done = 1;
        }
    }
    if (!done) {
        *(f32 *)(arg0 + 0x10) += *(f32 *)(arg0 + 0x1C) * D_800BE9A4;
        *(f32 *)(arg0 + 0x14) += *(f32 *)(arg0 + 0x20) * D_800BE9A4;
        *(f32 *)(arg0 + 0x18) += *(f32 *)(arg0 + 0x24) * D_800BE9A4;
        *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x34) * D_800BE9A4;
        *(f32 *)(arg0 + 0x2C) += *(f32 *)(arg0 + 0x38) * D_800BE9A4;
        *(f32 *)(arg0 + 0x30) += *(f32 *)(arg0 + 0x3C) * D_800BE9A4;
        if (arg0[0x40] & 8) {
            if (*(s16 *)(arg0 + 0x42) < *(s16 *)(arg0 + 0x4E)) {
                t = *(s16 *)(arg0 + 0x50) * *(s16 *)(arg0 + 0x42);
                if (t < arg0[0x4C]) {
                    arg0[0x4C] = t;
                }
            }
        }
    }
    if (done) {
        func_1516972C(arg0p);
    }
}
