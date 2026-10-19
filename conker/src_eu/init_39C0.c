#include <ultra64.h>

#include "functions.h"
#include "variables.h"

void func_10003ACC(s32 arg0, s32 arg1, s32 arg2);


void func_100039C0(void) {
    D_800BE620 = 292; // screen width px
    D_800BE624 = 216; // screen height px
    D_800380A0 = (f32) D_800BE620 / 292.0f;
    D_800380A4 = (f32) D_800BE624 / 216.0f;
    D_800BE9C4 = allocate_memory(D_800BE620 * D_800BE624 * 2, 255, 3, 0);
    func_10003ACC(0, 0, 0);
    func_15015FBC(D_800BE620, D_800BE624);
    // EU: the VI mode is no longer set here
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_39C0/func_10003ACC.s")

// EU only
#pragma GLOBAL_ASM("asm/nonmatchings/init_39C0/func_10003C10.s")
