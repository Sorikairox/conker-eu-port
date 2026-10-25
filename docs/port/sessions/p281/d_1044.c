/* P281: readable C for func_16001044 (compiled C, 155 insns). */
extern u8 D_160047E4[]; /* "NaN" */
extern u8 D_160047E8[]; /* "%s%s%f" */
extern u8 D_160047F0[]; /* "" */
extern u8 D_160047F4[]; /* "" */
// debug_print_value: prints `value` at text cell `cell` (rows from D_160038A0 to 0x340): kind 0 = 8 hex digits
// (written right to left), kind 1 = signed decimal without leading zeros, kind 2 = the float whose bits are `value`
// ("NaN" for infinities, NaNs and denormals).
void func_16001044(s32 cell, s32 kind, s32 value) {
    s32 pow10[10] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };
    u8 buf[0x24];
    u8 *pos;
    s32 *p;
    s32 i;
    s32 digit;
    s32 started;
    u8 c;
    s32 exp;

    if (cell < D_160038A0 * 32 || cell >= 0x341) {
        return;
    }
    pos = (u8 *) func_1600160C(cell);
    switch (kind) {
        case 0:
            pos += 0x70;
            for (i = 0; i < 8; i++) {
                c = value & 0xF;
                if (c >= 10) {
                    c += 7;
                }
                c += '0';
                func_160014F0((s16 *) pos, c);
                value >>= 4;
                pos -= 0x10;
            }
            break;
        case 1:
            if (value < 0) {
                pos = func_160014F0((s16 *) pos, '-');
                value = -value;
            }
            started = 0;
            for (p = &pow10[9]; p >= pow10; p--) {
                digit = value / *p;
                value = value % *p;
                if (digit > 0 || started || p == pow10) {
                    pos = func_160014F0((s16 *) pos, (u8) (digit + '0'));
                    started = 1;
                }
            }
            break;
        case 2:
            exp = (value & 0x7F800000) >> 23;
            if ((exp <= 0 || exp >= 0xFF) && (exp != 0 || (value << 9) != 0)) {
                func_160012B0(cell, D_160047E4);
                return;
            }
            func_16001B34(buf, D_160047E8, D_160047F0, D_160047F4, *(f32 *) &value); /* sprintf */
            func_160012B0(cell, buf);
            break;
    }
}
