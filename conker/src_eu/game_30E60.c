#include <ultra64.h>

#include "functions.h"
#include "variables.h"

// EU only: split from game_305D0.c, EU pads to a file boundary before this.

void func_150039B0(s32 arg0) {
}

void func_150039BC(s32 arg0) {
    D_800DBE5C = arg0;
    if (D_800DBE5C) {
        D_800DBE5C += 8;
    }
}
