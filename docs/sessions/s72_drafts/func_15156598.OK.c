void func_15156598(u8 *arg0, struct127 **arg1, u8 arg2) {
    if (arg2 == 0) {
        s32 a;
        a = arg1[0] - D_800CC2D0;
        if ((a >= 0) && (a < 25) && (a == arg0[0x10])) {
            func_1516972C((struct102 *)arg0);
        }
    } else if (arg2 == 0x2D) {
        s32 a;
        s32 b;
        a = arg1[0] - D_800CC2D0;
        b = arg1[1] - D_800CC2D0;
        if ((a >= 0) && (a < 25) && (b >= 0) && (b < 25)) {
            if (a == arg0[0x10]) { arg0[0x10] = b; }
            else if (b == arg0[0x10]) { arg0[0x10] = a; }
        }
    }
}
