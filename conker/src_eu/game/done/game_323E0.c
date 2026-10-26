#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15004F30 */
void model_kind_tables_clear(void) {
    bzero(&g_model_bases, 748); // bzero
    bzero(&g_type_descs, 748);
    bzero(&g_model_slot_users, 187);
    bzero(&g_model_slot_timers, 187);
    bzero(&g_model_anim_banks, 748);
    bzero(&g_model_anim_counts, 374);
    bzero(&g_model_vtx_ranges, 748);
    bzero(&g_model_coll_tris, 748);
    bzero(&g_model_vtx_ptr_tables, 748);
}
