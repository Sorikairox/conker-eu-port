#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_15100700 */
void obj_timer_link_post_remove(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    effect_nodes_broadcast(&tmp, 0x48);
}

/* was func_15100734 */
void obj_timer_link_spawn(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
        s16 unk6;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk6 = 0;
    temp_v0 = effect_node_create(300, -1, 0x4E, -1, 0, 0x3B, 8, 255, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 8);
    }
}

// linked_obj_event_48: event handler of an object whose link record sits at +0x28 ({ s32 id, u8 key }): event 0x48 removes the
// object (node_destroy) when the event's record matches by id or by key; any other event goes to the common
// handler effect_node_link_message.
/* was func_151007B0 */
void obj_timer_link_handle_event(struct102 *obj, u8 *ev, u8 type) {
    u8 *link = (u8 *) obj + 0x28;

    if (type == 0x48) {
        if (*(s32 *) link == *(s32 *) ev || link[4] == ev[4]) {
            node_destroy(obj);
        }
    } else {
        effect_node_link_message((s32) ev, type, (s32) link, (s32) (link + 4), (s32) obj);
    }
}

/* was func_1510083C */
void obj_timer_link_update(u8 *arg0)
{
  u8 *q = arg0 + 0x28;
  u8 *o = *(u8 **)q;
  if (*(s32 *)o == 0 || o[4] == 0xFF || q[4] != o[0x3B]) {
    *(s16 *)(arg0 + 0xE) = -1;
    return;
  }
  if (*(s32 *)(o + 0x318) != 0) {
    *(s16 *)(q + 6) -= D_800BE9E4;
  }
}
