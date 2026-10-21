s32 func_1000C350(s32 arg0, u8 arg1, s32 arg2, s32 arg3) {
    if (!(arg0 & 0x80)) {
        arg0 |= 0x80;
        if (D_800C35EA != 1) {
            func_1000886C(arg1, 0x1E, 1U);
            func_1000886C(arg1, 1, 1U);
            func_1000E40C(0x23, 0x61A8);
        } else if (D_800C3A08 == 3) {
            func_1000E40C(0x23, 0xFA);
            func_1517946C(2);
        } else if (D_800C3A08 == 6) {
            func_1000886C(arg1, 0x1E, 1U);
            func_1000886C(arg1, 1, 0x40U);
            func_1517946C(2);
        } else {
            func_1000E40C(0x23, 0x61A8);
        }
        return arg0;
    } else if (D_800BE9F0 != 0x1D) {
        func_10008F24(arg1);
    } else if (D_80041F08 != (arg0 & 0x7FU)) {
        switch (D_80041F08) {
        case 1:
            func_10008790(arg1, 0x1E, 0U, 0);
            func_10008790(arg1, 1, 0x40U, 0);
            break;
        case 2:
            func_10008790(arg1, 0x18, 0xFFU, 0);
            func_10008790(arg1, 6, 0U, 0);
            func_10008790(arg1, 1, 1U, 0);
            break;
        }
        arg0 = D_80041F08 | 0x80;
    }
    return arg0;
}
