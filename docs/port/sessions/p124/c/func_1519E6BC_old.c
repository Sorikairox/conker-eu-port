s32 memcpy(s32, u8 **, s32);

void func_1519E6BC(u8 *arg0) {
    s32 sp34;
    u8 sp30;
    u8 *sp2C;
    s32 temp_v0;

    func_1519E688();
    if (D_800E0D50 == 0) {
        sp34 = 0;
        sp2C = arg0;
        sp30 = (*(u8 *)((u8 *)arg0 + 0x3B));
        temp_v0 = func_151491F4(0x12C, -1, 9, 0U, 4U, 0xC, 0xFFU, 0);
        D_800E0D50 = temp_v0;
        if (temp_v0 != 0) {
            memcpy(temp_v0 + 0x28, &sp2C, 0xC);
        }
    }
}
