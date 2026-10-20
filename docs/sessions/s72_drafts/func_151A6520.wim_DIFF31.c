void func_151A6618(u8 *, s32, s32, s32, u8, u8);
void func_151A6520(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 **q = &arg0;
    s32 *m = arg1;
    s32 i;
    s32 found;
    u8 *p;
    u8 *v;
    u8 c;
    if (arg2 == 0x35) {
        found = 0;
        for (i = 0, p = (u8 *)m[1]; (i < m[0]) && (found == 0); ) {
            if (*p == (*q)[0x2C]) { found = 1; } else { i++; p++; }
        }
        if (found) {
            v = (*q) + 0x28;
            if ((*(u8 **)v)[0x14] == 1) {
                c = v[0xC];
                { u8 a; u8 b; a = c; b = c; a &= 1; b &= 2; func_151A6618(*(u8 **)v, *(s32 *)(v + 8), a, b, (*q)[0xC], (*q)[1]); }
                (*(u8 **)v)[0x14] = 0;
                *(s32 *)(v + 0x10) = m[2];
            }
        }
    }
}
