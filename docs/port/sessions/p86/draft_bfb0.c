extern void (*D_80088874[])(s32, s32, s32 *);

/* Variadic event dispatch like func_1509BE40, on the second handler table: func_1509BFB0(n, id, arg, x1 .. xn) sets
 * D_800D3380 = {id & 0xFFF, arg, x1 .. xn} and D_800D3C60 = n + 2 for the call (restored after), then calls
 * D_80088874[(id >> 12 & 0xF) - 1](id & 0xFFF, arg, D_800D3380). */
void func_1509BFB0(s32 n, s32 id, s32 arg, ...) {
    va_list ap;
    s32 saved;
    s32 i;

    va_start(ap, arg);
    saved = D_800D3C60;
    D_800D3380[0] = id & 0xFFF;
    D_800D3380[1] = arg;
    for (i = 0; i < n; i++) {
        D_800D3380[i + 2] = va_arg(ap, s32);
    }
    va_end(ap);
    D_800D3C60 = n + 2;
    D_80088874[((id & 0xF000) >> 12) - 1](id & 0xFFF, arg, D_800D3380);
    D_800D3C60 = saved;
}
