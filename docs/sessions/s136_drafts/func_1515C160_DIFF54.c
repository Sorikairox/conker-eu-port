s32 func_1513F4E4(s32, u8, s8 *);
s32 func_15142B7C(s32, s32, s32);
s32 func_15142C10(s32, s16, s16, s16, s32, s8 *);
s32 func_15142CF0(s32, s32, s32, s16, s32, s32, s32, s8 *);
s32 func_15142E24(s32, struct_eu_80090F10 *, s32, s32, s32, s32, s32, s32, s32, s8 *, s32);
u8 *func_15142FBC(s32, s32, s32, s8 *);
s32 func_151441A4(s16 *, s16 *, s16 *, s16 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_151442FC(s16 *, s16 *, s16 *, s16 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_800D30BC;

extern u32 D_800A4EA8[][2];
u8 *func_1515C160(s32 arg0, u8 *arg1, s32 arg2) {
    s8 flag;
    s16 a0, a1, a2, a3;
    s16 b0, b1, b2, b3;
    s32 x1, x2;
    s32 g;
    s32 m;
    u32 *t;

    flag = 1;
    func_151441A4(&a0, &a1, &a2, &a3, arg1[0x20], arg1[0x21], arg1[0x22], arg1[0x23], arg1[0x24], arg1[0x25], arg1[0x26], arg1[0x27], arg1[0x28], arg1[0x29]);
    func_151442FC(&b0, &b1, &b2, &b3, arg1[0x20], arg1[0x21], arg1[0x22], arg1[0x23], arg1[0x24], arg1[0x25], arg1[0x26], arg1[0x27], arg1[0x28], arg1[0x2A]);
    g = func_15142B7C(arg0, *(s32 *)(arg1 + 0x30), *(s32 *)(arg1 + 0x34));
    g = func_15142C10(g, b0, b1, b2, b3, &flag);
    g = func_15142CF0(g, 0, 0, a0, a1, a2, a3, &flag);
    g = func_15142E24(g, &D_80090F10[arg1[0x10]], *(s32 *)(arg1 + 0x18), 0, 0, 0, arg1[0x10], 0, 0, &flag, 3);
    g = func_1513F4E4(g, arg1[0x2C], &flag);
    if (arg1[0x11] & 2) {
        m = 0x100000;
    } else {
        m = 0;
    }
    t = (u32 *)func_15142FBC(g, m | 0x80000 | D_800D30BC | 0x2CA0, D_800A4EA8[arg1[0x2B]][1] | D_800A4EA8[arg1[0x2B]][0], &flag);
    t[1] = (u32)(arg1 + 0x50);
    t[0] = 0x01004008;
    t[2] = 0x05000204;
    t[3] = 0;
    t[4] = 0x05000406;
    t[5] = 0;
    return (u8 *)(t + 6);
}
