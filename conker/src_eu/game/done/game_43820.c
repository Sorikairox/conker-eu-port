#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15016370 */
void records_set_tint_180_60_60(void) {
    struct127 *tmp;
    s32 i;

    for (i = 0; i < D_8008FD8C; i++) {
        tmp = &g_objects[i];
        tmp->unk31C->unk114 = 180;
        tmp->unk31C->unk116 = 60;
        tmp->unk31C->unk118 = 60;
    }
}
