#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_15149130 */
struct260 *effect_node_create(s16 arg0, s8 arg1, s8 arg2, s8 arg3, u8 arg4, u8 arg5, struct37 *arg6, u8 arg7, s32 arg8) {
    struct260 *temp_v0;
    u8 phi_v0;
    s32 sp24;
    // fakematch? an alternative is to mark sp24 as volatile
    s32 *tmp;

    sp24 = &arg6->unk28;
    tmp = &sp24;

    if ((arg4 & 2) != 0) {
        phi_v0 = 95;
    } else {
        phi_v0 = 35;
    }

    temp_v0 = node_alloc(phi_v0, arg8, *tmp, 1, arg7, 1);
    if (temp_v0 == 0) {
        return NULL;
    }
    temp_v0->unkE  = arg0;
    temp_v0->unk10 = arg1;
    temp_v0->unk11 = arg2;
    temp_v0->unk12 = arg3;
    temp_v0->unkD  = arg4;
    temp_v0->unk13 = arg5;

    // what are we zero-ing out?
    bzero(&temp_v0->unk14, 16);

    return temp_v0;
}

/* was func_151491F4 */
struct260 *effect_node_create_nodraw(s16 arg0, s8 arg1, s8 arg2, u8 arg3, u8 arg4, s32 arg5, u8 arg6, s32 arg7) {
    return effect_node_create(arg0, arg1, arg2, -1, arg3, arg4, arg5, arg6, arg7);
}

/* was func_15149264 */
void effect_node_update(struct260 *arg0) {

    if ((arg0->unkD & 1) != 0) {
        arg0->unkE -= D_800BE9E4;
    }
    if (arg0->unk11 != -1) {
        g_effect_node_update_fns_b[arg0->unk11](arg0);
    }

    if (arg0->unkE < 0) {
        if (arg0->unk10 != -1) {
            g_effect_node_update_fns_a[arg0->unk10](arg0);
        }
    }
    if (arg0->unkE < 0) {
         node_destroy(arg0);
    }
}

/* was func_15149318 */
void effect_node_free_vtx(struct260 *arg0) {
    vtx_slot_buffers_free(&arg0->unk14);
}

/* was func_1514933C */
void effect_node_retire(struct260 *arg0) {
    effect_node_free_vtx(arg0);
    node_retire(arg0);
}

/* was func_15149368 */
void effect_node_free(struct260 *arg0) {
    effect_node_free_vtx(arg0);
    node_unlink_free(arg0);
}

/* was func_15149394 */
void effect_node_kind_call_a(struct260 *arg0) {
    s32 idx = arg0->unk13;

    if (idx < 0) {
        idx = 0U;
    } else {
        if (idx >= 74) {
            idx = 0U;
        }
    }
    g_effect_node_call_a_fns[idx](arg0);
}

/* was func_151493E4 */
void effect_node_kind_call_b(struct260 *arg0) {
    s32 idx = arg0->unk13;

    if (idx < 0) {
        idx = 0U;
    } else {
        if (idx >= 74) {
            idx = 0U;
        }
    }
    g_effect_node_call_b_fns[idx](arg0);
}

/* was func_15149434 */
void effect_node_kind_message(struct260 *arg0, s32 arg1, u8 arg2) {
    s32 idx = arg0->unk13;

    if ((idx < 0) || (idx >= 74)) {
        idx = 0U;
    }

    if (g_effect_node_msg_fns[idx] != 0) {
        g_effect_node_msg_fns[idx](arg0, arg1, arg2);
    }
}

/* was func_15149490 */
s32 effect_node_draw(s32 arg0, struct260 *arg1, s16 arg2) {
    s32 idx = arg1->unk12;
    if (idx != -1) {
        arg0 = g_effect_node_draw_fns[idx](arg0, arg1, arg2);
    }
    return arg0;
}

/* was func_151494E0 */
void effect_nodes_broadcast(s32 arg0, u8 arg1) {
    node_broadcast_types(&D_800A5770, 2, arg0, arg1);
}

/* was func_15149514 */
void effect_node_link_message(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4) {
    node_handle_link_message(arg0, arg1, arg2, arg3, arg4);
}
