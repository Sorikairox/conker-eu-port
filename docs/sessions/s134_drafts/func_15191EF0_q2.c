void func_15191EF0(struct102 *arg0, u8 *volatile arg1, u8 arg2) {
    if (arg2 == 0xD) {
        if (*(s32 *)((u8 *)arg0 + 0x10) == *(s32 *)(arg1 + 0) || arg0->unk14 == *(u8 *)(arg1 + 4)) {
            *(s16 *)((u8 *)arg0 + 0x16) = 0x64;
            arg0->unk18 |= 1;
        }
    } else if (arg2 == 0xC || arg2 == 0x50 || arg2 == 0xE) {
        if (*(s32 *)((u8 *)arg0 + 0x10) == *(s32 *)(arg1 + 0) || arg0->unk14 == *(u8 *)(arg1 + 4)) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x4E) {
        func_1516972C(arg0);
    } else {
        func_15169850((s32)arg1, (&arg2)[0], (s32)&arg0->unk10, (s32)&arg0->unk14, (s32)arg0);
    }
}
