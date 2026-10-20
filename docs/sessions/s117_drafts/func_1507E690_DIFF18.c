void func_1507E690(u8 *arg0) {
    if (arg0[4] == 0x2B) {
        return;
    }
    if (D_800C35EA == 1) {
        return;
    }
    if (arg0[0x127] != 0xFF && (*(u8 **)(arg0 + 0x31C))[0x120] != 0) {
        arg0[0x6A] = 1;
        arg0[0x6B] = 1;
        return;
    }
    if (arg0[0x6A] >= 3) {
        arg0[0x6A] = 0;
    }
    if (arg0[0x6B] >= 3) {
        arg0[0x6B] = 0;
    }
    if (arg0[0x6E] >= D_800BE9E4) {
        arg0[0x6E] -= D_800BE9E4;
        return;
    }
    arg0[0x6E] = 0;
    if (arg0[0x6C] == 1) {
        return;
    }
    arg0[0x6A] ^= 1;
    arg0[0x6B] ^= 1;
    if (arg0[0x6A] == 0) {
        arg0[0x6E] = func_150ADA20() % 140U + 10;
    } else {
        arg0[0x6E] = 1;
    }
}
