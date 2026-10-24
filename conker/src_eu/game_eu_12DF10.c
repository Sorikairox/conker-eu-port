#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15100700(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151494E0(&tmp, 0x48);
}

void func_15100734(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
        s16 unk6;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk6 = 0;
    temp_v0 = func_15149130(300, -1, 0x4E, -1, 0, 0x3B, 8, 255, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 8);
    }
}

#ifdef NON_MATCHING
// linked_obj_event_48: event handler of an object whose link record sits at +0x28 ({ s32 id, u8 key }): event 0x48 removes the
// object (func_1516972C) when the event's record matches by id or by key; any other event goes to the common
// handler func_15149514.
void func_151007B0(struct102 *obj, u8 *ev, u8 type) {
    u8 *link = (u8 *) obj + 0x28;

    if (type == 0x48) {
        if (*(s32 *) link == *(s32 *) ev || link[4] == ev[4]) {
            func_1516972C(obj);
        }
    } else {
        func_15149514((s32) ev, type, (s32) link, (s32) (link + 4), (s32) obj);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12DF10/func_151007B0.s")
#endif

void func_1510083C(u8 *arg0)
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
