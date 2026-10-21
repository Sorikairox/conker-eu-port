void func_1513F680(u8 *, u8, u8, u8, u8);
extern f32 D_800A5B6C;
extern f32 D_800A5B70;
s32 func_1514A004(u8 *arg0) {
    s32 off; // fakematch: offset in a variable keeps arg0+0x110 in a register (s166)
    s32 done = 1;
    u8 *v;

    off = 0x110;
    if (!(arg0[0x74] & 2)) {
        v = arg0 + off;
        *(f32 *)(arg0 + 0x2C) = (*(f32 *)(v + 8) - *(f32 *)(arg0 + 0x2C)) * *(f32 *)(v + 0x44) + *(f32 *)(arg0 + 0x2C);
        if (*(f32 *)(v + 8) * D_800A5B6C < *(f32 *)(arg0 + 0x2C)) {
            arg0[0x74] |= 2;
            done = 0;
        } else {
            done = 0;
        }
    }
    if (!(arg0[0x74] & 8)) {
        v = arg0 + off;
        *(f32 *)(arg0 + 0x30) = (*(f32 *)(v + 0x20) - *(f32 *)(arg0 + 0x30)) * *(f32 *)(v + 0x44) + *(f32 *)(arg0 + 0x30);
        if (*(f32 *)(v + 0x20) * D_800A5B70 < *(f32 *)(arg0 + 0x30)) {
            arg0[0x74] |= 8;
            done = 0;
        } else {
            done = 0;
        }
    }
    if (done) {
        func_1513F680(arg0, arg0[0x70], 0xD, arg0[0x72], arg0[0x73]);
    }
    if (*(s16 *)(arg0 + 0x1C) < 5) {
        func_1513F680(arg0, arg0[0x70], arg0[0x158], arg0[0x72], arg0[0x73]);
        *(s16 *)(arg0 + 0x1C) = 100;
        *(s32 *)(arg0 + 0x58) &= ~1;
    }
    return 1;
}
