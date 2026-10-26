#include <ultra64.h>

#include "functions.h"
#include "variables.h"

// owner-less u16 table at the start of this file's .rodata (no code reference)
const u16 D_eu_1FFF60_ro[20] = {
    0x01B0, 0x01B2, 0x01B3, 0x01B4, 0x01B5, 0x01B6, 0x01B7, 0x01B8, 0x01B9, 0x01BA,
    0x01BB, 0x01BC, 0x01BE, 0x01BD, 0x01C0, 0x01C1, 0x01C2, 0x01C3, 0x01C4, 0x01B1,
};

void attach_fx_unlink_from_ctrl(struct224 *arg0);
void attach_fx_link_to_ctrl(struct224 *arg0);

/* was func_151D2AB0 */
void attach_fx_asset_acquire(s32 arg0) {
    u32 tmp;

    (&g_attach_fx_asset_refs)[arg0] = (&g_attach_fx_asset_refs)[arg0] + 1;

    if ((&g_attach_fx_asset_refs)[arg0] < 2) {
        g_attach_fx_assets[arg0] = asset_load(&tmp, 2, 9, g_attach_fx_asset_ids[arg0]);
        g_attach_fx_point_counts[arg0] = tmp >> 4;
    }
}

/* was func_151D2B4C */
void attach_fx_asset_release(s32 arg0) {
    if ((&g_attach_fx_asset_refs)[arg0] != 0) {
        (&g_attach_fx_asset_refs)[arg0] = (&g_attach_fx_asset_refs)[arg0] - 1;
        if ((&g_attach_fx_asset_refs)[arg0] == 0) {
            heap_set_block_tag(g_attach_fx_assets[arg0], 4);
        }
    }
}

/* was func_151D2BA4 */
struct224 *attach_fx_spawn(void *arg0, struct17 *arg1, s32 arg2, u8 arg3, s32 arg4) {
    struct224 *tmp = node_alloc(0x3D, arg4, arg2 + 0x48, 1, arg3, 1);

    if (tmp == NULL) {
        return NULL;
    }
    memcpy(&tmp->unk10, arg0, 0x24);
    *(struct17 *)&tmp->unk34 = *arg1;
    attach_fx_link_to_ctrl(tmp);
    return tmp;
}

// effect_child_update: one effect child per frame. Freed (node_destroy) when its parent object is gone / hidden /
// re-used (id +0x3B != child +0x14) or has no bone matrices. Otherwise its position is its offset +0x18 through the
// parent's bone matrix (+0x1D4, bone +0x24); a timed child (+0x28 bit 0) counts +0x26 down by g_frame_ticks and at
// expiry runs its end handler g_attach_child_end_fns[+0x2A] (node, &pos) and is freed; the update handler g_attach_child_update_fns[+0x29]
// (node, &pos) returning 0 frees it; else the position is stored at +0x34.
// NON_MATCHING copy: the handler table at 0x8008FFE0 (g_attach_child_update_fns [0..6], g_attach_child_end_fns = [2..6]) is called through one
// signature, s32 (child *, void *) (wasm call_indirect); variables.h declares g_attach_child_end_fns void-returning, so the
// end-handler call casts. The one-argument entries take and ignore the position (bone_sparks_tick, bone_sparks_burst,
// attach_ctrl_destroy_children, bone_sparks_release).
/* was func_151D2C40 */
void attach_fx_update(struct_eu_1FFF60_child *arg0) {
    struct_eu_1FFF60_parent *parent = arg0->unk10;
    struct17 pos;

    if (parent->unk0 == 0 || parent->unk4 == 0xFF || parent->unk3B != arg0->unk14 || parent->unk1D4 == NULL ||
        (parent->unk74 & 0xF) == 0xF) {
        node_destroy(arg0);
        return;
    }
    mtx_transform_point_or_origin(&arg0->unk18, &pos, parent->unk1D4 + (arg0->unk24 << 6));
    if (arg0->unk28 & 1) {
        arg0->unk26 -= g_frame_ticks;
        if (arg0->unk26 < 0) {
            if (arg0->unk2A != -1) {
                ((s32 (*)(struct_eu_1FFF60_child *, void *))g_attach_child_end_fns[arg0->unk2A])(arg0, &pos);
            }
            arg0->unk2C = 0;
            node_destroy(arg0);
            return;
        }
    }
    if (arg0->unk29 != -1) {
        if (g_attach_child_update_fns[arg0->unk29](arg0, &pos) == 0) {
            node_destroy(arg0);
            return;
        }
    }
    arg0->unk34 = pos;
}

