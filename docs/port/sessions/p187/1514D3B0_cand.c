s32 func_1514DA28();   /* K&R definition below (s16 state, s16 base) */
extern s32 (*D_8008AF04[])(u8 *, s32, s32);   /* state event handlers: func_1514EE0C .. func_1514F0FC (8) */
// obj_state_event_dispatch: sends an event (arg2, arg3) to every state node of obj (list at +0x2F4, linked through
// +0x14) whose state (+0x1C) is `state` or derives from it (func_1514DA28 on the state table D_8008AF88); each
// matching node's state record names its handler (s16 at +0, -1 = none) in D_8008AF04, called with the node's data
// (+0x10). Returns whether the last handler called accepted the event (0 when none was called).
// Callers: func_15079390 (game_A28B0), func_15024910 (game_eu_51190, state 0xD with an animation), func_150EDCC8.
s32 func_1514D3B0(s32 obj, s16 state, u8 arg2, u8 arg3) {
    u8 *node;
    s16 idx;
    s32 handled;

    handled = 0;
    for (node = *(u8 **) ((u8 *) obj + 0x2F4); node != NULL; node = *(u8 **) (node + 0x14)) {
        if (state != *(s16 *) (node + 0x1C)
            && func_1514DA28(*(s16 *) (D_8008AF88[state] + 4), *(s16 *) (node + 0x1C)) == 0) {
            continue;
        }
        idx = *(s16 *) D_8008AF88[*(s16 *) (node + 0x1C)];
        if (idx != -1) {
            handled = D_8008AF04[idx](*(u8 **) (node + 0x10), arg2, arg3) != 0;
        }
    }
    return handled;
}
