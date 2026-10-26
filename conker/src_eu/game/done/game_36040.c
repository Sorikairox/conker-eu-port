#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15008B90 */
void level_timed_queue_init(void) {
    level_timed_queue_create();
}

/* was func_15008BB0 */
void level_timed_queue_create(void) {
    g_level_timed_queue = timed_queue_create(12, 1000, 1);
}

/* was func_15008BE0 */
void level_load_stub(void) {
}
