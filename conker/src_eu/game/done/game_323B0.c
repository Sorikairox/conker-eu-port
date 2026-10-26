#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15004F00 */
void attachment_list_reset(void) {
    g_attachment_list = 0;
}

/* was func_15004F10 */
void joint_chain_reset_mask_init(void) {
    g_tail_reset_mask = 0xF;
}