/* was func_151D2DAC */
void attach_fx_detach(struct102 *arg0) {
    attach_fx_unlink_from_ctrl(arg0);
}

/* was func_151D2DCC */
void attach_fx_destroy(struct102 *arg0) {
    struct102 *tmp = arg0;

    attach_fx_detach(tmp);

    if (tmp->unk2C != 0) {
        node_destroy(tmp->unk2C);
    }
    node_retire(tmp);
}

/* was func_151D2E14 */
void attach_fx_delete(struct102 *arg0) {
    struct102 *tmp = arg0;

    attach_fx_detach(tmp);

    if (tmp->unk2C != 0) {
        node_delete(tmp->unk2C);
    }
    node_unlink_free(tmp);
}

/* was func_151D2E5C */
void attach_fx_handle_message(struct102 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_v0;
    s32 temp_v1;
    u8 t14;
    u8 t4;

    if (arg2 == 0) {
        temp_v0 = *(s32 *)((u8 *)arg0 + 0x10);
        temp_v1 = *(s32 *)(arg1 + 0);
        t14 = *((u8 *)arg0 + 0x14);
        t4 = *(arg1 + 4);
        if ((temp_v0 == temp_v1) || (t14 == t4)) {
            node_destroy(arg0);
        }
    } else if (arg2 == 0x2D) {
        temp_v0 = *(s32 *)(arg1 + 0);
        temp_v1 = *(s32 *)((u8 *)arg0 + 0x10);
        if (temp_v0 == *(s32 *)((u8 *)arg0 + 0x10)) { // fakematch: reread of the field flips the cmp operands
            *(s32 *)((u8 *)arg0 + 0x10) = *(s32 *)(arg1 + 4);
            *((u8 *)arg0 + 0x14) = *(arg1 + 9);
            return;
        }
        if (*(s32 *)(arg1 + 4) == *(s32 *)((u8 *)arg0 + 0x10)) { // fakematch: reread
            *(s32 *)((u8 *)arg0 + 0x10) = temp_v0;
            *((u8 *)arg0 + 0x14) = *(arg1 + 8);
        }
    }
}
// NON-MATCHING: one bnel has its operands swapped (bnel t9, v1)
// void attach_fx_handle_message(struct224 *arg0, struct223 *arg1, u8 arg2) {
//     s32 temp_v0;
//     s32 temp_v1;
//     u8 temp_a2;
//     u8 temp_a3;
//
//     if (arg2 == 0) {
//         temp_v0 = arg0->unk10;
//         temp_v1 = arg1->unk0;
//         temp_a2 = arg0->unk14;
//         temp_a3 = arg1->unk4.ub;
//         if (temp_v0 == temp_v1 || temp_a2 == temp_a3) {
//             node_destroy(arg0);
//         }
//     } else if (arg2 == 0x2D) {
//         temp_v0 = arg1->unk0;
//         temp_v1 = arg0->unk10;
//         if (temp_v0 == temp_v1) {
//             arg0->unk10 = arg1->unk4.w;
//             arg0->unk14 = arg1->unk9;
//         } else if (arg1->unk4.w == temp_v1) {
//             arg0->unk10 = temp_v0;
//             arg0->unk14 = arg1->unk8;
//         }
//     }
// }

