#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* P28: under IDO sqrtf() is the sqrt.s intrinsic; elsewhere a plain sqrtf() call in sqrtf recurses forever */
#if defined(__GNUC__) || defined(__clang__)
#define NM_SQRTF(x) __builtin_sqrtf(x)
#else
#define NM_SQRTF(x) sqrtf(x)
#endif

#ifdef NON_MATCHING
f32 sqrtf(f32 value) {
    return NM_SQRTF(value);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_26860/sqrtf.s")
#endif