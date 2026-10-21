void func_1510F800(s32);
void func_150A49D0(s32, s16 *, s32);
u8 *func_150A6324(s16 *, u8 *, s32, s32);
extern s32 D_800D3AB0;
extern s16 D_800D3C00[];
extern s32 D_800DC26C;
extern s32 D_800DF514;
extern s32 D_800DF518;
extern s32 D_800DF51C;
extern s32 D_800DF520;
extern s32 D_800DF524;

s32 func_15187954(s32 arg0, s32 arg1, s32 arg2, u8 *arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 n;
    s32 i;
    u8 *p;
    s32 r;
    s32 c;

    if (D_800DC320 == 0) {
        return arg6;
    }
    func_1510F800(2);
    arg3 += arg6 * 0x14;
    D_800DF518 = arg0 - arg2;
    D_800DF51C = arg0 + arg2;
    D_800DF520 = arg1 - arg2;
    D_800DF524 = arg1 + arg2;
    n = 0;
    for (i = 0, p = (u8 *)D_800DBEF4; i < D_800DC320; i++, p += 0xA0) {
        if (p[0x6E] != 0) {
            continue;
        }
        if (p[0x4F] & 0x60) {
            continue;
        }
        r = *(u16 *)(p + 0x52);
        if (r < *(u16 *)(p + 0x50)) {
            r = *(u16 *)(p + 0x50);
        }
        c = *(s16 *)(p + 0x10);
        if (D_800DF51C < c - r || c + r < D_800DF518) {
            continue;
        }
        c = *(s16 *)(p + 0x14);
        if (D_800DF524 < c - r || c + r < D_800DF520) {
            continue;
        }
        D_800D3C00[n++] = i;
    }
    if (n != 0) {
        func_150A49D0(n, D_800D3C00, 0);
        D_800D3AB0 = D_800DC26C;
        D_800DF514 = n;
        arg6 += (func_150A6324(D_800D3C00, arg3, arg4, arg5) - arg3) / 20;
    }
    return arg6;
}
