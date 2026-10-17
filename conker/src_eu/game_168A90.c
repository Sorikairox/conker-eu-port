#include <ultra64.h>

#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B5E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B798.s")
// NON-MATCHING: only the stack slot of done differs (0x1B vs 0x1F)
// void func_1513B798(struct_eu_168A90 *arg0) {
//     u8 done;
//
//     done = FALSE;
//     if (arg0->unk10 & 1) {
//         arg0->unk14 -= D_800BE9E4;
//         if (arg0->unk14 < 0) {
//             done = TRUE;
//         }
//     }
//     if (!done) {
//         if (arg0->unk11 != -1) {
//             if (D_80089FB8[arg0->unk11](arg0) == 0) {
//                 done = TRUE;
//             }
//         }
//     }
//     if (done) {
//         func_1516972C(arg0);
//     }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B83C.s")

s32 func_1513B968(s32 arg0, s32 arg1) {
    // FIXME: &arg0->unk_120[D_800BE9C0]
    func_150A7B80(arg0 + 120 + (D_800BE9C0 << 6));
    return 1;
}

void func_1513B9A8(struct132 *arg0) {
    func_100043B4(arg0->unk4C, 4);
    func_15169804(arg0);
}

void func_1513B9DC(struct132 *arg0) {
    func_100043B4(arg0->unk4C, 4);
    func_15169824(arg0);
}

void func_1513BA10(struct132 *arg0) {
    D_80089C44[arg0->unk48]();
}

void func_1513BA44(struct132 *arg0) {
    D_80089C54[arg0->unk48]();
}

void func_1513BA78(u8 *arg0, s32 arg1, u8 arg2) {
    switch (arg0[0x48]) {
    case 1:
        func_151095E4(arg0, arg1, arg2);
        break;
    case 2:
        func_151BAA18(arg0, arg1, arg2);
        break;
    }
}

s32 func_1513BAD4(s32 arg0, s32 arg1) {
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513BAE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513BBFC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513BEB0.s")
