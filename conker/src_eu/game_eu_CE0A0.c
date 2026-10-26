#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 trigger_set_disabled(s32, s32);

/* was func_150A0890 */
s32 event_action_trigger(s32 arg0, u32 arg1, u8 *arg2) {
    switch (arg1) {
    case 0:
        trigger_set_disabled(arg0, 0);
        return 1;
    case 1:
        trigger_set_disabled(arg0, 1);
        return 1;
    case 2:
        trigger_set_kind_args(arg0, (*(s32 *)(arg2 + 8)), (*(s32 *)(arg2 + 0xC)));
        return 1;
    case 3:
        trigger_set_position(arg0, (*(s16 *)(arg2 + 0xA)), (*(s16 *)(arg2 + 0xE)), (*(s16 *)(arg2 + 0x12)));
        return 0;
    case 4:
        trigger_set_fields_masked(arg0, (u16) (*(s16 *)(arg2 + 0xA)), (*(s32 *)(arg2 + 0xC)), (*(s32 *)(arg2 + 0x10)), (*(s32 *)(arg2 + 0x14)), (*(s32 *)(arg2 + 0x18)));
        return 0;
    case 5:
        laser_switch_broadcast(*(s32 *)(arg2 + 8) == 0x3E7 ? 2 : (*(s32 *)(arg2 + 8) != 0 ? 0 : 1), (arg0 * 0x34) + D_800D34B8);
        break;
    }
    return 0;
}

#ifdef NON_MATCHING
/* Sequence-slot query handler: entry 3 of event_dispatch's handler table D_80088838, called as
 * handler(slot, cmd, args) like event_query_object (args[2] = first extra argument, D_800D3C60 = number of words).
 * `slot` indexes the 0x34-byte records at D_800D34B8 (the per-slot words +0x17 / +0x18 / +0x1C / +0x20 that
 * trigger_get_fields / trigger_set_fields_masked read and write). Object ids passed as arguments drop bits 12..15; their kind is
 * bits 12..15: 0x2000 = an object (obj_find_by_spawn, index in D_800CC2D0), 0x9000 = a player / character id. */
s32 trigger_find_touching_player(s32);
s32 trigger_test_camera(s32, u32);
s32 trigger_plane_side_object(s32, s32);
s32 trigger_plane_side_camera(s32, s32);
void trigger_get_fields(s32, s32 *, s32 *, s32 *, s32 *);
extern s32 D_800D3C60;

#define B9B8_SLOT(i) (D_800D34B8 + (i) * 0x34)
#define B9B8_OBJ(i) ((u8 *)D_800CC2D0 + (i) * 0x32C)   /* object i of D_800CC2D0 (0x32C each) */
#define B9B8_INDEX(p) (((u8 *)(p) - (u8 *)D_800CC2D0) / 0x32C)

/* was func_150A09B8 */
s32 event_query_trigger(s32 slot, s32 cmd, s32 *args) {
    s32 arg;
    s32 r;
    s32 a, b, flag, c;
    s32 i;
    u8 *obj;
    u8 *slotp;

    switch (cmd) {
    case 6: /* is the object / character not attached to this slot? */
        arg = args[2];
        r = 0; /* the original leaves r uninitialised for any other kind (stack word, 0 in practice) */
        switch (arg & 0xF000) {
        case 0x2000:
            obj = (u8 *)obj_find_by_spawn(arg & 0xFFFF0FFF);
            if (obj == NULL) {
                return 0;
            }
            r = trigger_test_player(B9B8_INDEX(obj), slot);
            break;
        case 0x9000:
            r = trigger_test_camera(arg & 0xFFFF0FFF, slot);
            break;
        }
        return r == 0;
    case 7:
        return B9B8_SLOT(slot)[0x14];
    case 8:
    case 9:
        trigger_get_fields(slot, &a, &b, &flag, &c);
        if (flag == 0) {
            return 0;
        }
        if (cmd == 8) {
            return D_800C35EA == 0;
        }
        return D_800C35EA == 1;
    case 0xA: /* packed x << 16 | z */
        slotp = B9B8_SLOT(slot);
        return (*(s16 *)(slotp + 0) << 16) | (u16)*(s16 *)(slotp + 4);
    case 0xB:
    case 0xC: /* first object of D_800CC2D0 with id args[2] that is attached to this slot */
        for (i = 0; i < 25; i++) {
            obj = B9B8_OBJ(i);
            if (*(s32 *)obj == args[2] && trigger_test_player(i, slot) == 0) {
                if (cmd == 0xB) {
                    return obj[0x13F] | 0x2000;
                }
                return obj[0x3B];
            }
        }
        return 0;
    case 0xD:
        arg = args[2];
        r = 0; /* uninitialised in the original for any other kind */
        switch (arg & 0xF000) {
        case 0x2000:
            obj = (u8 *)obj_find_by_spawn(arg & 0xFFFF0FFF);
            r = trigger_plane_side_object(B9B8_INDEX(obj), slot);
            break;
        case 0x9000:
            r = trigger_plane_side_camera(arg & 0xFFFF0FFF, slot);
            break;
        }
        return r;
    case 0xE:
        return *(s16 *)(B9B8_SLOT(slot) + 2);
    case 0xF:
        return trigger_find_touching_player(slot) != -1;
    case 0x10:
        if (trigger_find_touching_player(slot) != -1) {
            return 1;
        }
        for (i = 0; i < D_80090130; i++) {
            if (trigger_test_camera(i, slot) != 0) {
                continue;
            }
            /* character i is attached: with a second argument it must not be in state 3 and not attached to
             * the object args[2] */
            if (D_800D3C60 == 2 || args[3] == 0) {
                return 1;
            }
            if ((*(u8 **)(B9B8_OBJ(i) + 0x31C))[0x78] != 3 && trigger_test_camera(i, args[2] & 0xFFFF0FFF) == 0) {
                return 1;
            }
        }
        return 0;
    case 0x11:
        slotp = B9B8_SLOT(slot);
        switch (args[2]) {
        case 0:
            return slotp[0x17];
        case 1:
            return *(s32 *)(slotp + 0x18);
        case 2:
            return *(s32 *)(slotp + 0x1C);
        case 3:
            return *(s32 *)(slotp + 0x20);
        }
        return 0;
    case 0x12:
        return (s32)*(f32 *)(B9B8_SLOT(slot) + 0x10);
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE0A0/event_query_trigger.s")
#endif
