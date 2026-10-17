#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_3CA50/func_1500F240.s")

void func_1500F328(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct260 *temp_v0;

    temp_v0 = func_151491F4((s16) ((func_150ADA20() & 0x7F) + 0xA), 1, -1, 1U, 0U, 0xA, 0xFFU, 0);
    if (temp_v0 != NULL) {
        (*(s16 *)((u8 *)temp_v0 + 0x28)) = (s16) arg0;
        (*(s16 *)((u8 *)temp_v0 + 0x2A)) = (s16) arg1;
        (*(s16 *)((u8 *)temp_v0 + 0x2C)) = (s16) arg2;
        (*(s16 *)((u8 *)temp_v0 + 0x2E)) = (s16) arg3;
        (*(s8 *)((u8 *)temp_v0 + 0x30)) = 1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_3CA50/func_1500F3BC.s")
