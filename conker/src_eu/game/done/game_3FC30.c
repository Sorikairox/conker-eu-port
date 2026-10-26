#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15012780 */
void level_clear_dd410(void) {
    s32 i;

    D_800DD418 = 0;
    for (i = 0; i < 2; i++)
    {
        D_800DD410[i] = 0;
    }
}
