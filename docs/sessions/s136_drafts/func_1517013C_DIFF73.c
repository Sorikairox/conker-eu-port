s32 func_1517013C(u8 *arg0) {
    s32 v;
    s32 t;
    u8 c;

    v = arg0[0x1F];
    if (arg0[0x24] != 0) {
        if (v != 0xFF) {
            v += D_800BE9E4 * 0x10;
            if (v >= 0x100) {
                v = 0xFF;
            }
            arg0[0x1F] = v;
        }
    } else if (v != 0) {
        v -= D_800BE9E4 << arg0[0x2F];
        if (v < 0) {
            v = 0;
        }
        arg0[0x1F] = v;
    }
    if (arg0[0x24] == 0 && v == 0) {
        return 1;
    }
    *(s16 *)(arg0 + 0x14) += *(s8 *)(arg0 + 0x2D) * D_800BE9E4;
    *(s16 *)(arg0 + 0x16) += *(s8 *)(arg0 + 0x2E) * D_800BE9E4;
    if (*(s16 *)(arg0 + 0x14) <= 0 || *(s16 *)(arg0 + 0x14) <= 0) {
        *(s16 *)(arg0 + 0x16) = 0;
        *(s16 *)(arg0 + 0x14) = *(s16 *)(arg0 + 0x16);
        return 1;
    }
    v = arg0[0x2C] + D_800BE9E4;
    if (v >= 0x80) {
        v = 0x7F;
    }
    arg0[0x2C] = v;
    t = v * 2;
    c = arg0[0x26];
    arg0[0x1C] = (((arg0[0x29] - c) * t) >> 8) + c;
    c = arg0[0x27];
    arg0[0x1D] = (((arg0[0x2A] - c) * t) >> 8) + c;
    c = arg0[0x28];
    arg0[0x1E] = (((arg0[0x2B] - c) * t) >> 8) + c;
    return 0;
}
