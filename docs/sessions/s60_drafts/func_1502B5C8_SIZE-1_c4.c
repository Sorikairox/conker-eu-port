#include <stdarg.h>
s32 func_1502B350(u8 *, s32, s32 *);

s32 func_1502B5C8(s32 *arg0, s32 arg1, ...) {
    s32 *var_s2;
    u8 *var_s0;
    s32 sp40[4];
    s32 sp38;
    va_list ap;

    var_s2 = sp40;
    if (arg0 != NULL) {
        var_s2 = arg0;
    }
    *var_s2 = 1;
    var_s0 = D_AB2240;
    va_start(ap, arg1);
    if (arg1 != 0) {
        do {
                        if (*var_s2 != 0) {
                var_s0 += func_1502AC88(var_s0, va_arg(ap, s32), &sp38);
            }
            *var_s2 = sp38 & 0x0FFFFFFF;
        } while (--arg1 != 0);
    }
    if (*var_s2 != 0) {
        return func_1502B350(var_s0, sp38, var_s2);
    }
    return 0;
}
