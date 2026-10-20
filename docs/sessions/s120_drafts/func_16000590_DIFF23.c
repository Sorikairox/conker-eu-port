void func_16000590(struct118 *arg0) {
    s32 i;
    s32 pos;
    u32 bits;
    s32 k;
    s32 idx;
    u32 *r;

    k = 0;
    bits = ((u32 *)arg0)[0x12C / 4];
    func_160012B0(3, D_160047A4);
    func_16001044(10, 0, bits);
    bits >>= 12;
    pos = 44;
    for (i = 0; i < 6; i++) {
        if (bits & 1) {
            func_160012B0(pos, (u8 *)D_16003B30[i]);
            pos += 32;
        }
        bits >>= 1;
    }
    pos = 195;
    if (D_16003B28 == 1) {
        idx = 0x4C;
    } else {
        idx = 0x6C;
        k = 16;
    }
    r = (u32 *)arg0 + idx;
    for (i = 0; i < 16; i++) {
        func_160012B0(pos, D_160047AC);
        func_16001044(pos + 2, 1, i + k);
        func_16001044(pos + 5, 2, r[1]);
        r += 2;
        pos += 32;
    }
}
