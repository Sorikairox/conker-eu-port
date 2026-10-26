#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern s32 g_cutscene_actor_entries; /* was D_800C3A10 */

/* was func_15023920 */
void setup_link_spawned_obj(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct127 *temp_v0;

    if ((arg0 == 0xB) && (arg1 == 2)) {
        temp_v0 = obj_find_by_spawn(arg3);
        if (temp_v0 != NULL) {
            (*(u8 *)((u8 *)(*(s32 *)((u8 *)&g_cutscene_actor_entries + (arg2 * 4))) + 0x2A)) = (u8) temp_v0->unique_id;
        }
    }
}
