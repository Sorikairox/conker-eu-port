extern void (*D_8008A3CC[])(struct102 *, u8 *, u8);
void func_151416E8(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *p;

    if (D_8008A3CC[*((u8 *)arg0 + 0x168)] != NULL) {
        D_8008A3CC[*((u8 *)arg0 + 0x168)](arg0, arg1, arg2);
    }
    if (arg2 == 0x22 || arg2 == 0x24 || arg2 == 0x25) {
        p = (u8 *)arg0 + 0x110;
        if (*arg1 == p[0x58]) {
            switch (arg2) {
            case 0x22:
                func_1516972C(arg0);
                break;
            case 0x24:
                p[0x59] = -1;
                break;
            case 0x25:
                p[0x59] = 2;
                break;
            }
        }
    }
}
