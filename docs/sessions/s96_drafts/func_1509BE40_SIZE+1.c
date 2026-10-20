#include <stdarg.h>
extern s32 D_800D3380[];
extern s32 D_800D3C60;
extern void (*D_80088838[])(s32, s32, s32 *);
void func_1509BE40(s32 n, s32 x, s32 b, ...) {
    va_list ap;
    s32 idx;
    s32 saved;
    s32 i;
    s32 a;
    va_start(ap, n);
    a = va_arg(ap, s32);
    b = va_arg(ap, s32);
    saved = D_800D3C60;
    idx = ((a & 0xF000) >> 12) - 1;
    a &= 0xFFF;
    D_800D3380[0] = a;
    D_800D3380[1] = b;
    for (i = 0; i < n; i++) {
        D_800D3380[i + 2] = va_arg(ap, s32);
    }
    D_800D3C60 = n + 2;
    D_80088838[idx](a, b, D_800D3380);
    D_800D3C60 = saved;
}
