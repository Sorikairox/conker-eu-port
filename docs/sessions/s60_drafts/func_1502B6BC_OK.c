#include <stdarg.h>
s32 func_1502B350(u8 *, s32, s32 *);
s32 func_1502B4A8(s32, s32);
s32 func_1502B6BC(s32 *arg0, s32 arg1, s32 *arg2, s32 arg3, ...) {
    s32 *var_s2;
    s32 v;
    s32 sp44;
    s32 var_s0;
    u8 *var_s0_2;
    s32 sp38;
    va_list ap;
    var_s2 = &sp44;
    if (arg0 != NULL) {
        var_s2 = arg0;
    }
    *var_s2 = 1;
    var_s0_2 = D_AB2240;
    va_start(ap, arg3);
    if (arg3 != 0) {
        do {
            v = va_arg(ap, s32);
            if (*var_s2 != 0) {
                var_s0_2 += func_1502AC88(var_s0_2, v, &sp38);
            }
            *var_s2 = sp38 & 0x0FFFFFFF;
        } while (--arg3 != 0);
    }
    if (*var_s2 != 0) {
        var_s0 = func_1502B350(var_s0_2, sp38, var_s2);
        if ((*var_s2 != 0) && (var_s0 != 0)) {
            arg1 = func_1502B4A8(var_s0, arg1);
        } else {
            arg1 = 0;
        }
        if (arg2 != NULL) {
            *arg2 = arg1;
        }
    } else {
        var_s0 = 0;
    }
    return var_s0;
}
