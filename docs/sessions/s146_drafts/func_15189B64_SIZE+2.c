typedef struct { u8 u0; u8 u1; u8 u2; u8 u3; u8 pad4[4]; u8 *u8_; u8 padC[4]; u8 *u10; s32 u14; } S9B64;
extern u8 *D_800DFBF0;
extern u8 D_800DFBF4;
s32 func_15084E34(u8 *, s32 *);
void func_1503DD8C(u8 *, s32, s32, s32);
s32 func_1502DE10(u8);
Gfx *func_1502CC64(Gfx *, s32, s16, s32, s32);
Gfx *func_15189B64(Gfx *gfx, S9B64 *arg1, s16 arg2) {
    s32 sp64;
    s32 saved;
    s32 n;
    s32 m;
    s32 cnt;
    s32 base;
    s32 idx;
    s32 i;
    s32 count;
    u8 *obj;

    if (arg1->u2 == 0) {
        return gfx;
    }
    func_1503DD8C(arg1->u10, func_15084E34(arg1->u10, &sp64), sp64, 1);
    n = arg1->u1;
    m = arg1->u3;
    cnt = func_1502DE10(arg1->u10[4]);
    obj = arg1->u10;
    base = D_800BE9C0 * cnt * n;
    count = arg1->u2;
    idx = (obj - (u8 *)D_800CC2D0) / 0x32C;
    if (idx < 0 || idx >= 0x19) {
        return gfx;
    }
    saved = *(s32 *)(obj + 0x94);
    *(s32 *)(obj + 0x94) = arg1->u14;
    for (i = 0; i < count; i++) {
        D_800DFBF0 = arg1->u8_ + (base + i * cnt) * 0x40;
        D_800DFBF4 = (m * 3 * 0x20 + i * m * 0x20) >> 8;
        gfx = func_1502CC64(gfx, idx, arg2, 4, 1);
    }
    *(s32 *)(arg1->u10 + 0x94) = saved;
    return gfx;
}
