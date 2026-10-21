#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BA680/func_1518C900.s")

extern u8 D_800DFC00[];
extern s32 D_800DFDE8[];
extern s32 *D_800E0578[];
void func_1518CF74(s32 arg0) {
    if (arg0 != 0x1E4 && D_800DFC00[arg0] != 0) {
        if (--D_800DFC00[arg0] == 0) {
            func_1510DBB0(D_800DFDE8[arg0]);
            func_100043B4(D_800E0578[arg0], 4);
        }
    }
}
