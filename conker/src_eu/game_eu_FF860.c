#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 D_800A0CB0;
void func_150D2050(s32 arg0) {
    f32 *sp28;
    sp28 = (f32 *)((arg0 ^ 0) + 0x28); sp28 = sp28;
    func_151467A4(arg0 + 0x30, 10.0f, arg0 + 0x2C, 86.0f, 170.0f, 255.0f, D_800A0CB0, sp28);
    func_1515D4D4(*sp28, ((u8 *)&D_800DCD20)[1], ((u8 *)&D_800DCD20)[2], 0);
}

#ifdef NON_MATCHING
s32 func_1509BE40(s32, s32, ...);
#else
s32 func_1509BE40(s32, s32, s32, s32);
#endif

void func_150D20E0(u8 *arg0) {
    if (func_1509BE40(1, 0x402C, 6, 0x2000) != 0) {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x10);
        return;
    }
    (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & ~0x10);
}
