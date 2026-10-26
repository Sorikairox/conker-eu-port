#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_15178E50 */
s32 level_screen_effect_active(s32 arg0) {
    if ((D_800B0DF0->unk14 == 1)) {
        s32 tmp = D_800DBFF0->unk2FC;
        if (D_800B0DF0->unk16 < tmp) {
            return 1;
        }
    }
    return 0;
}
