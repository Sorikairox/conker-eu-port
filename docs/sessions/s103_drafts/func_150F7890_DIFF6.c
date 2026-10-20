void func_150F7890(u8 *arg0, u8 *volatile arg1, volatile u8 arg2) {
    u8 *p;

    p = arg0 + 0x28;
    if (arg2 == 0x3E) {
        if ((*(s32 *)p == *(s32 *)arg1) || (p[4] == arg1[4])) {
            func_1516972C(arg0);
        }
    } else {
        func_15149514(arg1, arg2, p, p + 4, arg0);
    }
}
