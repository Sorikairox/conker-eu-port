#include <ultra64.h>

#include "functions.h"
#include "variables.h"


extern struct54 *D_8003841C;

// heap init: one free block spanning D_800EA140 .. D_80038098
void func_10003BD0(void) {
    D_800380B4 = &D_800EA140;
    D_800380B4->unk0 = NULL;
    D_800380B4->unk4 = NULL;
    D_800380B4->unk8 = D_80038098 - (u32)&D_800EA140 - 0x14;
    D_800380B4->unkC = 0;
    D_800380B4->unk10 = 0;
    D_800380B8 = D_8003841C = D_800380B4;
    D_800380B0 = D_800380B4;
}
