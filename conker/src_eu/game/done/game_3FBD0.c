#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15012720 */
u8 level_get_proj_mode(void) {
    switch(g_level_id)
    {
        case 0:
        case 44:
        case 55:
            return 2;
        case 40:
            return 6;
        default:
            return 5;
    }
}