/* was func_151D2F00 */
void *attach_ctrl_spawn(void *arg0, s32 arg1, u8 arg2, s32 arg3) {
    u8 *temp_v0 = node_alloc(0x3E, arg3, arg1 + 0x30, 1, arg2, 1);

    if (temp_v0 == NULL) {
        return NULL;
    }
    memcpy(temp_v0 + 0x10, arg0, 0x10);
    *(s16 *)(temp_v0 + 0x20) = 0;
    *(s32 *)(temp_v0 + 0x24) = 0;
    *(s32 *)(temp_v0 + 0x28) = 0;
    temp_v0[0x18] &= ~2;
    return temp_v0;
}

extern s32 (*g_attach_ctrl_update_fns[])(u8 *); /* was D_8008FFEC */
extern void (*g_attach_ctrl_show_fns[])(u8 *); /* was D_8008FFF0 */
extern void (*g_attach_ctrl_hide_fns[])(u8 *); /* was D_8008FFF4 */
extern void (*g_attach_ctrl_expire_fns[])(u8 *); /* was D_8008FFF8 */

/* was func_151D2F90 */
void attach_ctrl_update(u8 *arg0) {
    u8 *p = *(u8 **)(arg0 + 0x10);
    u8 old = arg0[0x18] & 2;
    s8 w;
    u8 cur;

    if (*(s32 *)p == 0 || p[4] == 0xFF || arg0[0x14] != p[0x3B]) {
        node_destroy((struct102 *)arg0);
        return;
    }
    if (*(s32 *)(p + 0x1D4) != 0 && (p[0x74] & 0xF) != 0xF) {
        arg0[0x18] |= 2;
    } else {
        arg0[0x18] &= ~2;
    }
    if (arg0[0x18] & 1) {
        *(s16 *)(arg0 + 0x16) -= g_frame_ticks;
        if (*(s16 *)(arg0 + 0x16) < 0) {
            w = arg0[0x1C];
            if (w != -1) {
                g_attach_ctrl_expire_fns[w](arg0);
            }
            node_destroy((struct102 *)arg0);
            return;
        }
    }
    cur = arg0[0x18] & 2;
    if (old != cur) {
        if (cur) {
            g_attach_ctrl_show_fns[(s8)arg0[0x1A]](arg0);
        } else {
            g_attach_ctrl_hide_fns[(s8)arg0[0x1B]](arg0);
        }
    }
    w = arg0[0x19];
    if (w != -1 && !g_attach_ctrl_update_fns[w](arg0)) {
        node_destroy((struct102 *)arg0);
    }
}

// effect_node_release: runs the node's release hook g_attach_ctrl_release_fns[+0x1D] (if any), then for every child (list +0x24,
// next +0x40) its end handler g_attach_child_end_fns[+0x2A] (child, &child +0x34) and frees it (node_destroy), then releases
// the node (char_fx_detach_effect with +0x10).
// NON_MATCHING copy: the end handler is called through the table's common signature s32 (child *, void *) (see
// attach_fx_update).
/* was func_151D3130 */
void attach_ctrl_cleanup(struct_eu_1FFF60 *arg0) {
    struct_eu_1FFF60_child *child;

    if (g_attach_ctrl_release_fns[arg0->unk1D] != NULL) {
        g_attach_ctrl_release_fns[arg0->unk1D](arg0);
    }
    child = arg0->unk24;
    while (child != NULL) {
        struct_eu_1FFF60_child *next = child->unk40;
        if (child->unk2A != -1) {
            ((s32 (*)(struct_eu_1FFF60_child *, void *))g_attach_child_end_fns[child->unk2A])(child, &child->unk34);
        }
        child->unk2C = 0;
        node_destroy(child);
        child = next;
    }
    char_fx_detach_effect(arg0, arg0->unk10);
}

/* was func_151D31F4 */
void attach_ctrl_destroy(struct102 *arg0) {
    attach_ctrl_cleanup(arg0);
    node_retire(arg0);
}

