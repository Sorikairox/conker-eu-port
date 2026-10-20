void func_150D7930(u8 *arg0, u8 *arg1, u8 arg2) {
    if (arg2 == 0x36) {
        switch (*arg1) {
        case 1:
            arg0[0x28] = 0xFF;
            arg0[0x29] = 0;
            *(s32 *)(arg0 + 0x58) |= 2;
            arg0[0x2A] = 0;
            return;
        case 2:
            arg0[0x28] = 0xFF;
            arg0[0x29] = 0;
            *(s32 *)(arg0 + 0x58) |= 2;
            arg0[0x2A] = 0;
            return;
        case 3:
            arg0[0x28] = 0;
            arg0[0x29] = 0xFF;
            *(s32 *)(arg0 + 0x58) |= 2;
            arg0[0x2A] = 0;
            return;
        default:
        case 0:
            *(s32 *)(arg0 + 0x58) &= ~2;
            return;
        }
    }
}
