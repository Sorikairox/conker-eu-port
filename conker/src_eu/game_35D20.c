#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// loops and loops
/* was func_15008870 */
void effect_lists_clear(s32 arg0) {
    s32 start = 0;
    s32 end = 0x68;
    s32 i;
    s32 j;

    if (arg0 == 1) {
        end = 0x65;
    } else if (arg0 == 2) {
        start = 0x65;
    }
    for (i = 0; i < 2; i++) {
        for (j = start; j < end; j++) {
            D_800DD280[i][j] = NULL;
        }
    }
}
/* was func_15008930 */
void effect_run_init_hooks(s32 arg0) {
    void (**funcs)(void);
    s32 i;
    s32 count;

    if (arg0 == 1) {
        funcs = D_80082F60;
        count = 1;
    } else if (arg0 == 2) {
        funcs = D_80082F64;
        count = 1;
    } else {
        count = 0;
    }
    for (i = 0; i < count; i++) {
        funcs[i]();
    }
    D_800DD5E0 = -1;
}
