#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// sqrtf (built -O2 so that sqrt.s fills the jr ra delay slot)
f32 func_151EF840(f32 x) {
    return sqrtf(x);
}
