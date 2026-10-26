#include <ultra64.h>

#include "functions.h"
#include "variables.h"

/* was func_15008840 */
void zap_bolt_table_clear(void) {
    bzero(&g_zap_bolts, 32); // bzero
}
