
// buddy_marker_create: clears the old markers (func_1519E688) and, if none is active (D_800E0D50), creates a
// marker effect (func_151491F4, type 9) whose 12-byte payload at +0x28 is {owner arg0, owner id arg0[0x3B], 0}.
// P124: the payload is one struct (m2c had 3 locals and memcpy'd 12 bytes from the first).
void func_1519E6BC(u8 *arg0) {
    struct {
        u8 *u0;
        u8 u4;
        s32 u8;
    } t;
    s32 fx;

    func_1519E688();
    if (D_800E0D50 == 0) {
        t.u8 = 0;
        t.u0 = arg0;
        t.u4 = arg0[0x3B];
        fx = func_151491F4(0x12C, -1, 9, 0U, 4U, 0xC, 0xFFU, 0);
        D_800E0D50 = fx;
        if (fx != 0) {
            memcpy(fx + 0x28, (u8 **) &t, 0xC);
        }
    }
}
