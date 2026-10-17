#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FF860/func_150D2050.s")

s32 func_1509BE40(s32, s32, s32, s32);

void func_150D20E0(u8 *arg0) {
    if (func_1509BE40(1, 0x402C, 6, 0x2000) != 0) {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x10);
        return;
    }
    (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & ~0x10);
}
