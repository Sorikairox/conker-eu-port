#include <ultra64.h>

#include "functions.h"
#include "variables.h"


// wtf?
void func_15049260(struct_eu_bytes24 arg0) {
    func_150AB278(arg0);
}

void func_150492CC(f32 arg0, f32 arg1, f32 arg2) {
    D_800CC640 = arg0;
    D_800CC644 = arg1;
    D_800CC648 = arg2;
    D_800CC64C = arg0 / 2;
    D_800CC650 = arg1 / 2;
    D_800CC654 = arg2 / 2;
    if (arg0 == 0.0f) {
        arg0 = D_80099430;
    }
    D_800CC658 = arg1 / arg0;
    D_800CC65C = arg2 / arg0;
}

// too many temp vars
#pragma GLOBAL_ASM("asm/nonmatchings/game_76710/func_15049350.s")
