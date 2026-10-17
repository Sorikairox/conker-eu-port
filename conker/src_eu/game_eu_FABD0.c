#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FABD0/func_150CD3C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FABD0/func_150CD68C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FABD0/func_150CDAAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FABD0/func_150CDD08.s")

void func_150CE07C(s32 arg0) {
    u8 *temp_v1;

    if ((arg0 >= 0) && (arg0 < 0x100) && (D_80088C10 != NULL)) {
        temp_v1 = D_80088C10 + 0x28;
        *(f32 *)(temp_v1 + 4) = arg0 * D_800A0B74;
    }
}
