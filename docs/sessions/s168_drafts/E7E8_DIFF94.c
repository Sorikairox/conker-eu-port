u8 *func_1515F0F4(s32, s32, s32, s32, u8 **);
void func_1515E9AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4, u8 *arg5, u8 *arg6, u8 *arg7);
void func_1515E7E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4, u32 arg5, s32 arg6) {
    s32 pad[1];
    u8 tmp[3];
    u8 colA[3];
    u8 colB[3];
    u8 fadeA;
    u8 fadeB;
    u8 *p;
    u8 *s;
    u8 *d;
    u8 *a;
    u8 *b;
    u8 *t;
    s32 v;

    p = func_1515F0F4(arg0, arg1, arg2, arg3, (u8 **)D_800DCD80);
    if (p != NULL) {
        arg4[0] = *(u32 *)(p + 0x18);
        arg4[1] = *(u32 *)(p + 0x18) >> 8;
        arg4[2] = *(u32 *)(p + 0x18) >> 16;
    } else {
        d = arg4;
        for (s = (u8 *)&D_800DCD20; s != (u8 *)&D_800DCD20 + 3; s++, d++) {
            *d = (*s * (0x100 - ((s32)((arg5 >> 5) & 3) << 6))) >> 8;
        }
    }
    if (arg6 & 0x10) {
        func_1515E9AC(arg0, arg1, arg2, arg3, colA, colB, &fadeA, &fadeB);
        d = arg4;
        for (t = tmp, a = colA, b = colB; b != colB + 3; t++, a++, b++, d++) {
            *t = (*a * (u8)(*d + (((0xFF - *d) * fadeA) >> 8))) >> 8;
            *d = (*b * (u8)(*d + (((0xFF - *d) * fadeB) >> 8))) >> 8;
            v = ((*t * 7) >> 3) + *d;
            if (v >= 0x100) {
                v = 0xFF;
            }
            *d = v;
        }
    }
}
