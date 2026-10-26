#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15011C40 */
void level_clear_be500(void) {
    bzero(&g_sky_segment_on, 5); // bzero
}