/* was func_151D3220 */
void attach_ctrl_delete(struct102 *arg0) {
    attach_ctrl_cleanup(arg0);
    node_unlink_free(arg0);
}

extern s32 g_attach_ctrl_message_fns[]; /* was D_80090004 */
void attach_ctrl_free_if_owner(struct224 *, struct223 *);
/* was func_151D324C */
void attach_ctrl_handle_message(struct224 *arg0, struct223 *arg1, u8 arg2) {
    s32 (*temp_v0_2)(struct224 *, struct223 *, u8);
    if (arg2 == 0) {
        attach_ctrl_free_if_owner(arg0, arg1);
        goto dummy_label; dummy_label: ;
    } else if (arg2 == 0x2D) {
        if (arg0->unk10 == arg1->unk0) {
            arg0->unk10 = arg1->unk4.w;
            arg0->unk14 = arg1->unk9;
        } else if (arg0->unk10 == arg1->unk4.w) {
            arg0->unk10 = arg1->unk0;
            arg0->unk14 = arg1->unk8;
        }
    }
    temp_v0_2 = (void *)g_attach_ctrl_message_fns[arg0->pad15[8]];
    if (temp_v0_2 != NULL) {
        temp_v0_2(arg0, arg1, arg2);
    }
}

/* was func_151D3308 */
void attach_fx_link_to_ctrl(struct224 *arg0) {
    struct224 *temp_v0;
    struct224 *temp_v1;

    temp_v0 = arg0->unk30;
    if (temp_v0 != 0) {
        arg0->unk40 = temp_v0->unk24;
        temp_v1 = temp_v0->unk24;
        if (temp_v1 != 0) {
            temp_v1->unk44 = arg0;
        } else {
            temp_v0->unk28 = arg0;
        }
        arg0->unk44 = 0;
        temp_v0->unk24 = arg0;
        temp_v0->unk20 += 1;
        arg0->unk30 = temp_v0;
    }
}

/* was func_151D3354 */
void attach_fx_unlink_from_ctrl(struct224 *arg0) {
    struct224 *temp_v0;
    struct224 *temp_v1;
    struct224 *temp_v2;

    if (arg0->unk30) {
        temp_v0 = arg0->unk30;
        if (temp_v1 = arg0->unk44) {
            temp_v1->unk40 = arg0->unk40;
        } else {
            temp_v0->unk24 = arg0->unk40;
        }

        if (temp_v2 = arg0->unk40) {
            temp_v2->unk44 = arg0->unk44;
        } else {
            temp_v0->unk28 = arg0->unk44;
        }

        temp_v0->unk20 -= 1;
    }
}

// effect_node_children_free: effect-child handler (g_attach_child_update_fns [5] / g_attach_child_end_fns [3]): frees the node's children
// (node_destroy on the first child +0x24 while the count +0x20 is above 0; each free unlinks it). The second
// argument (the position the dispatchers pass) is unused; s32 return and the second parameter are the table's common
// signature s32 (node, pos) (wasm call_indirect). Returns 0 (the dispatchers that reach it ignore v0).
/* was func_151D33B8 */
s32 attach_ctrl_destroy_children(struct224 *arg0, void *pos) {
    while (arg0->unk20 > 0) {
        node_destroy(arg0->unk24);
    }
    return 0;
}

/* was func_151D33FC */
void attach_ctrl_free_if_owner(struct224 *arg0, struct223 *arg1) {
    s32 tmp0;
    s32 tmp1;
    s32 tmp2;
    s32 tmp3;

    tmp0 = arg0->unk10;
    tmp1 = arg0->unk14;
    tmp2 = arg1->unk4.ub;
    tmp3 = arg1->unk0;
    if ((tmp0 == tmp3) || (tmp2 == tmp1)) {
        node_destroy(arg0);
    }
}

/* was func_151D343C */
void attach_ctrl_broadcast(s32 arg0, u8 arg1) {
    const s32 sp1C[1] = {0x3E};

    node_broadcast_types(sp1C, 0x1, arg0, arg1);
}
