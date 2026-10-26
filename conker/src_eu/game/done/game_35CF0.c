#include <ultra64.h>

#include "functions.h"
#include "variables.h"

/* was func_15008840 */
void zap_bolt_table_clear(void) {
    bzero(&D_800D99D0, 32); // bzero
}
