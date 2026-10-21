typedef struct {
    u8 *u20;
    u8 u24;
    u8 pad25;
    s16 u26;
    s8 u28;
    s8 u29;
    s8 u2A;
} SpawnBE04;
u8 *func_15190770(u8 **arg0, s32 arg1, u8 arg2, s32 arg3);

void func_151ABE04(u8 *arg0) {
    SpawnBE04 sp;
    u8 *p;
    u8 k;

    p = *(u8 **)(arg0 + 0x18);
    k = p[4];
    if (k == 0 || k == 1 || k == 2 || k == 3 || k == 4 || k == 0x96) {
        sp.u20 = p;
        sp.u26 = 0x12C;
        sp.u28 = 0;
        sp.u29 = 0;
        sp.u24 = p[0x3B];
        if (p[4] == 0x96) {
            sp.u2A = 3;
        } else {
            sp.u2A = 0;
        }
        if (p[0x127] != 0xFF) {
            *(s16 *)(*(u8 **)(p + 0x31C) + 0x66) = 0x1F4;
        }
        func_15190770((u8 **)&sp, 0, arg0[0xC], arg0[1]);
    }
}
