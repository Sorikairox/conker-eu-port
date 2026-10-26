#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_150FE290 */
void sfx_tick_poke_kind28_objs(s32 arg0) {
    struct127 *p;

    sfx_cooldown_tick();
    if (D_800C35EA == 1) {
        p = D_800CC2D0;
        do {
            if (p->id == 0x28) {
                tank_set_track_speeds(p, 0x14, 0x14);
            }
            p++;
        } while (p != (struct127 *)&D_800D121C);
    }
}
