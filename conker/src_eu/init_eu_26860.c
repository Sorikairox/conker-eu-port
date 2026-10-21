#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
f32 sqrtf(f32 value) {
    return sqrtf(value);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_26860/sqrtf.s")
#endif