#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15044660(void) {
    D_800CC1BC = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15044670.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_1504481C.s")

void func_15044948(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15044950.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15044BC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15044C54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15044D18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15044E68.s")

void func_15044FD4(u8 *arg0) {
    s16 *temp_v0 = *(s16 **)(arg0 + 0x18);
    s16 temp_t0;

    *(s16 *)(arg0 + 6) = temp_v0[0];
    *(s16 *)(arg0 + 8) = temp_v0[1];
    *(s16 *)(arg0 + 0xA) = temp_v0[2];
    temp_t0 = **(s16 **)(arg0 + 0x1C) / 32;
    *(s16 *)(arg0 + 0x10) = temp_t0;
    *(s16 *)(arg0 + 0x12) = temp_t0;
    *(s16 *)(arg0 + 0x14) = temp_t0;
    func_15044E68(arg0);
}

s32 func_15045030(u8 *arg0) {
    func_1505D1C4((f32)*(s16 *)(arg0 + 6), (f32)*(s16 *)(arg0 + 8), (f32)*(s16 *)(arg0 + 0xA), *(s16 *)(arg0 + 0x10), 0xFF, 0, 0, 0);
    return 0;
}

void func_15045090(void) {
    if (D_800CC2D0->stunned == 0) {
        if (D_800CC2D0->immune == 0) {
            func_1505D024(D_800CC2D0, 5, D_800CC2D0->unk7A, -1);
        }
    }
}

void func_150450D8(void) {
    if (D_800CC2D0->stunned == 0) {
        if (D_800CC2D0->immune == 0) {
            if (D_800C35EA != 1) {
                func_1505D024(D_800CC2D0, 4, D_800CC2D0->unk7A, -1);
            }
        }
    }
}

void func_15045130(void) {
    if (D_800CC2D0->stunned == 0) {
        if (D_800CC2D0->immune == 0) {
            func_1505D024(D_800CC2D0, 0x40, D_800CC2D0->unk7A, -1);
        }
    }
}

void func_15045178(void) {
    if (D_800CC2D0->stunned == 0) {
        if (D_800CC2D0->immune == 0) {
            func_1505D024(D_800CC2D0, 1, D_800CC2D0->unk7A, -1);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_150451C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_150453BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_150455FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15045674.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_1504583C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15045A04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15045A70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15045AF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15045B70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15045DD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15046038.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_1504627C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_150464C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15046750.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_150469E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15046C6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15046EF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15046F70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15046FF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15047274.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_150472F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_150473A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_1504715C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_150475B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15047680.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15047978.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_150479F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15047E70.s")
