void func_15191FF4(struct102 *arg0, u8 *volatile arg1, u8 arg2) {
    u8 *p;

    p = (u8 *)&arg0->unk28;
    if (arg2 == 0xC || arg2 == 0xE || arg2 == 0x50) {
        if (*(s32 *)p == *(s32 *)arg1 || p[4] == arg1[4]) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x4E) {
        func_1516972C(arg0);
    } else if (arg2 == 0xD) {
        if (*(s32 *)p == *(s32 *)arg1 || p[4] == arg1[4]) {
            *(s16 *)((u8 *)arg0 + 0xE) = 0x64;
            *(u8 *)((u8 *)arg0 + 0xD) |= 1;
        }
    } else {
        func_15169850((s32)arg1, (&arg2)[0], (s32)p, (s32)(p + 4), (s32)arg0);
    }
}
