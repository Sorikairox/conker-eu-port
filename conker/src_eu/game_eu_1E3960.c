#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 obj_dust_trail_spawn();

/* was func_151B6150 */
void obj_dust_trail_on_link(struct127 *arg0, struct127 *arg1) {
    if (arg0->id == 0x53) {
        if (arg1->id == 0x16) {
            obj_dust_trail_spawn(arg1, 0xFF, 1);
        }
    }
}
