s32 func_1000F568(s32 arg0, s32 arg1) {
    u32 r;
    s32 v;
    s32 mask;
    s32 bits;
    s32 cur;
    u8 *p;

    r = (u32)func_150ADA20() % arg1;
    v = r;
    if (arg0 >= 0x6E2) {
        return 1;
    }
    if (arg1 < 2) {
        return arg0;
    }
    if (D_80041F5C != NULL) {
        p = &((u8 *)D_80041F5C)[arg0];
        if (arg1 < 8) {
            cur = *p;
            bits = cur;
            if (!(cur & 0x80) || !(cur & (mask = (1 << arg1) - 1))) {
                mask = (1 << arg1) - 1;
                cur = bits = 0xFF;
            }
            while (!(bits & (1 << v))) {
                v = (v + 1) % arg1;
            }
            cur = bits ^ (1 << v);
            *p = cur;
            if (!(cur & 0xFF & mask)) {
                ((u8 *)D_80041F5C)[arg0] = bits ^ mask;
            }
        } else {
            *p = r + 1;
        }
    }
    return arg0 + v;
}
