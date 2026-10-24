#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_151C9CBC(s32 arg0, s32 arg1);
void func_1515F170(s32, s32);

// level_effects_reset: resets the 17 effect slots 6..0x16 of D_800D34B8 (0x34 bytes each, func_151C9CBC mode 1;
// the asm copies the ids from a local table) and then calls func_1515F170(9, 1). arg0 is unused.
void func_150F58C0(s32 arg0) {
    static const s32 ids[17] = { 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22 };
    u8 i;

    for (i = 0; i <= 16; i++) {
        func_151C9CBC(1, (s32)(D_800D34B8 + ids[i] * 0x34));
    }
    func_1515F170(9, 1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1230D0/func_150F58C0.s")
#endif
