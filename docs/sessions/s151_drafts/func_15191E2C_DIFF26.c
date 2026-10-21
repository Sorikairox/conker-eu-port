s32 func_15190770(u8 *, s32, u8, u8);
void func_15191E2C(u8 *arg0) {
    s32 pad;
    u8 *o;
    u8 done;
    u8 *p;

    o = *(u8 **)(arg0 + 0x28);
    done = 0;
    if (*(s32 *)o == 0) {
        done = 1;
    } else if (arg0[0x2C] != o[0x3B]) {
        done = 1;
    }
    if (!done && *(s32 *)(o + 0x1D4) != 0) {
        p = arg0 + 0x28;
        done = 1;
        if (arg0[0xD] & 1) {
            p[8] |= 1;
            *(s16 *)(p + 6) = *(s16 *)(arg0 + 0xE);
        } else {
            *(s16 *)(p + 6) = 0x12C;
        }
        func_15190770(p, 0, arg0[0xC], arg0[1]);
    }
    if (done) {
        func_1516972C((struct102 *)arg0);
    }
}
