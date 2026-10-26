#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// sqrtf (built -O2 so that sqrt.s fills the jr ra delay slot)
/* was func_151EF840 */
f32 game_sqrtf(f32 x) {
    return sqrtf(x);
}
