#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1371A0/func_15109990.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1371A0/func_15109A7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1371A0/func_15109DC8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1371A0/func_1510A1A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1371A0/func_1510A454.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1371A0/func_1510A538.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1371A0/func_1510A8C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1371A0/func_1510A98C.s")

void func_1510ADF0(u8 *arg0, struct212 *arg1, u8 arg2) {
    struct212 *temp_v0 = (struct212 *)(arg0 + 0x28);
    if (arg2 == 0x2D) {
        if (temp_v0->unk0 == arg1->unk0) {
            temp_v0->unk0 = arg1->unk4.i.unk0;
            temp_v0->unk4.b.unk0 = arg1->unk9;
        } else if (temp_v0->unk0 == arg1->unk4.i.unk0) {
            temp_v0->unk0 = arg1->unk0;
            temp_v0->unk4.b.unk0 = arg1->unk8;
        }
    }
}

void func_1510AE4C(u8 *arg0, struct212 *arg1, u8 arg2) {
    struct212 *temp_v0 = (struct212 *)(arg0 + 0x28);
    if (arg2 == 0x2D) {
        if (temp_v0->unk0 == arg1->unk0) {
            temp_v0->unk0 = arg1->unk4.i.unk0;
            temp_v0->unk4.b.unk0 = arg1->unk9;
        } else if (temp_v0->unk0 == arg1->unk4.i.unk0) {
            temp_v0->unk0 = arg1->unk0;
            temp_v0->unk4.b.unk0 = arg1->unk8;
        }
    }
}
