#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15008DD0 */
void player_morph_cache_clear(void) {
    s32 i;

    for (i = 0; i < 2; i++)
    {
        D_800DD460[i] = 0;
    }
}
