#include <ultra64.h>

#include "functions.h"
#include "variables.h"

// EU only: split from game_305D0.c, EU pads to a file boundary before this.

/* was func_150039B0 */
void collision_noop(s32 arg0) {
}

/* was func_150039BC */
void collision_set_tri_flags_table(s32 arg0) {
    D_800DBE5C = arg0;
    if (D_800DBE5C) {
        D_800DBE5C += 8;
    }
}
