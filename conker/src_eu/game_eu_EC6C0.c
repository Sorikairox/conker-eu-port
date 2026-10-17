#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EC6C0/func_150BEEB0.s")

s32 func_150BEFA8(s32 arg0, s32 arg1) {
    if ((arg0 == 0) || (arg0 == 1)) {
        return 0x11;
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EC6C0/func_150BEFCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EC6C0/func_150BF130.s")

s32 func_150BF228(s32 arg0, s32 arg1) {
    if ((arg0 == 0) || (arg0 == 1)) {
        return 0x12;
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EC6C0/func_150BF24C.s")

s32 func_1509BE40(s32, s32, s32, s32);

void func_150BF3B0(u8 *arg0) {
    if ((func_1509BE40(1, 0x4063, 6, 0x2000) != 0) || (func_1509BE40(1, 0x4001, 6, 0x9000) != 0)) {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x1010);
    } else {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & ~0x1010);
    }
    if (func_1509BE40(1, 0x4069, 6, 0x2000) != 0) {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x01000000);
        return;
    }
    (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & 0xFEFFFFFF);
}
