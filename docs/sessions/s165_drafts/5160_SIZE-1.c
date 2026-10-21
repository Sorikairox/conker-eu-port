s32 func_15063F14(u8 *, s32);
s32 func_1507CD64(struct127 *, s32);
s32 func_15195160(s32 arg0, u8 *arg1, s8 *arg2) {
    u8 k;
    u8 *p;

    switch (arg1[4]) {
    case 0x16:
        func_15136C3C((s32)arg1, 1, 1, 1, 1, 0, 0xFF, 1);
        func_15145A50((struct127 *)arg1);
        /* fallthrough */
    case 0x7C:
        k = arg1[0x65];
        if (k != 0) {
            D_800CC2D0[k - 1].unk232 = 0xA;
            D_800CC2D0[k - 1].unk218 = NULL;
            arg1[0x65] = 0;
        }
        break;
    case 0x0: case 0x1: case 0x2: case 0x3: case 0x4: case 0x11: case 0x14: case 0x3B:
    case 0x58: case 0x5A: case 0x5B: case 0x5F: case 0x74: case 0x75: case 0x7A: case 0x80:
    case 0x87: case 0x88: case 0x90: case 0x96: case 0x98: case 0x9C: case 0x9D: case 0x9F:
    case 0xA0: case 0xB0: case 0xB1: case 0xB2: case 0xB4:
        func_15136C3C((s32)arg1, 1, 1, 1, 1, 0, 0xFF, 1);
        func_15145A50((struct127 *)arg1);
        func_1507CD64((struct127 *)arg1, 6);
        p = *(u8 **)(arg1 + 0x31C);
        if (p != NULL && p[0x19B] != 0) {
            func_15063F14(arg1, 0);
        }
        break;
    }
}
