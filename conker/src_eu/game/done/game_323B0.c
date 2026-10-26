#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15004F00 */
void attachment_list_reset(void) {
    D_800C3EE0 = 0;
}

/* was func_15004F10 */
void joint_chain_reset_mask_init(void) {
    D_800C4000 = 0xF;
}
