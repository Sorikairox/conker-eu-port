#include <ultra64.h>

#include "functions.h"
#include "variables.h"


f32 func_150489B0(); // fakematch: K&R decl so func_15048A40 re-masks the u8 arg (ref calls an undeclared function)
extern f32 D_8009A3E0[];
extern f32 D_8009A5E0[];
extern u8 D_8009A7E0[];
extern u8 D_8009A9E0[];
f32 func_150489B0(arg0)
u8 arg0;
{
    f32 r;
    s32 i;
    i = arg0;
    if (arg0 > 0x40) {
        if (arg0 > 0x80) {
            if (arg0 > 0xC0) {
                r = *(f32 *)(D_8009A9E0 + -(arg0 * 4));
            } else {
                r = -D_8009A3E0[i];
            }
        } else {
            r = -*(f32 *)(D_8009A7E0 + -(arg0 * 4));
        }
    } else {
        r = D_8009A5E0[arg0];
    }
    return r;
}

f32 func_15048A40(u8 arg0) {
    return func_150489B0((arg0 - 0x40) & 0xFF);
}

f32 func_15048A70(f32 arg0, f32 arg1) {
    f32 tmp = arg0 - arg1;
    if (tmp > 180.0f) {
        arg0 -= 360.0f;
    } else {
        if (tmp <= -180.0f) {
            arg1 -= 360.0f;
        }
    }
    return arg1 - arg0;
}

s32 func_15048AD0(s32 arg0, s32 arg1) {
    s32 temp_v0 = arg0 - arg1;
    if (temp_v0 >= 181) {
        arg0 = arg0 - 360;
    } else {
        if (temp_v0 < -179) {
            arg1 = arg1 - 360;
        }
    }
    return arg1 - arg0;
}
