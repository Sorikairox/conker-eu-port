s32 func_151C8D90(s32, u8 *);
void func_151C8F4C(s32, u8 *);
void func_151C8C5C(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *v;
    u8 **q = &arg0;
    switch (arg2) {
    case 0x20:
        v = (*q) + 0x110;
        if ((v[0x86] & 0x10) && (*(s32 *)(v + 0x28) == arg1[1])) {
            if (func_151C8D90(arg1[0], (*q))) {
                func_151C8F4C(arg1[0], (*q));
            }
        }
        break;
    case 0x3A:
        v = (*q) + 0x110;
        if (*(s32 *)(v + 0x28) == arg1[0]) {
            switch (((u8 *)arg1)[4]) {
            case 0: v[0x86] |= 2; break;
            case 1: v[0x86] &= ~2; break;
            case 2: func_151C8F4C(0, (*q)); break;
            }
        }
        break;
    }
}
